#pragma once
#include <string>
#include "glm/glm.hpp"

class Shader
{
public:
	unsigned int ShaderID;

    Shader(std::string VertexPath, std::string FragmentPath);
    ~Shader();
	
    void Use() const;
    // utility uniform functions
    void SetMatrix4x4(const std::string& name, glm::mat4 value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    
    void SetMatrix4x4(int uniformID, glm::mat4 value) const;
    void SetInt(int uniformID, int value) const;
    void SetFloat(int uniformID, float value) const;

};

