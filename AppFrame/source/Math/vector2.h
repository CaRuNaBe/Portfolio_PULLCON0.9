#pragma once
#include<cmath>
#include <limits>
namespace math
{
  class Matrix3;
  // 2D�x�N�g���N���X
  class Vector2
  {
  public:
    // x����,y����
    float x;
    float y;

    // �R���X�g���N�^
    Vector2() noexcept = default;
    constexpr Vector2(float ax,float ay) noexcept : x { ax },y { ay }
    {}

    constexpr Vector2(int ax,int ay) noexcept : x { static_cast<float>(ax) },y { static_cast<float>(ay) }
    {}
    Vector2(const Vector2&) = default; // �R�s�[
    Vector2(Vector2&&) = default; // ���[�u

    int IntX()
    {
      return static_cast<int>(x);
    }

    int IntY()
    {
      return static_cast<int>(y);
    }

    void Set(Vector2 vec2)
    {
      x = vec2.x;
      y = vec2.y;
    }

    Vector2& operator =(const Vector2&) = default; // �R�s�[
    Vector2& operator =(Vector2&&) = default; // ���[�u
    // �x�N�g���̉��Z a + b ���O���֐�
    const Vector2 operator+(const Vector2& rhs)const;
    // �x�N�g���̌��Z a - b ���O���֐�
    const Vector2 operator-(const Vector2& rhs)const;
    // �x�N�g���̃X�J���[�{ v * scalar ���O���֐�
    const Vector2 operator*(float rhs)const;
    // �x�N�g���̃X�J���[��  v/scalar ���O���֐�
    const Vector2 operator/(float rhs)const;

    // �x�N�g�����Z���
    Vector2& operator+=(const Vector2& right);

    // �x�N�g�����Z���
    Vector2& operator-=(const Vector2& right);

    // �x�N�g���̃X�J����Z���
    Vector2& operator*=(float scalar);

    // �x�N�g����r
    bool operator==(const Vector2& b) const;
    bool operator!=(const Vector2& b) const;

    // �x�N�g���̑傫��
    float Length(const Vector2& backvec = { 0,0 }) const;

    // �x�N�g���̐��K��
    void Normalized();
    const Vector2 GetNormalize()const;

    // �x�N�g���̓���(Dot product) a�Eb
    float Dot(const Vector2& multiplicator)const;

    // �x�N�g���̊O��(Cross product) a�~b
    float Cross(const Vector2& multiplicator)const;
    // �x�N�g���̍s��ϊ�
    static Vector2 Transform(const Vector2& vec,const class Matrix3& mat,float w = 1.0f);

    Vector2 GetCentor(const Vector2& right);
  };
}