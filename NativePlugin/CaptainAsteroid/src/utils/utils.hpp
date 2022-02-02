#pragma once

#include <string>

namespace Utils
{
constexpr float PI = 3.14159274101257324219;

const std::string GetSrcDir();
const std::string GetInstallDir();
const std::string GetVersions();
const std::string FloatToStr(float val, size_t precision = 10);
}// namespace Utils
