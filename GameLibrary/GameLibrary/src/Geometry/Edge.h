#pragma once

#include"Shape.h"

namespace Geometry{
	//������\������N���X
	class Edge:public Shape{
	public:
		//�֐�
		Edge(const Vector2 &position,const Vector2 &vector);//�n�_�Ɛ��̐L�т�����ō\��
		~Edge()=default;
		Vector2 GetVector()const{
			return m_vec;
		}
		Vector2 GetEndPoint()const{
			return m_position+m_vec;
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
		//�ÓI�֐�
		static Edge CreateWith2Point(const Vector2 &begin,const Vector2 &end){
			return Edge(begin,end-begin);
		}

	private:
		//�֐�
		std::pair<bool,Vector2> CalculateCrossPoint(const Edge &otherobj)const;//this��otherobj����_���������肵�A�����Ă���ꍇ�͌�_�����߂�

		//�ϐ�
		Vector2 m_vec;
	};
}