#ifndef GRADIENT_DESCENT_DIV_HPP
#define GRADIENT_DESCENT_DIV_HPP

#include "div_base.hpp"
#include "sbpt_generated_includes.hpp"

// Drawable Indexed Vertices
class Div : public DivBase {
  public:
    Div(ShaderType shader_type, std::vector<glm::vec3> vertex_positions, std::vector<unsigned int> indices,
        ShaderCache &shader_cache);
};

#endif // GRADIENT_DESCENT_DIV_HPP
