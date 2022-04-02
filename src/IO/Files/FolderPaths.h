#include <string>

#ifndef FOLDERPATHS_H
#define FOLDERPATHS_H

class FolderPaths{

public:

static std::string getShaderPath();
static std::string getModelsPath();
static std::string getTexturesPath();
static std::string getNormalTexturesPath();
static std::string getFontsPath();
static std::string getResPath();

};

#endif