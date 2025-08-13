#include "nn/operator.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

#include "nn/tensor.h"

/**
 * 2D Convolution operation
 * @param output Output tensor
 * @param input Input tensor
 * @param weights Convolution weights (kernel)
 * @param bias Bias tensor (can be NULL)
 */
void conv2d(Tensor* output, Tensor* input, Tensor* weights, Tensor* bias) {
    if (!output || !input || !weights) {
        fprintf(stderr, "Error: Invalid tensors for conv2d operation\n");
        return;
    }

    // Assume weights format: [output_channels, input_channels, kernel_height,
    // kernel_width] For simplicity, assume square kernels and same padding
    size_t kernel_size = weights->height;  // Assume square kernel
    size_t pad = kernel_size / 2;          // Same padding

    // Perform convolution
    for (size_t out_c = 0; out_c < output->channels; out_c++) {
        for (size_t out_h = 0; out_h < output->height; out_h++) {
            for (size_t out_w = 0; out_w < output->width; out_w++) {
                float sum = 0.0f;

                // Apply kernel
                for (size_t in_c = 0; in_c < input->channels; in_c++) {
                    for (size_t k_h = 0; k_h < kernel_size; k_h++) {
                        for (size_t k_w = 0; k_w < kernel_size; k_w++) {
                            // Calculate input position with padding
                            int in_h = (int)out_h + (int)k_h - (int)pad;
                            int in_w = (int)out_w + (int)k_w - (int)pad;

                            // Check bounds
                            if (in_h >= 0 && in_h < (int)input->height &&
                                in_w >= 0 && in_w < (int)input->width) {
                                float input_val =
                                    get_tensor_element(input, in_w, in_h, in_c);
                                float weight_val = get_tensor_element(
                                    weights, k_w, k_h, out_c);
                                sum += input_val * weight_val;
                            }
                        }
                    }
                }

                // Add bias if provided
                if (bias && bias->data) {
                    sum += bias->data[out_c];
                }

                set_tensor_element(output, out_w, out_h, out_c, sum);
            }
        }
    }
}

/**
 * Linear (fully connected) operation
 * @param output Output tensor
 * @param input Input tensor (flattened)
 * @param weights Weight matrix
 * @param bias Bias vector (can be NULL)
 */
void linear(Tensor* output, Tensor* input, Tensor* weights, Tensor* bias) {
    if (!output || !input || !weights) {
        fprintf(stderr, "Error: Invalid tensors for linear operation\n");
        return;
    }

    // Flatten input tensor
    size_t input_size = input->width * input->height * input->channels;
    size_t output_size = output->width * output->height * output->channels;

    // Perform matrix multiplication: output = input * weights + bias
    for (size_t out_idx = 0; out_idx < output_size; out_idx++) {
        float sum = 0.0f;

        for (size_t in_idx = 0; in_idx < input_size; in_idx++) {
            sum += input->data[in_idx] *
                   weights->data[out_idx * input_size + in_idx];
        }

        // Add bias if provided
        if (bias && bias->data) {
            sum += bias->data[out_idx];
        }

        output->data[out_idx] = sum;
    }
}

/**
 * ReLU activation function
 * @param output Output tensor
 * @param input Input tensor
 */
void relu(Tensor* output, Tensor* input) {
    if (!output || !input) {
        fprintf(stderr, "Error: Invalid tensors for relu operation\n");
        return;
    }

    // Check if tensors have same dimensions
    if (output->width != input->width || output->height != input->height ||
        output->channels != input->channels) {
        fprintf(stderr,
                "Error: Input and output tensors must have same dimensions for "
                "relu\n");
        return;
    }

    size_t total_elements = input->width * input->height * input->channels;

    // Apply ReLU: max(0, x)
    for (size_t i = 0; i < total_elements; i++) {
        output->data[i] = fmaxf(0.0f, input->data[i]);
    }
}

/**
 * 2D Max pooling operation
 * @param output Output tensor
 * @param input Input tensor
 * @param pool_size Size of pooling window (assumed square)
 */
void maxpool2d(Tensor* output, Tensor* input, size_t pool_size) {
    if (!output || !input) {
        fprintf(stderr, "Error: Invalid tensors for maxpool2d operation\n");
        return;
    }

    if (pool_size == 0) {
        fprintf(stderr, "Error: Invalid pool size for maxpool2d\n");
        return;
    }

    // Perform max pooling
    for (size_t c = 0; c < output->channels; c++) {
        for (size_t out_h = 0; out_h < output->height; out_h++) {
            for (size_t out_w = 0; out_w < output->width; out_w++) {
                float max_val = -FLT_MAX;

                // Find maximum in pooling window
                for (size_t pool_h = 0; pool_h < pool_size; pool_h++) {
                    for (size_t pool_w = 0; pool_w < pool_size; pool_w++) {
                        size_t in_h = out_h * pool_size + pool_h;
                        size_t in_w = out_w * pool_size + pool_w;

                        // Check bounds
                        if (in_h < input->height && in_w < input->width) {
                            float val =
                                get_tensor_element(input, in_w, in_h, c);
                            if (val > max_val) {
                                max_val = val;
                            }
                        }
                    }
                }

                set_tensor_element(output, out_w, out_h, c, max_val);
            }
        }
    }
}

/**
 * Flatten a multi-dimensional tensor into a 1D tensor
 * @param output Output tensor (should be 1D: [total_elements, 1, 1])
 * @param input Input tensor to be flattened
 */
void flatten(Tensor* output, Tensor* input) {
    if (!output || !input) {
        fprintf(stderr, "Error: Invalid tensors for flatten operation\n");
        return;
    }

    if (!output->data || !input->data) {
        fprintf(stderr,
                "Error: Tensors have NULL data for flatten operation\n");
        return;
    }

    // Calculate total elements in input tensor
    size_t input_total = input->channels * input->height * input->width;
    size_t output_total = output->channels * output->height * output->width;

    // Check if output tensor has correct size
    if (input_total != output_total) {
        fprintf(stderr,
                "Error: Output tensor size (%zu) doesn't match input tensor "
                "size (%zu)\n",
                output_total, input_total);
        return;
    }

    // Copy data from input to output (flattening)
    for (size_t i = 0; i < input_total; i++) {
        output->data[i] = input->data[i];
    }
}

/**
* Find the maximum value and its index in input tensor
* @param output Pointer to store the maximum value
* @param index Pointer to store the index of maximum value
* @param input Input tensor
*/
void max(float* output, int* index, Tensor* input) {
   if (!output || !index || !input || !input->data) {
       fprintf(stderr, "Error: Invalid parameters for max operation\n");
       return;
   }

   size_t input_total = input->channels * input->height * input->width;

   if (input_total == 0) {
       fprintf(stderr, "Error: Input tensor is empty\n");
       return;
   }

   float max_val = input->data[0];
   int max_idx = 0;

   for (size_t i = 1; i < input_total; i++) {
       if (input->data[i] > max_val) {
           max_val = input->data[i];
           max_idx = (int)i;
       }
   }

   *output = max_val;
   *index = max_idx;
}
