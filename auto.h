#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h> 

// svaka funkcija ima argumente x, y, z
// zato sto pozivam vise puta istu funkciju,
// a jedino sto menjam su koordinate objekta

void draw_sidewindow1(float x, float y, float z);
void draw_backlamp1(float x, float y, float z);
void draw_windsheild1(float x, float y, float z);
void draw_headlamp1(float x, float y, float z);
void draw_wheel1(float x, float y, float z);
void draw_body1();
void draw_car1();