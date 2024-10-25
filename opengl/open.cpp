#include <GL/glut.h>
#include <cmath>

// Function to draw a point
void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// DDA Line Drawing Algorithm
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = float(dx) / float(steps);
    float yIncrement = float(dy) / float(steps);
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        drawPixel(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
}

// Function to handle mouse click events
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Draw a line from (0, 0) to the clicked position
        drawLine(0, 0, x, glutGet(GLUT_WINDOW_HEIGHT) - y);
        glFlush();
    }
}

// Function to initialize OpenGL
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
}

// Function to display content on the screen
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);
    glColor3f(0.0, 0.0, 0.0);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("DDA Line Drawing Algorithm");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}
