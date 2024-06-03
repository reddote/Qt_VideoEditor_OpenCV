#ifndef GIF_H
#define GIF_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

struct GifPalette
{
    int bitDepth;
    uint8_t r[256];
    uint8_t g[256];
    uint8_t b[256];

    // k-d tree over RGB space, organized in heap fashion
    int treeSplitElt[255];
    int treeSplit[255];
};

struct GifWriter
{
    FILE* f;
    uint8_t* oldImage;
    bool firstFrame;
};

struct GifBitStatus
{
    // Output bit stream
    uint8_t bitIndex;  // How many bits are currently in the bit buffer?
    uint8_t byte;      // Current byte being assembled
    int32_t chunkIndex;
    uint8_t chunk[256];
};

inline int GifIMax(int l, int r) { return l > r ? l : r; }
inline int GifIMin(int l, int r) { return l < r ? l : r; }
inline int GifIAbs(int i) { return i < 0 ? -i : i; }

inline void GifGetClosestPaletteColor(struct GifPalette* pPal, int r, int g, int b, int* bestInd, int* bestDiff, int treeRoot)
{
    // Base case, reached the bottom of the tree
    if (treeRoot > (1 << pPal->bitDepth) - 1)
    {
        int ind = treeRoot - (1 << pPal->bitDepth);
        if (ind == 256)
            return;

        int r_err = GifIAbs(pPal->r[ind] - r);
        int g_err = GifIAbs(pPal->g[ind] - g);
        int b_err = GifIAbs(pPal->b[ind] - b);
        int diff = r_err * r_err + g_err * g_err + b_err * b_err;

        if (diff < *bestDiff)
        {
            *bestInd = ind;
            *bestDiff = diff;
        }

        return;
    }

    // Recurse down the tree
    int comps[3];
    comps[0] = r;
    comps[1] = g;
    comps[2] = b;

    int splitComp = comps[pPal->treeSplitElt[treeRoot]];

    if (splitComp < pPal->treeSplit[treeRoot])
    {
        GifGetClosestPaletteColor(pPal, r, g, b, bestInd, bestDiff, treeRoot * 2);
        if (*bestDiff > (splitComp - pPal->treeSplit[treeRoot]) * (splitComp - pPal->treeSplit[treeRoot]))
            GifGetClosestPaletteColor(pPal, r, g, b, bestInd, bestDiff, treeRoot * 2 + 1);
    }
    else
    {
        GifGetClosestPaletteColor(pPal, r, g, b, bestInd, bestDiff, treeRoot * 2 + 1);
        if (*bestDiff > (splitComp - pPal->treeSplit[treeRoot]) * (splitComp - pPal->treeSplit[treeRoot]))
            GifGetClosestPaletteColor(pPal, r, g, b, bestInd, bestDiff, treeRoot * 2);
    }
}

inline void GifSwapPixels(uint8_t* image, int pixA, int pixB)
{
    uint8_t rA = image[pixA * 4];
    uint8_t gA = image[pixA * 4 + 1];
    uint8_t bA = image[pixA * 4 + 2];
    uint8_t aA = image[pixA * 4 + 3];

    uint8_t rB = image[pixB * 4];
    uint8_t gB = image[pixB * 4 + 1];
    uint8_t bB = image[pixB * 4 + 2];
    uint8_t aB = image[pixB * 4 + 3];

    image[pixA * 4] = rB;
    image[pixA * 4 + 1] = gB;
    image[pixA * 4 + 2] = bB;
    image[pixA * 4 + 3] = aB;

    image[pixB * 4] = rA;
    image[pixB * 4 + 1] = gA;
    image[pixB * 4 + 2] = bA;
    image[pixB * 4 + 3] = aA;
}

inline int GifPartition(uint8_t* image, int left, int right, int elt, int pivotIndex)
{
    const int pivotValue = image[(pivotIndex) * 4 + elt];
    GifSwapPixels(image, pivotIndex, right - 1);
    int storeIndex = left;
    bool split = 0;
    for (int ii = left; ii < right - 1; ++ii)
    {
        int arrayVal = image[ii * 4 + elt];
        if (arrayVal < pivotValue)
        {
            GifSwapPixels(image, ii, storeIndex);
            ++storeIndex;
        }
        else if (arrayVal == pivotValue)
        {
            if (split)
            {
                GifSwapPixels(image, ii, storeIndex);
                ++storeIndex;
            }
            split = !split;
        }
    }
    GifSwapPixels(image, storeIndex, right - 1);
    return storeIndex;
}

