#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

// to this function are forwarded:
// 		- X and Z coordiantes of the player
// 		- X and Z coordinates of the car
// 		- width and length of the car

int collision_detection(float x_prev, float z_prev, float tmpx, float tmpz, float w, float l);