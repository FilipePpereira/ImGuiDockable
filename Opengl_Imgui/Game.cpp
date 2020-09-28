#include "Game.h"

#include<memory>


bool show_another_window = false;

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


Game* Game::s_pGame = 0;



Game::Game(): m_pWindow(nullptr), lastTime(0.0f), 
              currentTime(0.0f), deltaTime(0.0f), m_screenWidth(1280), m_screenHeight(720)
{
}

Game::~Game()
{
}

bool Game::Initialized(std::string title, int width, int height)
{

	m_screenWidth = width;
	m_screenHeight = height;

	if (!glfwInit())
	{
		std::cout << "Failed Init GLFW " << "\n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_MAXIMIZED, 1);

	m_pWindow = glfwCreateWindow(m_screenWidth, m_screenHeight, title.c_str(), NULL, NULL);

	if (!m_pWindow)
	{
		std::cout << "Failed Create Window " << "\n";
		return false;
	}

	glfwMakeContextCurrent(m_pWindow);
	glfwGetFramebufferSize(m_pWindow, &m_screenWidth, &m_screenHeight);
	glfwSetFramebufferSizeCallback(m_pWindow, framebuffer_size_callback);
	//glfwSetKeyCallback(m_pWindow, InputManagerCallback);


	//glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(m_pWindow, mouse_callback);

	POINT center = CenterWindow(m_screenWidth, m_screenHeight);
	SetWindowPosition(m_pWindow, center.x, center.y);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}



	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);


	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	m_ImGuiWrapp.Initialized(m_pWindow, m_screenWidth, m_screenHeight);

	
	
	return true;
}

void Game::Run()
{
	while (!Close())
	{
		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;

	
		if (deltaTime >= 1 / 60)
		{
			
			Update();
			

			Clean();

			m_ImGuiWrapp.UpdateImGui();
			Draw();
			lastTime = currentTime;

			SwapBuffers();

		}
		
	}

	Shutdown();
}

void Game::Update()
{
    glfwPollEvents();
}

void Game::Draw()
{
	
   m_ImGuiWrapp.DrawImGui(m_pWindow);
	
}

void Game::Shutdown()
{
	
	m_ImGuiWrapp.Destroy();
    glfwDestroyWindow(m_pWindow);
    glfwTerminate();
}

int Game::Close()
{
	return glfwWindowShouldClose(m_pWindow);
}

POINT Game::CenterWindow(int width, int height)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	POINT center;
	center.x = (screenWidth - width) / 2;
	center.y = (screenHeight - height) / 2;

	return center;
}

void Game::SetWindowPosition(GLFWwindow* window, int width, int height)
{
	glfwSetWindowPos(window, width, height);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Game::Clean()
{
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::SwapBuffers()
{
	glfwSwapBuffers(m_pWindow);
}
