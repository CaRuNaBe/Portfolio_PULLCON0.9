#include "Dxlib.h"
#include "TitlePlayer.h"


TitlePlayer::TitlePlayer( ApplicationBase& game,int layer,ModeTitle& mode )
  : ActorTitle( game,layer,mode )
{
  cg_player = ResourceServer::LoadGraph( "res/2D_image/title/cg_Heli.png" );
  cg_ui[0] = ResourceServer::LoadGraph( "res/2D_image/title/ui_push_guide_1.png" );
  cg_ui[1] = ResourceServer::LoadGraph( "res/2D_image/title/ui_push_guide_3.png" );
  cg_ui[2] = ResourceServer::LoadGraph( "res/2D_image/title/ui_push_guide_3.png" );
  cg_ui[3] = ResourceServer::LoadGraph( "res/2D_image/title/ui_push_guide_3.png" );

  Initialize();
}

TitlePlayer::~TitlePlayer()
{}

void TitlePlayer::Initialize()
{
  ActorTitle::Initialize();

  // �v���C���[���̏�����
  _pos = {static_cast<float>(math::utility::get_random( 0,1920 )),static_cast<float>(math::utility::get_random( 0,1000 ))};//�����_���̈ʒu�ɃX�|�[��
  _size = {180.0f,175.0f};//�I�u�W�F�N�g�̃T�C�Y��`
  _colPos.x = 0.0f;
  _colPos.y = 0.0f;
  _colSize.x = 180.0f;
  _colSize.y = 175.0f;
  _spd = 8;
  waitTime = 0;
  auto juge = static_cast<int>(math::utility::get_random( 0,1 ));//�����_���̒l���擾
  if ( juge % 2 == 0 )
  {
    isRight = true;//2�Ŋ���؂ꂽ��E����
  }
  else
  {
    isRight = false;//�ȊO�͍�����
  }
  isUidraw = false;//ui��\��
  PlayerState = State::MOVE;//�����Ă���ɏ�����
}

bool TitlePlayer::Update()
{
  ActorTitle::Update();
  // �L�[���͂𔻒肵�āA��l�����ړ�������
  // Vector2�𗘗p���Ď΂߈ړ��ł����Ȃ��悤��
  math::Vector2 dir = {_game.Getinput().GetLstickX(),-(_game.Getinput().GetLstickY())};// �������w��

  if ( dir.x != 0 || dir.y != 0 )
  {
    dir.Normalized();// �������m�[�}���C�Y

  }

  if ( dir.x > 0.f )
  {
    isRight = true;
  }
  if ( dir.x < 0.f )
  {
    isRight = false;
  }


  // ��ʂ̊O�ɏo�Ȃ��悤�ɂ���
  if ( _pos.x < 0 )
  {
    _pos.x = 0;
  }
  if ( _pos.x + _size.x > _game.DispSizeW() )
  {
    _pos.x = _game.DispSizeW() - _size.x;
  }
  if ( _pos.y < 0 )
  {
    _pos.y = 0;
  }
  if ( _pos.y + _size.y > _game.DispSizeH() )
  {
    _pos.y = _game.DispSizeH() - _size.y;
  }

  isUidraw = false;

  for ( auto&& obje : _mode.Get2DobjectServer().GetObjects() )
  {
    if ( (obje->GetType() == ActorTitle::Type::KGAMESTARTLOGO) || (obje->GetType() == ActorTitle::Type::KCREDITLOGO) || (obje->GetType() == ActorTitle::Type::KENDLOGO) )
    {
      if ( IsHitObject( *obje ) )
      {
        isUidraw = true;
        if ( !isRight )
        {
          if ( _game.Getinput().GetKeyXinput( XINPUT_BUTTON_X ) )
          {
            dir = {0,0};
            _pos.x = obje->GetPosition().x + 10.0f;
            _pos.y = obje->GetPosition().y - 130.0f;
            waitTime = 15;
          }
        }
        if ( isRight )
        {
          if ( _game.Getinput().GetKeyXinput( XINPUT_BUTTON_X ) )
          {
            dir = {0,0};
            _pos.x = obje->GetPosition().x - 100.0f;
            _pos.y = obje->GetPosition().y - 130.0f;
            waitTime = 15;
          }
        }
      }
    }
  }
  if ( waitTime > 0 )
  {
    PlayerState = State::WAIT;
  }
  switch ( PlayerState )
  {
    case  State::MOVE:
      dir *= _spd;// �m�[�}���C�Y���������ɑ��x��������
      _pos += dir;// �ʒu�𓮂��� ;
      break;
    case State::WAIT:
      waitTime--;
      if ( waitTime < 0 )
      {
        waitTime = 0;
        PlayerState = State::MOVE;
      }
      break;

    default:
      dir *= _spd;// �m�[�}���C�Y���������ɑ��x��������
      _pos += dir;// �ʒu�𓮂��� ;
  }

  UpdateCollision();// �R���W�����X�V
  return true;
}

bool TitlePlayer::Draw()
{
  ActorTitle::Draw();
  if ( !isRight )
  {
    DrawGraph( _pos.IntX(),_pos.IntY(),cg_player,TRUE );
  }
  else
  {
    DrawTurnGraph( _pos.IntX(),_pos.IntY(),cg_player,TRUE );
  }

  if ( isUidraw )
  {
    const math::Vector2 UISIZE = {150,66};
    math::Vector2 uiposi = {(_pos.x) - (UISIZE.x),_pos.y};

    if ( uiposi.x < 0.0f )
    {
      uiposi.x = 0.0f;
    }
    if ( uiposi.x + UISIZE.x > _game.DispSizeW() )
    {
      uiposi.x = static_cast <float>(_game.DispSizeW()) - uiposi.x;
    }
    if ( uiposi.y < 0.0f )
    {
      uiposi.y = 0.0f;
    }
    if ( uiposi.y + UISIZE.y > static_cast <float>(_game.DispSizeH()) )
    {
      uiposi.y = _game.DispSizeH() - UISIZE.y;
    }
    DrawTurnGraph( uiposi.IntX(),uiposi.IntY(),cg_ui[_cnt % cg_ui.size()],TRUE );
  }

#if _DEBUG//�f�o�b�O�\��
  int x = 0,y = 0,size = 16;
  SetFontSize( size );
  //DrawFormatString( x,y,GetColor( 255,0,0 ),"Camera:" ); y += size;
  //DrawFormatString( x,y,GetColor( 255,0,0 ),"  target = (%5.2f, %5.2f, %5.2f)",_cam._vTarget.x,_cam._vTarget.y,_cam._vTarget.z ); y += size;
  DrawFormatString( x,y,GetColor( 255,0,0 ),"  pos    = (%5.2f, %5.2f)",_pos.x,_pos.y ); y += size;
#endif
  DrawCollision();// �R���W�����`��
  return true;
}