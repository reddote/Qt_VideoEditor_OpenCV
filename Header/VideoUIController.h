#pragma once
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QDoubleSpinBox>
#include "SliderController.h"
#include "TimeLabelvp.h"

class VideoUIController : public QWidget
{
	Q_OBJECT

public:
	VideoUIController(QSlider* tempS, QLabel* current, QLabel* total, QWidget *parent = nullptr);
	void ResetUIElements();
	void InitUIElements();
	~VideoUIController();

protected:
	SliderController* slider;
	TimeLabelvp* totalTimeLabel;
	TimeLabelvp* currentTimeLabel;

private:
	int totalVideoTime;
	int videoFps;
	int currentVideoTime;

	int tempCurrentFrameNumber[2] = {0,0};

public slots:
	void InitVideoTime(int totalTime, int fps);
	void TimeUpdater(int time);
	void SetCurrentTimeDS(QDoubleSpinBox* spinbox, int order);

	void DoubleSpinBoxValueChanged(double time, int order);
	int GetDoubleSpinBoxFrames(int number);


};
