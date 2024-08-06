#include "divplo_diffuse_textured.hpp"
#include <spdlog/spdlog.h>

#include <utility>

DivploDiffuseTextured::DivploDiffuseTextured(ShaderType shader_type, std::vector<glm::vec3> vertex_positions,
                                             std::vector<unsigned int> indices,
                                             std::vector<glm::vec2> texture_coordinates,
                                             std::string diffuse_texture_path, ShaderCache &shader_cache,
                                             OpenGLTextureCache &gl_texture_cache)
    : DivpLinearOrder(shader_type, std::move(vertex_positions), std::move(indices), shader_cache),
      texture_coordinates(std::move(texture_coordinates)), diffuse_texture_path(std::move(diffuse_texture_path)),
      gl_texture_cache(gl_texture_cache) {
    generate_and_bind_textures_to_opengl();
    generate_opengl_vertex_texture_coordinate_buffer();
    bind_texture_coordinates_to_opengl_for_later_use();
    bind_vertex_texture_coordinate_attribute_interpretation_to_opengl_for_later_use();
};

DivploDiffuseTextured::DivploDiffuseTextured(ShaderType shader_type, TexturedMesh textured_mesh,
                                             ShaderCache &shader_cache, OpenGLTextureCache &gl_texture_cache)
    : DivpLinearOrder(shader_type, textured_mesh.vertex_positions, textured_mesh.indices, shader_cache),
      texture_coordinates(textured_mesh.texture_coordinates),
      diffuse_texture_path(textured_mesh.used_textures.front().path), gl_texture_cache(gl_texture_cache) {
    generate_and_bind_textures_to_opengl();
    generate_opengl_vertex_texture_coordinate_buffer();
    bind_texture_coordinates_to_opengl_for_later_use();
    bind_vertex_texture_coordinate_attribute_interpretation_to_opengl_for_later_use();
};

void DivploDiffuseTextured::bind_vertex_texture_coordinate_attribute_interpretation_to_opengl_for_later_use() {
    shader_cache.configure_vertex_attributes_for_drawables_vao(
        vertex_attribute_object, vertex_texture_coordinate_buffer_object, shader_type,
        ShaderVertexAttributeVariable::PASSTHROUGH_TEXTURE_COORDINATE);
}

void DivploDiffuseTextured::generate_opengl_vertex_texture_coordinate_buffer() {
    glGenBuffers(1, &vertex_texture_coordinate_buffer_object);
}

void DivploDiffuseTextured::bind_texture_coordinates_to_opengl_for_later_use() {
    glBindVertexArray(vertex_attribute_object);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_texture_coordinate_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, texture_coordinates.size() * sizeof(glm::vec2), texture_coordinates.data(),
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void DivploDiffuseTextured::generate_and_bind_textures_to_opengl() {
    opengl_texture_id = gl_texture_cache.load_texture(diffuse_texture_path);
}

/**
 * \note the texture calls don't have to be within a vao context because apparently texture are just global in opengl
 */
void DivploDiffuseTextured::draw() {
    glBindTexture(GL_TEXTURE_2D, opengl_texture_id);
    DivpLinearOrder::draw();
    glBindTexture(GL_TEXTURE_2D, 0);
}