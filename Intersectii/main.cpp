#include <stdio.h>
#include <GL/freeglut.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "scene.h"

double BackgroundColorRGBA[4] = { 1.0, 1.0, 1.0, 0.0 };

using namespace std;

int selectedPointIndex = 0;
bool pointSelected = false;

void MouseClick(int button, int state, int x, int y) {

	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	Point2D clickedPoint(x, windowHeight - y);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		// Find the closest point.
		if (Scene::Points.empty()) {
			return;
		}
		double minimumDistance = clickedPoint.Distance(Scene::Points[0]);
		int closestPointIndex = 0;

		for (unsigned int pointIndex = 1; pointIndex < Scene::Points.size(); pointIndex++) {
			double distance = clickedPoint.Distance(Scene::Points[pointIndex]);
			if (distance < minimumDistance) {
				minimumDistance = distance;
				closestPointIndex = pointIndex;
			}
		}

		if (minimumDistance > 10.0) {
			return;
		}
		selectedPointIndex = closestPointIndex;
		pointSelected = true;
		return;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

		if (pointSelected) {
			pointSelected = false;
			return;
		}
		pointSelected = false;
		Scene::Points.push_back(clickedPoint);
		glutPostRedisplay();
		return;
	}
}

void MouseMove(int x, int y) {

	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	Point2D mousePositionPoint(x, windowHeight - y);
	if (pointSelected) {
		Scene::Points[selectedPointIndex].X = mousePositionPoint.X;
		Scene::Points[selectedPointIndex].Y = mousePositionPoint.Y;
		glutPostRedisplay();
	}
}

void InitializeWindow(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 700);
	glutCreateWindow("Intersections");

	glClearColor(BackgroundColorRGBA[0], BackgroundColorRGBA[1], BackgroundColorRGBA[2], BackgroundColorRGBA[3]);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
	glShadeModel(GL_SMOOTH);

	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(Scene::Render);
	glutMotionFunc(MouseMove);
	glutMouseFunc(MouseClick);
	glutMainLoop();
}

int main(int argc, char ** argv) {
	for (int i = 0; i < 0; i ++ )
	{
		Scene::Points.push_back(Point2D(rand() % 1200 , rand() % 700));
	}
	InitializeWindow(argc, argv);

}
