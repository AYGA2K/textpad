#pragma once

// Catppuccin Mocha palette — https://catppuccin.com/palette
static const unsigned int MOCHA_ROSEWATER = 0xf5e0dcff;
static const unsigned int MOCHA_FLAMINGO  = 0xf2cdcdff;
static const unsigned int MOCHA_PINK      = 0xf5c2e7ff;
static const unsigned int MOCHA_MAUVE     = 0xcba6f7ff;
static const unsigned int MOCHA_RED       = 0xf38ba8ff;
static const unsigned int MOCHA_MAROON    = 0xeba0acff;
static const unsigned int MOCHA_PEACH     = 0xfab387ff;
static const unsigned int MOCHA_YELLOW    = 0xf9e2afff;
static const unsigned int MOCHA_GREEN     = 0xa6e3a1ff;
static const unsigned int MOCHA_TEAL      = 0x94e2d5ff;
static const unsigned int MOCHA_SKY       = 0x89dcebff;
static const unsigned int MOCHA_SAPPHIRE  = 0x74c7ecff;
static const unsigned int MOCHA_BLUE      = 0x89b4faff;
static const unsigned int MOCHA_LAVENDER  = 0xb4befeff;
static const unsigned int MOCHA_TEXT      = 0xcdd6f4ff;
static const unsigned int MOCHA_SUBTEXT1  = 0xbac2deff;
static const unsigned int MOCHA_SUBTEXT0  = 0xa6adc8ff;
static const unsigned int MOCHA_OVERLAY2  = 0x9399b2ff;
static const unsigned int MOCHA_OVERLAY1  = 0x7f849cff;
static const unsigned int MOCHA_OVERLAY0  = 0x6c7086ff;
static const unsigned int MOCHA_SURFACE2  = 0x585b70ff;
static const unsigned int MOCHA_SURFACE1  = 0x45475aff;
static const unsigned int MOCHA_SURFACE0  = 0x313244ff;
static const unsigned int MOCHA_BASE      = 0x1e1e2eff;
static const unsigned int MOCHA_MANTLE    = 0x181825ff;
static const unsigned int MOCHA_CRUST     = 0x11111bff;

// UI variants with reduced alpha
static const unsigned int MOCHA_HOVER_BG   = 0x31324488; // surface0 ~50% alpha
static const unsigned int MOCHA_PRESSED_BG = 0x585b70bb; // surface2 ~73% alpha
static const unsigned int MOCHA_TRANSPARENT = 0x00000000;

#define CATPPUCCIN_MOCHA_STYLE_PROPS_COUNT 14

static const GuiStyleProp
    catppuccinMochaStyleProps[CATPPUCCIN_MOCHA_STYLE_PROPS_COUNT] = {
        {0,  0, (int)MOCHA_SURFACE2},  // DEFAULT_BORDER_COLOR_NORMAL
        {0,  1, (int)MOCHA_SURFACE0},  // DEFAULT_BASE_COLOR_NORMAL
        {0,  2, (int)MOCHA_TEXT},      // DEFAULT_TEXT_COLOR_NORMAL
        {0,  3, (int)MOCHA_OVERLAY1},  // DEFAULT_BORDER_COLOR_FOCUSED
        {0,  4, (int)MOCHA_SURFACE1},  // DEFAULT_BASE_COLOR_FOCUSED
        {0,  5, (int)MOCHA_TEXT},      // DEFAULT_TEXT_COLOR_FOCUSED
        {0,  6, (int)MOCHA_MAUVE},     // DEFAULT_BORDER_COLOR_PRESSED
        {0,  7, (int)MOCHA_SURFACE2},  // DEFAULT_BASE_COLOR_PRESSED
        {0,  8, (int)MOCHA_BASE},      // DEFAULT_TEXT_COLOR_PRESSED
        {0,  9, (int)MOCHA_OVERLAY0},  // DEFAULT_BORDER_COLOR_DISABLED
        {0, 10, (int)MOCHA_MANTLE},    // DEFAULT_BASE_COLOR_DISABLED
        {0, 11, (int)MOCHA_OVERLAY1},  // DEFAULT_TEXT_COLOR_DISABLED
        {0, 18, (int)MOCHA_SURFACE2},  // DEFAULT_LINE_COLOR
        {0, 19, (int)MOCHA_BASE},      // DEFAULT_BACKGROUND_COLOR
};

static void GuiLoadStyleCatppuccinMocha(void) {
  for (int i = 0; i < CATPPUCCIN_MOCHA_STYLE_PROPS_COUNT; i++) {
    GuiSetStyle(catppuccinMochaStyleProps[i].controlId,
                catppuccinMochaStyleProps[i].propertyId,
                catppuccinMochaStyleProps[i].propertyValue);
  }
}
