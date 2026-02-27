#pragma once

#include "core/snapshot.h"
#include "core/providers.h"
#include "memory"

namespace core::snapshot {

class SnapshotBuilder : public ISnapshotBuilder {
public:
    SnapshotBuilder(std::shared_ptr<providers::ICpuCollector> cpuCollector,
                    std::shared_ptr<providers::IMemoryCollector> memoryCollector,
                    std::shared_ptr<providers::IProcessCollector> processCollector) 
        : cpuCollector_(cpuCollector)
        , memoryCollector_(memoryCollector)
        , processCollector_(processCollector) 
    {}

    Snapshot Build() override;

private:
    std::shared_ptr<providers::ICpuCollector> cpuCollector_;
    std::shared_ptr<providers::IMemoryCollector> memoryCollector_;
    std::shared_ptr<providers::IProcessCollector> processCollector_;
};

} // namespace core::snapshot