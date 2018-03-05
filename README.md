# Tensorflow-style-Neural-Network-Framework
*C++ style neural network feedforward framework, using the tensorflow-style convolution/fully-connected operation.*
## Usage
1. Download the Repository and copy the files in 'include' folder to your own project 'include' folder
2. include 'Network.h' in your source code.
3. Instantialize Class *Network*, and use the functions inside. Refer to file Network.h to see all the definitions and utilities of each candidate function of class Network.
## Import a graph
*To import a tensorflow graph to our C++ framework, there are four steps:*
1. Define your network in a header file as a configuration. The "DAC_include.h" is a good example which shows how to define your network. It is recommended that you write a specific configuration for each network you define. Then include this configuration file in Network.cpp.
2. Allocate memory for weight/bias/activation in Constructor Network::Network() using function: Network::AllocateMem(args *), and shapes from 1D to 4D are supported. Refer to "Network.h" for usage.
3. Preload weights from txt File. The file "NETNAME.h" tells you where the weight come from, and you can change whatever you like. Please note that the convolutional weights are stored in [H,W,I,O] format, fully-connected weights are stored in [I,O] format. The preload process is implemented in Network::SetNet() by calling function Network::SetLayer(). Change the code inside for your own network. 

*Note that since the framework supports quantization, if you do not to use quantization, enable the*
``` c++ 
#define NO_QUANTIZE 
```
*in "quantize.h", and set all args representing bit width to 32, and all args representing shifts to 0. Just simply enable the flag NO_QUANTIZE is also fine.*

4. Write the graph layers in Network::Forward. Refer to "Network.h" for all support functions.
## Quantization
If you want to use quantization, uncomment the 
``` c++ 
#define NO_QUANTIZE
``` 
In "quantize.h". Each layer (Conv2D/InnerProduct) can be configured with different width and float-point shifts. By default, the maxrange of quantization is 2, and you can change the value in "quantize.h" by modifying:
``` c++
#define MAXRANGE    2
#define MINRANGE    (-2)
```
in "quantize.h".
If you want to disable Shift functionality, uncomment the line:
``` c++
#define SHIFT_QUANTIZE
```
It is recommended that you wrap your fixed-point neural network in function: Network::FixedFoward(), in which way it is convenient for you to compare the float-point and fixed-point results.
in "quantize.h".
## Example
Suppose you have successfully imported a graph, then we instantialize the class and Run the network.
``` c++
#include "Network.h"

#define INPUT_BIT 8
#define INPUT_SHL 0
int main(){
  Network net;
  net.SetNet();
  // Feed the input
  int input_shape[3] = {224, 224, 3};
  // Suppose the function get_next_image() gives us an image
  float image[224][224][3] = get_next_image(); 
  net.FeedInput(input_shape, image, INPUT_BIT, INPUT_SHL);
  // Feed the input into the network, with 8-bit quantization and 0-bit shift.
  net.Forward();
  
}
```
## Major Realized Functions
#### Network::Conv2D(args *):
Convolutional Neural network operation, using tensorflow-style padding.

*Supports:2D Convolution with any ksize, stride and pad.*
#### Network::InnerProduct(args *):
Fully-connected layer operation.

*Supports:2D InnerProduct with any size*
#### Network::ReLU(args *):
Rectified Linear Unit.

*Supports: 1D/3D activation function*
#### Network::AllocateMem(args *):
Memory Allocator.

*Supports: 1D/2D/3D/4D Memory Allocation.*
#### Network::MaxPool(args *):
Max-pool function.

*Supports: Max-pool with any ksize and stride.*
#### Network::SetLayer(args *):
Layer Weight preloader.

*Supports: Any layer with any bit-width weights.*
