#include "div.hpp"
#include "glad/glad.h"
#include <cstdio>

/**
 * precondition: opengl must be configured first
 */
Div::Div(float vertices[], int num_vertices, unsigned int indices[], int num_indices, float r, float g, float b)
        : DivBase(GL_TRIANGLES, vertices, num_vertices, indices, num_indices, r, g, b) {
}