inline void GifPartitionByMedian(uint8_t* image, int left, int right, int com, int neededCenter)
{
    if (left < right - 1)
    {
        int pivotIndex = left + (right - left) / 2;

        pivotIndex = GifPartition(image, left, right, com, pivotIndex);

        if (pivotIndex > neededCenter)
            GifPartitionByMedian(image, left, pivotIndex, com, neededCenter);

        if (pivotIndex < neededCenter)
            GifPartitionByMedian(image, pivotIndex + 1, right, com, neededCenter);
    }
}

inline void GifSplitPalette(uint8_t* image, int numPixels, int firstElt, int lastElt, int splitElt, int splitDist, int treeNode, bool buildForDither, struct GifPalette* pal)
{
    if (firstElt == lastElt)
    {
        pal->r[treeNode] = image[firstElt * 4 + 0];
        pal->g[treeNode] = image[firstElt * 4 + 1];
        pal->b[treeNode] = image[firstElt * 4 + 2];
        return;
    }

    int splitCom = splitElt % 3;

    int medianIdx = numPixels / 2;
    GifPartitionByMedian(image, firstElt, lastElt + 1, splitCom, firstElt + medianIdx);

    pal->treeSplitElt[treeNode] = splitCom;
    pal->treeSplit[treeNode] = image[(firstElt + medianIdx) * 4 + splitCom];

    GifSplitPalette(image, medianIdx, firstElt, firstElt + medianIdx, splitElt + 1, splitDist / 2, treeNode * 2, buildForDither, pal);
    GifSplitPalette(image + medianIdx * 4, numPixels - medianIdx, firstElt + medianIdx, lastElt, splitElt + 1, splitDist / 2, treeNode * 2 + 1, buildForDither, pal);
}

inline int GifPickChangedPixels(const uint8_t* lastFrame, uint8_t* frame, int numPixels)
{
    int numChanged = 0;
    const int threshold = 3;
    for (int ii = 0; ii < numPixels; ++ii)
    {
        const int r = frame[ii * 4 + 0];
        const int g = frame[ii * 4 + 1];
        const int b = frame[ii * 4 + 2];
        const int a = frame[ii * 4 + 3];

        const int lr = lastFrame[ii * 4 + 0];
        const int lg = lastFrame[ii * 4 + 1];
        const int lb = lastFrame[ii * 4 + 2];
        const int la = lastFrame[ii * 4 + 3];

        const int diffR = GifIAbs(r - lr);
        const int diffG = GifIAbs(g - lg);
        const int diffB = GifIAbs(b - lb);
        const int diffA = GifIAbs(a - la);

        if (diffR + diffG + diffB + diffA > threshold)
        {
            ++numChanged;
        }
        else
        {
            frame[ii * 4 + 0] = 0;
            frame[ii * 4 + 1] = 0;
            frame[ii * 4 + 2] = 0;
            frame[ii * 4 + 3] = 0;
        }
    }

    return numChanged;
}

inline void GifMakePalette(const uint8_t* lastFrame, const uint8_t* nextFrame, unsigned int width, unsigned int height, int bitDepth, bool buildForDither, struct GifPalette* pPal)
{
    int numPixels = width * height;
    uint8_t* destroyableImage = (uint8_t*)malloc(numPixels * 4);
    memcpy(destroyableImage, nextFrame, numPixels * 4);

    if (lastFrame && buildForDither)
    {
        int numChanged = GifPickChangedPixels(lastFrame, destroyableImage, numPixels);
        numPixels = numChanged;
    }

    GifSplitPalette(destroyableImage, numPixels, 0, numPixels - 1, 0, 128, 1, buildForDither, pPal);

    free(destroyableImage);
}

