#ifndef DIV_CUBEMAP_HPP
#define DIV_CUBEMAP_HPP

#include "div.hpp"
#include <iostream>
#include <string>

/**
 * \note a cubemap dir must contain the files left, right, top, bottom, front, back .ext files
 */
class CubeMap : public Div {
  public:
    CubeMap(const std::string &cube_map_dir, const std::string &file_extension, ShaderType shader_type,
            ShaderCache &shader_cache);

    unsigned int opengl_texture_id;
    void draw();
};

#endif // DIV_CUBEMAP_HPP