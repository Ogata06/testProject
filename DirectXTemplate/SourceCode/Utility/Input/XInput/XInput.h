#ifndef XINPUT_H
#define XINPUT_H

#include <Windows.h>
#include <XInput.h>
#include <vector>
#include <unordered_map>
#include <memory>

#pragma comment( lib, "xinput.lib" )

struct stXInputState
{
	XINPUT_STATE		NowState;			// ���݂�Xinput�̏��.
	XINPUT_STATE		OldState;			// �O���Xinput�̏��.
	XINPUT_VIBRATION	Vibration;			// Xinput�̃o�C�u���[�V�����̏��.
	float				VibrationTimeRight;	// ���̃o�C�u���[�V�����̌v������.
	float				VibrationTimeLeft;	// ���̃o�C�u���[�V�����̌v������.	
	bool				Connected;			// �ڑ����Ă��邩.

	stXInputState()
		: NowState				()
		, OldState				()
		, Vibration				()
		, VibrationTimeRight	( 0.0f )
		, VibrationTimeLeft		( 0.0f )
		, Connected				( false )
	{}

} typedef SXInputState;


const UCHAR MAX_CONTROLLERS				= 4;					// �R���g���[���[�̍ő�ڑ���.
const UCHAR MAX_CONTROLLER_ARRAY_LEN	= MAX_CONTROLLERS-1;	// �R���g���[���[�̔z��̍ő吔.
const SHORT	IDLE_THUMB_MAX				=  10000;				// �X�e�B�b�N�̗V��.
const SHORT	IDLE_THUMB_MIN				= -10000;				// �X�e�B�b�N�̗V��.
const BYTE	IDLE_TIGGER_MAX				=  100;					// �g���K�[�{�^���̗V��.
const WORD	INPUT_VIBRATION_MIN			=  0;					// �o�C�u���[�V�����̍ŏ��l.
const WORD	INPUT_VIBRATION_MAX			=  65535;				// �o�C�u���[�V�����̍ő�l.

class CXInput
{
public:
	CXInput();
	~CXInput();

	// �X�V.
	static void Update( const float& time );

	// ������Ă���Ƃ�.
	static bool IsPress			( const WORD& buttonMask, const UCHAR& connectNum = 0 );
	// �������u��.
	static bool IsMomentPress	( const WORD& buttonMask, const UCHAR& connectNum = 0 );
	// ���������Ă���Ƃ�.
	static bool IsHold			( const WORD& buttonMask, const UCHAR& connectNum = 0 );
	// �������u��.
	static bool IsRelease		( const WORD& buttonMask, const UCHAR& connectNum = 0 );

	// ���g���K�[�擾.
	static BYTE GetLeftTrigger	( const UCHAR& connectNum = 0 );
	// �E�g���K�[�擾.
	static BYTE GetRightTrigger	( const UCHAR& connectNum = 0 );

	// ���X�e�B�b�NX���擾.
	static SHORT GetLeftThumbX	( const UCHAR& connectNum = 0 );
	// ���X�e�B�b�NY���擾.
	static SHORT GetLeftThumbY	( const UCHAR& connectNum = 0 );

	// �E�X�e�B�b�NX���擾.
	static SHORT GetRightThumbX	( const UCHAR& connectNum = 0 );
	// �E�X�e�B�b�NY���擾.
	static SHORT GetRightThumbY	( const UCHAR& connectNum = 0 );

	// �o�C�u���[�V�����̐ݒ�.
	static void SetVibration		( const WORD& rightMotorSpd, const WORD& leftMotorSpd, const float& time, const UCHAR& connectNum = 0 );
	// �E�̃o�C�u���[�V�����̐ݒ�.
	static void SetRightVibration	( const WORD& motorSpd, const float& time, const UCHAR& connectNum = 0 );
	// ���̃o�C�u���[�V�����̐ݒ�.
	static void SetLeftVibration	( const WORD& motorSpd, const float& time, const UCHAR& connectNum = 0 );

private:
	// ��Ԃ̍X�V.
	void StateUpdate();
	// �o�C�u���[�V�����̍X�V.
	void VibrationUpdate( const float& time );

	// �w�肵���R���g���[���[���L����.
	bool ControllerValid( const UCHAR& connectNum ) const;

	static CXInput* GetInstance()
	{
		static std::unique_ptr<CXInput> pInstance = std::make_unique<CXInput>();
		return pInstance.get();
	}

private:
	SXInputState	m_XinputState[MAX_CONTROLLERS];	// �R�����[���[�̐ڑ����.
	
private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CXInput( const CXInput & )				= delete;
	CXInput( CXInput && )					= delete;
	CXInput& operator = ( const CXInput & )	= delete;
	CXInput& operator = ( CXInput && )		= delete;
};


#endif	// #ifndef XINPUT_H.