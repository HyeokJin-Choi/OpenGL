#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.1415f

void glPointSize(GLfloat s);

//void RenderScene(void) { // 2D원 그리기
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
//	glPointSize(2.0f);           // 점 크기 설정
//
//	const float radius = 50.0f;   // 반지름
//	const int numPoints = 360;  // 찍을 점의 개수
//
//	glBegin(GL_POINTS);
//	for (int i = 0; i < numPoints; ++i) {
//		float angle = 2.0f * 3.1415926f * i / numPoints; // 라디안으로 변환
//		float x = radius * cos(angle);
//		float y = radius * sin(angle);
//		glVertex2f(x, y);
//	}
//	glEnd();
//
//	glFlush();
//}

void RenderScene(void) {
	GLfloat x, y, z, angle;
	GLfloat start_x, start_y, start_z;

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(45, 0.0f, 1.0f, 0.0f);

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	z = -50.0f;
	for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f) {
		if (angle == 0.0f) {
			glColor3f(0.0f, 1.0f, 0.0f); // 초록색
			start_x = 50.0f * cos(angle);
			start_y = 50.0f * sin(angle); // 45도에서 꺾어야함
			start_z = z;
			glVertex3f(start_x, start_y, start_z);
		}
		else {
			glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
			x = 50.0f * cos(angle);
			y = 50.0f * sin(angle);
			glVertex3f(x, y, z);
			z += 0.5f;
		}
	}
	glEnd();
	glPopMatrix();

	glFlush();
}

//void RenderScene(void) { //점으로 사각형 만들기.
//	GLfloat x, y;
//	float size = 50.0f;
//	float step = 1.0f;
//
//	glClear(GL_COLOR_BUFFER_BIT);
//	//glPushMatrix();
//
//	//glRotatef(45, 1.0f, 0.0f, 0.0f);
//	//glRotatef(45, 0.0f, 1.0f, 0.0f);
//
//	glPointSize(2.0f);
//	glBegin(GL_POINTS);
//	glColor3f(1.0f, 0.0f, 0.0f); // 빨간 점
//
//	// 아래 변 (왼->오)
//	for (x = -size; x <= size; x += step)
//		glVertex3f(x, -size, 0.0f);
//
//	// 오른쪽 변 (아래->위)
//	for (y = -size; y <= size; y += step)
//		glVertex3f(size, y, 0.0f);
//
//	// 위쪽 변 (오->왼)
//	for (x = size; x >= -size; x -= step)
//		glVertex3f(x, size, 0.0f);
//
//	// 왼쪽 변 (위->아래)
//	for (y = size; y >= -size; y -= step)
//		glVertex3f(-size, y, 0.0f);
//
//	glEnd();
//
//	glPopMatrix();
//	glFlush();
//}



void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void changeSize(GLsizei w, GLsizei h) {
	GLint t = 100;
	GLfloat aspectRatio;
	if (h == 0) h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h) {
		glOrtho(-t, t, -t/aspectRatio, t/aspectRatio, t, -t);
	}
	else {
		glOrtho(-t*aspectRatio, t*aspectRatio, -t, t, t, -t);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple");

	SetupRC();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(changeSize);
	glutMainLoop();
}
