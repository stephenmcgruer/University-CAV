//! \author Stephen McGruer

#include <GL/glut.h>

#include <map>
#include <set>

#include "./animation_controller.h"
#include "./cav_utils.h"
#include "./matrix.h"
#include "./triangle_mesh.h"

namespace ca = computer_animation;

const int kWindowWidth = 480;
const int kWindowHeight = 480;

// The lighting position and parameters. Position is (x, y, z, W),
// parameters are (R, G, B, A).
const GLfloat kLightPosition[] = {0.0, 0.0, 1.0, 0.0};
const GLfloat kAmbientLight[]  = {0.5, 0.5, 0.5, 1.0};
const GLfloat kDiffuseLight[]  = {0.8, 0.8, 0.8, 1.0};
const GLfloat kSpecularLight[] = {0.8, 0.8, 0.8, 1.0};

// Stores the model polygon.
ca::TriangleMesh the_model;
std::vector<ca::Vector3d<float> > skin_vertices;

// The current location and rotation of the model, using world
// co-ordinates.
GLfloat xloc = 0;
GLfloat yloc = 0;
GLfloat zloc = 0;
GLfloat angle = 0;  // Stored in degrees.

// Tracks whether the model matrix needs re-calculated.
bool refresh_model = true;

// Tracks the mouse state.
int mouse_state = -1;
int drag_start_x = -1;

// Keyboard Key --> Bone map.
std::map<char, int> CreateMap() {
  std::map<char, int> m;
  // The right leg.
  m['1'] = 1; m['2'] = 2;
  m['3'] = 3; m['4'] = 4;

  // The left leg.
  m['5'] = 18; m['6'] = 19;
  m['7'] = 20; m['8'] = 21;

  // The right arm.
  m['a'] = 14; m['s'] = 15;
  m['d'] = 16; m['f'] = 17;

  // The left arm.
  m['g'] = 9; m['h'] = 10;
  m['j'] = 11; m['k'] = 12;

  return m;
}
std::map<char, int> keyboard_map = CreateMap();
int current_bone = -1;

char current_axis = 'x';

// Animation-related trackers.
ca::AnimationController animation_controller;
bool animation_running = false;

// Forward declarations.
void DisplayCallback();
void TimerCallback(int frame);
void MouseClickCallback(int button, int state, int x, int y);
void MouseDragCallback(int x, int y);
void KeyPressedCallback(unsigned char key, int x, int y);
void RecalculateModelView(void);

int main(int argc, char **argv) {
  if (argc < 3)  {
    fprintf(stderr, "Usage: %s <object> <weight>\n", argv[0]);
    exit(1);
  }
  the_model.LoadFile(argv[1]);
  the_model.LoadWeights(argv[2]);
  skin_vertices.resize(the_model.GetNumberOfVertices());

  glutInit(&argc, argv);

  // RGB, double-buffered, depth-buffered, multisampling support enabled.
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

  glutInitWindowSize(kWindowWidth, kWindowHeight);
  glutCreateWindow("CAV Assignment 1");

  // Set the position and parameters of the light.
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);  // Enabled specific parameter setting.
  glLightfv(GL_LIGHT0, GL_POSITION, kLightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, kAmbientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, kDiffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, kSpecularLight);

  // Use the depth buffer algorithm for hidden surface elimination.
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_POINT_SMOOTH);

  // Setup the perspective projection parameters.
  glMatrixMode(GL_PROJECTION);
  gluPerspective(40.0,    // Field of view. (Degrees.)
      1.0,      // Aspect ratio.
      1.0,      // Z near.
      1000.0);  // Z far.

  // Setup the normal view parameters.
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 7.0,  // The viewing eye is at (0,0,7).
      0.0, 0.0, 0.0,        // The centre is at (0,0,0).
      0.0, 1.0, 0.0);       // The 'up' vector is in positive Y direction.

  // Push the base view parameters down one, so we can later push the
  // recalculations on top of that.
  glPushMatrix();

  // Display callback function.
  glutDisplayFunc(DisplayCallback);


  animation_controller.LoadAnimation("animations/all");

  glutMouseFunc(MouseClickCallback);
  glutMotionFunc(MouseDragCallback);
  glutKeyboardFunc(KeyPressedCallback);

  // Display everything and wait.
  glutMainLoop();

  return 0;
}

