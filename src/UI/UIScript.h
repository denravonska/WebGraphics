#include <string>
#include <sol/sol.hpp>
#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include <IO/Files/FileChecker.h>

#ifndef UISCRIPT_H
#define UISCRIPT_H

class UIScript
{
    Engine& engine;
    Graphics& graphics;

    sol::state lua;
    sol::load_result script;
    sol::function scriptUpdate, scriptRender;

    std::string scriptFileName;
    FileChecker fileChecker;
    std::string getScriptFilePath();
    bool loaded = false;
    bool load();
    void printError(sol::protected_function_result& result);
    void printError(sol::load_result& result);
    sol::protected_function_result testScriptValidity();
    void setUserTypes();

public:
    UIScript(std::string _scriptFileName, Engine& _engine);
    ~UIScript();
    void render();
    void update();

};

#endif
