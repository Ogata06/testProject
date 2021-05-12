/**
* @file Sphere.h.
* @brief ���̃N���X.
* @author ���c���.
*/
#ifndef SPHERE_H
#define SPHERE_H

#include "..\ColliderBase.h"

/*****************************************
*	���̃N���X.
**/
class CSphere : public CColliderBase
{
public:
	CSphere();
	virtual ~CSphere();

	// ���a�̐ݒ�.
	inline void		SetRadius( const float& rad )	{ m_Radius = rad; }
	// ���a�̎擾.
	inline float	GetRadius() const				{ return m_Radius; }

private:
	float m_Radius;	// ���a.
};

#endif	// #ifndef SPHERE_H.