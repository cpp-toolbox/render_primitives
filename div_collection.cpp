#include "div_collection.hpp"

void DivCollection::draw() {
    for (auto div : divs) {
        div.draw();
    }
}

DiffuseTexturedDivCollection::DiffuseTexturedDivCollection(ShaderType shader_type, TexturedModel &textured_model,
                                                           ShaderCache &shader_cache,
                                                           OpenGLTextureCache &gl_texture_cache) {
    for (const auto &textured_mesh : textured_model.meshes) {
        tdts.emplace_back(shader_type, textured_mesh, shader_cache, gl_texture_cache);
    }
}

void DiffuseTexturedDivCollection::draw() {
    for (auto tdt : tdts) {
        tdt.draw();
    }
}
