#pragma once
#include <QLabel>

class TimeLabelvp : public QLabel
{
	Q_OBJECT

public:
	TimeLabelvp(QLabel* temp, QWidget *parent = nullptr);
	~TimeLabelvp();
	void SetLabelText(QString data);

	void ResetLabelText(QString data);

protected:
	QLabel* label;
private:

public slots:

};
