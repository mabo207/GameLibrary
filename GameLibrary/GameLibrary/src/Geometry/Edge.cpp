#include"Edge.h"
#include"DxLib.h"
#include"Params.h"

//-----------------Edge-------------------
Geometry::Edge::Edge(const Vector2 &position,const Vector2 &vector)
	:Shape(Kind::e_edge,position)
	,m_vec(vector)
{}

std::shared_ptr<Geometry::Shape> Geometry::Edge::Copy()const{
	return std::shared_ptr<Shape>(new Edge(m_position,m_vec));
}

bool Geometry::Edge::JudgeCross(const Shape *otherShape)const{
	if(otherShape!=nullptr){
		const Kind kind=otherShape->GetKind();
		if(kind==Kind::e_circle){
			//�~�Ɛ���
			return otherShape->JudgeCross(this);//�������ڏ�
		} else if(kind==Kind::e_edge){
			//�����Ɛ���
			const Edge *pEdge=dynamic_cast<const Edge *>(otherShape);
			if(pEdge!=nullptr){
				return CalculateCrossPoint(*pEdge).first;
			}
		} else if(kind==Kind::e_polygon){
			//�����Ƒ��p�`
			return otherShape->JudgeCross(this);//�������ڏ�
		}
	}
	return false;
}

bool Geometry::Edge::JudgeInThis(const Shape *otherShape)const{
	//�������ɓ��邱�Ƃ͂ł��Ȃ�
	return false;
}

bool Geometry::Edge::JudgePointIn(const Vector2 &pointPos)const{
	//������ɓ_�����邩�ǂ���(=�O��0)
	return m_vec.CrossSize(pointPos-m_position)==0.0f;
}

Geometry::Vector2 Geometry::Edge::CalculateFeedback(const Shape *moveShape,const Vector2 &moveVec)const{
	if(moveShape!=nullptr){
		const Kind kind=moveShape->GetKind();
		if(kind==Kind::e_circle){
			//�~�Ɛ���
			return -moveShape->CalculateFeedback(this,-moveVec);//�������ڏ�(�x�N�g���̌����ɒ���)
		} else if(kind==Kind::e_edge){
			//�����Ɛ���
			const Edge *pEdge=dynamic_cast<const Edge *>(moveShape);
			if(pEdge!=nullptr){
				//this���pEdge�ւ̍ŋߖT�_�����߂�
				Edge afterMoveEdge=*pEdge;
				afterMoveEdge.Move(moveVec);
				//pEdge���ړ��ɂ����this���ׂ������𔻒肷��
				const float cross[4]={
					this->m_vec.CrossSize(pEdge->GetPosition()-this->m_position)
					,this->m_vec.CrossSize(pEdge->GetEndPoint()-this->m_position)
					,this->m_vec.CrossSize(afterMoveEdge.GetPosition()-this->m_position)
					,this->m_vec.CrossSize(afterMoveEdge.GetPosition()-this->m_position)
				};
				if((cross[0]>=0.0f && cross[1]>=0.0f && cross[2]>=0.0f && cross[3]>=0.0f)
					|| (cross[0]<0.0f && cross[1]<0.0f && cross[2]<0.0f && cross[3]<0.0f))
				{
					//�ׂ��ł��Ȃ��ꍇ(cross[i]�̕��������ׂē���)
					return Vector2::s_zero;
				} else{
					//�ׂ����ꍇ�AafterMoveEdge�𐂒��ɓ������Čׂ��Ȃ���Ԃɂ��邽�߂̃t�B�[�h�o�b�N��Ԃ�
					//moveVec��this->m_vec�̐�����������
					const Geometry::Vector2 moveVecVertical=moveVec.VerticalComponent(this->m_vec);
					//�ړ����2�_�ɂ��āAthis��̐����̑����炻�̓_�ɐL�΂����x�N�g��
					const Geometry::Vector2 afterBeginVertical=(afterMoveEdge.GetPosition()-this->m_position).VerticalComponent(this->m_vec)
						,afterEndVertical=(afterMoveEdge.GetEndPoint()-this->m_position).VerticalComponent(this->m_vec);
					//�ړ����2�_�̂ǂ��炪���AmoveVecVertical�ɐi��ł��邩�𔻒肵�āA����ɑΉ�����vertical�������t�����ɂ��ĕԂ��Ă�����
					if(moveVecVertical.Dot(afterBeginVertical)>moveVecVertical.Dot(afterEndVertical)){
						return -afterBeginVertical;
					} else{
						return -afterEndVertical;
					}
				}
				//const std::pair<bool,Vector2> crossInfo=CalculateCrossPoint(afterMoveEdge);
				//if(crossInfo.first){
				//	//��_�����݂��Ă��鎞�̂݁A�����o���������v�Z����
				//	//������ɏ悹�����_���ǂ��炩�v�Z
				//	Vector2 onLinePoint=Vector2::s_zero;
				//	if(this->m_vec.Dot(moveVec)>0.0f){
				//		//moveVec��afterMoveEdge�̌����������ꍇ�AafterMoveEdge.GetEndPoint()��this��ɏ悹��悤�ɂ���
				//		onLinePoint=afterMoveEdge.GetEndPoint();
				//	} else{
				//		//�������t�Ȃ�AafterMoveEdge.m_position��this��ɏ悹�悤�Ƃ���
				//		onLinePoint=afterMoveEdge.GetPosition();
				//	}
				//	//���������̃x�N�g�������߂�
				//	const Vector2 slantFeedback=crossInfo.second-onLinePoint;//�����this�ɐ����Ȑ��������߂�΂悢
				//	return slantFeedback.VerticalComponent(this->m_vec);
				//}
			}
		} else if(kind==Kind::e_polygon){
			//�����Ƒ��p�`
			return -moveShape->CalculateFeedback(this,-moveVec);//�������ڏ�(�x�N�g���̌����ɒ���)
		}
	}
	return Geometry::Vector2::s_zero;
}

