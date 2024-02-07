#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QObject>
#include "VideoWindow.h"

class ThreadWorker : public QObject {
	Q_OBJECT
public:
	explicit ThreadWorker(QObject *parent = nullptr);
private:
signals:
	void workFinished(); // Signal to indicate the work is done

public slots:
	void doWork(); // Slot to perform the work
};

#endif // THREADWORKER