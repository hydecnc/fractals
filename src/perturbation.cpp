#include "configuration.h"
#include <complex>
#include <glm/vec2.hpp>
#include <vector>

std::vector<std::complex<float>>
calculate_reference(std::complex<float> center) {
  std::vector<std::complex<float>> reference_orbit{};

  std::complex<long double> z{0};
  for (int i{0}; i < conf::kMaxIteration; ++i) {
    z = z * z + static_cast<std::complex<long double>>(center);
    reference_orbit.push_back(static_cast<std::complex<float>>(z));
    if (std::norm(z) > conf::kFractalExitBoundary)
      break;
  }

  return reference_orbit;
}

int nearby_iteration(const std::complex<float> point,
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
