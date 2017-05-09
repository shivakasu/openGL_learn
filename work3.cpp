/*
*
*  彩色旋转立方体
*  1. 定义六个面，同时定义每个顶点的颜色（与顶点坐标相对应）
*  2. 启用 GL_SMOOTH 方式渲染
*
*
*/
#include <Windows.h>
#include <stdio.h>
#include<GL\glut.h>

static float xrot = 0.0;
static float yrot = 0.0;
static float zrot = 0.0;


void cube()
{
    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,0.0);
        glVertex3f( 1.0, 1.0,-1.0);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(-1.0, 1.0,-1.0);
        glColor3f(0.0,1.0,1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glColor3f(1.0,1.0,1.0);
        glVertex3f( 1.0, 1.0, 1.0);

        glColor3f(1.0,0.0,1.0);
        glVertex3f( 1.0,-1.0, 1.0);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(-1.0,-1.0, 1.0);
        glColor3f(0.0,0.0,0.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glColor3f(1.0,0.0,0.0);
        glVertex3f( 1.0,-1.0,-1.0);

        glColor3f(1.0,1.0,1.0);
        glVertex3f( 1.0, 1.0, 1.0);
        glColor3f(0.0,1.0,1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(-1.0,-1.0, 1.0);
        glColor3f(1.0,0.0,1.0);
        glVertex3f( 1.0,-1.0, 1.0);

        glColor3f(1.0,0.0,0.0);
        glVertex3f( 1.0,-1.0,-1.0);
        glColor3f(0.0,0.0,0.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(-1.0, 1.0,-1.0);
        glColor3f(1.0,1.0,0.0);
        glVertex3f( 1.0, 1.0,-1.0);

        glColor3f(0.0,1.0,1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(-1.0, 1.0,-1.0);
        glColor3f(0.0,0.0,0.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(-1.0,-1.0, 1.0);

        glColor3f(1.0,1.0,0.0);
        glVertex3f( 1.0, 1.0,-1.0);
        glColor3f(1.0,1.0,1.0);
        glVertex3f( 1.0, 1.0, 1.0);
        glColor3f(1.0,0.0,1.0);
        glVertex3f( 1.0,-1.0, 1.0);
        glColor3f(1.0,0.0,0.0);
        glVertex3f( 1.0,-1.0,-1.0);
    glEnd();
}

void display(void)
{
    Sleep(10);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -5);
    glRotatef(xrot, 1, 0, 0);
    glRotatef(yrot, 0, 1, 0);
    glRotatef(zrot, 0, 0, 1);
    cube();
    xrot = xrot + 1;
    yrot = yrot + 2;
    zrot = zrot + 3;

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if(h==0) h = 1;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void init(int width, int height )
{
    if(height == 0) height = 1;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int w, int h)
{
    if(key == 'f') // 进入全屏
        glutFullScreen();
    if(key == 'F') // 退出全屏
    {
        glutReshapeWindow(640, 480); // 设置窗口大小（不能用初始化的函数）
        glutPositionWindow(400, 100); // 设置窗口位置（不能用初始化的函数）
    }
    if(key == 27) // ESC退出程序
        exit(0);
}

void runwork3(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(400, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("");

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    init(640, 480);
    glutMainLoop();
}
