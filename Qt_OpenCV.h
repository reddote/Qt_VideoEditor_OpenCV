#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_OpenCV.h"
#include "Header/VideoWindow.h"
#include "Header/VideoUIController.h"
#include <qgraphicsview.h>
#include <QMetaObject>

class Qt_OpenCV : public QMainWindow
{
    Q_OBJECT

public:
    Qt_OpenCV(QWidget *parent = nullptr);
	void InitMainWindow();
	void InitVideoWindows();
	~Qt_OpenCV();

private:
	VideoWindow *videoWindow;
	QGraphicsView *graphicsView;
	VideoUIController* uiController;

	QString filePath;
	QMetaObject::Connection globalPlayPauseConnection;

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
	void Reset();
};
