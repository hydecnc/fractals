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
  void update_reference(const std::complex<float> &center);

private:
  std::vector<std::complex<float>> m_orbit{};
  std::complex<float> m_prev_center{};
  GLuint m_ssbo{};

  void calculate_reference(const std::complex<float> &center);

  int nearby_iteration(
      const std::complex<float> point,
      const std::complex<float> reference_point,
      const std::vector<std::complex<float>> &reference_orbit) {
    const std::complex<float> dc{reference_point - point};

    std::complex<float> dz{0};
    for (int n{0}; n < reference_orbit.size(); ++n) {
      dz = 2.0f * reference_point * dz + dz * dz + dc;
      if (std::norm(reference_orbit[n] + dz) > conf::kFractalExitBoundary) {
        return n;
      }
    }
    return reference_orbit.size();
  }
};

#endif
