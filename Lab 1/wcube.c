/* -*- Mode: c; c-indentation-style: stroustrup; c-basic-offset: 4 -*- */

#include <GL/glut.h>

GLdouble angle;

void init() {
    glClearColor(0, 0, 0, 0);
    angle = 0;
}

void anim() {
    angle += 0.5;
    if (angle>360) angle -= 360;
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -3);
    glRotatef(angle, 0.5, 1, 0.3);
    glutWireCube(1);
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
    switch(key) {
    case 27:       /* Escape */
    case 3:        /* Ctrl-C */
        exit(0);
	break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
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
