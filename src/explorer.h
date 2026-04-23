#pragma once
#include <string>
#include <vector>

enum class ItemType { FILE, DIRECTORY };

struct ExplorerItem {
  std::string name;
  ItemType type;
  std::vector<ExplorerItem> children;
};

struct Explorer {
  std::string path;
  std::vector<ExplorerItem> items;
  bool visible;
  void render();
  void show();
  void hide();
  void move(int key);
  void deleteFile(int cursorX);
  void copyFile(int cursorX);
  void moveFile(int cursorX);
};
