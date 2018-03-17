//
// Created by demo02 on 18-1-30.
//

#ifndef FORWARD_QUANTIZE_H
#define FORWARD_QUANTIZE_H

#include <cmath>
#include <cstring>


#define MAXRANGE    2
#define MINRANGE    (-2)


//#define NO_QUANTIZE



double quantize(double num, int bits, int shift){
#ifdef NO_QUANTIZE
    return num;
#else
    double MAXRANGE2 = MAXRANGE;
    double MINRANGE2 = MINRANGE;
    for (int i=0; i<shift; i++){
        MAXRANGE2 = MAXRANGE2 / 2;
        MINRANGE2 = MINRANGE2 / 2;
    }


    if (bits >= 16)
        if (num>MAXRANGE2) {
            std::cout << "Overflow!" << std::endl;
            return MAXRANGE2;
        }
        else if (num<MINRANGE2) {
            std::cout << "Underflow!" << std::endl;
            return MINRANGE2;
        }
        else
            return num;
    double min_interval = double((MAXRANGE2 - MINRANGE2) / pow(2, bits));
    double y = num;
    double res = 0;
    double step = double(MAXRANGE2 / 2.);
    bool flag = false;
    if (y<0){
        flag = true;
        y = -y;
    }
    while ((y>min_interval) && (step >= min_interval)){
        if (y>step){
            y = y - step;
            res = res + step;
        }
        step = step / 2;
    }
    if (y > min_interval/2)
        res = res + min_interval;
    if (flag)
        return -res;
    else
        return res;
#endif
}

#endif //FORWARD_QUANTIZE_H
