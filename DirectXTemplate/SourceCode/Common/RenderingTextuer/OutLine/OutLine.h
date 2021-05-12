#ifndef OUTLINE_RENDER_H
#define OUTLINE_RENDER_H

#include "..\RenderingTextuer.h"

/***********************************************
*	�A�E�g���C���`��N���X.
**/
class COutLineRender : public CRenderTexture
{
	// G-Buffer�̎��.
	enum enOutLineNo
	{
		EOutLineNo_Default,		// �A�E�g���C��+�F���..
		EOutLineNo_LineOnly,	// �A�E�g���C���̂�.

		EOutLineNo_MAX,	// �ő�l.

	} typedef EOutLineNo;

public:
	// �R���X�^���g�o�b�t�@.
	struct OUTLINE_CBUFFER
	{
		// �T���v��.
		struct OUTLINE_SAMPLE
		{
			float NormalPower;		// �@���̃T���v���̋���.
			float NormalCompare;	// �@���̔�r�l.
			float DepthPower;		// �[�x�l�̃T���v���̋���.
			float DepthCompare;		// �[�x�l�̔�r�l.
			OUTLINE_SAMPLE()
				: NormalPower	( 0.0f )
				, NormalCompare	( 0.0f )
				, DepthPower	( 0.0f )
				, DepthCompare	( 0.0f )
			{}
		};
		D3DXVECTOR4		Color;
		OUTLINE_SAMPLE	Sample;

		OUTLINE_CBUFFER()
			: Color		( 0.0f, 0.0f, 0.0f, 0.0f )
			, Sample	()
		{};
	};

public:
	COutLineRender();
	virtual ~COutLineRender();

	// ������.
	virtual HRESULT Init( ID3D11DeviceContext* pContext11 ) override;

	// �`��.
	void Render( const int& srvCount, const std::vector<ID3D11ShaderResourceView*>& srvList );

	// �o�b�t�@�̐ݒ�.
	virtual void SetBuffer() override;
	// �V�F�[�_�[���\�[�X�r���[�̐����擾.
	virtual int GetSRVCount() override { return EOutLineNo_MAX; }

protected:
	// �e�N�X�`���̏�����.
	virtual HRESULT InitBufferTex() override;

private:
	ID3D11Buffer*	m_pConstantBufferFrame;	// �R���X�^���g�o�b�t�@.
	OUTLINE_CBUFFER	m_OutlineBuffer;
};

#endif	// #ifndef OUTLINE_RENDER_H.