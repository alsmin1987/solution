#include "StdAfx.h"
#include "renderer.h"
#include <fstream>

using namespace graphic;

renderer::renderer()
{

}

renderer::~renderer()
{

}


bool renderer::CreateDivice( HWND hWnd, const int width, const int height )
{
	if(!InitDirectX(hWnd, width, height, m_pDevice))
		return false;
	
	return true;
}

LPDIRECT3DDEVICE9 renderer::GetDevice()
{
	return m_pDevice;
}

bool graphic::InitRenderer( HWND hWnd, const int width, const int height )
{
	if(!renderer::Get()->CreateDivice(hWnd, width, height))
		return false;

	return true;
}

void graphic::ReleaseRenderer()
{

}

renderer* graphic::GetRenderer()
{
	return renderer::Get();
}

LPDIRECT3DDEVICE9 graphic::GetDevice()
{
	return renderer::Get()->GetDevice();
}

void graphic::ComputeNormals( graphic::vertexbuff vtxBuff, int vtxSize, graphic::indexbuff idxBuff, int faceSize )
{
	

	Vertex* vertices =(Vertex*)vtxBuff.Lock();
	WORD *indices = (WORD*)idxBuff.Lock();

	for (int i=0; i < faceSize*3; i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]].p;
		Vector3 p2 = vertices[ indices[ i+1]].p;
		Vector3 p3 = vertices[ indices[ i+2]].p;

		Vector3 v1 = p2 - p1;
		Vector3 v2 = p3 - p1;
		v1.Normalize();
		v2.Normalize();
		Vector3 n = v1.CrossProduct(v2);
		n.Normalize();

		if (vertices[ indices[ i]].n.IsEmpty())
		{
			vertices[ indices[ i]].n = n;
		}
		else
		{
			vertices[ indices[ i]].n += n;
			vertices[ indices[ i]].n /= 2.f;
		}

		if (vertices[ indices[ i+1]].n.IsEmpty())
		{
			vertices[ indices[ i+1]].n = n;
		}
		else
		{
			vertices[ indices[ i+1]].n += n;
			vertices[ indices[ i+1]].n /= 2.f;
		}

		if (vertices[ indices[ i+2]].n.IsEmpty())
		{
			vertices[ indices[ i+2]].n = n;
		}
		else
		{
			vertices[ indices[ i+2]].n += n;
			vertices[ indices[ i+2]].n /= 2.f;
		}
	}



	vtxBuff.Unlock();
	idxBuff.Unlock();
}

bool ReadModelFile( const string &fileName, LPDIRECT3DVERTEXBUFFER9 &vtxBuff, int &vtxSize, LPDIRECT3DINDEXBUFFER9 &idxBuff, int &faceSize )
{
	using namespace std;
	ifstream fin(fileName.c_str());
	if (!fin.is_open())
		return false;

	string vtx, vtx_eq;
	int numVertices;
	fin >> vtx >> vtx_eq >> numVertices;

	if (numVertices <= 0)
		return  false;

	vtxSize = numVertices;

	graphic::vertexbuff m_vtxBuff;

	m_vtxBuff.Create(vtxSize);
	m_vtxBuff.Lock();
	
	float num1, num2, num3;
	for (int i = 0; i < numVertices; i++)
	{
		fin >> num1 >> num2 >> num3;
		m_vtxBuff.vertices[i] = Vertex(num1, num2, num3);
	}

	m_vtxBuff.Unlock();


	string idx, idx_eq;
	int numIndices;
	fin >> idx >> idx_eq >> numIndices;

	if (numIndices <= 0)
		return false;

	faceSize = numIndices;

	graphic::indexbuff m_idxBuff;

	m_idxBuff.Create(faceSize);

	m_idxBuff.Lock();
	
	int num4, num5, num6;
	for (int i = 0; i < numIndices*3; i+=3)
	{
		fin >> num4 >> num5 >> num6;
		m_idxBuff.indices[ i] = num4;
		m_idxBuff.indices[ i+1] = num5;
		m_idxBuff.indices[ i+2] = num6;	
	}

	m_idxBuff.Unlock();

//	ComputeNormals(vtxBuff, vtxSize, idxBuff, faceSize); //정의 필요
	return true;
}
