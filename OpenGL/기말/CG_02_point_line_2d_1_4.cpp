#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.141592f

void glLineWidth(GLfloat ls);
void glPointSize(GLfloat s);


void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    bool bCull = true;
    if (bCull) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);

    GLfloat t = 10.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(t, t, 0);
    glVertex3f(t, 0, 0);
    glVertex3f(0, t, 0);
    glVertex3f(t, 2.0f*t, 0);
    glVertex3f(2.0f * t, t, 0);
    
    glEnd();

    glFlush();
}

void SetupRC(void){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);

}

void ChangeSize(GLsizei w, GLsizei h) {
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h; //순서는 상관없음
    GLfloat wSize = 50.0f;
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, wSize, -wSize);
    }
    else {
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, wSize, -wSize);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    glutCreateWindow("Checkjin's RenderScene");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();
    glutMainLoop();
}
