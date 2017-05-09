#include <Windows.h>
#include <stdio.h>
#include<GL\glut.h>

float fTranslate;
float fRotate;
float fScale     = 1.0f;
float color_b = 1.0f;

bool bPersp = false;
bool bAnim = false;
bool bWire = false;
bool isWhite = true;

int wHeight = 0;
int wWidth = 0;

GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 }; // 定义颜色

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

GLfloat spotangle = 5.0f; //角度

//环境光位置
GLfloat light_x = 0.0f;
GLfloat light_y = 0.0f;
GLfloat light_z = 0.0f;



void Draw_Triangle() // This function draws a triangle with RGB colors
{

    GLfloat mat_specular[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat mat_diffuse0[] = { 0.85f, 0.65f, 0.2f, 1.0f };

    //画茶壶
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);// 设置多边形正面的镜面反射属性
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);// 指定镜面指数
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse0); //设置多边形正面漫反射属性
    glRotatef(90, 1, 0, 0);
    glutSolidTeapot(1);
    glPopMatrix();


}


void updateView(int width, int height)
{
    glViewport(0,0,width,height);//设置视窗大小

    glMatrixMode(GL_PROJECTION);//设置矩阵模式为投影
    glLoadIdentity();   //初始化矩阵为单位矩阵

    float whRatio = (GLfloat)width/(GLfloat)height;  //设置显示比例
    if (bPersp) {
        gluPerspective(45.0f, whRatio,0.1f,100.0f); //透视投影
        //glFrustum(-3, 3, -3, 3, 3,100);
    } else {
        glOrtho(-3 ,3, -3, 3,-100,100);  //正投影
    }

    glMatrixMode(GL_MODELVIEW);  //设置矩阵模式为模型
}

void reshape4(int width, int height)
{
    if (height==0)      //如果高度为0
    {
        height=1;   //让高度为1（避免出现分母为0的现象）
    }

    wHeight = height;
    wWidth = width;

    updateView(wHeight, wWidth); //更新视角
}

void idle()
{
    glutPostRedisplay(); //调用当前绘制函数
}

void key(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 27:
    case 'q': {exit(0); break; }
    case 'p': {bPersp = !bPersp; break; }

    case ' ': {bAnim = !bAnim; break; }
    case 'o': {bWire = !bWire; break; }

    case 'j': {//环境光左移
        light_x = light_x - 0.2f;
        break;
    }
    case 'l': {//环境光右移
        light_x = light_x + 0.2f;
        break;
    }
    case 'i': {//环境光上移
        light_y = light_y + 0.2f;
        break;
    }
    case 'k': {//环境光下移
        light_y = light_y - 0.2f;
        break;
    }
    case 'n': {//环境光前移
        light_z = light_z + 0.2f;
        break;
    }
    case 'm': {//环境光后移
        light_z = light_z - 0.2f;
        break;
    }
    case 'r': {//环境光颜色切换
        isWhite = !isWhite;
        break;
    }
    }

    updateView(wHeight, wWidth);
}


void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除颜色缓存和深度缓存
    glLoadIdentity(); //初始化矩阵为单位矩阵

    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        0, 1, 0);               // 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //设置多边形绘制模式：正反面，线型
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //设置多边形绘制模式：正反面，填充
    }

    glEnable(GL_DEPTH_TEST);//开启深度测试
    glEnable(GL_LIGHTING);  //开启光照模式

    //GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_pos[] = {5.0 + light_x ,5.0 + light_y,5.0 + light_z,1}; //定义环境光位置
    GLfloat white[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //定义白色

    if (isWhite) {
        color[0] = 1.0f, color[1] = 1.0f, color[2] = 1.0f, color[3] = 1.0f;
    }
    else {
        color[0] = 0.0f, color[1] = 1.0f, color[2] = 0.0f, color[3] = 1.0f;
    }

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos); //设置第0号光源的光照位置
    glLightfv(GL_LIGHT0, GL_SPECULAR, white); //设置镜面反射光照颜色
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);                     //设置漫射光成分
    glLightfv(GL_LIGHT0, GL_AMBIENT, color);   //设置第0号光源多次反射后的光照颜色（环境光颜色）

    glEnable(GL_LIGHT0); //开启第0号光源



    glRotatef(fRotate, 0, 1.0f, 0); //旋转
    glRotatef(-90, 1, 0, 0); //旋转
    Draw_Triangle();    //绘制场景

    if (bAnim) fRotate    += 0.5f; //旋转因子改变


    glutSwapBuffers(); //交换缓冲区
}

void runwork4 (int argc,  char *argv[])
{
    glutInit(&argc, argv);//对glut的初始化
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480,480);//设置窗口大小
    int windowHandle = glutCreateWindow("Simple GLUT App");//设置窗口标题
    glutDisplayFunc(redraw); //注册绘制回调函数
    glutReshapeFunc(reshape4);   //注册重绘回调函数
    glutKeyboardFunc(key); //注册按键回调函数
    glutIdleFunc(idle);//注册全局回调函数：空闲时调用
    glutMainLoop();  // glut事件处理循环
}
