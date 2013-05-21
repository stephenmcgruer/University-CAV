//! \author Stephen McGruer

#ifndef SRC_BONE_H_
#define SRC_BONE_H_

#include <vector>

#include "./matrix-inl.h"
#include "./vector3d-inl.h"

namespace computer_animation {

//! \class Bone
//! \brief Represents a bone in the skeleton.
//!
//! Bones are represented based on their child joint, and store both their
//! rest position and their current position.
class Bone {
  public:
    //! \brief Creates a new bone at the position (x, y, z).
    Bone(float x, float y, float z)
        : parent_(NULL), rest_position_(x, y, z), current_position_(x, y, z),
          rotation_(0, 0, 0) {
    }

    //! \brief Sets the current bone location to a position.
    void SetPosition(const Vector3d<float> &position);

    //! \brief Calculates the M matrix used in linear blending.
    //!
    //! The matrix is calculated by recursing back to the root node, and
    //! multiplying the R and T matrices down it.
    void CalculateM(Matrix<float> *f);

    //! \brief Returns the current position of the bone.
    const Vector3d<float> CurrentPosition() const { return current_position_; }

    //! \brief Returns the rest position of the bone.
    const Vector3d<float> RestPosition() const { return rest_position_; }

    //! \brief Returns the rotation at the child joint of the bone.
    const Vector3d<int>& Rotation() const { return rotation_; }

    //! \brief Sets the rotation at the child joint of the bone.
    void SetRotation(const Vector3d<int> &rotation) {
      rotation_[0] = rotation[0] % 360;
      rotation_[1] = rotation[1] % 360;
      rotation_[2] = rotation[2] % 360;
    }

    //! \brief Returns the parent of the bone.
    //!
    //! The parent bone is the one which has as it's child joint the parent
    //! joint of this bone. The root bone has no parent bone, as it has no
    //! parent joint.
    const Bone* Parent() const { return parent_; }

    //! \brief Sets the parent of the bone.
    //!
    //! The parent bone is the one which has as it's child joint the parent
    //! joint of this bone. The root bone has no parent bone, as it has no
    //! parent joint.
    void SetParent(Bone* bone) { parent_ = bone; }


    //! \brief Sets the current position and rotation to those of another bone.
    //!
    //! The rest position does not change.
    Bone& operator=(const Bone &rhs);

    //! \brief Subtracts the current position and rotation of another bone.
    //!
    //! The rest position does not change.
    Bone& operator-=(const Bone &rhs);

    //! \brief Compares the bone for inequality against another bone.
    //!
    //! Two bones are considered equal if they have the same rest position.
    bool operator!=(const Bone &rhs);

  private:
    Bone* parent_;
    Vector3d<float> rest_position_;
    Vector3d<float> current_position_;
    Vector3d<int> rotation_;  // The rotation in degrees around each axis.
};
}

#endif  // SRC_BONE_H_
