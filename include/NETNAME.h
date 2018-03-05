
#ifndef FORWARD_NETNAME_H
#define FORWARD_NETNAME_H

#define NUM_WEIGHT_FILE 20

char INPUT_DUMP[255] =  "/home/demo02/Forward/net/activation/input";

//#define CLUSTER_W

#ifndef CLUSTER_W

char WEIGHT_FILENAME[NUM_WEIGHT_FILE][255] = {  "/home/demo02/Forward/net/weights/conv1_1_w",
                                                "/home/demo02/Forward/net/weights/conv1_1_b",
                                                "/home/demo02/Forward/net/weights/conv1_2_w",
                                                "/home/demo02/Forward/net/weights/conv1_2_b",
                                                "/home/demo02/Forward/net/weights/conv1_3_w",
                                                "/home/demo02/Forward/net/weights/conv1_3_b",
                                                "/home/demo02/Forward/net/weights/conv2_1_w",
                                                "/home/demo02/Forward/net/weights/conv2_1_b",
                                                "/home/demo02/Forward/net/weights/conv2_2_w",
                                                "/home/demo02/Forward/net/weights/conv2_2_b",
                                                "/home/demo02/Forward/net/weights/conv3_1_w",
                                                "/home/demo02/Forward/net/weights/conv3_1_b",
                                                "/home/demo02/Forward/net/weights/conv3_2_w",
                                                "/home/demo02/Forward/net/weights/conv3_2_b",
                                                "/home/demo02/Forward/net/weights/conv4_1_w",
                                                "/home/demo02/Forward/net/weights/conv4_1_b",
                                                "/home/demo02/Forward/net/weights/fc1_w",
                                                "/home/demo02/Forward/net/weights/fc1_b",
                                                "/home/demo02/Forward/net/weights/fc2_w",
                                                "/home/demo02/Forward/net/weights/fc2_b"};

char WEIGHT_FILENAME_OUT[NUM_WEIGHT_FILE][255] = {  "/home/demo02/Forward/net/weights_out/conv1_1_w",
                                                    "/home/demo02/Forward/net/weights_out/conv1_1_b",
                                                    "/home/demo02/Forward/net/weights_out/conv1_2_w",
                                                    "/home/demo02/Forward/net/weights_out/conv1_2_b",
                                                    "/home/demo02/Forward/net/weights_out/conv1_3_w",
                                                    "/home/demo02/Forward/net/weights_out/conv1_3_b",
                                                    "/home/demo02/Forward/net/weights_out/conv2_1_w",
                                                    "/home/demo02/Forward/net/weights_out/conv2_1_b",
                                                    "/home/demo02/Forward/net/weights_out/conv2_2_w",
                                                    "/home/demo02/Forward/net/weights_out/conv2_2_b",
                                                    "/home/demo02/Forward/net/weights_out/conv3_1_w",
                                                    "/home/demo02/Forward/net/weights_out/conv3_1_b",
                                                    "/home/demo02/Forward/net/weights_out/conv3_2_w",
                                                    "/home/demo02/Forward/net/weights_out/conv3_2_b",
                                                    "/home/demo02/Forward/net/weights_out/conv4_1_w",
                                                    "/home/demo02/Forward/net/weights_out/conv4_1_b",
                                                    "/home/demo02/Forward/net/weights_out/fc1_w",
                                                    "/home/demo02/Forward/net/weights_out/fc1_b",
                                                    "/home/demo02/Forward/net/weights_out/fc2_w",
                                                    "/home/demo02/Forward/net/weights_out/fc2_b"};

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
#else
char WEIGHT_FILENAME[NUM_WEIGHT_FILE][255] = {  "/home/demo02/Forward/net/clustered_weight/conv1_1_w",
                                                "/home/demo02/Forward/net/clustered_weight/conv1_1_b",
                                                "/home/demo02/Forward/net/clustered_weight/conv1_2_w",
                                                "/home/demo02/Forward/net/clustered_weight/conv1_2_b",
                                                "/home/demo02/Forward/net/clustered_weight/conv1_3_w",
                                                "/home/demo02/Forward/net/clustered_weight/conv1_3_b",
                                                "/home/demo02/Forward/net/clustered_weight/conv2_1_w",
                                                "/home/demo02/Forward/net/clustered_weight/conv2_1_b",
                                                "/home/demo02/Forward/net/clustered_weight/conv2_2_w",
                                                "/home/demo02/Forward/net/clustered_weight/conv2_2_b",
                                                "/home/demo02/Forward/net/clustered_weight/conv3_1_w",
                                                "/home/demo02/Forward/net/clustered_weight/conv3_1_b",
                                                "/home/demo02/Forward/net/clustered_weight/conv3_2_w",
                                                "/home/demo02/Forward/net/clustered_weight/conv3_2_b",
                                                "/home/demo02/Forward/net/clustered_weight/conv4_1_w",
                                                "/home/demo02/Forward/net/clustered_weight/conv4_1_b",
                                                "/home/demo02/Forward/net/clustered_weight/fc1_w",
                                                "/home/demo02/Forward/net/clustered_weight/fc1_b",
                                                "/home/demo02/Forward/net/clustered_weight/fc2_w",
                                                "/home/demo02/Forward/net/clustered_weight/fc2_b"};

char WEIGHT_FILENAME_OUT[NUM_WEIGHT_FILE][255] = {  "/home/demo02/Forward/net/clustered_weight_out/conv1_1_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv1_1_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv1_2_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv1_2_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv1_3_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv1_3_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv2_1_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv2_1_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv2_2_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv2_2_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv3_1_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv3_1_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv3_2_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv3_2_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv4_1_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/conv4_1_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/fc1_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/fc1_b",
                                                    "/home/demo02/Forward/net/clustered_weight_out/fc2_w",
                                                    "/home/demo02/Forward/net/clustered_weight_out/fc2_b"};

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
#endif
#endif //FORWARD_NETNAME_H
