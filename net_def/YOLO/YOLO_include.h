//
// Created by demo02 on 18-1-30.
//

#ifndef FORWARD_YOLO_INCLUDE_H
#define FORWARD_YOLO_INCLUDE_H

#define IN_H        448
#define IN_W        448
#define IN_I        3

#define ACT1_H      IN_H
#define ACT1_W      IN_W

#define IN_BIT      32

#define CONV1_1_KH  3
#define CONV1_1_KW  3
#define CONV1_1_KI  3
#define CONV1_1_KO  16
#define CONV1_1_S   1
#define CONV1_1_P   1
#define CONV1_1_TH  0.000

#define CONV1_1_BIT 32

#define POOL1_KH    2
#define POOL1_KW    2
#define POOL1_SH    2
#define POOL1_SW    2

#define ACT2_H      (ACT1_H / POOL1_SH)
#define ACT2_W      (ACT1_W / POOL1_SW)


#define CONV2_1_KH  3
#define CONV2_1_KW  3
#define CONV2_1_KI  16
#define CONV2_1_KO  32
#define CONV2_1_S   1
#define CONV2_1_P   1
#define CONV2_1_TH  0.000

#define CONV2_1_BIT 32

#define POOL2_KH    2
#define POOL2_KW    2
#define POOL2_SH    2
#define POOL2_SW    2

#define ACT3_H      (ACT2_H / POOL2_SH)
#define ACT3_W      (ACT2_W / POOL2_SW)


#define CONV3_1_KH  3
#define CONV3_1_KW  3
#define CONV3_1_KI  32
#define CONV3_1_KO  64
#define CONV3_1_S   1
#define CONV3_1_P   1
#define CONV3_1_TH  0.000

#define CONV3_1_BIT 32

#define POOL3_KH    2
#define POOL3_KW    2
#define POOL3_SH    2
#define POOL3_SW    2

#define ACT4_H      (ACT3_H / POOL3_SH)
#define ACT4_W      (ACT3_W / POOL3_SW)


#define CONV4_1_KH  3
#define CONV4_1_KW  3
#define CONV4_1_KI  64
#define CONV4_1_KO  128
#define CONV4_1_S   1
#define CONV4_1_P   1
#define CONV4_1_TH  0.000

#define CONV4_1_BIT 32

#define POOL4_KH    2
#define POOL4_KW    2
#define POOL4_SH    2
#define POOL4_SW    2

#define ACT5_H      (ACT4_H / POOL4_SH)
#define ACT5_W      (ACT4_W / POOL4_SW)


#define CONV5_1_KH  3
#define CONV5_1_KW  3
#define CONV5_1_KI  128
#define CONV5_1_KO  256
#define CONV5_1_S   1
#define CONV5_1_P   1
#define CONV5_1_TH  0.000

#define CONV5_1_BIT 32

#define POOL5_KH    2
#define POOL5_KW    2
#define POOL5_SH    2
#define POOL5_SW    2

#define ACT6_H      (ACT5_H / POOL5_SH)
#define ACT6_W      (ACT5_W / POOL5_SW)



#define CONV6_1_KH  3
#define CONV6_1_KW  3
#define CONV6_1_KI  256
#define CONV6_1_KO  512
#define CONV6_1_S   1
#define CONV6_1_P   1
#define CONV6_1_TH  0.000

#define CONV6_1_BIT 32

#define POOL6_KH    2
#define POOL6_KW    2
#define POOL6_SH    2
#define POOL6_SW    2

#define ACT7_H      (ACT6_H / POOL6_SH)
#define ACT7_W      (ACT6_W / POOL6_SW)


#define CONV7_1_KH  3
#define CONV7_1_KW  3
#define CONV7_1_KI  512
#define CONV7_1_KO  1024
#define CONV7_1_S   1
#define CONV7_1_P   1
#define CONV7_1_TH  0.000

#define CONV7_1_BIT 32


#define CONV7_2_KH  3
#define CONV7_2_KW  3
#define CONV7_2_KI  1024
#define CONV7_2_KO  1024
#define CONV7_2_S   1
#define CONV7_2_P   1
#define CONV7_2_TH  0.000

#define CONV7_2_BIT 32


#define CONV7_3_KH  3
#define CONV7_3_KW  3
#define CONV7_3_KI  1024
#define CONV7_3_KO  1024
#define CONV7_3_S   1
#define CONV7_3_P   1
#define CONV7_3_TH  0.000

#define CONV7_3_BIT 32


#define FC1_I       (7*7*1024)
#define FC1_O       256
#define FC1_BIT     8
#define FC1_TH      0.00

#define FC2_I       256
#define FC2_O       4096
#define FC2_BIT     8
#define FC2_TH      0.000

#define FC3_I       4096
#define FC3_O       (7*7*(20+2*5))
#define FC3_BIT     8
#define FC3_TH      0.000

