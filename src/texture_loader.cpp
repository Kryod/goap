#include <vector>

#define CUTE_FILES_IMPLEMENTATION
#include "cute_files.h"

#include "m_assert.h"
#include "texture_loader.h"

TextureLoader::TextureLoader() {
    std::vector<std::string> texturePaths =
        TextureLoader::listTextures("resources/textures");

    for (const std::string& path : texturePaths) {
        std::string fileName = path.substr(0, path.find_last_of('.'));
        this->textures[fileName] = sf::Texture();
        this->textures[fileName].setSmooth(true);
        this->textures[fileName].loadFromFile(path);
    }
}

TextureLoader& TextureLoader::instance() {
    static TextureLoader instance;
    return instance;
}

std::vector<std::string>
TextureLoader::listTextures(const std::string& rootDir) {
    std::vector<std::string> paths;

    cf_dir_t root;
    cf_dir_open(&root, rootDir.c_str());

    while (root.has_next) {
        cf_file_t dir;
        cf_read_file(&root, &dir);

        if (dir.is_dir && strcmp(dir.name, ".") && strcmp(dir.name, "..")) {
            cf_dir_t tDir;
            cf_dir_open(&tDir, dir.path);
            while (tDir.has_next) {
                cf_file_t file;
                cf_read_file(&tDir, &file);
                if (file.is_reg && !strcmp(file.ext, ".png")) {
                    paths.push_back(file.path);
                }
                cf_dir_next(&tDir);
            }
            cf_dir_close(&tDir);
        }
        cf_dir_next(&root);
    }
    cf_dir_close(&root);

    return paths;
}

const sf::Texture* TextureLoader::get(const std::string& name) const {
    std::string key = "resources/textures/" + name;
    M_ASSERT(this->textures.find(key) != this->textures.end(), "Texture \"" + key + "\" not found");
    return &this->textures.at(key);
}
