//! \author Stephen McGruer

#include "./two_dimensional_display.h"

#include <algorithm>
#include <cstdio>

namespace computer_visualization {

void TwoDimensionalDisplay::ExtraSetup() {
  // Set up an orthogonal projection to display the head on.
  gluOrtho2D(-kWindowWidth / 2, kWindowWidth / 2, -kWindowHeight / 2,
      kWindowHeight / 2);
}

void TwoDimensionalDisplay::Display() {
  // Clear the window.
  glClear(GL_COLOR_BUFFER_BIT);

  // Iterate over all of the head data, displaying the currently viewable
  // data.
  fprintf(stdout, "Rendering... (Transparency level %f)\n", transparency_level);
  for (int xi = 1 ; xi < vol.sizex()-1 ; xi++) {
    for (int yi = 1 ; yi < vol.sizey()-1 ; yi++) {
      for (int zi = vol.sizez()-1 ; zi > 0 ; zi--) {
        float tmpc = static_cast<float>(vol.volume(xi, yi, zi) / 255.f);

        float alpha = OpacityTransferFunction(tmpc);

        float color[3];
        ColourTransferFunction(tmpc, color);

        glColor4f(color[0], color[1], color[2], alpha);

        // The data is compressed such that the y range is too small, so each
        // voxel defines a square box.
        glRecti(xi-vol.sizex()/2 , 2*yi -vol.sizey(),
            xi-vol.sizex()/2+1, 2*yi-vol.sizey()+2);
      }
    }
  }
  fprintf(stdout, "Rendered.\n");

  glFlush();
}

void TwoDimensionalDisplay::KeyPressed(unsigned char key, int x, int y) {
  // '=' is a common typo for '+'.
  if (key == '+' || key == '=') {
    transparency_level = std::min(0.95f, transparency_level + 0.05f);
  } else if (key == '-') {
    transparency_level = std::max(0.05f, transparency_level - 0.05f);
  } else if (key >= '0' && key <= '9') {
    transparency_level = (key - '0') / 10.0f;
    fprintf(stdout, "Set transparency level to %f\n", transparency_level);
  } else {
    return;
  }

  glutPostRedisplay();
}
}
