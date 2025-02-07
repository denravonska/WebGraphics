
#ifndef IMAGESHADER_H
#define IMAGESHADER_H
#include "Shader.h"
#include "IO/Files/Texture/IOTexture.h"

class ImageShader : public Shader {

    IOTexture& iotexture;
    virtual void setCustomUniforms() override;
    GLuint textureID;
    GLuint normalID;

    void setClippingUniforms();
    void setTextureUniforms();

public:

    ImageShader();

    glm::vec3 defaultColor;
    bool image = true;
    bool grayscale = false;
    bool darken = false;
    float fade = 0.08;
    float thickness = 0.1f;
    float radius = 0.5f;
    glm::vec2 mouse = {0.0f,0.0f};
    glm::vec2 textureSize, textureCorner;

    void setTexture(GLuint _textureID);
    void setNormal(GLuint _textureID);
    void setTexture(std::string textureName);
    void setNormal(std::string normalName);

    void setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner);
};

#endif // !IMAGESHADER_H
