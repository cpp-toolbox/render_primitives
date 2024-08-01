#ifndef DIV_SOLID_COLOR_HPP
#define DIV_SOLID_COLOR_HPP

#include "div.hpp"

class DivSolidColor : Div {
    float r, g, b;
    DivSolidColor(float vertices[], int num_vertices, unsigned int indices[], int num_indices, float r, float g,
                  float b)
        : Div(vertices, num_vertices, indices, num_indices), r(r), g(g), b(b){};
};

#endif // DIV_SOLID_COLOR_HPP
