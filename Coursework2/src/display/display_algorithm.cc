//! \author Stephen McGruer

#include "./display_algorithm.h"

#include <algorithm>

namespace computer_visualization {

void DisplayAlgorithm::Render(std::string filename, int* argc, char** argv) {
  vol.load(filename);

  glutInit(argc, argv);

  glutInitWindowSize(kWindowWidth, kWindowHeight);
  glutCreateWindow("CAV Assignment 2");

  // Blending is used for the transparency.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // The clear colour is black.
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // Callback functions.
  glutDisplayFunc(DisplayCallback);
  glutKeyboardFunc(KeyPressedCallback);

  // Do any subclass specific stuff.
  ExtraSetup();

  // Show everything and wait.
  glutMainLoop();
}

float DisplayAlgorithm::OpacityTransferFunction(float value) {
  if (transparency_level < 0.25) {
    // Reduce the bone opacity for low transparency levels.
    if (value > 0.5) {
      return std::max(0.0f, value - (transparency_level + 0.25f));
    }
  }
  return std::max(0.0f, value - transparency_level);
}

void DisplayAlgorithm::ColourTransferFunction(float value, float colour[]) {
  // Attempt to split the colour range into bone (white), flesh (red), and
  // what appears to be hair (green).
  if (value > 0.5) {
    colour[0] = std::min(1.0f, value + 0.2f);
    colour[1] = std::min(1.0f, value + 0.2f);
    colour[2] = std::min(1.0f, value + 0.2f);
  } else if (value >= 0.15) {
    colour[0] = value;
    colour[1] = 0;
    colour[2] = 0;
  } else {
    colour[0] = 0;
    colour[1] = value;
    colour[2] = 0;
  }
}

// The below is a rather ugly hack to let the C-based GLUT work with
// C++ classes.

DisplayAlgorithm *DisplayAlgorithm::instance = 0;

void DisplayAlgorithm::SetInstance(DisplayAlgorithm* display_algorithm) {
  instance = display_algorithm;
}

void DisplayAlgorithm::DisplayCallback() {
  instance->Display();
}

void DisplayAlgorithm::KeyPressedCallback(unsigned char key, int x, int y) {
  instance->KeyPressed(key, x, y);
}
}
