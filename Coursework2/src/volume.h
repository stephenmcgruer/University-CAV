//! \author Stephen McGruer

#ifndef SRC_VOLUME_H_
#define SRC_VOLUME_H_

#include <stdint.h>

#include <string>
#include <vector>

namespace computer_visualization {

//! \class Volume
//! \brief Represents a volume in 3D space.
class Volume {
  public:
    //! \brief Loads in the data from a file and parses it.
    void load(std::string filename);

    //! \brief Returns the value of the volume at the given (x, y, z) point.
    uint16_t volume(int x, int y, int z) {
      return volume_.at(y).at(z * size_[2] + x);
    }

    int sizex() { return size_[0]; }
    int sizey() { return size_[1]; }
    int sizez() { return size_[2]; }
  private:
    // Stores the size of the data in the x, y, and z coordinates.
    int size_[3];

    // Stores the volume data. The out vector is indexed by the plane,
    // the inner one by the point in the plane. The inner plane is stored
    // flat; to access a point (x, z) calculate (z * _size[2] + x).
    std::vector<std::vector<uint16_t> > volume_;
};
}

#endif  // SRC_VOLUME_H_
