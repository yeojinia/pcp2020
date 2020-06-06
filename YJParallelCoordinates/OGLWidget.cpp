#include "OGLWidget.h"
#include "graph.hpp"
#include <string>

#define M_PI 3.141592
void	DoRasterString(float, float, float, char *);
const int INIT_WINDOW_SIZE = { 600 };
MyDataSet* mydata = MyDataSet::getInstance();

void DoRasterString(float x, float y, float z, char *s)
{
	// Range of Position (-1.3~1.3: width, 0~2: height)
	int length = strlen(s);
	x -= (length / 2.) / 50.;

	glPushMatrix();

	glRasterPos3f(x, y, (GLfloat)z);

	char c;			// one character to print
	for (; (c = *s) != '\0'; s++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
		//glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
	}
	glPopMatrix();
}


PCPWidget::PCPWidget(QWidget *parent) :QOpenGLWidget(parent)
{

}

PCPWidget::~PCPWidget()
{
}

void PCPWidget::initializeGL()
{
	qDebug() << "\tPCPWidget::initializeGL()";

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(INIT_WINDOW_SIZE, INIT_WINDOW_SIZE);

	glClearColor(0.887f, 0.887f, 0.887f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	UIInfo::getInstance()->widget_height = this->height();
	UIInfo::getInstance()->widget_width = this->width();
}

void PCPWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat x = (GLfloat)w / h;
	glFrustum(-x, x, -1.0, 1.0, 10., 15.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void PCPWidget::paintGL()
{
	//	qDebug() << "\tPCPWidget::paintGL()";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.887f, 0.887f, 0.887f, 0.0f);
	
	draw();
}


void PCPWidget::mousePressEvent(QMouseEvent *event)
{
	
	qDebug() << "\tPCPWidget::mousePressEvent" << event->x() << ", " << event->y();

}

void PCPWidget::mouseMoveEvent(QMouseEvent *event)
{
	qDebug() << "\tPCPWidget::mouseMoveEvent" << event->x() << ", " << event->y();

}

void PCPWidget::mouseReleaseEvent(QMouseEvent *event)
{
	float x = event->x();
	float y = event->y();
	qDebug() << "\tPCPWidget::mouseReleaseEvent, x: " << x << ", y: " << y;

}

void PCPWidget::updatePosition(int width, int height)
{
	float ratio = (float)width / (float)height;

	int num_features = mydata->features.size();
	for (int idx = 0; idx < mydata->features.size(); idx++) {
		int feature_id = mydata->features[idx].ordinal_id;
		mydata->features[idx].pos_x = -ratio + (float)(2.*ratio*(float)(feature_id + 1)) / (float)(num_features + 1);
	}
}

void PCPWidget::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0., 0., -10.); // -10: default

	glColor3d(0.5, 0.5, 1.);

	// update position to mydata
	updatePosition(width(), height());

	// Draw Coordinates
	drawCoordinates();

	// Draw Data
	drawSmoothLines(); // default

	// Draw Names of Feature
	glColor3f(0.153, 0.33, 0.4);
	drawFeatureNames();
	drawRanges();

	glFlush();

}

void PCPWidget::drawSmoothLines()
{

	int num_features = mydata->features.size();
	int num_examples = mydata->num_examples;

	// Draw Data Lines
	for (int i = 0; i < num_features - 1; i++) {
		for (int j = 0; j < num_examples; j++) {
			my_vec::my_vec2 start_anchor = getDataViewportPositionByDataIdx(i, j);
			my_vec::my_vec2 end_anchor = getDataViewportPositionByDataIdx(i + 1, j);

			my_vec::my_vec2 prev_start;
			if (i == 0) {
				prev_start = (start_anchor * 2.) - end_anchor;
			}
			else {
				prev_start = getDataViewportPositionByDataIdx(i - 1, j);
			}
			my_vec::my_vec2 next_end;
			if (i == num_features - 2) {
				next_end = (end_anchor * 2.) - start_anchor; 
			}
			else {
				next_end = getDataViewportPositionByDataIdx(i + 2, j);
			}

			float right = 1.;
			float left = -1.;
			my_vec::my_vec2 start_ctrl_pt = computeCtrlpoints(prev_start, start_anchor, end_anchor, right);
			my_vec::my_vec2 end_ctrl_pt = computeCtrlpoints(start_anchor, end_anchor, next_end, left);

			drawCubicBezierCurve(start_ctrl_pt, end_ctrl_pt, start_anchor, end_anchor, j);
		}
	}
	this->update();
}

