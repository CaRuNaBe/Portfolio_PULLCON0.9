
#include "appframe.h"
#include "ApplicationGlobal.h"

// ����
ApplicationGlobal gGlobal;
namespace
{
  const std::string IMAGE_ID_FILEPASS = "res/string_date/gamescript/ImageId.json";
  const std::string IMAGE_ID_ARRYNAME = "imageid";
  const std::string MUSIC_ID_FILEPASS = "res/string_date/gamescript/MusicId.json";
  const std::string MUSIC_ID_ARRYNAME = "musicid";
  const std::string OBJECT_ID_FILEPASS = "res/string_date/gamescript/ObjectId.json";
  const std::string OBJECT_ID_ARRYNAME = "ObjectId";

}
// �g�p����摜�t�@�C���̃e�[�u��
const ResourceServer::DivGraphMap usedInGame{
  {"effect_hit_player_frame",{ "res/2D_image/effect/fx_FrameAmmo.png",  8, 2, 512, 512 }},
  { "effect_spawn_ammo",   {"res/2D_image/effect/fx_SpawnAmmo.png",  3, 1, 512, 512} },
  { "effect_destroy_ammo",   {"res/2D_image/effect/fx_DestroyAmmo.png",  6, 2, 512, 512} },
  { "effect_hit_black_smoke",  {"res/2D_image/effect/fx_BlackSmoke.png", 3, 6, 512, 512} },
  { "effect_death_object",   {"res/2D_image/effect/fx_Boom.png",  8, 5, 512, 512} },
  { "effect_fire_player",  {"res/2D_image/effect/fx_PlayerDefaultFire.png", 3, 13, 512, 512} },
  { "effect_fire_gunship",  {"res/2D_image/effect/fx_GunShipFire.png", 2, 2, 512, 512} },
};

ApplicationGlobal::ApplicationGlobal()
{
  is_EndSpeakScript = true;
}

ApplicationGlobal::~ApplicationGlobal()
{}

bool ApplicationGlobal::Init()
{
  is_EndSpeakScript = true;
  // ��L�t�@�C����S�ēǂݍ���
  ResourceServer::LoadTextures(usedInGame);

  image_pass_date = std::make_shared<ScriptsData>();

  image_pass_date->LoadJson(IMAGE_ID_FILEPASS,IMAGE_ID_ARRYNAME);

  music_pass_date = std::make_shared<ScriptsData>();

  music_pass_date->LoadJson(MUSIC_ID_FILEPASS,MUSIC_ID_ARRYNAME);

  object_pass_date = std::make_shared<ScriptsData>();

  object_pass_date->LoadJson(OBJECT_ID_FILEPASS,OBJECT_ID_ARRYNAME);

  // SE�̎��O�ǂݍ���
  _se["pull"] = ResourceServer::LoadSoundMem("res/sound/AAA/�����������鉹/pull.wav");
  _se["AAA_death"] = ResourceServer::LoadSoundMem("res/sound/AAA/�΋�C�������S��/enemy_death.wav");
  _se["comm_start"] = ResourceServer::LoadSoundMem("res/sound/communication/communication_start.wav");
  _se["gunship_death"] = ResourceServer::LoadSoundMem("res/sound/gunship/gunship_explosion/gunship_explosion.wav");
  _se["player_object_crash"] = ResourceServer::LoadSoundMem("res/sound/player/�w���������ɏՓ˂��鉹/heli_object_crash.wav");
  _se["player_hovering"] = ResourceServer::LoadSoundMem("res/sound/player/�w���z�o�����O/heli_hovering.wav");
  _se["player_death"] = ResourceServer::LoadSoundMem("res/sound/player/�w�����S������/heli_death_explosion.wav");
  _se["player_pull_button"] = ResourceServer::LoadSoundMem("res/sound/player/�����������{�^����/pull_button_push.wav");
  _se["se_gunshot"] = ResourceServer::LoadSoundMem("res/sound/player/�e��/�ʏ�e/�ʏ�e���ˉ�/normal_bullet_fast.wav");
  _se["se_gunlanding"] = ResourceServer::LoadSoundMem("res/sound/player/�e��/�ʏ�e/�ʏ�e������/normal_bullet_hit.wav");
  _se["se_supply"] = ResourceServer::LoadSoundMem("res/sound/player/supply/supply.wav");

  return true;
}

