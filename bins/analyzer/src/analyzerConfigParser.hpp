#pragma once
#include "analyzerConfig.hpp"

#include <string>

namespace AnalyzerConfigParser {

AnalyzerConfig parseFile(const std::string& path);

} // namespace AnalyzerConfigParser
