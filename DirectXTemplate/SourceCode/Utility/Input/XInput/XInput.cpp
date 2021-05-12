#include "XInput.h"
#include <algorithm>

CXInput::CXInput()
	: m_XinputState	()
{
}

CXInput::~CXInput()
{
	for( int i = 0; i < MAX_CONTROLLERS; i++ ){
		m_XinputState[i].Vibration.wLeftMotorSpeed	= 0;
		m_XinputState[i].Vibration.wRightMotorSpeed	= 0;
		// �o�C�u���[�V�����̒l�̐ݒ�.
		XInputSetState( i, &m_XinputState[i].Vibration );
	}
}

//------------------------------------------------------.
// �X�V.
//------------------------------------------------------.
void CXInput::Update( const float& time )
{
	GetInstance()->StateUpdate();
	GetInstance()->VibrationUpdate( time );
}

//------------------------------------------------------.
// ������Ă���Ƃ�.
//------------------------------------------------------.
bool CXInput::IsPress( const WORD& buttonMask, const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return false;	// �R���g���[���[�������Ȃ�I��.

	// �w�肵���{�^���̏�Ԃ̃`�F�b�N.
	if( GetInstance()->m_XinputState[connectNum].NowState.Gamepad.wButtons & buttonMask ) return true;
	return false;
}

//------------------------------------------------------.
// �������u��.
//------------------------------------------------------.
bool CXInput::IsMomentPress( const WORD& buttonMask, const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return false;	// �R���g���[���[�������Ȃ�I��.

	// ���ݓ��͂őO����͂��ĂȂ����.
	if( ( GetInstance()->m_XinputState[connectNum].NowState.Gamepad.wButtons & buttonMask ) != 0 && 
		( GetInstance()->m_XinputState[connectNum].OldState.Gamepad.wButtons & buttonMask ) == 0 ){
			return true;
	}
	return false;
}

//------------------------------------------------------.
// ���������Ă���Ƃ�.
//------------------------------------------------------.
bool CXInput::IsHold( const WORD& buttonMask, const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return false;	// �R���g���[���[�������Ȃ�I��.

	// ���݂����͂őO������͂Ȃ�.
	if( ( GetInstance()->m_XinputState[connectNum].NowState.Gamepad.wButtons & buttonMask ) != 0 && 
		( GetInstance()->m_XinputState[connectNum].OldState.Gamepad.wButtons & buttonMask ) != 0 ){
		return true;
	}
	return false;
}

//------------------------------------------------------.
// �������u��.
//------------------------------------------------------.
bool CXInput::IsRelease( const WORD& buttonMask, const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return false;	// �R���g���[���[�������Ȃ�I��.

	// ���ݓ��͂��ĂȂ��O����͂��Ă�����.
	if( ( GetInstance()->m_XinputState[connectNum].NowState.Gamepad.wButtons & buttonMask ) == 0 && 
		( GetInstance()->m_XinputState[connectNum].OldState.Gamepad.wButtons & buttonMask ) != 0 ){
		return true;
	}
	return false;
}

//------------------------------------------------------.
// ���g���K�[�擾.
//------------------------------------------------------.
BYTE CXInput::GetLeftTrigger( const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return 0;	// �R���g���[���[�������Ȃ�I��.
	return GetInstance()->m_XinputState[connectNum].NowState.Gamepad.bLeftTrigger;
}

//------------------------------------------------------.
// �E�g���K�[�擾.
//------------------------------------------------------.
BYTE CXInput::GetRightTrigger( const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return 0;	// �R���g���[���[�������Ȃ�I��.
	return GetInstance()->m_XinputState[connectNum].NowState.Gamepad.bRightTrigger;
}

//------------------------------------------------------.
// ���X�e�B�b�NX���擾.
//------------------------------------------------------.
SHORT CXInput::GetLeftThumbX( const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return 0;	// �R���g���[���[�������Ȃ�I��.
	return GetInstance()->m_XinputState[connectNum].NowState.Gamepad.sThumbLX;
}

//------------------------------------------------------.
// ���X�e�B�b�NY���擾.
//------------------------------------------------------.
SHORT CXInput::GetLeftThumbY( const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return 0;	// �R���g���[���[�������Ȃ�I��.
	return GetInstance()->m_XinputState[connectNum].NowState.Gamepad.sThumbLY;
}

//------------------------------------------------------.
// �E�X�e�B�b�NX���擾.
//------------------------------------------------------.
SHORT CXInput::GetRightThumbX( const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return 0;	// �R���g���[���[�������Ȃ�I��.
	return GetInstance()->m_XinputState[connectNum].NowState.Gamepad.sThumbRX;
}

