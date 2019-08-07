#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <unistd.h>

#include "street.h"
#include "player.h"
#include "truck.h"
#include "car.h"
#include "collisions.h"
#include "image.h"
#include "grass.h"
#include "points.h"
#include "trees.h"
#include "text.h"

#define FILENAME0 "4.bmp"

// array for structures
GLuint names[1];

#define TIMER_ID 0
#define TIMER_INTERVAL 20
#define max 20

// struct for red car - first lane
typedef struct Red{
	// x, y, z coordinates
	float x_curr, y_curr, z_curr;
	// width and length
	float w, l;
	// id of the car in the lane
	int id;
}Red;

// struct for blue car - second lane
typedef struct Blue{
	// x, y, z coordinates
	float x_curr, y_curr, z_curr;
	// parameters width and length
	float w, l;
	// if of the car in the lane
	int id;
}Blue;

// struct for the cars in third lane - blue and red cars
typedef struct Combination{
	// x, y, z coordinates
	float x_curr, y_curr, z_curr;
	// parameters width and length
	float w, l;
	// id of the cars in the lane
	int id;
}Combination;

// struct for previous coordinates of objects 
typedef struct prev{
	float x_prev, y_prev, z_prev;
	float w, l;
}prev;

// arrays for creating cars
struct Red red_cars[max];
struct Blue blue_cars[max];
struct Combination comb_cars[max];

// arrays for previous coordinates of the cars
struct prev aprev[max];
struct prev bprev[max];
struct prev cprev[max];

static int window_width, window_height;
// indicator of animation
static int animation_ongoing;

// parameters for the lanes - moving the cars
static float a[max]; // I
static float b[max]; // II
static float c[max]; // III

static int i;

// coordinates for the lanes
static float t1 = 3.8;
static float t2 = 2.6;

// position of the player when he crosses on 
// the other side of the street
float end = 0.2; 

// at the beginning player has 3 lives
int life = 3;

// this variable is indicator for drawing text "GAME OVER" 
// and animation doesn't shut down immediately but it waits 
// 1 ms and then closes with exit(1)
int dead = 0;

// this variable is indicator for when program just started 
// and none of the keys aren't pressed still
int beginning = 1;

// this variable is indicator which is used when key >>ESC<<
// is pressed so function bye() could be called
int exiting = 0;

// this indicator is used when key >>p<< is pressed and
// function paused() could be called
int game_pause = 0;

// coordinates for the player - current
float pX = 0;
float pY = 0.4;
float pZ = 5.0;

// previous coordintaes for the player
static float x_prev;
static float y_prev;
static float z_prev;

// callback functions
static void on_keyboard(unsigned char c, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer();

// funciton that exits the program after player loses all the lives
static void done(void);

// function for drawing cars on the street
static void cars();

// fumction for initialization of the textures
static void initialize(void);

// function for initialization arrays and coordinates
static void init(int ind);

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(1200, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("side-to-side");

	glutKeyboardFunc(on_keyboard);
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);

	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	init(0);
	initialize();

	glutMainLoop();

	return 0;
}

static void init(int ind) {
	if (ind == 0) {	
		// this if is used if we called init() from the main or for resetting the animation,
		// here we set:
		// 		life and current coordinates for the player 
		// in case we called init() for drawing cars again then we don't need to change life 
		// and current coordinates of the player
		life = 3;
		pX = 0;
		pY = 0.4;
		pZ = 5.0;
	}
	int k;
	// initialization of the cars 
	for(k = 0; k < max; k++) {
		red_cars[k].x_curr = 0;
		red_cars[k].y_curr = 0.8;
		red_cars[k].z_curr = 4;
		red_cars[k].w = 1.5;
		red_cars[k].l = 1;
		red_cars[k].id = k;

		blue_cars[k].x_curr = 0;
		blue_cars[k].y_curr = 0.8;
		blue_cars[k].z_curr = 2.8;
		blue_cars[k].w = 2;
		blue_cars[k].l = 1;
		blue_cars[k].id = k;
	
		comb_cars[k].x_curr = 0;
		comb_cars[k].y_curr = 0.8;
		comb_cars[k].z_curr = 1.7;
		if (k % 2 == 0) {
			comb_cars[k].w = 2.0;
		}
		else {
			comb_cars[k].w = 1.5;
		}
		comb_cars[k].l = 1;
		comb_cars[k].id = k;
	}

	int m;
	// this for is used for setting initial position of the cars
	for (m = 0; m < max; m++) {
		a[m] = 21;
		b[m] = 20;
		c[m] = 22;
	}
    
    // returning variable life at initial state
    life = 3;
}