my_vec::my_vec2 PCPWidget::computeCtrlpoints(my_vec::my_vec2 prev, my_vec::my_vec2 current, my_vec::my_vec2 next, float direction)
{
	// Construct opposed_line
	double angle = atan2(prev.y() - next.y(), prev.x() - next.x());
	float lengthX = (next.x() - prev.x())*(next.x() - prev.x());
	float lengthY = (next.y() - prev.y())*(next.y() - prev.y());
	double length = sqrt((double)(lengthX + lengthY));
	double smoothness = mydata->smooth_value;
	
	length = smoothness * length;

	if (direction < 0.)
		return my_vec::my_vec2((current.x()) + (float)(length*cos(angle)), (current.y()) + (float)(length*sin(angle)));
	else
		return my_vec::my_vec2((current.x()) - (float)(length*cos(angle)), (current.y()) - (float)(length*sin(angle)));
}


void PCPWidget::drawCubicBezierCurve(my_vec::my_vec2 start_ctrl, my_vec::my_vec2 end_ctrl, my_vec::my_vec2 start_anchor, my_vec::my_vec2 end_anchor, int index)
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	auto NUMPOINTS = mydata->NUMPOINTS;
	float r = std::get<0>(mydata->color[index]);
	float g = std::get<1>(mydata->color[index]);
	float b = std::get<2>(mydata->color[index]);

	glBegin(GL_LINE_STRIP);
	double slope = (end_ctrl.y() - start_ctrl.y()) / (end_ctrl.x() - start_ctrl.x());

	double max_slope = ((2. / 3.) - (-2. / 3.)) / (end_anchor.x() - start_anchor.x());
	double min_slope = -max_slope;
	double avg_slope = abs(slope / (max_slope - min_slope));
	for (int it = 0; it <= NUMPOINTS; it++) {

		double t = (double)it / (double)NUMPOINTS;
		glColor4f(r, g, b, 1.);// avg_slope);
		double omt = 1.f - t;
		double omt_3 = omt * omt*omt;
		double omt_2 = omt * omt * 3.f*t;
		double omt_1 = 3.f*t*t*omt;
		double omt_0 = t * t*t;
		my_vec::my_vec2 vertex_ = ((start_anchor * omt_3) + (start_ctrl * omt_2) + (end_ctrl * omt_1) + (end_anchor * omt_0));
		double z = 0.;
		glVertex3d(vertex_.x(), vertex_.y(), z);
	
	}
	glEnd();
	glDisable(GL_BLEND);
}


void PCPWidget::drawCoordinates()
{
	int num_features = mydata->features.size();

	glLineWidth(1.5);
	glColor3f(0.153, 0.33, 0.4);
	glBegin(GL_LINES);
	for (int i = 0; i < num_features; i++) {
		// read the position of feature, and then draw them.
		auto pos = getAttributeViewportPositionByAttributeIdx(i);
		float center_x = std::get<0>(pos);
		float center_y = std::get<1>(pos);
		float len = std::get<2>(pos);
		glVertex3f(center_x, center_y - (len / 2.), 0.);
		glVertex3f(center_x, center_y + (len / 2.), 0.);
	}
	glEnd();
	glLineWidth(1);
}

void PCPWidget::drawFeatureNames()
{
	QStringList feature_name = mydata->feature_name;
	if (mydata->features.size() != 0) {
		for (int i = 0; i < feature_name.size(); i++) {
			float x = mydata->features[i].pos_x;
			float y = (mydata->features[i].pos_y) + (15. / 18.);
			DoRasterString(x, y, 0., feature_name[i].toUtf8().data());
		}
	}
	else {
		float ratio = float(((float)UIInfo::getInstance()->widget_width) / ((float)UIInfo::getInstance()->widget_height));
		for (int i = 0; i < feature_name.size(); i++) {
			float x = -ratio + (float)(2.*ratio*(float)(i + 1)) / (float)(feature_name.size() + 1);
			float y = (7. / 9.);
			DoRasterString(x, y, 0., feature_name[i].toUtf8().data());
		}
	}
}

