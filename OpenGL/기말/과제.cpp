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
GLfloat zTran = 0.0f;

GLfloat xLine = 0.0f;
GLfloat yLine = 0.0f;

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') {
        xLine -= 2.0f;
    }
    else if (key == 'd') {
        xLine += 2.0f;
    }
    else if (key == 'w') {
        yLine += 2.0f;
    }
    else if (key == 'x') {
        yLine -= 2.0f;
    }
    glutPostRedisplay();
}

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

GLfloat xLineRot = 0.0f;
GLfloat yLineRot = 0.0f;

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        xLineRot -= 2.0f;
    else if (key == GLUT_KEY_DOWN)
        xLineRot += 2.0f;
    else if (key == GLUT_KEY_LEFT)
        yLineRot -= 2.0f;
    else if (key == GLUT_KEY_RIGHT)
        yLineRot += 2.0f;
    glutPostRedisplay();
}

GLfloat rFlag, gFlag, bFlag;
int flag = 0;
GLfloat angle;
void TimerFunction(int value) {
    glutPostRedisplay();
    xTran = 50.0f * cos(angle);
    zTran = 50.0f * sin(angle);
    angle += GL_PI / 16.0f;

    glutTimerFunc(100, TimerFunction, 1);
}

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(xLineRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yLineRot, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // x축
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // y축
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 30.0f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // z축
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 30.0f);
    glEnd();
    glPopMatrix();
    glLoadIdentity();

    glTranslatef(0.0f, 10.0f, 0.0f);
    // glutSolidSphere( radius, slices, stacks )임.
    // radius는 원의 크기를 결정하고, slices는 구를 세로 방향으로 분할하는 횟수, stacks는 구를 가로 방향으로 분할하는 횟수.
    glPushMatrix();  // 사각형 전용 변환 행렬 시작
    glTranslatef(xTran, 10.0f, zTran);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidSphere(10, 30, 30); //객체를 돌려가면서 slices와 stacks를 이해할 것

    glLoadIdentity();

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple");

    SetupRC();

    glutTimerFunc(1000, TimerFunction, 1);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
}

