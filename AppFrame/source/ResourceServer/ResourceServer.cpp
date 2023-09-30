/*
** ���\�[�X�T�[�o
*/

#include "DxLib.h"
#include "ResourceServer.h"

// �ÓI�����o����
ResourceServer::ResourceMap ResourceServer::_mapGraph;
ResourceServer::DivGraphMap ResourceServer::_textures;
ResourceServer::DIVGRAPHMAP ResourceServer::_mapDivGraph;
ResourceServer::ResourceMap ResourceServer::_mapSound;
ResourceServer::ResourceMap ResourceServer::_mapMV1Model;

void    ResourceServer::Init()
{
  _mapGraph.clear();
  _textures.clear();
  _mapDivGraph.clear();
  _mapSound.clear();
  _mapMV1Model.clear();
}

void    ResourceServer::Release()
{
  ClearGraph();
}

void ResourceServer::ClearGraph()
{
  // ���ׂẴf�[�^�̍폜������
  for( auto itr = _mapGraph.begin(); itr != _mapGraph.end(); itr++ )
  {
    DeleteGraph(itr->second);
  }
  _mapGraph.clear();

  for( auto&& dgm : _textures )
  {
    for( auto gh : dgm.second._handles )
    {
      DeleteGraph(gh);
    }
  }
  _textures.clear();

  for( auto itr = _mapDivGraph.begin(); itr != _mapDivGraph.end(); itr++ )
  {
    for( int i = 0; i < itr->second.AllNum; i++ )
    {
      DeleteGraph(itr->second.handle[i]);
    }
    delete[] itr->second.handle;
  }
  _mapDivGraph.clear();

  for( auto itr = _mapSound.begin(); itr != _mapSound.end(); itr++ )
  {
    DeleteSoundMem(itr->second);
  }
  _mapSound.clear();

  for( auto itr = _mapMV1Model.begin(); itr != _mapMV1Model.end(); itr++ )
  {
    MV1DeleteModel(itr->second);
  }
  _mapMV1Model.clear();
}

int ResourceServer::LoadGraph(std::string FileName)
{
  // �L�[�̌���
  auto itr = _mapGraph.find(FileName);
  if( itr != _mapGraph.end() )
  {
    // �L�[��������
    return itr->second;
  }
  // �L�[����������
  int cg = ::LoadGraph(FileName.c_str());     // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���
  // �L�[�ƃf�[�^��map�ɓo�^
  _mapGraph[FileName] = cg;

  return cg;
}

void ResourceServer::LoadTextures(const DivGraphMap& divGraphMap)
{
  for( auto&& dgm : divGraphMap )
  {
    auto& key = dgm.first;
    // �L�[����������
    auto it = _textures.find(key);
    if( it != _textures.end() )
    {
      continue;
    }
    // DivGraph���R�s�[����
    auto dg = dgm.second;
    auto allNum = dg._xNum * dg._yNum;
    dg._handles.resize(allNum);
    // �摜�̕����ǂݍ���
    LoadDivGraph(dg._filename.c_str(),
                 allNum,
                 dg._xNum,dg._yNum,
                 dg._xSize,dg._ySize,dg._handles.data());
    // DivGraphMap�ɒǉ�����
    _textures.emplace(key.c_str(),dg);
  }
}

int ResourceServer::GetHandles(const std::string& key,int no)
{
  auto it = _textures.find(key);
  if( it == _textures.end() )
  {
    return -1;
  }
  auto gh = it->second._handles.at(no);
  return gh;
}
bool ResourceServer::GetHandles(const std::string& key,std::vector<int>& handles)
{
  auto it = _textures.find(key);
  if( it == _textures.end() )
  {
    return false;
  }
  handles.resize(it->second._handles.size());
  handles = it->second._handles;
  return true;
}
int ResourceServer::GetAllNum(const std::string& key)
{
  auto it = _textures.find(key);
  if( it == _textures.end() )
  {
    return -1;
  }
  return it->second._xNum * it->second._yNum;
}

const DivGraph& ResourceServer::GetDivGraph(const std::string& key)
{
  auto it = _textures.find(key);
  return it->second;
}

int ResourceServer::LoadDivGraph(std::string FileName,int AllNum,int XNum,int YNum,int XSize,int YSize,int* HandleBuf)
{
  // �L�[�̌���
  auto itr = _mapDivGraph.find(FileName);
  if( itr != _mapDivGraph.end() )
  {
    // �L�[��������
    // �f�[�^���R�s�[
    for( int i = 0; i < itr->second.AllNum; i++ )
    {
      HandleBuf[i] = itr->second.handle[i];
    }
    return 0;
  }
  // �L�[����������
  // �܂��̓��������쐬����
  int* hbuf = new int[AllNum];
  int err = ::LoadDivGraph(FileName.c_str(),AllNum,XNum,YNum,XSize,YSize,hbuf);     // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���
  if( err == 0 )
  {
    // ����
    // �L�[�ƃf�[�^��map�ɓo�^
    _mapDivGraph[FileName].AllNum = AllNum;
    _mapDivGraph[FileName].handle = hbuf;
    // �f�[�^���R�s�[
    for( int i = 0; i < AllNum; i++ )
    {
      HandleBuf[i] = hbuf[i];
    }
  }

  return err;
}

int ResourceServer::LoadSoundMem(std::string FileName)
{
  // �L�[�̌���
  auto itr = _mapSound.find(FileName);
  if( itr != _mapSound.end() )
  {
    // �L�[��������
    return itr->second;
  }
  // �L�[����������
  // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���
  int snd = ::LoadSoundMem(FileName.c_str());
  // �L�[�ƃf�[�^��map�ɓo�^
  _mapSound[FileName] = snd;

  return snd;
}

int ResourceServer::LoadMV1Model(std::string FileName)
{
  int cg = 0;
  if( _mapMV1Model.count(FileName) == 0 )
  {
    //�L�[���Ȃ�����
    int cg = ::MV1LoadModel(FileName.c_str());
    _mapMV1Model[FileName] = cg;
  }
  cg = MV1DuplicateModel(_mapMV1Model[FileName]);
  return cg;
}