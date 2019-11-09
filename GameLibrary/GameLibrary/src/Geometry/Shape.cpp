#include"Shape.h"

//---------------Shape-----------------
void Geometry::Shape::Resize(float rate){
	Resize(GetResizeBaseVector()*rate);
}

void Geometry::Shape::Move(const Vector2 &moveVec){
	m_position+=moveVec;
}

void Geometry::Shape::Warp(const Vector2 &position){
	m_position=position;
}

void Geometry::Shape::Draw(unsigned int color,int fillFlag,float lineThickness)const{
	Draw(m_position,color,fillFlag,lineThickness);
}

Geometry::Shape::Shape(Kind kind,const Vector2 &position)
	:m_position(position)
	,m_kind(kind)
{}