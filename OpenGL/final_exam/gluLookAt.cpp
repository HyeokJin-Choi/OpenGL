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
	bool bDepth = true;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 깊이에 따라 객체를 화면에 출력하는 모드를 설정

	if (bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if (bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // 카메라가 물체를 지나치거나 돌 때마다 좌표가 일시적으로 물체가 시야 밖으로 나갈 수도 있음.


	//카메라 좌표는 투영될 화면 방향을 결정
	gluLookAt(0.0f, 0.0f, 0.0f, //카메라 위치
		0.0f, 0.0f, -1.0f, //바라볼 목표 지점
		0.0f, 1.0f, 0.0f); // 카메라 상향 벡터 - 보통 (0,1,0) 사용
	// 후면 제거 유무는 Ortho와는 관련없음. Ortho는 단지 보이는 그림의 반전에만 영향

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(xTran, yTran, 0.0f);



	GLfloat x, y, angle, z = 20.0f;
	//바라보는 방향을 기준으로 시계/반시계 방향을 설정하여 앞면 뒷면을 정할것.
	// 큰 빨강 원
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, z);
	for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
	{
		x = 50.0f * cos(angle);
		y = 50.0f * sin(angle);

		glVertex3f(x, y, z);
	}
	glEnd();

	// 작은 파랑 원
	z = 10.0f;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, z);
	for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 8.0f))
	{
		x = 20.0f * cos(angle);
		y = 20.0f * sin(angle);

		glVertex3f(x, y, z);
	}
	glEnd();

	glPopMatrix();
	//glFlush();
	glutSwapBuffers();
	// 깊이에 따라 객체를 화면에 출력하는 모드를 설정
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
		glOrtho(-t, t, -t / wSizeRatio, t / wSizeRatio, -t, t);
	}
	else {
		glOrtho(-t * wSizeRatio, t * wSizeRatio, -t, t, -t, t);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
