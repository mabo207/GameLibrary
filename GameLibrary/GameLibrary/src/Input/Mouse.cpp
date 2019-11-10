#include"Mouse.h"
#include"DxLib.h"

//-------------Mouse-------------
Input::Mouse Input::Mouse::s_mouse=Input::Mouse();//������

Input::Mouse::Mouse()
	:m_position(Geometry::Vector2Int::s_zero)
	,m_move(Geometry::Vector2Int::s_zero)
	,m_wheelRotation(0)
{
	//m_position�̏�����(���Ă����Ȃ��ƁA���t���[����m_move���������Ȓl�ɂȂ�)
	UpdatePosition();
	//�{�^�����͂̏�����
	for(size_t i=0;i<buttonNum;i++){
		m_buttonFrame[i]=0;
		m_buttonCondition[i]=ButtonCondition::e_free;
	}	
}

void Input::Mouse::Update(){
	//�ʒu�֘A�̍X�V
	const Geometry::Vector2Int beforePos=m_position;//m_move�v�Z�p
	UpdatePosition();
	m_move=m_position-beforePos;
	//�{�^���X�V
	const int mouseInput=GetMouseInput();
	for(size_t i=0;i<buttonNum;i++){
		if(((mouseInput>>i) & 0x01)!=0){
			//������Ă���
			m_buttonFrame[i]++;
			m_buttonCondition[i]=ButtonCondition::e_pushed;
		} else{
			//������Ă��Ȃ�
			m_buttonFrame[i]=0;
			if(m_buttonCondition[i]==ButtonCondition::e_pushed){
				//�O�t���[���Ń{�^����������Ă����̂ŗ����ꂽ�u�Ԃ��ƕ�����
				m_buttonCondition[i]=ButtonCondition::e_released;
			} else{
				m_buttonCondition[i]=ButtonCondition::e_free;
			}
		}
	}
	//�z�C�[���̍X�V
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
		//�����E�V�t�g�����1���o�����邩�Ŕz��ԍ����`����
		if(((buttonCode>>index) & 0x01)!=0){
			break;
		}
	}
	return index;
}
