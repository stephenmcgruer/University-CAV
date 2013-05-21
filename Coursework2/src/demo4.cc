//! \author Stephen McGruer

#include <GL/glu.h>
#include <GL/glut.h>

#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>

#include "./display/display_algorithm.h"
#include "./display/three_dimensional_display.h"
#include "./display/two_dimensional_display.h"
#include "./volume.h"

namespace cv = computer_visualization;

cv::TwoDimensionalDisplay two_d_display;
cv::ThreeDimensionalDisplay three_d_display;

int main(int argc, char **argv) {
  // The display function to use.
  cv::DisplayAlgorithm* display;

  // The name of the input file.
  std::string filename;

  if (argc == 2)  {
    // The default view is 2D.
    fprintf(stdout, "Defaulting to two dimensional view.\n");
    display = &two_d_display;
    filename = argv[1];
  } else if (argc == 4 && strcmp(argv[1], "-d") == 0) {
    if (strcmp(argv[2], "2") == 0) {
      fprintf(stdout, "Two dimensional view chosen.\n");
      display = &two_d_display;
    } else if (strcmp(argv[2], "3") == 0) {
      fprintf(stdout, "Three dimensional view chosen.\n");
      display = &three_d_display;
    } else {
      fprintf(stderr, "Unknown dimensionality option: '%s'\n", argv[2]);
      fprintf(stderr, "    Accepted dimensionality values are '2' and '3'\n");
      return 1;
    }

    filename = argv[3];
  } else {
    fprintf(stderr, "Usage: %s [dimensionality] <filename>\n", argv[0]);
    return 1;
  }
  display->SetInstance(display);
  display->Render(filename, &argc, argv);

  return 0;
};
