#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

// ovoj funkciji se prosledjuju:
//		x i z koordinate igraca
//		x i z koordinate kola
//		sirina i duzina kola

int collision_detection(float x_prev, float z_prev, float tmpx, float tmpz, float w, float d);