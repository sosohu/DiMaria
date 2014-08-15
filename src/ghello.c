#include "graph/ghello.h"

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2i(180, 15);
		glVertex2i(10, 145);
	glEnd();

	glFlush();
}

void ghello(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Just For Test");

	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
}
