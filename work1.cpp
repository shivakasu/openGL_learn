    #include <Windows.h>
    #include <math.h>
    #include <gl/glut.h>


    const double PI=acos(-1.0);
    //Pos[2]=���������,Length=����ǳߴ�
    void DrawFivestar1(GLfloat Pos[2],GLfloat Length){
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
    }

    void display1(){
        glClear(GL_COLOR_BUFFER_BIT);
        float pCenter[]={200.0,200.0};
        DrawFivestar1(pCenter,100.0);
        glFlush();
    }

    void myinit(){
        glClearColor(1.0, 1.0, 1.0,1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 400.0, 0.0, 400.0);
        glMatrixMode(GL_MODELVIEW);
    }

    void runwork1(int argc, char** argv){
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // ����Ĭ����ʾģʽ���ɺ���
        glutInitWindowSize(500, 500);                   // ��СΪ500��500���صĻ�ͼ����
        glutInitWindowPosition(0, 0);                   // �ѻ�ͼ���ڵ����ϽǷ�����Ļ���Ͻ�
        glutCreateWindow("�����");          // ������ͼ���ڣ�����Ϊ��ͼ���ڵı���
        glutDisplayFunc(display1);                       // ע����ʾ�ص�����
        myinit();                                       // ��ʼ��һЩ����
        glutMainLoop();                                 // �����¼�ѭ��
    }
