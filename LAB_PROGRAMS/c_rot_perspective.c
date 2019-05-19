#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

float v[8][3] = {{-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1},{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1}},theta[3] ={0,0,0},viewer[3]={0,0,5};
int axis = 0;

void display();
void polygon(int a,int b,int c,int d)
{
   glBegin(GL_POLYGON);
   glVertex3fv(v[a]);
   glVertex3fv(v[b]);
   glVertex3fv(v[c]);
   glVertex3fv(v[d]);
   glEnd();
}

void spin()
{
theta[axis]+=1;

    display();
}



void cube()
{
   glColor3f(1,0,0);
   polygon(0,1,5,4);

   glColor3f(0,1,0);
   polygon(2,6,7,3);

   glColor3f(0,0,1);
   polygon(1,5,6,2);

   glColor3f(1,0,1);
   polygon(0,4,7,3);

   glColor3f(1,1,0);
   polygon(0,1,2,3);

   glColor3f(0,0,0);
   polygon(4,5,6,7);
	
}


void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);//added
	glRotatef(theta[0],1,0,0);
	glRotatef(theta[1],0,1,0);
	glRotatef(theta[2],0,0,1);
	
	cube();
	glFlush();
	glutSwapBuffers();
}


void keyb(unsigned char key,int x,int y)
{
	if(key=='X')
		viewer[0]+=1;
	if(key=='x')
		viewer[0]-=1;
	if(key=='Y')
		viewer[1]+=1;
	if(key=='y')
		viewer[1]-=1;
	if(key=='Z')
		viewer[2]+=1;
	if(key=='z')
		viewer[2]-=1;
	display();
}
void mouse(int button,int state,int x,int y)
{
   if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
      axis=0;
   if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
      axis=1;
   if(button==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
      axis=2;
   //display();
   spin();
}


/*void key(unsigned char ch,int x,int y)
{
	if(ch == 'a')
	{
		axis=0;
		axis=1;
		axis=2;
	}
	display();
}*/


void init()
{
 glMatrixMode(GL_PROJECTION);
 glFrustum(-2,2,-2,2,1,10);
 //glOrtho(-3,3,-3,3,-3,3);
 glMatrixMode(GL_MODELVIEW);

}


int main(int argc,char **argv)
{ 
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

 glutInitWindowPosition(0,0);
 glutInitWindowSize(500,500);
 glutCreateWindow("CUBE ROTATION");

 init();
 
 glutDisplayFunc(display);
 glutMouseFunc(mouse);
 glutKeyboardFunc(keyb);
 //glutIdleFunc(spin);
 glEnable(GL_DEPTH_TEST);
 glutMainLoop();
 return 0;
}


