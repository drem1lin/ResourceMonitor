#pragma once

#include "structs.h"

namespace core::providers {

class ICpuCollector {
public:
    virtual ~ICpuCollector() = default;
    virtual CpuMetrics Collect() = 0;
};

class IMemoryCollector {
public:
    virtual ~IMemoryCollector() = default;
    virtual MemoryMetrics Collect() = 0;
};

class IProcessCollector {
public:
    virtual ~IProcessCollector() = default;
    virtual std::vector<ProcessInfo> Collect() = 0;
};

} // namespace core::providers