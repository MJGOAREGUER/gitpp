#pragma once

#include <string>
#include <vector>

void cmd_add(const std::vector<std::string> &args);
void cmd_cat_file(const std::vector<std::string> &args);
void cmd_check_ignore(const std::vector<std::string> &args);
void cmd_checkout(const std::vector<std::string> &args);
void cmd_commit(const std::vector<std::string> &args);
void cmd_hash_object(const std::vector<std::string> &args);
void cmd_init(const std::vector<std::string> &args);
void cmd_log(const std::vector<std::string> &args);
void cmd_ls_files(const std::vector<std::string> &args);
void cmd_ls_tree(const std::vector<std::string> &args);
void cmd_rev_parse(const std::vector<std::string> &args);
void cmd_rm(const std::vector<std::string> &args);
void cmd_show_ref(const std::vector<std::string> &args);
void cmd_status(const std::vector<std::string> &args);
void cmd_tag(const std::vector<std::string> &args);
