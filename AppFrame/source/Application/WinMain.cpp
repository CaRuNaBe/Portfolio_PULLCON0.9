/*****************************************************************//**
 * \file   WinMain.cpp
 * \brief  エントリーポイント
 * 
 * \author 阿部健太郎
 * \date   November 2022
 *********************************************************************/

#include "../appframe.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
  // Log出力を行わない
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

  // 1フレームループを組む
  while( ProcessMessage() == 0 )// プログラムが終了するまでループ
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
