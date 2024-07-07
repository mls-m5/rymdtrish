#include "draw.h"
#include "input.h"
#include "world.h"
#include <GL/glut.h>
#include <cstdlib>

constexpr auto timerDelay = 20.;

void glutDisplay() {
    // Draw::drawAsteroid(0,0,0);  //This is just a test for rendering
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0, 0, -70);
    Draw::drawStars();
    World::draw();
    glPopMatrix();
    glutSwapBuffers();
}

void perspectiveTransformations() {
    glLoadIdentity();
    gluPerspective(50, 1, 1, 100);
}

void glutKeyboard(unsigned char key, int x, int y) {
    // Ställer in värdet på den nyss nedtryckta tangenten
    InputControl::setKey(key, 1);
}

void glutKeyboardUp(unsigned char key, int x, int y) {
    // Samma som ovan fast tvärt om
    InputControl::setKey(key, 0);
}

// Functions for special keypress
void glutSpecial(int key, int x, int y) {
    InputControl::setKey(key, 1);

    InputControl::setKey(key, 2);
}

void glutSpecialUp(int key, int x, int y) {
    InputControl::setKey(key, 0);
}

// gluts timer function
void glutTimer(int i) {
    glutTimerFunc(timerDelay, glutTimer, 0);
    perspectiveTransformations();
    World::update(timerDelay / 1000.);

    glutPostRedisplay();
}

int main(int argc, char **args) {
    // Initierar gl och glut

    glutInit(&argc, args);

    glutInitDisplayMode(GLUT_DEPTH * 0 | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 640);
    glutCreateWindow("Rymdtrish");

    // Callback functions
    glutDisplayFunc(glutDisplay);
    glutKeyboardFunc(glutKeyboard);
    glutKeyboardUpFunc(glutKeyboardUp);
    glutSpecialFunc(glutSpecial);
    glutSpecialUpFunc(glutSpecialUp);
    glutTimerFunc(timerDelay, glutTimer, 0);

    // Återställer knappar
    InputControl::resetKeys();

    World::init();

    // Startar huvudloopen
    glutMainLoop();

    World::terminate();
}
