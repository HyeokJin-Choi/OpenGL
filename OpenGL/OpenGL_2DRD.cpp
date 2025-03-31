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
	GLint wSize = 100;
	GLfloat aspectRatio;
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	//glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // 2D 좌표계 설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 400);
	glutCreateWindow("Simple");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	SetupRC();
	glutMainLoop();
}
