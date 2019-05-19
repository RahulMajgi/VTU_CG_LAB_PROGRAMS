#include <stdio.h>
#include <GL/glut.h>
float x0,ya,x1,yb,x2,y2,x3,y3,m;
void init()
{
	gluOrtho2D(0,300,0,300);
}

void edge_detect(float x0,float ya,float x1,float yb,float le[],float re[])
{
	float x;
	if(ya>yb)
	{
		float temp;
		temp=ya;
		ya=yb;
		yb=temp;
		temp=x0;
		x0=x1;
	        x1=temp;
	}
	m = (float)((x1-x0)/(yb-ya));
	x=x0;
	for(int i=ya;i<yb;i++)
	{
		if(x<le[i])
			le[i]=x;
		if(x>re[i]) 
			re[i]=x;
		x+=m;
	}
}


void scanfill(float x0,float ya,float x1,float yb,float x2,float y2,float x3,float y3)
{
float le[500],re[500];
for(int i=0;i<500;i++)
{
	le[i]=500;
	re[i]=0;
}
edge_detect(x0,ya,x1,yb,le,re);
edge_detect(x1,yb,x2,y2,le,re);
edge_detect(x2,y2,x3,y3,le,re);
edge_detect(x3,y3,x0,ya,le,re);
for(int y=0;y<500;y++)
{
	if(le[y]<re[y])
	{
		for(int i=le[y];i<re[y];i++)
		{
			glColor3f(0,0,1);
			glBegin(GL_POINTS);
			glVertex2f(i,y);
			glEnd();
			//glFlush();
		}
	}
}
}

int flag = 0;
void menu(int id)
{
if(id==1)
{
	flag=1;
}
else
{
	flag=0;
}
glutPostRedisplay();
}

void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glColor3f(0,0,1);
	glVertex2f(x0,ya);
	glVertex2f(x1,yb);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glEnd();
	if(flag == 1)
		scanfill(x0,ya,x1,yb,x2,y2,x3,y3);
	glFlush();
}
	

void main(int argc,char **argv)
{
	printf("ENTER THE VALUES FOR x0,ya,x1,yb,x2,y2,x3,y3 \n");
	scanf("%f%f%f%f%f%f%f%f",&x0,&ya,&x1,&yb,&x2,&y2,&x3,&y3);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("P O L Y G O N F I L L");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	init();
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("FILL",1);
	glutAddMenuEntry("CLEAR",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
