#ifndef NN_OPERATOR_H
#define NN_OPERATOR_H

#include "nn/tensor.h"

// Linear and Convolutional operations
void conv2d(Tensor* output, Tensor* input, Tensor* weights, Tensor* bias);
void linear(Tensor* output, Tensor* input, Tensor* weights, Tensor* bias);

// Activation functions
void relu(Tensor* output, Tensor* input);

// Pooling operations
void maxpool2d(Tensor* output, Tensor* input, size_t pool_size);

// Flatten operation
void flatten(Tensor* output, Tensor* input);

// Utility functions
void max(float* output, int* index, Tensor* input);

#endif // NN_OPERATOR_H
