#pragma once

#include"Shape.h"

namespace Geometry{
	//�~��\������N���X
	class Circle:public Shape{
	public:
		//�֐�
		Circle(const Vector2 &center,float r);
		~Circle()=default;
		float GetR()const{
			return m_r;
		}
		//���z�֐��̃I�[�o�[���C�h
		std::shared_ptr<Shape> Copy()const;//���g�������Ń|�C���^���قȂ�}�`��Ԃ�
		bool JudgeCross(const Shape *otherShape)const;//�d�Ȃ��Ă��邩�ǂ����𔻒肷��
		bool JudgeInThis(const Shape *otherShape)const;//�����ɓ����Ă��邩�ǂ����𔻒肷��
		bool JudgePointIn(const Vector2 &pointPos)const;//�_�������ɓ����Ă��邩�ǂ����𔻒肷��
		Vector2 CalculateFeedback(const Shape *moveShape,const Vector2 &moveVec)const;//moveShape��moveVec�����ړ����悤�Ƃ��Ă��鎞�ɁA���̐}�`�ɓ������ĉ����Ԃ��x�N�g�����v�Z����
		void Resize(const Vector2 &v);//��ƂȂ�x�N�g����v�ɂȂ�悤�ɕό`������
		Vector2 GetResizeBaseVector()const;//���݂̐}�`�ɂ�����AResize(Vector2)�̊�x�N�g����Ԃ�
		void Draw(const Vector2 &position,unsigned int color,int fillFlag,float lineThickness)const;//�`��
		Vector2 GetLeftTop()const;//����̍��W��Ԃ�
		Vector2 GetRightButtom()const;//�E���̍��W��Ԃ�

	private:
		float m_r;//���a
	};
}