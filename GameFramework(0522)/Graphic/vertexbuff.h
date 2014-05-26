#pragma once

namespace graphic
{
	class vertexbuff
	{
	public:
		vertexbuff(void);
		~vertexbuff(void);

		bool Create(int faceCount);
		void* Lock();
		void Unlock();

		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
		Vertex* vertices;
	};

	
}