void PCPWidget::drawRanges()
{
	for (int i = 0; i < mydata->features.size(); i++) {
		float ratio = float(((float)UIInfo::getInstance()->widget_width) / ((float)UIInfo::getInstance()->widget_height));
		std::string minimum = std::to_string(mydata->features[i].item_min);
		std::string maximum = std::to_string(mydata->features[i].item_max);
		float x1 = mydata->features[i].pos_x;
		float y1 = (mydata->features[i].pos_y) + (13. / 18.);
		float y2 = (mydata->features[i].pos_y) - (13. / 18.);
		DoRasterString(x1, y1, 0., (char *)maximum.c_str());
		DoRasterString(x1, y2, 0., (char *)minimum.c_str());

	}
}

my_vec::my_vec2 PCPWidget::getDataViewportPositionByDataIdx(int feature_id, int example_idx)
{
	auto view_pos = getFeatureViewportPositionByFeatureId(feature_id);
	double view_x = (double)(std::get<0>(view_pos));
	float feature_y_center = std::get<1>(view_pos);
	float length = std::get<2>(view_pos);
	float feature_y_bot = feature_y_center - (length / 2.);
	float feature_y_top = feature_y_center + (length / 2.);

	float min = mydata->features[feature_id].item_min;
	float max = mydata->features[feature_id].item_max;
	float value = mydata->features[feature_id].items[example_idx].value;
	double view_y = (double)(feature_y_bot + (feature_y_top - feature_y_bot)*(value - min) / (max - min));

	return my_vec::my_vec2(view_x, view_y);
}

// return <viewport_x, viewport_feature_bottom, viewport_feature_top>
std::tuple<float, float, float> PCPWidget::getAttributeViewportPositionByAttributeIdx(int feature_idx)
{

	float ratio = (float)width() / (float)height();

	float v_x = mydata->features[feature_idx].pos_x;
	float v_y = 0.;
	float length = 4. / 3.;

	return std::make_tuple(v_x, v_y, length);
}

std::tuple<float, float, float> PCPWidget::getFeatureViewportPositionByFeatureId(int feature_id)
{

	float ratio = (float)width() / (float)height();
	int num_features = mydata->num_features;

	float v_x = -ratio + (2.*ratio*(float)(feature_id + 1.)) / (float)(num_features + 1);
	float v_y = 0.;
	float length = 4. / 3.;

	return std::make_tuple(v_x, v_y, length);
}


std::tuple<float, float> PCPWidget::getWidgetSize()
{
	return std::make_tuple((float)this->width(), (float)this->height());
}

ColorPanel::ColorPanel(QWidget *parent) :QOpenGLWidget(parent)
{

}

ColorPanel::~ColorPanel()
{

}
void ColorPanel::initializeGL()
{
	//qDebug() << "\tColorPanel::initializeGL()";
	glClearColor(0.168627f, 0.168627f, 0.168627f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

}
void ColorPanel::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

}
void ColorPanel::paintGL()
{

}

void ColorPanel::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	drawColorWheel(&p);

}
ColorPanel::Cartesian ColorPanel::polarToCartesian(qreal radius, qreal angle)
{
	Cartesian cartesian;
	cartesian.x = (this->width() / 2) + radius * qCos(angle);
	cartesian.y = (this->width() / 2) + radius * qSin(angle);

	return cartesian;
}

ColorPanel::Polar ColorPanel::cartesianToPolar(qreal x, qreal y)
{
	qreal theta = qAtan2(y, x);
	if (theta < 0) {
		theta += (2 * M_PI);
	}
	qreal r = qSqrt((x*x) + (y*y));
	Polar p;
	p.angle = theta;
	p.radius = r;
	return p;
}
void ColorPanel::drawColorWheel(QPainter *p)
{
	QPen pen;
	// draw Color Wheel
	for (int w = 0; w < width(); w++) {//
		for (int h = 0; h < height(); h++) {
			int a = w - (width() / 2);//
			int b = (height() / 2) - h;
			Polar polar = cartesianToPolar(b, a);
			if (polar.radius <= width() / 2) {//		
				qreal hue = (polar.angle) / (2 * M_PI);
				qreal sat = polar.radius / width();

				QColor color;
				color.setHsvF(hue, sat, 0.5);
				int r, g, b;
				color.getRgb(&r, &g, &b);
				//qDebug() << r << g << b;
				pen.setColor(color);
				p->setPen(pen);
				p->drawPoint(QPoint(w, h));
			}
		}
	}
	
	// represent cluster color as a black
	for (int i = 0; i < cluster_color.size(); i++) {

		Cartesian pos = rgbToPos(std::get<0>(cluster_color[i]), std::get<1>(cluster_color[i]), std::get<2>(cluster_color[i]));
		pen.setColor(BLACK_PEN);
		pen.setWidth(5);
		p->setPen(pen);
		p->drawPoint(QPoint(pos.x, pos.y));
		if (i == cluster_color.size() - 1)
			this->update();
	}

}

