#pragma once
/*****************************************************************//**
 * \file   2dCollision.h
 * \brief  2dÕËm
 * 
 * \author ¢¾Y
 * \date   November 2022
 *********************************************************************/

#include "Math.h"
#include "vector2.h"
namespace math
{
  // ²½s«E{bNX(AABB:Axis-Aligned Bounding Boxj
  class AABB
  {
  public:
    Vector2 min;
    Vector2 max;
    void Draw(int red,int green,int blue) const;
  };

  // AABBÆAABBÌð·»è
  bool Intersect(const AABB& a,const AABB& b);

  // üª
  class LineSegment
  {
  public:
    Vector2 start;
    Vector2 end;
    void Draw(int red,int green,int blue) const;
  };
}