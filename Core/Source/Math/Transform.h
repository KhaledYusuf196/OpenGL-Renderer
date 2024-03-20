#pragma once
#include <glm/glm.hpp>

#include "glm/detail/type_quat.hpp"

class Transform
{
public:
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;


	Transform();
	glm::mat4 GetTransformMatrix() const;
	glm::mat4 GetInverseTransformMatrix() const;
};

