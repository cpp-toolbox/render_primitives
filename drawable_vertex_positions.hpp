#ifndef DRAWABLE_VERTEX_POSITIONS_HPP
#define DRAWABLE_VERTEX_POSITIONS_HPP

#include <vector>
#include "sbpt_generated_includes.hpp"
#include "drawable.hpp"

/**
 * \brief (D.V) Drawable Vertices: draws triangles through a list of sequential vertex_positions without a custom
 * indexing
 * \desc you can specify the draw mode which allows you do to things like triangle fan etc...
 * \author cuppajoeman
 */
class DrawableVertexPositions : public Drawable {

  public:
    std::vector<glm::vec3> vertex_positions;
    DrawableVertexPositions(unsigned int draw_mode, std::vector<glm::vec3> vertex_positions, ShaderType shader_type,
                            ShaderCache &shader_cache);
    void draw() override;
    void update_vertices(std::vector<glm::vec3> vertex_positions);
    unsigned int vertex_attribute_object, vertex_position_buffer_object, draw_mode;
};

#endif // DRAWABLE_VERTEX_POSITIONS_HPP
