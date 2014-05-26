
#include "stdafx.h"
#include "GameApp.h"

INIT_FRAMEWORK(cGameApp)


cGameApp::cGameApp()
{
	m_windowName = L"GameApp";
	const RECT r = {0, 0, 800, 600};
	m_windowRect = r;
}

cGameApp::~cGameApp()
{

}


bool cGameApp::OnInit()
{
	g_pVB = NULL; // 버텍스 버퍼
	g_pIB = NULL; // 인덱스 버퍼

	g_pVB2 = NULL; // 버텍스 버퍼
	g_pIB2 = NULL; // 인덱스 버퍼

	WINSIZE_X = 1024;		//초기 윈도우 가로 크기
	WINSIZE_Y = 768;	//초기 윈도우 세로 크기

	badakNum = 0;
	//바닥 버텍스 버퍼 생성
	if (FAILED(m_DxDevice->CreateVertexBuffer( 4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY, Vertex::FVF,
		D3DPOOL_MANAGED, &g_pVB, NULL)))
	{
		return false;
	}

	//바닥 버텍스 버퍼 초기화
	Vertex* vertices;
	if (FAILED(g_pVB->Lock( 0, sizeof(Vertex), (void**)&vertices, 0)))
		return false;
	// 0----------1
	// |          |
	// |          |
	// |          |
	// 2----------3
	vertices[ 0] = Vertex(-1, 0, 1);
	vertices[ 1] = Vertex(1, 0, 1);
	vertices[ 2] = Vertex(-1, 0, -1);
	vertices[ 3] = Vertex(1, 0, -1);
	
	g_pVB->Unlock();

	if (FAILED(m_DxDevice->CreateIndexBuffer(6 *sizeof(WORD), 
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIB, NULL)))
	{
		return false;
	}

	WORD *indices = NULL;
	g_pIB->Lock(0, 0, (void**)&indices, 0);

	int index = 0;
	indices[ index++] = 0; indices[ index++] = 1; indices[ index++] = 2;
	indices[ index++] = 2; indices[ index++] = 1; indices[ index++] = 3;

	g_pIB->Unlock();
	num1 = -4;
	num2 = 0;
	num5 = 0;
	num6 = 0;
	//////////////////////////////////////////////////////////////////////////////////

	if (FAILED(m_DxDevice->CreateVertexBuffer( 8 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY, Vertex::FVF,
		D3DPOOL_MANAGED, &g_pVB2, NULL)))
	{
		return false;
	}

	//바닥 버텍스 버퍼 초기화
	Vertex* vertices2;
	if (FAILED(g_pVB2->Lock( 0, sizeof(Vertex), (void**)&vertices2, 0)))
		return false;
	// 0----------1
	// |          |
	// |          |
	// |          |
	// 2----------3
	vertices2[ 0] = Vertex(-1, -1, -1);
	vertices2[ 1] = Vertex(-1, 1, -1);
	vertices2[ 2] = Vertex(1, 1, -1);
	vertices2[ 3] = Vertex(1, -1, -1);
	vertices2[ 4] = Vertex(-1, -1, 1);
	vertices2[ 5] = Vertex(-1, 1, 1);
	vertices2[ 6] = Vertex(1, 1, 1);
	vertices2[ 7] = Vertex(1, -1, 1);

	g_pVB2->Unlock();

	if (FAILED(m_DxDevice->CreateIndexBuffer(36 *sizeof(WORD), 
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIB2, NULL)))
	{
		return false;
	}

	WORD *indices2 = NULL;
	g_pIB2->Lock(0, 0, (void**)&indices2, 0);

	int index2 = 0;
	// front
	indices2[ index2++] = 0; indices2[ index2++] = 1; indices2[ index2++] = 2;
	indices2[ index2++] = 0; indices2[ index2++] = 2; indices2[ index2++] = 3;

	// back
	indices2[ index2++] = 4; indices2[ index2++] = 6; indices2[ index2++] = 5;
	indices2[ index2++] = 4; indices2[ index2++] = 7; indices2[ index2++] = 6;

	// left
	indices2[ index2++] = 4; indices2[ index2++] = 5; indices2[ index2++] = 1;
	indices2[ index2++] = 4; indices2[ index2++] = 1; indices2[ index2++] = 0;

	// right
	indices2[ index2++] = 3; indices2[ index2++] = 2; indices2[ index2++] = 6;
	indices2[ index2++] = 3; indices2[ index2++] = 6; indices2[ index2++] = 7;

	// top
	indices2[ index2++] = 1; indices2[ index2++] = 5; indices2[ index2++] = 6;
	indices2[ index2++] = 1; indices2[ index2++] = 6; indices2[ index2++] = 2;

	// bottom
	indices2[ index2++] = 4; indices2[ index2++] = 0; indices2[ index2++] = 3;
	indices2[ index2++] = 4; indices2[ index2++] = 3; indices2[ index2++] = 7;

	g_pIB2->Unlock();
	return true;
}


void cGameApp::OnUpdate(const float elapseT)
{
	if(GetKeyState(VK_LEFT) & 0x8000)
	{
		num5 -= 0.1f;
	}
	if(GetKeyState(VK_RIGHT) & 0x8000)
	{
		num5 += 0.1f;
	}

	camPositon = Vector3(0,4,num1);
	camTarget = Vector3(0,0,num2);
	camUpVecter = Vector3(0,1,0);
	num1 += 0.1f;
	num2 += 0.1f;
	
	D3DXMatrixLookAtLH((D3DXMATRIX*)&camVecter, (D3DXVECTOR3*)&camPositon, (D3DXVECTOR3*)&camTarget, (D3DXVECTOR3*)&camUpVecter);
	
	m_DxDevice->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&camVecter);

	Matrix44 proj;
	proj.SetProjection(D3DX_PI * 0.5f, (float)WINSIZE_X / (float) WINSIZE_Y, 1.f, 1000.0f) ;
	m_DxDevice->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&proj) ;

	m_DxDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

}


