#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include <QImage>
#include <opencv.hpp>
#include <core/mat.hpp> 
#include <imgcodecs.hpp> 

class VideoProcessor : public QObject {
	Q_OBJECT

public:
	explicit VideoProcessor(QObject *parent = nullptr);
	void SetVideoPath(const QString &path);

signals:
	void frameReady(const QImage &frame);
	void finished();

public slots:
	void ProcessVideo();

private:
	QString videoPath;
	QImage MatToQImage(const cv::Mat &mat);
};

#endif // VIDEOPROCESSOR
