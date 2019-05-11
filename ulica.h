#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

void draw_strips(float length);
void draw_sidewalk(float length, float d, float w1, float w2);
void draw_line(float length, float w1, float w2, float d);
void draw_floor(float length, float w1, float w2);
void draw_street();