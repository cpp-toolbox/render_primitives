#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "sbpt_generated_includes.hpp"

class Drawable {
  public:
    ShaderType shader_type;
    ShaderCache &shader_cache;
    Drawable(ShaderType shader_type, ShaderCache &shader_cache)
        : shader_type(shader_type), shader_cache(shader_cache){};
    virtual void draw() = 0;
};

#endif // CLIENT_DRAWABLE_HPP
