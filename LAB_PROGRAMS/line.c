#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
float x0,ya,x1,yb,m;

void draw_pixel(float x,float y)
{
	glColor3f(0,0,1);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void swapx()
{
	float temp;
	temp=x0;
	x0=x1;
	x1=temp;
}

void swapy()
{
	float temp;
	temp=ya;
	ya=yb;
	yb=temp;
}

void init()
{
	gluOrtho2D(-100,100,-\]]\]100,100);
}

void line_drawing1(float x0,float ya,float x1,float yb, float m)
{
	float x,p,y,dx,dy,ppos,pneg;
	if (x0>x1)
	{
		swapx();
		swapy();
	}
	x = x0;
	y = ya;
	dx = abs(x1-x0);
	dx = abs(yb-ya);
	p = (2*dx)-dy;
	pneg = 2*dy;
	ppos = 2*(dy-dx);
	draw_pixel(x,y); 
	while(x<x1)
	{
		x++;
		if(p<0)
		{
			p=p+pneg;
		}
		else
		{
			if(m<0)
				y--;
			else
				y++;
			p=p+ppos;
		}
		draw_pixel(x,y);
	}
}

void line_drawing2(float x0,float ya,float x1,float yb, float m)
{
	float x,p,y,dx,dy,ppos,pneg;
	if (ya>yb)
	{
		swapx();
		swapy();
	}
	x = x0;
	y = ya;
	dx = abs(x1-x0);
	dy = abs(yb-ya);
	p = (2*dx)-dy;
	pneg = 2*dx;
	ppos = 2*(dx-dy);
	draw_pixel(x,y); 
	while(y<yb)
	{
		y++;
		if(p<0)
		{
			p=p+pneg;
		}
		else
		{
			if(m<0)
				x--;
			else
				x++;
			p=p+ppos;
		}
		draw_pixel(x,y);
	}
}
void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	m = (yb-ya)/(x1-x0);
	if(fabs(m)<1)
		line_drawing1(x0,ya,x1,yb,m);
	else
		line_drawing2(x0,ya,x1,yb,m);
	glFlush();
}


void main(int argc,char **argv)
{
	printf("ENTER THE CO-ORDINATES\n");
	printf("ENTER x0\n");
	scanf("%f",&x0);
	printf("ENTER x1\n");
	scanf("%f",&x1);
	printf("ENTER ya\n");
	scanf("%f",&ya);
	printf("ENTER yb\n");
	scanf("%f",&yb);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("L I N E");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
