/*****************************************************************//**
 * \file   Vector4.h
 * \brief  3D�x�N�g���N���X��`
 * 
 * \author ���������Y
 * \date   November 2022
 *********************************************************************/
#pragma once
#include <limits>
#include <cmath>
namespace math
{
  class matrix44;

  class Vector4
  {
  public:
    /* ���� */
    float x;
    float y;
    float z;
    float w;
    // �R���X�g���N�^
    Vector4();
    Vector4(float x,float y,float z) : x(x),y(y),z(z),w(1.0)
    {}
    Vector4(float x,float y,float z,float w) : x(x),y(y),z(z),w(w)
    {}
    Vector4(int x,int y,int z) : x(static_cast<float>(x)),y(static_cast<float>(y)),z(static_cast<float>(z)),w(1.0)
    {}
    Vector4(int x,int y,int z,int w) : x(static_cast<float>(x)),y(static_cast<float>(y)),z(static_cast<float>(z)),w(static_cast<float>(w))
    {}
    Vector4(const Vector4&) = default; // �R�s�[
    Vector4(Vector4&&) = default; // ���[�u

    // �f�X�g���N�^
    virtual ~Vector4() = default;

    Vector4& operator =(const Vector4&) = default; // �R�s�[
    Vector4& operator =(Vector4&&) = default; // ���[�u

    // �x�N�g���̉��Z a + b
    const Vector4 operator +(const Vector4& rhs) const;
    // �x�N�g���̌��Z a - b
    const Vector4 operator -(const Vector4& rhs) const;
    // �x�N�g���̂����Z v * v
    const Vector4 operator *(const Vector4& rhs) const;
    // �x�N�g���̃X�J���[�{ v * scalar
    const Vector4 operator *(const float rhs) const;
    // �x�N�g���̃X�J���[��  v/scalar
    const Vector4 operator /(const float rhs) const;
    // �x�N�g�����Z���
    Vector4& operator+=(const Vector4& right);
    // �x�N�g�����Z���
    Vector4& operator-=(const Vector4& right);
    // �x�N�g���̃X�J����Z���
    Vector4& operator*=(float scalar);

    // �x�N�g���̍s��ϊ� �I�y���[�^
    const Vector4 operator *(const matrix44 rhs) const;
    // �x�N�g���̑傫��
    const float Lenght(const Vector4& second = { 0,0,0 }) const;
    // �x�N�g���̐��K��
    void Normalized();
    const Vector4 GetNormalize() const;
    // �x�N�g���̓���(Dot product) a�Eb
    const float Dot(const Vector4& rhs) const;
    // �x�N�g���̊O��(Cross product) a�~b
    const Vector4 Cross(const Vector4& rhs) const;

    const float GetX()const
    {
      return x;
    }
    const float GetY()const
    {
      return y;
    }
    const float GetZ()const
    {
      return z;
    }
    const float GetW()const
    {
      return w;
    }

    void SetX(const float& x)
    {
      this->x = x;
    }
    const float SetY(const float& y)
    {
      this->y = y;
    }
    const float SetZ(const float& z)
    {
      this->z = z;
    }
    const float SetW(const float& w)
    {
      this->w = w;
    }
  };
} // math