void cGameApp::OnRender(const float elapseT)
{

	if (SUCCEEDED(m_DxDevice->Clear( 
		0,			//청소할 영역의 D3DRECT 배열 갯수		( 전체 클리어 0 )
		NULL,		//청소할 영역의 D3DRECT 배열 포인터		( 전체 클리어 NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	//청소될 버퍼 플레그 ( D3DCLEAR_TARGET 컬러버퍼, D3DCLEAR_ZBUFFER 깊이버퍼, D3DCLEAR_STENCIL 스텐실버퍼
		D3DCOLOR_XRGB(255, 255, 255),			//컬러버퍼를 청소하고 채워질 색상( 0xAARRGGBB )
		1.0f,				//깊이버퍼를 청소할값 ( 0 ~ 1 0 이 카메라에서 제일가까운 1 이 카메라에서 제일 먼 )
		0					//스텐실 버퍼를 채울값
		)))
	{
		//화면 청소가 성공적으로 이루어 졌다면... 랜더링 시작
		m_DxDevice->BeginScene();
		
		num6 += 0.1f;
		for(int i = 0; i < 3000; ++i)
		{
		newBadak(i * 2);
		}
		penguin(num5 , num6);

		penguin(0, 10);
		penguin(-2, 30);
		penguin(3, 40);
		penguin(1, 60);
		penguin(0, 65);
		penguin(-3, 75);
		penguin(-1, 80);
		penguin(2, 85);
		penguin(0, 95);
		penguin(-2, 105);
		penguin(-3, 110);

		penguin(0, 110);
		penguin(-2, 130);
		penguin(3, 140);
		penguin(1, 160);
		penguin(0, 165);
		penguin(-3, 175);
		penguin(-1, 180);
		penguin(2, 185);
		penguin(0, 195);
		penguin(-2, 205);
		penguin(-3, 210);
		//랜더링 끝
		m_DxDevice->EndScene();
		//랜더링이 끝났으면 랜더링된 내용 화면으로 전송
		m_DxDevice->Present( NULL, NULL, NULL, NULL );
	}
}


void cGameApp::OnShutdown()
{

}


void cGameApp::MessageProc( UINT message, WPARAM wParam, LPARAM lParam)
{

}


void cGameApp::newBadak( int num )
{
	Matrix44 rx, ry, r;
	r.SetIdentity();
	r.SetTranslate(Vector3(0, 0, num));
	m_DxDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);
	m_DxDevice->SetStreamSource( 0, g_pVB, 0, sizeof(Vertex) );
	m_DxDevice->SetIndices(g_pIB);
	m_DxDevice->SetFVF( Vertex::FVF );
	m_DxDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	r.SetTranslate(Vector3(-2, 0, num));
	m_DxDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);
	m_DxDevice->SetStreamSource( 0, g_pVB, 0, sizeof(Vertex) );
	m_DxDevice->SetIndices(g_pIB);
	m_DxDevice->SetFVF( Vertex::FVF );
	m_DxDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	r.SetTranslate(Vector3(2, 0, num));
	m_DxDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);
	m_DxDevice->SetStreamSource( 0, g_pVB, 0, sizeof(Vertex) );
	m_DxDevice->SetIndices(g_pIB);
	m_DxDevice->SetFVF( Vertex::FVF );
	m_DxDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	
	r.SetTranslate(Vector3(-4, 0, num));
	m_DxDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);
	m_DxDevice->SetStreamSource( 0, g_pVB, 0, sizeof(Vertex) );
	m_DxDevice->SetIndices(g_pIB);
	m_DxDevice->SetFVF( Vertex::FVF );
	m_DxDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	r.SetTranslate(Vector3(4, 0, num));
	m_DxDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);
	m_DxDevice->SetStreamSource( 0, g_pVB, 0, sizeof(Vertex) );
	m_DxDevice->SetIndices(g_pIB);
	m_DxDevice->SetFVF( Vertex::FVF );
	m_DxDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	r.SetTranslate(Vector3(-6, 0, num));
	m_DxDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);
	m_DxDevice->SetStreamSource( 0, g_pVB, 0, sizeof(Vertex) );
	m_DxDevice->SetIndices(g_pIB);
	m_DxDevice->SetFVF( Vertex::FVF );
	m_DxDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	r.SetTranslate(Vector3(6, 0, num));
	m_DxDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);
	m_DxDevice->SetStreamSource( 0, g_pVB, 0, sizeof(Vertex) );
	m_DxDevice->SetIndices(g_pIB);
	m_DxDevice->SetFVF( Vertex::FVF );
	m_DxDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void cGameApp::penguin(float num1, float num2)
{
	Matrix44 rx, ry, r;
	r.SetIdentity();
	r.SetTranslate(Vector3(num1, 1, num2 - 2));
	m_DxDevice->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);
	m_DxDevice->SetStreamSource( 0, g_pVB2, 0, sizeof(Vertex) );
	m_DxDevice->SetIndices(g_pIB2);
	m_DxDevice->SetFVF( Vertex::FVF );
	m_DxDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}
