#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
void deleteLogFile() { std::filesystem::remove("log.txt"); }
void logToFile(const std::string &message) {
  std::ofstream logFile("log.txt", std::ios::app);
  if (!logFile) {
    return;
  }
  logFile << message << '\n';
}

std::string readFile(const std::string &path) {
  std::ifstream file(path);
  if (!file)
    return "";

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::string EditorData = "Hello world!";

enum class FileType { Directory, File };
struct DirectoryItem {
  std::string name;
  std::string path;
  FileType type;
  void click() const {
    if (type == FileType::Directory) {
      // TODO: open directory
      EditorData = "This is a directory";
    } else {
      EditorData = readFile(path);
    }
  }
};
std::vector<DirectoryItem> GetDirectoryItems(const std::string &path) {
  std::vector<DirectoryItem> items;
  for (const auto &entry : std::filesystem::directory_iterator(path)) {
    if (entry.is_directory()) {
      items.push_back({entry.path().filename().string(), entry.path().string(),
                       FileType::Directory});
    } else {
      items.push_back({entry.path().filename().string(), entry.path().string(),
                       FileType::File});
    }
  }
  return items;
}
ftxui::Component FileList(const std::string &path) {
  auto items = GetDirectoryItems(path);

  auto list = ftxui::Container::Vertical({});

  for (const auto &item : items) {
    std::string label =
        (item.type == FileType::Directory ? "📁 " : "📄 ") + item.name;

    auto option = ftxui::ButtonOption::Simple();
    option.transform = [](const ftxui::EntryState &s) {
      auto element =
          ftxui::text(s.label) | size(ftxui::HEIGHT, ftxui::EQUAL, 1);
      if (s.focused)
        element = element | ftxui::bold | color(ftxui::Color::Blue);
      return element;
    };

    auto button = Button(label, [item] { item.click(); }, option);
    list->Add(button);
  }

  return ftxui::Renderer(list, [list] {
    return list->Render() | ftxui::vscroll_indicator | ftxui::frame;
  });
}

int main() {
  deleteLogFile();
  auto fileList = FileList("/home/ayoub/code/textpad");
  ftxui::InputOption option;
  option.multiline = true;
  option.transform = [](ftxui::InputState state) {
    if (state.focused) {
      state.element |= color(ftxui::Color::Red);
    }
    return state.element;
  };
  auto input = ftxui::Input(&EditorData, option);
  auto editor =
      ftxui::Input(&EditorData) | ftxui::frame | ftxui::vscroll_indicator;
  auto layout = ftxui::Container::Vertical(
      {ftxui::Container::Horizontal({
           fileList | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30),
           editor,
       }) | ftxui::flex,
       ftxui::Renderer([=] { return ftxui::separator(); }),
       ftxui::Renderer([=] {
         return ftxui::vbox({
             ftxui::text("Hello world! this the status bar place holder :)"),
         });
       })});

  auto screen = ftxui::ScreenInteractive::Fullscreen();
  screen.Loop(layout);

  return 0;
}