void Geometry::Edge::Resize(const Vector2 &v){
	m_vec=v;
}

Geometry::Vector2 Geometry::Edge::GetResizeBaseVector()const{
	return m_vec;
}

void Geometry::Edge::Draw(const Vector2 &position,unsigned int color,int fillFlag,float lineThickness)const{
	const Vector2 end=position+m_vec;
	DrawLineAA(position.x,position.y,end.x,end.y,color,lineThickness);
}

Geometry::Vector2 Geometry::Edge::GetLeftTop()const{
	float left=m_position.x,top=m_position.y;
	if(m_vec.x<0.0f){
		left+=m_vec.x;
	}
	if(m_vec.y<0.0f){
		top+=m_vec.y;
	}
	return Vector2(left,top);
}

Geometry::Vector2 Geometry::Edge::GetRightButtom()const{
	float right=m_position.x,buttom=m_position.y;
	if(m_vec.x>0.0f){
		right+=m_vec.x;
	}
	if(m_vec.y>0.0f){
		buttom+=m_vec.y;
	}
	return Vector2(right,buttom);
}

std::pair<bool,Geometry::Vector2> Geometry::Edge::CalculateCrossPoint(const Edge &otherobj)const{
	//this->m_position=(x1,y1),this->m_vec=(x2,y2),otherobj.m_position=(x3,y3),otherobj.m_vec=(x4,y4)�ƒu���B
	//(x2*y4-x4*y2)==0�̎��X����0�Ȃ̂ŕ��s�ł���A���̒l�͌�ŗp����
	const float inclination=this->m_vec.x*otherobj.m_vec.y-otherobj.m_vec.x*this->m_vec.y;
	if(inclination==0.0f){
		//���s�̏ꍇ
		//���꒼����ɑ��݂��邩�̔��������(2��position���m�����񂾒�����this�����s���ǂ����Ŕ��肷��΂悢)
		//p1=this->GetPosition(),q1=this->GetEndPoint(),p2=otherobj.GetPosition(),q2=otherobj.GetEndPoint()�ł���
		const Vector2 p1p2=otherobj.GetPosition()-this->GetPosition();
		if(m_vec.x*p1p2.y==p1p2.x*m_vec.y){
			//���꒼����ɂ������ꍇ�A���ς�p���Ĕ���
			const Vector2 p1q2=otherobj.GetEndPoint()-this->GetPosition();
			const Vector2 q1p2=otherobj.GetPosition()-this->GetEndPoint();
			const Vector2 q1q2=otherobj.GetEndPoint()-this->GetEndPoint();
			if(p1p2.Dot(m_vec)<0.0f && p1q2.Dot(m_vec)<0.0f){
				//pEdge�̗��[�_��this��begin���m_vec�Ƌt���ɂ��鎞
				return std::make_pair(false,Vector2::s_zero);
			} else if(q1p2.Dot(m_vec)>0.0f && q1q2.Dot(m_vec)>0.0f){
				//pEdge�̗��[�_��this��end���m_vec�Ɠ������ɂ��鎞
				return std::make_pair(false,Vector2::s_zero);
			} else{
				//�����͕K����_�����Athis�̒[�_�̂ǂ��炩�͕K��otherobj��ɑ��݂���
				Vector2 p=Vector2::s_zero;
				if(p1p2.Dot(p1q2)<0.0f){
					//p1��p2q2��i��otherobj��j�ɂ���
					p=this->m_position;
				} else{
					p=this->GetEndPoint();
				}
				return std::make_pair(true,p);
			}
		}
	} else{
		//���s�łȂ��ꍇ�A�����̌�_�����߂Ă���炪������ɑ��݂��邩�����߂�
		//��_�̍��W��(x,y)=(x1,y1)+m*(x2,y2)=(x3,y3)+n*(x4,y4) (m,n��float)�ƂȂ�
		//0<=m,n<=1�ł���Ό�_����������ɑ��݂��邱�ƂɂȂ�
		//�������������ƁAm*(x2*y4-x4*y2)=y4*(x3-x1)-x4(y3-y1),n*(x2*y4-x4*y2)=y2*(x3-x1)-x2*(y3-y1)�ƂȂ�B
		const float m=(otherobj.m_vec.y*(otherobj.m_position.x-this->m_position.x)-otherobj.m_vec.x*(otherobj.m_position.y-this->m_position.y))/inclination;
		const float n=(this->m_vec.y*(otherobj.m_position.x-this->m_position.x)-this->m_vec.x*(otherobj.m_position.y-this->m_position.y))/inclination;
		return std::make_pair(m>=0.0f && m<=1.0f && n>=0.0f && n<=1.0f,this->m_position+this->m_vec*m);
	}
	return std::make_pair(false,Vector2::s_zero);
}
