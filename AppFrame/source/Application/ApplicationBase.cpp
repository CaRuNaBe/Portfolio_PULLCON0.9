/*****************************************************************//**
 * \file   ApplicationBase.h
 * \brief �A�v���P�[�V�������N���X�錾
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#include "ApplicationBase.h"

ApplicationBase* ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase()
{
  _lpInstance = this;
  font_hundle = 0;
  font_size = 29;
}

ApplicationBase::~ApplicationBase()
{}

bool ApplicationBase::Initialize(HINSTANCE hInstance)
{
#if _DEBUG
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
  // DX���C�u�����̏�����
  if( AppWindowed() )
  {
    ChangeWindowMode(true);// �E�B���h�E���[�h�Ɏw�肷��
  }
  SetZBufferBitDepth(32);
  SetGraphMode(DispSizeW(),DispSizeH(),32);


  if( DxLib_Init() == -1 )
  {
    // �G���[���N�����璼���ɏI��
    return false;
  }
  SetDrawScreen(DX_SCREEN_BACK);// �`����ʂ𗠉�ʂɃZ�b�g

  // �y�o�b�t�@��L���ɂ���
  SetUseZBuffer3D(TRUE);

  // �y�o�b�t�@�ւ̏������݂�L���ɂ���
  SetWriteZBuffer3D(TRUE);

  // ���[�h�T�[�o�̏�����
  _BaseServer = std::make_shared<GameServerShared<GameBase>>();

  font_hundle = 0;
  font_size = 29;
  is_game_end = false;
  return true;
}

bool ApplicationBase::Terminate()
{
  InitFontToHandle();
  // DX���C�u�����J��
  DxLib_End();

  return true;
}


bool ApplicationBase::Input()
{
  _input.Update();
  return true;
}

bool ApplicationBase::Update()
{
  _BaseServer->Update();
  return true;
}


bool ApplicationBase::Draw()
{
  ClearDrawScreen();// ��ʂ�����������
  _BaseServer->Draw();
  ScreenFlip();// ����ʂ̓��e��\��ʂɔ��f������
  return true;
}
