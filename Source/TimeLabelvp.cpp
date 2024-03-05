#include "..\Header\TimeLabelvp.h"

TimeLabelvp::TimeLabelvp(QLabel* temp, QWidget * parent) :
	QLabel(parent)
{
	label = temp;
}

void TimeLabelvp::SetLabelText(QString data)
{
	label->setText(data);
}

void TimeLabelvp::ResetLabelText(QString data) {
	label->setText(data);
}

TimeLabelvp::~TimeLabelvp()
{

}



