#pragma once

#include <memory>
#include "core/providers.h"

namespace platform {

std::unique_ptr<core::providers::ICpuCollector> CreateCpuCollector();
std::unique_ptr<core::providers::IMemoryCollector> CreateMemoryCollector();
std::unique_ptr<core::providers::IProcessCollector> CreateProcessCollector();

} // namespace platform