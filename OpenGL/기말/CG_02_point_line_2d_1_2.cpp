#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define GL_PI 3.141592f

void glLineWidth(GLfloat ls);
void glPointSize(GLfloat s);


void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    GLfloat t = 10.0f;

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glVertex3f(t, -t, t);
    glVertex3f(t, t, t);

    glVertex3f(t, t, t);
    glVertex3f(-t, t, t);

    glVertex3f(-t, t, t);
    glVertex3f(-t, -t, t);

    glVertex3f(-t, -t, t);
    glVertex3f(t, -t, t);

    glVertex3f(t, t, t);
    glVertex3f(t, t, -t);

    glVertex3f(t, t, -t);
    glVertex3f(-t, t, -t);

    glVertex3f(-t, t, -t);
    glVertex3f(-t, t, t);

    glVertex3f(-t, t, -t);
    glVertex3f(-t, -t, -t);

    glVertex3f(-t, -t, -t);
    glVertex3f(-t, -t, t);
    glEnd();


    GLfloat factor = 5;
    GLushort pattern = 0x5555;

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(factor, pattern);

    glBegin(GL_LINES);
    glVertex3f(t, -t, -t);
    glVertex3f(t, t, -t);

    glVertex3f(t, -t, -t);
    glVertex3f(-t, -t, -t);

    glVertex3f(t, -t, -t);
    glVertex3f(t, -t, t);
    glEnd();

    glDisable(GL_LINE_STIPPLE);


    glFlush();
}

void SetupRC(void){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
