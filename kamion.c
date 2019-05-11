#include "kamion.h"

void draw_sidewindow(float x, float y, float z) {
	glPushMatrix();
		// osvetljenje 
		GLfloat light_position[] = { 1, 1, 1, 0 };
		GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
		GLfloat light_diffuse[] = { 1, 1, 1, 1 };
		GLfloat light_specular[] = { 1, 1, 1, 1 };

		GLfloat prozor[] = {0.7, 0.7, 0.7, 1};
		GLfloat diffuse_coeffs[] = { 0.1, 0.5, 0.9, 1 };
		GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
		GLfloat shininess = 100;

		glEnable(GL_LIGHTING);
    	glEnable(GL_LIGHT0);
	    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	    glMaterialfv(GL_FRONT, GL_AMBIENT, prozor);
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
	    glMaterialf(GL_FRONT, GL_SHININESS, shininess);	

        glTranslatef(x, y, z);
        glRotatef(90, 0, 1, 0);
        glScalef(0.0, 0.4, 0.88);
        glutSolidCube(1);

        glDisable(GL_LIGHTING);
    glPopMatrix();
}

void draw_backlamp(float x, float y, float z) {
    //funkcija koja crta farove na kamionu
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(x, y, z);
        glScalef(0.0, 0.1, 0.2);
        glutSolidCube(1);
    glPopMatrix();
}

void draw_windshield(float x, float y, float z) {
    //funkcija koja crta sofersajbnu
    glPushMatrix();
    	// osvetljenje 
		GLfloat light_position[] = { 1, 1, 1, 0 };
		GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
		GLfloat light_diffuse[] = { 1, 1, 1, 1 };
		GLfloat light_specular[] = { 1, 1, 1, 1 };

		GLfloat prozor[] = {0.7, 0.7, 0.7, 1};
		GLfloat diffuse_coeffs[] = { 0.1, 0.5, 0.9, 1 };
		GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
		GLfloat shininess = 100;

		glEnable(GL_LIGHTING);
    	glEnable(GL_LIGHT0);
	    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	    glMaterialfv(GL_FRONT, GL_AMBIENT, prozor);
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
	    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

        glColor3f(0.392, 0.584, 0.929);
        glTranslatef(x, y, z);
        glScalef(0.0, 0.4, 0.88);
        glutSolidCube(1);

        glDisable(GL_LIGHTING);
    glPopMatrix();
}

void draw_headlamp(float x, float y, float z) {
	glPushMatrix();
		    	// osvetljenje 
		GLfloat light_position[] = { 1, 1, 1, 0 };
		GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
		GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
		GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

		GLfloat svetlo[] = {1.0, 1.0, 1.0, 1};
		GLfloat diffuse_coeffs[] = { 0.1, 0.1, 0.1, 1 };
		GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
		GLfloat shininess = 10;

		glEnable(GL_LIGHTING);
    	glEnable(GL_LIGHT0);
	    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	    glMaterialfv(GL_FRONT, GL_AMBIENT, svetlo);
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
	    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	    glColor3f(1, 1, 1);
	    glTranslatef(x, y, z);
	    glScalef(0.1, 0.1, 0.1);
	    glRotatef(90, 1, 0, 0);
	    glRotatef(90, 0, 0, 1);
	    glBegin(GL_TRIANGLE_FAN);
	        int i;
	        for (i = 0; i < 360; i++) {
	            float ugao = 2 * 3.141592653589793 * i / 360;
	            glNormal3f(cos(ugao), 0, sin(ugao));
	            glVertex3f(cos(ugao), 0, sin(ugao));
	        }
	    glEnd();
	    glDisable(GL_LIGHTING);
    glPopMatrix();
}

void draw_wheel(float x, float y, float z) {
	glPushMatrix();
		// osvetljenje 
		GLfloat light_position[] = { 0, 0, 0, 0 };
		GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
		GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
		GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

		GLfloat tocak[] = {0.1, 0.1, 1.0, 1};
		GLfloat diffuse_coeffs[] = { 0.1, 0.1, 1.0, 1 };
		GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
		GLfloat shininess = 10;

		glEnable(GL_LIGHTING);
    	glEnable(GL_LIGHT0);
	    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	    glMaterialfv(GL_FRONT, GL_AMBIENT, tocak);
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
	    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

        glColor3f(0, 0, 1);
        glTranslatef(x, y, z);
        glScalef(1.0, 1.0, 1.3); 
        glutSolidTorus(0.05, 0.1, 10, 10);

        glDisable(GL_LIGHTING);
    glPopMatrix();
}

void draw_body() {
	// donji deo kamiona
	glPushMatrix();
		glColor3f(0.6, 0.8, 0.196078);
		glScalef(1.5, 0.5, 1.0);
		glutSolidCube(1);
	glPopMatrix();

	// gornji deo kamiona
	glPushMatrix();
		glColor3f(1, 0, 0);
		glScalef(1.0, 0.5, 1.0);
		glTranslatef(-0.25, 1.0, 0.0);
		glutSolidCube(1);
	glPopMatrix();

}

void draw_truck() {
	
	// napred - blizi
	draw_wheel( 0.6, -0.4, 	0.4);
	// nazad - blizi
	draw_wheel(-0.6, -0.4, 	0.4);
	// napred - dalji
	draw_wheel( 0.6, -0.4, -0.4);
	// nazad - dalji
	draw_wheel(-0.6, -0.4, 	-0.4);

	// far - dalji
	draw_headlamp(0.7501, 0.1, -0.3);
	// far - blizi
	draw_headlamp(0.7501, 0.1,  0.3);

	// sofersajbna
	draw_windshield(0.2501, 0.5, 0.0);

	// staklo - pozadi
	draw_windshield(-0.7501, 0.5, 0.0);

	// pozadi - far (blizi i dalji)
	draw_backlamp(-0.7501, -0.1, -0.3);
    draw_backlamp(-0.7501, -0.1, 0.3);

    // bliza strana
    draw_sidewindow(-0.25, 0.5,  0.5005);
    // dalja strana
    draw_sidewindow(-0.25, 0.5, -0.5005);

    // osnova
	draw_body();
}