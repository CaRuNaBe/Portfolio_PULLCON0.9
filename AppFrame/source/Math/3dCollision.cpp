/*****************************************************************//**
 * \file   3dCollision.h
 * \brief  3d衝突検知
 *
 * \author 中田瑞希
 * \date   November 2023
 *********************************************************************/
#include "3dCollision.h"
#include "DxLib.h"

namespace math
{
  // AABBの交差判定
  bool Intersect(const Sphere& a,const Sphere& b)
  {
    float x = a._vCenter.x - b._vCenter.x;
    float y = a._vCenter.y - b._vCenter.y;
    float z = a._vCenter.z - b._vCenter.z;
    float r = x * x + y * y + z * z;//球同士の距離を求める
    float sum_radius = a._fRadius + b._fRadius;

    if( r <= sum_radius * sum_radius )
    {
      return true;//当たってる
    }

    return false;//外れてる

  }

  // Sphereの描画
  void Sphere::Draw(int red,int green,int blue) const
  {
    Vector4 Center = { _vCenter.x, _vCenter.y, _vCenter.z };
    DrawSphere3D(ToDX(Center),_fRadius,8,GetColor(red,green,blue),GetColor(0,0,0),FALSE);
  }
  // Sphereの描画
  void Sphere::DrawObject(int red,int green,int blue) const
  {
    Vector4 Center = { _vCenter.x, _vCenter.y, _vCenter.z };
    DrawSphere3D(ToDX(Center),_fRadius,64,GetColor(red,green,blue),GetColor(0,0,0),FALSE);
  }

}