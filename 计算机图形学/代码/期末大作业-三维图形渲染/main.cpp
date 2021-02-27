#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float s=1;
bool is_wl=true;
static GLuint texture;
float theta1,theta2,theta3; //ת���Ƕ�
float alpha=0.8;//͸��ֵ
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};

GLubyte*  readImg(char* filename, int * imagewidth, int * imageheight)
{
    //���ļ�
    int pixellength;
    GLubyte *  pixeldata ;
    FILE* pfile=fopen(filename,"rb");
    if(pfile == 0) exit(0);

    //��ȡͼ���С
    fseek(pfile,0x0012,SEEK_SET);
    fread(imagewidth,sizeof(*imagewidth),1,pfile);
    fread(imageheight,sizeof(*imageheight),1,pfile);

    //�����������ݳ���
    pixellength=(*imagewidth)*3;
    while(pixellength%4 != 0)pixellength++;
    pixellength *= (*imageheight);

    //��ȡ��������
    pixeldata = (GLubyte*)malloc(pixellength);
    if(pixeldata == 0) exit(0);

    fseek(pfile,54,SEEK_SET);
    fread(pixeldata,pixellength,1,pfile);

    fclose(pfile);
    return pixeldata;
}

void LoadTexture(char * filename, GLuint &texture)
{
    GLubyte * data;
    GLint width, height;

    //���ļ�
    data=readImg(filename, &width, &height );
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);//������
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //������ͼ
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //�Զ������������꣬ʹ������ӳ��
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;

    //������1:GL_UNPACK_ALIGNMENT ��ָ��OpenGL��δ����ݻ������н��ͼ������
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    glEnable(GL_TEXTURE_2D);//������ӳ��
    free(data); //�ͷ�����ͼ�����ݣ���������������һ�����ɲ����浽�������У�ʹ����Ϻ�Ӧ��glDeleteTextures�ͷ�������
}
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST);       //������Ȳ���
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };  //������ϵ������ӦRGBA�ĸ�������A�����ڻ�Ͽ�������Ч

    GLfloat mat_specular[] = { 0.8, 0.7, 0.8, 1.0 }; //���淴��ϵ��,��ӦRGBA�ĸ�������A�����ڻ�Ͽ�������Ч
    GLfloat mat_shininess[] = { 50.0 };


    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);//���û�����ϵ�����������ϵ��
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);  //set material ����ⷴ��
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//���ò��Ϸ���ָ��

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ָ����Ϻ���

    glEnable(GL_BLEND);        //���û��״̬
    glEnable(GL_COLOR_MATERIAL);//���ʸ��ٵ�ǰ��ͼɫ
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //������������
    LoadTexture("C:\\Users\\HP\\Desktop\\MyProject\\Graph\\TeaPot\\ͭ��.bmp",texture);
}
void drawBoard()
{
    glColor4f(0.5,0.5,0.5,alpha);

    glBegin(GL_QUADS);
    glVertex3f(-0.5,-0.5,1);
    glVertex3f(-0.5,0.5,1);
    glVertex3f(0.5,0.5,1);
    glVertex3f(0.5,-0.5,1);
    glEnd();
}
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//���һ������Ϊ0����ʾ��Դ������Զ��

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);//��Դλ��

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);  //ʹ��ģ����ͼ����ջ�������ļ��α任
    glPushMatrix();              //������������ϵ���۲�����ϵ�ı任����

    glTranslatef(-0.8,0,0);
    glPushMatrix();

    glColor4f (1,1,1,1); //���ù�Դ�󣬲���ʹ����ɫ������������ɫ
    glBindTexture(GL_TEXTURE_2D, texture);
    glRotatef(theta1,1.0f,0.0f,0.0f);
    glRotatef(theta2,0.0f,1.0f,0.0f);
    glRotatef(theta3,0.0f,0.0f,1.0f);
    if(is_wl)
        glEnable(GL_TEXTURE_2D);//������
    else
    {
        glDisable(GL_TEXTURE_2D);//�ر�����
        glColor3f(1,0,0);//���ú�ɫ
    }
    glutSolidTeapot(1*s);
    glPopMatrix();


    glPushMatrix();
    glDisable(GL_DEPTH_TEST); // �ر���Ȳ���
    glDisable(GL_TEXTURE_2D);//�ر�����
    glTranslatef(1,0,2);

    drawBoard();//����͸������

    glEnable(GL_TEXTURE_2D);//������
    glEnable(GL_DEPTH_TEST);//����Ȳ���
    glPopMatrix();

    glPopMatrix();                //�ָ���������ϵ���۲�����ϵ�ı任����
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);  //ʹ������С�����봰�ڵ���ʾ�����Сһ��
    glMatrixMode(GL_MODELVIEW);                    //ʹ��ģ����ͼ����ջ
    glLoadIdentity();


    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMatrixMode (GL_PROJECTION);                 //ʹ��ͶӰ����ջ��׼���趨ͶӰ����
    glLoadIdentity ();                            //��ʼ��ͶӰ����Ϊ��λ����

    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 0.5, 30.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
    case '+':
        if(alpha<1)
            alpha+=0.05;
        break;
    case '-':
        if(alpha>0)
            alpha-=0.05;
        break;
    case 'q':
    case 'Q':
        theta1+=5.0;
        break;
    case 'w':
    case 'W':
        theta1-=5.0;
        break;
    case 'a':
    case 'A':
        theta2+=5.0;
        break;
    case 's':
    case 'S':
        theta2-=5.0;
        break;
    case 'z':
    case 'Z':
        theta3+=5.0;
        break;
    case 'x':
    case 'X':
        theta3-=5.0;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void myMouse(int button, int state, int x, int y) //���ֿ�������
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        is_wl = !is_wl;//�����ʾ\ȡ������
    }
    if(button== 3 ) //�����ϻ��Ŵ�
    {
        s+= 0.005;
    }
    if(button== 4) //�����»���С
    {
        s-=0.005;
    }
    glutPostRedisplay(); //���µ��û��ƺ���
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}
