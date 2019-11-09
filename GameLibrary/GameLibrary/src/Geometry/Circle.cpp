#include"Circle.h"
#include"DxLib.h"

//-------------Circle--------------
Geometry::Circle::Circle(const Vector2 &center,float r)
	:Shape(Kind::e_circle,center)
	,m_r(r)
{}

std::shared_ptr<Geometry::Shape> Geometry::Circle::Copy()const{
	return std::shared_ptr<Shape>(new Circle(*this));
}

bool Geometry::Circle::JudgeCross(const Shape *otherShape)const{
	if(otherShape!=nullptr){
		const Kind kind=otherShape->GetKind();
		if(kind==Kind::e_circle){
			const Circle *pCircle=dynamic_cast<const Circle *>(otherShape);
			if(pCircle!=nullptr){
				//�~�Ɖ~�̌�������A2���S�Ԃ̋���L��p���Ĕ���
				//|this->m_r-pCircle->m_r|<=L<=this->m_r+pCircle->m_r�ł���Ό����A�����łȂ��ꍇ�͔����
				const float sqL=(this->m_position-pCircle->m_position).SqSize();
				const float sub=this->m_r-pCircle->m_r;
				const float sum=this->m_r+pCircle->m_r;
				return (sub*sub<=sqL) && (sqL<=sum*sum);
			}
		} else if(kind==Kind::e_edge){
			//�~�Ɛ����̌�������

		} else if(kind==Kind::e_polygon){
			//�~�Ƒ��p�`�̌�������

		}
	}
	return false;
}

bool Geometry::Circle::JudgeInThis(const Shape *otherShape)const{
	if(otherShape!=nullptr){
		const Kind kind=otherShape->GetKind();
		if(kind==Kind::e_circle){
			const Circle *pCircle=dynamic_cast<const Circle *>(otherShape);
			if(pCircle!=nullptr){
				//�~�Ɖ~�̕����A2���S�Ԃ̋���L��p���Ĕ���
				//L<=|this->m_r-pCircle->m_r|�ł���Ό����A�����łȂ��ꍇ�͔����
				const float sqL=(this->m_position-pCircle->m_position).SqSize();
				const float sub=this->m_r-pCircle->m_r;
				return (sqL<=sub*sub);
			}
		} else if(kind==Kind::e_edge){
			//�~�Ɛ����̕����

		} else if(kind==Kind::e_polygon){
			//�~�Ƒ��p�`�̕����

		}
	}
	return false;
}

bool Geometry::Circle::JudgePointIn(const Vector2 &pointPos)const{
	//�_�̉~��������́A���S����̋���������Ηǂ�
	return ((pointPos-m_position).SqSize()<=m_r*m_r);
}

Geometry::Vector2 Geometry::Circle::CalculateFeedback(const Shape *moveShape,const Vector2 &moveVec)const{
	if(moveShape!=nullptr){
		const Kind kind=moveShape->GetKind();
		if(kind==Kind::e_circle){
			const Circle *pCircle=dynamic_cast<const Circle *>(moveShape);
			if(pCircle!=nullptr){
				//�~�Ɖ~
				//�����o�������𔻒肷��i����or�O���j
				bool pushOut=true;//true:�O�������o�� false:���������o��
				if(this->m_r>pCircle->m_r){
					//�ړ��~��this�����Ɏ��܂�\�������鎞�̂݁A���������o�����N���肤��
					//�ړ��O�̈ړ��~���S��this�����ɂ��鎞�̂ݓ��������o��
					pushOut=((pCircle->GetPosition()-this->m_position).SqSize()>=this->m_r*this->m_r);
				}
				//�����o��������Ԃ�
				const Vector2 centerVec=pCircle->GetPosition()+moveVec-this->m_position;//�����o�����Ȃ��ꍇ�̈ړ���̒��S���m�����ԃx�N�g��
				if(pushOut){
					//�O�������o��
					const float rSum=this->m_r+pCircle->GetR();
					if(centerVec.SqSize()<rSum*rSum){
						//�ړ��~��this�ɂ߂荞��ł��āA�����o���K�v������ꍇ�ArSum-|centerVec|���������o��
						//�K�������Q�̉~����_�����K�v���Ȃ�
						return centerVec.MultipleNorm(rSum)-centerVec;
					} else{
						return Vector2::s_zero;
					}
				} else{
					//���������o��
					const float rSub=this->m_r-pCircle->GetR();
					if(rSub*rSub<centerVec.SqSize()){
						//�ړ��~��this���������Ă���ꍇ�ɁA�����o���x�N�g����Ԃ�
						return centerVec.MultipleNorm(rSub)-centerVec;
					} else{
						return Vector2::s_zero;
					}
				}
			}
		} else if(kind==Kind::e_edge){
			//�~�Ɛ����̌�������

		} else if(kind==Kind::e_polygon){
			//�~�Ƒ��p�`�̌�������

		}
	}
	return Vector2::s_zero;
}

void Geometry::Circle::Resize(const Vector2 &v){
	m_r=v.Size();
}

Geometry::Vector2 Geometry::Circle::GetResizeBaseVector()const{
	//�������x�N�g���̌�₪����̂ŁA�K���ɉ������̂��̂��쐬
	return Vector2(0.0f,m_r);
}

void Geometry::Circle::Draw(const Vector2 &position,unsigned int color,int fillFlag,float lineThickness)const{
	DrawCircleAA(position.x,position.y,m_r,30,color,fillFlag,lineThickness);
}

Geometry::Vector2 Geometry::Circle::GetLeftTop()const{
	return m_position-Vector2(m_r,m_r);
}

Geometry::Vector2 Geometry::Circle::GetRightButtom()const{
	return m_position+Vector2(m_r,m_r);
}
