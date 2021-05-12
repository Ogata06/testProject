#include "LoadRender.h"
#include "..\..\Common\Sprite\Sprite.h"
#include "..\..\Common\Sprite\SpriteRender.h"

namespace
{
	constexpr char	BACK_SPRITE_NAME[]			= "Data\\Sprite\\loadBase.png";	// �w�i�̉摜.
	constexpr float	BACK_SPRITE_SCROLL_SPEED	= 0.1f;
	enum enSpriteNo : unsigned char
	{
		ESpriteNo_None,

		ESpriteNo_Back = 0,

	} typedef ESpriteNo;
};


CLoadRender::CLoadRender()
	: m_pSprites		()
	, m_DeltaTime		( 0.0f )
	, m_IsLoadEnd		( false )
{
}

CLoadRender::~CLoadRender()
{
}

// �ǂݍ��݃N���X.
bool CLoadRender::Init()
{
	if( m_IsLoadEnd == true ) return true;

	if( LoadSprite()	== false )		return false;

	m_IsLoadEnd = true;
	return true;
}

// �X�V�֐�.
void CLoadRender::Update( const float& deltaTime )
{
	m_DeltaTime = deltaTime;
}

// �`��N���X.
void CLoadRender::Render()
{
	if( m_IsLoadEnd == false ) return;

	int spiteNo = ESpriteNo_None;
	for( auto& s : m_pSprites ){
		switch( spiteNo )
		{
		case ESpriteNo_Back:
			s->SetScrollSpeedX( BACK_SPRITE_SCROLL_SPEED * m_DeltaTime );
			break;
		}
		s->Render();
		spiteNo++;
	}
}

// �X�v���C�g�̐ݒ�.
bool CLoadRender::LoadSprite()
{
	const char* loadSpriteList[] =
	{
		BACK_SPRITE_NAME,
	};

	int spiteNo = ESpriteNo_None;
	// �ǂݍ��ރX�v���C�g�̐������[�v.
	for( auto& s : loadSpriteList ){
		m_pSprites.emplace_back( std::make_unique<CSprite>() );	// �v�f�̒ǉ�.
		// �摜�̓ǂݍ���.
		if( FAILED( m_pSprites.back()->Init( CDirectX11::GetContext(), s ) )){
			// ���s�����ꍇ�A�v�f����0�ɂ��ďI��.
			m_pSprites.clear();
			return false;
		}

		switch( spiteNo )
		{
		case ESpriteNo_Back:
			m_pSprites.back()->SetScrollUpdateX( true );
			break;
		}

		spiteNo++;
	}
	return true;
}