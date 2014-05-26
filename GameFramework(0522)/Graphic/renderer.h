#pragma once
#include "vertexbuff.h"
#include "indexbuff.h"
namespace graphic
{
	class renderer : public singleton<renderer>
	{
	public:
		renderer(void);
		virtual ~renderer(void);

		bool CreateDivice(HWND hWnd, const int widht, const int height);
		LPDIRECT3DDEVICE9 GetDevice();

	
	
	private:
		LPDIRECT3DDEVICE9 m_pDevice;
	};

	bool InitRenderer(HWND hWnd, const int widht, const int height);
	void ReleaseRenderer();
	renderer* GetRenderer();
	LPDIRECT3DDEVICE9 GetDevice();

	bool ReadModelFile( const string &fileName, LPDIRECT3DVERTEXBUFFER9 &vtxBuff, int &vtxSize,  LPDIRECT3DINDEXBUFFER9 &idxBuff, int &faceSize );
	void ComputeNormals(graphic::vertexbuff vtxBuff, int vtxSize, graphic::indexbuff idxBuff, int faceSize);


}

