#include "ext/rope"
#include "state.h"
namespace gnu = __gnu_cxx;
enum class EdiorMode { NORMAL, INSERT, VISUAL };
struct Cursor {
  int x;
  int y;
};
struct Editor {
  State *state;
  bool isFocused;
  Cursor cursor;
  EdiorMode mode;
  gnu::crope text;
  int lastKey = 0;
  void moveCursor();
  void draw();
};
