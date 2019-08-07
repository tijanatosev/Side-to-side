#include "collisions.h"

// variable which represents Z coordiante of the player when he crosses
// the street
extern float end;

int collision_detection(float x_prev, float z_prev, float tmpx, float tmpz, float w, float l) {    
    // this if checks if the player is on the other side of the street and fabs
    // is used because two float numbers can't be compared just with "=="
    if (fabs(z_prev - end) > 0.000001) {
    	if (x_prev >= tmpx) {
            // if the player is behind the car
            if (x_prev - 0.88 <= tmpx + w) {
                if (z_prev >= 0) {
                    if (z_prev - 0.88 <= tmpz + l/2) {
                        return -1;
                    }
                }
                else {
                    if (z_prev + 0.88 >= tmpz - l/2) {
                        return -1;
                    }
                }
            }
        }
        else if (x_prev <= tmpx) {
            // if the player is in front of the car
            if (x_prev + 0.88 >= tmpx - w) {
                if (z_prev >= 0) {
                    if (z_prev - 0.88 <= tmpz + l/2) {
                        return -1;
                    }
                }
                else {
                    if (z_prev + 0.88 >= tmpz - l/2) {  
                        return -1;
                    }
                }
            }
        }
    }

    // if collision didn't happen then we return 0
	return 0;
}