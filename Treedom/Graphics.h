#pragma once

#include "Engine.h"
#include "BranchingMesh.h"

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

namespace Engine
{
	struct CUSTOMVERTEX
	{
		float x, y, z;
		DWORD color;
	};

	class Graphics : public System
	{
	public:
		Graphics();
		Graphics(HWND hWnd);
		~Graphics();

		void CreateCamera();
		void CreateFont();
		void InitializeMatrix();
		void DrawMeshes();
		void GetFPS();
		virtual void Initialize();
		virtual void Update(float dt);
		virtual std::string GetName() {return "Graphics";}

		std::vector<Mesh*> meshList;
		ID3DXFont *font;
		LPDIRECT3D9 d3d;			//Pointer to the D9 device class
		LPDIRECT3DDEVICE9 d3ddev;	//The pointer to the device class
		LPDIRECT3DVERTEXBUFFER9 v_buffer;
		Mat2D matWorld, matView, matProj;
	};

	class Camera
	{
		Vec2D position;
	};
	
	extern Graphics* GRAPHICS;
}