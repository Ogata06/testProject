#ifndef SHADOW_H
#define SHADOW_H

#include "..\RenderingTextuer.h"

class CShadow : public CRenderTexture
{
public:
	CShadow();
	virtual ~CShadow();

	// ������.
	virtual HRESULT Init( ID3D11DeviceContext* pContext11 ) override;

	// �o�b�t�@�̐ݒ�.
	virtual void SetBuffer() override;
	// �V�F�[�_�[���\�[�X�r���[�̐����擾.
	virtual int GetSRVCount() override;


	// �e�N�X�`���̏�����.
	virtual HRESULT InitBufferTex() override;
};

#endif	// #ifndef SHADOW_H.