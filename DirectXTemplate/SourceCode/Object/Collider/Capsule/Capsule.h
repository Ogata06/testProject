/**
* @file Capsule.h.
* @brief �J�v�Z���N���X.
* @author ���c���.
*/
#ifndef CAPSULE_H
#define CAPSULE_H

#include "..\ColliderBase.h"
#include "CapsuleCalculation.h"

/*****************************************
*	�J�v�Z���N���X.
**/
class CCapsule : public CColliderBase
{
public:
	CCapsule();
	virtual ~CCapsule();

	// ���a�̐ݒ�.
	inline void		SetRadius( const float& rad )	{ m_Radius = rad; }
	// ���a�̎擾.
	inline float	GetRadius() const				{ return m_Radius; }
	// �����̐ݒ�.
	inline void		SetHeight( const float& height ){ m_Height = height; }
	// �����̎擾.
	inline float	GetHeight() const				{ return m_Height; }

	SSegment GetSegment();

private:
	float m_Radius;	// ���a.
	float m_Height;	// �J�v�Z���̍���.
};

#endif	// #ifndef SPHERE_H.