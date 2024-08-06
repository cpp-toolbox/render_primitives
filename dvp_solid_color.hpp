#ifndef DVP_SOLID_COLOR_HPP
#define DVP_SOLID_COLOR_HPP

#include "drawable_vertex_positions.hpp"

/**
 * \brief a dvp which is colored a single solid color (with alpha), r g b a are specified by intensity in [0, 1]
 */
class DvpSolidColor : DrawableVertexPositions {
    float r, g, b, alpha;

  public:
    DvpSolidColor(float r, float g, float b, float alpha, unsigned int draw_mode,
                  std::vector<glm::vec3> vertex_positions, ShaderCache &shader_cache)
        : DrawableVertexPositions(draw_mode, std::move(vertex_positions),
                                  ShaderType::ABSOLUTE_POSITION_WITH_SOLID_COLOR, shader_cache),
          r(r), g(g), b(b), alpha(alpha){};
    void draw();
};

#endif // DVP_SOLID_COLOR_HPP
