#ifndef _OGL_WIDGET_H
#define _OGL_WIDGET_H

#include <QDebug>
#include <QOpenGLWidget>
#include <QtMath>
#include <QCheckBox>
#include <QSlider>
#include <QTimer>
#include <glut.h>
#include "MyVec.hpp"
#include "Utils.h"

class RangeSlider;

class PCPWidget : public QOpenGLWidget
{
	Q_OBJECT
public:
	PCPWidget(QWidget *parent = 0);
	~PCPWidget();
	std::tuple<float, float> getWidgetSize();

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:

	void draw();
	void updatePosition(int width, int height);
	void drawCoordinates();
	void drawSmoothLines();
	void drawFeatureNames();
	void drawRanges();
	void drawCubicBezierCurve(my_vec::my_vec2 start_ctrl, my_vec::my_vec2 end_ctrl, my_vec::my_vec2 start, my_vec::my_vec2 end, int index);
	my_vec::my_vec2 computeCtrlpoints(my_vec::my_vec2 prev, my_vec::my_vec2 current, my_vec::my_vec2 next, float direction);

	my_vec::my_vec2 getDataViewportPositionByDataIdx(int feature_idx, int example_idx);
	std::tuple<float, float, float> getFeatureViewportPositionByFeatureId(int feature_id);
	std::tuple<float, float, float> getAttributeViewportPositionByAttributeIdx(int feature_index); // return attribute center position, length

};


class ColorPanel : public QOpenGLWidget
{
	Q_OBJECT
public:
	ColorPanel(QWidget *parent = 0);
	~ColorPanel();
	QVector<std::tuple<int, int, int>> cluster_color;
protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	virtual void paintEvent(QPaintEvent*);
	virtual void drawColorWheel(QPainter*);
	struct Polar {
		qreal radius;
		qreal angle;
	};
	struct Cartesian {
		qreal x;
		qreal y;
	};
	virtual Polar cartesianToPolar(qreal x, qreal y);
	virtual Cartesian polarToCartesian(qreal radius, qreal angle);
	Cartesian rgbToPos(float r, float g, float b);
	std::tuple<int, int, int> posToRgb(int w, int h);
	void set_default_cluster_color();							// set default color for each clusters
};

class HPCPWidget : public QOpenGLWidget
{
	Q_OBJECT
public:
	HPCPWidget(QWidget *parent = 0);
	~HPCPWidget();

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void timerEvent(QTimerEvent* e);
	void drawAxes();
	void drawFeatureNames();
	void drawRanges();
	//std::pair<GLfloat, GLfloat> getCenterOfMass(int feature, int cluster_id);

private:
	void draw();

private slots:
	void animate();
};


class HBWidget : public QOpenGLWidget
{
	Q_OBJECT
public:
	HBWidget(QWidget *parent = 0);
	~HBWidget();

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void timerEvent(QTimerEvent* e);
	void drawAxes();
	void drawFeatureNames();
	void drawRanges();
	void drawGraphs();
	my_vec::my_vec2 computeCtrlpoints(my_vec::my_vec2 prev, my_vec::my_vec2 current, my_vec::my_vec2 next, float direction);
	void drawCubicBezierCurve(my_vec::my_vec2 start_ctrl, my_vec::my_vec2 end_ctrl, my_vec::my_vec2 start_anchor, my_vec::my_vec2 end_anchor, int index);

private:
	void draw();

private slots:
	void animate();
};


class DoubleSlider : public QSlider {
	Q_OBJECT

public:
	DoubleSlider(QWidget* parent = 0);
	~DoubleSlider() {};
	double smooth_value = 0.;
signals:
	void doubleValueChanged(double value);
	void corrValueChanged(double value);
public slots:
	void notifyValueChanged(int value);
	void notifyCorrValueChanged(int value);
};

#endif
