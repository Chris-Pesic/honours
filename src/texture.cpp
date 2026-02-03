#include "texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int LoadTexture2D(const char* path, bool flipVertically){

    stbi_set_flip_vertically_on_load(flipVertically);

    int w = 0, h = 0, channels = 0;
    unsigned char* data = stbi_load(path, &w, &h, &channels, 0);

    if (!data){
        std::cerr << "Failed to load texture: " << path << std::endl;
        return 0;
    }

    GLenum format = GL_RGB;
    GLenum internalFormat = GL_RGB;

    if (channels == 1){
        format = GL_RED;
        internalFormat = GL_RED;
    }

    else if (channels == 3){
        format = GL_RGB;
        internalFormat = GL_RGB;
    }

    else if (channels == 4){
        format = GL_RGBA;
        internalFormat = GL_RGBA;
    }

    else{
        std::cerr << "Unsupported channel count (" << channels << ") for texture: " << path << std::endl;
        stbi_image_free(data);
        return 0;
    }

    GLuint texID = 0;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texID;
}