inline void GifDitherImage(const uint8_t* lastFrame, const uint8_t* nextFrame, uint8_t* outFrame, unsigned int width, unsigned int height, struct GifPalette* pPal)
{
    int numPixels = width * height;
    for (int ii = 0; ii < numPixels; ++ii)
    {
        int r = nextFrame[ii * 4 + 0];
        int g = nextFrame[ii * 4 + 1];
        int b = nextFrame[ii * 4 + 2];
        int a = nextFrame[ii * 4 + 3];

        if (lastFrame)
        {
            r -= lastFrame[ii * 4 + 0];
            g -= lastFrame[ii * 4 + 1];
            b -= lastFrame[ii * 4 + 2];
            a -= lastFrame[ii * 4 + 3];
        }

        outFrame[ii * 4 + 0] = (uint8_t)GifIMax(0, GifIMin(255, r + 127));
        outFrame[ii * 4 + 1] = (uint8_t)GifIMax(0, GifIMin(255, g + 127));
        outFrame[ii * 4 + 2] = (uint8_t)GifIMax(0, GifIMin(255, b + 127));
        outFrame[ii * 4 + 3] = (uint8_t)GifIMax(0, GifIMin(255, a + 127));
    }
}

inline void GifThresholdImage(const uint8_t* lastFrame, const uint8_t* nextFrame, uint8_t* outFrame, unsigned int width, unsigned int height, struct GifPalette* pPal)
{
    int numPixels = width * height;
    for (int ii = 0; ii < numPixels; ++ii)
    {
        int r = nextFrame[ii * 4 + 0];
        int g = nextFrame[ii * 4 + 1];
        int b = nextFrame[ii * 4 + 2];
        int a = nextFrame[ii * 4 + 3];

        if (lastFrame)
        {
            r -= lastFrame[ii * 4 + 0];
            g -= lastFrame[ii * 4 + 1];
            b -= lastFrame[ii * 4 + 2];
            a -= lastFrame[ii * 4 + 3];
        }

        outFrame[ii * 4 + 0] = (uint8_t)GifIMax(0, GifIMin(255, r + 127));
        outFrame[ii * 4 + 1] = (uint8_t)GifIMax(0, GifIMin(255, g + 127));
        outFrame[ii * 4 + 2] = (uint8_t)GifIMax(0, GifIMin(255, b + 127));
        outFrame[ii * 4 + 3] = (uint8_t)GifIMax(0, GifIMin(255, a + 127));
    }
}

inline void GifWriteBit(struct GifBitStatus* stat, uint32_t bit)
{
    bit &= 1;
    bit <<= stat->bitIndex;
    stat->byte |= bit;

    ++stat->bitIndex;
    if (stat->bitIndex > 7)
    {
        stat->chunk[stat->chunkIndex++] = stat->byte;
        stat->bitIndex = 0;
        stat->byte = 0;
    }
}

inline void GifWriteChunk(FILE* f, struct GifBitStatus* stat)
{
    fputc(stat->chunkIndex, f);
    fwrite(stat->chunk, 1, stat->chunkIndex, f);
    stat->chunkIndex = 0;
}

inline void GifWriteCode(FILE* f, struct GifBitStatus* stat, uint32_t code, uint32_t length)
{
    for (uint32_t ii = 0; ii < length; ++ii)
    {
        GifWriteBit(stat, code);
        code >>= 1;

        if (stat->chunkIndex == 255)
        {
            GifWriteChunk(f, stat);
        }
    }
}

inline void GifWritePalette(const struct GifPalette* pPal, FILE* f)
{
    fputc(0, f);
    fputc(255, f);
    fputc(0, f);

    for (int ii = 0; ii < (1 << pPal->bitDepth); ++ii)
    {
        fputc(pPal->r[ii], f);
        fputc(pPal->g[ii], f);
        fputc(pPal->b[ii], f);
    }
}

