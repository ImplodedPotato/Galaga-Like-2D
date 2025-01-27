#include "fun.h"

void doNothingMachine() { }

int bint(bool b) {
    if (b == true) {
        return 1;
    }
    return 0; 
}

float max(float num, float max) {
    if (num < max) {
        return max;
    }
    return num;
}

float min(float num, float max) {
    if (num > max) {
        return max;
    }
    return num;
}
