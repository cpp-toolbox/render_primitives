#include "div_base.hpp"
#include "glad/glad.h"
#include <cstdio>
#include <vector>

/**
 * \pre the associated shader program is bound
 * \brief draws the geometry this object
 */
void DivBase::draw() {
    shader_cache.use_shader_program(shader_type);
    glBindVertexArray(vertex_attribute_object);
    glDrawElements(this->draw_mode, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // unbinds current vertex_attribute_object
    glUseProgram(0);      // unbinds currently bound shader program
}

void DivBase::generate_opengl_vertex_array_and_buffers() {
    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_position_buffer_object);
    glGenBuffers(1, &index_buffer_object);
}

/**
 * \details given a collection of vertex geometry and indices bind them into this objects vao within the opengl context
 */
void DivBase::bind_index_vertex_data_to_opengl_for_later_use() {
    glBindVertexArray(vertex_attribute_object);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_position_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertex_positions.size() * sizeof(glm::vec3), vertex_positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void DivBase::bind_vertex_attribute_interpretation_to_opengl_for_later_use() {
    shader_cache.configure_vertex_attributes_for_drawables_vao(vertex_attribute_object, vertex_position_buffer_object,
                                                               shader_type, ShaderVertexAttributeVariable::POSITION);
}

/**
 * \pre there must be an active opengl context
 */
DivBase::DivBase(ShaderType shader_type, unsigned int draw_mode, std::vector<glm::vec3> vertex_positions,
                 std::vector<unsigned int> indices, ShaderCache &shader_cache)
    : shader_type(shader_type), draw_mode(draw_mode), shader_cache(shader_cache) {
    this->generate_opengl_vertex_array_and_buffers();
    this->bind_index_vertex_data_to_opengl_for_later_use();
    this->bind_vertex_attribute_interpretation_to_opengl_for_later_use();
    this->update_vertices_and_indices(vertex_positions, indices);
}

void DivBase::update_vertices_and_indices(std::vector<glm::vec3> vertex_positions, std::vector<unsigned int> indices) {
    this->vertex_positions = std::move(vertex_positions);
    this->indices = std::move(indices);
    this->bind_index_vertex_data_to_opengl_for_later_use();
};