//------------------------------------------------------.
// �E�X�e�B�b�NY���擾.
//------------------------------------------------------.
SHORT CXInput::GetRightThumbY( const UCHAR& connectNum ) 
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return 0;	// �R���g���[���[�������Ȃ�I��.
	return GetInstance()->m_XinputState[connectNum].NowState.Gamepad.sThumbRY;
}

//------------------------------------------------------.
// �o�C�u���[�V�����̐ݒ�.
//------------------------------------------------------.
void CXInput::SetVibration( const WORD& rightMotorSpd, const WORD& leftMotorSpd, const float& time, const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return;	// �R���g���[���[�������Ȃ�I��.

	GetInstance()->m_XinputState[connectNum].Vibration.wRightMotorSpeed	= std::clamp<WORD>( rightMotorSpd, INPUT_VIBRATION_MIN, INPUT_VIBRATION_MAX );;
	GetInstance()->m_XinputState[connectNum].Vibration.wLeftMotorSpeed	= std::clamp<WORD>( leftMotorSpd, INPUT_VIBRATION_MIN, INPUT_VIBRATION_MAX );;
	GetInstance()->m_XinputState[connectNum].VibrationTimeRight	= time;
	GetInstance()->m_XinputState[connectNum].VibrationTimeLeft	= time;
}

//------------------------------------------------------.
// �E�̃o�C�u���[�V�����̐ݒ�.
//------------------------------------------------------.
void CXInput::SetRightVibration ( const WORD& motorSpd, const float& time, const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return;	// �R���g���[���[�������Ȃ�I��.

	GetInstance()->m_XinputState[connectNum].Vibration.wRightMotorSpeed	= std::clamp<WORD>( motorSpd, INPUT_VIBRATION_MIN, INPUT_VIBRATION_MAX );
	GetInstance()->m_XinputState[connectNum].VibrationTimeRight	= time;
}

//------------------------------------------------------.
// ���̃o�C�u���[�V�����̐ݒ�.
//------------------------------------------------------.
void CXInput::SetLeftVibration ( const WORD& motorSpd, const float& time, const UCHAR& connectNum )
{
	if( GetInstance()->ControllerValid( connectNum ) == false ) return;	// �R���g���[���[�������Ȃ�I��.

	GetInstance()->m_XinputState[connectNum].Vibration.wLeftMotorSpeed	= std::clamp<WORD>( motorSpd, INPUT_VIBRATION_MIN, INPUT_VIBRATION_MAX );
	GetInstance()->m_XinputState[connectNum].VibrationTimeLeft	= time;
}

//------------------------------------------------------.
// ��Ԃ̍X�V.
//------------------------------------------------------.
void CXInput::StateUpdate()
{
	DWORD result;	// �ڑ����.
	for( int i = 0; i < MAX_CONTROLLERS; i++ ){
		// ���݂̏�Ԃ�ۑ����V������Ԃ��擾����.
		m_XinputState[i].OldState = m_XinputState[i].NowState;
		result = XInputGetState( i, &m_XinputState[i].NowState );
		m_XinputState[i].Connected = result == ERROR_SUCCESS ? true : false;
	}
}

//------------------------------------------------------.
// �o�C�u���[�V�����̍X�V.
//------------------------------------------------------.
void CXInput::VibrationUpdate( const float& time )
{
	for( int i = 0; i < MAX_CONTROLLERS; i++ ){
		if( m_XinputState[i].Connected == false ) continue;

		// �o�ߎ��Ԃ����炷.
		m_XinputState[i].VibrationTimeRight	-= time;
		m_XinputState[i].VibrationTimeLeft	-= time;

		// �o�ߎ��Ԃ� 0.0f ��肿�������Ȃ��.
		//	�o�C�u���[�V�������~�߂�.
		if( m_XinputState[i].VibrationTimeRight < 0.0f ){
			m_XinputState[i].VibrationTimeRight = 0.0f;
			m_XinputState[i].Vibration.wRightMotorSpeed = 0;
		}
		if( m_XinputState[i].VibrationTimeLeft < 0.0f ){
			m_XinputState[i].VibrationTimeLeft = 0.0f;
			m_XinputState[i].Vibration.wLeftMotorSpeed = 0;
		}
		// �o�C�u���[�V�����̒l�̐ݒ�.
		XInputSetState( i, &m_XinputState[i].Vibration );
	}
}

//------------------------------------------------------.
// �w�肵���R���g���[���[���L����.
//------------------------------------------------------.
bool CXInput::ControllerValid( const UCHAR& connectNum ) const
{
	if( connectNum > MAX_CONTROLLER_ARRAY_LEN )			return false;	// �ڑ��������l���傫����� false.
	if( m_XinputState[connectNum].Connected == false )	return false;	// �R���g�[���[���ڑ����ĂȂ���� false.

	return true;
}
