#include "Qt_OpenCV.h"
#include <QtWidgets/QApplication>

Qt_OpenCV::Qt_OpenCV(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	currentVideoTime = 0;
	videoProcessor = new VideoProcessor();
	uiController = new VideoUIController(ui.videoTimeSlider, ui.currentTime, ui.totalTime);
	
	InitVideoWindows();

	connect(videoProcessor, &VideoProcessor::totalFrameCounterSignal, uiController, &VideoUIController::InitVideoTime);
	connect(videoProcessor, &VideoProcessor::frameCounterSignal, uiController, &VideoUIController::TimeUpdater);
	
}

void Qt_OpenCV::InitVideoWindows() {
	QString path_1 = "C:\\Users\\3DDL\\Desktop\\Qt_OpenCV\\2.mp4";

	videoWindow = new VideoWindow(videoProcessor, path_1, ui.graphicsView);
}

Qt_OpenCV::~Qt_OpenCV()
{}
