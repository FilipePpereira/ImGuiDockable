#pragma once
#ifndef __MY_IMGUI_WINDOW_H_
#define __MY_IMGUI_WINDOW_H_



#include<iostream>
#include<string>

// include glad 
#include "glad\glad.h"

// include imgui 
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class MyImGuiWindow
{
public:
    MyImGuiWindow();
	~MyImGuiWindow();

    virtual void Update();
    void Show();
protected:
    virtual bool Begin(std::string name);
    void End();
    bool show;
};

#endif // !__MY_IMGUI_WINDOW_H_



