#ifndef DIVPLO_SOLID_COLOR_HPP
#define DIVPLO_SOLID_COLOR_HPP

#include "divp_linear_order.hpp"

/**
 * \brief Drawable Indexed Vertex Positions (in) Linear Order (drawn with) Solid Color
 * \details Colored a single solid color (with alpha), r g b a are specified by intensity in [0, 1]
 */
class DivploSolidColor : public DivpLinearOrder {
    float r, g, b, alpha;

  public:
    DivploSolidColor(float r, float g, float b, float alpha, std::vector<glm::vec3> vertex_positions,
                     std::vector<unsigned int> indices, ShaderCache &shader_cache);
    void draw();
};

#endif // DIVPLO_SOLID_COLOR_HPP
