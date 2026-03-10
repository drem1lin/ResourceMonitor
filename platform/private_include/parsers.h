#pragma once

#include <istream>
#include "core/structs.h"

namespace platform::details {
    core::CpuMetrics ParseCpuStat(std::istream&);
    core::MemoryMetrics ParseMemInfo(std::istream&);
} // namespace platform::details