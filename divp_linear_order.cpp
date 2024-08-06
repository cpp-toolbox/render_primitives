#include "divp_linear_order.hpp"
#include <cstdio>
#include <utility>

/**
 * \brief Drawable Indexed Vertex Positions Linear Order
 * \pre there is an active opengl context
 */

DivpLinearOrder::DivpLinearOrder(ShaderType shader_type, std::vector<glm::vec3> vertex_positions,
                                 std::vector<unsigned int> indices, ShaderCache &shader_cache)
    : DrawableIndexedVertexPositions(shader_type, GL_TRIANGLES, std::move(vertex_positions), std::move(indices),
                                     shader_cache) {}
