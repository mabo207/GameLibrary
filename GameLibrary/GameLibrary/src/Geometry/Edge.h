#pragma once

#include"Shape.h"

namespace Geometry{
	//線分を表現するクラス
	class Edge:public Shape{
	public:
		//関数
		Edge(const Vector2 &position,const Vector2 &vector);//始点と線の伸びる方向で構成
		~Edge()=default;
		Vector2 GetVector()const{
			return m_vec;
		}
		Vector2 GetEndPoint()const{
			return m_position+m_vec;
		}
		//仮想関数のオーバーライド
		std::shared_ptr<Shape> Copy()const;//中身が同じでポインタが異なる図形を返す
		bool JudgeCross(const Shape *otherShape)const;//重なっているかどうかを判定する
		bool JudgeInThis(const Shape *otherShape)const;//内部に入っているかどうかを判定する
		bool JudgePointIn(const Vector2 &pointPos)const;//点が内部に入っているかどうかを判定する
		Vector2 CalculateFeedback(const Shape *moveShape,const Vector2 &moveVec)const;//moveShapeがmoveVecだけ移動しようとしている時に、この図形に当たって押し返すベクトルを計算する
		void Resize(const Vector2 &v);//基準となるベクトルをvになるように変形させる
		Vector2 GetResizeBaseVector()const;//現在の図形における、Resize(Vector2)の基準ベクトルを返す
		void Draw(const Vector2 &position,unsigned int color,int fillFlag,float lineThickness)const;//描画
		Vector2 GetLeftTop()const;//左上の座標を返す
		Vector2 GetRightButtom()const;//右下の座標を返す
		//静的関数
		static Edge CreateWith2Point(const Vector2 &begin,const Vector2 &end){
			return Edge(begin,end-begin);
		}

	private:
		//関数
		std::pair<bool,Vector2> CalculateCrossPoint(const Edge &otherobj)const;//thisとotherobjが交点を持つか判定し、持っている場合は交点も求める

		//変数
		Vector2 m_vec;
	};
}