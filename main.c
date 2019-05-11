#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <unistd.h>

#include "ulica.h"
#include "igrac.h"
#include "kamion.h"
#include "auto.h"
#include "kolizije.h"
#include "image.h"
#include "trava.h"
#include "poeni.h"
#include "drvece.h"
#include "tekst.h"

#define FILENAME0 "4.bmp"

//niz za strukture
GLuint names[1];

#define TIMER_ID 0
#define TIMER_INTERVAL 20
#define max 20

//struktura za crvena kola - prva traka
typedef struct Kamion{
	//x, y, z koordinate 
	float x_curr, y_curr, z_curr;
	//parametri sirine i duzine
	float w, d;
	//oznaka kamiona u nizu
	int id;
}Kamion;

//struktura za plava kola - druga traka
typedef struct Kola{
	//x, y, z koordinate 
	float x_curr, y_curr, z_curr;
	//parametri sirine i duzine
	float w, d;
	//oznaka kola u nizu
	int id;
}Kola;

//struktura za kombinovana crvena i plava kola - treca traka
typedef struct Oba{
	//x, y, z koordinate 
	float x_curr, y_curr, z_curr;
	//parametri sirine i duzine
	float w, d;
	//oznaka automobila u nizu
	int id;
}Oba;

//struktura koja sluzi za prethodne koordinate objekata
typedef struct prev{
	float x_prev, y_prev, z_prev;
	float w, d;
}prev;

// potrebni nizovi za pravljenje kola
struct Kamion kamioni[max];
struct Kola kola[max];
struct Oba oba[max];

// nizovi za prethodne koordinate kola
struct prev aprev[max];
struct prev bprev[max];
struct prev cprev[max];

static int window_width, window_height;
// indikator animacije
static int animation_ongoing;

// parametri za trake - pomeranje kola
static float a[max]; // I
static float b[max]; // II
static float c[max]; // III

static int i;

// koordinate za trake
static float t1 = 3.8;
static float t2 = 2.6;
float kraj = 0.2; //pozicija kad igrac predje na drugu stranu

//igrac na pocetku ima 3 zivota
int zivot = 3;

// indikator koji sluzi za crtanje teksta game over
// kako se animacija ne bi odmah ugasila vec da saceka 1 milisekundu
// i onda da se ugasi animacija pomocu exit(1);
int poginuo = 0;

// indikator koji govori da je program upravo pokrenut i da nije
// pritisnut nijedan taster jos uvek
int pocetak = 1;

// indikator koji oznacava da je pritisnut taster esc i kako bi se
// pozvala funkcije bye()
int izlazak = 0;

// indikator koji oznacava da je pritisnut taster p i da bi se zato
// pozvala funkcija paused() i ispisao odgovarajuci tekst
int pauza = 0;

//	koordinate za igraca - curr
float pX = 0;
float pY = 0.4;
float pZ = 5.0;

// prethodne koordinate za igraca - prev
static float x_prev;
static float y_prev;
static float z_prev;