ColorPanel::Cartesian ColorPanel::rgbToPos(float r, float g, float b)
{
	QColor color(r, g, b, 1.);
	qreal hue, saturation, value, alpha;
	color.getHsvF(&hue, &saturation, &value, &alpha);

	// hsv to position in polar coordinates
	Polar polar;
	polar.angle = hue * (2 * M_PI);
	polar.radius = (width() / 2) * saturation;

	// polar coordinate to cartesian coordinates
	return polarToCartesian(polar.radius, polar.angle);

}
std::tuple<int, int, int> ColorPanel::posToRgb(int w, int h)
{
	return std::make_tuple(0, 0, 0);
}
void ColorPanel::set_default_cluster_color()
{
	cluster_color.clear();
	
	for (int i = 0; i < mydata->num_clusters; i++) {
		float r_f = std::get<0>(mydata->cluster_color[i]);
		float g_f = std::get<1>(mydata->cluster_color[i]);
		float b_f = std::get<2>(mydata->cluster_color[i]);
		cluster_color.push_back(std::make_tuple((int)(r_f*255.), (int)(g_f*255.), (int)(b_f*255.)));
	}
}

HPCPWidget::HPCPWidget(QWidget *parent) :QOpenGLWidget(parent)
{

	QTimer *aTimer = new QTimer;
	connect(aTimer, SIGNAL(timeout()), SLOT(animate()));
	aTimer->start(10);
}

HPCPWidget::~HPCPWidget()
{
}

void HPCPWidget::initializeGL()
{
	qDebug() << "\tHPCPWidget::initializeGL()";

	glClearColor(0.887f, 0.887f, 0.887f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

}

void HPCPWidget::resizeGL(int w, int h)
{
	qDebug() << "\tHPCPWidget::resize()";

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = (GLfloat)w / h;
	glOrtho(0., 2., 0., 2., 0., 1000.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void HPCPWidget::paintGL()
{
	//	qDebug() << "\tPCPWidget::paintGL()";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
	this->update();
}

void HPCPWidget::animate()
{
	// change variable here
	for (int i = 0; i < mydata->vGraph.size(); i++) {
		if (mydata->vGraph[i].iterate() > 0);
		else {
			if (mydata->vGraph[i].update_cycle() > 0) {
				mydata->vGraph[i].add_subvisions();

			}
			else {
				if (mydata->vGraph[i]._smooth_flag == false) {
					mydata->vGraph[i].smooth();
					mydata->vGraph[i]._smooth_flag = true;
				}
			}
		}
	}

}


void HPCPWidget::mousePressEvent(QMouseEvent *event)
{

}

void HPCPWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void HPCPWidget::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0., 0., -5.);

	glColor3f(0, 0, 1);

	drawFeatureNames();
	drawRanges();
	drawAxes();

	for (int i = 0; i < mydata->vGraph.size(); i++)
		mydata->vGraph[i].draw(1);

	glFlush();

}

void HPCPWidget::drawAxes()
{
	glLineWidth(1.5);
	glBegin(GL_LINES);
	for (int i = 0; i < mydata->num_features; i++) {
		float x = (2.*(double)(i + 1)) / ((double)(mydata->num_features + 1));
		glVertex3f(x, 1.67, 0);
		glVertex3f(x, 0.33, 0);
	}
	glEnd();
}

void HPCPWidget::drawFeatureNames()
{
	glColor3f(0.153, 0.33, 0.4);

	QStringList feature_name = mydata->feature_name;
	if (mydata->features.size() != 0) {
		for (int i = 0; i < feature_name.size(); i++) {
			float x = (float)(2.*(float)(i + 1)) / (float)(feature_name.size() + 1);//MyDataSet::getInstance()->features[i].pos_x;
			float y = (mydata->features[i].pos_y) + 1 + (15. / 18.);
			DoRasterString(x, y, 0., feature_name[i].toUtf8().data());
		}
	}

}

void HPCPWidget::drawRanges()
{
	for (int i = 0; i < mydata->features.size(); i++) {
		std::string minimum = std::to_string(mydata->features[i].item_min);
		std::string maximum = std::to_string(mydata->features[i].item_max);
		float x1 = (float)(2.*(float)(i + 1)) / (float)(mydata->features.size() + 1);
		float y1 = (mydata->features[i].pos_y) + 1 + (13. / 18.);
		float y2 = (mydata->features[i].pos_y) + 1 - (13. / 18.);
		DoRasterString(x1, y1, 0., (char *)maximum.c_str());
		DoRasterString(x1, y2, 0., (char *)minimum.c_str());

	}
}

void HPCPWidget::timerEvent(QTimerEvent* e)
{

}


HBWidget::HBWidget(QWidget *parent) :QOpenGLWidget(parent)
{

	QTimer *aTimer = new QTimer;
	connect(aTimer, SIGNAL(timeout()), SLOT(animate()));
	aTimer->start(10);
}

HBWidget::~HBWidget()
{
}

void HBWidget::initializeGL()
{
	qDebug() << "\tHPCPWidget::initializeGL()";

	glClearColor(0.887f, 0.887f, 0.887f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

}

void HBWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = (GLfloat)w / h;
	glOrtho(0., 2., 0., 2., 0., 1000.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	qDebug() << "\tHBWidget::resize()";
}

void HBWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
	this->update();
}

void HBWidget::animate()
{
}


void HBWidget::mousePressEvent(QMouseEvent *event)
{
}

void HBWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void HBWidget::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0., 0., -5.);

	glColor3f(0, 0, 1);

	drawFeatureNames();
	drawRanges();
	drawAxes();
	drawGraphs();

	glFlush();

}

