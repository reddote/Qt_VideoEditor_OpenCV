#include "Qt_OpenCV.h"
#include <QtWidgets/QApplication>
#include <QDebug>

Qt_OpenCV::Qt_OpenCV(QWidget *parent)
    : QMainWindow(parent)
{
	playPauseButtonIsPressed = false;
    ui.setupUi(this);

	currentVideoTime = 0;
	videoProcessor = new VideoProcessor();
	uiController = new VideoUIController(ui.videoTimeSlider, ui.currentTime, ui.totalTime);
	
	InitVideoWindows();

	connect(ui.videoTimeSlider, &QSlider::sliderMoved, this, &Qt_OpenCV::VideoTimeChanger);
	connect(ui.videoTimeSlider, &QSlider::sliderPressed, this, &Qt_OpenCV::VideoSliderIsPressed);
	connect(ui.videoTimeSlider, &QSlider::sliderReleased, this, &Qt_OpenCV::VideoSliderIsReleased);

	connect(videoProcessor, &VideoProcessor::totalFrameCounterSignal, uiController, &VideoUIController::InitVideoTime);
	connect(videoProcessor, &VideoProcessor::frameCounterSignal, uiController, &VideoUIController::TimeUpdater);

}

void Qt_OpenCV::InitVideoWindows() {
	QString path_1 = "C:\\Users\\3DDL\\Desktop\\Qt_OpenCV\\2.mp4";

	videoWindow = new VideoWindow(videoProcessor, path_1, ui.graphicsView);
	videoProcessor->Pause(!playPauseButtonIsPressed);

	connect(ui.playPauseButton, &QPushButton::clicked, [this]() {
		if (!playPauseButtonIsPressed) {
			videoProcessor->Play(playPauseButtonIsPressed);
			ui.playPauseButton->setText("ll");
		}
		else if (playPauseButtonIsPressed) {
			videoProcessor->Pause(playPauseButtonIsPressed);
			ui.playPauseButton->setText(">");
		}
		playPauseButtonIsPressed = !playPauseButtonIsPressed;// Toggle the state
		qDebug() << "Button clicked!";
	});

}

void Qt_OpenCV::VideoTimeChanger(int number) {
	videoProcessor->VideoTimeChanged(number);
}

Qt_OpenCV::~Qt_OpenCV()
{}

void Qt_OpenCV::VideoSliderIsPressed()
{
	isSliderPressed = true;
	videoProcessor->Pause(isSliderPressed);
}

void Qt_OpenCV::VideoSliderIsReleased()
{
	isSliderPressed = false;
	videoProcessor->Play(isSliderPressed);
}
