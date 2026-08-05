#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>

// Define OpenGL core extension function pointers natively so we don't need external heavy glad/glew libraries
typedef GLuint (APIENTRY *PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRY *PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
typedef void (APIENTRY *PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void (APIENTRY *PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* param);
typedef void (APIENTRY *PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef GLuint (APIENTRY *PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRY *PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRY *PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint* param);
typedef void (APIENTRY *PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void (APIENTRY *PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRY *PFNGLDELETESHADERPROC) (GLuint shader);

// Function Pointer Storage Instances
PFNGLCREATESHADERPROC    glCreateShader_ptr = nullptr;
PFNGLSHADERSOURCEPROC    glShaderSource_ptr = nullptr;
PFNGLCOMPILESHADERPROC   glCompileShader_ptr = nullptr;
PFNGLGETSHADERIVPROC     glGetShaderiv_ptr = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_ptr = nullptr;
PFNGLCREATEPROGRAMPROC   glCreateProgram_ptr = nullptr;
PFNGLATTACHSHADERPROC    glAttachShader_ptr = nullptr;
PFNGLLINKPROGRAMPROC     glLinkProgram_ptr = nullptr;
PFNGLGETPROGRAMIVPROC    glGetProgramiv_ptr = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_ptr = nullptr;
PFNGLUSEPROGRAMPROC      glUseProgram_ptr = nullptr;
PFNGLDELETESHADERPROC    glDeleteShader_ptr = nullptr;

void InitializeShaderFunctionPointers() {
    glCreateShader_ptr = (PFNGLCREATESHADERPROC)glfwGetProcAddress("glCreateShader");
    glShaderSource_ptr = (PFNGLSHADERSOURCEPROC)glfwGetProcAddress("glShaderSource");
    glCompileShader_ptr = (PFNGLCOMPILESHADERPROC)glfwGetProcAddress("glCompileShader");
    glGetShaderiv_ptr = (PFNGLGETSHADERIVPROC)glfwGetProcAddress("glGetShaderiv");
    glGetShaderInfoLog_ptr = (PFNGLGETSHADERINFOLOGPROC)glfwGetProcAddress("glGetShaderInfoLog");
    glCreateProgram_ptr = (PFNGLCREATEPROGRAMPROC)glfwGetProcAddress("glCreateProgram");
    glAttachShader_ptr = (PFNGLATTACHSHADERPROC)glfwGetProcAddress("glAttachShader");
    glLinkProgram_ptr = (PFNGLLINKPROGRAMPROC)glfwGetProcAddress("glLinkProgram");
    glGetProgramiv_ptr = (PFNGLGETPROGRAMIVPROC)glfwGetProcAddress("glGetProgramiv");
    glGetProgramInfoLog_ptr = (PFNGLGETPROGRAMINFOLOGPROC)glfwGetProcAddress("glGetProgramInfoLog");
    glUseProgram_ptr = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glUseProgram");
    glDeleteShader_ptr = (PFNGLDELETESHADERPROC)glfwGetProcAddress("glDeleteShader");
}

NayderShaderCompiler::NayderShaderCompiler() {
    ProgramID = 0;
}

bool NayderShaderCompiler::LoadAndCompileShaders(const std::string& vertex_path, const std::string& fragment_path) {
    InitializeShaderFunctionPointers();

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertex_path);
        fShaderFile.open(fragment_path);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << " 🚫 [SHADER FILE ERROR]: GLSL Source text files could not be read from disk!" << std::endl;
        return false;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // 1. VERTEX SHADER COMPILATION
    vertex = glCreateShader_ptr(0x8B31); // GL_VERTEX_SHADER
    glShaderSource_ptr(vertex, 1, &vShaderCode, NULL);
    glCompileShader_ptr(vertex);
    glGetShaderiv_ptr(vertex, 0x8B81, &success); // GL_COMPILE_STATUS
    if (!success) {
        glGetShaderInfoLog_ptr(vertex, 512, NULL, infoLog);
        std::cerr << " 🚫 [GLSL VERTEX ERROR]: Compilation failed:\n" << infoLog << std::endl;
        return false;
    }

    // 2. FRAGMENT SHADER COMPILATION
    fragment = glCreateShader_ptr(0x8B30); // GL_FRAGMENT_SHADER
    glShaderSource_ptr(fragment, 1, &fShaderCode, NULL);
    glCompileShader_ptr(fragment);
    glGetShaderiv_ptr(fragment, 0x8B81, &success);
    if (!success) {
        glGetShaderInfoLog_ptr(fragment, 512, NULL, infoLog);
        std::cerr << " 🚫 [GLSL FRAGMENT ERROR]: Compilation failed:\n" << infoLog << std::endl;
        return false;
    }

    // 3. HARDWARE SHADER PROGRAM LINKING
    ProgramID = glCreateProgram_ptr();
    glAttachShader_ptr(ProgramID, vertex);
    glAttachShader_ptr(ProgramID, fragment);
    glLinkProgram_ptr(ProgramID);
    
    // Check for linking errors
    GLint program_success;
    glGetProgramiv_ptr(ProgramID, 0x8B82, &program_success); // GL_LINK_STATUS
    if (!program_success) {
        glGetProgramInfoLog_ptr(ProgramID, 512, NULL, infoLog);
        std::cerr << " 🚫 [SHADER LINKER ERROR]: Linking failed:\n" << infoLog << std::endl;
        return false;
    }

    // Purge loose shader stages from RAM now that they are locked into VRAM binary blocks
    glDeleteShader_ptr(vertex);
    glDeleteShader_ptr(fragment);

    std::cout << "\n🔥 [REAL SHADER COMPILER ACTIVE]:" << std::endl;
    std::cout << " -> Vertex Pipeline   : Compiled '" << vertex_path << "' successfully." << std::endl;
    std::cout << " -> Fragment Pipeline : Compiled '" << fragment_path << "' successfully." << std::endl;
    std::cout << " -> STATUS            : ✅ Shader Program ID (" << ProgramID << ") compiled and linked into hardware VRAM!" << std::endl;

    return true;
}

void NayderShaderCompiler::UseShaderProgram() {
    if (glUseProgram_ptr && ProgramID != 0) {
        glUseProgram_ptr(ProgramID);
    }
}
