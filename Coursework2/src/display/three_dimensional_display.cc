//! \author Stephen McGruer

#include "./three_dimensional_display.h"

#include <cstdio>

namespace computer_visualization {

void ThreeDimensionalDisplay::ExtraSetup() {
  // Set up an orthogonal projection to display the head on.
  glMatrixMode(GL_PROJECTION);
  gluPerspective(40.0,     // Field of view. (Degrees.)
                 1.0,      // Aspect ratio.
                 1.0,      // Z near.
                 1000.0);  // Z far.

  // Setup the normal view parameters.
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 700.0,    // The viewing eye position.
            100.0, 100.0, 0.0,  // The scene centre.
            0.0, 1.0, 0.0);     // The 'up' vector direction.

  // Push the base view parameters down one, so we can later push the
  // recalculations on top of that.
  glPushMatrix();
}

void ThreeDimensionalDisplay::Display() {
  if (refresh_model) {
    RecalculateModelView();
  }

  // Clear the window.
  glClear(GL_COLOR_BUFFER_BIT);

  // Iterate over all of the head data, displaying the currently viewable
  // data.
  fprintf(stdout, "Rendering...\n");
  fprintf(stdout, "(Angle %f, Transparency level %f)\n", angle,
      transparency_level);
  for (int xi = 1; xi < vol.sizex(); xi++) {
    for (int yi = 1; yi < vol.sizey(); yi++) {
      for (int zi = vol.sizez() - 1; zi >= 0; zi--) {
        float tmpc = static_cast<float>(vol.volume(xi, yi, zi) / 255.f);

        float alpha = OpacityTransferFunction(tmpc);

        float color[3];
        ColourTransferFunction(tmpc, color);

        glColor4f(color[0], color[1], color[2], alpha);
        glBegin(GL_POINTS);
        // The data is compressed such that the y range is too small, so each
        // voxel is used twice.
        glVertex3d(xi, 2*yi, zi);
        glVertex3d(xi, 2*yi + 1, zi);
        glEnd();
      }
    }
  }
  fprintf(stdout, "Rendered.\n");

  glFlush();
}

void ThreeDimensionalDisplay::KeyPressed(unsigned char key, int x, int y) {
  // '=' is a common typo for '+'.
  if (key == '+' || key == '=') {
    transparency_level = std::min(0.95f, transparency_level + 0.05f);
  } else if (key == '-') {
    transparency_level = std::max(0.0f, transparency_level - 0.05f);
  } else if (key >= '0' && key <= '9') {
    transparency_level = (key - '0') / 10.0f;
    fprintf(stdout, "Set transparency level to %f\n", transparency_level);
  } else if (key == '[') {
    angle += 15.0f;
    if (angle >= 360) {
      angle -= 360;
    }
    refresh_model = true;
  } else if (key == ']') {
    angle -= 15.0f;
    if (angle < 0) {
      angle += 360;
    }
    refresh_model = true;
  } else {
    return;
  }

  glutPostRedisplay();
}

void ThreeDimensionalDisplay::RecalculateModelView() {
  // Replace the current view matrix with a new one.
  glPopMatrix();
  glPushMatrix();

  // Do the translation and rotation.
  glTranslatef(xloc, yloc, zloc);
  glRotatef(angle, 0.0, 1.0, 0.0);

  refresh_model = false;
}
}
