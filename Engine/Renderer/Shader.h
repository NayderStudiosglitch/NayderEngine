#pragma once
#include <string>

class NayderShaderCompiler {
public:
    unsigned int ProgramID;

    NayderShaderCompiler();
    bool LoadAndCompileShaders(const std::string& vertex_path, const std::string& fragment_path);
    void UseShaderProgram();
    void CleanUpShaderMemory();
};
