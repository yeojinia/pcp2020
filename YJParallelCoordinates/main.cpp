#include "YJParallelCoordinates.h"
#include "graph.hpp"
#include "glut.h"
#include "MyVec.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	QApplication a(argc, argv);
	YJParallelCoordinates w;
	w.show();
	return a.exec();
}
