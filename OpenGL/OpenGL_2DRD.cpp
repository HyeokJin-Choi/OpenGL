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
	if (h == 0) h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h; // 더 큰 값이 분자에 존재.
	if (w <= h) { // 세로가 더 크면 -> 수평 해상도 기준으로 정사각형 유지, "창이 세로로 길어지면 더 넓은 y범위를 보여줘야 찌그러지지 않음"
		glOrtho(-wSize, wSize, -wSize/aspectRatio, wSize/aspectRatio, 1, -1);
	}
	else { // 가로가 더 크면 -> 수직 해상도 기준으로 정사각형 유지, "창이 가로로 길어지면 더 넓은 x범위를 보여줘야 찌그러지지 않음"
		glOrtho(-wSize*aspectRatio, wSize*aspectRatio, -wSize, wSize, 1, -1);
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
