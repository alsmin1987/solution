#pragma once

namespace graphic
{
	class indexbuff
	{
	public:
		indexbuff(void);
		~indexbuff(void);
	
		bool Create(int faceCount);
		void* Lock();
		void Unlock();

		LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;
		WORD* indices;
	};
}


