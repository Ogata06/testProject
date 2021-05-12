#include "KeyInput.h"

#include <Windows.h>
#include <memory>

CKeyInput::CKeyInput()
	: m_NowInputState() 
{
	for( auto& k : m_NowInputState ) k = 0;
	for( auto& k : m_OldInputState ) k = 0;
}

CKeyInput::~CKeyInput()
{}

// �L�[�̏�Ԃ̍X�V.
void CKeyInput::Update()
{
	GetInstance()->KeyStateUpdate();
}

// ������Ă���Ƃ�.
bool CKeyInput::IsPress( const unsigned char& key )
{
	if( GetNowState( key ) & 0x80 ) return true;
	return false;
}

// �����ꂽ�u��.
bool CKeyInput::IsMomentPress( const unsigned char& key )
{
	// ���ݓ��͂őO����͂��ĂȂ����.
	if( ( GetNowState( key ) & 0x80 ) != 0 &&
		( GetOldState( key ) & 0x80 ) == 0){
		return true;
	}
	return false;
}

// ���������Ă���Ƃ�.
bool CKeyInput::IsHold( const unsigned char& key )
{
	// ���݂����͂őO������͂Ȃ�.
	if( ( GetNowState( key ) & 0x80 ) != 0 &&
		( GetOldState( key ) & 0x80 ) != 0){
		return true;
	}
	return false;
}

// �������u��.
bool CKeyInput::IsRelease( const unsigned char& key )
{
	// ���݂����͂őO������͂Ȃ�.
	if( ( GetNowState( key ) & 0x80 ) == 0 &&
		( GetOldState( key ) & 0x80 ) != 0){
		return true;
	}
	return false;
}

// �C���X�^���X�̎擾.
CKeyInput* CKeyInput::GetInstance()
{
	static std::unique_ptr<CKeyInput> pInstance = std::make_unique<CKeyInput>();
	return pInstance.get();
}

// �L�[�̏�Ԃ̍X�V.
void CKeyInput::KeyStateUpdate()
{
	memcpy_s( m_OldInputState, sizeof(m_OldInputState), m_NowInputState, sizeof(m_NowInputState) );
	GetKeyboardState( m_NowInputState );
};

// �L�[�̏�Ԃ̎擾.
unsigned char CKeyInput::GetNowState( const unsigned char& key )
{
	return GetInstance()->m_NowInputState[key];
}

// �L�[�̏�Ԃ̎擾.
unsigned char CKeyInput::GetOldState( const unsigned char& key )
{
	return GetInstance()->m_OldInputState[key];
}
