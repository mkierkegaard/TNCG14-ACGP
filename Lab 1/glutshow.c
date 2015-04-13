/* -*- Mode: c; c-indentation-style: stroustrup; c-basic-offset: 4 -*- */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLdouble angle;
GLdouble wobble;
GLdouble d2pi = M_PI / 180.0;
GLfloat cube_color[4] = { 0.9, 0.5, 0.2, 1.0 };
GLfloat cube_spec[4] = { 0.2, 0.2, 0.1, 1.0 };
GLfloat xRot = 0;
GLfloat yRot = 0;
GLfloat xRotOld = 0;
GLfloat yRotOld = 0;
int mouseState = 0;
int xCenter = 0;
int yCenter = 0;

#define M_ROTATE_XY     1


void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0);
    angle = 0;
}

void anim() {
    angle += 5;
    if (angle>180.0) angle -= 360.0;
    wobble = 80*sin(angle*d2pi);
    glutPostRedisplay();
}

void display(void) {
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -4);

    /* "World" rotation, controlled by mouse */
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);

    for (i = 0; i < 3; i++) {
	for (j = 0; j < 3; j++) {
	    glPushMatrix();
	    glTranslatef(i-1, j-1, 0);
	    glRotatef(wobble, 0.5, 1, 0.3);

	    switch (i*3 + j) {
	    case 0:
		glShadeModel(GL_FLAT);
		glutSolidCube(0.5);
		break;
	    case 1:
		glShadeModel(GL_SMOOTH);
		glutSolidSphere(0.4, 24, 18);
		break;
	    case 2:
		glShadeModel(GL_SMOOTH);
		glutSolidCone(0.3, 0.6, 24, 2);
		break;
	    case 3:
		glShadeModel(GL_SMOOTH);
		glutSolidTorus(0.1, 0.3, 12, 24);
		break;
	    case 4:
		glShadeModel(GL_FLAT);
		glScalef(0.2, 0.2, 0.2);
		glEnable(GL_NORMALIZE);
		glutSolidDodecahedron();
		break;
	    case 5:
		glShadeModel(GL_FLAT);
		glScalef(0.4, 0.4, 0.4);
		glutSolidOctahedron();     /* Still normalizing */
		break;
	    case 6:
		glShadeModel(GL_FLAT);
		glScalef(0.4, 0.4, 0.4);
		glutSolidTetrahedron();    /* Still normalizing */
		break;
	    case 7:
		glShadeModel(GL_FLAT);
		glScalef(0.35, 0.35, 0.35);
		glutSolidIcosahedron();    /* Still normalizing */
		glDisable(GL_NORMALIZE);
		break;
	    case 8:
		glShadeModel(GL_SMOOTH);
		glutSolidTeapot(0.4);
		break;

	    default:
		break;
	    }

	    glPopMatrix();
	}
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLdouble)w/(GLdouble)h, 0.1, 10);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {

     switch (key) {
     case 3:             /* Ctrl-C */
     case 27:            /* ESC */
         exit(0);
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
    } else {
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
