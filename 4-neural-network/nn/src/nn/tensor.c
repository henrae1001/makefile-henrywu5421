#include "nn/tensor.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Create a new tensor with specified dimensions
 * @param width Width of the tensor
 * @param height Height of the tensor
 * @param channels Number of channels
 * @return Pointer to newly created tensor, NULL on failure
 */
Tensor* create_tensor(size_t width, size_t height, size_t channels, bool random_init) {
    // Validate input dimensions
    if (width == 0 || height == 0 || channels == 0) {
        fprintf(stderr, "Error: Invalid tensor dimensions\n");
        return NULL;
    }

    // Allocate memory for tensor structure
    Tensor* tensor = (Tensor*)malloc(sizeof(Tensor));
    if (!tensor) {
        fprintf(stderr,
                "Error: Failed to allocate memory for tensor structure\n");
        return NULL;
    }

    // Set dimensions
    tensor->width = width;
    tensor->height = height;
    tensor->channels = channels;

    // Calculate total size and allocate data array
    size_t total_size = width * height * channels;
    tensor->data = (float*)calloc(total_size, sizeof(float));
    if (!tensor->data) {
        fprintf(stderr, "Error: Failed to allocate memory for tensor data\n");
        free(tensor);
        return NULL;
    }

    if (random_init) {
        random_init_tensor(tensor);
    }

    return tensor;
}

/**
 * Free tensor memory and set pointer to NULL
 * @param tensor Pointer to tensor pointer
 */
void free_tensor(Tensor** tensor) {
    if (tensor && *tensor) {
        // Free data array
        if ((*tensor)->data) {
            free((*tensor)->data);
            (*tensor)->data = NULL;
        }

        // Free tensor structure
        free(*tensor);
        *tensor = NULL;
    }
}

/**
 * Initialize tensor with random values using Xavier initialization
 * @param tensor Pointer to tensor to initialize
 */
void random_init_tensor(Tensor* tensor) {
    if (!tensor || !tensor->data) {
        fprintf(stderr, "Error: Invalid tensor for random initialization\n");
        return;
    }

    // Initialize random seed if not already done
    static bool seed_initialized = false;
    if (!seed_initialized) {
        srand((unsigned int)time(NULL));
        seed_initialized = true;
    }

    // Calculate total number of elements
    size_t total_elements = tensor->width * tensor->height * tensor->channels;

    // Xavier initialization: scale = sqrt(1/n) where n is number of inputs
    float scale = sqrtf(1.0f / (float)total_elements);

    // Fill tensor with random values
    for (size_t i = 0; i < total_elements; i++) {
        // Generate random number between -1 and 1
        float random_val = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        tensor->data[i] = random_val * scale;
    }
}

/**
 * Get tensor element at specified position
 * @param tensor Input tensor
 * @param w Width index
 * @param h Height index
 * @param c Channel index
 * @return Element value, 0.0f if out of bounds
 */
float get_tensor_element(Tensor* tensor, size_t w, size_t h, size_t c) {
    if (!tensor || !tensor->data || w >= tensor->width || h >= tensor->height || c >= tensor->channels) {
        return 0.0f;
    }
    return tensor->data[c * tensor->width * tensor->height + h * tensor->width + w];
}

/**
 * Set tensor element at specified position
 * @param tensor Output tensor
 * @param w Width index
 * @param h Height index
 * @param c Channel index
 * @param value Value to set
 */
void set_tensor_element(Tensor* tensor, size_t w, size_t h, size_t c, float value) {
    if (!tensor || !tensor->data || w >= tensor->width || h >= tensor->height || c >= tensor->channels) {
        return;
    }
    tensor->data[c * tensor->width * tensor->height + h * tensor->width + w] = value;
}

/**
 * Print tensor contents in a readable format
 * @param tensor Pointer to tensor to print
 */
void print_tensor(const Tensor* tensor) {
    if (!tensor) {
        fprintf(stderr, "Error: NULL tensor\n");
        return;
    }

    if (!tensor->data) {
        fprintf(stderr, "Error: Tensor has NULL data\n");
        return;
    }

    printf("Tensor[%zu, %zu, %zu] {\n", tensor->channels, tensor->height, tensor->width);

    // Handle different display strategies based on tensor size
    size_t total_elements = tensor->channels * tensor->height * tensor->width;

    // For very large tensors, show summary statistics
    if (total_elements > 100) {
        printf("  Size: %zu channels × %zu height × %zu width = %zu elements\n",
               tensor->channels, tensor->height, tensor->width, total_elements);

        // Calculate statistics
        float min_val = tensor->data[0];
        float max_val = tensor->data[0];
        float sum = 0.0f;

        for (size_t i = 0; i < total_elements; i++) {
            float val = tensor->data[i];
            if (val < min_val) min_val = val;
            if (val > max_val) max_val = val;
            sum += val;
        }

        float mean = sum / total_elements;

        printf("  Statistics: min=%.4f, max=%.4f, mean=%.4f\n", min_val, max_val, mean);

        // Show first few elements of each channel
        printf("  Sample data (first 3×3 of each channel):\n");
        for (size_t c = 0; c < tensor->channels && c < 3; c++) {
            printf("    Channel %zu:\n", c);
            size_t max_h = tensor->height < 3 ? tensor->height : 3;
            size_t max_w = tensor->width < 3 ? tensor->width : 3;

            for (size_t h = 0; h < max_h; h++) {
                printf("      ");
                for (size_t w = 0; w < max_w; w++) {
                    printf("%8.4f ", get_tensor_element((Tensor*)tensor, c, h, w));
                }
                if (tensor->width > 3) printf("...");
                printf("\n");
            }
            if (tensor->height > 3) printf("      ...\n");
            if (c < tensor->channels - 1) printf("\n");
        }
        if (tensor->channels > 3) printf("    ... (%zu more channels)\n", tensor->channels - 3);
    }
    else {
        // For small tensors, show complete data
        for (size_t c = 0; c < tensor->channels; c++) {
            if (tensor->channels > 1) {
                printf("  Channel %zu:\n", c);
            }

            for (size_t h = 0; h < tensor->height; h++) {
                printf("    ");
                for (size_t w = 0; w < tensor->width; w++) {
                    printf("%8.4f ", get_tensor_element((Tensor*)tensor, c, h, w));
                }
                printf("\n");
            }

            if (c < tensor->channels - 1) {
                printf("\n");
            }
        }
    }

    printf("}\n");
}
