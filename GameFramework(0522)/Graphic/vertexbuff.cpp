#include "StdAfx.h"
#include "vertexbuff.h"

using namespace graphic;

vertexbuff::vertexbuff(void)
{
}


vertexbuff::~vertexbuff(void)
{
}

bool vertexbuff::Create( int faceCount )
{
	if (FAILED(graphic::GetDevice()->CreateVertexBuffer(faceCount * sizeof(Vertex),
		D3DUSAGE_WRITEONLY, Vertex::FVF,
		D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return false;
	}

	return true;
}

void* vertexbuff::Lock()
{
	m_pVtxBuff->Lock( 0, sizeof(Vertex), (void**)&vertices, 0);

	return vertices;
}

void vertexbuff::Unlock()
{
	m_pVtxBuff->Unlock();
}
