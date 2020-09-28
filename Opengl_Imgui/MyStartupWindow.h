#pragma once
#include "MyImGuiWindow.h"




class MyStartupWindow :
    public MyImGuiWindow
{
public:
    MyStartupWindow();
    ~MyStartupWindow();




    // Inherited via MyImGuiWindow
    void Update() override;
private:
    int counter = 0;

};

