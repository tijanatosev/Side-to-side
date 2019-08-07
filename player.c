#include "player.h"

void player(float x, float y, float z) {
	glPushMatrix();
		// player is a sphere and here we set parameters for
		// light and material
		GLfloat light_position[] = { 1, 1, 0, 0 };
	    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
	    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
	    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

	    GLfloat ambient_coeffs[] = { 0.1, 0.1, 1.0, 1 };
	    GLfloat diffuse_coeffs[] = { 0.1, 0.1, 1.0, 1 };
	    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
	   	GLfloat shininess = 40;

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
		
		// placing and drawing sphere on set coordinates
		glTranslatef(x, y, z);
		glutSolidSphere(0.3, 40, 40);
		glDisable(GL_LIGHTING);
	glPopMatrix();
}