#include "divplo_collection.hpp"

void DivploCollection::draw() {
    for (auto div : divs) {
        div.draw();
    }
}

DivplodtCollection::DivplodtCollection(ShaderType shader_type, TexturedModel &textured_model, ShaderCache &shader_cache,
                                       OpenGLTextureCache &gl_texture_cache) {
    for (const auto &textured_mesh : textured_model) {
        tdts.emplace_back(shader_type, textured_mesh, shader_cache, gl_texture_cache);
    }
}

void DivplodtCollection::draw() {
    for (auto tdt : tdts) {
        tdt.draw();
    }
}
