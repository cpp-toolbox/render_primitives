#include "dvp_solid_color.hpp"

void DvpSolidColor::draw() {
    shader_cache.use_shader_program(ShaderType::ABSOLUTE_POSITION_WITH_SOLID_COLOR);
    glm::vec4 color(r, g, b, alpha);
    shader_cache.set_uniform(ShaderType::ABSOLUTE_POSITION_WITH_SOLID_COLOR, ShaderUniformVariable::COLOR, color);
    DrawableVertexPositions::draw();
    shader_cache.stop_using_shader_program();
}