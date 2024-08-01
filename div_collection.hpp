#ifndef DIV_COLLECTION_HPP
#define DIV_COLLECTION_HPP

#include "div.hpp"
#include "diffuse_textured_div.hpp"
#include <vector>

class DivCollection {
    std::vector<Div> divs;
    DivCollection(std::vector<Div> divs);
    void draw();
};

class DiffuseTexturedDivCollection {
    std::vector<DiffuseTexturedDiv> tdts;

  public:
    void draw();
    //    DiffuseTexturedDivCollection(std::vector<DiffuseTexturedDivCollection> tdts, OpenGLTextureCache
    //    &gl_texture_cache);
    DiffuseTexturedDivCollection(ShaderType shader_type, TexturedModel &textured_model, ShaderCache &shader_cache,
                                 OpenGLTextureCache &gl_texture_cache);
};

#endif // DIV_COLLECTION_HPP
