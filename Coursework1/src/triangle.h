//! \author Stephen McGruer

#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

namespace computer_animation {

//! \class Triangle
//! \brief Represents a triangle.
//!
//! The triangle vertices are stored as indices into the TriangleMesh's
//! list, as are the triangle edges.
class Triangle {
  friend class TriangleMesh;

  public:
    //! \brief Creates a triangle from three vertices and three normals.
    Triangle(int v1, int v2, int v3, int n1, int n2, int n3) {
      vertices_[0] = v1;
      vertices_[1] = v2;
      vertices_[2] = v3;

      normals_[0] = n1;
      normals_[1] = n2;
      normals_[2] = n3;
    }

    //! \brief Sets the edges of the triangle.
    void SetEdges(int e1, int e2, int e3);

    //! \brief Gets the indices of the triangle vertices.
    void GetVertexIndices(int *v1, int *v2, int *v3) {
      *v1 = vertices_[0];
      *v2 = vertices_[1];
      *v3 = vertices_[2];
    }

  private:
    int id_;
    int vertices_[3];
    int normals_[3];
    int edges_[3];
};
}

#endif  // SRC_TRIANGLE_H_
