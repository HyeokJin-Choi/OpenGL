//선은고정 객체만 움직이게---------------------------
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

GLfloat rFlag, gFlag, bFlag;
int flag = 0;
const int NUM_SLICES = 8;   // 고정: 8조각

int  filledSlices = 0;      // 현재까지 칠해질 조각 수 (0~8)
void TimerFunction(int value) {
    // 0~8 → 0~8 → … 반복
    filledSlices = (filledSlices + 1) % (NUM_SLICES + 1);

    glutPostRedisplay();
    glutTimerFunc(1000, TimerFunction, 1);
}

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);                     // 중심

    // 외곽 정점: (filledSlices) + 1 개 ⇒ 삼각형 (filledSlices)개
    for (int i = 0; i <= filledSlices; ++i)
    {
        float angle = (2.0f * GL_PI / NUM_SLICES) * i;
        glVertex3f(50.0f * cosf(angle), 50.0f * sinf(angle), 0.0f);
    }
    glEnd();

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
