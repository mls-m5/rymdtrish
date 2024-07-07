#pragma once

#include <GL/gl.h>
#include <cmath>
constexpr double pi = 3.14159265;

// En klass som används för utritning av diverse saker
class Draw {
public:
    struct Args {
        double x = 0;
        double y = 0;
        double a = 0;
        double r = 1;
        double g = 1;
        double b = 1;
        double scale = 1;
    };

private:
    // En funktion för att underlätta transformeringen innan utritningen
    inline static void transform(double x, double y, double a, double s) {
        glTranslated(x, y, 0);
        glScaled(s, s, s);
        glRotated(a * 180. / pi, 0, 0, 1);
    }

    inline static void transform(const Args &a) {
        transform(a.x, a.y, a.a, a.scale);
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

        // Återställer slump
        srand(rnd);
    }

    // Some functions for drawing different obsticles
    static void drawAsteroid(Args a) {
        glPushMatrix();
        transform(a);

        glBegin(GL_TRIANGLE_FAN);

        glColor3d(a.r, a.g, a.b);

        for (int i = 0; i < 5; i++) {
            auto ang = float(i + a.a) * 2. * pi / 5.;
            glVertex2d(sin(ang), cos(ang));
        }

        glEnd();
        glPopMatrix();
    }

    static void drawShip(Args a) {
        glPushMatrix();
        transform(a);

        glBegin(GL_TRIANGLE_FAN);

        glColor3d(a.r, a.g, a.b);

        glVertex2d(0, 1);
        glVertex2d(.5, -1);
        glVertex2d(-.5, -1);

        glEnd();
        glPopMatrix();
    }

    static void drawProjectile(Args a) {
        glPushMatrix();
        transform(a.x, a.y, a.a, a.scale);

        glBegin(GL_TRIANGLE_FAN);

        glColor3d(a.r, a.g, a.b);

        glVertex2d(0, .2);
        glVertex2d(.1, 0);
        glVertex2d(0, -1);
        glVertex2d(-.1, 0);

        glEnd();
        glPopMatrix();
    }

    static void drawSpark(Args a) {
        glPushMatrix();

        transform(a);

        glColor3d(a.r, a.g, a.b);
        glPointSize(2.);
        glBegin(GL_POINTS);
        glVertex2d(0, 0);
        glEnd();

        glPopMatrix();
    }
};
