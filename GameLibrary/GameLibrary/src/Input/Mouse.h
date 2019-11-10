#pragma once

#include"Geometry/Vector2.h"
#include<array>

namespace Input{
	//マウスを表現する関数
	class Mouse{
	public:
		//構造体
		enum class ButtonCondition{
			e_free//押されていないかつe_releasedでない
			,e_pushed//押されている
			,e_released//離された瞬間である
		};

		//関数
		Mouse();
		~Mouse()=default;
		void Update();//変数の更新
		//現在のマウスの位置の取得
		Geometry::Vector2 GetPosition()const;
		Geometry::Vector2Int GetPositionInt()const{
			return m_position;
		}
		//現フレームでのマウスがどのように移動したかを2次元ベクトルで取得
		Geometry::Vector2 GetMoveVector()const;
		Geometry::Vector2Int GetMoveVectorInt()const{
			return m_move;
		}
		//現フレームでマウスホイールがどのように移動したかを取得
		int GetWheelRotation()const{
			//>0:上に回した <0:下に回した
			return m_wheelRotation;
		}
		//マウスボタンに関する関数
		size_t GetButtonInputFrame(int buttonCode)const;//マウスのボタンが何フレーム押し続けられたかを取得
		ButtonCondition GetButtonCondition(int buttonCode)const;//マウスのボタンの状態

		//静的変数
		static Mouse s_mouse;//プログラムが実行されているコンピュータに接続されているマウス（１つだけ）

	private:
		//関数
		void UpdatePosition();//位置を更新する処理は2箇所出てくるため関数化しておく
		size_t GetButtonIndex(int buttonCode)const;//ボタンコードから配列番号を取得するための関数(ボタンコードはシフト演算に都合の良い変数が割り当てられていてキレイに配列番号順にならない)
		//定数
		static const size_t buttonNum=8;
		//変数
		Geometry::Vector2Int m_position;//位置
		Geometry::Vector2Int m_move;//移動ベクトル
		std::array<size_t,buttonNum> m_buttonFrame;//ボタンの入力フレーム
		std::array<ButtonCondition,buttonNum> m_buttonCondition;//ボタンの状態
		int m_wheelRotation;//ホイールの回転量
	};
}
