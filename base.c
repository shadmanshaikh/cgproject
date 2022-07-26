#include<GL/glut.h>
#include<stdio.h>
void MyInit(){
	glClearColor(0.0,0.0,0.0,0.0); //setting the color to black
	glClear(GL_COLOR_BUFFER_BIT); //clear the buffer (given color to be displayed) GL_COLOR_BUFFER_BITS is a constant 
	glMatrixMode(GL_PROJECTION); //projecting the graphics
	gluOrtho2D(0.0,200.0,0.0,200.0);
	
}
void line(){
	glColor3f(0.5,1.0,0.4);
//	glColor3f(1,1,1); //color
	glLineWidth(4.0);//width
	glBegin(GL_LINES); 
	glVertex2i(60,70); //2i is integer parameters p((x1,y1),(x2,y2)) 
	glVertex2i(120,180);
	
	glColor3f(1,1,1); 
	glBegin(GL_LINES);//color
	glVertex2i(100,90); //2i is integer parameters p((x1,y1),(x2,y2)) 
	glVertex2i(140,170);

	glEnd();
	glFlush();
}
void main(int argc,char *argv[]){
 	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1024,576);
	glutCreateWindow("CG program");
	MyInit();
	glutDisplayFunc(line);
	glutMainLoop();
}

