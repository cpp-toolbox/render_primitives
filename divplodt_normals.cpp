#include "divplodt_normals.hpp"
#include "divplo_diffuse_textured.hpp"

DivplodtNormals::DivplodtNormals(ShaderType shader_type, TexturedMesh textured_mesh, ShaderCache &shader_cache, OpenGLTextureCache &gl_texture_cache) : DivploDiffuseTextured(shader_type, textured_mesh, shader_cache, gl_texture_cache), vertex_normals(textured_mesh.normals){
    generate_opengl_vertex_normals_buffer();
    bind_normals_to_opengl_for_later_use();
    bind_vertex_normals_attribute_interpretation_to_opengl_for_later_use();
}

void DivplodtNormals::generate_opengl_vertex_normals_buffer() {
    glGenBuffers(1, &vertex_normals_buffer_object);
}

void DivplodtNormals::bind_normals_to_opengl_for_later_use() {
    glBindVertexArray(vertex_attribute_object);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_normals_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertex_normals.size() * sizeof(glm::vec3), vertex_normals.data(),
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void DivplodtNormals::bind_vertex_normals_attribute_interpretation_to_opengl_for_later_use() {
    shader_cache.configure_vertex_attributes_for_drawables_vao(
        vertex_attribute_object, vertex_normals_buffer_object, shader_type,
        ShaderVertexAttributeVariable::PASSTHROUGH_NORMAL);
}
