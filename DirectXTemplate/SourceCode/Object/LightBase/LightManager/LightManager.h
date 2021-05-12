#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "..\LightBase.h"
#include <queue>

class CNormalLight;

class CLightManager
{
public:
	CLightManager();
	~CLightManager();

	// �C���X�^���X�̎擾.
	static CLightManager* GetInstance();

	// �X�V�֐�.
	static void Update( const float& deltaTime );

	// ���W�̎擾.
	static D3DXVECTOR3 GetPosition(){ return GetInstance()->m_pLight->GetPosition(); }
	// ���_���W�̎擾.
	static D3DXVECTOR3 GetLookPosition(){ return GetInstance()->m_pLight->GetLookPosition(); }
	// �������擾.
	static D3DXVECTOR3 GetDirection(){ return GetInstance()->m_pLight->GetDirection(); }
	// �F���擾.
	static D3DXVECTOR3 GetColor(){ return GetInstance()->m_pLight->GetColor(); }
	// �������擾.
	static float GetIntensity(){ return GetInstance()->m_pLight->GetIntensity(); }

	// ���C�g�L���[�̎擾.
	static std::queue<SLightState> GetLightStateQueue(){ return GetInstance()->m_LightStateQueue; }
	// ���C�g�L���[�ɒǉ�.
	static void PushLightStateQueue( const SLightState& lightState ){ return GetInstance()->m_LightStateQueue.push(lightState); }
	static void LightStateQueueClear()
	{
		// �]�����L���[�̌�Еt��.
		const int queueSize = static_cast<int>(GetInstance()->m_LightStateQueue.size());
		for( int i = 0; i < queueSize; i++ ){
			GetInstance()->m_LightStateQueue.pop();
		}
	}
	// �ʒu�̕`��.
	static void PositionRender();

private:
	CLightBase*						m_pLight;
	std::unique_ptr<CNormalLight>	m_pNormalLight;
	std::queue<SLightState>			m_LightStateQueue;
#ifdef _DEBUG
	CDX9StaticMesh* m_StaticMesh;
#endif // #ifdef _DEBUG.

private:
	// �R�s�[�E���[�u�R���X�g���N�^, ������Z�q�̍폜.
	CLightManager( const CLightManager & )				= delete;
	CLightManager& operator = ( const CLightManager & )	= delete;
	CLightManager( CLightManager && )					= delete;
	CLightManager& operator = ( CLightManager && )		= delete;
};

#endif	// #ifndef LIGHT_MANAGER_H.