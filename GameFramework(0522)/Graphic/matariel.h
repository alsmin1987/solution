#pragma once
namespace graphic
{
	class matariel
	{
	public:
		matariel(void);
		virtual ~matariel(void);

		void Init(const Vector4 &ambient,
			const Vector4 &diffuse,
			const Vector4 &specular,
			const Vector4 &emissive,
			const float pow);
		void Bind();
		void InitBlue();
		D3DMATERIAL9 m_mtrl;
	};
}


