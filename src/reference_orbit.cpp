#include "reference_orbit.h"
#include <iostream>

ReferenceOrbit::ReferenceOrbit() { glGenBuffers(1, &m_ssbo); }

void ReferenceOrbit::bind() const {
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_ssbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

std::vector<std::complex<float>> ReferenceOrbit::reference_orbit() const {
  return m_orbit;
}

void ReferenceOrbit::update_reference(const std::complex<double> &center) {
  calculate_reference(center);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
  glBufferData(GL_SHADER_STORAGE_BUFFER,
               m_orbit.size() * sizeof(std::complex<float>), m_orbit.data(),
               GL_DYNAMIC_DRAW);
}

void ReferenceOrbit::calculate_reference(const std::complex<double> &center) {
  m_orbit.clear();

  std::complex<long double> z{0};
  for (int i{0}; i < conf::kMaxIteration; ++i) {
    m_orbit.push_back(static_cast<std::complex<float>>(z));
    z = z * z + static_cast<std::complex<long double>>(center);
    if (std::norm(z) > conf::kFractalExitBoundary)
      break;
  }
}
