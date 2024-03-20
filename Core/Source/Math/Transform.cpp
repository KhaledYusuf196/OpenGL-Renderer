#include "Transform.h"
#include <glm/glm.hpp>

#include "glm/gtc/quaternion.hpp"


Transform::Transform() : Position(0, 0, 0), Rotation(1, 0, 0, 0), Scale(1, 1, 1)
{ }

glm::mat4 Transform::GetTransformMatrix() const
{
	return glm::translate(glm::identity<glm::mat4>(), Position) * glm::mat4_cast(Rotation) * glm::scale(glm::identity<glm::mat4>(), Scale);
}

glm::mat4 Transform::GetInverseTransformMatrix() const
{
	return glm::scale(glm::identity<glm::mat4>(), 1.0f / Scale) * glm::mat4_cast(inverse(Rotation)) * glm::translate(glm::identity<glm::mat4>(), -Position);
}
