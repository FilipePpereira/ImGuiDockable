#include "MyImGuiWindow.h"

MyImGuiWindow::MyImGuiWindow()
{
}

MyImGuiWindow::~MyImGuiWindow()
{
}

void MyImGuiWindow::Update()
{
}

void MyImGuiWindow::Show()
{
	show = true;
}

bool MyImGuiWindow::Begin(std::string name)
{
	return ImGui::Begin(name.c_str(), &show);
}

void MyImGuiWindow::End()
{
	ImGui::End();
}
