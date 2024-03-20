#pragma once
#include <Math/Transform.h>

class Camera
{
public:
	Transform CameraTransform;
	float FOV;

	Camera();
	float DegToRad(float deg);
	glm::mat4 GetProjectionMatrix();

};

