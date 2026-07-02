#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace fs = std::filesystem;

using GitConfig = std::map<std::string, std::map<std::string, std::string>>;

class GitRepository {
public:
  // Constructor
  GitRepository(const fs::path &path, bool force = false);

  // Create a new repo on the disk
  static GitRepository create(const fs::path &path);

  // Utils for path
  fs::path path(const std::vector<std::string> &parts) const;
  fs::path dir(const std::vector<std::string> &parts, bool mkdir = false) const;
  fs::path file(const std::vector<std::string> &parts,
                bool mkdir = false) const;

  // Getters
  const fs::path &worktree() const { return m_worktree; }
  const fs::path &gitdir() const { return m_gitdir; }
  const GitConfig &config() const { return m_conf; }

private:
  fs::path m_worktree;
  fs::path m_gitdir;
  GitConfig m_conf;

  static GitConfig parseConfig(const fs::path &filepath);
  static void writeConfig(const fs::path &filepath, const GitConfig &config);
  static GitConfig defaultConfig();
};
