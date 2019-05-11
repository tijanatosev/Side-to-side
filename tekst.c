#include "tekst.h"

// indikator koji oznacava pocetak programa, tj da je program tek pokrenut
extern int pocetak;

// funkcija koja odmah nakon pokretanja programa ispisuje instrukciju za 
// pokretanje animacije
void begining(void) {
    glPushMatrix();
        const char *startgame = "PRESS  G  TO  START  THE  GAME";
        int duzina = strlen(startgame);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 1);
        glRasterPos2f(-3.5, 1.05);
        for (p = 0; p < duzina; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, startgame[p]);
        }
    glPopMatrix();
    pocetak = 0;
}

// funkcija koja se poziva u situaciji kada je pritisnut taster esc kako
// bi se ispisala poruka "GOOD BYE"
void bye(void) {
    glPushMatrix();
        const char *endgame = "GOOD  BYE";
        int duzina = strlen(endgame);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 1);
        glRasterPos2f(-1.35, 1.05);
        for (p = 0; p < duzina; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, endgame[p]);
        }
    glPopMatrix();
}

// funkcija koja ispisuje tekst kada je korisnik izgubio sve zivote
void gameover(void) {
    glPushMatrix();
        const char *gameover ="GAME OVER";
        int duzina = strlen(gameover);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 1);
        glRasterPos2f(-1.05, 1.05);
        for (p = 0; p < duzina; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gameover[p]);
        }
    glPopMatrix();
}

// funkcija koja ispisuje tekst "PRESS G TO UNPAUSE" i koja se poziva kada
// je pritisnut taster p
void paused(void) {
    glPushMatrix();
        const char *paused ="PRESS  G  TO  UNPAUSE";
        int duzina = strlen(paused);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 1);
        glRasterPos2f(-2.45, 1.05);
        for (p = 0; p < duzina; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, paused[p]);
        }
    glPopMatrix();
}

// funkcija koja ispisuje tekst "THANK YOU FOR PLAYING" i koja se poziva
// kada se poziva i funkcija bye(), odnosno na izlasku iz igre
void thankyou(void) {
    glPushMatrix();
        const char *thanks ="THANK  YOU  FOR  PLAYING";
        int duzina = strlen(thanks);
        int p;
        glColor3f(0.62352, 0.372549, 0.623529);
        glTranslatef(0, 0, 5);
        glRasterPos2f(-2.1, 1.05);
        for (p = 0; p < duzina; p++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, thanks[p]);
        }
    glPopMatrix();
} 