#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "GL/glut.h"

//drawPoints() is used to draw the point and its 7 symmetry point
void drawPoints(int center_x, int center_y, int x, int y) {
	glBegin(GL_POINTS);
	glVertex3f(center_x + x, center_y + y, 0);
	glVertex3f(center_x - x, center_y + y, 0);
	glVertex3f(center_x + x, center_y - y, 0);
	glVertex3f(center_x - x, center_y - y, 0);
	glVertex3f(center_x + y, center_y + x, 0);
	glVertex3f(center_x - y, center_y + x, 0);
	glVertex3f(center_x + y, center_y - x, 0);
	glVertex3f(center_x - y, center_y - x, 0);
	glEnd();
}

//use Bresenham algorithm to decide the position of next point.
void drawCircle_Bresenham(int center_x, int center_y, int r) {
	int x = 0, y = r;
	int p = 3 - 2 * y;
	glBegin(GL_POINTS);
	glVertex3f(center_x, center_y, 0);
	glEnd();
	while (x < y) {
		drawPoints(center_x, center_y, x, y);
		if (p > 0) {
			p = p + 4 * x - 4 * y + 10;
			x = x + 1; 
			y = y - 1;
		}
		else {
			p = p + 4 * x + 6;
			x = x + 1;
		}
	}
	if (x == y) {
		drawPoints(center_x, center_y, x, y);
	}
}

//use Midpoint algorithm to decide the position of next point.
void drawCircle_Midpoint(int center_x, int center_y, int r) {
	int x = 0, y = r;
	int d = 1.25 - r;
	glBegin(GL_POINTS);
	glVertex3f(center_x, center_y, 0);
	glEnd();
	while (x < y) {
		drawPoints(center_x, center_y, x, y);
		if (d < 0) {
			x = x + 1;
			d = d + 2 * x + 3;	
		}
		else {
			x = x + 1;
			y = y - 1;
			d = d + 2 * x - 2 * y + 5;
		}
	}
	if (x == y) {
		drawPoints(center_x, center_y, x, y);
	}
}

void drawCircle_Extra(int center_x, int center_y, int r) {
	int x = 0, y = r;
	int d = 0;
	glBegin(GL_POINTS);
	glVertex3f(center_x, center_y, 0);
	glEnd();
	while (x < y) {
		drawPoints(center_x, center_y, x, y);
		if (d < 0) {
			x = x + 1;
			d = d + 2 * y + 1;
		}
		else {
			y = y - 1;
			d = d - 2 * x + 1;
		}
	}
	if (x == y) {
		drawPoints(center_x, center_y, x, y);
	}

}

//display the circle and set the parameter
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	drawCircle_Bresenham(0, 0, 15);
	drawCircle_Midpoint(32, 0, 15);
	drawCircle_Midpoint(-32, 0, 15);
	glFlush();
}

//initialize the window
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("HW3 by 12330404");
	init();

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}