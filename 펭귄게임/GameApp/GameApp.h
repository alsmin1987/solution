
#pragma once

struct Vertex
{
	Vertex() {}
	Vertex(float x0, float y0, float z0) : x(x0), y(y0), z(z0) {}
	float x, y, z; 
	static const DWORD FVF;
};

const DWORD Vertex::FVF  = D3DFVF_XYZ;

class cGameApp : public framework::cGameMain
{
public:
	cGameApp();
	virtual ~cGameApp();

	LPDIRECT3DVERTEXBUFFER9 g_pVB; // 버텍스 버퍼
	LPDIRECT3DINDEXBUFFER9 g_pIB; // 인덱스 버퍼

	LPDIRECT3DVERTEXBUFFER9 g_pVB2; // 버텍스 버퍼
	LPDIRECT3DINDEXBUFFER9 g_pIB2; // 인덱스 버퍼

	int WINSIZE_X;		//초기 윈도우 가로 크기
	int WINSIZE_Y;	//초기 윈도우 세로 크기
	int WINPOS_X; //초기 윈도우 시작 위치 X
	int WINPOS_Y; //초기 윈도우 시작 위치 Y

	//카메라 벡터
	Vector3 camPositon;
	Vector3 camTarget; 
	Vector3 camUpVecter;
	Matrix44 camVecter;
	int badakNum;

	//

	float num1;
	float num2;
	float num5;
	float num6;
	virtual bool OnInit() override;
	virtual void OnUpdate(const float elapseT) override;
	virtual void OnRender(const float elapseT) override;
	virtual void OnShutdown() override;
	virtual void MessageProc( UINT message, WPARAM wParam, LPARAM lParam) override;
	void newBadak(int num);
	void penguin(float num1, float num2);
protected:

};

