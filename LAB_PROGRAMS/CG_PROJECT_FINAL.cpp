//BEGINNIG OF THE CODE FOR DISPLAYING OLYMPIC RING ANIMATION
//HEADER FILES INCLUSION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<GL/gl.h>
#include <GL/glut.h>

//Some <math.h> files do not define M_PI and CUSTOM DEFINITIONS
#ifndef M_PI
#define M_PI 3.141592654
#endif

#ifdef WIN32
#define drand48() (((float) rand())/((float) RAND_MAX))
#define srand48(x) (srand((x)))
#else
extern double drand48(void);
extern void srand48(long seedval);
#endif

#define XSIZE   100
#define YSIZE   75

#define RINGS 6
#define BLUERING 0
#define BLACKRING 1
#define REDRING 2
#define YELLOWRING 3
#define GREENRING 4
#define MAGENTARING 5

#define BACKGROUND 8
//FUNCTION PROTOTYPES
void Init();
void Reshape(int width, int height);
//FUNCTION TO ADD DELAY
void delay()
{
    for(int i=0;i<2500;i++)
       for(int j=0;j<2500;j++);
}
//END OF FUNCTION TO ADD DELAY
//ENUMERATION OBJECTS DECLARATION AND FUNCTION TO DETERMINE TYPE FOR DISPLAY MODE
enum
{
	BLACK = 0,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
};

GLenum rgb, doubleBuffer, directRender;
GLenum Args(int argc, char **argv)
{
	GLint i;

	rgb = GL_TRUE;
	doubleBuffer = GL_TRUE;

	for (i = 1; i < argc; i++)
        {
		if (strcmp(argv[i], "-ci") == 0)
		{
			rgb = GL_FALSE;
		} else if (strcmp(argv[i], "-rgb") == 0)
		{
			rgb = GL_TRUE;
		} else if (strcmp(argv[i], "-sb") == 0)
		{
			doubleBuffer = GL_FALSE;
		} else if (strcmp(argv[i], "-db") == 0)
		{
			doubleBuffer = GL_TRUE;
		} else
		{
			printf("%s (Bad option).\n", argv[i]);
			return GL_FALSE;
		}
	}
	return GL_TRUE;
}
//END OF ENUMERATION OBJECTS DECLARATION AND FUNCTION TO DETERMINE TYPE FOR DISPLAY MODE
//DECLARATION OF RING VALUES AND VARIABLES RELATED TO CONSTRUCTION OF RINGS
typedef short Point[2];



