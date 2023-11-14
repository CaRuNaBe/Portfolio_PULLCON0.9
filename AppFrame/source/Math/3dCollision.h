#pragma once
/*****************************************************************//**
 * \file   3dCollision.h
 * \brief  3d�Փˌ��m
 * 
 * \author ���c����
 * \date   November 2023
 *********************************************************************/

#include "Math.h"
#include "Vector4.h"
namespace math
{
  // ��
  class Sphere
  {
  public:
    void SetSphere(Vector4 pos,float r)
    {
      _vCenter = pos,_fRadius = r;
    }

    Vector4 _vCenter;
    float   _fRadius;
    void Draw(int red,int green,int blue) const;
    void DrawObject(int red,int green,int blue) const;
  };

  // Sphere��Sphere�̌�������
  bool Intersect(const Sphere& a,const Sphere& b);


}
