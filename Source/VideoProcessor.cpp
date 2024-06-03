#include "..\Header\VideoProcessor.h"
#include <QDebug>

VideoProcessor::VideoProcessor(QObject *parent) : QObject(parent) {
	outputVideoName = "C:\\Users\\3DDL\\Desktop\\Qt_VideoEditor_Tool\\";
	tempOutputVideoName = outputVideoName + "output.mp4";
}

void VideoProcessor::SetVideoPath(const QString &path) {
	videoPath = path;
}

void VideoProcessor::SetOutputVideoName(QString temp){
	tempOutputVideoName = "";
	tempOutputVideoName = outputVideoName + temp;
}

void VideoProcessor::ProcessVideo() {
	if (videoPath.isEmpty()) {
		qDebug() << "Video path is empty";
		emit finished();
		return;
	}

	cv::VideoCapture capture(videoPath.toStdString());
	cutCapture = cv::VideoCapture(videoPath.toStdString());

	if (!capture.isOpened()) {
		qDebug() << "Error: Could not open video file.";
		emit finished();
		return;
	}

	cv::Mat frame;
	cv::Mat tempFrame;

	emit totalFrameCounterSignal(FrameCounter(capture), VideoTimeCalculator(capture));
	
	//qDebug() << capture.get(cv::CAP_PROP_FRAME_COUNT);

	while (capture.read(frame)) {
		{
			QMutexLocker locker(&mutex);
			if (isTimeChanged) {
				capture.set(cv::CAP_PROP_POS_FRAMES, frameNumber);
				isTimeChanged = false;
			}
			if (paused) {
				if (isCutterWorking) {
					VideoCutter(firstCutterFrame, secondCutterFrame);
				}
				pauseCondition.wait(&mutex);
			}
		}
		emit frameCounterSignal(capture.get(cv::CAP_PROP_POS_FRAMES));
		cvtColor(frame, tempFrame, cv::COLOR_RGB2BGR);
		QImage image = MatToQImage(tempFrame);
		emit frameReady(image);

		// Artificial delay to simulate processing time and control the frame rate
		cv::waitKey(15); 
	}

	qDebug() << "Video processing completed.";
	emit finished();
}

void VideoProcessor::VideoCutter(int firstFrame, int secondFrame) {
	//std::string outputPath = "output_video.avi";
	double fps = cutCapture.get(cv::CAP_PROP_FPS);
	int videoWidth = static_cast<int>(cutCapture.get(cv::CAP_PROP_FRAME_WIDTH));
	int videoHeight = static_cast<int>(cutCapture.get(cv::CAP_PROP_FRAME_HEIGHT));

	cv::VideoWriter outputVideo(tempOutputVideoName.toStdString(), cv::VideoWriter::fourcc('M', 'P', '4', 'V'), fps, cv::Size(videoWidth, videoHeight));

	if (!outputVideo.isOpened()) {
		std::cerr << "Could not open the output video for write." << std::endl;
	}

	int currentFrame = 0;

	cv::Mat frame;
	while (true) {
		if (!cutCapture.read(frame)) {
			break; // Break the loop if there are no more frames
		}

		// Increment current frame counter
		++currentFrame;

		if (currentFrame >= firstFrame && currentFrame <= secondFrame) {
			outputVideo.write(frame); // Write the frame to the output video
		}
	}

	cutCapture.release();
	outputVideo.release();

	isCutterWorking = false;
	firstCutterFrame = 0;
	secondCutterFrame = 0;
}

void VideoProcessor::FrameHolder(int firstFrame, int secondFrame) {
	std::vector<cv::Mat> frameHolderList;
	//std::string outputPath = "output_video.avi";
	double fps = cutCapture.get(cv::CAP_PROP_FPS);
	int videoWidth = static_cast<int>(cutCapture.get(cv::CAP_PROP_FRAME_WIDTH));
	int videoHeight = static_cast<int>(cutCapture.get(cv::CAP_PROP_FRAME_HEIGHT));

	
	int currentFrame = 0;

	cv::Mat frame;
	while (true) {
		if (!cutCapture.read(frame)) {
			break; // Break the loop if there are no more frames
		}

		// Increment current frame counter
		++currentFrame;

		frameHolderList.push_back(frame);
	}

	gifMaker = new GifConverter(tempOutputVideoName.toStdString(), (tempOutputVideoName.toStdString() + ".gif"));
	if (gifMaker->convertToGif()) {
		qDebug() <<  "Conversion succeeded!";
	}
	else{
		qDebug() << "Conversion failed!";
	}
}

void VideoProcessor::Pause(bool checked) {
	QMutexLocker locker(&mutex);
	paused = checked;
}

void VideoProcessor::Play(bool checked) {
	QMutexLocker locker(&mutex);
	paused = checked;
	pauseCondition.wakeAll();
}

void VideoProcessor::Cutter(bool checked, int first, int second)
{
	QMutexLocker locker(&mutex);
	paused = checked;
	isCutterWorking = checked;
	firstCutterFrame = first;
	secondCutterFrame = second;
}

void VideoProcessor::VideoTimeChanged(int frameN) {
	QMutexLocker locker(&mutex);
	isTimeChanged = true;
	frameNumber = frameN;
}

QImage VideoProcessor::MatToQImage(const cv::Mat &mat) {
	switch (mat.type()) {
	case CV_8UC4: {
		QImage image((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image;
	}
	case CV_8UC3: {
		QImage image((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	case CV_8UC1: {
		QImage image((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
		return image;
	}
	default:
		qWarning("Unsupported Mat format in MatToQImage");
		return QImage();
	}
}

void VideoProcessor::SetVideoFrame(cv::VideoCapture video, int frameNumber) {
	video.set(cv::CAP_PROP_FRAME_COUNT, frameNumber);
}

int VideoProcessor::FrameCounter(cv::VideoCapture video)
{
	return video.get(cv::CAP_PROP_FRAME_COUNT);
}

int VideoProcessor::VideoTimeCalculator(cv::VideoCapture video) {
	return video.get(cv::CAP_PROP_FPS);
}
