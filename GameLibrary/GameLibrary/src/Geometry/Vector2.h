#pragma once

#include<cmath>

namespace Geometry{
	//2次元ベクトルを実現するクラス
	template <class T_param,class T_multiple> struct basic_Vector2D{
		//T_param:パラメータの型
		//T_multiple:掛け算する時の型
	public:
		//関数
		basic_Vector2D(T_param i_x,T_param i_y):x(i_x),y(i_y){}
		~basic_Vector2D()=default;
		//四則演算
		basic_Vector2D operator+(const basic_Vector2D &otherobj)const{ return basic_Vector2D(this->x+otherobj.x,this->y+otherobj.y); }
		void operator+=(const basic_Vector2D &otherobj){ *this=*this+otherobj; }
		basic_Vector2D operator-(const basic_Vector2D &otherobj)const{ return *this+(-otherobj); }
		void operator-=(const basic_Vector2D &otherobj){ *this=*this-otherobj; }
		basic_Vector2D operator*(const T_multiple &rate)const{ return basic_Vector2D(this->x*rate,this->y*rate); }
		void operator*=(const T_multiple &rate){ *this=*this*rate; }
		basic_Vector2D operator/(const T_multiple &rate)const{ return basic_Vector2D(this->x/rate,this->y/rate); }
		void operator/=(const T_multiple &rate){ *this=*this/rate; }
		//比較演算
		bool operator==(const basic_Vector2D &otherobj)const{ return (this->x==otherobj.x && this->y==otherobj.y); }
		bool operator!=(const basic_Vector2D &otherobj)const{ return !(*this==otherobj); }
		//ベクトルを反転
		basic_Vector2D operator-()const{
			return basic_Vector2D(-x,-y);
		}
		//ベクトル特有の機能
		T_param Dot(const basic_Vector2D &otherobj)const{
			//内積
			return this->x*otherobj.x+this->y*otherobj*y;
		}
		T_param CrossSize(const basic_Vector2D &otherobj)const{
			//外積の大きさ：2ベクトルによって構成される平行四辺形の面積
			return this->x*otherobj.y-this->y*otherobj.x;
		}
		T_param SqSize()const{
			//長さの2乗
			return x*x+y*y;
		}
		T_multiple Size()const;//長さを返す(この時、ベクトルに掛け算されることが多い事を考えるとT_multipleで返してあげると親切なはず、実装は型によって分岐)
		T_multiple GetRadian()const;//角度を返す
		basic_Vector2D Turn(T_multiple radian)const;//回転させる
		basic_Vector2D MultipleNorm(T_multiple length)const{
			//lengthの長さの傾きが同じベクトルを返す
			return *this*(length/Size());
		}
		//変数
		T_param x,y;
		static const basic_Vector2D s_zero;//零ベクトル
	};

	//普段使いするベクトルの明示(実装し終わっていない関数はVector2.cppにて実装する)
	using Vector2=basic_Vector2D<float,float>;
	using Vector2Int=basic_Vector2D<int,double>;

	//コンバート用関数
	Vector2 ConvertToVector2(const Vector2Int &intVec);
	Vector2Int ConvertToVector2Int(const Vector2 &vec);
}
