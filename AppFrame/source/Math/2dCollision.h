#pragma once
/*****************************************************************//**
 * \file   2dCollision.h
 * \brief  2d衝突検知
 * 
 * \author 阿部健太郎
 * \date   November 2022
 *********************************************************************/

#include "Math.h"
#include "vector2.h"
namespace math
{
  // 軸平行境界ボックス(AABB:Axis-Aligned Bounding Box）
  class AABB
  {
  public:
    Vector2 min;
    Vector2 max;
    void Draw(int red,int green,int blue) const;
  };

  // AABBとAABBの交差判定
  bool Intersect(const AABB& a,const AABB& b);

  // 線分
  class LineSegment
  {
  public:
    Vector2 start;
    Vector2 end;
    void Draw(int red,int green,int blue) const;
  };
}