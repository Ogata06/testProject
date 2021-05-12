#include "CollisionManager.h"
#include "..\Sphere\Sphere.h"
#include "..\Capsule\Capsule.h"
#include "..\Box\Box.h"
#include "..\Ray\Ray.h"

namespace coll
{

	//---------------------------------------.
	// ���̓��m�̓����蔻��.
	//---------------------------------------.
	bool IsSphereToSphere( CSphere* pMySphere, CSphere* pOppSphere )
	{
		// �X�t�B�A�� nullptr �Ȃ�I��.
		if( pMySphere	== nullptr ) return false;
		if( pOppSphere	== nullptr ) return false;

		// ���a�� 0 �ȉ��Ȃ�I��.
		if( pMySphere->GetRadius()	<= 0.0f ) return false;
		if( pOppSphere->GetRadius()	<= 0.0f ) return false;

		// ��_�Ԃ̋������擾.
		const float length = D3DXVec3Length( &(pMySphere->GetPosition() - pOppSphere->GetPosition()) );
		// ���݂��̔��a�̍��v���擾.
		const float totalRadius = pMySphere->GetRadius() + pOppSphere->GetRadius();

		// 2�_�Ԃ̋�����2�̔��a�̍��v���傫���̂�.
		if( length > totalRadius ){
			// �Փ˂��Ă��Ȃ�.
			pMySphere->SetHitOff();
			pOppSphere->SetHitOff();
			return false;
		}

		// �Փ˂��Ă���.
		pMySphere->SetHitOn();
		pOppSphere->SetHitOn();

		return true;
	}

	//---------------------------------------.
	// �J�v�Z�����m�̓����蔻��.
	//---------------------------------------.
	bool IsCapsuleToCapsule( CCapsule* pMyCapsule, CCapsule* pOppCapsule )
	{
		if( pMyCapsule	== nullptr ) return false;
		if( pOppCapsule	== nullptr ) return false;

		// ���a�� 0 �ȉ��Ȃ�I��.
		if( pMyCapsule->GetRadius()	<= 0.0f ) return false;
		if( pOppCapsule->GetRadius()<= 0.0f ) return false;

		SSegment mySeg	= pMyCapsule->GetSegment();
		SSegment oppSeg	= pOppCapsule->GetSegment();

		float d = CalcSegmentSegmentDist( mySeg, oppSeg );
		if( d >= pMyCapsule->GetRadius()+pOppCapsule->GetRadius() ){
			// �Փ˂��Ă��Ȃ�.
			pMyCapsule->SetHitOff();
			pOppCapsule->SetHitOff();
			return false;
		}

		// �Փ˂��Ă���.
		pMyCapsule->SetHitOn();
		pOppCapsule->SetHitOn();

		return true;
	}

