#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

// TODO: promeniti naziv fajla - vise ne izgleda kao kamion 

// svaka funkcija ima argumente x, y, z
// zato sto pozivam vise puta istu funkciju,
// a jedino sto menjam su koordinate objekta

void draw_sidewindow(float x, float y, float z);
void draw_backlamp(float x, float y, float z);
void draw_windsheild(float x, float y, float z);
void draw_headlamp(float x, float y, float z);
void draw_wheel(float x, float y, float z);
void draw_body();
void draw_truck();