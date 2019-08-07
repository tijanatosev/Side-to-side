#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <string.h>


// all function are using function glutBitmapCharacter() which writes 
// text that is forwarded as a string pointer

// for writing "GOOD BYE" when >ESC< is pressed
void bye(void);
// for writing "PRESS G TO START THE GAME" 
void begining(void);
// for writing "GAME OVER" when player loses all lives
void gameover(void);
// for writing "PRESS G TO UNPAUSE" when >p< is pressed
void paused(void);
// for writing "THANK YOU FOR PLAYING" before exiting the game
void thankyou(void);