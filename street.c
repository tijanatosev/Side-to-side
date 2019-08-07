#include "street.h"

void draw_floor(float length, float w1, float w2) {
	glPushMatrix();
		glColor3f(0.25, 0.25, 0.25);
		glBegin(GL_POLYGON);
			glVertex3f(   0.0,  0.0, w1);
			glVertex3f(   0.0,  0.0, w2);
			glVertex3f(length,  0.0, w2);
			glVertex3f(length,  0.0, w1);
		glEnd();
	glPopMatrix();
}

void draw_line(float length, float w1, float w2, float d) {
// sidewalkd
	glPushMatrix();
		glColor3f(0.1, 0.1, 0.1);
		glLineWidth(4);
		glBegin(GL_LINES);
			glVertex3f(   0.0, 0.0001, w1 + d);
			glVertex3f(length, 0.0001, w1 + d);
			glVertex3f(   0.0, 0.0001, w2 - d);
			glVertex3f(length, 0.0001, w2 - d);
		glEnd();
	glPopMatrix();
}

void draw_sidewalk(float length, float d, float w1, float w2) {
	// further
	glPushMatrix();
		glColor3f(0.15, 0.15, 0.15);
		glBegin(GL_POLYGON);
			glVertex3f(   0.0, 0.001, w1);
			glVertex3f(	  0.0, 0.001, w1 + d);
			glVertex3f(length, 0.001, w1 + d);
			glVertex3f(length, 0.001, w1);
		glEnd();
	glPopMatrix();
	
	// near
	glPushMatrix();
		glColor3f(0.15, 0.15, 0.15);
		glBegin(GL_POLYGON);
			glVertex3f(   0.0, 0.001, w2 - d);
			glVertex3f(   0.0, 0.001, w2);
			glVertex3f(length, 0.001, w2);
			glVertex3f(length, 0.001, w2 - d);
		glEnd();
	glPopMatrix();
}

void draw_strips(float length) {
	glPushMatrix();
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glLineWidth(2);
			double i = 0.0;
			int k = 0;
			while(i <= length) {
				glVertex3f(i, 0.0001, 1.9);
				k++;
				if (k == 2) {
					// if two dots are drawn add space for the next two
					k = 0;
					i += 0.5;
				}
				else {
					i += 1.2;
				}
			}
			i = 0.0;
			k = 0;
			while(i <= length) {
				glVertex3f(i, 0.0001, 3.1);
				k++;
				if (k == 2) {
					k = 0;
					i += 0.5;
				}
				else {
					i += 1.2;
				}
			}
		glEnd();
	glPopMatrix();
}

void draw_street() {
	// when we are choosing length of the street then we have to calculate
	// how many strips on the street will be drawn
	// example: if we want 15 strips then first we multiply 15 with 1.2, 
	// after that we want 14 spaces between the strips and we multiply
	// 14 with 0.5, finanlly we add those numbers and get: 25

	draw_floor(59.1, -0.5, 5.5);
	
	draw_line(59.1, -0.5, 5.5, 1.2);

	draw_sidewalk(59.1, 1.2, -0.5, 5.5);

	draw_strips(59.1);
}