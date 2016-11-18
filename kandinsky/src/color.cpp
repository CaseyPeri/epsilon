#include <kandinsky/color.h>

KDColor KDColor::blend(KDColor first, KDColor second, uint8_t alpha) {
  /* This function is a hot path since it's being called for every single pixel
   * whenever we want to display a string. In this context, we're quite often
   * calling it with a value of either 0 or 0xFF, which can be very trivially
   * dealt with. So let's make a special case for them. */
  if (alpha == 0) {
    return second;
  } else if (alpha == 0xFF) {
    return first;
  }

  // We want to do first*alpha + second*(1-alpha)
  // First is RRRRR GGGGGG BBBBB
  // Second is same

  uint8_t oneMinusAlpha = 0xFF-alpha;
  uint16_t red = first.red()*alpha + second.red()*oneMinusAlpha;
  uint16_t green = first.green()*alpha + second.green()*oneMinusAlpha;
  uint16_t blue = first.blue()*alpha + second.blue()*oneMinusAlpha;
  return RGB888(red>>8, green>>8, blue>>8);


  // Blend White + black, ask for white
  // white.red() = 0x1F << 3 = 0xF8
//  white.red() * 0xFF = 0xF708, we wanted 0xF800
}

uint8_t KDColor::red() {
  uint8_t r5 = (m_value>>11)&0x1F;
  return r5 << 3;
}

uint8_t KDColor::green() {
  uint8_t g6 = (m_value>>5)&0x3F;
  return g6 << 2;
}

uint8_t KDColor::blue() {
  uint8_t b5 = m_value&0x1F;
  return b5 << 3;
}
