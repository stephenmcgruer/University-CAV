//! \author Stephen McGruer

#ifndef SRC_DISPLAY_THREE_DIMENSIONAL_DISPLAY_H_
#define SRC_DISPLAY_THREE_DIMENSIONAL_DISPLAY_H_

#include "./display_algorithm.h"

namespace computer_visualization {

//! \class ThreeDimensionalDisplay
//!
//! \brief Displays the skull in 3D, allowing rotation around the y-axis.
class ThreeDimensionalDisplay : public virtual DisplayAlgorithm {
  public:
    ThreeDimensionalDisplay()
        : xloc(0), yloc(0), zloc(0), angle(50), refresh_model(true) {
    }

    virtual void ExtraSetup();
    virtual void Display();
    virtual void KeyPressed(unsigned char key, int x, int y);

  private:
    // The current location and rotation of the object, using world coordinates.
    GLfloat xloc;
    GLfloat yloc;
    GLfloat zloc;
    GLfloat angle;  // Stored in degrees.

    // Tracks whether the object matrix needs re-calculated.
    bool refresh_model;

    //! Recalculates the view matrix based on the current translation and rotation
    //! of the model.
    void RecalculateModelView();
};
}

#endif  // SRC_DISPLAY_THREE_DIMENSIONAL_DISPLAY_H_
