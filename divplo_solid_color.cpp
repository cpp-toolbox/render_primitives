#include "divplo_solid_color.hpp"

DivploSolidColor::DivploSolidColor(float r, float g, float b, float alpha, std::vector<glm::vec3> vertex_positions,
                                   std::vector<unsigned int> indices, ShaderCache &shader_cache)
    : DivpLinearOrder(ShaderType::ABSOLUTE_POSITION_WITH_SOLID_COLOR, std::move(vertex_positions), std::move(indices),
                      shader_cache),
      r(r), g(g), b(b), alpha(alpha){};

/**
 * \pre the shader program type associated with this div is bound to the opengl context, todo (should we be doing it
 * this way?)
 *
 */
void DivploSolidColor::draw() {
    shader_cache.use_shader_program(ShaderType::ABSOLUTE_POSITION_WITH_SOLID_COLOR);
    glm::vec4 color(r, g, b, alpha);
    shader_cache.set_uniform(ShaderType::ABSOLUTE_POSITION_WITH_SOLID_COLOR, ShaderUniformVariable::COLOR, color);
    DivpLinearOrder::draw();
    shader_cache.stop_using_shader_program();
}