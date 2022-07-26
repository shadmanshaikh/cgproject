#include<stdio.h>
#include<GL/glut.h>
float v[4][3]={{0.0,0.0,1.0},{0.0,1.0,0.0},{-1.0,-0.5,0.0},{1.0,-0.5,0.0}};
float colors[4][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{0.0,0.0,0.0}};
int n;

void triangle(float *va,float *vb,float *vc)
{
glBegin(GL_TRIANGLES);
glVertex3fv(va);
glVertex3fv(vb);
glVertex3fv(vc);
glEnd();
}

void tetra(float *a,float *b,float *c,float *d)
{
glColor3fv(colors[0]);
triangle(a,b,c);
glColor3fv(colors[1]);
triangle(a,c,d);
glColor3fv(colors[2]);
triangle(a,d,b);
glColor3fv(colors[3]);
triangle(b,d,c);
}

void divide_tetra(float *a,float *b,float *c,float *d,int m)
{
float mid[6][3];
int j;
if(m>0)
{
for(j=0;j<3;j++)
mid[0][j]=(a[j]+b[j])/2;
for(j=0;j<3;j++)
mid[1][j]=(a[j]+c[j])/2;
for(j=0;j<3;j++)
mid[2][j]=(a[j]+d[j])/2;
for(j=0;j<3;j++)
mid[3][j]=(b[j]+c[j])/2;
for(j=0;j<3;j++)
mid[4][j]=(c[j]+d[j])/2;
for(j=0;j<3;j++)
mid[5][j]=(b[j]+d[j])/2;
divide_tetra(a, mid[0],mid[1],mid[2],m-1);
divide_tetra(mid[0],b,mid[3],mid[5],m-1);
divide_tetra(mid[1],mid[3],c,mid[4],m-1);
divide_tetra(mid[2],mid[5],mid[4],d,m-1);
}
else
tetra(a,b,c,d);//draw triangle at end of recursion//
}

void display()
{
glClearColor(1.0,1.0,1.0,1.0);
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
divide_tetra(v[0],v[1],v[2],v[3],n);
glFlush();
}

void myReshape(int w,int h)
{
glViewport(0,0,w,h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
if(w<=h)
glOrtho(-2.0,2.0,-2.0*(float)h/(float)w,2.0*(float)h/(float)w,-10.0,10.0);
else
glOrtho(-2.0*(float)w/(float)h,2.0*(float)w/(float)h,-2.0,2.0,-10.0,10.0);
glMatrixMode(GL_MODELVIEW);
glutPostRedisplay();
}

int main(int argc,char *argv[])
{
printf("Enter the no of division\n");
scanf("%d",&n);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(500,500);
glutCreateWindow("3d gasket | 4MT19CS140");
glutReshapeFunc(myReshape);
glutDisplayFunc(display);
glEnable(GL_DEPTH_TEST);
glutMainLoop();
return 0;
}
