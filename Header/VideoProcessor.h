#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>
#include <opencv.hpp>
#include <core/mat.hpp> 
#include <imgcodecs.hpp> 
#include "GifConverter.h"

class VideoProcessor : public QObject {
	Q_OBJECT

public:
	explicit VideoProcessor(QObject *parent = nullptr);
	void SetVideoPath(const QString &path);

	void SetOutputVideoName(QString temp);

private:
	QString videoPath;
	QString outputVideoName;
	QString tempOutputVideoName;
	QImage MatToQImage(const cv::Mat &mat);
	void SetVideoFrame(cv::VideoCapture video, int frame);
	int FrameCounter(cv::VideoCapture video);
	int VideoTimeCalculator(cv::VideoCapture video);
	cv::VideoCapture cutCapture;

	GifConverter *gifMaker;

	QMutex mutex;
	QWaitCondition pauseCondition;
	bool paused = true;
	bool isTimeChanged = false;
	bool isCutterWorking = false;
	int frameNumber = 0;
	int firstCutterFrame = 0;
	int secondCutterFrame = 0;

signals:
	void frameReady(const QImage &frame);
	void finished();
	void totalFrameCounterSignal(const int &frameCount, const int &fps);
	void frameCounterSignal(const int &frameCount);

public slots:
	void ProcessVideo();
	void VideoCutter(int firstFrame, int secondFrame);
	void FrameHolder(int firstFrame, int secondFrame);
	void Pause(bool checked);
	void Play(bool checked);
	void Cutter(bool checked, int first, int second);
	void VideoTimeChanged(int frameN);

};

#endif // VIDEOPROCESSOR
