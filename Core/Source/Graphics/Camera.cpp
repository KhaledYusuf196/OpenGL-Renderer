#include "Camera.h"

Camera::Camera() : FOV(60)
{
}

float Camera::DegToRad(float deg)
{
	return deg * glm::pi<float>() / 180.0f;
}

glm::mat4 Camera::GetProjectionMatrix()
{

	glm::mat4 viewMat = CameraTransform.GetInverseTransformMatrix();
	glm::mat4 projectionMat = glm::perspective(DegToRad(60.0f), 1.7778f, 0.1f, 10.0f);

	glm::mat4 ViewProjection = projectionMat * viewMat;
	return ViewProjection;
}
