#ifndef DIV_CUBEMAP_HPP
#define DIV_CUBEMAP_HPP

#include "divp_linear_order.hpp"
#include <string>

/**
 * \brief Drawable Index Vertex Positions (in) Linear Order (representing a) Cube Map
 * \pre a cubemap dir must contain the files left, right, top, bottom, front, back .ext files
 * \author cuppajoeman
 */
class DivploCubeMap : public DivpLinearOrder {
  public:
    DivploCubeMap(const std::string &cube_map_dir, const std::string &file_extension, ShaderType shader_type,
            ShaderCache &shader_cache);

    unsigned int opengl_texture_id;
    void draw();
};

#endif // DIV_CUBEMAP_HPP
