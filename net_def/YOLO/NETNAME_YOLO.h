//
// Created by jsyang on 18-3-8.
//

#ifndef FORWARD_NETNAME_YOLO_H
#define FORWARD_NETNAME_YOLO_H



#define NUM_WEIGHT_FILE 24




char WEIGHT_FILENAME[NUM_WEIGHT_FILE][255] = {  "/home/jsyang/data_yolo/weights/conv1_1_w",
                                                "/home/jsyang/data_yolo/weights/conv1_1_b",
                                                "/home/jsyang/data_yolo/weights/conv2_1_w",
                                                "/home/jsyang/data_yolo/weights/conv2_1_b",
                                                "/home/jsyang/data_yolo/weights/conv3_1_w",
                                                "/home/jsyang/data_yolo/weights/conv3_1_b",
                                                "/home/jsyang/data_yolo/weights/conv4_1_w",
                                                "/home/jsyang/data_yolo/weights/conv4_1_b",
                                                "/home/jsyang/data_yolo/weights/conv5_1_w",
                                                "/home/jsyang/data_yolo/weights/conv5_1_b",
                                                "/home/jsyang/data_yolo/weights/conv6_1_w",
                                                "/home/jsyang/data_yolo/weights/conv6_1_b",
                                                "/home/jsyang/data_yolo/weights/conv7_1_w",
                                                "/home/jsyang/data_yolo/weights/conv7_1_b",
                                                "/home/jsyang/data_yolo/weights/conv7_2_w",
                                                "/home/jsyang/data_yolo/weights/conv7_2_b",
                                                "/home/jsyang/data_yolo/weights/conv7_3_w",
                                                "/home/jsyang/data_yolo/weights/conv7_3_b",
                                                "/home/jsyang/data_yolo/weights/fc1_w",
                                                "/home/jsyang/data_yolo/weights/fc1_b",
                                                "/home/jsyang/data_yolo/weights/fc2_w",
                                                "/home/jsyang/data_yolo/weights/fc2_b",
                                                "/home/jsyang/data_yolo/weights/fc3_w",
                                                "/home/jsyang/data_yolo/weights/fc3_b"};




char WEIGHT_FILENAME_OUT[NUM_WEIGHT_FILE][255] = {  "/home/jsyang/data_yolo/weights_out/conv1_1_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv1_1_b",
                                                    "/home/jsyang/data_yolo/weights_out/conv2_1_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv2_1_b",
                                                    "/home/jsyang/data_yolo/weights_out/conv3_1_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv3_1_b",
                                                    "/home/jsyang/data_yolo/weights_out/conv4_1_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv4_1_b",
                                                    "/home/jsyang/data_yolo/weights_out/conv5_1_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv5_1_b",
                                                    "/home/jsyang/data_yolo/weights_out/conv6_1_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv6_1_b",
                                                    "/home/jsyang/data_yolo/weights_out/conv7_1_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv7_1_b",
                                                    "/home/jsyang/data_yolo/weights_out/conv7_2_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv7_2_b",
                                                    "/home/jsyang/data_yolo/weights_out/conv7_3_w",
                                                    "/home/jsyang/data_yolo/weights_out/conv7_3_b",
                                                    "/home/jsyang/data_yolo/weights_out/fc1_w",
                                                    "/home/jsyang/data_yolo/weights_out/fc1_b"};



/*
char ACTIVATION_FILENAME_OUT[NUM_WEIGHT_FILE/2][255] = {
        "/home/demo02/Forward/net/activation/conv1_1_a",
        "/home/demo02/Forward/net/activation/conv1_2_a",
        "/home/demo02/Forward/net/activation/conv1_3_a",
        "/home/demo02/Forward/net/activation/conv2_1_a",
        "/home/demo02/Forward/net/activation/conv2_2_a",
        "/home/demo02/Forward/net/activation/conv3_1_a",
        "/home/demo02/Forward/net/activation/conv3_2_a",
        "/home/demo02/Forward/net/activation/conv4_1_a",
        "/home/demo02/Forward/net/activation/fc1_a",
        "/home/demo02/Forward/net/activation/fc2_a"};
*/





#endif //FORWARD_NETNAME_YOLO_H
