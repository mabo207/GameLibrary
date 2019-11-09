#pragma once

#include"Vector2.h"
#include<memory>

namespace Geometry{
	//�}�`��\������N���X
	class Shape{
	public:
		//�}�`�̎��
		enum class Kind{
			e_circle
			,e_edge
			,e_polygon
		};

		//�֐�
		void Resize(float rate);//rate�{�����g�傷��
		void Move(const Vector2 &moveVec);//���݈ʒu����moveVec�����ړ�����
		void Warp(const Vector2 &position);//position�ֈړ�����
		void Draw(unsigned int color,int fillFlag,float lineThickness)const;//�`��
		Kind GetKind()const{
			return m_kind;
		}
		Vector2 GetPosition()const{
			return m_position;
		}

		//�������z�֐�
		virtual std::shared_ptr<Shape> Copy()const=0;//���g�������Ń|�C���^���قȂ�}�`��Ԃ�
		virtual bool JudgeCross(const Shape *otherShape)const=0;//�d�Ȃ��Ă��邩�ǂ����𔻒肷��
		virtual bool JudgeInThis(const Shape *otherShape)const=0;//�����ɓ����Ă��邩�ǂ����𔻒肷��
		virtual bool JudgePointIn(const Vector2 &pointPos)const=0;//�_�������ɓ����Ă��邩�ǂ����𔻒肷��
		virtual Vector2 CalculateFeedback(const Shape *moveShape,const Vector2 &moveVec)const=0;//moveShape��moveVec�����ړ����悤�Ƃ��Ă��鎞�ɁA���̐}�`�ɓ������ĉ����Ԃ��x�N�g�����v�Z����
		virtual void Resize(const Vector2 &v)=0;//��ƂȂ�x�N�g����v�ɂȂ�悤�ɕό`������
		virtual Vector2 GetResizeBaseVector()const=0;//���݂̐}�`�ɂ�����AResize(Vector2)�̊�x�N�g����Ԃ�
		virtual void Draw(const Vector2 &position,unsigned int color,int fillFlag,float lineThickness)const=0;//�`��
		virtual Vector2 GetLeftTop()const=0;//����̍��W��Ԃ�
		virtual Vector2 GetRightButtom()const=0;//�E���̍��W��Ԃ�

	protected:
		Shape(Kind kind,const Vector2 &position);
		virtual ~Shape()=default;

		//�ϐ�
		Vector2 m_position;//�}�`�̈ʒu
		Kind m_kind;//�}�`�̎��
	};
}