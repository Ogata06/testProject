#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>
#include <functional>
#include <memory>
#include <Windows.h>

#include "InputEnums.h"
#include "XInput/XInput.h"
#include "KeyInput/KeyInput.h"
#include "..\..\Global.h"

// ���͎��̖����͈�.
inline static const float	INPUT_AXIS_DEAD_ZONE = 0.4f;
// ���͎���n��l.
// �R���g���[���[����󂯎�����l��n�悷���.
// �l�����炩�ɂȂ�.
// https://hexadrive.jp/lab/tips/976/.
inline static const int		INPUT_AXIS_POW_VALUE = 3;

class CInput
{
public:
	// �L�[�o�C���h�̃y�A�\����.
	struct stKeyBindPair
	{
		const unsigned char	Key;	// �L�[�ԍ�.
		const WORD			Button;	// Xinput�̃{�^���ԍ�.

		stKeyBindPair()
			: stKeyBindPair	( 0, 0 )
		{}
		stKeyBindPair(
			const unsigned char&	k,
			const WORD&				b )
			: Key		( k )
			, Button	( b )
		{}

	};

	// ���o�C���h.
	struct stAxisBind
	{
		const unsigned char	MinusKey;	// �}�C�i�X�����Ŏ󂯎��L�[�ԍ�.
		const unsigned char	PlusKey;	// �v���X�����Ŏ󂯎��L�[�ԍ�.

		const std::function<SHORT()> GetValue;// �R���g���[���̎��l�̎擾�֐�.

		const float MinValue;	// �L�[�Ŏ󂯎��ۂ̍ŏ��l.
		const float MaxValue;	// �L�[�Ŏ󂯎��ۂ̍ő�l.

		stAxisBind() : stAxisBind	( 0, 0, [](){ return 0; }, 0.0f, 0.0f ){}
		stAxisBind(
			const unsigned char& mk,
			const unsigned char& pk,
			const std::function<SHORT()>& func,
			const float& minValue,
			const float& maxValue )
			: MinusKey	( mk )
			, PlusKey	( pk )
			, GetValue	( func )
			, MinValue	( minValue )
			, MaxValue	( maxValue )
		{}
	};

	struct Vector2
	{
		float x;
		float y;
		float length;

		Vector2() : x (0), y (0), length (0){}
	};

	using SKeyBindPair	= stKeyBindPair;
	using SAxisBind		= stAxisBind;
public:
	CInput();
	~CInput();

	// �E�B���h�E�n���h���̐ݒ�.
	static void SetHWND( HWND hWnd ){ GetInstance()->m_hWnd = hWnd; }

	// �o�C���h�̏�����.
	static void InitBind();
	// �o�C���h�̏����� : �O������ݒ�p.
	static void InitBind(
		std::function<void(std::unordered_map<EKeyBind, SKeyBindPair>&)>	keyFunc,
		std::function<void(std::unordered_map<EAxisBind, SAxisBind>&)>		axisFunc );

	// �L�[�o�C���h�̏�����.
	static void InitKeyBind();
	// ���o�C���h�̏�����.
	static void InitAxisBind();
	// �L�[�o�C���h�̏����� : �O������ݒ�p.
	// �ȉ��g�p��.
	/*
		CInput::InitKeyBind( []( std::unordered_map<EKeyBind, CInput::SKeyBindPair>& list )
		{
			list =
			{
				�L�[�o�C���h�񋓑�,		�ݒ肷��L�[�A�Q�[���p�b�h�̃{�^���̐ݒ�.
				{ EKeyBind::Decision,	CInput::SKeyBindPair( VK_RETURN,	XINPUT_GAMEPAD_B )	},
				{ EKeyBind::Cancel,		CInput::SKeyBindPair( VK_BACK,		XINPUT_GAMEPAD_A )	},
			};
		};
	*/
	static void InitKeyBind( std::function<void(std::unordered_map<EKeyBind, SKeyBindPair>&)> func );
	// ���o�C���h�̏����� : �O������ݒ�p.
	// �ȉ��g�p��.
	/*
		CInput::InitAxisBind( []( std::unordered_map<EAxisBind, SAxisBind>& list )
		{
			list =
			{
				���o�C���h�̗񋓑�		�ݒ肷��L�[�A�󂯎�鎲�̊֐��A�󂯎��ŏ��l�A�ő�l.
				{ EAxisBind::L_Forward,	SAxisBind( 'S', 'W', [](){ return CXInput::LThumbY_Axis(); }, -1.0f, 1.0f ) },
				{ EAxisBind::L_Right,	SAxisBind( 'A', 'D', [](){ return CXInput::LThumbX_Axis(); }, -1.0f, 1.0f ) },
			};
		};
	*/
	static void InitAxisBind( std::function<void(std::unordered_map<EAxisBind, SAxisBind>&)> func );

