#include <windows.h>
#include <GL/glut.h>

void init(void)
{
        glClearColor(1.0, 1.0, 1.0, 1.0);   // ָ�������ɫ������ɫ��Ϊ��ɫ
        gluOrtho2D(0.0, 400.0, 0.0, 300.0);    //ָ����ά����ϵ�б���ʾ������
}

void display(void)
{
        glClear(GL_COLOR_BUFFER_BIT);   // �����ʾ����
        glColor3f(1.0, 0.0, 0.0);       // ָ��ǰ��ɫ����ǰ������ɫ��Ϊ��ɫ
        glLineWidth(5.0);               //������ϸ
        glBegin(GL_LINES);
        glVertex2i(0, 300);        // ָ������
        glVertex2i(200, 20);
        glEnd();
        glFlush();       // ʹ����������ӳ����Ļ��
}

int main(int argc, char** argv)
{
        glutInit(&argc, argv);                          // ��ʼ GLUT.
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //�趨��ʾģʽ
        glutInitWindowPosition(100, 100);    // �趨����λ��
        glutInitWindowSize(400, 300);       // �趨���ڴ�С
        glutCreateWindow("An Example OpenGL Program");  // ��ǰ��ָ�������������ڣ������崰������
        init();                              // ����һЩ��ʼ������
        glutDisplayFunc(display);        // ָ�����ƵĻص�����
        glutMainLoop();            // ��������ѭ�����ȴ��¼�����
        return 0;
}
