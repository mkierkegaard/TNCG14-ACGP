/* -*- Mode: c; c-indentation-style: stroustrup; c-basic-offset: 4 -*- */

#include <GL/glut.h>

GLdouble angle;
GLfloat sun_color[] = { 0.9, 0.0, 0.0, 1.0 };
GLfloat sun_spec[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat center[] = { 0, 0, -3, 1 };
GLfloat ambient0[] = { 0, 0, 0 ,1};
GLfloat diffuse0[] = { 0.5, 0.5, 0.5, 1 };
GLfloat specular0[] = { 0.9, 0.5, 0, 1 };
GLfloat sun_emission[] = { 0.9, 0.3, 0.1, 0.1 };

void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0);
    angle = 0;
	
	glLightfv(GL_LIGHT0, GL_POSITION, center);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.9);
}

void anim() {
    angle += 0.5;
    if (angle>360) angle -= 360;
    glutPostRedisplay();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	//glPushMatrix();

	
	
    glTranslatef(0, 0, -3);

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
    glShadeModel(GL_FLAT);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_spec);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);
    glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	glTranslatef(1, 0, 0);
	glRotatef(angle, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_spec);
	glMaterialfv(GL_FRONT, GL_EMISSION, ambient0);

	glutSolidSphere(0.05, 100, 100);

	glPopMatrix();
	//glPopMatrix();

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
    glutIdleFunc(anim);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
