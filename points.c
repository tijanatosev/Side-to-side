#include "points.h"

// variable which indicates numbers of lives player have
extern int life;
// coordiante of the player we need for moving cubes on Z axes
extern float pZ;

void draw_points() {
	
	int i;
	for (i = 0; i < life; i++) {
		glPushMatrix();
			GLfloat light_position[] = { -1, 0, 1, 0 };
		    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
		    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
		    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

		    GLfloat ambient_coeffs[] = { 0.1, 0.1, 1.0, 1 };
		    GLfloat diffuse_coeffs[] = { 0.1, 0.1, 1.0, 1 };
		    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
		   	GLfloat shininess = 40;

		   	// adjusting lights and materials
		    glEnable(GL_LIGHTING);
		    glEnable(GL_LIGHT0);
			    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
			    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
			    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
			    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
			    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
			    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
			    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


			// when cubes are added - they are translated so they are a little apart
			glTranslatef(0.2*i*2 - 5, 5, pZ - 1);
			// drawing cubes
			glutSolidCube(0.2);

            // we have to disable the light in order not to change the light
            // of the whole animation
			glDisable(GL_LIGHTING);
		glPopMatrix();
	}
}