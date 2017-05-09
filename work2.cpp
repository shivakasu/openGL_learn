#include <stdio.h>
#include <Windows.h>
#include <gl/glut.h>
#include <math.h>

//输出模式，0-单缓存模式；非0双缓存模式
#define OUTPUT_MODE 1

//角度
int angle = 0;
int dec = 1,olddec=1;
void display2(void)
{
    if(dec!=olddec){
        angle = 360-angle;
        olddec=dec;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(angle, 0,0,dec);

    float Pos[2]={200.0,200.0};
    double PI=acos(-1.0);
    float Length=100.0;
    float Short=Length*sin(0.1*PI)/sin(0.7*PI);
    float out[5][2],inner[5][2];
    int i;
    glColor3f(0.0,0.0,0.0);
    for(int i=0;i<10;i++){
        if(i%2==0){
            inner[i/2][0]=Short*cos((i+1)*0.2*PI+56/180.0)+Pos[0];
            inner[i/2][1]=Short*sin((i+1)*0.2*PI+56/180.0)+Pos[1];

        }
        else{
            out[i/2][0]=Length*cos((i+1)*0.2*PI+56/180.0)+Pos[0];
            out[i/2][1]=Length*sin((i+1)*0.2*PI+56/180.0)+Pos[1];
        }
    }
    float d0=out[0][0],d1=out[0][1];
    for(i=0;i<5;i++){
        out[i][0]-=d0;
        out[i][1]-=d1;
        out[i][0]/=200;
        out[i][1]/=200;
        inner[i][0]-=d0;
        inner[i][1]-=d1;
        inner[i][0]/=200;
        inner[i][1]/=200;
    }
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for(i=0;i<5;i++)
        glVertex2fv(out[i]);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2fv(out[0]);
    glVertex2fv(out[3]);
    glVertex2fv(out[3]);
    glVertex2fv(out[1]);
    glVertex2fv(out[1]);
    glVertex2fv(out[4]);
    glVertex2fv(out[4]);
    glVertex2fv(out[2]);
    glVertex2fv(out[2]);
    glVertex2fv(out[0]);
    glEnd();
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    for(i=0;i<5;i++)
        glVertex2fv(inner[i]);
    glEnd();


    angle += 1;
    angle %= 360;
    if (OUTPUT_MODE == 0) {
        glFlush();//单缓存GLUT_SINGLE时使用
    } else {
        glutSwapBuffers();//因为使用的是双缓存GLUT_DOUBLE，所以这里必须要交换缓存才会显示
    }
    Sleep(10);
}

void keyboard2(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
    case 'X':
        dec=1;
        break;
    case 'z':
    case 'Z':
        dec=-1;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void reshape2(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void runwork2(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | (OUTPUT_MODE == 0 ? GLUT_SINGLE : GLUT_DOUBLE));
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);

    glutCreateWindow("五角星旋转");
    glutDisplayFunc(&display2);
    glutIdleFunc(display2);  //设置不断调用显示函数
    glutReshapeFunc(reshape2);
    glutKeyboardFunc(&keyboard2);
    glClearColor(1.0, 1.0, 1.0,1.0);
    glutMainLoop();
}
