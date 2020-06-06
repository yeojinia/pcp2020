/********************************************************************************
** Form generated from reading UI file 'YJParallelCoordinates.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YJPARALLELCOORDINATES_H
#define UI_YJPARALLELCOORDINATES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "OGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ParallelCoordinates
{
public:
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionImportData;
    QAction *actionImportFeatures;
    QAction *actionClassification;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QGridLayout *gridLayout_3;
    PCPWidget *openGLWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_4;
    QVBoxLayout *sliderLayout;
    QHBoxLayout *hsvPanel;
    ColorPanel *colorPanel;
    QSpacerItem *horizontalSpacer;
    DoubleSlider *drSlider;
    QVBoxLayout *variableLayout;
    DoubleSlider *smoothSlider;
    QCheckBox *brushCheck;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    HPCPWidget *hOpenGLWidget;
    QVBoxLayout *hVerticalLayout;
    QScrollArea *hScrollArea;
    QWidget *hScrollAreaWidgetContents;
    QCheckBox *animateCheck;
    QListWidget *hListWidget;
    QWidget *tab_4;
    QGridLayout *gridLayout_7;
    HBWidget *hbOpenGLWidget;
    QVBoxLayout *vertical_UI_Layout;
    QSlider *horizontalSlider;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOpen;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuInsert;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ParallelCoordinates)
    {
        if (ParallelCoordinates->objectName().isEmpty())
            ParallelCoordinates->setObjectName(QString::fromUtf8("ParallelCoordinates"));
        ParallelCoordinates->resize(1145, 729);
        ParallelCoordinates->setStyleSheet(QString::fromUtf8("background-color: rgb(43, 43, 43);\n"
""));
        actionSave = new QAction(ParallelCoordinates);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionQuit = new QAction(ParallelCoordinates);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionImportData = new QAction(ParallelCoordinates);
        actionImportData->setObjectName(QString::fromUtf8("actionImportData"));
        actionImportFeatures = new QAction(ParallelCoordinates);
        actionImportFeatures->setObjectName(QString::fromUtf8("actionImportFeatures"));
        actionClassification = new QAction(ParallelCoordinates);
        actionClassification->setObjectName(QString::fromUtf8("actionClassification"));
        centralWidget = new QWidget(ParallelCoordinates);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        sizePolicy.setHeightForWidth(tab_1->sizePolicy().hasHeightForWidth());
        tab_1->setSizePolicy(sizePolicy);
        tab_1->setMinimumSize(QSize(0, 498));
        tab_1->setCursor(QCursor(Qt::ArrowCursor));
        gridLayout_3 = new QGridLayout(tab_1);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        openGLWidget = new PCPWidget(tab_1);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(43, 43, 43, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(4, 4, 4, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        openGLWidget->setPalette(palette);

        gridLayout_3->addWidget(openGLWidget, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(tab_1);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 254, 275));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        sliderLayout = new QVBoxLayout();
        sliderLayout->setSpacing(6);
        sliderLayout->setObjectName(QString::fromUtf8("sliderLayout"));

        gridLayout_4->addLayout(sliderLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        hsvPanel = new QHBoxLayout();
        hsvPanel->setSpacing(6);
        hsvPanel->setObjectName(QString::fromUtf8("hsvPanel"));
        hsvPanel->setSizeConstraint(QLayout::SetFixedSize);
        colorPanel = new ColorPanel(tab_1);
        colorPanel->setObjectName(QString::fromUtf8("colorPanel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(colorPanel->sizePolicy().hasHeightForWidth());
        colorPanel->setSizePolicy(sizePolicy2);
        colorPanel->setMinimumSize(QSize(200, 200));

        hsvPanel->addWidget(colorPanel);

        horizontalSpacer = new QSpacerItem(20, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);

        hsvPanel->addItem(horizontalSpacer);

        drSlider = new DoubleSlider(tab_1);
        drSlider->setObjectName(QString::fromUtf8("drSlider"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(drSlider->sizePolicy().hasHeightForWidth());
        drSlider->setSizePolicy(sizePolicy3);
        drSlider->setMaximumSize(QSize(16777215, 220));
        drSlider->setOrientation(Qt::Vertical);

        hsvPanel->addWidget(drSlider);


        verticalLayout->addLayout(hsvPanel);

        variableLayout = new QVBoxLayout();
        variableLayout->setSpacing(6);
        variableLayout->setObjectName(QString::fromUtf8("variableLayout"));
        smoothSlider = new DoubleSlider(tab_1);
        smoothSlider->setObjectName(QString::fromUtf8("smoothSlider"));
        sizePolicy2.setHeightForWidth(smoothSlider->sizePolicy().hasHeightForWidth());
        smoothSlider->setSizePolicy(sizePolicy2);
        smoothSlider->setMaximumSize(QSize(240, 20));
        smoothSlider->setOrientation(Qt::Horizontal);

        variableLayout->addWidget(smoothSlider);

        brushCheck = new QCheckBox(tab_1);
        brushCheck->setObjectName(QString::fromUtf8("brushCheck"));

        variableLayout->addWidget(brushCheck);


        verticalLayout->addLayout(variableLayout);


        gridLayout_3->addLayout(verticalLayout, 1, 1, 1, 1);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        sizePolicy.setHeightForWidth(tab_2->sizePolicy().hasHeightForWidth());
        tab_2->setSizePolicy(sizePolicy);
        tab_2->setMinimumSize(QSize(0, 498));
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        hOpenGLWidget = new HPCPWidget(tab_2);
        hOpenGLWidget->setObjectName(QString::fromUtf8("hOpenGLWidget"));
        sizePolicy.setHeightForWidth(hOpenGLWidget->sizePolicy().hasHeightForWidth());
        hOpenGLWidget->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(hOpenGLWidget, 0, 0, 1, 1);

        hVerticalLayout = new QVBoxLayout();
        hVerticalLayout->setSpacing(6);
        hVerticalLayout->setObjectName(QString::fromUtf8("hVerticalLayout"));
        hScrollArea = new QScrollArea(tab_2);
        hScrollArea->setObjectName(QString::fromUtf8("hScrollArea"));
        sizePolicy1.setHeightForWidth(hScrollArea->sizePolicy().hasHeightForWidth());
        hScrollArea->setSizePolicy(sizePolicy1);
        hScrollArea->setWidgetResizable(true);
        hScrollAreaWidgetContents = new QWidget();
        hScrollAreaWidgetContents->setObjectName(QString::fromUtf8("hScrollAreaWidgetContents"));
        hScrollAreaWidgetContents->setGeometry(QRect(0, 0, 254, 289));
        sizePolicy.setHeightForWidth(hScrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        hScrollAreaWidgetContents->setSizePolicy(sizePolicy);
        hScrollArea->setWidget(hScrollAreaWidgetContents);

        hVerticalLayout->addWidget(hScrollArea);

        animateCheck = new QCheckBox(tab_2);
        animateCheck->setObjectName(QString::fromUtf8("animateCheck"));

        hVerticalLayout->addWidget(animateCheck);

        hListWidget = new QListWidget(tab_2);
        hListWidget->setObjectName(QString::fromUtf8("hListWidget"));
        sizePolicy1.setHeightForWidth(hListWidget->sizePolicy().hasHeightForWidth());
        hListWidget->setSizePolicy(sizePolicy1);

        hVerticalLayout->addWidget(hListWidget);


        gridLayout_5->addLayout(hVerticalLayout, 0, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_7 = new QGridLayout(tab_4);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        hbOpenGLWidget = new HBWidget(tab_4);
        hbOpenGLWidget->setObjectName(QString::fromUtf8("hbOpenGLWidget"));
        sizePolicy.setHeightForWidth(hbOpenGLWidget->sizePolicy().hasHeightForWidth());
        hbOpenGLWidget->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(hbOpenGLWidget, 0, 0, 1, 1);

        vertical_UI_Layout = new QVBoxLayout();
        vertical_UI_Layout->setSpacing(6);
        vertical_UI_Layout->setObjectName(QString::fromUtf8("vertical_UI_Layout"));
        horizontalSlider = new QSlider(tab_4);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        sizePolicy2.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy2);
        horizontalSlider->setMinimumSize(QSize(240, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);

        vertical_UI_Layout->addWidget(horizontalSlider);


        gridLayout_7->addLayout(vertical_UI_Layout, 0, 2, 1, 1);

        tabWidget->addTab(tab_4, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        ParallelCoordinates->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ParallelCoordinates);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1145, 21));
        menuBar->setStyleSheet(QString::fromUtf8("background-color: rgb(227, 227, 227);"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setStyleSheet(QString::fromUtf8(""));
        menuOpen = new QMenu(menuFile);
        menuOpen->setObjectName(QString::fromUtf8("menuOpen"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuEdit->setStyleSheet(QString::fromUtf8(""));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuView->setStyleSheet(QString::fromUtf8(""));
        menuInsert = new QMenu(menuBar);
        menuInsert->setObjectName(QString::fromUtf8("menuInsert"));
        menuInsert->setStyleSheet(QString::fromUtf8(""));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuTools->setStyleSheet(QString::fromUtf8(""));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setStyleSheet(QString::fromUtf8(""));
        ParallelCoordinates->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ParallelCoordinates);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setStyleSheet(QString::fromUtf8(""));
        ParallelCoordinates->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ParallelCoordinates);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setStyleSheet(QString::fromUtf8(""));
        ParallelCoordinates->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuInsert->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(menuOpen->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionQuit);
        menuOpen->addAction(actionImportData);
        menuOpen->addAction(actionImportFeatures);
        menuOpen->addSeparator();
        menuOpen->addAction(actionClassification);

        retranslateUi(ParallelCoordinates);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ParallelCoordinates);
    } // setupUi

    void retranslateUi(QMainWindow *ParallelCoordinates)
    {
        ParallelCoordinates->setWindowTitle(QCoreApplication::translate("ParallelCoordinates", "YJParallelCoordinates", nullptr));
        actionSave->setText(QCoreApplication::translate("ParallelCoordinates", "Save", nullptr));
        actionQuit->setText(QCoreApplication::translate("ParallelCoordinates", "Quit", nullptr));
        actionImportData->setText(QCoreApplication::translate("ParallelCoordinates", "Import Data", nullptr));
        actionImportFeatures->setText(QCoreApplication::translate("ParallelCoordinates", "Import Features", nullptr));
        actionClassification->setText(QCoreApplication::translate("ParallelCoordinates", "Classfication", nullptr));
        brushCheck->setText(QCoreApplication::translate("ParallelCoordinates", "brush mode", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QCoreApplication::translate("ParallelCoordinates", "Parallel Coordinates", nullptr));
        animateCheck->setText(QCoreApplication::translate("ParallelCoordinates", "Animate", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("ParallelCoordinates", "Hierarchical Parallel Coordinates", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("ParallelCoordinates", "Hierarchical Parallel + Bezier", nullptr));
        menuFile->setTitle(QCoreApplication::translate("ParallelCoordinates", "File", nullptr));
        menuOpen->setTitle(QCoreApplication::translate("ParallelCoordinates", "Open", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("ParallelCoordinates", "Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("ParallelCoordinates", "View", nullptr));
        menuInsert->setTitle(QCoreApplication::translate("ParallelCoordinates", "Insert", nullptr));
        menuTools->setTitle(QCoreApplication::translate("ParallelCoordinates", "Tools", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("ParallelCoordinates", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParallelCoordinates: public Ui_ParallelCoordinates {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YJPARALLELCOORDINATES_H
