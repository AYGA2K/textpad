#pragma once
#include "raylib.h"
#include <string>
#include <vector>

enum class ItemType { FILE, DIRECTORY };

struct ExplorerItem {
  std::string parent;
  std::string name;
  ItemType type;
  std::vector<ExplorerItem> children;
  bool isOpen;
};

struct Explorer {
  std::string path;
  std::vector<ExplorerItem> items;
  bool visible;
  Vector2 scrollOffset = {0, 0};
  ExplorerItem *selectedItem = nullptr;
  void scan();
  void draw();
  void show();
  void hide();
  void move(int key);
  void deleteFile(int cursorX);
  void copyFile(int cursorX);
  void moveFile(int cursorX);
};
