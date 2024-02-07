#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_OpenCV.h"
#include "Header/VideoWindow.h"
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
	int totalVideoTime;
	int currentVideoTime;
	float totalTimeinSeconds;
	int videoFps;

    Ui::Qt_OpenCVClass ui;

public slots:
	void TimeSliderController(int time);
	void InitTimeSlider(int totalTime, int fps);

};
