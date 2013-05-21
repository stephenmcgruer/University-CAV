//! \author Stephen McGruer

#ifndef SRC_VECTOR3D_INL_H_
#define SRC_VECTOR3D_INL_H_

#include "./vector3d.h"

#include <cmath>

namespace computer_animation {

template <typename T> float Vector3d<T>::DistanceTo(const Vector3d<T> &v)
    const {
  float squared_distance =
      (v[0] - coordinates_[0]) * (v[0] - coordinates_[0]) +
      (v[1] - coordinates_[1]) * (v[1] - coordinates_[1]) +
      (v[2] - coordinates_[2]) * (v[2] - coordinates_[2]);

  return std::sqrt(squared_distance);
}

template <typename T> void Vector3d<T>::Normalize() {
  float squared_length = coordinates_[0]*coordinates_[0] +
      coordinates_[1]*coordinates_[1] + coordinates_[2]*coordinates_[2];

  for (int i = 0; i < 3; i++) {
    coordinates_[i] /= std::sqrt(squared_length);
  }
}

template <typename T> Vector3d<T> CrossProduct(const Vector3d<T> &v1,
    const Vector3d<T> &v2) {
  int i;
  Vector3d<T> result;

  for (i = 0; i < 3; i++) {
    result.coordinates_[i] = v1[(i + 1) % 3] * v2[(i + 2) % 3] -
        v2[(i + 1) % 3] * v1[(i + 2) % 3];
  }

  return result;
}

template <typename T> Vector3d<T> operator+ (const Vector3d<T> &v1,
    const Vector3d<T> &v2) {
  Vector3d<T> result(v1);
  for (int i = 0; i < 3; i++) {
    result[i] += v2[i];
  }

  return result;
}

template <typename T> Vector3d<T> operator- (const Vector3d<T> &v1,
    const Vector3d<T> &v2) {
  Vector3d<T> result(v1);
  for (int i = 0; i < 3 ; i++) {
    result[i] -= v2[i];
  }

  return result;
}
}

#endif  // SRC_VECTOR3D_INL_H_
