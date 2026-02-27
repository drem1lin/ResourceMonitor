#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <chrono>

namespace core {

struct CpuMetrics {
    double usage_percent;
};

struct MemoryMetrics {
    uint64_t total;
    uint64_t used;
};

struct ProcessInfo {
    uint32_t pid;
    std::string name;
    uint64_t memory_bytes;
    double cpu_percent;
};

struct Snapshot {
    std::chrono::steady_clock::time_point timestamp;
    CpuMetrics cpu;
    MemoryMetrics memory;
    std::vector<ProcessInfo> processes;
};

} // namespace core