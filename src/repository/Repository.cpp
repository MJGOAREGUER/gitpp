#include "Repository.hpp"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

// Constructor
GitRepository::GitRepository(const fs::path &path, bool force) {
  m_worktree = path;
  m_gitdir = path / ".git";

  if (!force && !fs::is_directory(m_gitdir))
    throw std::runtime_error("[ERROR] Not a git++ repository: " +
                             path.string());

  fs::path config_path = m_gitdir / "config";

  if (fs::exists(config_path)) {
    m_conf = parseConfig(config_path);
  } else if (!force) {
    throw std::runtime_error("[ERROR] Configuration file missing");
  }

  if (!force) {
    int vers = std::stoi(m_conf["core"]["repositoryformatversion"]);
    if (vers != 0) {
      throw std::runtime_error("[ERROR] Unsuported repositoryformatversion: " +
                               std::to_string(vers));
    }
  }
}

// Create a repo
GitRepository GitRepository::create(const fs::path &path) {
  GitRepository repo(path, true);

  if (fs::exists(repo.m_worktree)) {
    if (!fs::is_directory(repo.m_worktree)) {
      throw std::runtime_error("[ERROR] " + path.string() +
                               " is not a directory!");
    }
    if (fs::exists(repo.m_gitdir) && !fs::is_empty(repo.m_gitdir)) {
      throw std::runtime_error("[ERROR] " + path.string() + " is not empty!");
    }
  } else {
    fs::create_directories(repo.m_worktree);
  }

  repo.dir({"branches"}, true);
  repo.dir({"objects"}, true);
  repo.dir({"refs", "tags"}, true);
  repo.dir({"refs", "heads"}, true);

  std::ofstream(repo.file({"description"}))
      << "Unnamed repository; edit this file 'description' to name the "
         "repository.\n";

  std::ofstream(repo.file({"HEAD"})) << "ref: ref/heads/master\n";

  repo.m_conf = defaultConfig();
  writeConfig(repo.file({"config"}), repo.m_conf);

  return repo;
}

// Utils for path
fs::path GitRepository::path(const std::vector<std::string> &parts) const {
  fs::path p = m_gitdir;

  for (auto &part : parts)
    p /= part;

  return p;
}

fs::path GitRepository::dir(const std::vector<std::string> &parts,
                            bool mkdir) const {
  fs::path p = path(parts);

  if (fs::exists(p)) {
    if (fs::is_directory(p))
      return p;
    throw std::runtime_error("[ERROR] Not a directory: " + p.string());
  }

  if (mkdir) {
    fs::create_directories(p);
    return p;
  }

  return {};
}

fs::path GitRepository::file(const std::vector<std::string> &parts,
                             bool mkdir) const {
  std::vector<std::string> parent(parts.begin(), parts.end() - 1);

  if (!parent.empty())
    dir(parent, mkdir);

  return path(parts);
}

// Config Ini
GitConfig GitRepository::parseConfig(const fs::path &filepath) {
  GitConfig config;
  std::ifstream f(filepath);
  std::string line, section;

  while (std::getline(f, line)) {
    // Ignore empty line or comment line
    if (line.empty() || line[0] == ';' || line[0] == '#')
      continue;

    // Detect if its section [name]
    if (line.front() == '[') {
      section = line.substr(1, line.find(']') - 1);
    } else {
      // key=value
      auto eq = line.find('=');

      if (eq == std::string::npos)
        continue;

      std::string key = line.substr(0, eq);
      std::string value = line.substr(eq + 1);

      // trim
      key.erase(key.find_last_not_of(" \t") + 1);
      value.erase(0, value.find_first_not_of(" \t"));

      config[section][key] = value;
    }
  }
  return config;
}

void GitRepository::writeConfig(const fs::path &filepath,
                                const GitConfig &config) {
  std::ofstream f(filepath);

  for (auto &[section, keys] : config) {
    f << "[" << section << "]\n";
    for (auto &[key, value] : keys) {
      f << "\t" << key << " = " << value << "\n";
    }
  }
}

GitConfig GitRepository::defaultConfig() {
  GitConfig config;
  config["core"]["repositoryformatversion"] = "0";
  config["core"]["filemode"] = "false";
  config["core"]["bare"] = "false";
  return config;
}
