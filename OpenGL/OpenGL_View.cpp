#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

void RenderScene(void) {
	std::cout << "RenderScene" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT); // 현재 색상을 사용하여 화면을 지운다.
	//glFlush(); // 강제로 화면에 출력하는 함수, 드로잉 명령을 사용한다.
	// default좌표계 = ModeView = Object좌표계
	glMatrixMode(GL_PROJECTION); // Projection 좌표계로 이동(카메라 좌표계)
	glLoadIdentity(); // 좌표계의 전환이 여러번 동시에 이루어 지는 것을 분리해서 다시 설정하고 ... -> 변수의 초기화 느낌.

	glViewport(0, 0, 640, 480); 
	glOrtho(0,640,0,480,1,-1); // left, right, bottom, top, near, far
	glMatrixMode(GL_MODELVIEW); // Object 좌표계로 다시 이동
	glLoadIdentity(); // 좌표계 초기화

	glColor3f(1.0f, 0.0f, 0.0f); // R G B
	glRectf(0,240,320,0); // 직사각형의 중심을 기준으로 사분면을 활용. x1,y1은 왼쪽 하단 또는 상단이고 x2,y2은 오른쪽 하단 또는 상단으로 적용.
	glutSwapBuffers(); // 출력시 첫 화면에서 검정창으로 뜨는 오류를 해결하기 위해서 삽입.
}
void SetupRC(void) { // window창의 배경색
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // R, G, B, a(투명도)
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 띄워질 윈도우 창의 설정 (버퍼의 개수 | 색상)
	glutInitWindowSize(640, 480); // 띄워질 윈도우 창의 크기
	glutInitWindowPosition(0, 300); // 화면에서 윈도우 창을 띄울 위치 (x,y)형태
	glutCreateWindow("Simple"); //window창의 title
	SetupRC(); // window창의 배경색을 먼저 띄우고 
	glutDisplayFunc(RenderScene); // 해당 window창의 내부에 직사각형을 그린다.
	glutMainLoop();
}


/* #include <GL/glut.h>
#include <stdio.h>
#include <iostream>

void RenderScene(void) {
	std::cout << "RenderScene" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(320/2, 240/2, 640, 480); // 그림을 그릴 도화지 설정.
	glOrtho(0, 640, 0, 480, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(0, 240, 320, 0); // viewpoint의 원점부터 그림 현재 설정값으로 해당 원점은 (320/2, 240/2)임. 따라서 여기서부터 가로 세로240, 가로320 크기의 직사각형을 그림.
	glutSwapBuffers();
}

void SetupRC(void) { 
	std::cout << "SetupRC" << std::endl;
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(600, 200);
	glutCreateWindow("Simple");
	SetupRC();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
*/
