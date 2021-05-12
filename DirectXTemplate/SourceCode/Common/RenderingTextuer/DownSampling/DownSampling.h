#ifndef DOWN_SAMPLING_RENDER_H
#define DOWN_SAMPLING_RENDER_H

#include "..\RenderingTextuer.h"

/***********************************************
*	Bloom�p�ɖ��x�𗎂Ƃ��N���X.
**/
class CDownSamplingRender : public CRenderTexture
{
public:
	struct stDownSamplePrame
	{
		float SoftThrshold;
		float Thrshold;
		float Intensity;

		stDownSamplePrame()
			: SoftThrshold	( 1.0f )
			, Thrshold		( 0.55f )
			, Intensity		( 1.0f )
		{}
	} typedef SDownSamplePrame;

private:
	struct C_BUFFER_PER_FRAME
	{
		D3DXVECTOR4 SoftKneePram;
		D3DXVECTOR4 Intensity;
	};

public:
	CDownSamplingRender();
	virtual ~CDownSamplingRender();

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
	ID3D11Buffer*		m_pConstantBufferFrame;	// �R���X�^���g�o�b�t�@.
	SDownSamplePrame	m_DownSamleParam;
};

#endif	// #ifndef DOWN_SAMPLING_RENDER_H.