#pragma once
#include <d3d11.h>
#include "Prerrequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "Material.h"

class GraphicsEngine
{
public:
	RenderSystem * getRenderSystem();
	TextureManager * getTextureManager();
	MeshManager * getMeshManager();
	void getVertexMeshLayoutShaderByteCodeAndSize(void ** bytecode, size_t* size);

	MaterialPtr createMaterial(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	MaterialPtr createMaterial(const MaterialPtr & material);
	void setMaterial(const MaterialPtr& material);

	static GraphicsEngine* get();

	static void create();
	static void release();

private:
	//Initialize the GraphicsEngine and DirectX
	GraphicsEngine();
	// Release all the resources loaded
	~GraphicsEngine();

	RenderSystem* m_render_system = nullptr;
	TextureManager* m_tex_manager = nullptr;
	MeshManager* m_mesh_manager = nullptr;

	static GraphicsEngine* m_engine;
	
	unsigned char m_mesh_layour_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};

