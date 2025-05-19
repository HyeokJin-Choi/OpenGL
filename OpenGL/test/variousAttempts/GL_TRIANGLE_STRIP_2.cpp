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
	float x, y;
	float centerX = 0.0f, centerY = 0.0f;
	float radius = 50.0f;
	int count = 0;
	bool mutex = false;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(centerX, centerY, 0.0f);  // 중심점
	for (float angle = 0.0f; angle <= 2.0f * GL_PI + 0.1f; angle += (GL_PI/8.0f)) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		/**
		if (count %2 == 0) {
			glColor3f(0.0f, 1.0f, 0.0f);  // 빨간색
		}
		else {
			glColor3f(1.0f, 0.0f, 0.0f);  // 초록색
		}
		*/
		if (mutex) {
			glColor3f(1.0f, 0.0f, 0.0f);
			mutex = false;
		}
		else {
			glColor3f(0.0f, 1.0f, 0.0f);
			mutex = true;
		}
		glVertex3f(x, y, 0.0f);
		count++;
	}
	glEnd();

	/*
	glPointSize(6.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex3f(centerX, centerY, 0.0f);  // 중심점
	for (float angle = 0.0f; angle <= 2.0f * GL_PI + 0.1f; angle += (GL_PI / 8.0f)) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, 0.0f);          // 외곽 점
	}
	glEnd();
	*/

	glFlush();
}


void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	//glShadeModel(GL_FLAT); // 한번만 실행되면 되는 거라서, SetUpRC함수에 넣음.
	glShadeModel(GL_SMOOTH);
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
