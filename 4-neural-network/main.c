#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "nn/operator.h"
#include "nn/tensor.h"

/**
 * Simple CNN implementation
 * Architecture:
 * Input(16x16x1) -> Conv1(16x16x4) -> Pool1(8x8x4) -> Conv2(8x8x8) ->
 * Pool2(4x4x8) -> FC3(10)
 */
void simple_cnn(Tensor* output, Tensor* input) {
    // ===== Layer 1: Convolution (16x16x1 -> 16x16x4) =====
    Tensor* conv1_weights = create_tensor(3, 3, 4, true);
    Tensor* conv1_bias = create_tensor(4, 1, 1, true);
    Tensor* conv1_output = create_tensor(16, 16, 4, false);
    conv2d(conv1_output, input, conv1_weights, conv1_bias);
    relu(conv1_output, conv1_output);
    free_tensor(&conv1_weights);
    free_tensor(&conv1_bias);

    // ===== Layer 2: Max Pooling (16x16x4 -> 8x8x4) =====
    Tensor* pool1_output = create_tensor(8, 8, 4, false);
    maxpool2d(pool1_output, conv1_output, 2);
    free_tensor(&conv1_output);

    // ===== Layer 3: Convolution (8x8x4 -> 8x8x8) =====
    Tensor* conv2_weights = create_tensor(3, 3, 8, true);
    Tensor* conv2_bias = create_tensor(8, 1, 1, true);
    Tensor* conv2_output = create_tensor(8, 8, 8, false);
    conv2d(conv2_output, pool1_output, conv2_weights, conv2_bias);
    relu(conv2_output, conv2_output);
    free_tensor(&pool1_output);
    free_tensor(&conv2_weights);
    free_tensor(&conv2_bias);

    // ===== Layer 4: Max Pooling (8x8x8 -> 4x4x8) =====
    Tensor* pool2_output = create_tensor(4, 4, 8, false);
    maxpool2d(pool2_output, conv2_output, 2);
    free_tensor(&conv2_output);

    // ===== Layer 5: Flatten and Fully Connected (4x4x8=128 -> 10) =====
    Tensor* fc_weights = create_tensor(10, 128, 1, true);
    Tensor* fc_bias = create_tensor(10, 1, 1, true);
    Tensor* flatten_input = create_tensor(128, 1, 1, false);
    flatten(flatten_input, pool2_output);
    linear(output, flatten_input, fc_weights, fc_bias);

    free_tensor(&pool2_output);
    free_tensor(&flatten_input);
    free_tensor(&fc_weights);
    free_tensor(&fc_bias);
}

int main() {
    Tensor* input = create_tensor(16, 16, 1, true);
    Tensor* output = create_tensor(10, 1, 1, false);

    printf("Input Tensor:\n");
    print_tensor(input);

    printf("Running simple CNN...\n");
    simple_cnn(output, input);

    printf("Output Tensor:\n");
    print_tensor(output);

    float max_value;
    int max_index;
    max(&max_value, &max_index, output);
    printf("Max value in output: %.4f at index %d\n", max_value, max_index);

    free_tensor(&input);
    free_tensor(&output);
    return 0;
}
