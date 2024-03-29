#include "..\Header\VideoUIController.h"

VideoUIController::VideoUIController(QSlider* tempS, QLabel* current, QLabel* total, QWidget * parent) :
	QWidget(parent)
{
	currentVideoTime = 0;
	slider = new SliderController(tempS);
	currentTimeLabel = new TimeLabelvp(current);
	totalTimeLabel = new TimeLabelvp(total);
	InitUIElements();
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
	currentTimeLabel->ResetLabelText("0");
}

void VideoUIController::InitUIElements() {
	currentTimeLabel->SetLabelText("0");
	totalTimeLabel->SetLabelText("0");
}

void VideoUIController::SetCurrentTimeDS(QDoubleSpinBox* spinbox, int order) {
	spinbox->setValue((float)currentVideoTime / videoFps);
	tempCurrentFrameNumber[order] = currentVideoTime;
}

void VideoUIController::DoubleSpinBoxValueChanged(double time, int order) {
	int currentFrame = (int)time * videoFps;
	tempCurrentFrameNumber[order] = currentFrame;
}

int VideoUIController::GetDoubleSpinBoxFrames(int number){
	return tempCurrentFrameNumber[number];
}

VideoUIController::~VideoUIController()
{

}