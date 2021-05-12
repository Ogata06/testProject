#ifndef RAY_MESH_H
#define RAY_MESH_H

#include "..\..\Common.h"

class CRayMesh : public CCommon
{
	// ���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	// ���_���W.
	};
	// �R���X�^���g�o�b�t�@.
	struct C_BUFFER_PER_FRAME
	{
		D3DXMATRIX	mWVP;	// ���[���h�s��.
		D3DXVECTOR4	vColor;	// �F.
	};
public:
	CRayMesh();
	virtual ~CRayMesh();

	// �������֐�.
	HRESULT Init( ID3D11DeviceContext* pContext11 );
	// ���.
	void Release();

	// �`��֐�.
	void Render();

	// �x�N�g���̐ݒ�.
	void SetVector( const D3DXVECTOR3& v ){ m_Vector = v; }

private:
	// �V�F�[�_�[�̍쐬.
	HRESULT InitShader();
	// ���_�o�b�t�@�̍쐬.
	HRESULT InitVertexBuffer();

private:
	ID3D11VertexShader*		m_pVertexShader;	// ���_�V�F�[�_�[.
	ID3D11PixelShader*		m_pPixelShader;		// �s�N�Z���V�F�[�_�[.
	ID3D11InputLayout*		m_pVertexLayout;	// ���_���C�A�E�g.
	ID3D11Buffer*			m_pConstantBuffer;	// �R���X�^���g�o�b�t�@.
	ID3D11Buffer*			m_pVertexBuffer;	// ���_�o�b�t�@.

	D3DXVECTOR3				m_Vector;			// �����x�N�g��.
};

#endif	// #ifndef RAY_MESH_H.