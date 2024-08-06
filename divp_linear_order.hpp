#ifndef GRADIENT_DESCENT_DIV_HPP
#define GRADIENT_DESCENT_DIV_HPP

#include "drawable_indexed_vertex_positions.hpp"
#include "sbpt_generated_includes.hpp"

/**
 * \brief Drawable Indexed Vertex Positions (in) Linear Order
 */
class DivpLinearOrder : public DrawableIndexedVertexPositions {
  public:
    DivpLinearOrder(ShaderType shader_type, std::vector<glm::vec3> vertex_positions, std::vector<unsigned int> indices,
                    ShaderCache &shader_cache);
};

#endif // GRADIENT_DESCENT_DIV_HPP
