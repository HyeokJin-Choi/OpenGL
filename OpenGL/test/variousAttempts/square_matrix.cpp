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
	GLfloat offset = 25.0f;
	glGetFloatv(GL_LINE_WIDTH_RANGE, sizes);
	glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &step);

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(45, 0.0f, 1.0f, 0.0f); 

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	/*
	//---------------
	glVertex3f(-offset, -offset, -offset);
	glVertex3f(offset, -offset, -offset); //x축
	glVertex3f(-offset, -offset, -offset);
	glVertex3f(-offset, offset, -offset); //y축
	glVertex3f(-offset, -offset, -offset);
	glVertex3f(-offset, -offset, offset); //z축

	glVertex3f(-offset, offset, offset);
	glVertex3f(offset, offset, offset); //x축
	glVertex3f(-offset, offset, offset);
	glVertex3f(offset, -offset, offset); //y축
	glVertex3f(-offset, offset, offset);
	glVertex3f(-offset, offset, -offset); //z축

	glVertex3f(offset, offset, -offset);
	glVertex3f(-offset, offset, -offset); //x축
	glVertex3f(offset, offset, -offset);
	glVertex3f(offset, -offset, -offset); //y축
	glVertex3f(offset, offset, -offset);
	glVertex3f(offset, offset, offset); //z축

	glVertex3f(offset, -offset, offset);
	glVertex3f(-offset, -offset, offset); //x축
	glVertex3f(offset, -offset, offset);
	glVertex3f(offset, offset, offset); //y축
	glVertex3f(offset, -offset, offset);
	glVertex3f(offset, -offset, -offset); //z축
	//-----------------
	glEnd();
	*/
	glBegin(GL_LINES);

	// ✅ 정육면체 꼭짓점 8개
	GLfloat v[8][3] = {
		{-offset, -offset, -offset}, // 0
		{ offset, -offset, -offset}, // 1
		{ offset,  offset, -offset}, // 2
		{-offset,  offset, -offset}, // 3
		{-offset, -offset,  offset}, // 4
		{ offset, -offset,  offset}, // 5
		{ offset,  offset,  offset}, // 6
		{-offset,  offset,  offset}  // 7
	};

	// ✅ 정육면체 모서리 12개
	int edges[12][2] = {
		{0, 1}, {1, 2}, {2, 3}, {3, 0}, // 아래 면
		{4, 5}, {5, 6}, {6, 7}, {7, 4}, // 위 면
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  // 수직 연결
	};

	for (int i = 0; i < 12; ++i) {
		glVertex3fv(v[edges[i][0]]);
		glVertex3fv(v[edges[i][1]]);
	}

	glEnd();

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
