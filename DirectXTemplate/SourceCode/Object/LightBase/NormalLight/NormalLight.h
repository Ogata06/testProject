#ifndef NORMAL_LIGHT_H
#define NORMAL_LIGHT_H

#include "..\LightBase.h"

/******************************************
*	 �ʏ탉�C�g.
**/
class CNormalLight : public CLightBase
{
public:
	CNormalLight();
	virtual ~CNormalLight();

	// �X�V�֐�.
	virtual void Update( const float& deltaTime ) override;
};

#endif	// #ifndef NORMAL_LIGHT_H.