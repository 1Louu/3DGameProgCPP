#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    Process(GetFileContent(vertexPath), GetFileContent(fragmentPath));
}

void Shader::Process(std::string vertexCode, std::string fragmentCode)
{
    const char* tmp = vertexCode.c_str();
    //Shader creation => only geometry
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &tmp, NULL);
    glCompileShader(vertexShader);

    //check if work
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "VERTEX SHADER : COMPILATION FAILED: \n" << infoLog << std::endl;
    }

    tmp = fragmentCode.c_str();

    //Shader creation => only visual 
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &tmp, NULL);
    glCompileShader(fragmentShader);

    // check if work
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "FRAG SHADER : COMPILATION FAILED: \n" << infoLog << std::endl;
    }
    // Attach shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    //check
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "SHADER PROGRAM : LINK FAILED: \n" << infoLog << std::endl;
    }
}

void Shader::Use() const
{
    glUseProgram(ID);
}

void Shader::Shutdown() const
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::SetMatrix4(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetVector3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void Shader::SetVector3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

std::string Shader::GetFileContent(const char* path)
{
    try
    {
        std::ifstream shaderFile; 
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        shaderFile.open(path);
        std::stringstream shaderStream; 
        shaderStream << shaderFile.rdbuf(); 
        shaderFile.close(); 
        
        return shaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR : File cant be read" << e.what() << std::endl; 
    }
}
