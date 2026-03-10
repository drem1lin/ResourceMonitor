#include "core/providers.h"
#include "core/structs.h"
#include "platform/factories.h"

#include <fstream>
#include <string>



namespace platform::details {

core::CpuMetrics ParseCpuStat(std::istream& in) 
{
    std::string cpu;
    uint64_t user=0, nice=0, system=0, idle=0;

    in >> cpu >> user >> nice >> system >> idle;

    uint64_t total = user + nice + system + idle;

    core::CpuMetrics m{};
    m.usage_percent = total == 0 ? 
        0.0 : 
        100.0 * (total - idle) / total;

    return m;
}

class LinuxCpuCollector : public core::providers::ICpuCollector 
{
public:

    core::CpuMetrics Collect() override {
        std::ifstream file("/proc/stat");
        return ParseCpuStat(file);
    }
};

} // namespace platform::details

std::unique_ptr<core::providers::ICpuCollector> platform::CreateCpuCollector() 
{
    return std::make_unique<platform::details::LinuxCpuCollector>();
}