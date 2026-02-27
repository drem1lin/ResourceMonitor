#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "snapshot_builder.h"          //  core/private_include
#include "core/snapshot.h"
#include "core/structs.h"
#include "core/providers.h"  

using namespace core;

class MockCpuCollector : public providers::ICpuCollector {
public:
  MOCK_METHOD(CpuMetrics, Collect, (), (override));
};

class MockMemoryCollector : public providers::IMemoryCollector {
public:
  MOCK_METHOD(MemoryMetrics, Collect, (), (override));
};

class MockProcessCollector : public providers::IProcessCollector {
public:
  MOCK_METHOD(std::vector<ProcessInfo>, Collect, (), (override));
};

TEST(SnapshotBuilder, BuildsSnapshotFromProviders) {
    auto cpu = std::make_shared<MockCpuCollector>();
    ON_CALL(*cpu, Collect()).WillByDefault(::testing::Return(CpuMetrics{.usage_percent = 12.5}));
  
    auto mem = std::make_shared<MockMemoryCollector>();
    ON_CALL(*mem, Collect()).WillByDefault(::testing::Return(MemoryMetrics{ .total = 1000, .used = 250 }));

    auto proc = std::make_shared<MockProcessCollector>();
    ON_CALL(*proc, Collect()).WillByDefault(::testing::Return(std::vector<ProcessInfo>{
        ProcessInfo{ .pid = 1, .name = "init", .memory_bytes = 111, .cpu_percent = 1.0 },
        ProcessInfo{ .pid = 2, .name = "worker", .memory_bytes = 222, .cpu_percent = 2.0 },
        }));
   
    snapshot::SnapshotBuilder builder(cpu, mem, proc);
    Snapshot snap = builder.Build();

    EXPECT_GT(snap.timestamp.time_since_epoch().count(), 0) ;

    EXPECT_DOUBLE_EQ(snap.cpu.usage_percent, 12.5);
    EXPECT_EQ(snap.memory.total, 1000u);
    EXPECT_EQ(snap.memory.used, 250u);

    ASSERT_EQ(snap.processes.size(), 2u);
    EXPECT_EQ(snap.processes[0].pid, 1u); 
    EXPECT_EQ(snap.processes[1].name, "worker");
}