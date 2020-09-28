#pragma once
#include<iostream>


// include glfw 
#include<GLFW/glfw3.h>
#include<GLFW/glfw3native.h>

// include imgui 
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class ImGuiWrapp
{
public:
	ImGuiWrapp();
	~ImGuiWrapp();

	bool Initialized(GLFWwindow* window, float width, float height);

	void UpdateImGui();

	void DrawImGui(GLFWwindow* context);
	void Destroy();

	//void Drawteste();
	
	void DockSpaceMainWindow();
	ImVec2 WindowSizeViewport();
	ImVec2 Centerviewport(float aspect);
private:
	const char* glsl_version;

	
};

