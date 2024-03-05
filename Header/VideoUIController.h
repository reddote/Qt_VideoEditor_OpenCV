#pragma once
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include "SliderController.h"
#include "TimeLabelvp.h"

class VideoUIController : public QWidget
{
	Q_OBJECT

public:
	VideoUIController(QSlider* tempS, QLabel* current, QLabel* total, QWidget *parent = nullptr);
	void ResetUIElements();
	~VideoUIController();

protected:
	SliderController* slider;
	TimeLabelvp* totalTimeLabel;
	TimeLabelvp* currentTimeLabel;

private:
	int totalVideoTime;
	int videoFps;
	int currentVideoTime;

public slots:
	void InitVideoTime(int totalTime, int fps);
	void TimeUpdater(int time);
};
