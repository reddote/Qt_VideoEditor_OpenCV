#include "../Header/ThreadWorker.h"

ThreadWorker::ThreadWorker(QObject *parent) : QObject(parent) {
}

void ThreadWorker::doWork() {
	emit workFinished(); // Emit signal when done
}