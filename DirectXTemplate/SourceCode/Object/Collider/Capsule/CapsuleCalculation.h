#ifndef CAPSULE_CALCULATION_H
#define CAPSULE_CALCULATION_H

#include "..\..\..\Global.h"

/*
*	ŤQl.
*	http://marupeke296.com/COL_3D_No27_CapsuleCapsule.html.
*/

// źü.
struct stLine
{
	D3DXVECTOR3 Point;
	D3DXVECTOR3 Vector;

	stLine()
		: Point	( 0.0f, 0.0f, 0.0f )
		, Vector( 1.0f, 0.0f, 0.0f )
	{}
	stLine( const D3DXVECTOR3& p, const D3DXVECTOR3& v )
		: Point	( p )
		, Vector( v )
	{}

	D3DXVECTOR3 GetPoint( const float& t ) const
	{
		return Point + t * Vector;
	}
} typedef SLine;

// üŞ.
struct stSegment : public SLine
{
	stSegment(){}
	stSegment( const D3DXVECTOR3& p, const D3DXVECTOR3& v )
		: SLine( p, v )
	{}
	stSegment( const D3DXVECTOR3& p, const D3DXVECTOR3& v1, const D3DXVECTOR3& v2 )
		: SLine( p, v2 - v1 )
	{}
	D3DXVECTOR3 GetEndPoint() const
	{
		return Point + Vector;
	};
} typedef SSegment;



//----------------------------------.
// Úp1p2p3ÍspH.
//----------------------------------.
bool IsSharpAngle( const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, const D3DXVECTOR3& p3 );

//----------------------------------.
// ˝sŠÇ¤Š.
//----------------------------------.
bool IsParallel( const D3DXVECTOR3& v1, const D3DXVECTOR3& v2 );

//----------------------------------.
// 2źüĚĹZŁ.
//----------------------------------.
float CalcLineLineDist( const SLine& l1, const SLine& l2, D3DXVECTOR3& p1, D3DXVECTOR3& p2, float& t1, float& t2 );

//----------------------------------.
// _ĆźüĚĹZŁ.
//----------------------------------.
float CalcPointLineDist( const D3DXVECTOR3& p, const SLine& l, D3DXVECTOR3& h, float& t );

//----------------------------------.
// _ĆüŞĚĹZŁ.
//----------------------------------.
float CalcPointSegmentDist( const D3DXVECTOR3& p, const SSegment& seg, D3DXVECTOR3& h, float& t );

//----------------------------------.
// ZOgŻmĚŁđvZ.
//----------------------------------.
float CalcSegmentSegmentDist( const SSegment& s1, const SSegment& s2 );

#endif	// #ifndef CAPSULE_CALCULATION_H.
