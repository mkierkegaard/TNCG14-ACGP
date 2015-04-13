#include <GL/glut.h>

void display(void) {
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutCreateWindow("Ullstrumpa");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
