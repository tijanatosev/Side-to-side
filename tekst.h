#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <string.h>

// sve funkcije koriste funkciju glutBitmapCharacter() koja ispisuje tekst
// koji je prosledjen kao string pokazivac

// za ispisivanje "GOOD BYE" kada se pritisne ESC
void bye(void);
// za ispisivanje "PRESS G TO START THE GAME"
void begining(void);
// za ispisivanje "GAME OVER" kada korisnik izgubi sve zivote
void gameover(void);
// za ispisivanje "PRESS G TO UNPAUSE" kada korisnik pritisne taster p
void paused(void);
// za ispisivanje "THANK YOU FOR PLAYING" pre izlaska iz igre
void thankyou(void);