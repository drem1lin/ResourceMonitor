#include <gtest/gtest.h>
#include <unistd.h>

#include "core/structs.h"
#include "platform/factories.h"


TEST(ProcessCollectorLinux, ReturnsProcesses)
{
    auto collector = platform::CreateProcessCollector();

    auto processes = collector->Collect();

    EXPECT_FALSE(processes.empty());
}

TEST(ProcessCollectorLinux, ContainsCurrentProcess)
{
    auto collector = platform::CreateProcessCollector();

    auto processes = collector->Collect();

    int current_pid = getpid();

    auto it = std::find_if(processes.begin(), processes.end(),
        [&](const core::ProcessInfo& p)
        {
            return p.pid == current_pid;
        });

    EXPECT_TRUE(it != processes.end());
}

TEST(ProcessCollectorLinux, PidsArePositive)
{
    auto collector = platform::CreateProcessCollector();

    auto processes = collector->Collect();

    for (const auto& p : processes)
    {
        EXPECT_GT(p.pid, 0);
    }
}