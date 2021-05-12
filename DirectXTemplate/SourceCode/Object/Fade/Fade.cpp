#include "Fade.h"
#include "..\..\Common\Sprite\Sprite.h"
#include "..\..\Resource\SpriteResource\SpriteResource.h"
#include "..\..\Utility\Input\Input.h"

namespace
{
	constexpr char	MAIN_TEXTURE_NAME[]	= "Data\\Sprite\\Fade.png";
	constexpr char	MASK_TEXTURE_NAME[]	= "Data\\Sprite\\Mask.png";
	constexpr float	FADE_IN_SECONDS		= 0.8f;	// �t�F�[�h�C�����鎞��.
	constexpr float	FADE_OUT_SECONDS	= 0.6f;	// �t�F�[�h�A�E�g���鎞��.
	constexpr float	FADE_VALUE_MAX		= 1.0f;
	constexpr float	FADE_VALUE_MIN		= 0.0f;
};


CFade::CFade()
	: m_MainSprite		( nullptr )
	, m_MaskSprite		( nullptr )
	, m_MainSpriteState	()
	, m_NowState		( EFadeState::End )
	, m_IsNextFade		( false )
	, m_IsKeepRender	( false )
{
	m_MainSprite = std::make_unique<CSprite>();
	m_MaskSprite = std::make_unique<CSprite>();
}

CFade::~CFade()
{
}

// �C���X�^���X�̐���.
CFade* CFade::GetInstance()
{
	static std::unique_ptr<CFade> pInstance = std::make_unique<CFade>();
	return pInstance.get();
}

// ������.
bool CFade::Init()
{
	if( GetInstance()->LoadSprite() == false ) return false;

	return true;
}

// �X�V.
void CFade::Update( const float& deltaTime )
{
	switch( GetInstance()->m_NowState )
	{
	case EFadeState::In:
		if( GetInstance()->m_MainSpriteState.FadeValue < FADE_VALUE_MAX ){
			GetInstance()->m_MainSpriteState.FadeValue += deltaTime / FADE_IN_SECONDS;
		} else {
			GetInstance()->m_MainSpriteState.FadeValue = FADE_VALUE_MAX;
			GetInstance()->m_NowState = EFadeState::End;
			if( GetInstance()->m_IsNextFade == true ){
				GetInstance()->m_NowState = EFadeState::Out;
				GetInstance()->m_IsNextFade = false;
			}
		}
		break;
	case EFadeState::Out:
		if( GetInstance()->m_MainSpriteState.FadeValue > FADE_VALUE_MIN ){
			GetInstance()->m_MainSpriteState.FadeValue -= deltaTime / FADE_OUT_SECONDS;
		} else {
			GetInstance()->m_MainSpriteState.FadeValue = FADE_VALUE_MIN;
			GetInstance()->m_NowState = EFadeState::End;
			if( GetInstance()->m_IsNextFade == true ){
				GetInstance()->m_NowState = EFadeState::In;
				GetInstance()->m_IsNextFade = false;
			}
		}
		break;
	case EFadeState::End:
		break;
	}
}

// �`��.
void CFade::Render()
{
	if( GetInstance()->m_IsKeepRender == false ){
		if( GetInstance()->m_NowState == EFadeState::End ) return;
	}
	GetInstance()->m_MainSprite->SetMaskTexture( GetInstance()->m_MaskSprite->GetTexture() );
	GetInstance()->m_MainSprite->Render( &GetInstance()->m_MainSpriteState );
}

// �t�F�[�h�C���ݒ�֐�.
void CFade::SetFadeIn( const bool& isNextFade )
{
	if( GetInstance()->m_NowState == EFadeState::In ) return;

	GetInstance()->m_MainSpriteState.FadeValue = FADE_VALUE_MIN;
	GetInstance()->m_NowState = EFadeState::In;
	GetInstance()->m_IsNextFade = isNextFade;
}

// �t�F�[�h�A�E�g�ݒ�֐�.
void CFade::SetFadeOut( const bool& isNextFade )
{
	if( GetInstance()->m_NowState == EFadeState::Out ) return;

	GetInstance()->m_MainSpriteState.FadeValue = FADE_VALUE_MAX;
	GetInstance()->m_NowState = EFadeState::Out;
	GetInstance()->m_IsNextFade = isNextFade;
}

// �����ĕ`�悷��.
void CFade::KeepRender( const bool& isKeep )
{
	GetInstance()->m_IsKeepRender = isKeep;
}

// �摜�̓ǂݍ���.
bool CFade::LoadSprite()
{
	if( FAILED( m_MainSprite->Init( CDirectX11::GetContext(), MAIN_TEXTURE_NAME ) )) return false;
	if( FAILED( m_MaskSprite->Init( CDirectX11::GetContext(), MASK_TEXTURE_NAME ) )) return false;
	m_MainSpriteState = m_MainSprite->GetRenderState();
	m_MainSpriteState.ShaderNo = EPSShaderNo_TAlphaOut;

	return true;
}