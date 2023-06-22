#include "engine.h"

int height = 800;
int width = 600;

const char* Window = "test";

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(height, width);
    glutCreateWindow(Window);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
}
