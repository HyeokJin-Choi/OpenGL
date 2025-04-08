#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.1415f

void glPointSize(GLfloat s);

//void RenderScene(void) {
//	GLfloat x, y, z, angle;
//	GLfloat pointSize = 1.0f;
//	GLfloat sizes[2];
//	GLfloat step;
//	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
//	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
//
//	glClear(GL_COLOR_BUFFER_BIT);
//	glPushMatrix();
//	glRotatef(45, 1.0f, 0.0f, 0.0f);
//	glRotatef(45, 0.0f, 1.0f, 0.0f);
//
//	glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
//
//	glBegin(GL_POINTS);
//	z = -50.0f;
//	for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f) {
//		x = 50.0f * cos(angle);
//		y = 50.0f * sin(angle);
//		glVertex3f(x, y, z);
//		z += 0.5f;
//		glPointSize(pointSize);
//		pointSize += 0.1f;
//	}
//	glEnd();
//	glPopMatrix();
//
//	glFlush();
//}

//void RenderScene(void) {
//    GLfloat x, y, z, angle;
//    GLfloat pointSize;
//    GLfloat sizes[2];
//    GLfloat step;
//    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
//    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
//
//    pointSize = sizes[0];
//
//    glClear(GL_COLOR_BUFFER_BIT);
//    glPushMatrix();
//    glRotatef(45, 1.0f, 0.0f, 0.0f);
//    glRotatef(45, 0.0f, 1.0f, 0.0f);
//
//    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
//
//    z = -50.0f;
//    for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f) {
//        x = 50.0f * cos(angle);
//        y = 50.0f * sin(angle);
//
//        glPointSize(pointSize);
//
//        glBegin(GL_POINTS);
//        glVertex3f(x, y, z);
//        glEnd();
//
//        z += 0.5f;
//
//        pointSize += step;
//        if (pointSize > sizes[1]) {
//            pointSize = sizes[1];
//        }
//    }
//
//    glPopMatrix();
//    glFlush();
//}

float getRandomFloat() {
    return (float)rand() / (float)RAND_MAX;
}

    void RenderScene(void) {
        GLfloat x, y, z, angle;
        GLfloat pointSize;
        GLfloat sizes[2];
        GLfloat step;
        glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
        glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

        pointSize = sizes[0];

        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glRotatef(45, 1.0f, 0.0f, 0.0f);
        glRotatef(45, 0.0f, 1.0f, 0.0f);

        GLfloat R=0.0f, G=0.0f, B=0.0f;

        z = -50.0f;

        float squareSize = 5.0f;      // 정사각형 한 변 길이
        float spacing = 0.5f;         // 점 간격
        float halfSize = squareSize / 2.0f;

        

        for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f) {
            x = 50.0f * cos(angle);
            y = 50.0f * sin(angle);
            R = getRandomFloat();
            G = getRandomFloat();
            B = getRandomFloat();

            glColor3f(R, G, B);
            glPointSize(pointSize); // 점 크기
            glBegin(GL_POINTS);

            // 상단, 하단
            for (float dx = -halfSize; dx <= halfSize; dx += spacing) {
                glVertex3f(x + dx, y + halfSize, z);  // 상단 변
                glVertex3f(x + dx, y - halfSize, z);  // 하단 변
            }

            // 좌측, 우측
            for (float dy = -halfSize; dy <= halfSize; dy += spacing) {
                glVertex3f(x - halfSize, y + dy, z);  // 좌측 변
                glVertex3f(x + halfSize, y + dy, z);  // 우측 변
            }

            glEnd();


            z += 0.5f;
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
	GLint t = 100;
	GLfloat aspectRatio;
	if (h == 0) h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h) {
		glOrtho(-t, t, -t/aspectRatio, t/aspectRatio, t, -t);
	}
	else {
		glOrtho(-t*aspectRatio, t*aspectRatio, -t, t, t, -t);
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
