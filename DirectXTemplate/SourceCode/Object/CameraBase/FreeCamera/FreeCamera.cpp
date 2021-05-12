#include "FreeCamera.h"
#include "..\..\..\Utility\Input\Input.h"

namespace
{
	const float CAMERA_MOVE_SPEED				= 8.0f;		// �J�����̈ړ����x.
	const float CAMERA_POS_CAMERA_LOOK_DISTANCE = 15.0f;	// �J�����Ǝ��_�̋���.
	const float MOUSE_MOVE_SPEED				= 2.0f;		// �}�E�X�̈ړ����x.
	const float CONTROLLER_MOVE_SPEED			= 2.0f;		// �R���g���[���[�̈ړ����x.
	const float RADIAN_THRESHOLD_X_MAX			= 360.0f;	// ���W�A��X�̍ő債�����l.
	const float RADIAN_THRESHOLD_X_MIN			= 0.0f;		// ���W�A��X�̍ŏ��������l.
	const float RADIAN_THRESHOLD_Y_MAX			= 90.0f;	// ���W�A��Y�̍ő債�����l.
	const float RADIAN_THRESHOLD_Y_MIN			= -90.0f;	// ���W�A��Y�̍ŏ��������l.
	const D3DXVECTOR3	INIT_POSITION			= { 0.0f, 10.0f, -30.0f };	// �������W.
}

CFreeCamera::CFreeCamera()
	: m_Radian		( 0.0f, 0.0f )
	, m_DeltaTime	( 0.0f )
{
}

CFreeCamera::~CFreeCamera()
{
}

//------------------------------.
// �X�V�֐�.
//------------------------------.
void CFreeCamera::Update( const float& deltaTime )
{
	if( CKeyInput::IsHold(VK_LCONTROL) == false ) return;

	m_DeltaTime = deltaTime;

	D3DXMATRIX mRot;
	D3DXMatrixRotationYawPitchRoll( &mRot, m_Radian.x, 0.0f, 0.0f );
	// ���x�N�g����p��.
	D3DXVECTOR3 vecAxisX( CAMERA_MOVE_SPEED, 0.0f, 0.0f );	// X��.
	D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, CAMERA_MOVE_SPEED );	// Z��.
	// X���x�N�g�����̂��̂���]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord( &vecAxisX, &vecAxisX, &mRot );
	// Z���x�N�g�����̂��̂���]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord( &vecAxisZ, &vecAxisZ, &mRot );

	// �O�i.
	if( CKeyInput::IsHold('W') == true || CXInput::GetLeftThumbY() > IDLE_THUMB_MAX )
		m_Tranceform.Position += vecAxisZ * m_DeltaTime;
	// ���.
	if( CKeyInput::IsHold('S') == true || CXInput::GetLeftThumbY() < IDLE_THUMB_MIN )
		m_Tranceform.Position -= vecAxisZ * m_DeltaTime;
	// �E�Ɉړ�.
	if( CKeyInput::IsHold('D') == true || CXInput::GetLeftThumbX() > IDLE_THUMB_MAX )
		m_Tranceform.Position += vecAxisX * m_DeltaTime;
	// ���Ɉړ�.
	if( CKeyInput::IsHold('A') == true || CXInput::GetLeftThumbX() < IDLE_THUMB_MIN )
		m_Tranceform.Position -= vecAxisX * m_DeltaTime;
	// �㏸.
	if( CKeyInput::IsHold('E') == true || CXInput::GetRightTrigger() > IDLE_TIGGER_MAX ) 
		m_Tranceform.Position.y += CAMERA_MOVE_SPEED * m_DeltaTime;
	// ���~.
	if( CKeyInput::IsHold('Q') == true || CXInput::GetLeftTrigger() > IDLE_TIGGER_MAX )
		m_Tranceform.Position.y -= CAMERA_MOVE_SPEED * m_DeltaTime;

	MouseUpdate();

	// �����ʒu���Z�o.
	m_LookPosition.x = m_Tranceform.Position.x + ( sinf(m_Radian.x) * CAMERA_POS_CAMERA_LOOK_DISTANCE );
	m_LookPosition.y = m_Tranceform.Position.y + ( sinf(m_Radian.y) * CAMERA_POS_CAMERA_LOOK_DISTANCE );
	m_LookPosition.z = m_Tranceform.Position.z + ( cosf(m_Radian.x) * CAMERA_POS_CAMERA_LOOK_DISTANCE );
}

//------------------------------.
// �}�E�X�̍X�V.
//------------------------------.
void CFreeCamera::MouseUpdate()
{
	float xSub = 0.0f;
	float ySub = 0.0f;
	float moveSpeed = MOUSE_MOVE_SPEED * m_DeltaTime;
	if( CXInput::GetRightThumbY() > IDLE_THUMB_MAX )	ySub = -static_cast<float>(CXInput::GetRightThumbY());
	if( CXInput::GetRightThumbY() < IDLE_THUMB_MIN )	ySub = -static_cast<float>(CXInput::GetRightThumbY());
	if( CXInput::GetRightThumbX() > IDLE_THUMB_MAX )	xSub =  static_cast<float>(CXInput::GetRightThumbX());
	if( CXInput::GetRightThumbX() < IDLE_THUMB_MIN )	xSub =  static_cast<float>(CXInput::GetRightThumbX());
	if( CKeyInput::IsPress(VK_LBUTTON) == false ){
		moveSpeed = CONTROLLER_MOVE_SPEED * m_DeltaTime;	// �ړ����x�𔼕��ɂ���.
	} else {
		// �}�E�X����ʊO�Ȃ�I��.
		if( CInput::IsScreenMiddleMouse() == false ) return;
		// �}�E�X�̌��݂̍��W�Ɖߋ��̍��W���������l���Z�o.
		if( ySub == 0.0f ) ySub = CInput::GetMousePosisionY() - CInput::GetMouseOldPosisionY();
		if( xSub == 0.0f ) xSub = CInput::GetMousePosisionX() - CInput::GetMouseOldPosisionX();
	}


	if( xSub < 0.0f ) m_Radian.x -= moveSpeed;
	if( xSub > 0.0f ) m_Radian.x += moveSpeed;
	if( ySub > 0.0f ) m_Radian.y -= moveSpeed;
	if( ySub < 0.0f ) m_Radian.y += moveSpeed;
	// �K��l�𒴂��Ȃ��悤����.
	if( m_Radian.x > static_cast<float>(D3DXToRadian(RADIAN_THRESHOLD_X_MAX)) )
		m_Radian.x = static_cast<float>(D3DXToRadian(RADIAN_THRESHOLD_X_MIN));
	if( m_Radian.x < static_cast<float>(D3DXToRadian(RADIAN_THRESHOLD_X_MIN)) ) 
		m_Radian.x = static_cast<float>(D3DXToRadian(RADIAN_THRESHOLD_X_MAX));
	if( m_Radian.y > static_cast<float>(D3DXToRadian(RADIAN_THRESHOLD_Y_MAX)) )
		m_Radian.y = static_cast<float>(D3DXToRadian(RADIAN_THRESHOLD_Y_MAX));
	if( m_Radian.y < static_cast<float>(D3DXToRadian(RADIAN_THRESHOLD_Y_MIN)) )
		m_Radian.y = static_cast<float>(D3DXToRadian(RADIAN_THRESHOLD_Y_MIN));
}