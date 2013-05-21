//! \author Stephen McGruer

#include "./volume.h"

#include <fstream>

namespace computer_visualization {

void Volume::load(std::string filename) {
  int plane_size;
  int size[3];

  // Google style guide says not to use streams, but the input data format
  // is so odd it's easier to read it with them.
  std::ifstream fin;
  fin.open(filename.c_str());

  if (fin == NULL) {
    fprintf(stderr, "%s cannot be found.\n", filename.c_str());
    return;
  }

  // The first line is the size of each dimension. The data is given on a set of
  // 2D planes, where the x and y axes are perpendicular, and the z axis defines
  // depth. I think. The dimension sizes seem to be given in the wrong order?
  fin >> size[2] >> size[0] >> size[1];

  // Resize the volume vector to fit the data.
  volume_.resize(size[1]);
  plane_size = size[2] * size[0];
  for (int i = 0; i < size[1]; i++) {
    volume_.at(i).resize(plane_size);
  }

  // Read in the data, from front to back.
  for (int plane = 0; plane < size[1]; plane++) {
    for (int i = 0; i < size[2]; i++) {
      for (int j = 0; j < size[0]; j++) {
        fin >> volume_.at(size[1] - 1 - plane).at(i * size[2] + j);
      }
    }
  }

  fin.close();

  size_[0] = size[0];
  size_[1] = size[1];
  size_[2] = size[2];
}
}
