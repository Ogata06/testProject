#ifndef G_BUFFER_RENDER_H
#define G_BUFFER_RENDER_H

#include "..\RenderingTextuer.h"

/*********************************************
*	G-Buffer�̕`��N���X.
**/
class CGBufferRender : public CRenderTexture
{
public:
	// G-Buffer�̎��.
	enum enGBufferNo
	{
		EGBufferNo_BACK,		// �F���.
		EGBufferNo_COLOR,		// �F���.
		EGBufferNo_NORMAL,		// �@�����.
		EGBufferNo_WORLDPOS,	// ���[���h���W.
		EGBufferNo_Z_DEPTH,		// �[�x�l���.
		EGBufferNo_DIFFUSE,		// �F���.

		EGBufferNo_MAX,	// �ő�l.

	} typedef EGBufferNo;
public:
	CGBufferRender();
	virtual ~CGBufferRender();

	// ������.
	virtual HRESULT Init( ID3D11DeviceContext* pContext11 ) override;

	// �o�b�t�@�̐ݒ�.
	virtual void SetBuffer() override;
	// �V�F�[�_�[���\�[�X�r���[�̐����擾.
	virtual int GetSRVCount() override { return EGBufferNo_MAX; }

protected:
	// �e�N�X�`���̏�����.
	virtual HRESULT InitBufferTex() override;
};

#endif	// #ifndef G_BUFFER_RENDER_H.