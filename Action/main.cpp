//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SDL.h"
#include "Game.h"

/*
�N���X���ł̐錾���Ԃ�public>protected>private>public(GetSet)�̏�
*/

/*
 @file ��.h
 @brief �ȒP�Ȑ���
	*/

	/*
	   @fn�����Ɋ֐��̐���������
	   @brief �v�����
	   @param ������ ����
	   @param ������ ����
	   @return �߂�l�̐���
	   @sa �Q�Ƃ��ׂ��֐��������΃����N���\���
	   @detail �ڍׂȐ���
	 */

/*
	@param ������ ����
*/

/*
  @fn
  @brief
*/

/*
  @fn
*/

/*
   @fn
   @brief
   @return
*/

/*
	 @enum Enum
	 ����
*/



//	@fn	main�֐�
//  @param  �R�}���h���C�������̐�
//  @param  �R�}���h���C������
int main(int argc, char** argv)
{
	Game game;
	//�Q�[���N���X�̒�`
	//�Q�[���N���X�̏�����������������
	bool success = game.Initialize();
	if (success)
	{
		game.GameLoop();
	}
	//�Q�[���N���X�̏I������
	game.Termination();

	return 0;
}