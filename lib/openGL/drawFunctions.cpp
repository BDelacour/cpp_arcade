#include "OpenGL.h"

void drawCube(double x, double y, double height, float red, float green, float blue)
{
    float matAmb[4] = {red, green, blue, 1.f};
    float matDiff[4] = {red, green, blue, 1.f};
    float matSpec[4] = {1.f, 1.f, 1.f, 1.f};
    float matShin[1] = {100.f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShin);
    glPushMatrix();
    glBegin(GL_TRIANGLES);

    /*      This is the bottom face*/
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(x, y - 1.0f, height - 1.0f);
    glVertex3f(x, y -1.0f, height);
    glVertex3f(x - 1.0f, y - 1.0f, height);
    glVertex3f(x, y - 1.0f, height - 1.0f);
    glVertex3f(x - 1.0f, y - 1.0f, height);
    glVertex3f(x - 1.0f, y - 1.0f, height - 1.0f);

    //top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x, y, height - 1.0f);
    glVertex3f(x - 1.0f, y, height - 1.0f);
    glVertex3f(x - 1.0f, y, height);
    glVertex3f(x, y, height - 1.0f);
    glVertex3f(x - 1.0f, y, height);
    glVertex3f(x, y, height);

    //right face
    glNormal3f(x, 0.0f, 0.0f);
    glVertex3f(x, y - 1.0f, height - 1.0f);
    glVertex3f(x, y, height - 1.0f);
    glVertex3f(x, y, height);
    glVertex3f(x, y - 1.0f, height - 1.0f);
    glVertex3f(x, y, height);
    glVertex3f(x, y - 1.0f, height);

    //front face
    glNormal3f(0.0f, 0.0f, 1.f);
    glVertex3f(x, y - 1.0f, height);
    glVertex3f(x, y, height);
    glVertex3f(x - 1.0f, y, height);
    glVertex3f(x, y - 1.0f, height);
    glVertex3f(x - 1.0f, y, height);
    glVertex3f(x - 1.0f, y - 1.0f, height);

    //left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(x - 1.0f, y - 1.0f, height);
    glVertex3f(x - 1.0f, y, height);
    glVertex3f(x - 1.0f, y, height - 1.0f);
    glVertex3f(x - 1.0f, y - 1.0f, height);
    glVertex3f(x - 1.0f, y, height - 1.0f);
    glVertex3f(x - 1.0f, y - 1.0f, height - 1.0f);

    //back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(x, y, height - 1.0f);
    glVertex3f(x, y - 1.0f, height - 1.0f);
    glVertex3f(x - 1.0f, y - 1.0f, height - 1.0f);
    glVertex3f(x, y, height - 1.0f);
    glVertex3f(x - 1.0f, y - 1.0f, height - 1.0f);
    glVertex3f(x - 1.0f, y, height - 1.0f);

    glEnd();
    glPopMatrix();
/*
    glBegin(GL_QUADS);
    glVertex3d(x, y, height
    );
    glVertex3d(x, y,
               0);
    glVertex3d(x
               - 1, y, 0);
    glVertex3d(x
               - 1, y, height);

    glVertex3d(x, y
                  - 1, height);
    glVertex3d(x, y
                  - 1, 0);
    glVertex3d(x, y,
               0);
    glVertex3d(x, y, height
    );

    glVertex3d(x
               - 1, y - 1, height);
    glVertex3d(x
               - 1, y - 1, 0);
    glVertex3d(x, y
                  - 1, 0);
    glVertex3d(x, y
                  - 1, height);

    glVertex3d(x
               - 1, y, height);
    glVertex3d(x
               - 1, y, 0);
    glVertex3d(x
               - 1, y - 1, 0);
    glVertex3d(x
               - 1, y - 1, height);

    glVertex3d(x, y,
               0);
    glVertex3d(x, y
                  - 1, 0);
    glVertex3d(x
               - 1, y - 1, 0);
    glVertex3d(x
               - 1, y, 0);

    glVertex3d(x, y
                  - 1, height);
    glVertex3d(x, y, height
    );
    glVertex3d(x
               - 1, y, height);
    glVertex3d(x
               - 1, y - 1, height);

    glEnd();*/

}

void drawSphere(double x, double y, double radius, float red, float green, float blue)
{
    float matAmb[4] = {red, green, blue, 1.f};
    float matDiff[4] = {red, green, blue, 1.f};
    float matSpec[4] = {1.f, 1.f, 1.f, 1.f};
    float matShin[1] = {100.f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShin);
    glTranslated(x - 0.5, y - 0.5, 0.5);
    GLUquadric *quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluSphere(quad, radius, 20, 20);
    gluDeleteQuadric(quad);
}

void drawFloor(int width, int height)
{
    float matAmb[4] = {0.35f, 0.23f, 0.13f, 1.f};
    float matDiff[4] = {0.35f, 0.23f, 0.13f, 1.f};
    float matSpec[4] = {1.f, 1.f, 1.f, 1.f};
    float matShin[1] = {100.f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShin);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.f);
    glVertex3f(-1, height - 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(-1 + width, -1, 0);
    glVertex3f(-1, height - 1, 0);
    glVertex3f(-1 + width, -1, 0);
    glVertex3f(-1 + width, height - 1, 0);
    glEnd();
    glPopMatrix();
}

void drawMap(int width, int height, std::vector<CaseType> &map)
{
    int LightPos[4] = {0, 0, 3, 1};
    float ambient[4] = {0.45f, 0.45f, 0.45f, 1.0f};
    float diffuse[4] = {1.f, 1.f, 1.f, 1.f};

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0, 0, 5);
    glRotated(90, 0, 0, 1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse);
    glLightiv(GL_LIGHT0, GL_POSITION, LightPos);
    glLoadIdentity();
    gluLookAt((width - 1) / 2, -height / 6, height - 5, (width - 1) / 2, height + 30, -height - 20, 0, 1, 1);
    drawFloor(width, height);
    for (int i = 0; i < width * height; i++)
    {
        switch (map[i])
        {
            case CaseType::WALL:
                glLoadIdentity();
                gluLookAt((width - 1) / 2, -height / 6, height - 5, (width - 1) / 2, height + 30, -height - 20, 0, 1,
                          1);
                drawCube(i % width, height - i / width - 1, 0.25, 0.4f, 0.4f, 0.4f);
                break;
            case CaseType::SNAKE:
                glLoadIdentity();
                gluLookAt((width - 1) / 2, -height / 6, height - 5, (width - 1) / 2, height + 30, -height - 20, 0, 1,
                          1);
                drawSphere(i % width, height - i / width - 1, 0.75f, 0.f, 0.5f, 0.f);
                break;
            case CaseType::POWERUP:
                glLoadIdentity();
                gluLookAt((width - 1) / 2, -height / 6, height - 5, (width - 1) / 2, height + 30, -height - 20, 0, 1,
                          1);
                drawSphere(i % width, height - i / width - 1, 0.5, 0.5f, 0.f, 0.f);
                break;
            default:
                break;
        }
    }
}