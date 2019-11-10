#pragma once

#include<cmath>

namespace Geometry{
	//2�����x�N�g������������N���X
	template <class T_param,class T_multiple> struct basic_Vector2D{
		//T_param:�p�����[�^�̌^
		//T_multiple:�|���Z���鎞�̌^
	public:
		//�֐�
		basic_Vector2D(T_param i_x,T_param i_y):x(i_x),y(i_y){}
		~basic_Vector2D()=default;
		//�l�����Z
		basic_Vector2D operator+(const basic_Vector2D &otherobj)const{ return basic_Vector2D(this->x+otherobj.x,this->y+otherobj.y); }
		void operator+=(const basic_Vector2D &otherobj){ *this=*this+otherobj; }
		basic_Vector2D operator-(const basic_Vector2D &otherobj)const{ return *this+(-otherobj); }
		void operator-=(const basic_Vector2D &otherobj){ *this=*this-otherobj; }
		basic_Vector2D operator*(const T_multiple &rate)const{ return basic_Vector2D(this->x*rate,this->y*rate); }
		void operator*=(const T_multiple &rate){ *this=*this*rate; }
		basic_Vector2D operator/(const T_multiple &rate)const{ return basic_Vector2D(this->x/rate,this->y/rate); }
		void operator/=(const T_multiple &rate){ *this=*this/rate; }
		//��r���Z
		bool operator==(const basic_Vector2D &otherobj)const{ return (this->x==otherobj.x && this->y==otherobj.y); }
		bool operator!=(const basic_Vector2D &otherobj)const{ return !(*this==otherobj); }
		//�x�N�g���𔽓]
		basic_Vector2D operator-()const{
			return basic_Vector2D(-x,-y);
		}
		//�x�N�g�����L�̋@�\
		T_param Dot(const basic_Vector2D &otherobj)const{
			//����
			return this->x*otherobj.x+this->y*otherobj*y;
		}
		T_param CrossSize(const basic_Vector2D &otherobj)const{
			//�O�ς̑傫���F2�x�N�g���ɂ���č\������镽�s�l�ӌ`�̖ʐ�
			return this->x*otherobj.y-this->y*otherobj.x;
		}
		T_param SqSize()const{
			//������2��
			return x*x+y*y;
		}
		T_multiple Size()const;//������Ԃ�(���̎��A�x�N�g���Ɋ|���Z����邱�Ƃ����������l�����T_multiple�ŕԂ��Ă�����Ɛe�؂Ȃ͂��A�����͌^�ɂ���ĕ���)
		T_multiple GetRadian()const;//�p�x��Ԃ�
		basic_Vector2D Turn(T_multiple radian)const;//��]������
		basic_Vector2D MultipleNorm(T_multiple length)const{
			//length�̒����̌X���������x�N�g����Ԃ�
			return *this*(length/Size());
		}
		//�ϐ�
		T_param x,y;
		static const basic_Vector2D s_zero;//��x�N�g��
	};

	//���i�g������x�N�g���̖���(�������I����Ă��Ȃ��֐���Vector2.cpp�ɂĎ�������)
	using Vector2=basic_Vector2D<float,float>;
	using Vector2Int=basic_Vector2D<int,double>;

	//�R���o�[�g�p�֐�
	Vector2 ConvertToVector2(const Vector2Int &intVec);
	Vector2Int ConvertToVector2Int(const Vector2 &vec);
}
