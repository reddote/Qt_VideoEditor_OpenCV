#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_OpenCV.h"
#include "Header/VideoWindow.h"
#include "Header/VideoUIController.h"
#include <qgraphicsview.h>

class Qt_OpenCV : public QMainWindow
{
    Q_OBJECT

public:
    Qt_OpenCV(QWidget *parent = nullptr);
	void InitVideoWindows();
	~Qt_OpenCV();

private:
	VideoWindow *videoWindow;
	QGraphicsView *graphicsView;
	VideoProcessor *videoProcessor;
	VideoUIController* uiController;

	QString filePath;

	int totalVideoTime;
	int currentVideoTime;
	float totalTimeinSeconds;
	int videoFps;
	bool playPauseButtonIsPressed;
	bool isSliderPressed = false;

    Ui::Qt_OpenCVClass ui;

public slots:
	void VideoTimeChanger(int number);
	void VideoSliderIsPressed();
	void VideoSliderIsReleased();
	void OpenFileButton();
};
