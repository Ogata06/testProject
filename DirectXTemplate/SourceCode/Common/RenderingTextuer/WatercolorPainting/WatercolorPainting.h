#ifndef WATERCOLOR_PAINTING_RENDER_H
#define WATERCOLOR_PAINTING_RENDER_H

#include "..\RenderingTextuer.h"

/***********************************************
*	���C�e�B���O�`��N���X.
**/
class CWatercolorPaintingRender : public CRenderTexture
{
	// �R���X�^���g�o�b�t�@.
	struct LIGHT_CBUFFER
	{
		D3DXVECTOR4 Color;
		LIGHT_CBUFFER()
		{
		};
	};

public:
	CWatercolorPaintingRender();
	virtual ~CWatercolorPaintingRender();

	// ������.
	virtual HRESULT Init( ID3D11DeviceContext* pContext11 ) override;

	// �`��.
	void Render( const int& srvCount, const std::vector<ID3D11ShaderResourceView*>& srvList );

	// �o�b�t�@�̐ݒ�.
	virtual void SetBuffer() override;
	// �V�F�[�_�[���\�[�X�r���[�̐����擾.
	virtual int GetSRVCount() override { return 1; }

protected:
	// �e�N�X�`���̏�����.
	virtual HRESULT InitBufferTex() override;

private:
	ID3D11Buffer*	m_pConstantBufferFrame;	// �R���X�^���g�o�b�t�@.
};

#endif	// #ifndef WATERCOLOR_PAINTING_RENDER_H.