#define OUT_H       7
#define OUT_W       7
#define CLASSES     20
#define CONFIDENCE  2
#define COORDINATE  4
#define INDEX       5

// QUANTIZATION SECTION

//#define SHIFT_QUANTIZE
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
#define CONV5_1_W_SHL	0
#define CONV5_1_B_SHL	0
#define CONV6_1_W_SHL	0
#define CONV6_1_B_SHL	0
#define CONV7_1_W_SHL	0
#define CONV7_1_B_SHL	0
#define CONV7_2_W_SHL	0
#define CONV7_2_B_SHL	0
#define CONV7_3_W_SHL	0
#define CONV7_3_B_SHL	0
#define FC1_W_SHL	0
#define FC1_B_SHL	0
#define FC2_W_SHL	0
#define FC2_B_SHL	0
#define FC3_W_SHL	0
#define FC3_B_SHL	0

#else

#define CONV1_1_W_SHL	4
#define CONV1_1_B_SHL	3
#define CONV1_2_W_SHL	2
#define CONV1_2_B_SHL	4
#define CONV1_3_W_SHL	2
#define CONV1_3_B_SHL	4
#define CONV2_1_W_SHL	2
#define CONV2_1_B_SHL	4
#define CONV2_2_W_SHL	2
#define CONV2_2_B_SHL	4
#define CONV3_1_W_SHL	1
#define CONV3_1_B_SHL	3
#define CONV3_2_W_SHL	2
#define CONV3_2_B_SHL	3
#define CONV4_1_W_SHL	2
#define CONV4_1_B_SHL	4
#define FC1_W_SHL	1
#define FC1_B_SHL	3
#define FC2_W_SHL	3
#define FC2_B_SHL	3

#endif

// SHAPE SECTION


#define BUFFER_MAX  FC1_I * FC1_O


int shape_input[3] = {IN_H, IN_W, IN_I};

int shape_conv1_1[4] = {CONV1_1_KH, CONV1_1_KW, CONV1_1_KI, CONV1_1_KO};
int shape_conv1_1_b[1] = {CONV1_1_KO};
int stride_conv1_1[4] = {1, CONV1_1_S, CONV1_1_S, 1};
int pad_conv1_1[2] = {CONV1_1_P, CONV1_1_P};

int shape_act_1_1[3] = {ACT1_H, ACT1_W, CONV1_1_KO};

int shape_act_1[3]  = {ACT2_H, ACT2_W, CONV1_1_KO};

int shape_conv2_1[4] = {CONV2_1_KH, CONV2_1_KW, CONV2_1_KI, CONV2_1_KO};
int shape_conv2_1_b[1] = {CONV2_1_KO};
int stride_conv2_1[4] = {1, CONV2_1_S, CONV2_1_S, 1};
int pad_conv2_1[2] = {CONV2_1_P, CONV2_1_P};

int shape_act_2_1[3] = {ACT2_H, ACT2_W, CONV2_1_KO};

int shape_act_2[3]  = {ACT3_H, ACT3_W, CONV2_1_KO};

int shape_conv3_1[4] = {CONV3_1_KH, CONV3_1_KW, CONV3_1_KI, CONV3_1_KO};
int shape_conv3_1_b[1] = {CONV3_1_KO};
int stride_conv3_1[4] = {1, CONV3_1_S, CONV3_1_S, 1};
int pad_conv3_1[2] = {CONV3_1_P, CONV3_1_P};

int shape_act_3_1[3] = {ACT3_H, ACT3_W, CONV3_1_KO};

int shape_act_3[3]  = {ACT4_H, ACT4_W, CONV3_1_KO};

int shape_conv4_1[4] = {CONV4_1_KH, CONV4_1_KW, CONV4_1_KI, CONV4_1_KO};
int shape_conv4_1_b[1] = {CONV4_1_KO};
int stride_conv4_1[4] = {1, CONV4_1_S, CONV4_1_S, 1};
int pad_conv4_1[2] = {CONV4_1_P, CONV4_1_P};

int shape_act_4_1[3] = {ACT4_H, ACT4_W, CONV4_1_KO};

int shape_act_4[3] = {ACT5_H, ACT5_W, CONV4_1_KO};

int shape_conv5_1[4] = {CONV5_1_KH, CONV5_1_KW, CONV5_1_KI, CONV5_1_KO};
int shape_conv5_1_b[1] = {CONV5_1_KO};
int stride_conv5_1[4] = {1, CONV5_1_S, CONV5_1_S, 1};
int pad_conv5_1[2] = {CONV5_1_P, CONV5_1_P};

int shape_act_5_1[3] = {ACT5_H, ACT5_W, CONV5_1_KO};

int shape_act_5[3] = {ACT6_H, ACT6_W, CONV5_1_KO};

