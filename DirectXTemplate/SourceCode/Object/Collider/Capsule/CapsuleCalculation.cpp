#include "CapsuleCalculation.h"
#include <algorithm>

namespace
{
	constexpr float OX_EPSILON = 0.000001f;
};


//----------------------------------.
// ��p1p2p3�͉s�p�H.
//----------------------------------.
bool IsSharpAngle( const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, const D3DXVECTOR3& p3 )
{
	D3DXVECTOR3 vec1 = p1 - p2;
	D3DXVECTOR3 vec2 = p3 - p2;
	return D3DXVec3Dot( &vec1, &vec2 ) >= 0.0f;
}

//----------------------------------.
// ���s���ǂ���.
//----------------------------------.
bool IsParallel( const D3DXVECTOR3& v1, const D3DXVECTOR3& v2 )
{
	D3DXVECTOR3 crossVec;
	D3DXVec3Cross( &crossVec, &v1, &v2 );
	float d = D3DXVec3LengthSq( &crossVec );

	// �덷�͈̔͂Ȃ��Ȃ畽�s.
	return ( - OX_EPSILON < d && d < OX_EPSILON );
};

//----------------------------------.
// 2�����̍ŒZ����.
//----------------------------------.
float CalcLineLineDist( const SLine& l1, const SLine& l2, D3DXVECTOR3& p1, D3DXVECTOR3& p2, float& t1, float& t2 )
{
	// 2���������s�H
	if( IsParallel( l1.Vector, l2.Vector ) == true ){

		// �_P11�ƒ���L2�̍ŒZ�����̖��ɋA��
		float len = CalcPointLineDist( l1.Point, l2, p2, t2 );
		p1 = l1.Point;
		t1 = 0.0f;

		return len;
	}
	
	// 2�����͂˂���֌W
	float DV1V2 = D3DXVec3Dot( &l1.Vector, &l2.Vector );
	float DV1V1 = D3DXVec3LengthSq( &l1.Vector );
	float DV2V2 = D3DXVec3LengthSq( &l2.Vector );
	D3DXVECTOR3 P21P11 = l1.Point - l2.Point;
	t1 = ( DV1V2 * D3DXVec3Dot( &l2.Vector, &P21P11 ) - 
		DV2V2 * D3DXVec3Dot( &l1.Vector, &P21P11 ) ) / 
		( DV1V1 * DV2V2 - DV1V2 * DV1V2 );
	p1 = l1.GetPoint( t1 );
	t2 = D3DXVec3Dot( &l2.Vector, &( p1 - l2.Point )) / DV2V2;
	p2 = l2.GetPoint( t2 );

	return D3DXVec3Length( &( p2 - p1 ) );
}

//----------------------------------.
// �_�ƒ����̍ŒZ����.
//----------------------------------.
float CalcPointLineDist( const D3DXVECTOR3& p, const SLine& l, D3DXVECTOR3& h, float& t )
{
	float lenSqV = D3DXVec3LengthSq( &l.Vector );
	t = 0.0f;
	if ( lenSqV > 0.0f ){
		t = D3DXVec3Dot( &l.Vector, &(p - l.Point) ) / lenSqV;
	}

	h = l.Point + t * l.Vector;
	return D3DXVec3Length( &(h - p) );
}

//----------------------------------.
// �_�Ɛ����̍ŒZ����.
//----------------------------------.
float CalcPointSegmentDist( const D3DXVECTOR3& p, const SSegment& seg, D3DXVECTOR3& h, float& t )
{
	const D3DXVECTOR3 e = seg.GetEndPoint();

	// �����̒����A�����̑��̍��W�y��t���Z�o
	float len = CalcPointLineDist( p, SLine( seg.Point, e - seg.Point ), h, t );

	if ( IsSharpAngle( p, seg.Point, e ) == false ) {
		// �n�_���̊O��
		h = seg.Point;
		return D3DXVec3Length( &(seg.Point - p) );
	}
	else if ( IsSharpAngle( p, e, seg.Point ) == false ) {
		// �I�_���̊O��
		h = e;
		return D3DXVec3Length( &( e - p ) );
	}

	return len;
}

//----------------------------------.
// �Z�O�����g���m�̋������v�Z.
//----------------------------------.
float CalcSegmentSegmentDist( const SSegment& s1, const SSegment& s2 )
{
	D3DXVECTOR3	p1, p2;
	float		t1, t2;

	// s1 ���k�ނ��Ă��邩.
	if( D3DXVec3LengthSq( &s1.Vector ) < OX_EPSILON ){
		// s2 ���k�ނ��Ă��邩.
		if ( D3DXVec3LengthSq( &s2.Vector ) < OX_EPSILON ){
			const float len = D3DXVec3Length( &(s2.Point - s1.Point) );
			p1 = s1.Point;
			p2 = s2.Point;
			t1 = t2 = 0.0f;
			// �_�Ɠ_�Ƃ̋���.
			return len;
		} else {
			const float len = CalcPointSegmentDist( s1.Point, s2, p2, t2 );
			p1 = s1.Point;
			t1 = 0.0f;
			t2 = std::clamp( t2, 0.0f, 1.0f );
			return len;
		}
	// s2 ���k�ނ��Ă��邩.
	} else if ( D3DXVec3LengthSq( &s2.Vector ) < OX_EPSILON ){
		const float len =  CalcPointSegmentDist( s2.Point, s1, p1, t1 );
		p2 = s2.Point;
		t1 = std::clamp( t1, 0.0f, 1.0f );
		t2 = 0.0f;
		return len;
	}

	// �������m�����s�������ꍇ.
	if( IsParallel( s1.Vector, s2.Vector ) == true ){
		t1 =  0.0f;
		p1 = s1.Point;
		float len = CalcPointSegmentDist( s1.Point, s2, p2, t2 );
		if( 0.0f <= t2 && t2 <= 1.0f ) return len;
	} else {
		float len = CalcLineLineDist( s1, s2, p1, p2, t1, t2 );
		if( 0.0f <= t1 && t1 <= 1.0f && 
			0.0f <= t2 && t2 <= 1.0f ){
			return len;
		}
	}

	// �����̑����O�ɂ��鎖������.
	// S1����t1��0�`1�̊ԂɃN�����v���Đ������~�낷.
	t1 = std::clamp( t1, 0.0f, 1.0f );
	p1 = s1.GetPoint( t1 );
	float len = CalcPointSegmentDist( p1, s2, p2, t2 );
	if( 0.0f <= t2 && t2 <= 1.0f ) return len;

	// S2�����O�������̂�S2�����N�����v�AS1�ɐ������~�낷.
	t2 = std::clamp( t2, 0.0f, 1.0f );
	p2 = s2.GetPoint( t2 );
	len = CalcPointSegmentDist( p2, s1, p1, t1 );
	if( 0.0f <= t1 && t1 <= 1.0f ) return len;

	// �o���̒[�_���ŒZ�Ɣ���.
	t1 = std::clamp( t1, 0.0f, 1.0f );
	p1 = s1.GetPoint( t1 );
	return D3DXVec3Length( &( p2 - p1 ) );
};