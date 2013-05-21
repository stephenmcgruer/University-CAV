//! \author Stephen McGruer

#ifndef SRC_SKELETON_H_
#define SRC_SKELETON_H_

#include <vector>

#include "./bone.h"
#include "./vector3d-inl.h"

namespace computer_animation {

//! \class Skeleton
//! \brief Represents the skeleton that the model is rigged to.
class Skeleton {
  public:
    Skeleton() {
      // Intialize the hard-coded bone vector.
      init();
    }

    //! \brief Move the i-th bone to a position, using the CCD technique.
    //!
    //! Currently does not fully implement CCD. See the comments in the
    //! implementation for details.
    void CCDMoveBoneTo(int i, Vector3d<float> position);

    //! \brief Adjusts the rotation of the i-th bone.
    //!
    //! The given delta_rotation is added to the bone's current rotation.
    void AdjustBoneRotation(int i, Vector3d<int> delta_rotation);

    //! \brief Sets the skeleton's bones to those of another skeleton.
    Skeleton& operator=(const Skeleton &rhs);

    //! \brief Subtracts the skeleton's bones by those of another skeleton.
    Skeleton& operator-=(const Skeleton &rhs);

    //! \brief Subtracts one skeleton from another.
    const Skeleton operator-(const Skeleton &other) const;

    //! \brief Returns the i-th bone of the skeleton.
    inline Bone& GetBone(int i) { return bones_[i]; }

    //! \brief Returns the i-th bone of the skeleton.
    inline Bone GetBone(int i) const { return bones_[i]; }

    //! \brief Returns the number of bones in the skeleton.
    inline const int GetNumberBones() const { return bones_.size(); }

    //! \brief Resets the skeleton to it's rest position.
    //!
    //! In the rest position, all rotations are 0, and the current position
    //! is the same as the rest position.
    void Reset();

  private:
    //! \brief Initializes the links between bones.
    void init();

    std::vector<Bone> bones_;
    // The allowable error between a target point and the effector when
    // doing CCD.
    static const float kCCDDistanceThreshold = 0;

    // The maximum number of iterations performed when doing CCD.
    static const int kMaxCCDIterations = 1;
};
}

#endif  // SRC_SKELETON_H_
