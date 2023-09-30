#pragma once
//!
//! @file Collision.h
//!
//! @brief �Փˌ��m
//!
#include "Math.h"
#include "vector2.h"
namespace math
{
  // �����s���E�{�b�N�X(AABB:Axis-Aligned Bounding Box�j
  class AABB
  {
  public:
    Vector2 min;
    Vector2 max;
    void Draw(int red,int green,int blue) const;
  };

  // AABB��AABB�̌�������
  bool Intersect(const AABB& a,const AABB& b);

  // ����
  class LineSegment
  {
  public:
    Vector2 start;
    Vector2 end;
    void Draw(int red,int green,int blue) const;
  };
}