#include "grass.h"

extern GLuint names[1];

void draw_grass() {
    // drawing closer grass to the camera
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, names[0]);
        glRotatef(90, 1, 0, 0);
        glTranslatef(-25, -25.5, 0);
        glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);

            glTexCoord2f(0, 0);
            glVertex3f(0, 0, 0);

            glTexCoord2f(130, 0);
            glVertex3f(65, 0, 0);

            glTexCoord2f(120, 50);
            glVertex3f(65, 25, 0);

            glTexCoord2f(0, 50);
            glVertex3f(0, 25, 0);
        glEnd();
    glPopMatrix();

    // drawing futrher grass from the camera
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, names[0]);
        glRotatef(90, 1, 0, 0);
        glTranslatef(-25, 5.5, 0);
        glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);

            glTexCoord2f(0, 0);
            glVertex3f(0, 0, 0);

            glTexCoord2f(130, 0);
            glVertex3f(65, 0, 0);

            glTexCoord2f(120, 50);
            glVertex3f(65, 25, 0);

            glTexCoord2f(0, 50);
            glVertex3f(0, 25, 0);
        glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}