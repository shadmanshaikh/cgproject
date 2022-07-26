#include<stdio.h>
#include<GL/glut.h>
float x1,x2,x3,x4,y11,y2,y3,y4;
int le[500],re[500];
void edgedetect(float x1, float y1, float x2, float y2 );
void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void display();
void myinit();
void fill_menu();
void edgedetect(float x1 , float y1, float x2, float y2){
        int i;
        float mx, x , temp;
        if((y2-y1)<0){
                temp=y1;y1=y2;y2=temp;
                temp=x1;x1=x2;x2=temp;
        }
        if((y2-y1)!=0)
            mx=(x2-x1)/(y2-y1);
        else
            mx=x2-x1;
        x=x1;
        for(i=y1;i<=y2;i++){
                if(x<le[i])
                    le[i]=x;
                if(x>re[i])
                    re[i]=x;
                x+=mx;
        }
}
void scanfill(float x1, float y11, float x2, float y2, float x3, float y3, float x4, float y4){
    int i,y;
    for(i=200;i<=400;i++){
            le[i]=500;
            re[i]=0;
    }
    edgedetect(x1,y11,x2,y2);
    edgedetect(x2,y2,x3,y3);
    edgedetect(x4,y4,x3,y3);
    edgedetect(x1,y11,x4,y4);
    for(y=200;y<=400;y++){
    for(i=le[y];i<=re[y];i++){
            glColor3f(1.0,1.0,0.0);
            glBegin(GL_POINTS);
            glVertex2i(i,y);
            glEnd();
            glFlush();
    }
    }
}
void display(){
        x1=200.0;y11=200.0;x2=100.0;y2=300.0;x3=200.0;y3=400.0;x4=300.0;y4=300.0;
        glFlush();
}
void myinit(){
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0,0.0,500.0);
    glMatrixMode(GL_MODELVIEW);
}
void fill_menu(int c)
{

    switch(c){
        case 1: glColor3f(0.0,0.0,1.0);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x1,y11);
                glVertex2f(x2,y2);
                glVertex2f(x3,y3);
                glVertex2f(x4,y4);
                glEnd();
                glFlush();
                break;
        case 2: glColor3f(0.0,0.0,1.0);
                glVertex2f(x1,y11);
                glVertex2f(x2,y2);
                glVertex2f(x3,y3);
                glVertex2f(x4,y4);
                glEnd();
                scanfill(x1,y11,x2,y2,x3,y3,x4,y4);
                glFlush();
                break;
    }
}
void main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("filling a polygon using scan-line algorithm");
    glutDisplayFunc(display);
    myinit();
    glutCreateMenu(fill_menu);
    glutAddMenuEntry("Draw Polygon",1);
    glutAddMenuEntry("fill Polygon",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}



