#pragma once
#include "Prerrequisites.h"
#include <d3d11.h>

class RenderSystem
{
public:
	//Initialize the RenderSystem and DirectX
	RenderSystem();

	SwapChainPtr createSwapChain(HWND hwnd, UINT width, UINT height);
	DeviceContextPtr getImmediateDeviceContext();
	VertexBufferPtr createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	ConstantBufferPtr createConstantBuffer(void* buffer, UINT size_buffer);
	IndexBufferPtr createIndexBuffer(void* list_indices, UINT size_list);
	VertexShaderPtr createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShaderPtr createPixelShader(const void* shader_byte_code, size_t byte_code_size);

	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledShader();

	void setRasterizerState(bool cull_front);

// Release all the resources loaded
	~RenderSystem();

private:

	void initRasterizerState();


	ID3D11Device * m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	IDXGIDevice * m_dxgi_device;
	IDXGIAdapter * m_dxgi_adapter;
	IDXGIFactory * m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

	DeviceContextPtr m_imm_device_context;

	ID3DBlob * m_blob = nullptr;

	ID3D11RasterizerState* m_cull_front_state = nullptr;
	ID3D11RasterizerState* m_cull_back_state = nullptr;

	ID3D11VertexShader * m_vs = nullptr;
	ID3D11PixelShader * m_ps = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class IndexBuffer;
	friend class Texture;

};



