#include "MyStartupWindow.h"

MyStartupWindow::MyStartupWindow()
{
}

MyStartupWindow::~MyStartupWindow()
{
}

void MyStartupWindow::Update()
{
    int count = 0;
    bool inShow = true;
    ImGui::Begin("Startup", &inShow);
    ImGui::Text("This is an example window");
    ImGui::Text("Dock this window!");
    ImGui::Separator();
    ImGui::Text("You can create your own windows for any purpose");
    if (ImGui::Button("This is a button"))
    {
        count++;
    }

    ImGui::Text("Count: %d", count);

    ImGui::End();
}
