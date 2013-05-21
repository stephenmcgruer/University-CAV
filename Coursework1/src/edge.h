//! \author Stephen McGruer

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include <map>
#include <set>

namespace computer_animation {

//! \class Edge
//! \brief Represents a non-directed edge between two vertices.
//!
//! The vertices are stored as indices into the TriangleMesh's list. Also
//! stores a set of triangles that the edge is part of.
class Edge {
  public:
    //! \brief Creates a new edge between vertices v1 and v2.
    Edge(int v1, int v2)
        : v1_(v1), v2_(v2) {
    }

    //! \brief Adds a triangle that the edge is part of.
    //!
    //! Adding the same triangle multiple times will only add a single copy
    //! to the Edge's set.
    void AddTriangle(int triangle);

    //! \brief Returns the first vertex.
    inline const int v1() const { return v1_; }

    //! \brief Returns the second vertex.
    inline const int v2() const { return v2_; }

    //! \brief Checks if two edges are equal.
    //!
    //! Two edges are considered equal if they have the same end-vertices,
    //! order-independent.
    bool operator== (const Edge &edge) const;

  private:
    int v1_, v2_;
    std::set<int> triangles_;
};
}

#endif  // SRC_EDGE_H_
