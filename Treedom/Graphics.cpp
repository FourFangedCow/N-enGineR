#include "Precompiled.h"
#include "Graphics.h"


namespace Engine
{

	Graphics* GRAPHICS = NULL;

	Graphics::Graphics(HWND hWnd)
	{
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		
		D3DPRESENT_PARAMETERS d3dpp;			//Struct for device info

		ZeroMemory(&d3dpp, sizeof(d3dpp));		//Clears memory
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hWnd;

		//Create the device
		d3d->CreateDevice(D3DADAPTER_DEFAULT,
						  D3DDEVTYPE_HAL,
						  hWnd,
						  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
						  &d3dpp,
						  &d3ddev);
	}

	void Graphics::Update(float dt)
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
		d3ddev->BeginScene();
		d3ddev->SetRenderState(D3DRS_CULLMODE, 1);
		d3ddev->SetFVF(CUSTOMFVF);
		d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
		d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting
		
		DrawMeshes();

		GetFPS();

		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}

	void Graphics::Initialize()
	{
		// create the vertices using the CUSTOMVERTEX struct
		d3ddev->CreateVertexBuffer(3000 * sizeof(CUSTOMVERTEX),
								   D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
								   CUSTOMFVF,
								   D3DPOOL_DEFAULT,
								   &v_buffer,
								   NULL);
		GRAPHICS = this;

		InitializeMatrix();

	}

	void Graphics::InitializeMatrix()
	{

		D3DXMatrixLookAtLH(&matView,
		                   &D3DXVECTOR3 (0.0f, 0.0f, 10.0f),    // the camera position
		                   &D3DXVECTOR3 (0.0f, 0.0f, 0.0f),    // the look-at position
		                   &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));    // the up direction

		d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

		D3DXMATRIX matProjection;     // the projection transform matrix

		D3DXMatrixPerspectiveFovLH(&matProjection,
		                           D3DXToRadian(45),    // the horizontal field of view
		                           (FLOAT)1440 / (FLOAT)900, // aspect ratio
		                           1.0f,    // the near view-plane
		                           100.0f);    // the far view-plane

		d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

	}

	void Graphics::DrawMeshes()
	{
		for(std::vector<Mesh*>::iterator iter = meshList.begin(); iter != meshList.end(); ++iter)
		{
			Mesh* currMesh = *iter;
			currMesh->Draw();
			float scale = currMesh->transform->Scale;
			D3DXMATRIX matRotateX, matScale, matTranslate;
		
			D3DXMatrixRotationZ(&matRotateX, D3DXToRadian(currMesh->transform->Rotation));
			D3DXMatrixScaling(&matScale, scale, scale, scale);
			D3DXMatrixTranslation(&matTranslate, currMesh->transform->Position.x, currMesh->transform->Position.y, 0.0f);

			d3ddev->SetTransform(D3DTS_WORLD, &(matRotateX * matScale * matTranslate));
			int dicks = currMesh->num;
			d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, dicks );
		}
	}

	void Graphics::CreateFont()
	{
		D3DXCreateFont(
			d3ddev,     //D3D Device
			22,               //Font height
			0,                //Font width
			FW_NORMAL,        //Font Weight
			1,                //MipLevels
			false,            //Italic
			DEFAULT_CHARSET,  //CharSet
			OUT_DEFAULT_PRECIS, //OutputPrecision
			ANTIALIASED_QUALITY, //Quality
			DEFAULT_PITCH|FF_DONTCARE,//PitchAndFamily
			"Arial",          //pFacename,
			&font);         //ppFont
	}

	void Graphics::GetFPS()
	{
		static int currframes = 0;
		static int perframes = 0;
		static unsigned int currtime = timeGetTime();
		++currframes;
		if (timeGetTime() - currtime >= 1000)
		{
			perframes = currframes;
			currframes = 0;
			currtime = timeGetTime();
		}
		printf("FPS: %i\n", perframes);
	}

	Graphics::~Graphics()
	{
		v_buffer->Release();
		d3ddev->Release();
		d3d->Release();
	}
}