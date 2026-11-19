#ifndef __DEFINE_H
#define __DEFINE_H

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH  800

#define FONT_SIZE      19
#define LETTER_SPACING -0.5

// FIXME: 9.0f is advanceX of the font. This changes for font size.
// we can only fetch it during runtime.
constexpr float STEP_WIDTH {
  (static_cast<float>(FONT_SIZE) / (FONT_SIZE + 1) * 9.0f + LETTER_SPACING)
};

#define MOUSE_SENSITIVITY 20

#endif

