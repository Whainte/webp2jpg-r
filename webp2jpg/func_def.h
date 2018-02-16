#pragma once

#include<filesystem>

namespace fs = std::experimental::filesystem;
inline void showHelp();
void conv_recursive(fs::path); //TODO: add depth
void conv(fs::path);