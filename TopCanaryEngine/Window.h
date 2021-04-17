#pragma once
#include <Windows.h>



class Window
{

public:
	
	//Initialize the window
	Window();


	bool isRunning();
	RECT getClientWindowRect();
	RECT getSizeScreen();

	// EVENTS

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();
	virtual void onSize();

	
	//Release the window
	~Window();

private:
	bool broadcast();

protected:
	HWND m_hwnd;
	bool m_isRunning;
	bool m_is_init = false;

};