void initialize(void)
{
	// function initialize is taken from class "Computers graphics"

    // object that represents texture loaded from the file
    Image * image;

    // enabling textures
    glEnable(GL_TEXTURE_2D);

    // setting mode of drawing the textures
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // initialization of image object
    image = image_init(0, 0);

    // creating the texture
    image_read(image, FILENAME0);

    // generating indetificator of the texture
    glGenTextures(1, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    // closing the active texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // destroying object for reading the texture from file
    image_done(image);

    // initialization of rotation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void on_keyboard(unsigned char c, int x, int y) {
	switch(c) {
		case 27:
			// indicator that key >>ESC<< is pressed and function 
			// bye() should be called
            exiting = 1;
            
            // this if is used to check if before this key >>p<< was
            // pressed and if it was we change pause to 0 and new text
            // won't be written over already written text
            if (game_pause == 1)
                game_pause = 0;
            
            // function on_display() is called again so text about exiting 
            // the animation is written
            on_display();
            sleep(1);
			glDeleteTextures(1, names);
			exit(0);
			break;

		case 'd':
		case 'D':
			// moving the player to the right and he can move only to
			// the right where the street is shown
			glPushMatrix();
				if (pX >= 9) {
					pX = 0;
					life--;
				}
				pX += 1;
			glPopMatrix();
			glutPostRedisplay();
			break;

		case 'a':
		case 'A':
			// moving the player to the left and he can move only to
			// the left where the street is shown
			glPushMatrix();
				if (pX <= -9) {
					pX = 0;
					life--;
				}
				pX -= 1;
			glPopMatrix();
			glutPostRedisplay();
			break;

		case 'w':
		case 'W':
			// moving player forward 
			glPushMatrix();
				if (pZ <= 0.2) {
					pZ = 6.2;
				}
				pZ -= 1.2;
			glPopMatrix();
			glutPostRedisplay();
			break;

		case 's':
		case 'S':
			// moving player backward
			glPushMatrix();
				if (pZ >= 4.0) {
					pZ = 3.8;
				}
				pZ += 1.2;
				glPopMatrix();
			glutPostRedisplay();
			break;

		case 'g':
        case 'G':
        	// pokretanje animacije i postavljanje indikatora pause na 0
            // kako se ne bi iscrtavala poruka "PRESS G TO UNPAUSE"

        	// starting the animation and setting indicator pause to 0
        	// because we don't want to show message "PRESS G TO UNPAUSE"
        	// on the screen
            game_pause = 0;
            if (!animation_ongoing) {
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
				animation_ongoing = 1;
			}
			break;

		case 'p':
		case 'P':
			// stopping animation
            game_pause = 1;
			animation_ongoing = 0;
			break;

		case 'r':
		case 'R':
			// resetting animation
			init(0);
			animation_ongoing = 1;
			break;
	}
}

static void on_reshape(int width, int height) {
	window_width = width;
	window_height = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, window_width, window_height);
	gluPerspective(60, (float) window_width / window_height, 1, 100);
	glMatrixMode(GL_MODELVIEW);
}

static void done() {
    // here we call function sleep because we want to show message
    // on the screen and then to shut down animation
    sleep(1);
    glDeleteTextures(1, names);
    exit(1);
}

