#ifndef NN_TENSOR_H
#define NN_TENSOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Tensor {
    float* data;
    size_t width;
    size_t height;
    size_t channels;
} Tensor;

Tensor* create_tensor(size_t width, size_t height, size_t channels, bool random_init);
void free_tensor(Tensor** tensor);
void random_init_tensor(Tensor* tensor);
float get_tensor_element(Tensor* tensor, size_t w, size_t h, size_t c);
void set_tensor_element(Tensor* tensor, size_t w, size_t h, size_t c, float value);
void print_tensor(const Tensor* tensor);

#endif // NN_TENSOR_H
