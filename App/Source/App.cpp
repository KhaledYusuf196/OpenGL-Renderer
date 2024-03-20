#include <vector>

#include "Core/Core.h"
#include "Graphics/Camera.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

void Core::DrawScene()
{
    Mesh cube({
        {{-0.5f, 0.5f, 0.0f},   {1, 0, 0},  {0,1}},
        {{-0.5f, -0.5f, 0.0f},  {0, 1, 0},  {0,0}},
        {{0.5f, -0.5f, 0.0f},   {0, 0, 1},  {1,0}},
        {{0.5f, 0.5f, 0.0f},    {1, 1, 0},  {1,1}}
        }, {0,1,2,2,3,0});

    Camera camera;
    camera.CameraTransform.Position = {0,0,1};
    Shader shader("res/VS.glsl", "res/FS.glsl");
    Texture texture(std::string("res/Mic.png"));
    DrawMesh(cube, Transform(), camera, shader, texture);
}

int main()
{
    auto window = Core::InitWindow(1280, 720);
    if(window == nullptr || !Core::InitializeGLEW()) return 1;

    Core::UpdateWindow(window);

    Core::TerminateGLFW();
}