void HBWidget::drawGraphs()
{
	std::vector< my_vec::my_vec2 * > point_set;

	for (int i = 0; i < (2* mydata->vGraph.size()) +1; i++) {
		point_set.push_back(new my_vec::my_vec2[mydata->num_examples]);
	}
	
	for (int i = 0; i < mydata->vGraph.size(); i++) {

		std::vector<anchor_pts> points = mydata->vGraph[i].get_three_points();
	
		for (int j = 0; j < points.size(); j++) {
			point_set[2 * i][j] = std::get<0>(points[j]);
			point_set[2 * i + 1][j] = std::get<1>(points[j]);

		}

		if (i == mydata->vGraph.size() - 1) {
			std::vector<my_vec::my_vec2> last_point = mydata->vGraph[i].get_last_points();
			for (int j = 0; j < last_point.size(); j++) {
				point_set[point_set.size() - 1][j] = last_point[j];
			}
		}
	}

	for (int i = 0; i < point_set.size() - 1; i++) {
		for (int j = 0; j < mydata->num_examples; j++) {
			my_vec::my_vec2 prev;
			my_vec::my_vec2 next;
			float right = 1.;
			float left = -1.;

			if (i == 0) {
				prev = (point_set[i][j] * 2.) - point_set[i+1][j];
			}
			else {
				prev = point_set[i - 1][j];
			}
			if (i == point_set.size() - 2) {
				next = (point_set[i + 1][j] * 2.) - point_set[i][j];
			}
			else {
				next = point_set[i + 2][j];
			}

			my_vec::my_vec2 start_ctrl_pt = computeCtrlpoints(prev, point_set[i][j], point_set[i + 1][j], right);
			my_vec::my_vec2 end_ctrl_pt = computeCtrlpoints(point_set[i][j], point_set[i + 1][j], next, left);
		
			drawCubicBezierCurve(start_ctrl_pt, end_ctrl_pt, point_set[i][j], point_set[i + 1][j], j);

		}

	}
}
my_vec::my_vec2 HBWidget::computeCtrlpoints(my_vec::my_vec2 prev, my_vec::my_vec2 current, my_vec::my_vec2 next, float direction)
{
	// Construct opposed_line
	double angle = atan2(prev.y() - next.y(), prev.x() - next.x());
	double lengthX = (next.x() - prev.x())*(next.x() - prev.x());
	double lengthY = (next.y() - prev.y())*(next.y() - prev.y());
	double length = sqrt((double)(lengthX + lengthY));
	double smoothness = mydata->smooth_value;

	smoothness = 0.1;
	length = smoothness * length;

	if (direction < 0.)
		return my_vec::my_vec2(current.x() + (float)(length*cos(angle)), current.y() + (float)(length*sin(angle)));
	else
		return my_vec::my_vec2(current.x() - (float)(length*cos(angle)), current.y() - (float)(length*sin(angle)));
}


