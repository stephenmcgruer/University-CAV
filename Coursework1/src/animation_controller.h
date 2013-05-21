//! \author Stephen McGruer

#ifndef SRC_ANIMATION_CONTROLLER_H_
#define SRC_ANIMATION_CONTROLLER_H_

#include <vector>

#include "./skeleton.h"

namespace computer_animation {

//! \brief The target number of frames per second.
const int kFps = 25;

//! \brief The number of milliseconds per frame.
const int kMillisecondsPerFrame = 1000 / kFps;

//! \class AnimationController
//! \brief Loads animations from files and allows access to their frames.
//!
//! Animations are converted from a set of keyframes to a set of individual
//! frames, which can then be accessed by calling Frame(int i).
class AnimationController {
  public:
    //! \brief Loads in an animation from a file.
    //!
    //! The animation is converted from a set of keyframes stored in a file
    //! to a full set of kFps frames per second. Each keyframe in the file
    //! is a set of line which conform to:
    //!
    //! [bone_number] [rot_x] [rot_y] [rot_z]
    //!
    //! Keyframes are separated by the time that it should take to translate
    //! from the current keyframe to the next (in seconds):
    //!
    //! t [time]
    //!
    //! Only bones that are different from the rest position need to be
    //! specified in a keyframe. An empty keyframe is just the rest position.
    void LoadAnimation(const char* filename);

    //! \brief Returns the i-th frame of the current animation.
    inline Skeleton Frame(int i) const { return animation_.at(i); }

    //! \brief Returns the number of frames in the current animation.
    inline int NumberFrames() const { return animation_.size(); }

  private:
    std::vector<Skeleton> animation_;
};
}

#endif  // SRC_ANIMATION_CONTROLLER_H_
