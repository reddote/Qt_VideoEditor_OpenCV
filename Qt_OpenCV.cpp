#include "Qt_OpenCV.h"
#include <QtWidgets/QApplication>

Qt_OpenCV::Qt_OpenCV(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	currentVideoTime = 0;
	videoProcessor = new VideoProcessor();

	InitVideoWindows();

	connect(videoProcessor, &VideoProcessor::totalFrameCounterSignal, this, &Qt_OpenCV::InitTimeSlider);
	connect(videoProcessor, &VideoProcessor::frameCounterSignal, this, &Qt_OpenCV::TimeSliderController);
	
}

void Qt_OpenCV::InitVideoWindows() {
	QString path_1 = "C:\\Users\\3DDL\\Desktop\\Qt_OpenCV\\2.mp4";

	videoWindow = new VideoWindow(videoProcessor, path_1, ui.graphicsView);
}



void Qt_OpenCV::TimeSliderController(int time) {
	currentVideoTime = time;
	
	ui.videoTimeSlider->setValue(currentVideoTime);

	QString temp = QString::number((float)currentVideoTime / videoFps);
	ui.currentTime->setText(temp);

}

void Qt_OpenCV::InitTimeSlider(int totalTime, int fps) {
	totalVideoTime = totalTime;
	videoFps = fps;
	float tempTime = ((float)totalVideoTime / fps);
	totalTimeinSeconds = tempTime;
	QString temp = QString::number(totalTimeinSeconds);
	ui.totalTime->setText(temp);
	ui.videoTimeSlider->setMaximum(totalVideoTime);
}

Qt_OpenCV::~Qt_OpenCV()
{}
