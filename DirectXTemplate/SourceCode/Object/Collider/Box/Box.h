/**
* @file Box.h.
* @brief �{�b�N�X�N���X.
* @author ���c���.
*/
#ifndef BOX_H
#define BOX_H

#include "..\ColliderBase.h"

/*****************************************
*	�{�b�N�X�N���X.
**/
class CBox : public CColliderBase
{
public:
	CBox();
	virtual ~CBox();

	// �����x�N�g���̎擾.
	D3DXVECTOR3 GetDirection( const int& index );
};

#endif	// #ifndef BOX_H.