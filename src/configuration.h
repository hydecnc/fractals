#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <complex>

namespace conf {
inline constexpr unsigned int kScrWidth{800};
inline constexpr unsigned int kScrHeight{600};
inline constexpr unsigned int kMaxIteration{200};
inline constexpr int kGameWidth{10};
inline constexpr int kGameHeight{10};
inline constexpr float kGameWidthf{static_cast<float>(kGameWidth)};
inline constexpr float kGameHeightf{static_cast<float>(kGameHeight)};
inline constexpr std::complex<float> kFractalCenter{-0.5f, 0.0f};
inline constexpr float kFractalExitBoundary{256.0f * 256.0f};
inline constexpr float kScrollSpeed{1.3f};
inline constexpr double kKeyPressMoveAmount{10.0};
inline constexpr float kInitialZoom{1.0f};
inline constexpr float kMaxZoomScale{3e13f};
inline constexpr float kMinZoomScale{0.1f};
inline constexpr float kPanSensitivity{0.01f};
} // namespace conf

#endif
