#include"Mouse.h"
#include"DxLib.h"

//-------------Mouse-------------
Input::Mouse Input::Mouse::s_mouse=Input::Mouse();//初期化

Input::Mouse::Mouse()
	:m_position(Geometry::Vector2Int::s_zero)
	,m_move(Geometry::Vector2Int::s_zero)
	,m_wheelRotation(0)
{
	//m_positionの初期化(しておかないと、初フレームのm_moveがおかしな値になる)
	UpdatePosition();
	//ボタン入力の初期化
	for(size_t i=0;i<buttonNum;i++){
		m_buttonFrame[i]=0;
		m_buttonCondition[i]=ButtonCondition::e_free;
	}	
}

void Input::Mouse::Update(){
	//位置関連の更新
	const Geometry::Vector2Int beforePos=m_position;//m_move計算用
	UpdatePosition();
	m_move=m_position-beforePos;
	//ボタン更新
	const int mouseInput=GetMouseInput();
	for(size_t i=0;i<buttonNum;i++){
		if(((mouseInput>>i) & 0x01)!=0){
			//押されていた
			m_buttonFrame[i]++;
			m_buttonCondition[i]=ButtonCondition::e_pushed;
		} else{
			//押されていない
			m_buttonFrame[i]=0;
			if(m_buttonCondition[i]==ButtonCondition::e_pushed){
				//前フレームでボタンが押されていたので離された瞬間だと分かる
				m_buttonCondition[i]=ButtonCondition::e_released;
			} else{
				m_buttonCondition[i]=ButtonCondition::e_free;
			}
		}
	}
	//ホイールの更新
	m_wheelRotation=GetMouseWheelRotVol();
}

Geometry::Vector2 Input::Mouse::GetPosition()const{
	return Geometry::ConvertToVector2(m_position);
}

Geometry::Vector2 Input::Mouse::GetMoveVector()const{
	return Geometry::ConvertToVector2(m_move);
}

size_t Input::Mouse::GetButtonInputFrame(int buttonCode)const{
	const size_t index=GetButtonIndex(buttonCode);
	if(index<buttonNum){
		return m_buttonFrame[index];
	} else{
		return 0;
	}
}

Input::Mouse::ButtonCondition Input::Mouse::GetButtonCondition(int buttonCode)const{
	const size_t index=GetButtonIndex(buttonCode);
	if(index<buttonNum){
		return m_buttonCondition[index];
	} else{
		return ButtonCondition::e_free;
	}
}

void Input::Mouse::UpdatePosition(){
	GetMousePoint(&m_position.x,&m_position.y);
}

size_t Input::Mouse::GetButtonIndex(int buttonCode)const{
	size_t index=0;
	for(;index<buttonNum;index++){
		//何個分右シフトすれば1が出現するかで配列番号を定義する
		if(((buttonCode>>index) & 0x01)!=0){
			break;
		}
	}
	return index;
}
