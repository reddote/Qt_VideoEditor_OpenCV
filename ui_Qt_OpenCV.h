/********************************************************************************
** Form generated from reading UI file 'Qt_OpenCVh14884.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QT_OPENCVH14884_H
#define QT_OPENCVH14884_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_OpenCVClass
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QSlider *videoTimeSlider;
    QLabel *currentTime;
    QLabel *label_2;
    QLabel *totalTime;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_OpenCVClass)
    {
        if (Qt_OpenCVClass->objectName().isEmpty())
            Qt_OpenCVClass->setObjectName(QStringLiteral("Qt_OpenCVClass"));
        Qt_OpenCVClass->resize(1102, 541);
        centralWidget = new QWidget(Qt_OpenCVClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(50, 30, 1001, 381));
        videoTimeSlider = new QSlider(centralWidget);
        videoTimeSlider->setObjectName(QStringLiteral("videoTimeSlider"));
        videoTimeSlider->setGeometry(QRect(49, 430, 341, 22));
        videoTimeSlider->setMaximum(100);
        videoTimeSlider->setValue(0);
        videoTimeSlider->setOrientation(Qt::Horizontal);
        currentTime = new QLabel(centralWidget);
        currentTime->setObjectName(QStringLiteral("currentTime"));
        currentTime->setGeometry(QRect(260, 460, 61, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 460, 61, 31));
        totalTime = new QLabel(centralWidget);
        totalTime->setObjectName(QStringLiteral("totalTime"));
        totalTime->setGeometry(QRect(330, 460, 61, 31));
        Qt_OpenCVClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Qt_OpenCVClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1102, 21));
        Qt_OpenCVClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_OpenCVClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Qt_OpenCVClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Qt_OpenCVClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qt_OpenCVClass->setStatusBar(statusBar);

        retranslateUi(Qt_OpenCVClass);

        QMetaObject::connectSlotsByName(Qt_OpenCVClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_OpenCVClass)
    {
        Qt_OpenCVClass->setWindowTitle(QApplication::translate("Qt_OpenCVClass", "Qt_OpenCV", 0));
        currentTime->setText(QApplication::translate("Qt_OpenCVClass", "TextLabel", 0));
        label_2->setText(QApplication::translate("Qt_OpenCVClass", "/", 0));
        totalTime->setText(QApplication::translate("Qt_OpenCVClass", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Qt_OpenCVClass: public Ui_Qt_OpenCVClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QT_OPENCVH14884_H
