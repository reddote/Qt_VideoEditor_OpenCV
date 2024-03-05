#include "..\Header\VideoUIController.h"

VideoUIController::VideoUIController(QSlider* tempS, QLabel* current, QLabel* total, QWidget * parent) :
	QWidget(parent)
{
	currentVideoTime = 0;
	slider = new SliderController(tempS);
	currentTimeLabel = new TimeLabelvp(current);
	totalTimeLabel = new TimeLabelvp(total);
}

void VideoUIController::InitVideoTime(int totalTime, int fps) {
	totalVideoTime = totalTime;
	videoFps = fps;
	float tempTime = ((float)totalTime / fps);
	QString temp = QString::number(tempTime);
	totalTimeLabel->SetLabelText(temp);
	slider->InitTimeSlider(totalTime);
}

void VideoUIController::TimeUpdater(int time) {
	currentVideoTime = time;
	slider->TimeSliderUpdater(currentVideoTime);
	QString temp = QString::number((float)currentVideoTime / videoFps);
	currentTimeLabel->SetLabelText(temp);
}

void VideoUIController::ResetUIElements() {
	slider->ResetSlider();
}

VideoUIController::~VideoUIController()
{

}