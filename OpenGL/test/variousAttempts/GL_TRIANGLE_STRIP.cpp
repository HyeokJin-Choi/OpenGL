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
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(0.0f, 0.0f); //v0
	glVertex2f(50.0f, 0.0f); //v1
	glVertex2f(50.0f, 50.0f); //v2, v0v1v2 삼각형 생성
	glVertex2f(0.0f, 50.0f); //v3, v1v2v3 삼각형 생성
	glVertex2f(50.0f, 100.0f); //v4, v2v3v4 삼각형 생성
	glEnd();

	glFlush();
}

// void RenderScene() { //다른 그림으로 도전
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	glColor3f(1.0f, 0.0f, 0.0f);

// 	glBegin(GL_TRIANGLE_STRIP);
// 	glVertex2f(0.0f, 0.0f); //v0
// 	glVertex2f(0.0f, 12.5f); //v1
// 	glVertex2f(12.5f, 0.0f); //v2
// 	glVertex2f(12.5f, 25.0f); //v3
// 	glVertex2f(37.5f, 0.0f); //v4
// 	glVertex2f(37.5f, 50.0f); //v5
// 	glVertex2f(87.5f, 0.0f); //v6
// 	glEnd();

// 	glColor3f(0.0f, 0.0f, 1.0f);
// 	glLineWidth(2.0f);
// 	glBegin(GL_LINE_STRIP);
// 	glVertex2f(0.0f, 0.0f); //v0
// 	glVertex2f(0.0f, 12.5f); //v1
// 	glVertex2f(12.5f, 0.0f); //v2
// 	glVertex2f(12.5f, 25.0f); //v3
// 	glVertex2f(37.5f, 0.0f); //v4
// 	glVertex2f(37.5f, 50.0f); //v5
// 	glVertex2f(87.5f, 0.0f); //v6
// 	glEnd();

// 	glFlush();
// }

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
