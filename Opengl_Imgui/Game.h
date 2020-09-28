#pragma once
#include<iostream>

// core window
#include<Windows.h>
#include<iostream>
#include<string>

// include glad 
#include "glad\glad.h"

// include glfw 
#include<GLFW/glfw3.h>
#include<GLFW/glfw3native.h>

// include imgui 
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include"ImGuiWrapp.h"

#include"UIManagerImGuiI.h"
#include"MyStartupWindow.h"


class Game
{
public:

	static Game* Instance()
	{
		if (s_pGame == 0)
		{
			s_pGame = new Game;
			return s_pGame;
		}
		return s_pGame;
	}
	Game();
	~Game();

	bool Initialized(std::string title, int width, int height);
	void Run();
	void Update();
	void Draw();
	void Shutdown();
	GLFWwindow* GetWindow() { return m_pWindow; };

	int Close();

	int GetScrennWidth() { return m_screenWidth; };
	int GetScrennHeight() { return m_screenHeight; };
	void Clean();
	void SwapBuffers();
		
private:
	void SetWindowPosition(GLFWwindow* window, int width, int height);
	POINT CenterWindow(int width, int height);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


	

	GLFWwindow* m_pWindow;

	int m_screenWidth;
	int m_screenHeight;
	bool IsRuning;

	float lastTime;
	float currentTime;
	float deltaTime;

	
	ImGuiWrapp m_ImGuiWrapp;

	static Game* s_pGame;
};

typedef Game theGame;