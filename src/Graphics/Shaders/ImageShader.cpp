#include "ImageShader.h"

ImageShader::ImageShader(GLData& _glData) : Shader(_glData, "image"), defaultColor({}), normalID(0), textureID(0) {
    textureSize = glm::vec2(1.0f, 1.0f);
    textureCorner = glm::vec2(0.0f, 0.0f);
}

void ImageShader::setCustomUniforms() {
    glUniform3fv(glGetUniformLocation(programID, "defaultColor"), 1, &defaultColor[0]);
    glUniform1f(glGetUniformLocation(programID, "image"), image ? 1.0f : 0.0f);
    //glUniform1f(glGetUniformLocation(programID, "normal"), normal ? 1.0f : 0.0f);
    glUniform1f(glGetUniformLocation(programID, "grayscale"), grayscale ? 1.0f : 0.0f);
    glUniform1f(glGetUniformLocation(programID, "darken"), darken ? 1.0f : 0.0f);
    glUniform1f(glGetUniformLocation(programID, "effect"), effect);
    glUniform2fv(glGetUniformLocation(programID, "mouse"), 1, &mouse[0]);
    setClippingUniforms();
    setTextureUniforms();
}

void ImageShader::setTexture(GLuint _textureID)
{
    textureID = _textureID;
}

void ImageShader::setNormal(GLuint _textureID)
{
    normalID = _textureID;
}

void ImageShader::setTexture(std::string textureName) {
    setTexture(glData.getTexture(textureName));
}
void ImageShader::setNormal(std::string normalName) {
    setNormal(glData.getTexture(normalName));
}

void ImageShader::setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner)
{
    textureSize = _textureSize;
    textureCorner = _textureCorner;
}

void ImageShader::setClippingUniforms()
{
    glUniform2fv(glGetUniformLocation(programID, "inTexCoord"), 1, &textureCorner[0]);
    glUniform2fv(glGetUniformLocation(programID, "textureSize"), 1, &textureSize[0]);
}

void ImageShader::setTextureUniforms()
{
    GLuint mTex1Handle0 = glGetUniformLocation(programID, "tex");
    glUniform1i(mTex1Handle0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    /*if (normal)
    {
        GLuint mTex1Handle1 = glGetUniformLocation(programID, "normalMap");
        glUniform1i(mTex1Handle1, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalID);
    }*/
}

