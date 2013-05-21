//! \author Stephen McGruer

#include "./triangle_mesh.h"

#include <cstdlib>
#include <cstring>

#include "./cav_utils.h"

namespace computer_animation {

void TriangleMesh::LoadFile(char *filename) {
  FILE *f;
  f = fopen(filename, "r");

  if (f == NULL) {
    fprintf(stderr, "Error: Failed reading polygon data file %s\n", filename);
    exit(1);
  }

  char buf[1024];
  char header[100];
  float x, y, z;
  int v1, v2, v3;

  while (fgets(buf, sizeof(buf), f) != NULL) {
    if (buf[0] == 'v') {
      // This is safe as buf is a bounded-size input.
      sscanf(buf, "%s %f %f %f", header, &x, &y, &z);

      mesh_vertices_.push_back(Vector3d<float>(x, y, z));

      // Add a default normal.
      mesh_normals_.push_back(Vector3d<float>(0.0f, 0.0f, 1.0f));
    } else if (buf[0] == 'f') {
      // This is safe as buf is a bounded-size input.
      sscanf(buf, "%s %d %d %d", header, &v1, &v2, &v3);

      // The normal indices are the same as the vertex ones.
      Triangle triangle(v1 - 1, v2 - 1, v3 - 1, v1 - 1, v2 - 1, v3 - 1);

      triangle.id_ = mesh_triangles_.size();
      mesh_triangles_.push_back(triangle);

      // Create the edges of the triangle.
      Edge e1(v1 - 1, v2 - 1);
      Edge e2(v2 - 1, v3 - 1);
      Edge e3(v3 - 1, v1 - 1);
      Edge edges[] = {e1, e2, e3};

      int id1 = FindEdge(e1, mesh_edges_);
      int id2 = FindEdge(e2, mesh_edges_);
      int id3 = FindEdge(e3, mesh_edges_);
      int edge_ids[] = {id1, id2, id3};

      // If any of the edges don't exist, create them.
      for (int i = 0; i < 3; i++) {
        int id = edge_ids[i];
        if (id >= 0) {
          continue;
        }

        id = mesh_edges_.size();
        edges[i].AddTriangle(triangle.id_);
        mesh_edges_.push_back(edges[i]);

        edge_ids[i] = id;
      }

      id1 = edge_ids[0];
      id2 = edge_ids[1];
      id3 = edge_ids[2];

      mesh_edges_[id1].AddTriangle(triangle.id_);
      mesh_edges_[id2].AddTriangle(triangle.id_);
      mesh_edges_[id3].AddTriangle(triangle.id_);

      mesh_triangles_[mesh_triangles_.size()-1].SetEdges(id1, id2, id3);
    }
  }

  std::vector<std::vector<int> > faces(mesh_vertices_.size());
  std::vector<Vector3d<float> > face_norms(mesh_triangles_.size());

  for (unsigned int i = 0; i < mesh_triangles_.size(); i++)  {
    Vector3d<float> face_normal = CrossProduct(
        (mesh_vertices_[mesh_triangles_[i].vertices_[2]] -
            mesh_vertices_[mesh_triangles_[i].vertices_[0]]),
        (mesh_vertices_[mesh_triangles_[i].vertices_[1]] -
            mesh_vertices_[mesh_triangles_[i].vertices_[0]]));
    face_normal.Normalize();
    face_norms.at(i) = face_normal;

    faces[mesh_triangles_[i].vertices_[0]].push_back(i);
    faces[mesh_triangles_[i].vertices_[1]].push_back(i);
    faces[mesh_triangles_[i].vertices_[2]].push_back(i);
  }

  for (unsigned int i = 0; i < mesh_vertices_.size(); i++) {
    Vector3d<float> N(0.0f, 0.0f, 0.0f);

    float rate1, rate2;

    if (mesh_vertices_[i][1] > 0.5) {
      rate1 = 1.0f;
      rate2 = 0.0f;
    } else if (mesh_vertices_[i][1] < -0.5) {
      rate1 = 0.0f;
      rate2 = 1.0f;
    } else {
      rate1 = mesh_vertices_[i][1] + 0.5f;
      rate2 = 1.0f - rate1;
    }

    for (unsigned int j = 0; j < faces[i].size(); j++) {
      N += face_norms[faces[i][j]];
    }

    N /= static_cast<float>(faces[i].size());

    mesh_normals_[i] = N;
  }

  fclose(f);
}

void TriangleMesh::LoadWeights(char *filename) {
  FILE *f;
  f = fopen(filename, "r");

  if (f == NULL) {
    fprintf(stderr, "Error: Failed reading weights data file %s\n", filename);
    exit(1);
  }

  char buf[1024];

  while (fgets(buf, sizeof(buf), f) != NULL) {
    // Remove newlines.
    char* p = strchr(buf, '\n');
    if (p) {
      *p = '\0';
    }

    // The root 'bone' has no weight on anything.
    bone_weights_.at(0).push_back(0.0);
    int i = 1;
    char *token;
    char *sp;
    token = strtok_r(buf, " ", &sp);
    while (token != NULL) {
      float weight = atof(token);
      bone_weights_.at(i).push_back(weight);

      token = strtok_r(NULL, " ", &sp);
      i++;
    }
  }

  fclose(f);
}
}
