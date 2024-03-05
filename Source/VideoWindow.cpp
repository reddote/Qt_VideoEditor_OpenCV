#include "..\Header\VideoWindow.h"
#include <QThread>

VideoWindow::VideoWindow(VideoUIController *vp, QString temppath, QWidget * parent) :
	QGraphicsView(parent), scene(new QGraphicsScene(this))
{
	processor = new VideoProcessor();
	startVideoProcessing(temppath);
	uiController = vp;

	connect(processor, &VideoProcessor::totalFrameCounterSignal, uiController, &VideoUIController::InitVideoTime);
	connect(processor, &VideoProcessor::frameCounterSignal, uiController, &VideoUIController::TimeUpdater);
}

VideoWindow::VideoWindow(VideoUIController *vp, QWidget * parent) :
	QGraphicsView(parent), scene(new QGraphicsScene(this))
{
	processor = new VideoProcessor();
	uiController = vp;
	thread = new QThread();

	connect(processor, &VideoProcessor::totalFrameCounterSignal, uiController, &VideoUIController::InitVideoTime);
	connect(processor, &VideoProcessor::frameCounterSignal, uiController, &VideoUIController::TimeUpdater);
}

void VideoWindow::ThreadTerminaterForVP(QString tempPath) {
	thread->terminate();
	startVideoProcessing(tempPath);
}

void VideoWindow::startVideoProcessing(QString temp) {
	// Path to the video file
	QString videoPath = temp;

	processor->SetVideoPath(videoPath);
	processor->moveToThread(thread);

	connect(thread, &QThread::started, processor, &VideoProcessor::ProcessVideo);
	connect(processor, &VideoProcessor::frameReady, this, &VideoWindow::UpdateFrameUI);
	connect(processor, &VideoProcessor::finished, thread, &QThread::quit);

	thread->start();
}

// Slot in VideoWindow to update the UI with a new frame
void VideoWindow::UpdateFrameUI(const QImage& frame) {
	scene = new QGraphicsScene(this);
	scene->clear();
	scene->addPixmap(QPixmap::fromImage(frame));
	this->setScene(scene);
	this->setFixedSize(1171, 381);
	this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
	this->show(); // Ensure the view is visible
}

void VideoWindow::Pause(bool checked) {
	processor->Pause(checked);
}

void VideoWindow::Play(bool checked) {
	processor->Play(checked);
}

void VideoWindow::VideoTimeChanger(int number) {
	processor->Play(false);
	processor->VideoTimeChanged(number);
	processor->Pause(true);
}


//Mouse Controller Start
void VideoWindow::wheelEvent(QWheelEvent *event) {
	// Zoom Factor
	double scaleFactor = 1.15;
	if (event->angleDelta().y() > 0) {
		// Zoom in
		scale(scaleFactor, scaleFactor);
	}
	else {
		// Zooming out
		scale(1.0 / scaleFactor, 1.0 / scaleFactor);
	}
}

void VideoWindow::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::RightButton) {
		startPanning(event->pos());
	}else if(event->button() == Qt::LeftButton) {
		QPointF scenePos = mapToScene(event->pos());

		// Create a pen with desired color (blue) and increased width for boldness
		QPen pen(Qt::blue);
		pen.setWidth(5); // Increase the width of the pen to make the ellipse bolder

		QGraphicsEllipseItem* ellipse = scene->addEllipse(scenePos.x() - 10, scenePos.y() - 10, 20, 20, pen, QBrush(Qt::transparent));
		ellipse->setFlag(QGraphicsItem::ItemIsMovable);
	}

	QGraphicsView::mousePressEvent(event); // Call base class implementation
}

void VideoWindow::mouseMoveEvent(QMouseEvent *event) {
	if (_lastPanPoint != QPoint()) {
		doPanning(event->pos());
	}
	QGraphicsView::mouseMoveEvent(event);
}

void VideoWindow::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		stopPanning();
	}
	QGraphicsView::mouseReleaseEvent(event);
}

void VideoWindow::startPanning(const QPoint &pos) {
	_lastPanPoint = pos;
	setCursor(Qt::ClosedHandCursor);
}

void VideoWindow::doPanning(const QPoint &pos) {
	QPoint delta = pos - _lastPanPoint;
	_lastPanPoint = pos;
	horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
	verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
}

void VideoWindow::stopPanning() {
	_lastPanPoint = QPoint();
	setCursor(Qt::ArrowCursor);
}
//Mouse Controller End


VideoWindow::~VideoWindow()
{
}
