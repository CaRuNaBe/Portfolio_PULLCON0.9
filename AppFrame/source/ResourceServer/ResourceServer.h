#pragma once
#include <unordered_map>
#include<string>
#include <memory>
#include <vector>
// ���\�[�X�Ǘ��T�[�o
// ���ׂĐÓI�����o�ō\������
struct DIVGRAPH
{
  int AllNum;
  int* handle;
};
// �����ǂݍ���LoadDivGraph�p
struct DivGraph
{
  std::string _filename;
  int _xNum;
  int _yNum;
  int _xSize;
  int _ySize;
  std::vector<int> _handles;
};


class ResourceServer
{
public:
  using ResourceMap = std::unordered_map<std::string,int>;
  using DIVGRAPHMAP = std::unordered_map<std::string,DIVGRAPH>;
  using DivGraphMap = std::unordered_map<std::string,DivGraph>;
  static void Init();
  static void Release();
  static void ClearGraph();

  //�摜�ꊇ�ǂݍ���
  // div_graph_map DivGraphMap�e�[�u��
  static void LoadTextures(const DivGraphMap& div_graph_map);

  static int LoadGraph(std::string FileName);

  //�摜�n���h���̎擾
  static int GetHandles(const std::string& key,int no = 0);
  static bool GetHandles(const std::string& key,std::vector<int>& handles);
  static int GetAllNum(const std::string& key);
  static const DivGraph& GetDivGraph(const std::string& key);

  static int LoadDivGraph(std::string FileName,int AllNum,int XNum,int YNum,int XSize,int YSize,int* HandleBuf);

  static int LoadSoundMem(std::string FileName);

  static int LoadMV1Model(std::string FileName);
private:
  static DIVGRAPHMAP _mapDivGraph;
  static DivGraphMap _textures;
  static ResourceMap _mapGraph;
  static ResourceMap _mapSound;
  static ResourceMap _mapMV1Model;

};

