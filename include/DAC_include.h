//
// Created by demo02 on 18-1-30.
//

#ifndef FORWARD_DAC_INCLUDE_H
#define FORWARD_DAC_INCLUDE_H

#define IN_H        216
#define IN_W        384
#define IN_I        3

#define ACT1_H      IN_H
#define ACT1_W      IN_W

#define IN_BIT      8

#define CONV1_1_KH  5
#define CONV1_1_KW  5
#define CONV1_1_KI  3
#define CONV1_1_KO  8
#define CONV1_1_S   1
#define CONV1_1_P   2
#define CONV1_1_TH  0.000

#define CONV1_1_BIT 8

#define CONV1_2_KH  5
#define CONV1_2_KW  5
#define CONV1_2_KI  8
#define CONV1_2_KO  16
#define CONV1_2_S   1
#define CONV1_2_P   2
#define CONV1_2_TH  0.000

#define CONV1_2_BIT 8

#define CONV1_3_KH  5
#define CONV1_3_KW  5
#define CONV1_3_KI  16
#define CONV1_3_KO  32
#define CONV1_3_S   1
#define CONV1_3_P   2
#define CONV1_3_TH  0.000

#define CONV1_3_BIT 8

#define POOL1_KH    2
#define POOL1_KW    2
#define POOL1_SH    2
#define POOL1_SW    2

#define ACT2_H      (ACT1_H / POOL1_SH)
#define ACT2_W      (ACT1_W / POOL1_SW)


#define CONV2_1_KH  3
#define CONV2_1_KW  3
#define CONV2_1_KI  32
#define CONV2_1_KO  64
#define CONV2_1_S   1
#define CONV2_1_P   1
#define CONV2_1_TH  0.000

#define CONV2_1_BIT 8

#define CONV2_2_KH  3
#define CONV2_2_KW  3
#define CONV2_2_KI  64
#define CONV2_2_KO  128
#define CONV2_2_S   1
#define CONV2_2_P   1
#define CONV2_2_TH  0

#define CONV2_2_BIT 8

#define POOL2_KH    4
#define POOL2_KW    4
#define POOL2_SH    4
#define POOL2_SW    4

#define ACT3_H      (ACT2_H / POOL2_SH)
#define ACT3_W      (ACT2_W / POOL2_SW)

#define CONV3_1_KH  3
#define CONV3_1_KW  3
#define CONV3_1_KI  128
#define CONV3_1_KO  96
#define CONV3_1_S   1
#define CONV3_1_P   1
#define CONV3_1_TH  0

#define CONV3_1_BIT 8

#define CONV3_2_KH  3
#define CONV3_2_KW  3
#define CONV3_2_KI  96
#define CONV3_2_KO  64
#define CONV3_2_S   1
#define CONV3_2_P   1
#define CONV3_2_TH  0.000

#define CONV3_2_BIT 8

#define POOL3_KH    4
#define POOL3_KW    4
#define POOL3_SH    4
#define POOL3_SW    4

#define ACT4_H      (ACT3_H / POOL3_SH)
#define ACT4_W      (ACT3_W / POOL3_SW)

#define CONV4_1_KH  3
#define CONV4_1_KW  3
#define CONV4_1_KI  64
#define CONV4_1_KO  16
#define CONV4_1_S   1
#define CONV4_1_P   1
#define CONV4_1_TH  0.000

#define CONV4_1_BIT 8

#define FC1_I       1296
#define FC1_O       256
#define FC1_BIT     8
#define FC1_TH      0.02

#define FC2_I       256
#define FC2_O       20
#define FC2_BIT     8
#define FC2_TH      0.000



#define BUFFER_MAX  FC1_I * FC1_O


int shape_input[3] = {IN_H, IN_W, IN_I};

int shape_conv1_1[4] = {CONV1_1_KH, CONV1_1_KW, CONV1_1_KI, CONV1_1_KO};
int shape_conv1_1_b[1] = {CONV1_1_KO};
int stride_conv1_1[4] = {1, CONV1_1_S, CONV1_1_S, 1};
int pad_conv1_1[2] = {CONV1_1_P, CONV1_1_P};

int shape_act_1_1[3] = {ACT1_H, ACT1_W, CONV1_1_KO};

int shape_conv1_2[4] = {CONV1_2_KH, CONV1_2_KW, CONV1_2_KI, CONV1_2_KO};
int shape_conv1_2_b[1] = {CONV1_2_KO};
int stride_conv1_2[4] = {1, CONV1_2_S, CONV1_2_S, 1};
int pad_conv1_2[2] = {CONV1_2_P, CONV1_2_P};

