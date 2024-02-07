#pragma once
#include <QWidget>
#include <opencv.hpp>
#include <QApplication>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPointF>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "VideoProcessor.h"


class VideoWindow : public QGraphicsView
{
	Q_OBJECT

public:
	VideoWindow(QString temppath, QWidget *parent = nullptr);
	~VideoWindow();

	void startVideoProcessing(QString temp);

protected:
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	QTimer *timer;
	cv::VideoCapture *videoCap;
	QGraphicsScene *scene;
	QString path;

	bool _dragging;
	QPointF _lastDragPoint;
	QPoint _lastPanPoint;
	void startPanning(const QPoint &pos);
	void doPanning(const QPoint &pos);
	void stopPanning();

public slots:
	void UpdateFrameUI(const QImage & frame);

};
