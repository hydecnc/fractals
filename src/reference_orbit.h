#ifndef REFERENCE_ORBIT_H_
#define REFERENCE_ORBIT_H_

#include "configuration.h"
#include <complex>
#include <glad/glad.h>
#include <vector>

class ReferenceOrbit {
public:
  ReferenceOrbit();
  std::vector<std::complex<float>> reference_orbit() const;

  void bind() const;
  void update_reference(const std::complex<double> &center);

private:
  std::vector<std::complex<float>> m_orbit{};
  GLuint m_ssbo{};

  void calculate_reference(const std::complex<double> &center);
};

#endif
