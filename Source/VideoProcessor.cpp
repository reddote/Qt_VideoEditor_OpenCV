#include "..\Header\VideoProcessor.h"
#include <QDebug>

VideoProcessor::VideoProcessor(QObject *parent) : QObject(parent) {
}

void VideoProcessor::SetVideoPath(const QString &path) {
	videoPath = path;
}

void VideoProcessor::ProcessVideo() {
	if (videoPath.isEmpty()) {
		qDebug() << "Video path is empty";
		emit finished();
		return;
	}

	cv::VideoCapture capture(videoPath.toStdString());
	if (!capture.isOpened()) {
		qDebug() << "Error: Could not open video file.";
		emit finished();
		return;
	}

	cv::Mat frame;
	cv::Mat tempFrame;
	while (capture.read(frame)) {
		cvtColor(frame, tempFrame, cv::COLOR_RGB2BGR);
		QImage image = MatToQImage(tempFrame);
		emit frameReady(image);

		// Artificial delay to simulate processing time and control the frame rate
		cv::waitKey(15); 
	}

	qDebug() << "Video processing completed.";
	emit finished();
}

QImage VideoProcessor::MatToQImage(const cv::Mat &mat) {
	switch (mat.type()) {
	case CV_8UC4: {
		QImage image((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	case CV_8UC3: {
		QImage image((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped().copy();
	}
	case CV_8UC1: {
		QImage image((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
		return image.copy();
	}
	default:
		qWarning("Unsupported Mat format in MatToQImage");
		return QImage();
	}
}
