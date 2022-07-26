#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416
GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = 0.0, xwcMax = 130.0;
GLfloat ywcMin = 0.0, ywcMax = 130.0;
int flag;
struct wcPt3D
{
GLfloat x, y, z;
};
void bino(GLint n, GLint *C)
{
GLint k, j;
for(k=0;k<=n;k++)
{
C[k]=1;
for(j=n;j>=k+1;j--)
C[k]*=j;
for(j=n-k;j>=2;j--)
C[k]/=j;
}
}

void computeBezPt(GLfloat u,struct wcPt3D *bezPt, GLint nCtrlPts, struct wcPt3D *ctrlPts, GLint *C)
{

GLint k, n=nCtrlPts-1;
GLfloat bezBlendFcn;
bezPt ->x =bezPt ->y = bezPt->z=0.0;
for(k=0;k<nCtrlPts;k++)
{
bezBlendFcn = C[k] * pow(u, k) * pow( 1-u, n-k);
bezPt ->x += ctrlPts[k].x * bezBlendFcn;
bezPt ->y += ctrlPts[k].y * bezBlendFcn;
bezPt ->z += ctrlPts[k].z * bezBlendFcn;
}
}
void bezier(struct wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
struct wcPt3D bezCurvePt;
GLfloat u;
GLint C[nCtrlPts], k;
bino(nCtrlPts-1, C);
glBegin(GL_LINE_STRIP);
for(k=0;k<=nBezCurvePts;k++)
{
u=GLfloat(k)/GLfloat(nBezCurvePts);
computeBezPt(u,&bezCurvePt, nCtrlPts, ctrlPts, C);
glVertex2f(bezCurvePt.x,bezCurvePt.y);
}
glEnd();

}
void displayFcn()
{
GLint nCtrlPts = 4, nBezCurvePts =20;
static float theta = 0;
struct wcPt3D ctrlPts[4] = {{20, 100, 0},{30, 110, 0},{50, 90, 0},{60, 100, 0}};
if(flag ==0){
	glClear(GL_COLOR_BUFFER_BIT);
	}
	else{
ctrlPts[1].x +=10*sin(theta * PI/180.0);
ctrlPts[1].y +=5*sin(theta * PI/180.0);
ctrlPts[2].x -= 10*sin((theta+30) * PI/180.0);
ctrlPts[2].y -= 10*sin((theta+30) * PI/180.0);
ctrlPts[3].x-= 4*sin((theta) * PI/180.0);
ctrlPts[3].y += sin((theta-30) * PI/180.0);
theta+=0.5;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 1.0, 1.0);
glPointSize(5);
glPushMatrix();
glLineWidth(5);
glColor3f(255/255, 153/255.0, 51/255.0); 
for(int i=0;i<8;i++)
{
glTranslatef(0,-0.8, 0);
bezier(ctrlPts, nCtrlPts, nBezCurvePts);
}
glColor3f(1, 1, 1); 
for(int i=0;i<8;i++)
{

glTranslatef(0, -0.8, 0);
bezier(ctrlPts,nCtrlPts, nBezCurvePts);
}
glColor3f(19/255.0, 136/255.0, 8/255.0); 
for(int i=0;i<8;i++)
{
glTranslatef(0,-0.8, 0);
bezier(ctrlPts, nCtrlPts, nBezCurvePts);
}
glPopMatrix();
glColor3f(0.7, 0.5,0.3);
glLineWidth(5);
glBegin(GL_LINES);
glVertex2f(20,100);
glVertex2f(20,40);
glEnd();
glFlush();
}
glutPostRedisplay();
glutSwapBuffers();
}
void disp(){
	//glClearColor(1.0,1.0,1.0,1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.0,0.0,0.0);
	displayFcn();
}
void winReshapeFun(GLint newWidth, GLint newHeight)
{
glViewport(0, 0, newWidth, newHeight);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
}

void menu(int c){
	switch(c){
		case 1:glutDisplayFunc(displayFcn);
			flag=1;
			displayFcn();
			break;
		case 2:exit(0);
	}
}
int main(int argc, char **argv)
{
glutInit(& argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowPosition(50, 50);
glutInitWindowSize(winWidth, winHeight);
glutCreateWindow("Bezier Curve | 4MT19CS140");
glutDisplayFunc(disp);
glutReshapeFunc(winReshapeFun);
glutCreateMenu(menu);
	glutAddMenuEntry("Draw flag",1);
	glutAddMenuEntry("exit",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
glutMainLoop();
return 0;
}