int shape_act_1_2[3] = {ACT1_H, ACT1_W, CONV1_2_KO};

int shape_conv1_3[4] = {CONV1_3_KH, CONV1_3_KW, CONV1_3_KI, CONV1_3_KO};
int shape_conv1_3_b[1] = {CONV1_3_KO};
int stride_conv1_3[4] = {1, CONV1_3_S, CONV1_3_S, 1};
int pad_conv1_3[2] = {CONV1_3_P, CONV1_3_P};

int shape_act_1_3[3] = {ACT1_H, ACT1_W, CONV1_3_KO};

int shape_act_1[3]  = {ACT2_H, ACT2_W, CONV1_3_KO};

int shape_conv2_1[4] = {CONV2_1_KH, CONV2_1_KW, CONV2_1_KI, CONV2_1_KO};
int shape_conv2_1_b[1] = {CONV2_1_KO};
int stride_conv2_1[4] = {1, CONV2_1_S, CONV2_1_S, 1};
int pad_conv2_1[2] = {CONV2_1_P, CONV2_1_P};

int shape_act_2_1[3] = {ACT2_H, ACT2_W, CONV2_1_KO};

int shape_conv2_2[4] = {CONV2_2_KH, CONV2_2_KW, CONV2_2_KI, CONV2_2_KO};
int shape_conv2_2_b[1] = {CONV2_2_KO};
int stride_conv2_2[4] = {1, CONV2_2_S, CONV2_2_S, 1};
int pad_conv2_2[2] = {CONV2_2_P, CONV2_2_P};

int shape_act_2_2[3] = {ACT2_H, ACT2_W, CONV2_2_KO};

int shape_act_2[3]  = {ACT3_H, ACT3_W, CONV2_2_KO};

int shape_conv3_1[4] = {CONV3_1_KH, CONV3_1_KW, CONV3_1_KI, CONV3_1_KO};
int shape_conv3_1_b[1] = {CONV3_1_KO};
int stride_conv3_1[4] = {1, CONV3_1_S, CONV3_1_S, 1};
int pad_conv3_1[2] = {CONV3_1_P, CONV3_1_P};

int shape_act_3_1[3] = {ACT3_H, ACT3_W, CONV3_1_KO};

int shape_conv3_2[4] = {CONV3_2_KH, CONV3_2_KW, CONV3_2_KI, CONV3_2_KO};
int shape_conv3_2_b[1] = {CONV3_2_KO};
int stride_conv3_2[4] = {1, CONV3_2_S, CONV3_2_S, 1};
int pad_conv3_2[2] = {CONV3_2_P, CONV3_2_P};

int shape_act_3_2[3] = {ACT3_H, ACT3_W, CONV3_2_KO};

int shape_act_3[3]  = {ACT4_H, ACT4_W, CONV3_2_KO};

int shape_conv4_1[4] = {CONV4_1_KH, CONV4_1_KW, CONV4_1_KI, CONV4_1_KO};
int shape_conv4_1_b[1] = {CONV4_1_KO};
int stride_conv4_1[4] = {1, CONV4_1_S, CONV4_1_S, 1};
int pad_conv4_1[2] = {CONV4_1_P, CONV4_1_P};

int shape_act_4_1[3] = {ACT4_H, ACT4_W, CONV4_1_KO};

int ksize_pool1[4] = {1, POOL1_KH, POOL1_KW, 1};
int stride_pool1[4] = {1, POOL1_SH, POOL1_SW, 1};

int ksize_pool2[4] = {1, POOL2_KH, POOL2_KW, 1};
int stride_pool2[4] = {1, POOL2_SH, POOL2_SW, 1};

int ksize_pool3[4] = {1, POOL3_KH, POOL3_KW, 1};
int stride_pool3[4] = {1, POOL3_SH, POOL3_SW, 1};

int shape_flat[1] = {FC1_I};

int shape_fc1_a[1] = {FC1_O};
int shape_fc1_b[1] = {FC1_O};
int shape_fc2_a[1] = {FC2_O};
int shape_fc2_b[1] = {FC2_O};

int shape_fc1[2] = {FC1_I, FC1_O};
int shape_fc2[2] = {FC2_I, FC2_O};


#endif //FORWARD_DAC_INCLUDE_H