unsigned char rgb_colors[RINGS][3];
int mapped_colors[RINGS];
float dests[RINGS][3];
float offsets[RINGS][3];
float angs[RINGS];
float rotAxis[RINGS][3];
int iters[RINGS];
GLuint theTorus;
int flag=0;
//END OF DECLARATION OF RING VALUES AND VARIABLES RELATED TO CONSTRUCTION OF RINGS
//FUNCTION TO GENERATE RANDOM NUMBER
float MyRand(void)
{
	return 10.0 * (drand48() - 0.5);
}
//END OF FUNCTION TO GENERATE RANDOM NUMBER
//FUNCTION TO FILL COLORS TO THE RINGS
void FillTorus(float rc, int numc, float rt, int numt)
{
	int i, j, k;
	double s, t;
	double x, y, z;
	double pi, twopi;

	pi = M_PI;
	twopi = 2 * pi;
	for (i = 0; i < numc; i++) {
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= numt; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = cos(t * twopi / numt) * cos(s * twopi / numc);
				y = sin(t * twopi / numt) * cos(s * twopi / numc);
				z = sin(s * twopi / numc);
				glNormal3f(x, y, z);

				x = (rt + rc * cos(s * twopi / numc)) * cos(t * twopi / numt);
				y = (rt + rc * cos(s * twopi / numc)) * sin(t * twopi / numt);
				z = rc * sin(s * twopi / numc);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}
//END OF FUNCTION TO FILL COLORS TO THE RINGS
//FUNCTION CALLED DRAWSCENE TO DRAW THE RINGS
void DrawScene()
{
	int i;

	glPushMatrix();
        delay();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	for (i = 0; i < RINGS; i++)
	{
		if (rgb)
		{
			glColor3ubv(rgb_colors[i]);
		} 
		else
		{
			glIndexi(mapped_colors[i]);
		}
		glPushMatrix();
		glTranslatef(dests[i][0] + offsets[i][0], dests[i][1] + offsets[i][1],
				dests[i][2] + offsets[i][2]);
		glRotatef(angs[i], rotAxis[i][0], rotAxis[i][1], rotAxis[i][2]);
		glCallList(theTorus);
		glPopMatrix();
	}

	glPopMatrix();
	if (doubleBuffer)
    {
		glutSwapBuffers();
	}
	else
	{
		glFlush();
	}
}
//END OF FUNCTION TO DRAW RINGS
//FUNCTIONS TO DRAW THE WELCOME AND END PAGES
void output(GLfloat x, GLfloat y, char* text)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(1/130.38, 1/130.38, 1/130.38);
	for( char* p = text; *p; p++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
}
void output1(GLfloat x, GLfloat y, char* text)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(1/200.34, 1/200.34, 1/200.34);
	for( char* p = text; *p; p++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
}
void output2(GLfloat x, GLfloat y, char* text)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(1/100.34, 1/100.34, 1/100.34);
	for( char* p = text; *p; p++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
}
void output3(GLfloat x, GLfloat y, char* text)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(1/90.34, 1/90.34, 1/90.34);
	for( char* p = text; *p; p++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
}
void Welcome(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3ub(0,0,255);
	output(-2.25,8.0,"WELCOME");
	output1(-5.30,5.25,"CMR INSTITUTE OF TECHNOLOGY");
	output1(-9.30,2.25,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	output(-4.50,-2.25,"MINI PROJECT ON");
	output(-7.15,-6.25,"{||OLYMPIC RINGS ANIMATION||}");

	glutSwapBuffers();
	glFlush();

}
void TY(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3ub(0,0,255);
	glColor3f(1,1,0);
	output2(-3.75,6.75,"THANK YOU");
	output1(-8.90,5.0,"NAME 1: Rahul Prasad Majgi   USN : 1CR16CS123");
	output1(-8.90,3.0,"NAME 1: Ronjay Rudra       USN : 1CR16CS136");
    output1(-8.90,1.0,"GUIDE NAME: Kartheek G.C.R");
    output3(-7.75,-6.5,"PRESS ESC TO EXIT");

	glutSwapBuffers();
	glFlush();

}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

	if(flag==0)
	{
		Welcome();
	}
	else if(flag==1)
	{
	    Init();
	    Reshape(1500,900);
	    flag=2;
	}
	else
    {
        DrawScene();
    }
}
//END OF CODE SECTION TO DRAW WELCOME AND END PAGES
float Clamp(int iters_left, float t)
{

	if (iters_left < 3)
    {
		return 0.0;
	}
	return (iters_left - 2) * t / iters_left;
}
//DEFINES WHAT TO DO WHEN THE SYSTEM IS IDLE
void Idle(void)
{
	int i, j;
	int more = GL_FALSE;

	for (i = 0; i < RINGS; i++)
    {
		if (iters[i])
		{
			for (j = 0; j < 3; j++)
			{
				offsets[i][j] = Clamp(iters[i], offsets[i][j]);
			}
			angs[i] = Clamp(iters[i], angs[i]);
			iters[i]--;
			more = GL_TRUE;
		}
	}
	if (more)
	{
		glutPostRedisplay();
	}
	else
	{
		glutIdleFunc(NULL);
	}
}
//END OF CODE SECTION THAT DEFINES WHAT THE SYSTEM DOES WHEN IDLE
//FUNCTIONS TO INITIALIZE OR RE-INITIALIZE THE DRAWN RINGS
void ReInit(void)
{
	int i;
	float deviation;

	deviation = MyRand() / 2;
	deviation = deviation * deviation;
	for (i = 0; i < RINGS; i++)
	{
		offsets[i][0] = MyRand();
		offsets[i][1] = MyRand();
		offsets[i][2] = MyRand();
		angs[i] = 260.0 * MyRand();
		rotAxis[i][0] = MyRand();
		rotAxis[i][1] = MyRand();
		rotAxis[i][2] = MyRand();
		iters[i] = (deviation * MyRand() + 60.0);
	}
}

void Init(void)
{
	int i;
	float top_y = 1.0;
	float bottom_y = 0.0;
	float top_z = 0.15;
	float bottom_z = 0.69;
	float spacing = 2.5;
	static float lmodel_ambient[] =
	{0.0, 0.0, 0.0, 0.0};
	static float lmodel_twoside[] =
	{GL_FALSE};
	static float lmodel_local[] =
	{GL_FALSE};
	static float light0_ambient[] =
	{0.1, 0.1, 0.1, 1.0};
	static float light0_diffuse[] =
	{1.0, 1.0, 1.0, 0.0};
	static float light0_position[] =
	{0.8660254, 0.5, 1, 0};
	static float light0_specular[] =
	{1.0, 1.0, 1.0, 0.0};
	static float bevel_mat_ambient[] =
	{0.0, 0.0, 0.0, 1.0};
	static float bevel_mat_shininess[] =
	{40.0};
	static float bevel_mat_specular[] =
	{1.0, 1.0, 1.0, 0.0};
	static float bevel_mat_diffuse[] =
	{1.0, 0.0, 0.0, 0.0};

	srand48(0x102342);
	ReInit();
	for (i = 0; i < RINGS; i++)
        {
		rgb_colors[i][0] = rgb_colors[i][1] = rgb_colors[i][2] = 0;
	}
	rgb_colors[BLUERING][2] = 255;
	rgb_colors[REDRING][0] = 255;
	rgb_colors[GREENRING][1] = 255;
	rgb_colors[YELLOWRING][0] = 255;
	rgb_colors[YELLOWRING][1] = 255;
	mapped_colors[BLUERING] = BLUE;
	mapped_colors[REDRING] = RED;
	mapped_colors[GREENRING] = GREEN;
	mapped_colors[YELLOWRING] = YELLOW;
	mapped_colors[BLACKRING] = BLACK;

	dests[BLUERING][0] = -spacing;
	dests[BLUERING][1] = top_y;
	dests[BLUERING][2] = top_z;

	dests[BLACKRING][0] = 0.0;
	dests[BLACKRING][1] = top_y;
	dests[BLACKRING][2] = top_z;

	dests[REDRING][0] = spacing;
	dests[REDRING][1] = top_y;
	dests[REDRING][2] = top_z;

	dests[YELLOWRING][0] = -spacing / 2.0;
	dests[YELLOWRING][1] = bottom_y;
	dests[YELLOWRING][2] = bottom_z;

	dests[GREENRING][0] = spacing / 2.0;
	dests[GREENRING][1] = bottom_y;
	dests[GREENRING][2] = bottom_z;
	
	dests[MAGENTARING][0] = spacing / 2.0;
	dests[MAGENTARING][1] = bottom_y;
	dests[MAGENTARING][2] = bottom_z;

	theTorus = glGenLists(1);
	glNewList(theTorus, GL_COMPILE);
	FillTorus(0.1, 8, 1.0, 25);
	glEndList();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	if (rgb)
        {
		glClearColor(0.5, 0.5, 0.5, 0.0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
		glEnable(GL_LIGHT0);

		glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, lmodel_local);
		glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
		glEnable(GL_LIGHTING);

		glMaterialfv(GL_FRONT, GL_AMBIENT, bevel_mat_ambient);
		glMaterialfv(GL_FRONT, GL_SHININESS, bevel_mat_shininess);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bevel_mat_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bevel_mat_diffuse);

		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glShadeModel(GL_SMOOTH);
	}
	else
	{
		glClearIndex(BACKGROUND);
		glShadeModel(GL_FLAT);
	}

	glMatrixMode(GL_PROJECTION);
	gluPerspective(5, 1.33, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
//END OF FUNCTIONS FOR INITIALIZING AND RE-INITIALIZING THE DRAWN RINGS
//FUNCTIONS TO DEFINE KEYBOARD AND MOUSE ACTIONS
void Key(unsigned char key, int x, int y)
{

	switch (key)
	{
		case 27:
			exit(0);
			break;
		case ' ':
			ReInit();
			glutIdleFunc(Idle);
			break;
		case 13:
		    if(flag==0)
		    {
                    printf("Zzzzz");
                    flag=1;
		    }
		myDisplay();
	    break;
	}
}
void myMouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        TY();
    }
}
//END OF FUNCTIONS TO DEFINE WHAT KEYBOARD AND MOUSE DO
//FUNCTION TO DISPLAY CONTENT ON IDLE
void visible(int vis)
{
	if (vis == GLUT_VISIBLE)
    {
		glutIdleFunc(Idle);
	}
	else
	{
		glutIdleFunc(NULL);
	}
}
//END OF FUNCTION TO DISPLAY CONTENT WHEN IDLE
//FUNCTION TO RESHAPE THE WINDOW SIZE
void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}
//END OF FUNCTION TO RESHAPE WINDOW SIZE
//MAIN FUNCTION
int main(int argc, char **argv)
{
	GLenum type;
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 900);

	if (Args(argc, argv) == GL_FALSE)
	{
		exit(1);
	}

	type = (rgb) ? GLUT_RGB : GLUT_INDEX;
	type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
	glutInitDisplayMode(type);

	glutCreateWindow("Olympic");

	Init();

    //glutFullScreen();
	glutKeyboardFunc(Key);
	glutDisplayFunc(myDisplay);
    glutReshapeFunc(Reshape);
	glutVisibilityFunc(visible);
    glutMouseFunc(myMouse);
	glutMainLoop();
	return 0;
}
//END OF MAIN FUCNTION
