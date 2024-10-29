#ifndef DIFFUSE_TEXTURED_DIV_HPP
#define DIFFUSE_TEXTURED_DIV_HPP

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "divp_linear_order.hpp"

#include "sbpt_generated_includes.hpp"

/**
 * \brief Drawable Indexed Vertex Positions (in) Linear Order (which is) Diffuse Textured
 *
 * \details When you see an object in real life, this is because light hit that object and bounced into your eye.
 * The term "diffuse" describes how the light is spread out over the surface rather than being concentrated in one
 * direction, this scattering is responsible for the basic color of objects as perceived by the human eye under uniform
 * lighting conditions.
 *
 * Therefore the name for regular old textures are "diffuse textures" or "diffuse maps", because they give it their
 * fundamental color, also later on they can actually be used to compute lighting, if necessary.
 *
 * \author cuppajoeman
 */
class DivploDiffuseTextured : public DivpLinearOrder {
  public:
    DivploDiffuseTextured(ShaderType shader_type, std::vector<glm::vec3> vertex_positions,
                          std::vector<unsigned int> indices, std::vector<glm::vec2> texture_coordinates,
                          std::string diffuse_texture_path, ShaderCache &shader_cache,
                          OpenGLTextureCache &gl_texture_cache);

    DivploDiffuseTextured(ShaderType shader_type, TexturedMesh textured_mesh, ShaderCache &shader_cache,
                          OpenGLTextureCache &gl_texture_cache);

    unsigned int opengl_texture_id;
    std::vector<glm::vec2> texture_coordinates;
    std::string diffuse_texture_path;
    OpenGLTextureCache &gl_texture_cache;

    unsigned int vertex_texture_coordinate_buffer_object;

    void bind_texture_coordinates_to_opengl_for_later_use();
    void generate_and_bind_textures_to_opengl();
    void bind_vertex_texture_coordinate_attribute_interpretation_to_opengl_for_later_use();
    void generate_opengl_vertex_texture_coordinate_buffer();

  public:
    void draw();
};

#endif // DIFFUSE_TEXTURED_DIV_HPP
