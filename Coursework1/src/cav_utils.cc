//! \author Stephen McGruer

#include "./cav_utils.h"

#include <cmath>

namespace computer_animation {

int FindEdge(const Edge &edge, const std::vector<Edge> &edge_list) {
  for (std::vector<Edge>::const_iterator it = edge_list.begin();
      it != edge_list.end(); it++) {
    if (*it == edge) {
      return std::distance(edge_list.begin(), it);
    }
  }
  return -1;
}

void CreateIdentityMatrix(Matrix<float> *f) {
  if (f->num_cols() != f->num_rows()) {
    fprintf(stderr, "Error: #rows != #columns");
    return;
  }
  int size = f->num_rows();

  for (int i = 0; i < size; i++) {
    (*f)(i, i) = 1;
  }
}

void CreateTranslationMatrix(Matrix<float> *f,
    const Vector3d<float> &translation) {
  if (f->num_cols() != 4 || f->num_rows() != 4) {
    fprintf(stderr, "Error: Input matrix wrong size.");
    return;
  }

  (*f)(0, 0) = 1.0f;
  (*f)(0, 1) = 0.0f;
  (*f)(0, 2) = 0.0f;
  (*f)(0, 3) = translation[0];

  (*f)(1, 0) = 0.0f;
  (*f)(1, 1) = 1.0f;
  (*f)(1, 2) = 0.0f;
  (*f)(1, 3) = translation[1];

  (*f)(2, 0) = 0.0f;
  (*f)(2, 1) = 0.0f;
  (*f)(2, 2) = 1.0f;
  (*f)(2, 3) = translation[2];

  (*f)(3, 0) = 0.0f;
  (*f)(3, 1) = 0.0f;
  (*f)(3, 2) = 0.0f;
  (*f)(3, 3) = 1.0f;
}

void CreateXRotMatrix(Matrix<float> *f, float theta) {
  if (f->num_cols() != 4 || f->num_rows() != 4) {
    fprintf(stderr, "Error: Input matrix wrong size.");
    return;
  }

  float cosTheta = cos(theta * M_PI / 180);
  float sinTheta = sin(theta * M_PI / 180);

  (*f)(0, 0) = 1.0f;
  (*f)(0, 1) = 0.0f;
  (*f)(0, 2) = 0.0f;
  (*f)(0, 3) = 0.0f;

  (*f)(1, 0) = 0.0f;
  (*f)(1, 1) = cosTheta;
  (*f)(1, 2) = -sinTheta;
  (*f)(1, 3) = 0.0f;


  (*f)(2, 0) = 0.0f;
  (*f)(2, 1) = sinTheta;
  (*f)(2, 2) = cosTheta;
  (*f)(2, 3) = 0.0f;

  (*f)(3, 0) = 0.0f;
  (*f)(3, 1) = 0.0f;
  (*f)(3, 2) = 0.0f;
  (*f)(3, 3) = 1.0f;
}

void CreateYRotMatrix(Matrix<float> *f, float theta) {
  if (f->num_cols() != 4 || f->num_rows() != 4) {
    fprintf(stderr, "Error: Input matrix wrong size.");
    return;
  }

  float cosTheta = cos(theta * M_PI / 180);
  float sinTheta = sin(theta * M_PI / 180);

  (*f)(0, 0) = cosTheta;
  (*f)(0, 1) = 0.0f;
  (*f)(0, 2) = sinTheta;
  (*f)(0, 3) = 0.0f;

  (*f)(1, 0) = 0.0f;
  (*f)(1, 1) = 1.0f;
  (*f)(1, 2) = 0.0f;
  (*f)(1, 3) = 0.0f;

  (*f)(2, 0) = -sinTheta;
  (*f)(2, 1) = 0.0f;
  (*f)(2, 2) = cosTheta;
  (*f)(2, 3) = 0.0f;

  (*f)(3, 0) = 0.0f;
  (*f)(3, 1) = 0.0f;
  (*f)(3, 2) = 0.0f;
  (*f)(3, 3) = 1.0f;
}

void CreateZRotMatrix(Matrix<float> *f, float theta) {
  if (f->num_cols() != 4 || f->num_rows() != 4) {
    fprintf(stderr, "Error: Input matrix wrong size.");
    return;
  }

  float cosTheta = cos(theta * M_PI / 180);
  float sinTheta = sin(theta * M_PI / 180);

  (*f)(0, 0) = cosTheta;
  (*f)(0, 1) = -sinTheta;
  (*f)(0, 2) = 0.0f;
  (*f)(0, 3) = 0.0f;

  (*f)(1, 0) = sinTheta;
  (*f)(1, 1) = cosTheta;
  (*f)(1, 2) = 0.0f;
  (*f)(1, 3) = 0.0f;

  (*f)(2, 0) = 0.0f;
  (*f)(2, 1) = 0.0f;
  (*f)(2, 2) = 1.0f;
  (*f)(2, 3) = 0.0f;

  (*f)(3, 0) = 0.0f;
  (*f)(3, 1) = 0.0f;
  (*f)(3, 2) = 0.0f;
  (*f)(3, 3) = 1.0f;
}
}