	// ���͏�Ԃ̍X�V.
	static void Update( const float& time );

	// ������Ă���Ƃ�.
	static bool IsPress( const EKeyBind& key );
	// �����ꂽ�u��.
	static bool IsMomentPress( const EKeyBind& key );
	// ���������Ă���Ƃ�.
	static bool IsHold( const EKeyBind& key );
	// �������u��.
	static bool IsRelease( const EKeyBind& key );
	// �����Ă��Ȃ�.
	static bool NotPress( const EKeyBind& key );

	// ���l�̎擾(vector2).
	static Vector2 GetAxisVector( const EAxisBind& key_x, const EAxisBind& key_y );
#ifdef	__D3DX9MATH_H__	//�uD3DX�`�v�n���Ă΂ꂢ��Έȉ��̊֐����g�p�ł���.
	// ���l�̎擾(D3DXVECTOR2).
	static D3DXVECTOR2 GetAxisDxVector( const EAxisBind& key_x, const EAxisBind& key_y );
#endif	// #ifdef __D3DX9MATH_H__

	// ���l�̎擾.
	static float GetAxisValue( const EAxisBind& key );

	//-----------------------------------------------.
	// �� �}�E�X�n ��
	//-----------------------------------------------.

	// ���W�̎擾.
	static POINT GetMousePosition()		{ return GetInstance()->m_MouseNowPoint; }
	// �O��̍��W�̎擾.
	static POINT GetMouseOldPosition()	{ return GetInstance()->m_MouseOldPoint; }
	// ���WX�̎擾.
	static float GetMousePosisionX()	{ return static_cast<float>(GetInstance()->m_MouseNowPoint.x); }
	// ���WY�̎擾.
	static float GetMousePosisionY()	{ return static_cast<float>(GetInstance()->m_MouseNowPoint.y); }
	// �O��̍��WX�̎擾.
	static float GetMouseOldPosisionX()	{ return static_cast<float>(GetInstance()->m_MouseOldPoint.x); }
	// �O��̍��WY�̎擾.
	static float GetMouseOldPosisionY()	{ return static_cast<float>(GetInstance()->m_MouseOldPoint.y); }

	// �}�E�X���X�N���[���̒���.
	static bool IsScreenMiddleMouse();

	// �}�E�X�z�C�[���̒l�̐ݒ�.
	static void SetMouseWheelDelta( const int& delta ){ GetInstance()->m_MouseWheel = delta; }
	// �}�E�X�z�C�[���̒l�̎擾.
	//	+ ������ւ̈ړ�.
	//	- �������ւ̈ړ�.
	static int GetMouseWheelDelta(){ return GetInstance()->m_MouseWheel; }

private:
	// �C���X�^���X�̎擾.
	static CInput* GetInstance();

	// �}�E�X�̍X�V.
	void UpdateMouse();

private:
	HWND										m_hWnd;				// �E�B���h�E�n���h��.
	std::unordered_map<EKeyBind, SKeyBindPair>	m_KeyBindList;		// KeyBindPair�̃��X�g.
	std::unordered_map<EAxisBind, SAxisBind>	m_AxisBindList;		// AxisBind�̃��X�g.
	POINT										m_MouseNowPoint;	// ���݂̃}�E�X���W.
	POINT										m_MouseOldPoint;	// �O��̃}�E�X���W.
	int											m_MouseWheel;		// �}�E�X�z�C�[���l.
private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CInput( const CInput & )				= delete;
	CInput( CInput && )						= delete;
	CInput& operator = ( const CInput & )	= delete;
	CInput& operator = ( CInput && )		= delete;
};

#endif	// #ifndef INPUT_H.