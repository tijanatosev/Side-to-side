#include "kolizije.h"

//promenljiva koja predstavlja z koordinatu igraca kada predje na drugu
//stranu ulice
extern float kraj;

int collision_detection(float x_prev, float z_prev, float tmpx, float tmpz, float w, float d) {
    //potreban je ovaj if kako bismo proverili na igrac nije stigao na drugu stranu
    //a fabs je potrebno jer ne mogu uvek dva float broja da se uporede samo sa ==
    if (fabs(z_prev - kraj) > 0.000001) {
    	if (x_prev >= tmpx) {
            // ako je igrac iza kola
            if (x_prev - 0.88 <= tmpx + w) {
                if (z_prev >= 0) {
                    if (z_prev - 0.88 <= tmpz + d/2) {
                        return -1;
                    }
                }
                else {
                    if (z_prev + 0.88 >= tmpz - d/2) {
                        return -1;
                    }
                }
            }
        }
        else if (x_prev <= tmpx) {
            // ako je igrac ispred kola
            if (x_prev + 0.88 >= tmpx - w) {
                if (z_prev >= 0) {
                    if (z_prev - 0.88 <= tmpz + d/2) {
                        return -1;
                    }
                }
                else {
                    if (z_prev + 0.88 >= tmpz - d/2) {  
                        return -1;
                    }
                }
            }
        }
    }
    // ako nije doslo do kolizije vraca se nula
	return 0;
}