// callback funkcije
static void on_keyboard(unsigned char c, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer();

// funkcija koja izlazi iz programa nakon sto igrac izgubi sve zivote
static void gotovo(void);

// funkcija za crtanje kola na tabli
static void cars();

// funkcija za inicijalizaciju texutura
static void initialize(void);

// funkcija za inicijalizaciju nizova i koordinata
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
		// ovaj if sluzi ako smo pozvali init iz main-a ili zbog resetovanja animacije,
		// da postavi vrednosti koordinata na pocetne i da postavi zivote na 3,
		// a smo pozvali init zbog pokretanja kola ispocetka onda je potrebno da ne menjamo
		// vrednost zivota i da ne vracamo igraca na pocetnu poziciju
		zivot = 3;
		pX = 0;
		pY = 0.4;
		pZ = 5.0;
	}
	int k;
	//inicijaliziju se parametri kola
	for(k = 0; k < max; k++) {
		kamioni[k].x_curr = 0;
		kamioni[k].y_curr = 0.8;
		kamioni[k].z_curr = 4;
		kamioni[k].w = 1.5;
		kamioni[k].d = 1;
		kamioni[k].id = k;

		kola[k].x_curr = 0;
		kola[k].y_curr = 0.8;
		kola[k].z_curr = 2.8;
		kola[k].w = 2;
		kola[k].d = 1;
		kola[k].id = k;
	
		oba[k].x_curr = 0;
		oba[k].y_curr = 0.8;
		oba[k].z_curr = 1.7;
		if (k % 2 == 0) {
			oba[k].w = 2.0;
		}
		else {
			oba[k].w = 1.5;
		}
		oba[k].d = 1;
		oba[k].id = k;
	}

	int m;
	//petlja za odredjivanje pocetne pozicije kola
	for (m = 0; m < max; m++) {
		a[m] = 21;
		b[m] = 20;
		c[m] = 22;
	}
    
    //vracanje zivota na pocetno stanje
    zivot = 3;
}

