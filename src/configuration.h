#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <glm/vec2.hpp>

namespace conf {
inline constexpr unsigned int kScrWidth{800};
inline constexpr unsigned int kScrHeight{600};
inline constexpr unsigned int kMaxIteration{100};
inline constexpr int kGameWidth{10};
inline constexpr int kGameHeight{10};
inline constexpr float kGameWidthf{static_cast<float>(kGameWidth)};
inline constexpr float kGameHeightf{static_cast<float>(kGameHeight)};
inline constexpr glm::vec2 kFractalCenter{-0.5f, 0.0f};
inline constexpr float kScrollSpeed{0.3f};
} // namespace conf

#endif
