//! \author Stephen McGruer

#ifndef SRC_DISPLAY_TWO_DIMENSIONAL_DISPLAY_H_
#define SRC_DISPLAY_TWO_DIMENSIONAL_DISPLAY_H_

#include "./display_algorithm.h"

namespace computer_visualization {

//! \class TwoDimensionalDisplay
//!
//! \brief Displays the skull in 2D.
class TwoDimensionalDisplay : public virtual DisplayAlgorithm {
  public:
    virtual void ExtraSetup();
    virtual void Display();
    virtual void KeyPressed(unsigned char key, int x, int y);
};
}

#endif  // SRC_DISPLAY_TWO_DIMENSIONAL_DISPLAY_H_
