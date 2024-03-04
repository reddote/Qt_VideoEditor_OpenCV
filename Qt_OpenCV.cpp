#include "Qt_OpenCV.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QFileDialog>

Qt_OpenCV::Qt_OpenCV(QWidget *parent)
    : QMainWindow(parent)
{
	playPauseButtonIsPressed = false;
    ui.setupUi(this);

	currentVideoTime = 0;
	filePath = "C:\\Users\\3DDL\\Desktop\\Qt_OpenCV\\2.mp4";

	videoProcessor = new VideoProcessor();
	uiController = new VideoUIController(ui.videoTimeSlider, ui.currentTime, ui.totalTime);
	videoWindow = new VideoWindow(videoProcessor, ui.graphicsView);


	//InitVideoWindows();
	
	connect(ui.actionOpenFile, &QAction::triggered, this, &Qt_OpenCV::OpenFileButton);

	connect(ui.videoTimeSlider, &QSlider::sliderMoved, this, &Qt_OpenCV::VideoTimeChanger);
	connect(ui.videoTimeSlider, &QSlider::sliderPressed, this, &Qt_OpenCV::VideoSliderIsPressed);
	connect(ui.videoTimeSlider, &QSlider::sliderReleased, this, &Qt_OpenCV::VideoSliderIsReleased);

	connect(videoProcessor, &VideoProcessor::totalFrameCounterSignal, uiController, &VideoUIController::InitVideoTime);
	connect(videoProcessor, &VideoProcessor::frameCounterSignal, uiController, &VideoUIController::TimeUpdater);

}

void Qt_OpenCV::InitVideoWindows() {

	//videoWindow = new VideoWindow(videoProcessor, filePath, ui.graphicsView);
	videoWindow->startVideoProcessing(filePath);
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
	videoProcessor->Play(false);
	videoProcessor->VideoTimeChanged(number);
	videoProcessor->Pause(true);
}

void Qt_OpenCV::VideoSliderIsPressed()
{
	isSliderPressed = true;
	videoProcessor->Pause(isSliderPressed);
	ui.playPauseButton->setText(">");
	playPauseButtonIsPressed = !playPauseButtonIsPressed;
}

void Qt_OpenCV::VideoSliderIsReleased()
{
	isSliderPressed = false;
	videoProcessor->Play(isSliderPressed);
	ui.playPauseButton->setText("ll");
	playPauseButtonIsPressed = !playPauseButtonIsPressed;
}

void Qt_OpenCV::OpenFileButton() {
	QString filter = "All Files (*.*) ;; Videos (*.mp4)";
	QString tempfilePath = QFileDialog::getOpenFileName(this, "Select a file", QDir::homePath(), filter);

	if (!filePath.isEmpty()) {
		// Do something with the file path, for example, print it
		qDebug() << "Selected file path:" << tempfilePath;
		filePath = tempfilePath;
		InitVideoWindows();
	}
}

Qt_OpenCV::~Qt_OpenCV()
{}


