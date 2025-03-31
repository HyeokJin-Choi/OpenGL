#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

void RenderScene(void) {
	std::cout << "RenderScene" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(-25.0f, 25.0f, 25.0f, -25.0f);
	glFlush();
}

void SetupRC(void) { 
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;

	GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w >= h) { // 가로가 더 넓으면 -> 수직 해상도 기준으로 정사각형 유지
		gluOrtho2D(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0); // left/aspectRatio, right/aspectRatio, bottom, top, -> x좌표계를 늘려준다.
	}
	else { // 세로가 더 크면 -> 수평 해상도 기준으로 정사각형 유지
		gluOrtho2D(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio); // left, right, bottom/aspectRatio, top/aspectRatio, -> y좌표계를 늘려준다.
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("Simple");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	SetupRC();
	glutMainLoop();
}
