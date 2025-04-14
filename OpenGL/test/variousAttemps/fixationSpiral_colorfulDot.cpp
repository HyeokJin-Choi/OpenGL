#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.1415f

void glPointSize(GLfloat s);

void RenderScene() {
	GLfloat x, y, z=-50.0f, angle;
	GLint offset = 2;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(45, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POINTS);
	for (angle = 0.0f; angle <= 2 * (GL_PI) * 3.0f; angle += 0.1f) {
		x = 50.0f * cos(angle);
		y = 50.0f * sin(angle);
		GLfloat r = (rand() % 100) / 99.0f; // % 255시 255가지 색상으로 나눌 수 있음.
		GLfloat g = (rand() % 100) / 99.0f;
		GLfloat b = (rand() % 100) / 99.0f;
		glColor3f(r, g, b);
		
		for (float i = -offset; i <= offset; i += 0.2f) {
			glVertex3f(x + i, y + offset, z);
			glVertex3f(x + i, y - offset, z);
			glVertex3f(x + offset, y + i, z);
			glVertex3f(x - offset, y + i, z);
		}
		
		z += 0.5;
	}
	glEnd();

	glPopMatrix();
	glFlush();
}

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void changeSize(GLsizei w, GLsizei h) {
	GLfloat t = 100;
	GLfloat windowRatio;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	windowRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h) {
		glOrtho(-t,t,-t/ windowRatio, t/ windowRatio,t,-t);
	}
	else {
		glOrtho(-t* windowRatio,t* windowRatio,-t,t,t,-t);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_SINGLE| GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Checkjin");

	SetupRC();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(changeSize);
	glutMainLoop();
}