inline void GifWriteLzwImage(FILE* f, uint8_t* image, uint32_t left, uint32_t top, uint32_t width, uint32_t height, uint32_t delay, struct GifPalette* pPal)
{
    const uint32_t kStartLZWCode = 1 << 8;
    uint32_t nextCode = kStartLZWCode + 2;

    struct GifBitStatus stat = { 0 };

    uint32_t clearCode = kStartLZWCode;
    GifWriteCode(f, &stat, clearCode, kStartLZWCode + 1);

    uint32_t codeSize = kStartLZWCode + 1;
    uint32_t maxCode = 1 << codeSize;
    uint32_t suffix = image[0];
    uint32_t prefix = suffix;

    for (int ii = 1; ii < width * height; ++ii)
    {
        suffix = image[ii];
        uint32_t key = (prefix << 8) | suffix;
        if (key < nextCode)
        {
            prefix = key;
        }
        else
        {
            GifWriteCode(f, &stat, prefix, codeSize);
            if (nextCode < 4096)
            {
                ++codeSize;
                maxCode <<= 1;
                prefix = suffix;
                ++nextCode;
            }
            else
            {
                GifWriteCode(f, &stat, clearCode, kStartLZWCode + 1);
                nextCode = kStartLZWCode + 2;
                codeSize = kStartLZWCode + 1;
                maxCode = 1 << codeSize;
                prefix = suffix;
            }
        }
    }

    GifWriteCode(f, &stat, prefix, codeSize);
    GifWriteCode(f, &stat, kStartLZWCode + 1, kStartLZWCode + 1);

    GifWriteChunk(f, &stat);
}

inline bool GifBegin(struct GifWriter* writer, const char* filename, uint32_t width, uint32_t height, uint32_t delay, int bitDepth, bool dither)
{
    writer->f = fopen(filename, "wb");
    if (!writer->f)
        return false;

    fputc('G', writer->f);
    fputc('I', writer->f);
    fputc('F', writer->f);
    fputc('8', writer->f);
    fputc('9', writer->f);
    fputc('a', writer->f);

    fwrite(&width, 1, 2, writer->f);
    fwrite(&height, 1, 2, writer->f);

    fputc(0xF7, writer->f);
    fputc(0, writer->f);
    fputc(0, writer->f);

    struct GifPalette pPal;
    pPal.bitDepth = bitDepth;
    if (dither)
    {
        pPal.r[0] = 0;
        pPal.g[0] = 0;
        pPal.b[0] = 0;
    }
    else
    {
        for (int ii = 0; ii < 256; ++ii)
        {
            pPal.r[ii] = ii;
            pPal.g[ii] = ii;
            pPal.b[ii] = ii;
        }
    }

    GifWritePalette(&pPal, writer->f);

    writer->firstFrame = true;
    writer->oldImage = NULL;

    return true;
}

inline bool GifWriteFrame(struct GifWriter* writer, const uint8_t* image, uint32_t width, uint32_t height, uint32_t delay, int bitDepth, bool dither)
{
    if (!writer->firstFrame)
    {
        fwrite(",", 1, 1, writer->f);

        fwrite(&width, 1, 2, writer->f);
        fwrite(&height, 1, 2, writer->f);

        fputc(0, writer->f);
        fputc(0, writer->f);
        fputc(0, writer->f);

        fputc(0, writer->f);

        GifWriteLzwImage(writer->f, (uint8_t*)image, 0, 0, width, height, delay, NULL);
    }
    else
    {
        fwrite("!", 1, 1, writer->f);
        fputc(0xF9, writer->f);
        fputc(4, writer->f);
        fputc(0, writer->f);
        fwrite(&delay, 1, 2, writer->f);
        fputc(0, writer->f);
        fputc(0, writer->f);

        fwrite(",", 1, 1, writer->f);

        fwrite(&width, 1, 2, writer->f);
        fwrite(&height, 1, 2, writer->f);

        fputc(0, writer->f);
        fputc(0, writer->f);
        fputc(0, writer->f);

        struct GifPalette pPal;
        pPal.bitDepth = bitDepth;
        if (dither)
        {
            pPal.r[0] = 0;
            pPal.g[0] = 0;
            pPal.b[0] = 0;
        }
        else
        {
            for (int ii = 0; ii < 256; ++ii)
            {
                pPal.r[ii] = ii;
                pPal.g[ii] = ii;
                pPal.b[ii] = ii;
            }
        }

        GifWritePalette(&pPal, writer->f);

        GifWriteLzwImage(writer->f, (uint8_t*)image, 0, 0, width, height, delay, &pPal);

        writer->firstFrame = false;
        writer->oldImage = (uint8_t*)malloc(width * height * 4);
    }

    memcpy(writer->oldImage, image, width * height * 4);

    return true;
}

inline bool GifEnd(struct GifWriter* writer)
{
    fputc(';', writer->f);
    fclose(writer->f);
    free(writer->oldImage);
    writer->f = NULL;
    writer->oldImage = NULL;
    return true;
}

#endif // GIF_H
