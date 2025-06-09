#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.1415f 

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

void RenderScene() {
    GLint factor = 1;
    GLushort pattern = 0x00FF;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // 모델뷰 행렬 초기화


    glTranslatef(0.0f, 0.0f, -30.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glTranslatef(xTran, yTran, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 30.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 30.0f);
    glEnd();


    glEnable(GL_LINE_STIPPLE);
    glLineStipple(factor, pattern);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutWireCube(10.0f);
    glDisable(GL_LINE_STIPPLE);

    glPushMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutWireCube(10.0f);
    glPopMatrix();

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h) {
    std::cout << "w= " << w << " h= " << h << std::endl;
    std::cout << "Changesize" << std::endl;

    GLint wSize = 50;
    if (h == 0) h = 1;

    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, 100, -100);
    }
    else {
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, 100, -100);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // 모델뷰 행렬 초기화 (여기선 초기 세팅)
}

void SetupRC(void) {
    std::cout << "SetupRC" << std::endl;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel(GL_FLAT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple");

    SetupRC();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
}

