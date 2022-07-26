#include<stdio.h>
#include<GL/glut.h>
float theta[3] = {0.0,0.0,0.0};
int axis =0;
float vertices[8][3]=
{
    {
        -1.0,-1.0,-1.0
    },
    {
        1.0,-1.0,-1.0
    },
    {
        1.0,1.0,-1.0
    },
    {
        -1.0,1.0,-1.0
    },
    {
        -1.0,-1.0,1.0
    },
    {
        1.0,-1.0,1.0
    },
    {
        1.0,1.0,1.0
    },
    {
        -1.0,1.0,1.0
    }
};
float colors[8][3]={
    {
        0.0,0.0,0.0
    },
    {
        1.0,0.0,0.0
    },
    {
        1.0,1.0,0.0
    },
    {
        0.0,1.0,0.0
    },
    {
        0.0,0.0,1.0
    },
    {
        1.0,0.0,1.0
    },
    {
        1.0,1.0,1.0
    },
    {
        0.0,1.0,1.0
    }
};
void Polygon(int a, int b, int c ,int d){
    glBegin(GL_POLYGON);
    glColor3fv(colors[a]);
    glVertex3fv(vertices[a]);

    glColor3fv(colors[b]);
    glVertex3fv(vertices[b]);

    glColor3fv(colors[c]);
    glVertex3fv(vertices[c]);

    glColor3fv(colors[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}
void colorcube(void){
        Polygon(0,3,2,1);
        Polygon(2,3,7,6);
        Polygon(0,4,7,3);
        Polygon(1,2,6,5);
        Polygon(4,5,6,7);
        Polygon(0,1,5,4);
}
void display(){
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(theta[0],1.0,0.0,0.0);
        glRotatef(theta[1],0.0,1.0,0.0);
        glRotatef(theta[2],0.0,0.0,1.0);
        colorcube();
        glFlush();
        glutSwapBuffers();

}
void spincube(){
    theta[axis]+=1;
    if(theta[axis]>360.0)
        theta[axis]=0;
    glutPostRedisplay();
}
void mouse(int btn , int state , int x ,int y){
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            axis=0;
    if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis=1;
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;
        spincube();
}
void myReshape(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-5.0,5.0,-5.0*(float)h/(float)w, 5.0*(float)h/(float)w,-10.0,10.0);
    else
        glOrtho(-5.0*(float)w/(float)h,5.0*(float)w/(float)h,-5.0,5.0,-10.0,10.0);
        glMatrixMode(GL_MODELVIEW);
        glutPostRedisplay();
}
int main(int argc,char *argv[]){
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(0,0);
        glutCreateWindow("cube spin");
        glutReshapeFunc(myReshape);
        glutDisplayFunc(spincube);
        glutMouseFunc(mouse);
        glEnable(GL_DEPTH_TEST);
        glutMainLoop();
        return 0;
}
