#ifndef GRADIENT_DESCENT_DIV_HPP
#define GRADIENT_DESCENT_DIV_HPP

#include "../shader_pipeline/shader_pipeline.hpp"
#include "div_base.hpp"

// Drawable Indexed Vertices
class Div : public DivBase {
public:
    Div(float vertices[], int num_vertices, unsigned int indices[], int num_indices);
};

#endif //GRADIENT_DESCENT_DIV_HPP
