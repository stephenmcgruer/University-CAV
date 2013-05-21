//! \author Stephen McGruer

#ifndef SRC_VECTOR3D_H_
#define SRC_VECTOR3D_H_

namespace computer_animation {

//! \class Vector3d
//! \brief Represents a three dimensional vector of Ts.
//!
//! Allows access to the x, y, and z coordinates using the [] operator.
template <typename T> class Vector3d {
  public:
    //! \brief Creates a vector with the default values for T.
    Vector3d() {
      coordinates_[0] = T();
      coordinates_[1] = T();
      coordinates_[2] = T();
    }

    //! \brief Creates a vector at the position (x, y, z).
    Vector3d(T x, T y, T z) {
      coordinates_[0] = x;
      coordinates_[1] = y;
      coordinates_[2] = z;
    }

    //! \brief Calculates the Euclidean distance to another vector.
    float DistanceTo(const Vector3d<T> &v) const;

    //! \brief Normalizes the vector.
    void Normalize();

    //! \brief Returns the i-th element of the vector.
    //!
    //! Does not perform bounds checking.
    T& operator[] (int i) {
      return coordinates_[i];
    }

    //! \brief Returns the i-th element of the vector.
    //!
    //! Does not perform bounds checking.
    T operator[] (int i) const {
      return coordinates_[i];
    }

    //! \brief Sets the vector equivalent to another.
    Vector3d<T>& operator= (const Vector3d<T> &obj) {
      coordinates_[0] = obj[0];
      coordinates_[1] = obj[1];
      coordinates_[2] = obj[2];

      return *this;
    }

    //! \brief Increases the vectors coordinates by those of another vector.
    Vector3d<T>& operator+= (const Vector3d<T> &obj) {
      coordinates_[0] += obj[0];
      coordinates_[1] += obj[1];
      coordinates_[2] += obj[2];

      return *this;
    }

    //! \brief Decreases the vectors coordinates by those of another vector.
    Vector3d<T>& operator-= (const Vector3d<T> &obj) {
      coordinates_[0] -= obj[0];
      coordinates_[1] -= obj[1];
      coordinates_[2] -= obj[2];

      return *this;
    }

    //! \brief Point-wise multiplies the vector elements by a value.
    Vector3d<T>& operator*= (const T &t) {
      coordinates_[0] *= t;
      coordinates_[1] *= t;
      coordinates_[2] *= t;

      return *this;
    }

    //! \brief Point-wide divides the vector elements by a value.
    Vector3d<T>& operator/= (const T &t) {
      coordinates_[0] /= t;
      coordinates_[1] /= t;
      coordinates_[2] /= t;

      return *this;
    }

    //! \brief Compares the vector for equality with another vector.
    bool operator==(const Vector3d<T> &other) {
      return coordinates_[0] == other.coordinates_[0] &&
          coordinates_[1] == other.coordinates_[1] &&
          coordinates_[2] == other.coordinates_[2];
    }

    //! \brief Computes the cross product of two vectors.
    template <typename V> friend Vector3d<V>
        CrossProduct(const Vector3d<V> &v1, const Vector3d<V> &v2);

    //! \brief Adds two vectors and returns the result.
    template <typename V> friend Vector3d<V>
        operator+ (const Vector3d<V> &v1, const Vector3d<V> &v2);

    //! \brief Subtracts two vectors and returns the result.
    template <typename V> friend Vector3d<V>
        operator- (const Vector3d<V> &v1, const Vector3d<V> &v2);

  private:
    T coordinates_[3];
};
}

#endif  // SRC_VECTOR3D_H_
