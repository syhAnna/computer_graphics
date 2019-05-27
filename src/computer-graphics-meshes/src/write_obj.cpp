#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Opens the file identified by argument filename, associating it with the stream object
  // write objects to the file according to the format in .obj file
  // https://en.wikipedia.org/wiki/Wavefront_.obj_file
  std::ofstream writeFile(filename);

  // check whether successfully open the file
  if (!writeFile) {
      return false;
  }

  // write vertex positions V
  // List of geometric vertices
  for (int i = 0; i < V.rows(); i++) {
      writeFile << "v" << " " << V(i, 0) << " " << V(i, 1) << " " << V(i, 2) << std::endl;
  }

  // write 2D parametrization position UV
  // List of texture coordinates
  for (int i = 0; i < UV.rows(); i++) {
      writeFile << "vt" << " " << UV(i, 0) << " " << UV(i, 1) << " " << UV(i, 2) << std::endl;
  }

  // write 3D normal vector NV
  // List of vertex normals
  for (int i = 0; i < NV.rows(); i++) {
      writeFile << "vn" << " " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << std::endl;
  }

  // write f : F UF NF
  // Polygonal face element
  for (int i = 0; i < F.rows(); i++) {
      writeFile << "f ";
      for (int j = 0; j < F.cols(); j++) {
          writeFile << (F(i, j) + 1) << "/" << (UF(i, j) + 1) << "/" << (NF(i, j) + 1) << " ";
      }
      writeFile << std::endl;
  }
  ////////////////////////////////////////////////////////////////////////////
  return true;
}
