#include "text.h"

// variable begining indicates the start of the program, which means that
// the program already started
extern int beginning;

// function immediately after running the program writes instructions
// for starting the animation
void begining(void) {
    glPushMatrix();
        const char *startgame = "PRESS  G  TO  START  THE  GAME";
        int length = strlen(startgame);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 1);
        glRasterPos2f(-3.5, 1.05);
        for (p = 0; p < length; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, startgame[p]);
        }
    glPopMatrix();
    beginning = 0;
}

// function is called when button >ESC< is pressed and then message
// "GOOD BYE" is written
void bye(void) {
    glPushMatrix();
        const char *endgame = "GOOD  BYE";
        int length = strlen(endgame);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 1);
        glRasterPos2f(-1.35, 1.05);
        for (p = 0; p < length; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, endgame[p]);
        }
    glPopMatrix();
}


// this function writes text "GAME OVER" when player loses all lives
void gameover(void) {
    glPushMatrix();
        const char *gameover ="GAME OVER";
        int length = strlen(gameover);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 1);
        glRasterPos2f(-1.05, 1.05);
        for (p = 0; p < length; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameover[p]);
        }
    glPopMatrix();
}

// this function is called when button >p< is pressed and writes 
// text "PRESS G TO UNPAUSE"
void paused(void) {
    glPushMatrix();
        const char *paused ="PRESS  G  TO  UNPAUSE";
        int length = strlen(paused);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 1);
        glRasterPos2f(-2.45, 1.05);
        for (p = 0; p < length; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, paused[p]);
        }
    glPopMatrix();
}

// this function is called when function bye() is called (on leaving the
// game) and text "THANK YOU FOR PLAYING" is written 
void thankyou(void) {
    glPushMatrix();
        const char *thanks ="THANK  YOU  FOR  PLAYING";
        int length = strlen(thanks);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 5);
        glRasterPos2f(-2.1, 1.05);
        for (p = 0; p < length; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, thanks[p]);
        }
    glPopMatrix();
} 