int shape_conv6_1[4] = {CONV6_1_KH, CONV6_1_KW, CONV6_1_KI, CONV6_1_KO};
int shape_conv6_1_b[1] = {CONV6_1_KO};
int stride_conv6_1[4] = {1, CONV6_1_S, CONV6_1_S, 1};
int pad_conv6_1[2] = {CONV6_1_P, CONV6_1_P};

int shape_act_6_1[3] = {ACT6_H, ACT6_W, CONV6_1_KO};

int shape_act_6[3] = {ACT7_H, ACT7_W, CONV6_1_KO};

int shape_conv7_1[4] = {CONV7_1_KH, CONV7_1_KW, CONV7_1_KI, CONV7_1_KO};
int shape_conv7_1_b[1] = {CONV7_1_KO};
int stride_conv7_1[4] = {1, CONV7_1_S, CONV7_1_S, 1};
int pad_conv7_1[2] = {CONV7_1_P, CONV7_1_P};

int shape_act_7_1[3] = {ACT7_H, ACT7_W, CONV7_1_KO};

int shape_conv7_2[4] = {CONV7_2_KH, CONV7_2_KW, CONV7_2_KI, CONV7_2_KO};
int shape_conv7_2_b[1] = {CONV7_2_KO};
int stride_conv7_2[4] = {1, CONV7_2_S, CONV7_2_S, 1};
int pad_conv7_2[2] = {CONV7_2_P, CONV7_2_P};

int shape_act_7_2[3] = {ACT7_H, ACT7_W, CONV7_2_KO};

int shape_conv7_3[4] = {CONV7_3_KH, CONV7_3_KW, CONV7_3_KI, CONV7_3_KO};
int shape_conv7_3_b[1] = {CONV7_3_KO};
int stride_conv7_3[4] = {1, CONV7_3_S, CONV7_3_S, 1};
int pad_conv7_3[2] = {CONV7_3_P, CONV7_3_P};

int shape_act_7_3[3] = {ACT7_H, ACT7_W, CONV7_3_KO};

int shape_transpose[3] = {CONV7_3_KO, ACT7_H, ACT7_W};   //Transpose
int transpose_cfg[3] = {2, 0, 1};

int ksize_pool1[4] = {1, POOL1_KH, POOL1_KW, 1};
int stride_pool1[4] = {1, POOL1_SH, POOL1_SW, 1};

int ksize_pool2[4] = {1, POOL2_KH, POOL2_KW, 1};
int stride_pool2[4] = {1, POOL2_SH, POOL2_SW, 1};

int ksize_pool3[4] = {1, POOL3_KH, POOL3_KW, 1};
int stride_pool3[4] = {1, POOL3_SH, POOL3_SW, 1};

int ksize_pool4[4] = {1, POOL4_KH, POOL4_KW, 1};
int stride_pool4[4] = {1, POOL4_SH, POOL4_SW, 1};

int ksize_pool5[4] = {1, POOL5_KH, POOL5_KW, 1};
int stride_pool5[4] = {1, POOL5_SH, POOL5_SW, 1};

int ksize_pool6[4] = {1, POOL6_KH, POOL6_KW, 1};
int stride_pool6[4] = {1, POOL6_SH, POOL6_SW, 1};

int shape_flat[1] = {FC1_I};

int shape_fc1_a[1] = {FC1_O};
int shape_fc1_b[1] = {FC1_O};
int shape_fc2_a[1] = {FC2_O};
int shape_fc2_b[1] = {FC2_O};
int shape_fc3_a[1] = {FC3_O};
int shape_fc3_b[1] = {FC3_O};

int shape_fc1[2] = {FC1_I, FC1_O};
int shape_fc2[2] = {FC2_I, FC2_O};
int shape_fc3[2] = {FC3_I, FC3_O};

int shape_predicts[3] = {OUT_H, OUT_W, (CLASSES + CONFIDENCE + CONFIDENCE*COORDINATE)};
int shape_classes_data[3] = {OUT_H, OUT_W, CLASSES};
int shape_confidence_data[3] = {OUT_H, OUT_W, CONFIDENCE};
int shape_coordinate_data[3] = {OUT_H, OUT_W, CONFIDENCE*COORDINATE};
int shape_classes[2] = {0, OUT_W*OUT_H*CLASSES};
int shape_confidence[2] = {OUT_W*OUT_H*CLASSES, OUT_W*OUT_H*(CLASSES+CONFIDENCE)};
int shape_coordinate[2] = {OUT_W*OUT_H*(CLASSES+CONFIDENCE), OUT_W*OUT_H*(CLASSES+CONFIDENCE+CONFIDENCE*COORDINATE)};
int shape_Probability[4] = {OUT_H, OUT_W, CONFIDENCE, CLASSES};
int shape_index[2] = {OUT_H*OUT_W*CONFIDENCE, INDEX};
int shape_index_coord[2] = {OUT_H*OUT_W*CONFIDENCE, INDEX+1};
int shape_max_coord[1] = {COORDINATE};

#endif //FORWARD_YOLO_INCLUDE_H
