#include "StdAfx.h"
#include "indexbuff.h"

using namespace graphic;

indexbuff::indexbuff(void)
{
}


indexbuff::~indexbuff(void)
{
	if(m_pIdxBuff)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

bool graphic::indexbuff::Create( int faceCount )
{
	if(FAILED(graphic::GetDevice()->CreateIndexBuffer(faceCount * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff, NULL)))
	{
		return false;
	}

	return true;
}

void* graphic::indexbuff::Lock()
{
	indices = NULL;
	m_pIdxBuff->Lock(0, 0, (void**)*indices, 0);
	return indices;
}

void graphic::indexbuff::Unlock()
{
	m_pIdxBuff->Unlock();
}
