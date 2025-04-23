#include <GL/glut.h>
#include <iostream>
#define GL_PI 3.141592
using namespace std;
void glPointSize(GLfloat size);
void glLineSize(GLfloat size);
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,75.0f,0.0f);
	glVertex3f(0.0f, 75.0f, 0.0f);
	glVertex3f(5.0f, 70.0f, 0.0f);
	glVertex3f(0.0f, 75.0f, 0.0f);
	glVertex3f(-5.0f, 70.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(75.0f, 0.0f, 0.0f);
	glVertex3f(75.0f, 0.0f, 0.0f);
	glVertex3f(70.0f, 0.0f, 5.0f);
	glVertex3f(75.0f, 0.0f, 0.0f);
	glVertex3f(70.0f, 0.0f, -5.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 75.0f);
	glVertex3f(0.0f, 0.0f, 75.0f);
	glVertex3f(5.0f, 0.0f, 70.0f);
	glVertex3f(0.0f, 0.0f, 75.0f);
	glVertex3f(-5.0f, 0.0f, 70.0f);

	glEnd();

	glPopMatrix();
	glFlush();
}
void SetupRC(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat aspectRatio;
	GLfloat t = 100.0f;
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	aspectRatio = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-t, t, -t / aspectRatio, t * aspectRatio, t, -t);
	}
	else {
		glOrtho(-t * aspectRatio, t * aspectRatio, -t, t, t, -t);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("Checkjin's RenderScene");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
}
