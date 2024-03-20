-- premake5.lua
workspace "OpenGL_Renderer"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Core/Build-Core.lua"

group "ThirdParty"
	include "ThirdParty/GLFW/Build-GLFW.lua"
   include "ThirdParty/GLEW/Build-GLEW.lua"
   include "ThirdParty/GLM/Build-GLM.lua"
group ""
 
include "App/Build-App.lua"