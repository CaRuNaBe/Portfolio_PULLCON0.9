#include "Vector2.h"
#include "matrix33.h"
namespace math
{
  // �x�N�g���̉��Z a + b ���O���֐�
  const Vector2 Vector2::operator+(const Vector2& rhs)const
  {
    return Vector2(x + rhs.x,y + rhs.y);
  }
  // �x�N�g���̌��Z a - b ���O���֐�
  const Vector2 Vector2::operator-(const Vector2& rhs)const
  {
    return Vector2(x - rhs.x,y - rhs.y);
  }
  // �x�N�g���̃X�J���[�{ v * scalar ���O���֐�
  const Vector2 Vector2::operator*(float rhs)const
  {
    return { x * rhs, y * rhs };
  }
  // �x�N�g���̃X�J���[��  v/scalar ���O���֐�
  const Vector2 Vector2::operator/(float rhs)const
  {
    return { x / rhs, y / rhs };
  }

  // �x�N�g�����Z���
  Vector2& Vector2::operator+=(const Vector2& right)
  {
    x += right.x;
    y += right.y;
    return *this;
  }

  // �x�N�g�����Z���
  Vector2& Vector2::operator-=(const Vector2& right)
  {
    x -= right.x;
    y -= right.y;
    return *this;
  }

  // �x�N�g���̃X�J����Z���
  Vector2& Vector2::operator*=(float scalar)
  {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  // �x�N�g����r
  bool Vector2::operator==(const Vector2& b) const
  {
    if( x == b.x && y == b.y )
    {
      return true;
    }
    return false;
  }
  bool Vector2::operator!=(const Vector2& b) const
  {
    return !(*this == b);
  }

  // �x�N�g���̑傫��
  float Vector2::Length(const Vector2& backvec) const
  {
    Vector2 vec = { x - backvec.x,y - backvec.y };
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
  }

  // �x�N�g���̐��K��
  void Vector2::Normalized()
  {
    auto length = Length();

    // �덷�����Ȃ�[���Ƃ݂Ȃ��B
    if( std::abs(length) < std::numeric_limits<float>::epsilon() )
    {
      x = 0.0;
      y = 0.0;
    } else
    {
      x /= length;
      y /= length;
    }
  }
  const Vector2 Vector2::GetNormalize()const
  {
    auto len = Length();
    auto nx = 0.0f;
    auto ny = 0.0f;
    // �덷�����Ȃ�[���Ƃ݂Ȃ��B
    if( std::abs(len) < std::numeric_limits<float>::epsilon() )
    {
      nx = 0.0f;
      ny = 0.0f;
    } else
    {
      nx = x / len;
      ny = y / len;
    }
    return Vector2(nx,ny);
  }

  // �x�N�g���̓���(Dot product) a�Eb
  float Vector2::Dot(const Vector2& multiplicator)const
  {
    return (x * multiplicator.x + y * multiplicator.y);
  }

  // �x�N�g���̊O��(Cross product) a�~b
  float Vector2::Cross(const Vector2& multiplicator)const
  {
    return (x * multiplicator.y - y * multiplicator.x);
  }

  // �x�N�g���̍s��ϊ�
  Vector2 Vector2::Transform(const Vector2& vec,const Matrix3& mat,float w)
  {
    return {
      vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + w * mat.m[2][0],
      vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + w * mat.m[2][1],
    };
  }

  Vector2 Vector2::GetCentor(const Vector2& right)
  {
    float x2 = ((x * 2.0f) + right.x) / 2.0f;
    float y2 = ((y * 2.0f) + right.y) / 2.0f;
    Vector2 vec = { x2,y2 };
    return vec;
  };
}