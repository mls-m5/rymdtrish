#ifndef _draw_h_
#define _draw_h_
#include <GL/gl.h>
#include <cmath>
//#include <stdlib.h>
#define pi 3.14159265

// En klass som används för utritning av diverse saker
class Draw {
private:
    // En funktion för att underlätta transformeringen innan utritningen
    inline static void transform(double x, double y, double a, double s) {
        glTranslated(x, y, 0);
        glScaled(s, s, s);
        glRotated(a * 180. / pi, 0, 0, 1);
    }

public:
    static void transformView(double x, double y, double angle) {
        glRotated(-angle * 180. / pi, 0, 0, 1);
        glTranslated(-x, -y, 0);
    }

    static void drawStars() {
        // Always seeds the random generator with the same number so the stars
        // stay in the same place
        long rnd;
        rnd = rand();
        srand(20);
        glPointSize(1);
        glBegin(GL_POINTS);
        glColor3f(1, 1, 1);
        for (int i = 0; i < 200; i++) {
            glVertex3i(rand() % 200 - 100, rand() % 200 - 100, rand() % 9 + 1);
        }
        glEnd();

        //Återställer slump
        srand(rnd);
    }

    // The parameters is the same for all draw functions
    // therefore the marko PARA
#define PARA                                                                   \
    double x, double y, double a, double r = 1, double g = 1, double b = 1,    \
                                         double scale = 1

    // Some functions for drawing different obsticles
    static void drawAsteroid(PARA) {
        glPushMatrix();
        transform(x, y, a, scale);

        glBegin(GL_TRIANGLE_FAN);

        glColor3d(r, g, b);

        // float ang;

        for (int i = 0; i < 5; i++) {
            a = float(i) * 2. * pi / 5.;
            glVertex2d(sin(a), cos(a));
        }

        // glVertex2d(0,-1);
        // glVertex2d(1,0);
        // glVertex2d(0,1);
        // glVertex2d(-1,0);

        glEnd();
        glPopMatrix();
    }

    static void drawShip(PARA) {
        glPushMatrix();
        transform(x, y, a, scale);

        glBegin(GL_TRIANGLE_FAN);

        glColor3d(r, g, b);

        glVertex2d(0, 1);
        glVertex2d(.5, -1);
        glVertex2d(-.5, -1);

        glEnd();
        glPopMatrix();
    }

    static void drawProjectile(PARA) {
        glPushMatrix();
        transform(x, y, a, scale);

        glBegin(GL_TRIANGLE_FAN);

        glColor3d(r, g, b);

        glVertex2d(0, .2);
        glVertex2d(.1, 0);
        glVertex2d(0, -1);
        glVertex2d(-.1, 0);

        glEnd();
        glPopMatrix();
    }

    static void drawSpark(PARA) {
        glPushMatrix();

        transform(x, y, a, scale);

        glColor3d(r, g, b);
        glPointSize(2.);
        glBegin(GL_POINTS);
        glVertex2d(0, 0);
        glEnd();

        glPopMatrix();
    }
};

#endif
