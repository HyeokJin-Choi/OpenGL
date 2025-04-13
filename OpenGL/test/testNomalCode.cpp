#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.1415f

void glPointSize(GLfloat s);

float getRandomFloat() { //색상의 랜덤 값 설정
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

	// glRotatef(); 
	// glRotatef(); 

	// z = ;
	// float squaresize = ;
	// float spacing = ;
	// float halfsize = ;

	pointSize = sizes[0];
	
	// for (angle = 0.0f; angle <= ; angle += 0.1f) { // angle의 최대값을 설정할 것.
		// x =  * cos(angle); 
		// y =  * sin(angle);

		// r = ;
		// g = ;
		// b = ;

		glColor3f(r, g, b);
		glPointSize(pointSize);
		glBegin(GL_POINTS);
		// for (float dx = -halfsize; dx <= halfsize; dx += spacing) { //왼쪽에서 오른쪽으로 점을 찍음
			// glVertex3f(x + , y + , z); // 윗변
			// glVertex3f(x + , y - , z); // 아랫변
		//}
		//for (float dy = -halfsize; dy <= halfsize; dy += spacing) { //아래쪽에서 위쪽으로 점을 찍음
		//	glVertex3f(x - , y + , z); //좌측변
		//	glVertex3f(x + , y + , z); //우측변
		//}
		glEnd();

		// z += f;
		// pointSize += ;
		if (pointSize > sizes[1]) {
			pointSize = sizes[1];
		}

	}

	glPopMatrix();
	glFlush();
}

void SetupRC(void) {
	std::cout << "SetupRC" << std::endl;
	// glClearColor();
}

void changeSize(GLsizei w, GLsizei h) {
	GLfloat t = 100;
	GLfloat wSizeRatio;
	// glViewport(); 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// wSizeRatio = ;
	//if (w <= h) { 
	//	glOrtho();
	//}
	//else {
	//	glOrtho();
	//}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
