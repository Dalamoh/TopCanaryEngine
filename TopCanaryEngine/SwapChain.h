#pragma once
#include <d3d11.h>

#include "Prerrequisites.h"

class SwapChain
{
public:
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem * system);

	void resize(unsigned int width, unsigned int height);
	void setFullScreen(bool fullscreen, unsigned int width, unsigned int height);
	bool present(bool vsync);

	~SwapChain();


private:
	void reloadBuffers(unsigned int width, unsigned int height);

	IDXGISwapChain * m_swap_chain = nullptr;
	ID3D11RenderTargetView * m_render_target_view = nullptr;
	ID3D11DepthStencilView * m_depth_stencil_view = nullptr;
	RenderSystem * m_system = nullptr;

	friend class DeviceContext;
};

