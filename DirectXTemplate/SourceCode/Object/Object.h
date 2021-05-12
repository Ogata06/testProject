/**
* @file Objct.h.
* @brief �I�u�W�F�N�g���N���X.
* @author ���c���.
*/
#ifndef OBJECT_H
#define OBJECT_H

#include "..\Global.h"
#include "..\Common\DebugText\DebugText.h"

/*******************************************
*	�I�u�W�F�N�g�N���X.
**/
class CObject
{
public:
	CObject();
	virtual ~CObject();

	// �g�����X�t�H�[���̐ݒ�.
	inline void SetTranceform	( const STranceform& t ){ m_Tranceform = t; }
	// ���W�̐ݒ�.
	inline void SetPosition		( const D3DXVECTOR3& p ){ m_Tranceform.Position = p; }
	// ��]�̐ݒ�.
	inline void SetRotation		( const D3DXVECTOR3& r ){ m_Tranceform.Rotation = r; }
	// �g��E�k���̐ݒ�.
	inline void SetScale		( const D3DXVECTOR3& s ){ m_Tranceform.Scale = s; }

	// �g�����X�t�H�[���̎擾.
	inline STranceform GetTranceform() const { return m_Tranceform; }
	// ���W�̎擾.
	inline D3DXVECTOR3 GetPosition	() const { return m_Tranceform.Position; }
	// ��]�̎擾.
	inline D3DXVECTOR3 GetRotation	() const { return m_Tranceform.Rotation; }
	// �g��E�k���̎擾.
	inline D3DXVECTOR3 GetScale		() const { return m_Tranceform.Scale; }

protected:
	STranceform m_Tranceform;	// �g�����X�t�H�[��.
};

#endif	// #ifndef OBJECT_H.