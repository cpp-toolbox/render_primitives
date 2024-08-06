// #include <cassert>
#include "drawable_vertex_positions.hpp"

DrawableVertexPositions::DrawableVertexPositions(unsigned int draw_mode, std::vector<glm::vec3> vertex_positions,
                                                 ShaderType shader_type, ShaderCache &shader_cache)
    : draw_mode(draw_mode), vertex_positions(vertex_positions), Drawable(shader_type, shader_cache) {

    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_position_buffer_object);

    glBindVertexArray(vertex_attribute_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_position_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertex_positions.size() * sizeof(glm::vec3), vertex_positions.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);

    shader_cache.configure_vertex_attributes_for_drawables_vao(vertex_attribute_object, vertex_position_buffer_object,
                                                               shader_type, ShaderVertexAttributeVariable::POSITION);
}

void DrawableVertexPositions::draw() {
    shader_cache.use_shader_program(shader_type);
    glBindVertexArray(vertex_attribute_object);
    glDrawArrays(draw_mode, 0, vertex_positions.size());
    glBindVertexArray(0); // unbinds current vertex_attribute_object
    shader_cache.stop_using_shader_program();
}
