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

	GLfloat factor = 1;
	GLushort pattern = 0x5555;

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glRotatef(90, 0.0f, 0.0f, 1.0f);
	//glRotatef(90, 0.0f, 1.0f, 0.0f); 

	glColor3f(1.0f, 0.0f, 0.0f);
	glEnable(GL_LINE_STIPPLE); // 점선
	for (GLfloat offset = -75.0f; offset <= 75.0f; offset += 25.0f) {

		glLineStipple(factor, pattern); // factor는 점선의 간격(각 비트마다 몇 개의 픽셀을 차지할지), pattern은 아래와 같음 
		// 0x00FF = 0000 0000 1111 1111 (2진수)로 쳤을때 
		// 앞의 8비트(00000000) → 빈 공간 (선을 안 그림)
		// 뒤의 8비트(11111111) → 선을 그림
		// 이 패턴이 반복됨 → 빈 공간 8칸 → 선 8칸 반복
		/*  factor = 1이면
			→ 0101 0101 0101 0101 이 패턴을 그대로 한 픽셀 단위로 사용

			factor = 2이면
			→ 각 비트당 2픽셀을 차지하니까
			00 11 00 11 ... 처럼 길이가 2배 늘어난 점선이 돼

			factor = 3이면
			→ 000 111 000 111 ... 처럼
			선과 공백이 3픽셀씩 번갈아가며 그려짐
		*/



		glBegin(GL_LINES);
		glVertex2f(80.0f, offset);
		glVertex2f(-80.0f, offset);
		glEnd();

		factor++;
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
