#include "core/providers.h"
#include "core/structs.h"
#include "platform/factories.h"

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

namespace platform::details {

class LinuxProcessCollector : public core::providers::IProcessCollector {
public:

    std::vector<core::ProcessInfo> Collect() override {

        std::vector<core::ProcessInfo> result;

        for(auto &p : fs::directory_iterator("/proc")) {

            if(!p.is_directory())
                continue;

            auto name = p.path().filename().string();

            if(!std::all_of(name.begin(), name.end(), ::isdigit))
                continue;

            core::ProcessInfo info{};
            info.pid = std::stoi(name);

            result.emplace_back(std::move(info));
        }

        return result;
    }
};

} // namespace platform:: details

std::unique_ptr<core::providers::IProcessCollector> platform::CreateProcessCollector() 
{
    return std::make_unique<platform::details::LinuxProcessCollector>();
}