	//---------------------------------------.
	// �{�b�N�X���m�̓����蔻��.
	//---------------------------------------.
	bool IsOBBToOBB( CBox* pMyBox, CBox* pOppBox )
	{
		if( pMyBox	== nullptr ) return false;
		if( pOppBox	== nullptr ) return false;

		auto LenSegOnSeparateAxis = []( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0 )
		{
			// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z.
			// ������Sep�͕W��������Ă��邱��.
			FLOAT r1 = fabs(D3DXVec3Dot( Sep, e1 ));
			FLOAT r2 = fabs(D3DXVec3Dot( Sep, e2 ));
			FLOAT r3 = e3 ? (fabs(D3DXVec3Dot( Sep, e3 ))) : 0;
			return r1 + r2 + r3;
		};

		// �e�����x�N�g���̊m��.
		// �iN***:�W���������x�N�g���j.
		D3DXVECTOR3 NAe1 = pMyBox->GetDirection(0), Ae1 = NAe1 * pMyBox->GetScale().x;
		D3DXVECTOR3 NAe2 = pMyBox->GetDirection(1), Ae2 = NAe2 * pMyBox->GetScale().y;
		D3DXVECTOR3 NAe3 = pMyBox->GetDirection(2), Ae3 = NAe3 * pMyBox->GetScale().z;
		D3DXVECTOR3 NBe1 = pOppBox->GetDirection(0), Be1 = NBe1 * pOppBox->GetScale().x;
		D3DXVECTOR3 NBe2 = pOppBox->GetDirection(1), Be2 = NBe2 * pOppBox->GetScale().y;
		D3DXVECTOR3 NBe3 = pOppBox->GetDirection(2), Be3 = NBe3 * pOppBox->GetScale().z;
		D3DXVECTOR3 Interval = pMyBox->GetPosition() - pOppBox->GetPosition();

		FLOAT rA, rB, L;
		auto isHitLength = [&](
		const D3DXVECTOR3& e, 
		D3DXVECTOR3 Ne,
		D3DXVECTOR3 e1, D3DXVECTOR3 e2, D3DXVECTOR3 e3 )
		{
			rA = D3DXVec3Length( &e );
			rB = LenSegOnSeparateAxis( &Ne, &e1, &e2, &e3 );
			L = fabs(D3DXVec3Dot( &Interval, &Ne ));
			if( L > rA + rB ){
				// �Փ˂��Ă��Ȃ�.
				pMyBox->SetHitOff();
				pOppBox->SetHitOff();
				return false; // �Փ˂��Ă��Ȃ�.
			}
			return true;
		};

		auto isHitCross = [&]( 
			const D3DXVECTOR3& NAe, const D3DXVECTOR3& NBe, 
			D3DXVECTOR3 Ae1, D3DXVECTOR3 Ae2,
			D3DXVECTOR3 Be1, D3DXVECTOR3 Be2 )
		{
			D3DXVECTOR3 Cross;
			D3DXVec3Cross( &Cross, &NAe, &NBe );
			rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
			rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
			L = fabs(D3DXVec3Dot( &Interval, &Cross ));
			if( L > rA + rB ){
				// �Փ˂��Ă��Ȃ�.
				pMyBox->SetHitOff();
				pOppBox->SetHitOff();
				return false; // �Փ˂��Ă��Ȃ�.
			}
			return true;
		};

		// ������ : Ae.
		if( isHitLength( Ae1, NAe1, Be1, Be2, Be3 ) == false ) return false;
		if( isHitLength( Ae2, NAe2, Be1, Be2, Be3 ) == false ) return false;
		if( isHitLength( Ae3, NAe3, Be1, Be2, Be3 ) == false ) return false;
		// ������ : Be.
		if( isHitLength( Be1, NBe1, Ae1, Ae2, Ae3 ) == false ) return false;
		if( isHitLength( Be2, NBe2, Ae1, Ae2, Ae3 ) == false ) return false;
		if( isHitLength( Be3, NBe3, Ae1, Ae2, Ae3 ) == false ) return false;

		// ������ : C1.
		if( isHitCross( NAe1, NBe1, Ae2, Ae3, Be2, Be3 ) == false ) return false;
		if( isHitCross( NAe1, NBe2, Ae2, Ae3, Be1, Be3 ) == false ) return false;
		if( isHitCross( NAe1, NBe3, Ae2, Ae3, Be1, Be2 ) == false ) return false;
		// ������ : C2.
		if( isHitCross( NAe2, NBe1, Ae1, Ae3, Be2, Be3 ) == false ) return false;
		if( isHitCross( NAe2, NBe2, Ae1, Ae3, Be1, Be3 ) == false ) return false;
		if( isHitCross( NAe2, NBe3, Ae1, Ae3, Be1, Be2 ) == false ) return false;
		// ������ : C3.
		if( isHitCross( NAe3, NBe1, Ae1, Ae2, Be2, Be3 ) == false ) return false;
		if( isHitCross( NAe3, NBe2, Ae1, Ae2, Be1, Be3 ) == false ) return false;
		if( isHitCross( NAe3, NBe3, Ae1, Ae2, Be1, Be2 ) == false ) return false;

		// �Փ˂��Ă���.
		pMyBox->SetHitOn();
		pOppBox->SetHitOn();

		return true;
	}

	//---------------------------------------.
	// ���C�Ƌ��̂̓����蔻��.
	//---------------------------------------.
	bool IsRayToSphere( CRay* pRay, CSphere* pSphere, D3DXVECTOR3* pOutStartPos, D3DXVECTOR3* pOutEndPos )
	{
		if( pRay	== nullptr ) return false;
		if( pSphere	== nullptr ) return false;

		const D3DXVECTOR3 v = pRay->GetVector();
		const D3DXVECTOR3 l = pRay->GetStartPos();
		const D3DXVECTOR3 p = pSphere->GetPosition() - l;
		const float A = v.x * v.x + v.y * v.y + v.z * v.z;
		const float B = v.x * p.x + v.y * p.y + v.z * p.z;
		const float C = p.x * p.x + p.y * p.y + p.z * p.z - pSphere->GetRadius()*pSphere->GetRadius();

		// �x�N�g���̒������Ȃ���ΏI��.
		if( A == 0.0f ){
			pRay->SetHitOff();
			pSphere->SetHitOff();
			return false;
		}
		const float s = B * B - A * C;
		const float sq = sqrtf(s);
		const float a1 = ( B - sq ) / A;
		const float a2 = ( B + sq ) / A;

		// ���C�̊J�n�ʒu�Ƌ��̂̋�����.
		//	���̂̔��a��菬������ΏՓ˂��Ă���.
		if( D3DXVec3Length( &p ) <= pSphere->GetRadius() ){
			*pOutStartPos = pRay->GetStartPos();

			pOutEndPos->x = l.x + a2 * v.x;
			pOutEndPos->y = l.y + a2 * v.y;
			pOutEndPos->z = l.z + a2 * v.z;

			pRay->SetHitOn();
			pSphere->SetHitOn();
			return true;
		}

		if( s < 0.0f ){
			pRay->SetHitOff();
			pSphere->SetHitOff();
			return false;
		}

		if( a1 < 0.0f || a2 < 0.0f ){
			pRay->SetHitOff();
			pSphere->SetHitOff();
			return false;
		}

		pRay->SetHitOn();
		pSphere->SetHitOn();

		if( pOutStartPos == nullptr ) return true;
		pOutStartPos->x = l.x + a1 * v.x;
		pOutStartPos->y = l.y + a1 * v.y;
		pOutStartPos->z = l.z + a1 * v.z;

		if( pOutEndPos == nullptr ) return true;
		pOutEndPos->x = l.x + a2 * v.x;
		pOutEndPos->y = l.y + a2 * v.y;
		pOutEndPos->z = l.z + a2 * v.z;

		return true;
	}
};