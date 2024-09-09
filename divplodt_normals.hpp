#ifndef DIVPLODT_NORMALS_HPP
#define DIVPLODT_NORMALS_HPP

#include "divplo_diffuse_textured.hpp"

/**
 * @brief Divplodt (using) Normals
 */
class DivplodtNormals : public DivploDiffuseTextured {
public:
    DivplodtNormals (ShaderType shader_type, TexturedMesh textured_mesh, ShaderCache &shader_cache, OpenGLTextureCache &gl_texture_cache);

    void generate_opengl_vertex_normals_buffer();
    void bind_vertex_normals_attribute_interpretation_to_opengl_for_later_use();
    void bind_normals_to_opengl_for_later_use();

    std::vector<glm::vec3> vertex_normals;
    unsigned int vertex_normals_buffer_object;

};

#endif // DIVPLODT_NORMALS_HPP