//! \brief Called whenever OpenGL redraws the screen.
void DisplayCallback() {
  if (refresh_model) {
    RecalculateModelView();
  }

  // Clear the window.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int number_of_triangles = the_model.GetNumberOfTriangles();

  ca::Skeleton skeleton = *the_model.skeleton();
  int num_bones = skeleton.GetNumberBones();
  int number_of_vertices = the_model.GetNumberOfVertices();

  std::vector<ca::Matrix<float> > ms;
  for (int i = 0; i < num_bones; i++) {
    ca::Bone bone = skeleton.GetBone(i);
    ca::Matrix<float> m(4, 4);
    bone.CalculateM(&m);
    ms.push_back(m);
  }

  // Do the linear blending.
  for (int i = 0; i < number_of_vertices; i++) {
    ca::Vector3d<float> v_hat = the_model.GetVertex(i);
    ca::Vector3d<float> v(0, 0, 0);

    for (int b = 0; b < num_bones; b++) {
      ca::Bone bone = skeleton.GetBone(b);
      float weight = the_model.GetBoneWeight(b, i);

      // M_hat^-1
      ca::Vector3d<float> tmp = v_hat - bone.RestPosition();

      // M
      ca::Matrix<float> m = ms[b];
      ca::Matrix<float> vertex_matrix(4, 1);
      vertex_matrix(0, 0) = tmp[0];
      vertex_matrix(0, 1) = tmp[1];
      vertex_matrix(0, 2) = tmp[2];
      vertex_matrix(0, 3) = 1.0f;

      ca::Matrix<float> result = m * vertex_matrix;

      tmp[0] = (result(0, 0) / result(0, 3));
      tmp[1] = (result(0, 1) / result(0, 3));
      tmp[2] = (result(0, 2) / result(0, 3));

      // W_i
      tmp *= weight;

      v += tmp;
    }

    skin_vertices[i] = v;
  }

  // Temporary variables for vertices and normals.
  ca::Vector3d<float> v1;
  ca::Vector3d<float> v2;
  ca::Vector3d<float> v3;
  int v1_i;
  int v2_i;
  int v3_i;
  ca::Vector3d<float> n1;
  ca::Vector3d<float> n2;
  ca::Vector3d<float> n3;

  for (int i = 0; i < number_of_triangles; i++) {
    ca::Triangle triangle = the_model.GetTriangle(i);
    triangle.GetVertexIndices(&v1_i, &v2_i, &v3_i);
    the_model.GetTriangleNormals(i, &n1, &n2, &n3);
    v1 = skin_vertices[v1_i];
    v2 = skin_vertices[v2_i];
    v3 = skin_vertices[v3_i];

    GLfloat skinColor[] = {0.8, 0.1, 0.1, 1.0};

    glBegin(GL_TRIANGLES);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor);
    glNormal3f(-n1[0], -n1[1], -n1[2]);
    glVertex3f(v1[0], v1[1], v1[2]);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor);
    glNormal3f(-n2[0], -n2[1], -n2[2]);
    glVertex3f(v2[0], v2[1], v2[2]);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor);
    glNormal3f(-n3[0], -n3[1], -n3[2]);
    glVertex3f(v3[0], v3[1], v3[2]);
    glEnd();
  }

  glutSwapBuffers();
}

//! \brief A timer callback used to run animations.
void TimerCallback(int frame) {
  if (frame >= animation_controller.NumberFrames() || frame < 0) {
    animation_running = false;
  } else {
    the_model.SetSkeleton(animation_controller.Frame(frame));
    glutPostRedisplay();
    glutTimerFunc(ca::kMillisecondsPerFrame, TimerCallback, frame + 1);
  }
}

//! \brief Called when the user clicks a mouse button.
void MouseClickCallback(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    mouse_state = state;
    drag_start_x = (state == GLUT_DOWN) ? x : drag_start_x;
  }
  glutPostRedisplay();
}

//! \brief Called when the user moves the mouse while holding down a button.
void MouseDragCallback(int x, int y) {
  // Only move if the left mouse button is being held down.
  if (mouse_state == GLUT_DOWN) {
    angle = angle + (x - drag_start_x);
    drag_start_x = x;
    refresh_model = true;
  }
  glutPostRedisplay();
}

//! \brief Called when the user pressed a key.
//!
//! Handles running animations, CCD, manually altering the model,
//! resetting the model, and printing out the skeleton state.
void KeyPressedCallback(unsigned char key, int x, int y) {
  if (animation_running) {
    return;
  }

  if (key == '[') {
    // Start animation.
    animation_running = true;
    glutTimerFunc(0, TimerCallback, 0);
  } else if (key == ']') {
    // Attempt CCD.
    ca::Skeleton skeleton;
    ca::Vector3d<float> new_pos(1.3, -1.9, -0.622992);

    skeleton.CCDMoveBoneTo(21, new_pos);
    the_model.SetSkeleton(skeleton);
  } else if (keyboard_map.find(key) != keyboard_map.end()) {
    // Select a bone.
    current_bone = keyboard_map[key];
    ca::Bone bone = the_model.skeleton()->GetBone(current_bone);

    const ca::Vector3d<float> pos = bone.CurrentPosition();
    fprintf(stdout, "You have selected joint %d\n", current_bone);
  } else if (key == 'x' || key == 'y' || key == 'z') {
    // Select an axis.
    current_axis = key;
    fprintf(stdout, "You have selected the %c-axis.\n", current_axis);
  } else if ((key == '+' || key == '=' || key == '-') && current_bone != -1) {
    // Adjust the rotation around the selected axis.
    // '=' is also captured as it is a common mis-type for '+'.
    ca::Vector3d<int> rotation_delta;
    int rotation = (key == '-') ? -10 : 10;

    switch (current_axis) {
      case 'x':
        rotation_delta[0] = rotation;
        break;
      case 'y':
        rotation_delta[1] = rotation;
        break;
      case 'z':
        rotation_delta[2] = rotation;
        break;
      default:
        // Do nothing.
        break;
    }
    the_model.skeleton()->AdjustBoneRotation(current_bone,
        rotation_delta);
  } else if (key == '#') {
    // Reset.
    the_model.skeleton()->Reset();
  } else if (key == 'p') {
    // Print out the current keyframe.
    fprintf(stdout, "Current keyframe:\n");

    ca::Skeleton skeleton = *the_model.skeleton();
    for (int i = 0; i < skeleton.GetNumberBones(); i++) {
      ca::Vector3d<int> rotation = skeleton.GetBone(i).Rotation();
      if (rotation[0] != 0 || rotation[1] != 0 || rotation[2] != 0) {
        fprintf(stdout, "%d %d %d %d\n", i, rotation[0], rotation[1],
            rotation[2]);
      }
    }
    fprintf(stdout, "End keyframe.\n");
  }

  glutPostRedisplay();
}

//! Recalculates the view matrix based on the current translation and rotation
//! of the model.
void RecalculateModelView(void) {
  // Replace the current view matrix with a new one.
  glPopMatrix();
  glPushMatrix();

  // Do the translation and rotation.
  glTranslatef(xloc, yloc, zloc);
  glRotatef(angle, 0.0, 1.0, 0.0);

  refresh_model = false;
}
