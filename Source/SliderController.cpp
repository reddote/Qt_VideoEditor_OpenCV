#include "..\Header\SliderController.h"

SliderController::SliderController(QSlider* temp, QWidget * parent) :
	QSlider(parent)
{
	slider = temp;
}

SliderController::~SliderController()
{

}

void SliderController::InitTimeSlider(int totalTime)
{
	slider->setMaximum(totalTime);
}

void SliderController::TimeSliderUpdater(int time)
{
	slider->setValue(time);
}

float SliderController::GetCurrentValue(){
	return slider->value();
}