static void on_display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 9, 7 + pZ/3, 
			  0, 0, pZ/4,
			  0, 1, 0);

    // checking if program started and calling function that
    // draws instructions for beginning the animation
    if (beginning == 1)
        begining();

    // checking if key >>ESC<< is pressed and calling function
    // that draws messages "GOOD BYE" and "THANK YOU FOR PLAYING"
    if (exiting == 1) {
        bye();
        thankyou();
    }
    
    // checking if animation is paused
    if (game_pause == 1)
        paused();
    

    // here are to planes that cut off end of the street on both sides
    // so it seems like cars are getting out of the tunnel
	glPushMatrix();
		double clip_plane0[] = {1, 0, 0, 0};
		glTranslatef(-25, 0, 0);
    	glClipPlane(GL_CLIP_PLANE0, clip_plane0);
    glPopMatrix();

    glPushMatrix();
		double clip_plane1[] = {-1, 0, 0, 0};
		glTranslatef(25, 0, 0);
    	glClipPlane(GL_CLIP_PLANE1, clip_plane1);
    glPopMatrix();
    
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);

    // placing street on the screen
	glPushMatrix();
		glTranslatef(-28, 0, 0);
		draw_street();
	glPopMatrix();

	// placing the player on initial position
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		player(pX, pY, pZ);
	glPopMatrix();

	// placing grass on the screen
	draw_grass();

	// drawing points on the screen
	draw_points();

	// placing trees on the screen 
	glPushMatrix();
		draw_tree(1, -17, 2, -7);
		draw_tree(1, 18, 2, -9);
		draw_tree(1, 12, 2, -5);
		draw_tree(1, 7, 2, -7);
		draw_tree(1, -3, 2, -3);
		draw_tree(1, -2, 2, -10);
		draw_tree(1, -6, 2, 7);
		draw_tree(2, -8, 0, -8);
		draw_tree(2, 11, 0, -11);
		draw_tree(2, 1, 0, -1);
		draw_tree(2, 7, 0, -2);
		draw_tree(2, -13, 0, -2);
		draw_tree(2, -5, 0, -1);
		draw_tree(2, 4, 0, 6.5);
	glPopMatrix();

	// function for drawing cars on the street
	cars();

	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	
    // here we check if the player lost all his lives and if so message is
    // drawn on the screen and after that window is closed
    if (life == 0) {
        // function gameover() draws text "GAME OVER"
        gameover();
        dead += 1;
        // this call of glutPostRedisplay() is needed because value of indicator
        // dead must change so it can go to other if and call function done()
        glutPostRedisplay();
    }
    
    // this indicator dead is used for waiting to draw text on the screen
    // and to wait to close the window
    if (dead > 2)
        done();
    
	glutSwapBuffers();
}

static void cars() {
	// in this function we draw cars on the street

	// if the last car in the third lane got to the position when x coordinate
	// is greater of equal to 45 then function init() is called and moving of
	// the cars start start from the beginning 
	if (comb_cars[20].x_curr >= 35) {
		init(1);
		animation_ongoing = 1;
		glutPostRedisplay();
	}

	// for each lane new coordinates are calculated for the cars based on the
	// paremeters specified for each lane
	for (i = 0; i < max; i++) {
		glPushMatrix();
			// we substract i*4 so the cars are separated by space
			red_cars[i].x_curr = a[i] - i*4;
			red_cars[i].w *= 0.7;
			red_cars[i].l *= 0.7;
			glTranslatef(red_cars[i].x_curr, red_cars[i].y_curr, red_cars[i].z_curr);
			glScalef(0.7, 0.7, 0.7);
			draw_truck();
		glPopMatrix();

		glPushMatrix();
			blue_cars[i].x_curr = b[i] - i*4;
			blue_cars[i].w *= 0.7;
			blue_cars[i].l *= 0.7;
			glTranslatef(blue_cars[i].x_curr, blue_cars[i].y_curr, blue_cars[i].z_curr);
			glScalef(0.7, 0.7, 0.7);
			draw_car1();
		glPopMatrix();

		glPushMatrix();
			comb_cars[i].x_curr = c[i] - i*4;
			comb_cars[i].w *= 0.7;
			comb_cars[i].l *= 0.7;
			glTranslatef(comb_cars[i].x_curr, comb_cars[i].y_curr, comb_cars[i].z_curr);
			glScalef(0.7, 0.7, 0.7);
			// based on indicator i we draw red or blue car
			if (i % 2 == 0) {
				draw_car1();
			}
			else {
				draw_truck();
			}
		glPopMatrix();
	}
}

