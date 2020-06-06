#pragma once

#include <vector>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QApplication>
#include "Utils.h"
#include "ui_YJParallelCoordinates.h"

class YJParallelCoordinates : public QMainWindow
{
	Q_OBJECT

public:
	YJParallelCoordinates(QWidget *parent = Q_NULLPTR);
	QStandardItemModel *model;
	//std::vector<RangeSlider *> hRangeSlider;
	QVector <RangeSlider*> rangeSlider;
	QVector <SliderName*> rangeSliderName;
	double smooth_value;

public slots:
	void updateSmoothValue(double value);
	void updateCorrelationValue(double value);
private:
	Ui::ParallelCoordinates ui;
	void createActions();

private slots:
	void loadDataFromFile();
	void loadFeatureNameFromFile();
	void loadkMeansClassificationFromFile();
	void drawSliders();
	void drawParallelCoordinates();
//	void slotRangeValueChanged();
};

