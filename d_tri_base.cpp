//
// Created by ccn on 30/03/24.
//

#include <cassert>
#include "d_tri_base.hpp"

void DTriBase::draw() {
    glUseProgram(shader_pipeline.shader_program_id);
    glBindVertexArray(vertex_attribute_object);
    glDrawArrays(this->draw_mode, 0, this->num_vertices);
    glBindVertexArray(0); // unbinds current vertex_attribute_object
}

void DTriBase::generate_opengl_vertex_array_and_buffers() {
    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_buffer_object);
}

void DTriBase::bind_index_vertex_data_to_opengl_for_later_use() const {
    glBindVertexArray(vertex_attribute_object);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, this->num_flattened_vertices * sizeof(float), flattened_vertices, GL_STATIC_DRAW);
}


void DTriBase::bind_vertex_attribute_interpretation_to_opengl_for_later_use() const {
    // vertex positions
    GLuint position_attribute_location = glGetAttribLocation(shader_pipeline.shader_program_id, "position");
    glEnableVertexAttribArray(position_attribute_location);
    glVertexAttribPointer(position_attribute_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
}

/**
 * precondition: opengl must be configured first
 */
DTriBase::DTriBase(unsigned int draw_mode, float flattened_vertices[], int num_flattened_vertices) {
    shader_pipeline.load_in_shaders_from_file("../graphics/shaders/absolute_position.vert", "../graphics/shaders/absolute_position_with_color_uniform.frag");
    assert(num_flattened_vertices % 3 == 0);
    this->num_vertices = num_flattened_vertices / 3;
    this->draw_mode = draw_mode;
    this->generate_opengl_vertex_array_and_buffers();
    this->update_vertices(flattened_vertices, num_flattened_vertices);
    this->bind_vertex_attribute_interpretation_to_opengl_for_later_use();
}


void DTriBase::update_vertices(float flattened_vertices[], int num_flattened_vertices) {
    this->flattened_vertices = flattened_vertices;
    this->num_flattened_vertices = num_flattened_vertices;
    this->bind_index_vertex_data_to_opengl_for_later_use();
}