static void on_timer() {

	int j;
    for (j = 0; j < max; j++) {
    	// we store current coordinates of the cars because we need it for
    	// detection of collisions with the player
    	aprev[j].x_prev = red_cars[j].x_curr;
    	aprev[j].y_prev = red_cars[j].y_curr;
    	aprev[j].z_prev = red_cars[j].z_curr;
    	aprev[j].w = red_cars[j].w;
    	aprev[j].l = red_cars[j].l;

    	bprev[j].x_prev = blue_cars[j].x_curr;
    	bprev[j].y_prev = blue_cars[j].y_curr;
    	bprev[j].z_prev = blue_cars[j].z_curr;
    	bprev[j].w = blue_cars[j].w;
    	bprev[j].l = blue_cars[j].l;

    	cprev[j].x_prev = comb_cars[j].x_curr;
    	cprev[j].y_prev = comb_cars[j].y_curr;
    	cprev[j].z_prev = comb_cars[j].z_curr;
    	cprev[j].w = comb_cars[j].w;
    	cprev[j].l = comb_cars[j].l;
    	
    	a[j] += 0.08;
    	b[j] += 0.06;
    	c[j] += 0.08;
    }
    // we store current coordinates of the player because we need it for
    // checking of collisions of the player and the cars
    x_prev = pX;
    y_prev = pY;
    z_prev = pZ;

    // here we check if collision happend on specific lane and if so
    // then the player is placed on initial position and he loses one life
	for (j = 0; j < max; j++) {
		if (z_prev == t1) {
			// if the player is in the first lane we check for collisions
			if (collision_detection(x_prev, z_prev, aprev[j].x_prev, aprev[j].z_prev, aprev[j].w, aprev[j].l) != 0) {
	    		pX = 0;
	    		pZ = 5;
	    		if (life == 0) {
	    			animation_ongoing = 0;
	    			break;
	    		}
	    		life--;
	    		break;
    		}
    	}
	    else if (z_prev == t2) {
	    	// if the player is in the second lane we check for collisions
	    	if (collision_detection(x_prev, z_prev, bprev[j].x_prev, bprev[j].z_prev, bprev[j].w, bprev[j].l) != 0) {
	    		pX = 0;
	    		pZ = 5;
	    		if (life == 0) {
					animation_ongoing = 0;
	    			break;
	    		}
	    		life--;
	    		break;
    		}
    	}
    	else if (z_prev != t1 && z_prev != t2) {
    		// if the player is in the third lane we check for collisions
    		if (collision_detection(x_prev, z_prev, cprev[j].x_prev, cprev[j].z_prev, cprev[j].w, cprev[j].l) != 0) {
    			pX = 0;
    			pZ = 5;
    			if (life == 0) {
					animation_ongoing = 0;
	    			break;
    			}
    			life--;
    			break;
    		}
    	}
	}
	// if the player lost all of the lives then we exit the animation but
	// before the calling of function gameover() we have to call function
	// on_display()
	if (life == 0) {
        draw_points();
		animation_ongoing = 0;
        dead = 1;
	}


	// if player got to the other side of the street then he gets a life
	// and it's placed on the initial position
	if (fabs(z_prev - end) < 0.000001) {
		life++;
		pX = 0;
		pZ = 5;
	}

	glutPostRedisplay();

	if (animation_ongoing) {
		glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
	}
}
