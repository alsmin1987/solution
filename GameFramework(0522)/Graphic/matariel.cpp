#include "StdAfx.h"
#include "matariel.h"

using namespace graphic;


void matariel::Init( const Vector4 &ambient, const Vector4 &diffuse, const Vector4 &specular, const Vector4 &emissive, const float pow )
{
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	m_mtrl.Ambient = *(D3DXCOLOR*)&ambient;
	m_mtrl.Diffuse = *(D3DXCOLOR*)&diffuse;
	m_mtrl.Specular = *(D3DXCOLOR*)&specular;
	m_mtrl.Emissive = *(D3DXCOLOR*)&emissive;
	m_mtrl.Power = pow;
}

void matariel::Bind()
{
	GetDevice()->SetMaterial(&m_mtrl);
}

void matariel::InitBlue()
{
	Init(Vector4(0,0,1,1),
		Vector4(0,0,1,1),
		Vector4(0,0,1,1),
		Vector4(0,0,0,1),
		0);
}
