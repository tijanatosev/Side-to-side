#include "trees.h"

#define PI 3.1415926535
#define EPSILON 0.01

void set_normal_and_vertex(float u, float v){
    glNormal3f(sin(v),0,cos(v));
    glVertex3f(sin(v), u, cos(v));
}

void type1() {

	glEnable(GL_NORMALIZE);
	GLfloat light_position[] = { 1, 1, 1, 0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    GLfloat ambient_coeffs[] = { 0.1, 0.3, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0.1, 0.3, 0.1, 1 };
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    GLfloat shininess = 40;

    // setting of light and materials
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
    

    // here we draw tree crown level by level
    glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.13, 0.15, 50, 50);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 0.33, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.2, 0.22, 50, 50);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 0.17, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.26, 0.3, 50, 50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0.0, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.30, 0.35, 50, 50);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, -0.17, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.34, 0.4, 50, 50);
    glPopMatrix();
    
   glPushMatrix();
        glTranslatef(0, -0.33, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.38, 0.42, 50, 50);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, -0.5, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.44, 0.46, 50, 50);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, -0.67, 0);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(0.48, 0.48, 50, 50);
    glPopMatrix();

    // parameters for material of the tree (scape) 
    GLfloat ambient_coeffs1[] = { 0.545, 0.271, 0.075, 1 };
    GLfloat diffuse_coeffs1[] = { 0.545, 0.271, 0.075, 1 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs1);
    

    // here we use helper function for drawing of 
    // cylinder (scape) of the tree
    glPushMatrix();
        float u, v;
        glScalef(0.1, 0.7, 0.1);
        glTranslatef(0, -2.8, 0);
        for (u = 0; u < PI/2; u += PI / 20) {
        glBegin(GL_TRIANGLE_STRIP);
        for (v = 0; v <= PI*2 + EPSILON; v += PI / 20) {
            set_normal_and_vertex(u, v);
            set_normal_and_vertex(u + PI / 20, v);
        }
        glEnd();
    }
    glPopMatrix();

    glDisable(GL_LIGHTING);
}

void type2() {

	glEnable(GL_NORMALIZE);

	GLfloat light_position[] = { 1, 1, 1, 0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    GLfloat ambient_coeffs[] = { 0.1, 0.6, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0.1, 0.6, 0.1, 1 };
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    GLfloat shininess = 40;

    // setting of light and materials
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
    
    // here we draw canopy of the tree
    glPushMatrix();
        glTranslatef(0, 1, 0);
        glutSolidSphere(0.4, 50, 50);
    glPopMatrix();

    // parameters for material of the tree (scape)
    GLfloat ambient_coeffs1[] = { 0.545, 0.271, 0.075, 1 };
    GLfloat diffuse_coeffs1[] = { 0.545, 0.271, 0.075, 1 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs1);
    
    //koristim pomocnu funkciju za crtanje cilindra/stabla
    glPushMatrix();
        float u, v;
        glColor3f(0.545, 0.271, 0.075);
        glScalef(0.06, 0.3, 0.06);
        for (u = 0; u < PI; u += PI / 20) {
        glBegin(GL_TRIANGLE_STRIP);
        for (v = 0; v <= PI*2 + EPSILON; v += PI / 20) {
            set_normal_and_vertex(u, v);
            set_normal_and_vertex(u + PI / 20, v);
        }
        glEnd();
    }
    glPopMatrix();
}

void draw_tree(int id, float x, float y, float z) {
	switch(id) {
		case 1:
            // if id is 1 then we draw fir tree
			glPushMatrix();
				glTranslatef(x, y, z);
				glScalef(1.5, 2, 1.5);
				type1();
			glPopMatrix();
			break;
		case 2:
            // if id is 2 then we draw tree with a canopy
			glPushMatrix();
				glTranslatef(x, y, z);
				glScalef(2, 1.8, 2);
				type2();
			glPopMatrix();
			break;
	}

}