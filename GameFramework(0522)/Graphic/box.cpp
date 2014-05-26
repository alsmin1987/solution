#include "StdAfx.h"
#include "box.h"

using namespace graphic;

box::box(void)
{
}


box::~box(void)
{
}

void box::SetBox( const Vector3 &vMin, const Vector3 &vMax )
{
	m_box[0] = Vector3( vMin.x, vMax.y, vMax.z);
	m_box[1] = Vector3( vMax.x, vMax.y, vMax.z);
	m_box[2] = Vector3( vMin.x, vMax.y, vMin.z);
	m_box[3] = Vector3( vMax.x, vMax.y, vMin.z);
	m_box[4] = Vector3( vMin.x, vMin.y, vMax.z);
	m_box[5] = Vector3( vMax.x, vMin.y, vMax.z);
	m_box[6] = Vector3( vMin.x, vMin.y, vMin.z);
	m_box[7] = Vector3( vMax.x, vMin.y, vMin.z);
	m_min = vMin;
	m_max = vMax;
//	m_matWorld.SetIdentity();
}

bool box::IsCollision( const Box &box )
{
  return false;
}

void graphic::box::SetWorldTM( const Matrix44 &tm )
{

}
