/**
* @file ColliderBase.h.
* @brief �����蔻����N���X.
* @author ���c���.
*/
#ifndef COLLIDER_BASE_H
#define COLLIDER_BASE_H

#include "..\Object.h"

/**********************************************
*	�����蔻��p�x�[�X�N���X.
**/
class CColliderBase : public CObject
{
public:
	CColliderBase();
	virtual ~CColliderBase();

	// �q�b�g�t���O�𗧂Ă�.
	inline void SetHitOn()		{ m_IsHit = true; }
	// �q�b�g�t���O�����낷.
	inline void SetHitOff()		{ m_IsHit = false; }
	inline bool IsHit()	const	{ return m_IsHit; }

protected:
	bool	m_IsHit;	// �q�b�g�t���O.
};

#endif	// #ifndef COLLIDER_BASE_H.