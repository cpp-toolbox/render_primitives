#ifndef DIV_HPP
#define DIV_HPP

#include <vector>
#include <glm/glm.hpp>
#include "sbpt_generated_includes.hpp"

// Drawable Indexed Vertices
/*
 * \brief a class which allows you to draw triangles with a custom index order
 */
class DivBase {
  public:
    std::vector<glm::vec3> vertex_positions;
    std::vector<unsigned int> indices;
    DivBase(ShaderType shader_type, unsigned int draw_mode, std::vector<glm::vec3> vertex_positions,
            std::vector<unsigned int> indices, ShaderCache &shader_cache);
    void draw();
    void update_vertices_and_indices(std::vector<glm::vec3> vertex_positions, std::vector<unsigned int> indices);
    unsigned int vertex_attribute_object, vertex_position_buffer_object, index_buffer_object, draw_mode;
    ShaderType shader_type;
    ShaderCache &shader_cache;

  private:
    void bind_vertex_attribute_interpretation_to_opengl_for_later_use();
    void bind_index_vertex_data_to_opengl_for_later_use();
    void generate_opengl_vertex_array_and_buffers();
};

#endif // DIV_HPP
