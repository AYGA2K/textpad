#include "explorer.h"
#include "filesystem"
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<ExplorerItem> buildTree(fs::path path) {
  std::vector<ExplorerItem> items;
  for (const auto &entry : fs::directory_iterator(path)) {
    ExplorerItem item = {};
    item.name = entry.path().filename().string();
    if (entry.is_directory()) {
      item.type = ItemType::DIRECTORY;
      item.children = buildTree(entry.path());
    } else {
      item.type = ItemType::FILE;
    }
    items.push_back(item);
  }
  return items;
}
void Explorer::render() {
  fs::path currentPath("../test");
  if (!fs::exists(currentPath)) {
    return;
  }
  this->items = buildTree(currentPath);
}
