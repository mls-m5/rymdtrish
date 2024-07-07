#include "draw.h"
#include "input.h"
#include "world.h"
#include <GL/glut.h>
#include <cstdlib>

#define TIMER_DELAY 20.

//////
World *world;

void glutDisplay() {
    // Draw::drawAsteroid(0,0,0);  //This is just a test for rendering
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0, 0, -70);
    Draw::drawStars();
    world->draw();
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
    glutTimerFunc(TIMER_DELAY, glutTimer, 0);
    perspectiveTransformations();
    world->update(TIMER_DELAY / 1000.);

    glutPostRedisplay();
}

void terminate() {
    // Det verkar som att det inte bara är onödigt att tömma världen, utan att
    // det till och med krashar programmet World::terminate();
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
    glutTimerFunc(TIMER_DELAY, glutTimer, 0);

    //Återställer knappar
    InputControl::resetKeys();

    // Skapar världen
    // world = new World;

    World::init();

    // Ställer in vad som ska hända när programmet stängs av
    atexit(terminate);

    // Startar huvudloopen
    glutMainLoop();
}
