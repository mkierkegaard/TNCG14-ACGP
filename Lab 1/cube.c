/* -*- Mode: c; c-indentation-style: stroustrup; c-basic-offset: 4 -*- */
#define _USE_MATH_DEFINES
#define M_ROTATE_XY     1

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLdouble angle, angle2, angle3;
GLfloat sun_color[] = { 0.9, 0.0, 0.0, 1.0 };
GLfloat sun_spec[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat center[] = { 0, 0, -3, 1 };
GLfloat ambient0[] = { -0.1, -0.1, -0.1 ,1};
GLfloat diffuse0[] = { 0.5, 0.5, 0.5, 1 };
GLfloat specular0[] = { 0.9, 0.5, 0, 1 };
GLfloat sun_emission[] = { 0.9, 0.3, 0.1, 0.1 };
GLfloat earth_color[] = { 0.1, 0.6, 0.3, 1 };
GLboolean showOrbit;

int mouseState = 0;
int xCenter = 0;
int yCenter = 0;
GLfloat xRot = 0;
GLfloat yRot = 0;
GLfloat xRotOld = 0;
GLfloat yRotOld = 0;

//earthTexture = LoadBitmap("earth_texture.jpg");
GLuint earthTexture;
//Image* image = loadBMP("earth_texture.bmp");
void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0);
    angle = 0;
	angle2 = 0;
	angle3 = 0;
	
	glLightfv(GL_LIGHT0, GL_POSITION, center);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.9);
}

void anim() {
    angle += 0.08;
	angle2 += 2.4;
	angle3 += 0.48;
    if (angle>360) angle -= 360;
	if (angle2>360) angle -= 360;
	if (angle3>360) angle -= 360;
    glutPostRedisplay();
}


void drawLine()
{
	double angle = 2 * 3.14 / 200;
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.5);
	//glMaterialfv(GL_FRONT, GL_EMISSION, ambient0);
	glBegin(GL_LINE_LOOP);
	double angle1 = 0.0;
	glVertex3d( cos(0.0), 0.0,  sin(0.0));
	int i;
	for (i = 0; i < 200; ++i)
	{
		glVertex3d( cos(angle1), 0.0,  sin(angle1));
		angle1 += angle;
	}
	glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	printf("\n%f and %f", xRot, yRot);

    glTranslatef(0, 0, -3);

	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glDisable(GL_LIGHT0);
	if (showOrbit)
		drawLine();
	glEnable(GL_LIGHT0);

	glRotatef(angle, 0, 1, 0);
    glShadeModel(GL_FLAT);
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_spec);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);
    glutSolidSphere(0.2, 100, 100);

	

	glPopMatrix();
	
	glDisable(GL_COLOR_MATERIAL);
	
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();

	glRotatef(angle, 0, 1, 0);
	glTranslatef(1, 0, 0);
	glRotatef(-angle, 0, 1, 0);
	glRotatef(10, 0, 0, 1);

	glRotatef(angle2, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_color);
	glMaterialfv(GL_FRONT, GL_EMISSION, ambient0);
	glEnable(GL_TEXTURE_2D);
	
	glDisable(GL_LIGHT0);

	glBegin(GL_LINES);
	glVertex3f(0.0, 0.15, 0.0);
	glVertex3f(0.0, -0.15, 0.0);
	glEnd();
	glEnable(GL_LIGHT0);
	glutSolidSphere(0.05, 20, 20);
	
	glPushMatrix();
	glRotatef(angle3, 0, 1, 0);
	glTranslatef(0.3, 0, 0);

	glutSolidSphere(0.02, 10, 10);
	


    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLdouble)w/(GLdouble)h, 0.1, 5);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {

     switch (key) {
     case 3:             /* Ctrl-C */
     case 27:            /* ESC */
         exit(0);
	 case 'o': showOrbit = !showOrbit;
		 break;
     }
}


void mouse(int button, int state, int x, int y) {
	xCenter = x;
	yCenter = y;
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			mouseState = M_ROTATE_XY;
			xRotOld = xRot;
			yRotOld = yRot;
		}
	}
	else {
		mouseState = 0;
	}
}

void motion(int x, int y) {
	
	if (mouseState == M_ROTATE_XY) {
		xRot = xRotOld + (float)(y - yCenter) / 4.0;
		yRot = yRotOld + (float)(x - xCenter) / 4.0;
	}
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Brüsselcole");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
    glutIdleFunc(anim);
    glutReshapeFunc(reshape);	
    glutMainLoop();
}
