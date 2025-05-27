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
	else if(key == GLUT_KEY_RIGHT)
		yRot += 2.0f;
	glutPostRedisplay();
}

void RenderScene() {
	float x, y;
	float centerX = 0.0f, centerY = 0.0f;
	float radius = 50.0f;
	int count = 0;
	bool flag = false;
	bool bCull = true;

	glClear(GL_COLOR_BUFFER_BIT);

	if (bCull) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glTranslated(xTran, 0.0f, 0.0f);
	glTranslated(0.0f, yTran, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(centerX, centerY, 0.0f);  // 중심점
	// 시계방향으로 그리면 후면, 반시계방향으로 그리면 전면
	for (float angle = 0.0f; angle <= 2.0f * GL_PI + 0.1f; angle += (GL_PI / 8.0f)) {
		x = radius * sin(angle); // x를 sin으로 설정하면 시계방향으로 그리기 때문에 후면으로 판단 
		y = radius * cos(angle);
		if (flag) {
			glColor3f(1.0f, 0.0f, 0.0f);
			flag = false;
		}
		else {
			glColor3f(0.0f, 1.0f, 0.0f);
			flag = true;
		}
		glVertex3f(x, y, 0.0f);
		count++;
	}
	glVertex3f(centerX, centerY, 0.0f);  // 중심점
	for (float angle = 0.0f; angle <= 2.0f * GL_PI + 0.1f; angle += (GL_PI / 8.0f)) {
		x = radius * cos(angle); // x를 sin으로 설정하면 시계방향으로 그리기 때문에 후면으로 판단 
		y = radius * sin(angle);
		if (flag) {
			glColor3f(1.0f, 1.0f, 1.0f);
			flag = false;
		}
		else {
			glColor3f(1.0f, 1.0f, 1.0f);
			flag = true;
		}
		glVertex3f(x, y, 0.0f);
		count++;
	}
	glEnd();

	glPopMatrix();
	glFlush();
}


void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_FLAT); // 한번만 실행되면 되는 거라서, SetUpRC함수에 넣음.
	//glShadeModel(GL_SMOOTH);
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
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(changeSize);
	glutMainLoop();
}