void HBWidget::drawCubicBezierCurve(my_vec::my_vec2 start_ctrl, my_vec::my_vec2 end_ctrl, my_vec::my_vec2 start_anchor, my_vec::my_vec2 end_anchor, int index)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto NUMPOINTS = mydata->NUMPOINTS;
	float r = std::get<0>(mydata->color[index]);
	float g = std::get<1>(mydata->color[index]);
	float b = std::get<2>(mydata->color[index]);

	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	double slope = (end_ctrl.y() - start_ctrl.y()) / (end_ctrl.x() - start_ctrl.x());
	double max_slope = ((2. / 3.) - (-2. / 3.)) / (end_anchor.x() - start_anchor.x());
	double min_slope = -max_slope;
	double avg_slope = abs(slope / (max_slope - min_slope));
	for (int it = 0; it <= NUMPOINTS; it++) {
		double t = (double)it / (double)NUMPOINTS;
		glColor4d(r, g, b, 1.);
		double omt = 1.f - t;
		double omt_3 = omt * omt*omt;
		double omt_2 = omt * omt * 3.f*t;
		double omt_1 = 3.f*t*t*omt;
		double omt_0 = t * t*t;
		my_vec::my_vec2 vertex_= ((start_anchor * omt_3) + (start_ctrl * omt_2) + (end_ctrl * omt_1) + (end_anchor * omt_0));
		double z = 0.;
		glVertex3d(vertex_.x(), vertex_.y(), z);
	}
	glEnd();
	glDisable(GL_BLEND);
}

void HBWidget::drawAxes()
{
	glLineWidth(1.5);
	glBegin(GL_LINES);
	for (int i = 0; i < mydata->num_features; i++) {
		float x = (2.*(double)(i + 1)) / ((double)(mydata->num_features + 1));
		glVertex3f(x, 1.67, 0);
		glVertex3f(x, 0.33, 0);
	}
	glEnd();
}

void HBWidget::drawFeatureNames()
{
	glColor3f(0.153, 0.33, 0.4);

	
	QStringList feature_name = mydata->feature_name;
	if (mydata->features.size() != 0) {
		for (int i = 0; i < feature_name.size(); i++) {
			float x = (float)(2.*(float)(i + 1)) / (float)(feature_name.size() + 1);
			float y = (mydata->features[i].pos_y) + 1 + (15. / 18.);
			DoRasterString(x, y, 0., feature_name[i].toUtf8().data());
		}
	}

}

void HBWidget::drawRanges()
{
	for (int i = 0; i < mydata->features.size(); i++) {
		std::string minimum = std::to_string(mydata->features[i].item_min);
		std::string maximum = std::to_string(mydata->features[i].item_max);
		float x1 = (float)(2.*(float)(i + 1)) / (float)(mydata->features.size() + 1);
		float y1 = (mydata->features[i].pos_y) + 1 + (13. / 18.);
		float y2 = (mydata->features[i].pos_y) + 1 - (13. / 18.);
		DoRasterString(x1, y1, 0., (char *)maximum.c_str());
		DoRasterString(x1, y2, 0., (char *)minimum.c_str());

	}
}

void HBWidget::timerEvent(QTimerEvent* e)
{

}

DoubleSlider::DoubleSlider(QWidget* parent) :QSlider(parent)
{
	connect(this, SIGNAL(valueChanged(int)), this, SLOT(notifyValueChanged(int)));
	connect(this, SIGNAL(valueChanged(int)), this, SLOT(notifyCorrValueChanged(int)));
}

void DoubleSlider::notifyValueChanged(int value)
{
	double doubleValue = (double)value / 300.0;
	emit doubleValueChanged(doubleValue);

}

void DoubleSlider::notifyCorrValueChanged(int value)
{
	double doubleValue = (double)value / 100.0;
	emit corrValueChanged(doubleValue);
}
