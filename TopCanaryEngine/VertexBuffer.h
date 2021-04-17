#pragma once
#include <d3d11.h>

#include "Prerrequisites.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader, RenderSystem * system);
	UINT getSizeVertexList();

	~VertexBuffer();


private:
	UINT m_size_vertex;
	UINT m_size_list;

	ID3D11Buffer * m_buffer;
	ID3D11InputLayout * m_layout;

	RenderSystem * m_system = nullptr;

	friend class DeviceContext;
};

