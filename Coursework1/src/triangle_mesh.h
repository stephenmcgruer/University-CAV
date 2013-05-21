//! \author Stephen McGruer

#ifndef SRC_TRIANGLE_MESH_H_
#define SRC_TRIANGLE_MESH_H_

#include <cstdio>
#include <vector>

#include "./edge.h"
#include "./skeleton.h"
#include "./triangle.h"

namespace computer_animation {

//! \class TriangleMesh
//! \brief Represents a polygon implemented as a mesh of triangles.
class TriangleMesh {
  public:
    TriangleMesh() {
      bone_weights_.resize(skeleton_.GetNumberBones());
    }

    //! \brief Loads in an object file and populates the mesh from it.
    void LoadFile(char *filename);

    //! \brief Loads in a weights file.
    void LoadWeights(char *filename);

    //! \brief Returns the i-th vertex of the mesh.
    Vector3d<float> GetVertex(int i) const {
      return mesh_vertices_[i];
    }

    //! \brief Returns the i-th vertex of the mesh.
    Triangle GetTriangle(int i) {
      return mesh_triangles_[i];
    }

    //! \brief Returns the normals of the vertices for the i-th triangle.
    void GetTriangleNormals(int i, Vector3d<float> *v1, Vector3d<float> *v2,
        Vector3d<float> *v3) {
      *v1 = mesh_normals_[mesh_triangles_[i].normals_[0]];
      *v2 = mesh_normals_[mesh_triangles_[i].normals_[1]];
      *v3 = mesh_normals_[mesh_triangles_[i].normals_[2]];
    }

    //! \brief Returns the number of vertices in the mesh.
    inline const int GetNumberOfVertices() const {
      return mesh_vertices_.size();
    }

    //! \brief Returns the number of triangles in the mesh.
    inline const int GetNumberOfTriangles() const {
      return mesh_triangles_.size();
    }

    //! \brief Returns the object's skeleton.
    inline Skeleton* skeleton() { return &skeleton_; }

    //! \brief Sets the object's skeleton.
    void SetSkeleton(Skeleton skeleton) { skeleton_ = skeleton; }

    //! \brief Gets the weight for bone b and vertex w.
    const float GetBoneWeight(int b, int w) {
      return bone_weights_.at(b).at(w);
    }

  private:
    Skeleton skeleton_;
    std::vector<Vector3d<float> > mesh_vertices_;
    std::vector<Vector3d<float> > mesh_normals_;
    std::vector<Triangle> mesh_triangles_;
    std::vector<Edge> mesh_edges_;
    std::vector<std::vector<float> > bone_weights_;
};
}

#endif  // SRC_TRIANGLE_MESH_H_
