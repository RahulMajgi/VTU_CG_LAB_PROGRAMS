#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<stdbool.h>

double xmin = 50, ymin = 50;
double xmax = 100, ymax = 100;
int x0,y0,x1,y1;

// double xvmin, yvmin = 200;
// double xvmax, yvmax = 300;

int right = 8;
int left = 2;
int top = 4;
int bottom = 1;

int compute(double x, double y){
	int code = 0;
	if(y > ymax)
		code |= top;
	else if(y < ymin)
		code |= bottom;
	if(x > xmax)
		code |= right;
	else if(x< xmin)
		code |= left;

	return code;
}


void cohen(int x0, int y0, int x1, int y1){
	int code0, code1,out;
	
	float x,y = 0;
	bool done = false, accept = false;
	code0 = compute(x0,y0);
	code1 = compute(x1,y1);

	do{
		if (code0 & code1)
			done =  true;
		else if(!(code0 | code1)){
			accept = true;
			done = true; 		
		}
		else {
				float m = (float)(y1-y0)/(x1-x0);
				out = code0 ? code0 : code1;
				if (out & bottom){
					x = x0 + (ymin-y0)*(1/m);
					y = ymin;				
				}
				if(out & top){
					x = x0 + (ymax - y0)*(1/m);
					y = ymax;
				}
				if(out & left){
					x =xmin;
					y = y0 + (xmin - x0)*m;
				}
				if(out & right){
					x = xmax;
					y = y0 + (xmax-x0)*m;				
				}
				if(out == code0){
					x0 = x;
					y0 = y;
					code0 =compute(x0,y0);				
				}
				if(out == code1){
					x1 = x;
					y1 = y;
					code1 = compute(x1, y1);				
				}
		}		

	}while(!done);
	if(accept){
		glTranslatef(100,100,0);
		glColor3f(0,1,0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(xmin, ymin);
			glVertex2f(xmax, ymin);
			glVertex2f(xmax, ymax);
			glVertex2f(xmin, ymax);
		glEnd();

		glBegin(GL_LINES);
			glVertex2f(x0,y0);
			glVertex2f(x1, y1);
		glEnd();			
	}
	 

}


void display(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin, ymin);
		glVertex2f(xmax, ymin);
		glVertex2f(xmax, ymax);
		glVertex2f(xmin, ymax);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(x0,y0);
		glVertex2f(x1, y1);
	glEnd();

	cohen(x0,y0,x1,y1);
	glFlush();	
}

void init(){
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv){
	printf("Enter x0,y0,x1,y1\n");
	scanf("%d %d %d %d",&x0,&y0,&x1,&y1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("cohen");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
