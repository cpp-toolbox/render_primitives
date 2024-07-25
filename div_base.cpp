#include "div_base.hpp"
#include "glad/glad.h"
#include <cstdio>

void DivBase::draw() {
    glUseProgram(shader_pipeline.shader_program_id);
    glBindVertexArray(vertex_attribute_object);
    glDrawElements(this->draw_mode, this->num_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // unbinds current vertex_attribute_object
}

void DivBase::generate_opengl_vertex_array_and_buffers() {
    glGenVertexArrays(1, &vertex_attribute_object);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &index_buffer_object);
}

void DivBase::bind_index_vertex_data_to_opengl_for_later_use() const {

    glBindVertexArray(vertex_attribute_object);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, this->num_vertices * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->num_indices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}


void DivBase::bind_vertex_attribute_interpretation_to_opengl_for_later_use() const {
    // vertex positions
    GLuint position_attribute_location = glGetAttribLocation(shader_pipeline.shader_program_id, "position");
    glEnableVertexAttribArray(position_attribute_location);
    glVertexAttribPointer(position_attribute_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
}

/**
 * precondition: opengl must be configured first
 */
DivBase::DivBase(unsigned int draw_mode, float vertices[], int num_vertices, unsigned int indices[], int num_indices,
                 float r, float g, float b) {
    shader_pipeline.load_in_shaders_from_file("../graphics/shaders/absolute_position.vert",
                                              "../graphics/shaders/absolute_position_with_color_uniform.frag");
    this->set_color_in_shader(r, g, b);
    this->draw_mode = draw_mode;
    this->generate_opengl_vertex_array_and_buffers();
    this->update_vertices_and_indices(vertices, num_vertices, indices, num_indices);
    this->bind_vertex_attribute_interpretation_to_opengl_for_later_use();
}


void DivBase::update_vertices_and_indices(float vertices[], int num_vertices, unsigned int indices[], int num_indices) {
    this->vertices = vertices;
    this->num_vertices = num_vertices;
    this->indices = indices;
    this->num_indices = num_indices;
    this->bind_index_vertex_data_to_opengl_for_later_use();
}

/**
 * \pre the shader pipeline has loaded in shaders
 */
void DivBase::set_color_in_shader(float r, float g, float b) const {
    glUseProgram(this->shader_pipeline.shader_program_id);
    int color_uniform_location = glGetUniformLocation(this->shader_pipeline.shader_program_id, "color");
    glUniform4f(color_uniform_location, r, g, b, 1.0f);
    glUseProgram(0);
}
