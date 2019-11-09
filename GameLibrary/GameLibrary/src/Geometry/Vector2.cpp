#include"Vector2.h"

//floatによるベクトル表現の実装(Vector2)
float Geometry::Vector2::Size()const{
	return std::sqrtf(SqSize());
}
float Geometry::Vector2::GetRadian()const{
	return std::atan2f(y,x);
}
Geometry::Vector2 Geometry::Vector2::Turn(float radian)const{
	const float cos=std::cosf(radian),sin=std::sinf(radian);
	return Vector2(x*cos-y*sin,x*sin+y*cos);
}
//intによるベクトル表現の実装(Vector2Int)
double Geometry::Vector2Int::Size()const{
	return std::sqrt(SqSize());
}
double Geometry::Vector2Int::GetRadian()const{
	return std::atan2(y,x);
}
Geometry::Vector2Int Geometry::Vector2Int::Turn(double radian)const{
	const double cos=std::cos(radian),sin=std::sin(radian);
	return Vector2Int((int)(x*cos-y*sin),(int)(x*sin+y*cos));
}

//コンバート用関数
Geometry::Vector2 Geometry::ConvertToVector2(const Vector2Int &intVec){
	return Vector2((float)intVec.x,(float)intVec.y);
}
Geometry::Vector2Int Geometry::ConverToVector2Int(const Vector2 &vec){
	return Vector2Int((int)vec.x,(int)vec.y);
}
