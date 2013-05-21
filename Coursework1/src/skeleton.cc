//! \author Stephen McGruer

#include <cstdio>
#include <limits>

#include "./cav_utils.h"
#include "./skeleton.h"

namespace computer_animation {

// This function is currently incomplete, as I cannot figure out how to
// determine the rotations necessary to move the end effector from it's
// current position to the closest point on the sphere to the target.
// Without this ability, it's still possible to move the end effector,
// but not to update any intermediate bones positions - this means that
// not only will the skeleton be wrong, running more iterations of CCD
// doesn't even make sense. (As the distances between the end effector
// and each parent/grandparent/... bone has changed.)
//
// If you press ']' when running the program, you can see it attempt to
// move a foot, and observe the output in the terminal for one iteration.
void Skeleton::CCDMoveBoneTo(int i, Vector3d<float> target_position) {
  fprintf(stdout, "CCD:\n");
  fprintf(stdout, "Initial target: (%f, %f, %f)\n\n", target_position[0],
      target_position[1], target_position[2]);

  float distance_to_target = std::numeric_limits<float>::infinity();

  // CCD is performed a maximum of kMaxCCDIterations times - if the target
  // cannot be reached after this then we give up.
  int iteration = 0;
  while (distance_to_target > kCCDDistanceThreshold &&
      iteration++ < kMaxCCDIterations) {
    // For each bone up to the root, move the bone so that the end effector
    // is as close as possible to the target point.
    const Bone* current_bone =  bones_.at(i).Parent();
    while (current_bone != NULL) {
      const Vector3d<float> sphere_centre = current_bone->CurrentPosition();
      fprintf(stdout, "Sphere Centre: (%f, %f, %f)\n", sphere_centre[0],
          sphere_centre[1], sphere_centre[2]);

      Vector3d<float> effector_position = bones_.at(i).CurrentPosition();

      fprintf(stdout, "Effector Position (before): (%f, %f, %f)\n",
          effector_position[0], effector_position[1], effector_position[2]);

      float sphere_radius = sphere_centre.DistanceTo(effector_position);

      fprintf(stdout, "Radius: %f\n", sphere_radius);

      // Find the line from the sphere centre to the target.
      Vector3d<float> line_delta = (target_position - sphere_centre);
      float line_distance = sphere_centre.DistanceTo(target_position);
      line_delta /= line_distance;

      // Now calculate the closest position on the sphere to the target
      // position.
      line_delta *= sphere_radius;
      Vector3d<float> sphere_target = sphere_centre + line_delta;
      Vector3d<float> sphere_target_2 = sphere_centre - line_delta;

      fprintf(stdout, "Sphere target: (%f, %f, %f)\n", sphere_target[0],
          sphere_target[1], sphere_target[2]);
      fprintf(stdout, "Sphere target2: (%f, %f, %f)\n", sphere_target_2[0],
          sphere_target_2[1], sphere_target_2[2]);

      // Move the bone directly to sphere_target.
      bones_.at(i).SetPosition(sphere_target);

      effector_position = bones_.at(i).CurrentPosition();
      fprintf(stdout, "Effector Position (after): (%f, %f, %f)\n\n",
          effector_position[0], effector_position[1], effector_position[2]);

      current_bone = current_bone->Parent();
    }
  }

  if (iteration > kMaxCCDIterations) {
    fprintf(stdout, "Max number of iterations reached.\n");
  }

  Bone end_effector = bones_.at(i);
  Vector3d<float> effector_position = end_effector.CurrentPosition();
  fprintf(stdout, "End Effector Final Position: (%f, %f, %f)\n",
      effector_position[0], effector_position[1], effector_position[2]);
}

void Skeleton::AdjustBoneRotation(int i, Vector3d<int> delta_rotation) {
  Bone* bone = &bones_.at(i);
  Vector3d<int> current_rotation = bone->Rotation();

  bone->SetRotation(current_rotation + delta_rotation);
}

Skeleton& Skeleton::operator=(const Skeleton &rhs) {
  if (this == &rhs) {
    return *this;
  }

  std::vector<Bone>::iterator this_it = bones_.begin();
  std::vector<Bone>::const_iterator rhs_it = rhs.bones_.begin();

  while (this_it != bones_.end()) {
    *this_it = *rhs_it;

    this_it++;
    rhs_it++;
  }

  return *this;
}

Skeleton& Skeleton::operator-=(const Skeleton &rhs) {
  std::vector<Bone>::iterator this_it = bones_.begin();
  std::vector<Bone>::const_iterator rhs_it = rhs.bones_.begin();

  while (this_it != bones_.end()) {
    *this_it -= *rhs_it;

    this_it++;
    rhs_it++;
  }

  return *this;
}

const Skeleton Skeleton::operator-(const Skeleton &other) const {
  Skeleton result = *this;
  result -= other;
  return result;
}

void Skeleton::init() {
  bones_.push_back(Bone(-0.0881862, -0.223678, -0.929536));
  bones_.push_back(Bone(-0.566275, -0.541542, -0.899938));
  bones_.push_back(Bone(-0.616166, -1.19613, -1.0551));
  bones_.push_back(Bone(-0.614267, -1.74914, -1.16717));
  bones_.push_back(Bone(-0.86033, -1.84008, -0.670307));
  bones_.push_back(Bone(-0.0871545, 0.0924213, -0.927642));
  bones_.push_back(Bone(-0.0640778, 0.577047, -0.846801));
  bones_.push_back(Bone(-0.113935, 1.09478, -0.921801));
  bones_.push_back(Bone(0.267937, 0.551273, -0.789762));
  bones_.push_back(Bone(0.578372, 0.536381, -0.666565));
  bones_.push_back(Bone(0.824687, 0.573724, -0.517252));
  bones_.push_back(Bone(1.07611, 0.735785, -0.0939775));
  bones_.push_back(Bone(1.21808, 0.700675, 0.158607));
  bones_.push_back(Bone(-0.370623, 0.532531, -0.852921));
  bones_.push_back(Bone(-0.675322, 0.48007, -0.770522));
  bones_.push_back(Bone(-0.936812, 0.474334, -0.677436));
  bones_.push_back(Bone(-1.26404, 0.784372, -0.351252));
  bones_.push_back(Bone(-1.45527, 0.892911, 0.0528238));
  bones_.push_back(Bone(0.3686, -0.428869, -0.978191));
  bones_.push_back(Bone(0.617329, -1.04685, -0.899962));
  bones_.push_back(Bone(0.593214, -1.71593, -1.08845));
  bones_.push_back(Bone(0.982818, -1.82164, -0.622992));

  bones_.at(1).SetParent(&bones_.at(0));
  bones_.at(2).SetParent(&bones_.at(1));
  bones_.at(3).SetParent(&bones_.at(2));
  bones_.at(4).SetParent(&bones_.at(3));
  bones_.at(5).SetParent(&bones_.at(0));
  bones_.at(6).SetParent(&bones_.at(5));
  bones_.at(7).SetParent(&bones_.at(6));
  bones_.at(8).SetParent(&bones_.at(6));
  bones_.at(9).SetParent(&bones_.at(8));
  bones_.at(10).SetParent(&bones_.at(9));
  bones_.at(11).SetParent(&bones_.at(10));
  bones_.at(12).SetParent(&bones_.at(11));
  bones_.at(13).SetParent(&bones_.at(6));
  bones_.at(14).SetParent(&bones_.at(13));
  bones_.at(15).SetParent(&bones_.at(14));
  bones_.at(16).SetParent(&bones_.at(15));
  bones_.at(17).SetParent(&bones_.at(16));
  bones_.at(18).SetParent(&bones_.at(0));
  bones_.at(19).SetParent(&bones_.at(18));
  bones_.at(20).SetParent(&bones_.at(19));
  bones_.at(21).SetParent(&bones_.at(20));
}

void Skeleton::Reset() {
  for (std::vector<Bone>::iterator it = bones_.begin();
       it != bones_.end(); it++) {
    (*it).SetRotation(Vector3d<int>(0, 0, 0));
    (*it).SetPosition((*it).RestPosition());
  }
}
}
