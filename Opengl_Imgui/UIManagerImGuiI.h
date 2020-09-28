#pragma once
#include"MyImGuiWindow.h"
// include glad 
#include "glad\glad.h"

// include glfw 
#include<GLFW/glfw3.h>
#include<GLFW/glfw3native.h>

#include <vector>


#include"MyStartupWindow.h"



class UIManagerImGuiI
{
public:
	UIManagerImGuiI();
	~UIManagerImGuiI();


	void InitWindows(GLFWwindow* window);
	void Update();

	void Render();
	void AddWindow(MyImGuiWindow newWin);

private:

	

	std::vector<MyImGuiWindow> windows;
	void ShowDockSpace(bool* p_open);

	void Setstyle();
	void UpdateWindows();
	void DeleteWindows();

};

