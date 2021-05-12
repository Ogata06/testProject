/**
* @file Common.h.
* @brief �f�o�C�X�g�p�n�̊��N���X.
* @author ���c���.
*/
#ifndef COMMON_H
#define COMMON_H

#include "..\Global.h"
#include "D3DX/D3DX11.h"

/***************************************
*	�f�o�C�X���g�p�n�N���X�̊��N���X.
**/
class CCommon
{
public:
	CCommon();
	virtual ~CCommon();

	// �g�����X�t�H�[���̐ݒ�.
	void SetTranceform( const STranceform& t ){ m_Tranceform = t; }
	// ���W�̐ݒ�.
	void SetPosition( const D3DXVECTOR3& vPos ){ m_Tranceform.Position = vPos; }
	// ��]���̐ݒ�.
	void SetRotation( const D3DXVECTOR3& vRot ){ m_Tranceform.Rotation = vRot; }
	// �T�C�Y�̐ݒ�.
	void SetScale( const D3DXVECTOR3& vScale ){ m_Tranceform.Scale = vScale; }
	void SetScale( const float& fScale ){ m_Tranceform.Scale = { fScale, fScale, fScale }; }
	// �F�̐ݒ�.
	void SetColor( const D3DXVECTOR4& vColor ){ m_Color = vColor; }
	// �A���t�@�l�̐ݒ�.
	void SetAlpha( const float& fAlpha ){ m_Color.w = fAlpha; }

	// �u�����h��L��:�����ɐݒ肷��.
	void SetBlend( bool EnableAlpha );
	// �A���t�@�J�o���[�W��L��:�����ɐݒ肷��.
	void SetCoverage( bool EnableCoverage );
	// �[�x�e�X�g��L��:�����ɐݒ肷��.
	void SetDeprh( bool flag );
	// ���X�^���C�U�X�e�[�g�ݒ�.
	void SetRasterizerState( const ERS_STATE& rsState );

protected:
	// �f�o�C�X�̎擾�A�e���̏�����.
	HRESULT SetDevice( ID3D11DeviceContext* pContext11 );

protected:
	ID3D11Device*			m_pDevice11;	// �f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;	// �f�o�C�X�R���e�L�X�g.

	STranceform m_Tranceform;	// �g�����X�t�H�[��.
	D3DXVECTOR4 m_Color;		// �F.
};

#endif	// #ifndef COMMON_H.