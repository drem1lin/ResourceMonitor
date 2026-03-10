#include "core/providers.h"
#include "core/structs.h"
#include "platform/factories.h"

#include <fstream>
#include <string>

namespace platform::details{

core::MemoryMetrics ParseMemInfo(std::istream& in) {
    std::string key;
    uint64_t value;
    std::string unit;

    uint64_t total = 0;
    uint64_t avail = 0;

    while (in >> key >> value >> unit) {
        if (key == "MemTotal:")
            total = value;
        else if (key == "MemAvailable:")
            avail = value;
    }

    core::MemoryMetrics m{};
    m.total = total * 1024;
    m.used = (total - avail) * 1024;
    return m;
}

class LinuxMemoryCollector : public core::providers::IMemoryCollector {
public:

    core::MemoryMetrics Collect() override 
    {
        std::ifstream file("/proc/meminfo");
        return ParseMemInfo(file);
    }
};

} // namespace platform:: details

std::unique_ptr<core::providers::IMemoryCollector> platform::CreateMemoryCollector() {
    return std::make_unique<platform::details::LinuxMemoryCollector>();
}