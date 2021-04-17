#include "Window.h"
#include <exception>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,  WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		//Now its done in broadcast()
		break;
	}

	case WM_SIZE:
	{
		// Event triggered when the window is resized
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (window) window->onSize();
		break;
	}

	case WM_SETFOCUS:
	{
		// Event triggered when the window get focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if(window) window->onFocus();
		break;
	}

	case WM_KILLFOCUS:
	{
		// Event triggered when the window lost focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onKillFocus();
		break;
	}

	case WM_DESTROY:
	{
		// Event triggered when the window is destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);

	}

	return NULL;
}

Window::Window()
{
	//Setting up the WNDCLASSEX object
	WNDCLASSEX windowClass;
	windowClass.cbClsExtra = NULL;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.cbWndExtra = NULL;
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hInstance = NULL;
	windowClass.lpszClassName = "TopCanaryWindowClass";
	windowClass.lpszMenuName = "";
	windowClass.style = NULL;
	windowClass.lpfnWndProc = &WndProc;

	
	if (!::RegisterClassEx(&windowClass)) // In case the registration fails, the function returns exception
		throw std::exception("WindowClass couldn't be registered");
	

	/*if (!window)
		window = this;*/

	//Creation of the window
	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "TopCanaryWindowClass", "DirectX Application", 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	//if the creation fail return exception
	if (!m_hwnd) 
		throw std::exception("WindowClass couldn't be created");

	//show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);


	// Set isRunning flag to true
	m_isRunning = true;
}



bool Window::broadcast()
{
	MSG msg;

	if (!this->m_is_init) 
	{
		SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
		this->onCreate();
		this->m_is_init = true;
	}

	this->onUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(0);

	return true;
}

bool Window::isRunning()
{
	if (m_isRunning)
		broadcast();
	return m_isRunning;
}

RECT Window::getClientWindowRect()
{
	RECT rect;
	::GetClientRect(this->m_hwnd, &rect);
	return rect;
}

RECT Window::getSizeScreen()
{
	RECT rc;
	rc.right = ::GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = ::GetSystemMetrics(SM_CYSCREEN);
	return rc;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	// Set isRunning flag to false
	m_isRunning = false;
}

void Window::onFocus()
{
}

void Window::onKillFocus()
{
}

void Window::onSize()
{
}

Window::~Window()
{
}
