//! \author Stephen McGruer

#include "./bone.h"

#include "./cav_utils.h"

namespace computer_animation {

void Bone::SetPosition(const Vector3d<float> &position) {
  current_position_ = position;
}

void Bone::CalculateM(Matrix<float> *f) {
  // If at the root, terminate by returning I.
  if (parent_ == NULL) {
    CreateIdentityMatrix(f);
    return;
  }

  Matrix<float> rotation(4, 4);
  Matrix<float> tmp(4, 4);

  // Rotations are carried out around the x-axis first, then the y-axis,
  // and finally around the z-axis.
  CreateIdentityMatrix(&rotation);
  CreateXRotMatrix(&tmp, rotation_[0]);
  rotation = rotation * tmp;
  CreateYRotMatrix(&tmp, rotation_[1]);
  rotation = rotation * tmp;
  CreateZRotMatrix(&tmp, rotation_[2]);
  rotation = rotation * tmp;

  Matrix<float> translation(4, 4);
  Vector3d<float> translation_vector =
      current_position_ - parent_->current_position_;
  CreateTranslationMatrix(&translation, translation_vector);

  Matrix<float> parent_M(4, 4);
  parent_->CalculateM(&parent_M);

  tmp = rotation * translation;

  *f = parent_M * tmp;
}


Bone& Bone::operator=(const Bone &rhs) {
  if (this == &rhs) {
    return *this;
  }

  current_position_ = rhs.current_position_;
  rotation_ = rhs.rotation_;

  return *this;
}

Bone& Bone::operator-=(const Bone &rhs) {
  current_position_ -= rhs.current_position_;
  rotation_ -= rhs.rotation_;

  return *this;
}

bool Bone::operator!=(const Bone &rhs) {
  return rest_position_ == rhs.rest_position_;
}
}
