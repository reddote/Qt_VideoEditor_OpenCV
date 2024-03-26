#include "Qt_OpenCV.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QFileDialog>

Qt_OpenCV::Qt_OpenCV(QWidget *parent)
    : QMainWindow(parent)
{
	playPauseButtonIsPressed = false;
    ui.setupUi(this);
	ui.outputNameTextBox->setText("output.mp4");
	InitMainWindow();

}

void Qt_OpenCV::InitMainWindow() {
	currentVideoTime = 0;
	filePath = "C:\\Users\\3DDL\\Desktop\\Qt_OpenCV\\2.mp4";

	uiController = new VideoUIController(ui.videoTimeSlider, ui.currentTime, ui.totalTime);
	videoWindow = new VideoWindow(uiController, ui.graphicsView);

	//InitVideoWindows();

	connect(ui.actionOpenFile, &QAction::triggered, this, &Qt_OpenCV::OpenFileButton);

	connect(ui.videoTimeSlider, &QSlider::sliderMoved, this, &Qt_OpenCV::VideoTimeChanger);
	connect(ui.videoTimeSlider, &QSlider::sliderPressed, this, &Qt_OpenCV::VideoSliderIsPressed);
	connect(ui.videoTimeSlider, &QSlider::sliderReleased, this, &Qt_OpenCV::VideoSliderIsReleased);
}

void Qt_OpenCV::InitVideoWindows() {

	//videoWindow = new VideoWindow(videoProcessor, filePath, ui.graphicsView);
	videoWindow->startVideoProcessing(filePath);
	videoWindow->Pause(!playPauseButtonIsPressed);

	globalPlayPauseConnection = connect(ui.playPauseButton, &QPushButton::clicked, [this]() {
		if (!playPauseButtonIsPressed) {
			videoWindow->Play(playPauseButtonIsPressed);
			ui.playPauseButton->setText("ll");
		}
		else if (playPauseButtonIsPressed) {
			videoWindow->Pause(playPauseButtonIsPressed);
			ui.playPauseButton->setText(">");
		}
		playPauseButtonIsPressed = !playPauseButtonIsPressed;// Toggle the state
		qDebug() << "Button clicked!";
	});

}

void Qt_OpenCV::VideoTimeChanger(int number) {
	videoWindow->VideoTimeChanger(number);
}

void Qt_OpenCV::VideoSliderIsPressed()
{
	isSliderPressed = true;
	videoWindow->Pause(isSliderPressed);
	ui.playPauseButton->setText(">");
	playPauseButtonIsPressed = !playPauseButtonIsPressed;
}

void Qt_OpenCV::VideoSliderIsReleased()
{
	isSliderPressed = false;
	videoWindow->Play(isSliderPressed);
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
		Reset();
		//InitVideoWindows();
	}
}

void Qt_OpenCV::Reset() {
	// Reset the UI components to their initial state
	playPauseButtonIsPressed = false;
	currentVideoTime = 0;

	// Clear and delete dynamic objects if they are not nullptr
	if (uiController != nullptr) {
		uiController->ResetUIElements();
		delete uiController;
		uiController = new VideoUIController(ui.videoTimeSlider, ui.currentTime, ui.totalTime);
	}
	if (videoWindow != nullptr) {
		delete videoWindow;
		videoWindow = new VideoWindow(uiController, ui.graphicsView);
	}

	// Re-establish connections
	// Since we're deleting and recreating objects, previous connections are lost and need to be re-established.
	//connect(ui.actionOpenFile, &QAction::triggered, this, &Qt_OpenCV::OpenFileButton);

	connect(ui.videoTimeSlider, &QSlider::sliderMoved, this, &Qt_OpenCV::VideoTimeChanger);
	connect(ui.videoTimeSlider, &QSlider::sliderPressed, this, &Qt_OpenCV::VideoSliderIsPressed);
	connect(ui.videoTimeSlider, &QSlider::sliderReleased, this, &Qt_OpenCV::VideoSliderIsReleased);

	connect(ui.firstCT, &QPushButton::clicked, [this]() {
		uiController->SetCurrentTimeDS(ui.doubleSpinBox, 0);
	});

	connect(ui.secondCT, &QPushButton::clicked, [this]() {
		uiController->SetCurrentTimeDS(ui.doubleSpinBox_2, 1);
	});

	connect(ui.doubleSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double value) {
		uiController->DoubleSpinBoxValueChanged(value, 0);
	});

	connect(ui.doubleSpinBox_2, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double value) {
		uiController->DoubleSpinBoxValueChanged(value, 1);
	});

	connect(ui.Cut, &QPushButton::clicked, [this](){
		videoWindow->SetOutputVideoName(ui.outputNameTextBox->toPlainText());
		videoWindow->VideoCutter(uiController->GetDoubleSpinBoxFrames(0), uiController->GetDoubleSpinBoxFrames(1));
		videoWindow->Pause(playPauseButtonIsPressed);
		ui.playPauseButton->setText(">");
		playPauseButtonIsPressed = !playPauseButtonIsPressed;
	});
	
	disconnect(globalPlayPauseConnection);
	
	InitVideoWindows();
}

Qt_OpenCV::~Qt_OpenCV()
{}


