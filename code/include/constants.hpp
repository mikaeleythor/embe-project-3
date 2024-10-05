#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TARGET_VELOCITY 3000

// Control parameters
extern double KP; // Declare as extern
extern double TI; // Declare as extern
#define KI 0.1 // Example value for integral gain
#define MAX_VELOCITY 3350
#define CONTROLLER_UPDATE_RATE_MS 4

#endif // CONSTANTS_H
