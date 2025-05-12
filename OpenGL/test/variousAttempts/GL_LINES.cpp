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

void RenderScene() {
	GLfloat x, y, z, angle;
	GLfloat sizes[2], step;
	GLfloat lineSize;
	glGetFloatv(GL_LINE_WIDTH_RANGE, sizes);
	glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &step);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glRotatef(45, 0.0f, 0.0f, 1.0f); 
	//glRotatef(90, 0.0f, 1.0f, 0.0f); 

	glColor3f(1.0f, 0.0f, 0.0f);
	lineSize = sizes[0];

	for (GLfloat offset = -75.0f; offset <= 75.0f; offset += 25.0f) {

		glLineWidth(lineSize);
		glBegin(GL_LINES);
		glVertex2f(80.0f, offset);
		glVertex2f(-80.0f, offset);
		glEnd();

		lineSize += 2.0f;
	}

	glPopMatrix();
	glFlush();
}

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void changeSize(GLsizei w, GLsizei h) {
	GLfloat t = 100;
	GLfloat wSizeRatio;
	glViewport(0, 0, w, h); // 도화지는 카메라의 투영과 상관없으니, glMatrixMode()함수 안에 들어가지 x

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	wSizeRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h) { // 세로로 창이 늘어남 -> 투영을 세로로 확장
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
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(changeSize);
	glutMainLoop();
}
