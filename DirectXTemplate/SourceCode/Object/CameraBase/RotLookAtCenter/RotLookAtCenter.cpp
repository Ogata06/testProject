#include "RotLookAtCenter.h"

CRotLookAtCenter::CRotLookAtCenter()
	: m_vDegree			{ 0.0f, 0.0f }
	, m_Length			( DEFAULT_LENGTH )
	, m_HorizontalMax	( DEFAULT_HORIZONTAL_MAX )
	, m_HorizontalMin	( DEFAULT_HORIZONTAL_MIN )
	, m_VerticalMax		( DEFAULT_VERTICAL_MAX )
	, m_VerticalMin		( DEFAULT_VERTICAL_MIN )
	, m_RightMoveSpeed	( DEFAULT_MOVE_SPEED )
	, m_LeftMoveSpeed	(-DEFAULT_MOVE_SPEED )
	, m_AddValue		( 0.0f, 0.0f, 0.0f )
{
}

CRotLookAtCenter::CRotLookAtCenter( const bool& isLoad )
	: CRotLookAtCenter	()
{
}

CRotLookAtCenter::~CRotLookAtCenter()
{
}

// �p�����[�^�[�̓ǂݍ���.
bool CRotLookAtCenter::LoadParameter( const bool& isLoad )
{
	return true;
}

// �X�V.
void CRotLookAtCenter::Update( const float& deltaTime )
{
	m_Tranceform.Position = { 10.0f, 10.0f, 10.0f };
}

//-------------------------------.
// �I�u�W�F�N�g���𒍎��ɉ�].
//-------------------------------.
void CRotLookAtCenter::RotationLookAtObject( const D3DXVECTOR3& vLookPos, const float& attenRate )
{
	// �����ʒu���擾.
	m_LookPosition = vLookPos;

	D3DXVECTOR3 pos;	// �{���̍��W.
	// �J�����ʒu���Z�o.
	pos.x = m_LookPosition.x + ( sinf(m_vDegree.x) * m_Length );
	pos.y = m_Tranceform.Position.y;
	pos.z = m_LookPosition.z + ( cosf(m_vDegree.x) * m_Length );
	// lerp����. ( out, ���݂̍��W, �{�����B���Ă�����W, �␳�l ).
	D3DXVec3Lerp( &m_Tranceform.Position, &m_Tranceform.Position, &pos, attenRate );
	m_Tranceform.Position += m_AddValue;
	m_AddValue = { 0.0f, 0.0f, 0.0f };
}

//-------------------------------.
// �������̉�].
//-------------------------------.
void CRotLookAtCenter::DegreeHorizontalMove( const float& movePower )
{
	// �������ɑ������킹��.
	m_vDegree.x += movePower;
}

//-------------------------------.
// �������̉E��].
//-------------------------------.
void CRotLookAtCenter::DegreeHorizontalRightMove()
{
	DegreeHorizontalMove( m_RightMoveSpeed );
}

//-------------------------------.
// �������̍���].
//-------------------------------.
void CRotLookAtCenter::DegreeHorizontalLeftMove()
{
	DegreeHorizontalMove( m_LeftMoveSpeed );
}

//-------------------------------.
// �c�����̉�].
//-------------------------------.
void CRotLookAtCenter::DegreeVerticalMove( const float& movePower )
{
	// �c�����ɑ������킹��.
	m_vDegree.y += movePower;
}

//-------------------------------.
// �J�����ƒ����_�̒����ݒ�.
//-------------------------------.
void CRotLookAtCenter::SetLength( const float& length )
{
	m_Length = length;
}

//-------------------------------.
// �����̐ݒ�.
//-------------------------------.
void CRotLookAtCenter::SetHeight( const float& height )
{
	m_Tranceform.Position.y = height;
}

//-------------------------------.
// �������̍ő�A�ŏ��̐ݒ�.
//-------------------------------.
void CRotLookAtCenter::SetHorizontalDegree( const float& max, const float& min )
{
	m_HorizontalMax	= max;
	m_HorizontalMin	= min;
}

//-------------------------------.
// �c�����̍ő�A�ŏ��̐ݒ�.
//-------------------------------.
void CRotLookAtCenter::SetVerticalDegree( const float& max, const float& min )
{	
	m_VerticalMax = max;
	m_VerticalMin = min;
}

//-------------------------------.
// ���W�ɑ������킹��l�̐ݒ�.
//-------------------------------.
void CRotLookAtCenter::SetAddPositionValue( const D3DXVECTOR3& addValue )
{
	m_AddValue = addValue;
}