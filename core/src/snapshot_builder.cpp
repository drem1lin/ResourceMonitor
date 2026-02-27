#include "snapshot_builder.h"

namespace core::snapshot {

Snapshot SnapshotBuilder::Build() {
    Snapshot snapshot{};
    snapshot.timestamp = std::chrono::steady_clock::now();
    snapshot.cpu = cpuCollector_->Collect();
    snapshot.memory = memoryCollector_->Collect();
    snapshot.processes = processCollector_->Collect();
    return snapshot;
}

} // namespace core::snapshot