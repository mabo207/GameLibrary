#pragma once

#include"Vector2.h"
#include<memory>

namespace Geometry{
	//図形を表現するクラス
	class Shape{
	public:
		//図形の種類
		enum class Kind{
			e_circle
			,e_edge
			,e_polygon
		};

		//関数
		void Resize(float rate);//rate倍だけ拡大する
		void Move(const Vector2 &moveVec);//現在位置からmoveVecだけ移動する
		void Warp(const Vector2 &position);//positionへ移動する
		void Draw(unsigned int color,int fillFlag,float lineThickness)const;//描画
		Kind GetKind()const{
			return m_kind;
		}
		Vector2 GetPosition()const{
			return m_position;
		}

		//純粋仮想関数
		virtual std::shared_ptr<Shape> Copy()const=0;//中身が同じでポインタが異なる図形を返す
		virtual bool JudgeCross(const Shape *otherShape)const=0;//重なっているかどうかを判定する
		virtual bool JudgeInThis(const Shape *otherShape)const=0;//内部に入っているかどうかを判定する
		virtual bool JudgePointIn(const Vector2 &pointPos)const=0;//点が内部に入っているかどうかを判定する
		virtual Vector2 CalculateFeedback(const Shape *moveShape,const Vector2 &moveVec)const=0;//moveShapeがmoveVecだけ移動しようとしている時に、この図形に当たって押し返すベクトルを計算する
		virtual void Resize(const Vector2 &v)=0;//基準となるベクトルをvになるように変形させる
		virtual Vector2 GetResizeBaseVector()const=0;//現在の図形における、Resize(Vector2)の基準ベクトルを返す
		virtual void Draw(const Vector2 &position,unsigned int color,int fillFlag,float lineThickness)const=0;//描画
		virtual Vector2 GetLeftTop()const=0;//左上の座標を返す
		virtual Vector2 GetRightButtom()const=0;//右下の座標を返す

	protected:
		Shape(Kind kind,const Vector2 &position);
		virtual ~Shape()=default;

		//変数
		Vector2 m_position;//図形の位置
		Kind m_kind;//図形の種類
	};
}