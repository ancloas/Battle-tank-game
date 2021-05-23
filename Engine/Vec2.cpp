#include "Vec2.h"
#include <cmath>

Vec2::Vec2( float x_in,float y_in )
	:
	x( x_in ),
	y( y_in )
{
}

Vec2 Vec2::operator+( const Vec2& rhs ) const
{
	return Vec2( x + rhs.x,y + rhs.y );
}

Vec2& Vec2::operator+=( const Vec2& rhs )
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator*( float rhs ) const
{
	return Vec2( x * rhs,y * rhs );
}

Vec2& Vec2::operator*=( float rhs )
{
	return *this = *this * rhs;
}

Vec2 Vec2::operator-( const Vec2& rhs ) const
{
	return Vec2( x - rhs.x,y - rhs.y );
}

Vec2& Vec2::operator-=( const Vec2& rhs )
{
	return *this = *this - rhs;
}

float Vec2::GetLength() const
{
	return std::sqrt( GetLengthSq() );
}

float Vec2::GetLengthSq() const
{
	return x * x + y * y;
}

Vec2& Vec2::Normalize()
{
	return *this = GetNormalized();
}

Vec2 Vec2::GetNormalized() const
{
	const float len = GetLength();
	if( len != 0.0f )
	{
		return *this * (1.0f / len);
	}
	return *this;
}

void Vec2::Rotate_by_90_degree_clockwise_wrt_origin(const Vec2 & Origin)
{
	Vec2 Pos_wrt_Origin_after_rotation =Vec2((*this-Origin).y,-1*(*this - Origin).x);

	*this = Origin + Pos_wrt_Origin_after_rotation;
}

void Vec2::Rotate_by_90_degree_anticlockwise_wrt_origin(const Vec2 & Origin)
{
	Vec2 Pos_wrt_Origin_after_rotation = Vec2(-1*(*this - Origin).y, (*this - Origin).x);

	*this = Origin + Pos_wrt_Origin_after_rotation;
}
