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
				//円と円の交差判定、2中心間の距離Lを用いて判定
				//|this->m_r-pCircle->m_r|<=L<=this->m_r+pCircle->m_rであれば交差、そうでない場合は非交差
				const float sqL=(this->m_position-pCircle->m_position).SqSize();
				const float sub=this->m_r-pCircle->m_r;
				const float sum=this->m_r+pCircle->m_r;
				return (sub*sub<=sqL) && (sqL<=sum*sum);
			}
		} else if(kind==Kind::e_edge){
			//円と線分の交差判定

		} else if(kind==Kind::e_polygon){
			//円と多角形の交差判定

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
				//円と円の包括判定、2中心間の距離Lを用いて判定
				//L<=|this->m_r-pCircle->m_r|であれば交差、そうでない場合は非交差
				const float sqL=(this->m_position-pCircle->m_position).SqSize();
				const float sub=this->m_r-pCircle->m_r;
				return (sqL<=sub*sub);
			}
		} else if(kind==Kind::e_edge){
			//円と線分の包括判定

		} else if(kind==Kind::e_polygon){
			//円と多角形の包括判定

		}
	}
	return false;
}

bool Geometry::Circle::JudgePointIn(const Vector2 &pointPos)const{
	//点の円内部判定は、中心からの距離を見れば良い
	return ((pointPos-m_position).SqSize()<=m_r*m_r);
}

Geometry::Vector2 Geometry::Circle::CalculateFeedback(const Shape *moveShape,const Vector2 &moveVec)const{
	if(moveShape!=nullptr){
		const Kind kind=moveShape->GetKind();
		if(kind==Kind::e_circle){
			const Circle *pCircle=dynamic_cast<const Circle *>(moveShape);
			if(pCircle!=nullptr){
				//円と円
				//押し出す方向を判定する（内部or外部）
				bool pushOut=true;//true:外部押し出し false:内部押し出し
				if(this->m_r>pCircle->m_r){
					//移動円がthis内部に収まる可能性がある時のみ、内部押し出しが起こりうる
					//移動前の移動円中心がthis内部にある時のみ内部押し出し
					pushOut=((pCircle->GetPosition()-this->m_position).SqSize()>=this->m_r*this->m_r);
				}
				//押し出す方向を返す
				const Vector2 centerVec=pCircle->GetPosition()+moveVec-this->m_position;//押し出しがない場合の移動後の中心同士を結ぶベクトル
				if(pushOut){
					//外部押し出し
					const float rSum=this->m_r+pCircle->GetR();
					if(centerVec.SqSize()<rSum*rSum){
						//移動円がthisにめり込んでいて、押し出す必要がある場合、rSum-|centerVec|だけ押し出す
						//必ずしも２つの円が交点を持つ必要がない
						return centerVec.MultipleNorm(rSum)-centerVec;
					} else{
						return Vector2::s_zero;
					}
				} else{
					//内部押し出し
					const float rSub=this->m_r-pCircle->GetR();
					if(rSub*rSub<centerVec.SqSize()){
						//移動円とthisが交差している場合に、押し出しベクトルを返す
						return centerVec.MultipleNorm(rSub)-centerVec;
					} else{
						return Vector2::s_zero;
					}
				}
			}
		} else if(kind==Kind::e_edge){
			//円と線分の交差判定

		} else if(kind==Kind::e_polygon){
			//円と多角形の交差判定

		}
	}
	return Vector2::s_zero;
}

void Geometry::Circle::Resize(const Vector2 &v){
	m_r=v.Size();
}

Geometry::Vector2 Geometry::Circle::GetResizeBaseVector()const{
	//いくつかベクトルの候補があるので、適当に下向きのものを作成
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
