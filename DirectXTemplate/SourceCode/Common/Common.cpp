#include "Common.h"

CCommon::CCommon()
	: m_pDevice11				( nullptr )
	, m_pContext11				( nullptr )
	, m_Tranceform				()
	, m_Color					( 1.0f, 1.0f, 1.0f, 1.0f )
{
}

CCommon::~CCommon()
{
	m_pContext11	= nullptr;
	m_pDevice11		= nullptr;
}

//--------------------------------------------.
// �f�o�C�X�̎擾�A�e���̏�����.
//--------------------------------------------.
HRESULT CCommon::SetDevice( ID3D11DeviceContext* pContext11 )
{
	if( pContext11 == nullptr ){
		ERROR_MESSAGE( "�f�o�C�X�R���e�L�X�g�擾 : ���s" );
		return E_FAIL;
	}

	m_pContext11 = pContext11;
	m_pContext11->GetDevice( &m_pDevice11 );
	if( m_pDevice11 == nullptr ){
		ERROR_MESSAGE( "�f�o�C�X�擾 : ���s" );
		return E_FAIL;
	}

	return S_OK;
}

//--------------------------------------------.
// �u�����h��L��:�����ɐݒ肷��.
//--------------------------------------------.
void CCommon::SetBlend( bool EnableAlpha )
{
	CDirectX11::SetBlend( EnableAlpha );
}

//--------------------------------------------.
// �A���t�@�J�o���[�W��L��:�����ɐݒ肷��.
//--------------------------------------------.
void CCommon::SetCoverage( bool EnableCoverage )
{
	CDirectX11::SetCoverage( EnableCoverage );
}

//--------------------------------------------.
// �[�x�e�X�g��L��:�����ɐݒ肷��.
//--------------------------------------------.
void CCommon::SetDeprh( bool flag )
{
	CDirectX11::SetDeprh( flag );
}

//--------------------------------------------.
// ���X�^���C�U�X�e�[�g�ݒ�.
//--------------------------------------------.
void CCommon::SetRasterizerState( const ERS_STATE& rsState )
{
	CDirectX11::SetRasterizerState( rsState );
}
