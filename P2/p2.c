#include<stdio.h>
#include<GL/glut.h>

int choice;
float h=0.0,k=0.0,theta;
void myInit();
void rotate_origin();
void rotate_fixed_point();
void draw_triangle();
void display_about_origin();
void display_about_fixed_point();

void rotate_origin(){
	glRotatef(theta,0,0,1);
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);	
	glMatrixMode(GL_PROJECTION);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluOrtho2D(-500.0,500.0,-500.0,500.0);
	glMatrixMode(GL_MODELVIEW);
}
void draw_triangle()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2f(100,100);
	glVertex2f(400,100);
	glVertex2f(250,350);
	glEnd();
}

void display_about_origin()
{
	draw_triangle();
	rotate_origin();
	draw_triangle();
	glLoadIdentity();	
	glFlush();
}
void rotate_fixed_point()
{
	glTranslatef(h,k,0);
	glRotatef(theta,0,0,1);	
	glTranslatef(-h,-k,1);
}

void display_about_fixed_point()
{
	draw_triangle();
	rotate_fixed_point();
	draw_triangle();
	glLoadIdentity();
	glFlush();
}
	
void main(int argc,char *argv[])
{
	printf("Enter your choice\n1.Rotation about origin\n2.Rotation about fixed point\n");
	scanf("%d",&choice);
	printf("Enter rotation angle:");
	scanf("%f",&theta);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	if(choice==1)
	{
		glutCreateWindow("Rotation of a triangle with respect to origin|4MT19CS141");
		glutDisplayFunc(display_about_origin);
	}
	else if(choice==2)
	{
		printf("Enter the pivot (x,y) point\n");
		scanf("%f%f",&h,&k);
		glutCreateWindow("Rotation of a triangle wrt fixed point|4MT19CS141");
		glutDisplayFunc(display_about_fixed_point);
	}
	else
	{
		printf("Invalid choice");
	}
	myinit();
	glutMainLoop();
}




