/*****************************************************************//**
 * \file   2dCollision.cpp
 * \brief  �Փˌ��m
 * 
 * \author ���������Y
 * \date   November 2022
 *********************************************************************/

#include "2dCollision.h"
#include "DxLib.h"

namespace math
{
  // AABB�̌�������
  bool Intersect(const AABB& a,const AABB& b)
  {
    // ������ł�true�Ȃ�������Ă��Ȃ�
    if( a.max.x < b.min.x )
    {
      return false;
    }
    if( b.max.x < a.min.x )
    {
      return false;
    }
    if( a.max.y < b.min.y )
    {
      return false;
    }
    if( b.max.y < a.min.y )
    {
      return false;
    }
    return true;

    // �ȉ��̂悤�ɒZ�k�����L�q������
    //bool no = a.max.x < b.min.x ||
    //b.max.x < a.min.x ||
    //a.max.y < b.min.y ||
    //b.max.y < a.min.y;
    //return !no;
  }

  // AABB�̕`��
  void AABB::Draw(int red,int green,int blue) const
  {
    DrawBoxAA(min.x,min.y,max.x,max.y,GetColor(red,green,blue),FALSE);
  }

  // �����̕`��
  void LineSegment::Draw(int red,int green,int blue) const
  {
    DrawLineAA(start.x,start.y,end.x,end.y,GetColor(red,green,blue),5);
  }
}