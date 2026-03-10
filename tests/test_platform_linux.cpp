#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <unistd.h>

#include "core/structs.h"
#include "parsers.h" //platform/private_include

TEST(LinuxCpuCollector, ParsesCpuStat) {

    std::stringstream data;
    data << "cpu 100 0 50 50\n";
 
    core::CpuMetrics m = platform::details::ParseCpuStat(data);

    EXPECT_NEAR(m.usage_percent, 75.0, 0.01);
}

TEST(ProcIntegration, CpuStatFromRealSystem)
{
    std::ifstream file("/proc/stat");
    ASSERT_TRUE(file.is_open());

    auto metrics = platform::details::ParseCpuStat(file);

    EXPECT_GE(metrics.usage_percent, 0.0);
    EXPECT_LE(metrics.usage_percent, 100.0);
}

TEST(LinuxMemoryCollector, ParsesMemInfo) {

    std::stringstream data;
    data
        << "MemTotal: 1000 kB\n"
        << "MemFree: 100 kB\n"
        << "MemAvailable: 400 kB\n";

    core::MemoryMetrics m = platform::details::ParseMemInfo(data);

    EXPECT_EQ(m.total, 1000 * 1024);
    EXPECT_EQ(m.used, 600 * 1024);
}

TEST(ProcIntegration, MemInfoFromRealSystem)
{
    std::ifstream file("/proc/meminfo");
    ASSERT_TRUE(file.is_open());

    auto mem = platform::details::ParseMemInfo(file);

    EXPECT_GT(mem.total, 0);
    EXPECT_GT(mem.used, 0);

    EXPECT_LE(mem.used, mem.total);
}