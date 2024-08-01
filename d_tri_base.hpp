#ifndef TRI_BASE_HPP
#define TRI_BASE_HPP

#include "../shader_pipeline/shader_pipeline.hpp"

/*
 * \brief draws triangles through a list of sequential vertex_positions without a custom indexing
 *
 * \desc you can specify the draw mode which allows you do to things like triangle fan etc...
 */
class DTriBase {
  public:
    int num_flattened_vertices, num_vertices;
    float *flattened_vertices;
    DTriBase(unsigned int draw_mode, float flattened_vertices[], int num_flattened_vertices, float r, float g, float b);
    void draw();
    void update_vertices(float flattened_vertices[], int num_flattened_vertices);
    ShaderPipeline shader_pipeline;

  private:
    unsigned int vertex_attribute_object, vertex_buffer_object, draw_mode;
    void bind_index_vertex_data_to_opengl_for_later_use() const;
    void bind_vertex_attribute_interpretation_to_opengl_for_later_use() const;
    void generate_opengl_vertex_array_and_buffers();
    void set_color_in_shader(float r, float g, float b) const;
};

#endif // D_TRI_BASE_HPP
