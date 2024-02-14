#pragma once
#include <QSlider>

class SliderController : public QSlider
{
	Q_OBJECT

public:
	SliderController(QSlider* temp, QWidget *parent = nullptr);
	~SliderController();
	void InitTimeSlider(int totalTime);
	void TimeSliderUpdater(int time);

protected:
	QSlider* slider;
private:

public slots:

};
