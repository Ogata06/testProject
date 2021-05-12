#include "GBuffer.h"

CGBufferRender::CGBufferRender()
{
}

CGBufferRender::~CGBufferRender()
{
}

//------------------------------------.
// ������.
//------------------------------------.
HRESULT CGBufferRender::Init( ID3D11DeviceContext* pContext11 )
{
	if( FAILED( InitBase( pContext11 ) ))		return E_FAIL;
	if( FAILED( InitBufferTex() ))				return E_FAIL;
	return S_OK;
}

//------------------------------------.
// �o�b�t�@�̐ݒ�.
//------------------------------------.
void CGBufferRender::SetBuffer()
{
	CRenderTexture::SetBuffer( EGBufferNo_MAX );
}

//------------------------------------.
// �e�N�X�`���̏�����.
//------------------------------------.
HRESULT CGBufferRender::InitBufferTex()
{
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width				= m_WndWidth ;						// ��.
	texDesc.Height				= m_WndHeight;						// ����.
	texDesc.MipLevels			= 1;								// �~�b�v�}�b�v���x��:1.
	texDesc.ArraySize			= 1;								// �z��:1.
	texDesc.Format				= DXGI_FORMAT_R16G16B16A16_FLOAT;	// 32�r�b�g�t�H�[�}�b�g.
	texDesc.SampleDesc.Count	= 1;								// �}���`�T���v���̐�.
	texDesc.SampleDesc.Quality	= 0;								// �}���`�T���v���̃N�I���e�B.
	texDesc.Usage				= D3D11_USAGE_DEFAULT;				// �g�p���@:�f�t�H���g.
	texDesc.BindFlags			= D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;	// �����_�[�^�[�Q�b�g�A�V�F�[�_�[���\�[�X.
	texDesc.CPUAccessFlags		= 0;								// CPU����̓A�N�Z�X���Ȃ�.
	texDesc.MiscFlags			= 0;								// ���̑��̐ݒ�Ȃ�.

	m_pRenderTargetViewList.resize( EGBufferNo_MAX );
	m_pShaderResourceViewList.resize( EGBufferNo_MAX );
	m_pTexture2DList.resize( EGBufferNo_MAX );

	for( int i = 0; i < EGBufferNo_MAX; i++ ){
		if( i == EGBufferNo_Z_DEPTH ){
			texDesc.Format = DXGI_FORMAT_R32_FLOAT;;
		} else {
			texDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		}
		if( FAILED( CreateBufferTex(
			texDesc,
			&m_pRenderTargetViewList[i],
			&m_pShaderResourceViewList[i],
			&m_pTexture2DList[i] ))) return E_FAIL;
	}
	return S_OK;
}
