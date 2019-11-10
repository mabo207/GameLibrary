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
			//円と線分
			return otherShape->JudgeCross(this);//処理を移譲
		} else if(kind==Kind::e_edge){
			//線分と線分
			const Edge *pEdge=dynamic_cast<const Edge *>(otherShape);
			if(pEdge!=nullptr){
				return CalculateCrossPoint(*pEdge).first;
			}
		} else if(kind==Kind::e_polygon){
			//線分と多角形
			return otherShape->JudgeCross(this);//処理を移譲
		}
	}
	return false;
}

bool Geometry::Edge::JudgeInThis(const Shape *otherShape)const{
	//線分内に入ることはできない
	return false;
}

bool Geometry::Edge::JudgePointIn(const Vector2 &pointPos)const{
	//線分上に点があるかどうか(=外積0)
	return m_vec.CrossSize(pointPos-m_position)==0.0f;
}

Geometry::Vector2 Geometry::Edge::CalculateFeedback(const Shape *moveShape,const Vector2 &moveVec)const{
	if(moveShape!=nullptr){
		const Kind kind=moveShape->GetKind();
		if(kind==Kind::e_circle){
			//円と線分
			return -moveShape->CalculateFeedback(this,-moveVec);//処理を移譲(ベクトルの向きに注意)
		} else if(kind==Kind::e_edge){
			//線分と線分
			const Edge *pEdge=dynamic_cast<const Edge *>(moveShape);
			if(pEdge!=nullptr){
				//this上のpEdgeへの最近傍点を求める
				Edge afterMoveEdge=*pEdge;
				afterMoveEdge.Move(moveVec);
				//pEdgeが移動によってthisを跨いだかを判定する
				const float cross[4]={
					this->m_vec.CrossSize(pEdge->GetPosition()-this->m_position)
					,this->m_vec.CrossSize(pEdge->GetEndPoint()-this->m_position)
					,this->m_vec.CrossSize(afterMoveEdge.GetPosition()-this->m_position)
					,this->m_vec.CrossSize(afterMoveEdge.GetPosition()-this->m_position)
				};
				if((cross[0]>=0.0f && cross[1]>=0.0f && cross[2]>=0.0f && cross[3]>=0.0f)
					|| (cross[0]<0.0f && cross[1]<0.0f && cross[2]<0.0f && cross[3]<0.0f))
				{
					//跨いでいない場合(cross[i]の符号がすべて同じ)
					return Vector2::s_zero;
				} else{
					//跨いだ場合、afterMoveEdgeを垂直に動かして跨がない状態にするためのフィードバックを返す
					//moveVecのthis->m_vecの垂直方向成分
					const Geometry::Vector2 moveVecVertical=moveVec.VerticalComponent(this->m_vec);
					//移動後の2点について、this上の垂線の足からその点に伸ばしたベクトル
					const Geometry::Vector2 afterBeginVertical=(afterMoveEdge.GetPosition()-this->m_position).VerticalComponent(this->m_vec)
						,afterEndVertical=(afterMoveEdge.GetEndPoint()-this->m_position).VerticalComponent(this->m_vec);
					//移動後の2点のどちらがが、moveVecVerticalに進んでいるかを判定して、それに対応したvertical成分を逆向きにして返してあげる
					if(moveVecVertical.Dot(afterBeginVertical)>moveVecVertical.Dot(afterEndVertical)){
						return -afterBeginVertical;
					} else{
						return -afterEndVertical;
					}
				}
				//const std::pair<bool,Vector2> crossInfo=CalculateCrossPoint(afterMoveEdge);
				//if(crossInfo.first){
				//	//交点が存在している時のみ、押し出し距離を計算する
				//	//線分上に乗せたい点がどちらか計算
				//	Vector2 onLinePoint=Vector2::s_zero;
				//	if(this->m_vec.Dot(moveVec)>0.0f){
				//		//moveVecとafterMoveEdgeの向きが同じ場合、afterMoveEdge.GetEndPoint()をthis上に乗せるようにする
				//		onLinePoint=afterMoveEdge.GetEndPoint();
				//	} else{
				//		//向きが逆なら、afterMoveEdge.m_positionをthis上に乗せようとする
				//		onLinePoint=afterMoveEdge.GetPosition();
				//	}
				//	//垂直方向のベクトルを求める
				//	const Vector2 slantFeedback=crossInfo.second-onLinePoint;//これのthisに垂直な成分を求めればよい
				//	return slantFeedback.VerticalComponent(this->m_vec);
				//}
			}
		} else if(kind==Kind::e_polygon){
			//線分と多角形
			return -moveShape->CalculateFeedback(this,-moveVec);//処理を移譲(ベクトルの向きに注意)
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
	//this->m_position=(x1,y1),this->m_vec=(x2,y2),otherobj.m_position=(x3,y3),otherobj.m_vec=(x4,y4)と置く。
	//(x2*y4-x4*y2)==0の時傾きが0なので平行である、この値は後で用いる
	const float inclination=this->m_vec.x*otherobj.m_vec.y-otherobj.m_vec.x*this->m_vec.y;
	if(inclination==0.0f){
		//平行の場合
		//同一直線上に存在するかの判定をする(2つのposition同士を結んだ直線とthisが平行かどうかで判定すればよい)
		//p1=this->GetPosition(),q1=this->GetEndPoint(),p2=otherobj.GetPosition(),q2=otherobj.GetEndPoint()である
		const Vector2 p1p2=otherobj.GetPosition()-this->GetPosition();
		if(m_vec.x*p1p2.y==p1p2.x*m_vec.y){
			//同一直線上にあった場合、内積を用いて判定
			const Vector2 p1q2=otherobj.GetEndPoint()-this->GetPosition();
			const Vector2 q1p2=otherobj.GetPosition()-this->GetEndPoint();
			const Vector2 q1q2=otherobj.GetEndPoint()-this->GetEndPoint();
			if(p1p2.Dot(m_vec)<0.0f && p1q2.Dot(m_vec)<0.0f){
				//pEdgeの両端点がthisのbeginよりm_vecと逆側にある時
				return std::make_pair(false,Vector2::s_zero);
			} else if(q1p2.Dot(m_vec)>0.0f && q1q2.Dot(m_vec)>0.0f){
				//pEdgeの両端点がthisのendよりm_vecと同じ側にある時
				return std::make_pair(false,Vector2::s_zero);
			} else{
				//ここは必ず交点を持つ、thisの端点のどちらかは必ずotherobj上に存在する
				Vector2 p=Vector2::s_zero;
				if(p1p2.Dot(p1q2)<0.0f){
					//p1がp2q2上（＝otherobj上）にある
					p=this->m_position;
				} else{
					p=this->GetEndPoint();
				}
				return std::make_pair(true,p);
			}
		}
	} else{
		//平行でない場合、直線の交点を求めてそれらが線分上に存在するかを求める
		//交点の座標は(x,y)=(x1,y1)+m*(x2,y2)=(x3,y3)+n*(x4,y4) (m,nはfloat)となる
		//0<=m,n<=1であれば交点が両線分上に存在することになる
		//方程式を解くと、m*(x2*y4-x4*y2)=y4*(x3-x1)-x4(y3-y1),n*(x2*y4-x4*y2)=y2*(x3-x1)-x2*(y3-y1)となる。
		const float m=(otherobj.m_vec.y*(otherobj.m_position.x-this->m_position.x)-otherobj.m_vec.x*(otherobj.m_position.y-this->m_position.y))/inclination;
		const float n=(this->m_vec.y*(otherobj.m_position.x-this->m_position.x)-this->m_vec.x*(otherobj.m_position.y-this->m_position.y))/inclination;
		return std::make_pair(m>=0.0f && m<=1.0f && n>=0.0f && n<=1.0f,this->m_position+this->m_vec*m);
	}
	return std::make_pair(false,Vector2::s_zero);
}
