#ifndef DIV_COLLECTION_HPP
#define DIV_COLLECTION_HPP

#include "divp_linear_order.hpp"
#include "divplo_diffuse_textured.hpp"
#include "divplodt_normals.hpp"
#include <vector>

/**
 * \brief Drawable Indexed Vertex Positions (in) Linear Order Collection
 */
class DivploCollection {
    std::vector<DivpLinearOrder> divs;
    DivploCollection(std::vector<DivpLinearOrder> divs);
    void draw();
};

/**
 * \brief Drawable Indexed Vertex Positions (in) Linear Order (which are) Diffuse Textured Collection
 */
class DivplodtCollection {
    std::vector<DivploDiffuseTextured> tdts;

  public:
    void draw();
    //    DiffuseTexturedDivCollection(std::vector<DiffuseTexturedDivCollection> tdts, OpenGLTextureCache
    //    &gl_texture_cache);
    DivplodtCollection(ShaderType shader_type, TexturedModel &textured_model, ShaderCache &shader_cache,
                                 OpenGLTextureCache &gl_texture_cache);
};

class DivplodtnCollection {
    std::vector<DivplodtNormals> drawables;

  public:
    void draw();
    //    DiffuseTexturedDivCollection(std::vector<DiffuseTexturedDivCollection> tdts, OpenGLTextureCache
    //    &gl_texture_cache);
    DivplodtnCollection(ShaderType shader_type, TexturedModel &textured_model, ShaderCache &shader_cache,
                                 OpenGLTextureCache &gl_texture_cache);
};

#endif // DIV_COLLECTION_HPP
