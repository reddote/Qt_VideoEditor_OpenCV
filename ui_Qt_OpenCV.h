/********************************************************************************
** Form generated from reading UI file 'Qt_OpenCVp13948.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QT_OPENCVP13948_H
#define QT_OPENCVP13948_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_OpenCVClass
{
public:
    QAction *actionOpenFile;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QSlider *videoTimeSlider;
    QLabel *currentTime;
    QLabel *label_2;
    QLabel *totalTime;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_3;
    QPushButton *playPauseButton;
    QPushButton *firstCT;
    QPushButton *secondCT;
    QPushButton *Cut;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_OpenCVClass)
    {
        if (Qt_OpenCVClass->objectName().isEmpty())
            Qt_OpenCVClass->setObjectName(QStringLiteral("Qt_OpenCVClass"));
        Qt_OpenCVClass->resize(1102, 601);
        actionOpenFile = new QAction(Qt_OpenCVClass);
        actionOpenFile->setObjectName(QStringLiteral("actionOpenFile"));
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
        currentTime->setGeometry(QRect(400, 430, 61, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 460, 61, 21));
        totalTime = new QLabel(centralWidget);
        totalTime->setObjectName(QStringLiteral("totalTime"));
        totalTime->setGeometry(QRect(470, 430, 61, 21));
        doubleSpinBox = new QDoubleSpinBox(centralWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(255, 460, 62, 22));
        doubleSpinBox_2 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(330, 460, 62, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(460, 430, 61, 21));
        playPauseButton = new QPushButton(centralWidget);
        playPauseButton->setObjectName(QStringLiteral("playPauseButton"));
        playPauseButton->setGeometry(QRect(10, 425, 31, 31));
        firstCT = new QPushButton(centralWidget);
        firstCT->setObjectName(QStringLiteral("firstCT"));
        firstCT->setGeometry(QRect(175, 460, 75, 23));
        secondCT = new QPushButton(centralWidget);
        secondCT->setObjectName(QStringLiteral("secondCT"));
        secondCT->setGeometry(QRect(395, 460, 75, 23));
        Cut = new QPushButton(centralWidget);
        Cut->setObjectName(QStringLiteral("Cut"));
        Cut->setGeometry(QRect(280, 500, 75, 23));
        Qt_OpenCVClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Qt_OpenCVClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1102, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        Qt_OpenCVClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_OpenCVClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Qt_OpenCVClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Qt_OpenCVClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qt_OpenCVClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpenFile);

        retranslateUi(Qt_OpenCVClass);

        QMetaObject::connectSlotsByName(Qt_OpenCVClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_OpenCVClass)
    {
        Qt_OpenCVClass->setWindowTitle(QApplication::translate("Qt_OpenCVClass", "Qt_OpenCV", 0));
        actionOpenFile->setText(QApplication::translate("Qt_OpenCVClass", "Open File", 0));
        currentTime->setText(QApplication::translate("Qt_OpenCVClass", "TextLabel", 0));
        label_2->setText(QApplication::translate("Qt_OpenCVClass", "/", 0));
        totalTime->setText(QApplication::translate("Qt_OpenCVClass", "TextLabel", 0));
        label_3->setText(QApplication::translate("Qt_OpenCVClass", "/", 0));
        playPauseButton->setText(QApplication::translate("Qt_OpenCVClass", ">", 0));
        firstCT->setText(QApplication::translate("Qt_OpenCVClass", "Use Current", 0));
        secondCT->setText(QApplication::translate("Qt_OpenCVClass", "Use Current", 0));
        Cut->setText(QApplication::translate("Qt_OpenCVClass", "Cut", 0));
        menuFile->setTitle(QApplication::translate("Qt_OpenCVClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class Qt_OpenCVClass: public Ui_Qt_OpenCVClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QT_OPENCVP13948_H
