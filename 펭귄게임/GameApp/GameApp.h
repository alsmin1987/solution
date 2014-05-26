
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

	LPDIRECT3DVERTEXBUFFER9 g_pVB; // ���ؽ� ����
	LPDIRECT3DINDEXBUFFER9 g_pIB; // �ε��� ����

	LPDIRECT3DVERTEXBUFFER9 g_pVB2; // ���ؽ� ����
	LPDIRECT3DINDEXBUFFER9 g_pIB2; // �ε��� ����

	int WINSIZE_X;		//�ʱ� ������ ���� ũ��
	int WINSIZE_Y;	//�ʱ� ������ ���� ũ��
	int WINPOS_X; //�ʱ� ������ ���� ��ġ X
	int WINPOS_Y; //�ʱ� ������ ���� ��ġ Y

	//ī�޶� ����
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

