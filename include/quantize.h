//
// Created by demo02 on 18-1-30.
//

#ifndef FORWARD_TOOLS_H
#define FORWARD_TOOLS_H

#include <cmath>
#include <cstring>


#define MAXRANGE    2
#define MINRANGE    (-2)

#define SHIFT_QUANTIZE
#define NO_QUANTIZE

#ifndef SHIFT_QUANTIZE

#define CONV1_1_W_SHL	0
#define CONV1_1_B_SHL	0
#define CONV1_2_W_SHL	0
#define CONV1_2_B_SHL	0
#define CONV1_3_W_SHL	0
#define CONV1_3_B_SHL	0
#define CONV2_1_W_SHL	0
#define CONV2_1_B_SHL	0
#define CONV2_2_W_SHL	0
#define CONV2_2_B_SHL	0
#define CONV3_1_W_SHL	0
#define CONV3_1_B_SHL	0
#define CONV3_2_W_SHL	0
#define CONV3_2_B_SHL	0
#define CONV4_1_W_SHL	0
#define CONV4_1_B_SHL	0
#define FC1_W_SHL	0
#define FC1_B_SHL	0
#define FC2_W_SHL	0
#define FC2_B_SHL	0

#else

#define CONV1_1_W_SHL	2
#define CONV1_1_B_SHL	1
#define CONV1_2_W_SHL	0
#define CONV1_2_B_SHL	2
#define CONV1_3_W_SHL	0
#define CONV1_3_B_SHL	2
#define CONV2_1_W_SHL	0
#define CONV2_1_B_SHL	2
#define CONV2_2_W_SHL	0
#define CONV2_2_B_SHL	2
#define CONV3_1_W_SHL	0
#define CONV3_1_B_SHL	1
#define CONV3_2_W_SHL	0
#define CONV3_2_B_SHL	1
#define CONV4_1_W_SHL	0
#define CONV4_1_B_SHL	2
#define FC1_W_SHL	0
#define FC1_B_SHL	1
#define FC2_W_SHL	1
#define FC2_B_SHL	1


#endif


float quantize(float num, int bits, int shift){
#ifdef NO_QUANTIZE
    return num;
#else
    float MAXRANGE2 = MAXRANGE;
    float MINRANGE2 = MINRANGE;
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
    float min_interval = float((MAXRANGE2 - MINRANGE2) / pow(2, bits));
    float y = num;
    float res = 0;
    float step = float(MAXRANGE2 / 2.);
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





#endif //FORWARD_TOOLS_H
