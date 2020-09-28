#include "ImGuiWrapp.h"
#include <GLFW\glfw3.h>
#include"StylesWindow.h"
#include"Game.h"




ImGuiWrapp::ImGuiWrapp(): glsl_version("#version 150")
{
}

ImGuiWrapp::~ImGuiWrapp()
{
}

bool ImGuiWrapp::Initialized(GLFWwindow* window, float width, float height)
{


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	{
		
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

																	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		io.ConfigViewportsNoAutoMerge = true;
		io.ConfigViewportsNoTaskBarIcon = true;


		io.ConfigViewportsNoDefaultParent = false;

	}


	io.DisplaySize = ImVec2(width, height);

	Style::StylesWindow::SetStyleDefault();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	

    return true;
}

void ImGuiWrapp::UpdateImGui()
{



	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	/*ImGui::DockSpaceOverViewport();*/
	
	// demo window callBack
	//ImGui::ShowDemoWindow();
	DockSpaceMainWindow();

	



	ImGuiIO& io = ImGui::GetIO(); (void)io;
	{
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		
		ImGuiWindowFlags flags =   ImGuiWindowFlags_NoScrollbar;
		ImGuiStyle style = ImGui::GetStyle();
		bool is;
		if (ImGui::Begin("GameView", &is, flags))
		{
			style.WindowRounding = 0.0f;
			style.FrameBorderSize = 0.0f;
			/*ImVec2 size = ImVec2(theGame::Instance()->GetScrennWidth(), theGame::Instance()->GetScrennHeight());*/
			ImVec2 size = ImVec2(280.0f, theGame::Instance()->GetScrennHeight());
			//ImVec2 position = ImVec2(theGame::Instance()->GetScrennWidth() / 2 + 440, 19.0f);

			ImVec2 position = ImVec2(0.0f, 19.0f);


			ImGui::SetWindowSize(size);
			ImGui::SetWindowPos(position);


			ImGuiID dockspace_id = ImGui::GetID("DockSpace");

			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));




			ImGui::End();
		}
	}




	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit", nullptr, false))
			{
				/*theGame::Instance()->Close();*/
				glfwWindowShouldClose(theGame::Instance()->GetWindow());
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", nullptr, false))
			{

			}
			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Styles"))
		{
			if (ImGui::MenuItem("Default", nullptr, false))
			{
				Style::StylesWindow::SetStyleDefault();
			}

			if (ImGui::MenuItem("Light", nullptr, false))
			{
				ImGui::StyleColorsLight();
			}
			if (ImGui::MenuItem("Classic", nullptr, false))
			{
				ImGui::StyleColorsClassic();
			}
			if (ImGui::MenuItem("Dark", nullptr, false))
			{
				ImGui::StyleColorsDark();

			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Show Console", nullptr, false))
			{

			}
			ImGui::EndMenu();
		}


		ImGui::EndMainMenuBar();
	}
}

void ImGuiWrapp::DrawImGui(GLFWwindow* context)
{
    // Rendering
    ImGui::Render();

	ImGui::RenderPlatformWindowsDefault();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		glfwMakeContextCurrent(context);
	}
}

void ImGuiWrapp::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiWrapp::DockSpaceMainWindow()
{

	bool* p_open = {};
	
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", p_open,  window_flags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);


	ImGui::End();
}

ImVec2 ImGuiWrapp::WindowSizeViewport()
{
	ImVec2 windowsize = ImVec2();
	ImGui::GetContentRegionAvail();
	ImGui::GetContentRegionMax();
	windowsize.x -= ImGui::GetScrollX();
	windowsize.y -= ImGui::GetScrollY();

	float aspect = theGame::Instance()->GetScrennWidth() / theGame::Instance()->GetScrennHeight();
	float aspectWidth = windowsize.x;
	float aspectHeight = aspectWidth / aspect;

	if (aspectHeight > windowsize.y)
	{
		aspectHeight = windowsize.y;

		aspectWidth = aspectHeight * aspect;
	}



	return ImVec2(aspectWidth, aspectHeight);
}

ImVec2 ImGuiWrapp::Centerviewport(float aspect)
{

	ImVec2 windowsize = ImGui::GetContentRegionAvail();
	windowsize.x -= ImGui::GetScrollX();
	windowsize.y -= ImGui::GetScrollY();

	
	float viewportX = (windowsize.x / 2.0f) - (aspect / 2.0f);
	float viewporty = (windowsize.y / 2.0f) - (aspect / 2.0f);


	return ImVec2(viewportX, viewporty);
}
