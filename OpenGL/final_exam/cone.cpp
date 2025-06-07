#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.1415f 
void glPointSize(GLfloat s);
void glLineWidth(GLfloat ls);

float getRandomFloat() {
	return (float)rand() / (float)RAND_MAX;
}

GLfloat xTran = 0.0f;
GLfloat yTran = 0.0f;

void keyboard(unsigned char key, int x, int y) {
	if (key == 'a') {
		xTran -= 2.0f;
	}
	else if (key == 'd') {
		xTran += 2.0f;
	}
	else if (key == 'w') {
		yTran += 2.0f;
	}
	else if (key == 'x') {
		yTran -= 2.0f;
	}
	glutPostRedisplay();
}

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		xRot -= 2.0f;
	else if (key == GLUT_KEY_DOWN)
		xRot += 2.0f;
	else if (key == GLUT_KEY_LEFT)
		yRot -= 2.0f;
	else if (key == GLUT_KEY_RIGHT)
		yRot += 2.0f;
	glutPostRedisplay();
}
void RenderScene(void)
{
	bool bCull = true;
	glClear(GL_COLOR_BUFFER_BIT);

	if (bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(xTran, yTran, 0.0f);

	GLfloat x, y, angle;
	int iPivot = 1;

	// 첫 번째 삼각형 팬 (z = 0.0f)
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
	{
		x = 50.0f * sin(angle);
		y = 50.0f * cos(angle);

		if ((iPivot % 2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);

		iPivot++;
		glVertex2f(x, y);
	}
	glEnd();

	// 두 번째 삼각형 팬 (z = 80.0f)
	iPivot = 1;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 80.0f);
	for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
	{
		x = 50.0f * cos(angle);
		y = 50.0f * sin(angle);

		if ((iPivot % 2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);

		iPivot++;
		glVertex3f(x, y, 0.0f);
	}
	glEnd();

	glPopMatrix();
	glFlush();
}


void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_FLAT);
}

void changeSize(GLsizei w, GLsizei h) {
	GLfloat t = 100;
	GLfloat wSizeRatio;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	wSizeRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h) {
		glOrtho(-t, t, -t / wSizeRatio, t / wSizeRatio, t, -t);
	}
	else {
		glOrtho(-t * wSizeRatio, t * wSizeRatio, -t, t, t, -t);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Checkjin");

	SetupRC();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(changeSize);
	glutMainLoop();
}
