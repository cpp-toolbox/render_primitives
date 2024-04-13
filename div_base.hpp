#ifndef DIV_HPP
#define DIV_HPP

#include "../shader_pipeline/shader_pipeline.hpp"

// Drawable Indexed Vertices
/*
 * \brief a class which allows you to draw triangles with a custom index order
 */
class DivBase {
  public:
    int num_vertices, num_indices;
    float *vertices;
    unsigned int *indices;
    DivBase(unsigned int draw_mode, float vertices[], int num_vertices, unsigned int indices[], int num_indices,
            float r, float g, float b);
    void draw();
    void update_vertices_and_indices(float vertices[], int num_vertices, unsigned int indices[], int num_indices);
    ShaderPipeline shader_pipeline;

  private:
    unsigned int vertex_attribute_object, vertex_buffer_object, index_buffer_object, draw_mode;
    void bind_index_vertex_data_to_opengl_for_later_use() const;
    void bind_vertex_attribute_interpretation_to_opengl_for_later_use() const;
    void generate_opengl_vertex_array_and_buffers();

    void set_color_in_shader(float r, float g, float b) const;
};

#endif // DIV_HPP