void initialize(void)
{
	// funkcija initialize je preuzeta sa casa
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    /*
     * Podesava se rezim iscrtavanja tekstura tako da boje na teksturi
     * potpuno odredjuju boju objekata.
     */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(1, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);

    /* Inicijalizujemo matricu rotacije. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void on_keyboard(unsigned char c, int x, int y) {
	switch(c) {
		case 27:
            // indikator da je pritisnut taster esc i za pozivanje
            // funkcije bye();
            izlazak = 1;
            // provera ako je pre toga bio pritisnut taster p i ako
            // jeste promena indikatora pauza na 0 kako se ne bi ispisao
            // novi tekst preko vec napisanog teksta
            if (pauza == 1)
                pauza = 0;
            // moram ponovo da pozovem funkciju on_display() kako bi se 
            // iscrtala poruka o prekidanju programa
            on_display();
            sleep(1);
			glDeleteTextures(1, names);
			exit(0);
			break;
		case 'd':
		case 'D':
			//pomeranje igraca desno
			//igrac moze da se krece desno samo onim delom ulice koji je vidljiv
			glPushMatrix();
				if (pX >= 9) {
					pX = 0;
					zivot--;
				}
				pX += 1;
			glPopMatrix();
			glutPostRedisplay();
			break;
		case 'a':
		case 'A':
			//pomeranje igraca levo
			//igrac moze da se krece levo samo onim delom ulice koji je vidljiv
			glPushMatrix();
				if (pX <= -9) {
					pX = 0;
					zivot--;
				}
				pX -= 1;
			glPopMatrix();
			glutPostRedisplay();
			break;

		case 'w':
		case 'W':
			//pomeranje igraca napred
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
			//pomeranje igraca napred
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
        	// pokretanje animacije i postavljanje indikatora pauza na 0
            // kako se ne bi iscrtavala poruka "PRESS G TO UNPAUSE"
            pauza = 0;
            if (!animation_ongoing) {
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
				animation_ongoing = 1;
			}
			break;

		case 'p':
		case 'P':
			// zaustavljanje animacije
            pauza = 1;
			animation_ongoing = 0;
			break;

		case 'r':
		case 'R':
			// resetovanje animacije
			// nije potrebno ponovo pokretanje animacije kada se resetuje
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

static void gotovo() {
    // funkcija koja poziva sleep kako bi se videla iscrtana poruka
    // i zatim ugasila animacija
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

    // provera da li je tek pokrenut program i pozivanje funkcije koja
    // ispisuje instrukciju za pokretanje animacije
    if (pocetak == 1)
        begining();  
    
    // provera da li je pritisnut taster esc i pozivanje funkcije koja
    // ispisuje tekst na ekranu "GOOD BYE" i "THANK YOU FOR PLAYING"
    if (izlazak == 1) {
        bye();
        thankyou();
    }
    
    // provera da li je pritisnut taster p i pozivanje funkcije paused()
    // koja ispisuje tekst "PRESS G TO UNPAUSE"
    if (pauza == 1)
        paused();
    
	glPushMatrix();
		//dodala sam ravan koja odseca kraj ulice kako bi
		//izgledalo kao da automobili izlaze iz tunela
		double clip_plane0[] = {1, 0, 0, 0};
		glTranslatef(-25, 0, 0);
    	glClipPlane(GL_CLIP_PLANE0, clip_plane0);
    glPopMatrix();

    glPushMatrix();
		//dodala sam ravan koja odseca kraj ulice kako 
    	//se ne bi videlo da izlaze
		double clip_plane1[] = {-1, 0, 0, 0};
		glTranslatef(25, 0, 0);
    	glClipPlane(GL_CLIP_PLANE1, clip_plane1);
    glPopMatrix();
    
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);

    //postavljam ulicu na tablu
	glPushMatrix();
		glTranslatef(-28, 0, 0);
		draw_street();
	glPopMatrix();

	//postavljam igraca na tablu
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		player(pX, pY, pZ);
	glPopMatrix();

	//poziva se funkcija za crtanje trave
	draw_grass();
    
	//poziva se funkcija za crtanje zivota igraca
	//koji se nalaze iznad table i kako se pomera igrac 
	//tako se i pomeraju zivoti
	draw_points();

	//postavljam drvece na tablu
	//(pokusala sam jos drveca da nacrtam ali jako usporava kretanja
	// tako da sam nacrtala samo na onom delu table koji je vidljiv 
	// u odnosu na poziciju kamere)
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

	//funkcija za iscrtavanje kola na ulici
	cars();

	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	
    
    // provera da li je igrac izgubio sve zivote kako bi se ispisao tekst 
    // "GAME OVER" i nakon toga izaslo iz prozora
    if (zivot == 0) {
        // poziv funkcije koja ispisuje tekst "GAME OVER"
        gameover();
        poginuo += 1;
        // ovaj poziv glutPostRedisplay() je potreban kako bi se promenila
        // vrednost indikatora poginuo i na taj nacin usao u if i pozvao 
        // funkciju gotovo
        glutPostRedisplay();
    }
    
    // koristi se indikator poginuo kako bi se sacekalo da se ispise tekst
    // na ekranu i kako se ne bi odmah iskljucio prozor 
    if (poginuo > 2)
        // poziv funkcije koja izlazi iz programa i izvrsava sleep()
        gotovo();
    
	glutSwapBuffers();
}
// funkcija za iscrtavanje kola i kamiona na ulici
static void cars() {
	// ako je poslednji kamion u trecoj traci dosao do pozicije kada je
	// x koordinata >= 45 onda se poziva funkcija init
	// i kretanje kola pocinje iz pocetka
	// (nisam uspela nikako drugacije da namestim kretanje kola ispocetka
	//  osim na ovaj nacin, tako da kad se to dogodi jasno se vidi da se
	//  dogodila ova inicijalizacija)
	if (oba[20].x_curr >= 35) {
		init(1);
		animation_ongoing = 1;
		glutPostRedisplay();
	}
	// za svaku traku se racunaju nove koordinate kola na osnovu parametra
	// koji je odredjen za svaku traku
	for (i = 0; i < max; i++) {
		glPushMatrix();
			kamioni[i].x_curr = a[i] - i*4; //oduzimam i*4 kako bi kamioni bili razdvojeni
			kamioni[i].w *= 0.7;
			kamioni[i].d *= 0.7;
			glTranslatef(kamioni[i].x_curr, kamioni[i].y_curr, kamioni[i].z_curr);
			glScalef(0.7, 0.7, 0.7);
			draw_truck();
		glPopMatrix();

		glPushMatrix();
			kola[i].x_curr = b[i] - i*4;
			kola[i].w *= 0.7;
			kola[i].d *= 0.7;
			glTranslatef(kola[i].x_curr, kola[i].y_curr, kola[i].z_curr);
			glScalef(0.7, 0.7, 0.7);
			draw_car1();
		glPopMatrix();

		glPushMatrix();
			oba[i].x_curr = c[i] - i*4;
			oba[i].w *= 0.7;
			oba[i].d *= 0.7;
			glTranslatef(oba[i].x_curr, oba[i].y_curr, oba[i].z_curr);
			glScalef(0.7, 0.7, 0.7);
			// pozivam crtanje kamiona ili kola u zavisnosti od parnosti parametra i
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
    	//pamtim koordinate svih kola jer su potrebne za ispitivanje kolizija
    	aprev[j].x_prev = kamioni[j].x_curr;
    	aprev[j].y_prev = kamioni[j].y_curr;
    	aprev[j].z_prev = kamioni[j].z_curr;
    	aprev[j].w = kamioni[j].w;
    	aprev[j].d = kamioni[j].d;

    	bprev[j].x_prev = kola[j].x_curr;
    	bprev[j].y_prev = kola[j].y_curr;
    	bprev[j].z_prev = kola[j].z_curr;
    	bprev[j].w = kola[j].w;
    	bprev[j].d = kola[j].d;

    	cprev[j].x_prev = oba[j].x_curr;
    	cprev[j].y_prev = oba[j].y_curr;
    	cprev[j].z_prev = oba[j].z_curr;
    	cprev[j].w = oba[j].w;
    	cprev[j].d = oba[j].d;

    	//parametri animacije
    	a[j] += 0.08;
    	b[j] += 0.06;
    	c[j] += 0.08;

    }
    //pamtim koordinate igraca jer su potrebne da proveravanje kolizija igraca i kola
    x_prev = pX;
    y_prev = pY;
    z_prev = pZ;

    //provera kolizija sa kolima na odredjenoj traci
    //ako dodje do kolizije igrac se postavlja na pocetnu poziciju
	for (j = 0; j < max; j++) {
		if (z_prev == t1) {
			//ako se igrac nalazi na prvoj traci
			if (collision_detection(x_prev, z_prev, aprev[j].x_prev, aprev[j].z_prev, aprev[j].w, aprev[j].d) != 0) {
	    		pX = 0;
	    		pZ = 5;
	    		if (zivot == 0) {
	    			animation_ongoing = 0;
	    			break;
	    		}
	    		zivot--;
	    		break;
    		}
    	}
	    else if (z_prev == t2) {
	    	//ako se igrac nalazi na drugoj traci
	    	if (collision_detection(x_prev, z_prev, bprev[j].x_prev, bprev[j].z_prev, bprev[j].w, bprev[j].d) != 0) {
	    		pX = 0;
	    		pZ = 5;
	    		if (zivot == 0) {
					animation_ongoing = 0;
	    			break;
	    		}
	    		zivot--;
	    		break;
    		}
    	}
    	else if (z_prev != t1 && z_prev != t2) {
    		//ako se igrac nalazi na trecoj traci
    		if (collision_detection(x_prev, z_prev, cprev[j].x_prev, cprev[j].z_prev, cprev[j].w, cprev[j].d) != 0) {
    			pX = 0;
    			pZ = 5;
    			if (zivot == 0) {
					animation_ongoing = 0;
	    			break;
    			}
    			zivot--;
    			break;
    		}
    	}
	}
	// ako je igrac izgubio sve zivote izlazi se iz programa ali se pre toga
	// poziva funkcija gameover() u funkciji on_display()
	if (zivot == 0) {
        draw_points();
		animation_ongoing = 0;
        // indikator za proveru u on_display() funkciji za iscrtavanje teksta
        poginuo = 1;
	}

	// ako je igrac stigao na drugi kraj ulice - dobija zivot 
	// i postavlja se na pocetnu poziciju
	if (fabs(z_prev - kraj) < 0.000001) {
		zivot++;
		pX = 0;
		pZ = 5;
	}

	glutPostRedisplay();

	if (animation_ongoing) {
		glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
	}
}
