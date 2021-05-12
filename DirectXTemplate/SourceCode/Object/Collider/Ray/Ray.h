/**
* @file Ray.h.
* @brief ���C�N���X.
* @author ���c���.
*/
#ifndef RAY_H
#define RAY_H

#include "..\ColliderBase.h"

/*****************************************
*	���C�N���X.
**/
class CRay : public CColliderBase
{
public:
	CRay();
	virtual ~CRay();

	// �����x�N�g���̐ݒ�.
	void SetVector( const D3DXVECTOR3& v )		{ m_Vector = v; }
	// �J�n�ʒu�̐ݒ�.
	void SetStartPos( const D3DXVECTOR3& pos )	{ m_StartPos = pos; }
	// �I���ʒu�̐ݒ�.
	void SetEndPos( const D3DXVECTOR3& pos )	{ m_EndPos = pos ; }
	// �����x�N�g���̎擾.
	D3DXVECTOR3 GetVector()		const { return m_Vector; }
	// �J�n�ʒu�̎擾.
	D3DXVECTOR3 GetStartPos()	const { return m_StartPos; }
	// �I���ʒu�̎擾.
	D3DXVECTOR3 GetEndPos()		const { return m_EndPos; }

private:
	D3DXVECTOR3 m_Vector;	// �����x�N�g��.
	D3DXVECTOR3 m_StartPos;	// ���C�J�n�ʒu.
	D3DXVECTOR3 m_EndPos;	// ���C�I���ʒu.
};

#endif	// #ifndef RAY_H.