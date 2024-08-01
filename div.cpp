#include "div.hpp"
#include "glad/glad.h"
#include <cstdio>
#include <utility>

/**
 * \pre there is an active opengl context
 */

Div::Div(ShaderType shader_type, std::vector<glm::vec3> vertex_positions, std::vector<unsigned int> indices,
         ShaderCache &shader_cache)
    : DivBase(shader_type, GL_TRIANGLES, std::move(vertex_positions), std::move(indices), shader_cache) {}
