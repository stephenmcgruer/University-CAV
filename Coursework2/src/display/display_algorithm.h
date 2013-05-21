//! \author Stephen McGruer

#include <GL/glu.h>
#include <GL/glut.h>

#ifndef SRC_DISPLAY_DISPLAY_ALGORITHM_H_
#define SRC_DISPLAY_DISPLAY_ALGORITHM_H_

#include <string>

#include "../volume.h"

namespace computer_visualization {

//! \class DisplayAlgorithm
//! \brief Represents a generic display approach.
//!
//! Presents an interface for a generic display approach, wrapping the
//! common GLUT calls and providing hooks to attach extra setup calls,
//! keyboard callbacks, and display callbacks. After creating an instance
//! of this class, you *must* call SetInstance() with itself as the parameter
//! in order for it to work.
class DisplayAlgorithm {
  public:
    DisplayAlgorithm()
        : transparency_level(0.25) {
    }

    virtual ~DisplayAlgorithm() { }

    //! \brief Renders the data given in the named file.
    //!
    //! Setups the basic GLUT interface, and loads the data from
    //! the file.
    void Render(std::string filename, int* argc, char** argv);

    //! \brief Sets the instance of itself for this class.
    //!
    //! A self-instance is required in order to allow the C-style GLUT
    //! library to interact with C++ classes. The instance cannot be
    //! set in the constructor as at that point the object has not yet
    //! been built.
    static void SetInstance(DisplayAlgorithm* display_algorithm);

    //! \brief The opacity transfer function.
    //!
    //! This function provides a transformation from a scalar value to
    //! an opacity level, [0,1]. By default it simply subtracts a small
    //! delta from the value and returns it.
    float OpacityTransferFunction(float value);

    //! \brief The colour transfer function.
    //!
    //! This function provides a transformation from a scalar value to
    //! a RGB colour. By default it attempts to split the value range
    //! into bone (white) and flesh (red).
    void ColourTransferFunction(float value, float colour[]);

    //! \brief A hook for any extra GLUT setup that a subclass requires.
    virtual void ExtraSetup() = 0;

    //! \brief A hook for GLUT's display function.
    virtual void Display() = 0;

    //! \brief A hook for GLUT's key press function.
    //!
    //! By default nothing is done on a key press.
    virtual void KeyPressed(unsigned char key, int x, int y) { }

  protected:
    //! The width of the GLUT window.
    static const int kWindowWidth = 480;

    //! The height of the GLUT window.
    static const int kWindowHeight = 480;

    //! The self-instance used to allow GLUT to work with C++ classes.
    static DisplayAlgorithm* instance;

    // The volume storing the data.
    Volume vol;

    // Controls how much of the volume is currently shown.
    float transparency_level;

  private:
    //! \brief The wrapper for GLUT's display callback.
    static void DisplayCallback();

    //! \brief The wrapper for GLUT's keypress callback.
    static void KeyPressedCallback(unsigned char key, int x, int y);
};
}

#endif  // SRC_DISPLAY_DISPLAY_ALGORITHM_H_
