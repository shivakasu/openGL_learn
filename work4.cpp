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

GLfloat color[] = { 1.0, 1.0, 1.0, 1.0 }; // ������ɫ

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

GLfloat spotangle = 5.0f; //�Ƕ�

//������λ��
GLfloat light_x = 0.0f;
GLfloat light_y = 0.0f;
GLfloat light_z = 0.0f;



void Draw_Triangle() // This function draws a triangle with RGB colors
{

    GLfloat mat_specular[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat mat_diffuse0[] = { 0.85f, 0.65f, 0.2f, 1.0f };

    //�����
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);// ���ö��������ľ��淴������
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);// ָ������ָ��
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse0); //���ö������������������
    glRotatef(90, 1, 0, 0);
    glutSolidTeapot(1);
    glPopMatrix();


}


void updateView(int width, int height)
{
    glViewport(0,0,width,height);//�����Ӵ���С

    glMatrixMode(GL_PROJECTION);//���þ���ģʽΪͶӰ
    glLoadIdentity();   //��ʼ������Ϊ��λ����

    float whRatio = (GLfloat)width/(GLfloat)height;  //������ʾ����
    if (bPersp) {
        gluPerspective(45.0f, whRatio,0.1f,100.0f); //͸��ͶӰ
        //glFrustum(-3, 3, -3, 3, 3,100);
    } else {
        glOrtho(-3 ,3, -3, 3,-100,100);  //��ͶӰ
    }

    glMatrixMode(GL_MODELVIEW);  //���þ���ģʽΪģ��
}

void reshape4(int width, int height)
{
    if (height==0)      //����߶�Ϊ0
    {
        height=1;   //�ø߶�Ϊ1��������ַ�ĸΪ0������
    }

    wHeight = height;
    wWidth = width;

    updateView(wHeight, wWidth); //�����ӽ�
}

void idle()
{
    glutPostRedisplay(); //���õ�ǰ���ƺ���
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

    case 'j': {//����������
        light_x = light_x - 0.2f;
        break;
    }
    case 'l': {//����������
        light_x = light_x + 0.2f;
        break;
    }
    case 'i': {//����������
        light_y = light_y + 0.2f;
        break;
    }
    case 'k': {//����������
        light_y = light_y - 0.2f;
        break;
    }
    case 'n': {//������ǰ��
        light_z = light_z + 0.2f;
        break;
    }
    case 'm': {//���������
        light_z = light_z - 0.2f;
        break;
    }
    case 'r': {//��������ɫ�л�
        isWhite = !isWhite;
        break;
    }
    }

    updateView(wHeight, wWidth);
}


void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //�����ɫ�������Ȼ���
    glLoadIdentity(); //��ʼ������Ϊ��λ����

    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        0, 1, 0);               // ������0��0��0�����ӵ����� (0,5,50)��Y������

    if (bWire) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //���ö���λ���ģʽ�������棬����
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //���ö���λ���ģʽ�������棬���
    }

    glEnable(GL_DEPTH_TEST);//������Ȳ���
    glEnable(GL_LIGHTING);  //��������ģʽ

    //GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_pos[] = {5.0 + light_x ,5.0 + light_y,5.0 + light_z,1}; //���廷����λ��
    GLfloat white[] = { 1.0f, 0.0f, 0.0f, 1.0f }; //�����ɫ

    if (isWhite) {
        color[0] = 1.0f, color[1] = 1.0f, color[2] = 1.0f, color[3] = 1.0f;
    }
    else {
        color[0] = 0.0f, color[1] = 1.0f, color[2] = 0.0f, color[3] = 1.0f;
    }

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos); //���õ�0�Ź�Դ�Ĺ���λ��
    glLightfv(GL_LIGHT0, GL_SPECULAR, white); //���þ��淴�������ɫ
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);                     //���������ɷ�
    glLightfv(GL_LIGHT0, GL_AMBIENT, color);   //���õ�0�Ź�Դ��η����Ĺ�����ɫ����������ɫ��

    glEnable(GL_LIGHT0); //������0�Ź�Դ



    glRotatef(fRotate, 0, 1.0f, 0); //��ת
    glRotatef(-90, 1, 0, 0); //��ת
    Draw_Triangle();    //���Ƴ���

    if (bAnim) fRotate    += 0.5f; //��ת���Ӹı�


    glutSwapBuffers(); //����������
}

void runwork4 (int argc,  char *argv[])
{
    glutInit(&argc, argv);//��glut�ĳ�ʼ��
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480,480);//���ô��ڴ�С
    int windowHandle = glutCreateWindow("Simple GLUT App");//���ô��ڱ���
    glutDisplayFunc(redraw); //ע����ƻص�����
    glutReshapeFunc(reshape4);   //ע���ػ�ص�����
    glutKeyboardFunc(key); //ע�ᰴ���ص�����
    glutIdleFunc(idle);//ע��ȫ�ֻص�����������ʱ����
    glutMainLoop();  // glut�¼�����ѭ��
}
