/*****************************************************************//**
 * \file   WinMain.cpp
 * \brief  �G���g���[�|�C���g
 * 
 * \author ���������Y
 * \date   November 2022
 *********************************************************************/

#include "../appframe.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
  // Log�o�͂��s��Ȃ�
  SetOutApplicationLogValidFlag(FALSE);
  auto appBase = ApplicationBase::GetInstance();
  if( !appBase )
  {
    return 0;
  }

  if( !appBase->Initialize(hInstance) )
  {
    return 0;
  }

  // 1�t���[�����[�v��g��
  while( ProcessMessage() == 0 )// �v���O�������I������܂Ń��[�v
  {
    appBase->Input();

    if( !appBase->Update() )
    {
      break;
    };

    appBase->Draw();
  }

  appBase->Terminate();

  return 0;
}
