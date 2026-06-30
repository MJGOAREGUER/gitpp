#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "commands/Command.hpp"

static const std::unordered_map<
    std::string, std::function<void(const std::vector<std::string> &)>>
    commands = {
        {"add", cmd_add},
        {"cat-file", cmd_cat_file},
        {"check-ignore", cmd_check_ignore},
        {"checkout", cmd_checkout},
        {"commit", cmd_commit},
        {"hash-object", cmd_hash_object},
        {"init", cmd_init},
        {"log", cmd_log},
        {"ls-files", cmd_ls_files},
        {"ls-tree", cmd_ls_tree},
        {"rev-parse", cmd_rev_parse},
        {"rm", cmd_rm},
        {"show-ref", cmd_show_ref},
        {"status", cmd_status},
        {"tag", cmd_tag},
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "[ERROR] Usage: git++ <command> [args...]\n";
    return EXIT_FAILURE;
  }

  // We get the first argument as the command not the 0 its the name of the
  // copyright
  std::string command = argv[1];
  std::vector<std::string> args(argv + 2, argv + argc);

  auto it = commands.find(command);
  if (it == commands.end()) {
    std::cerr << "[ERROR] git++: bad command '" << command << "'\n";
    return EXIT_FAILURE;
  }

  try {
    it->second(args);
  } catch (const std::exception &e) {
    std::cerr << "[ERROR] fatal: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
