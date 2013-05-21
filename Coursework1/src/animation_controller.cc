//! \author Stephen McGruer

#include "./animation_controller.h"

#include <cstdio>
#include <cstring>

namespace computer_animation {

void AnimationController::LoadAnimation(const char* filename) {
  FILE *f;
  f = fopen(filename, "r");

  if (f == NULL) {
    fprintf(stderr, "Error: Failed reading animation file %s\n", filename);
    return;
  }

  char buf[1024];
  char header[100];
  float time;
  int bone;
  int rx, ry, rz;

  std::vector<Skeleton> keyframes;
  std::vector<float> times;
  Skeleton skeleton;
  while (fgets(buf, sizeof(buf), f) != NULL) {
    if (buf[0] == 't') {
      // This is safe as buf is a bounded-size input.
      sscanf(buf, "%s %f", header, &time);
      times.push_back(time);

      // New frame.
      keyframes.push_back(skeleton);
      skeleton = Skeleton();
    } else {
      // New bone.

      // This is safe as buf is a bounded-size input.
      sscanf(buf, "%d %d %d %d", &bone, &rx, &ry, &rz);

      skeleton.AdjustBoneRotation(bone, Vector3d<int>(rx, ry, rz));
    }
  }
  keyframes.push_back(skeleton);
  fclose(f);

  // Now calculate the frames from the keyframes, using linear interpolation.
  animation_.clear();
  for (unsigned int i = 0; i < times.size(); i++) {
    // Calculate the difference between the frames.
    Skeleton difference = keyframes.at(i + 1) - keyframes.at(i);

    // Keyframes i and i+1 are linked by (time_between_keyframes *
    // frames_per_second) normal frames.
    int num_frames = times.at(i) * kFps;

    // Scale the difference by the number of frames.
    int num_bones = difference.GetNumberBones();
    for (int bone = 0; bone < num_bones; bone++) {
      Vector3d<int> rotation = difference.GetBone(bone).Rotation();
      rotation /= num_frames;
      difference.GetBone(bone).SetRotation(rotation);
    }

    // Add the frames to the animation.
    for (int frame = 0; frame < num_frames; frame++) {
      Skeleton tmp = keyframes.at(i);
      for (int bone = 0; bone < num_bones; bone++) {
        Vector3d<int> rotation_delta = difference.GetBone(bone).Rotation();
        rotation_delta *= (frame + 1);

        tmp.AdjustBoneRotation(bone, rotation_delta);
      }
      animation_.push_back(tmp);
    }
  }
}
}
