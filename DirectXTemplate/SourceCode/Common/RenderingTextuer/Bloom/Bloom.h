#ifndef BLOOM_RENDER_H
#define BLOOM_RENDER_H

#include "..\RenderingTextuer.h"

class CDownSamplingRender;

/***********************************************
*	�u���[���`��N���X.
**/
class CBloomRender : public CRenderTexture
{
	struct C_BUFFER_PER_FRAME
	{
		D3DXVECTOR4 SoftKneePram;
	};
public:
	CBloomRender();
	virtual ~CBloomRender();

	// ������.
	virtual HRESULT Init( ID3D11DeviceContext* pContext11 ) override;

	// �`��.
	void Render( const int& srvCount, const std::vector<ID3D11ShaderResourceView*>& srvList );

	// �o�b�t�@�̐ݒ�.
	virtual void SetBuffer() override;
	// �V�F�[�_�[���\�[�X�r���[�̐����擾.
	virtual int GetSRVCount() override { return m_pShaderResourceViewList.size(); }

protected:
	// �e�N�X�`���̏�����.
	virtual HRESULT InitBufferTex() override;

private:
	// ���_�o�b�t�@�[�̍쐬.
	virtual HRESULT InitVertexBuffer() override;
	// �R���X�^���g�o�b�t�@�̍쐬.
	virtual HRESULT InitConstantBuffer() override;

private:
	std::unique_ptr<CDownSamplingRender>	m_pDownSampling;		// �_�E���T���v��.
	std::vector<ID3D11Buffer*>				m_pConstantBuffersInit;	// �R���X�^���g�o�b�t�@.
	std::vector<ID3D11Buffer*>				m_pVertexBuffers;		// ���_�o�b�t�@.
};

#endif	// #ifndef BLOOM_RENDER_H.