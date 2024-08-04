#include "div_cubemap.hpp"
#include "sbpt_generated_includes.hpp"

std::vector<glm::vec3> cube_vertex_positions =

    {                          //   Coordinates
        {-1.0f, -1.0f, 1.0f},  //        7--------6
        {1.0f, -1.0f, 1.0f},   //       /|       /|
        {1.0f, -1.0f, -1.0f},  //      4--------5 |
        {-1.0f, -1.0f, -1.0f}, //      | |      | |
        {-1.0f, 1.0f, 1.0f},   //      | 3------|-2
        {1.0f, 1.0f, 1.0f},    //      |/       |/
        {1.0f, 1.0f, -1.0f},   //      0--------1
        {-1.0f, 1.0f, -1.0f}};

std::vector<unsigned int> cube_vertex_indices = { // Right
    1, 2, 6, 6, 5, 1,
    // Left
    0, 4, 7, 7, 3, 0,
    // Top
    4, 5, 6, 6, 7, 4,
    // Bottom
    0, 3, 2, 2, 1, 0,
    // Back
    0, 1, 5, 5, 4, 0,
    // Front
    3, 7, 6, 6, 2, 3};

std::string remove_trailing_slash(const std::string &path) {
    // Check if the path is empty
    if (path.empty()) {
        return path;
    }

    // Copy the input path to modify it
    std::string result = path;

    // Check if the last character is a slash and remove it if necessary
    if (result.back() == '/' || result.back() == '\\') {
        result.pop_back();
    }

    return result;
}

CubeMap::CubeMap(const std::string &cube_map_dir, const std::string &file_extension, ShaderType shader_type,
                 ShaderCache &shader_cache)
    : Div(shader_type, cube_vertex_positions, cube_vertex_indices, shader_cache) {

    glGenTextures(1, &opengl_texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, opengl_texture_id);

    std::function<std::string(std::string)> create_path = [&](std::string file_name) {
        return remove_trailing_slash(cube_map_dir) + "/" + file_name + "." + file_extension;
    };

    std::unordered_map<GLenum, std::string> gl_texture_target_to_path = {
        {GL_TEXTURE_CUBE_MAP_POSITIVE_X, create_path("right")}, {GL_TEXTURE_CUBE_MAP_NEGATIVE_X, create_path("left")},
        {GL_TEXTURE_CUBE_MAP_POSITIVE_Y, create_path("up")},    {GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, create_path("down")},
        {GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, create_path("back")},  {GL_TEXTURE_CUBE_MAP_POSITIVE_Z, create_path("front")}};

    // Iterating using range-based for loop
    for (const auto &pair : gl_texture_target_to_path) {
        GLenum target = pair.first;
        const std::string &path = pair.second;
        TextureData texture_info = load_texture_from_file(path);
        glTexImage2D(target, 0, GL_RGB, texture_info.width, texture_info.height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     texture_info.image_data.data());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeMap::draw() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, opengl_texture_id);
    Div::draw();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
