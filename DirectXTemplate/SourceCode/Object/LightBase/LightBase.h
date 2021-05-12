#ifndef LIGHT_BASE_H
#define LIGHT_BASE_H

#include "..\Object.h"

// ���C�g���.
struct stLightState
{
	static constexpr int NONE_LIGHT			= 0;	// ���C�g����.
	static constexpr int DIRECTIONAL_LIGHT	= 1;	// �f�B���N�V���i�����C�g.
	static constexpr int POINT_LIGHT		= 2;	// �|�C���g���C�g.
	static constexpr int SPOT_LIGHT			= 3;	// �X�|�b�g���C�g.

	D3DXVECTOR4 Position;	// ���W.
	D3DXVECTOR4 Vector;		// ����.
	D3DXVECTOR4 Color;		// �F w�������Ƃ��Ďg�p.
	D3DXVECTOR4 ConeAngle;	// �X�|�b�g���C�g�̃R�[���l.
	int Type;				// ���C�g�̎��.

	stLightState()
		: Position	( 0.0f, 0.0f, 0.0f, 0.0f )
		, Vector	( 0.0f, 0.0f, 0.0f, 0.0f )
		, Color		( 0.0f, 0.0f, 0.0f, 0.0f )
		, ConeAngle	( 0.0f, 0.0f, 0.0f, 0.0f )
		, Type		( NONE_LIGHT )
	{}

} typedef SLightState;

/*************************************************
*	���C�g�x�[�X�N���X.
**/
class CLightBase : public CObject
{
public:
	CLightBase();
	virtual ~CLightBase();

	// �X�V�֐�.
	virtual void Update( const float& deltaTime ) = 0;

	// �������W�̐ݒ�.
	inline void SetLookPosition( const D3DXVECTOR3& p ) { m_LookPosition = p; }
	// �������W�̎擾.
	inline D3DXVECTOR3	GetLookPosition()	const { return m_LookPosition; }
	// �������擾.
	inline D3DXVECTOR3	GetDirection()		const { return m_Direction; }
	// ���C�g�̐F���擾.
	inline D3DXVECTOR3	GetColor()			const { return m_Color; }
	// ���C�g�̋������擾.
	inline float		GetIntensity()		const { return m_Intensity; }

	// ���삵�Ă��邩
	inline bool			IsActive()			const { return m_IsActive; }

protected:
	// �V���v���Ȉړ�.
	void SimpleMove( const float& deltaTime );

protected:
	D3DXVECTOR3	m_LookPosition;	// ���_���W.
	D3DXVECTOR3	m_Direction;	// ���C�g����.
	D3DXVECTOR3	m_Color;		// ���C�g�̐F.
	float		m_Intensity;	// ���C�g�̋���.
	bool		m_IsActive;		// ���삵�Ă��邩.
};

#endif	// #ifndef LIGHT_BASE_H.