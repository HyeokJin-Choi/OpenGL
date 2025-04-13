#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.1415f

void glPointSize(GLfloat s);

float getRandomFloat() { 
    return ;
}

void RenderScene() {
	
}

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
}

void changeSize(GLsizei w, GLsizei h) {
	
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	// glutInitDisplayMode( | GLUT_RGB);
	// glutInitWindowSize(, );
	// glutInitWindowPosition(, );
	// glutCreateWindow();

	SetupRC();
	//glutDisplayFunc();
	//glutReshapeFunc();
	glutMainLoop();
}
