// atom.c - A simple OpenGL animation of a rotating atom
#include <GL/glut.h>
#include <math.h>

static float xRot = 0.0f;
static float yRot = 0.0f;

void RenderScene(void)
{
    //핵 주위의 공전 각도 설정
    static GLfloat fElect1 = 0.0f;
    //창의 내용을 지움
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //모델뷰 행렬 초기화
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -50.0f);
    //적색 원자핵, glColor3ub : 0-255로 스케일링 해서 이용(unsigned char)
    glColor3ub(255, 0, 0);
    glutSolidSphere(20.0f, 15, 15);
    //노란색 전자
    glColor3ub(255, 255, 0);
    //첫 번째 전자의 궤도
    //변환의 내용을 스택에 저장한다 .
    glPushMatrix();
    //공전각 에 따 라 회전시킨다.
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    //원점에서 궤도 거리만큼 이동하는 변환
    glTranslatef(30.0f, 0.0f, 0.0f);
    //전자를 그 린다.
    glutSolidSphere(6.0f, 15, 15);
    //관측 변환의 내 용을 복구 한다 .
    glPopMatrix();
    //두 번째 전자의 궤도
    glPushMatrix();
    glColor3ub(0, 255, 0);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(-50.0f, 0.0f, 0.0f);
    glutSolidSphere(6.0f, 15, 15);
    glPopMatrix();
    //세 번째 전자의 궤도
    glPushMatrix();
    glColor3ub(0, 255, 255);
    glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 50.0f);
    glutSolidSphere(6.0f, 15, 15);
    glPopMatrix();
    //공전각을 증가시 킨다 .
    fElect1 += 10.0f;

    if(fElect1 > 360.0f)
        fElect1 = 0.0f;

    // Display the results
    glutSwapBuffers();
}

void SetupRC()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
}

void TimerFunction(int value)
{
    xRot += 5.0f;
    if (xRot > 360.0f)
        xRot = 0.0f;

    yRot += 4.0f;
    if (yRot > 360.0f)
        yRot = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLdouble nRange = 100.0f;
    GLdouble aspectRatio;

    // O으로 나누지 않도록 함
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 클리핑 영역 설정(left, right, bottom, top, near, far 순서)
    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, -nRange, nRange);
    else
        glOrtho(-nRange * aspectRatio, nRange * aspectRatio, -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);  //GL_MODELVIEW : 모델(그리는 물체)에 대한 각각의 좌표계
    glLoadIdentity();   //좌표계 초기화(원점)
}

void ChangeSize_P(GLsizei w, GLsizei h)
{
    GLfloat fAspect;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0f, fAspect, 1.0f, 500.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0.0f, 0.0f, -0.0f);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Atom");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);

    SetupRC();

    glutMainLoop();
    return 0;
}
