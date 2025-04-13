#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.1415f

void glPointSize(GLfloat s);

float getRandomFloat() {
    return (float)rand() / (float)RAND_MAX;
}

void RenderScene() {
	GLfloat x, y, z, angle;
	GLfloat r=0.0f, g=0.0f, b=0.0f;
	GLfloat sizes[2], step;
	GLfloat pointSize;
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glRotatef(45, 1.0f, 0.0f, 0.0f); // x축을 기준으로 45도 회전
	glRotatef(45, 0.0f, 1.0f, 0.0f); // y축을 기준으로 45도 회전

	z = -25.0f;
	float squaresize = 5.0f;
	float spacing = 0.3;
	float halfsize = squaresize / 2.0f;

	pointSize = sizes[0];
	
	for (angle = 0.0f; angle <= (2.0f * GL_PI) * 5.0f; angle += 0.1f) {
		x = 25.0f * cos(angle);
		y = 25.0f * sin(angle);

		r = getRandomFloat();
		g = getRandomFloat();
		b = getRandomFloat();

		glColor3f(r, g, b);
		glPointSize(pointSize);
		glBegin(GL_POINTS);
		for (float dx = -halfsize; dx <= halfsize; dx += spacing) { //왼쪽에서 오른쪽으로 점을 찍음
			glVertex3f(x + dx, y + halfsize, z); // 윗변
			glVertex3f(x + dx, y - halfsize, z); // 아랫변
		}
		for (float dy = -halfsize; dy <= halfsize; dy += spacing) { //아래쪽에서 위쪽으로 점을 찍음
			glVertex3f(x - halfsize, y + dy, z); //좌측변
			glVertex3f(x + halfsize, y + dy, z); //우측변
		}
		glEnd();

		z += 0.25f;
		pointSize += step;
		if (pointSize > sizes[1]) {
			pointSize = sizes[1];
		}

	}

	glPopMatrix();
	glFlush();
}

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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
		glOrtho(-t * wSizeRatio, t * wSizeRatio, -t, t, t ,-t);
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
