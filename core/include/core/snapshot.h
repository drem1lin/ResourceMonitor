#pragma once

#include "structs.h"

namespace core::snapshot {

class ISnapshotBuilder {
public:
    virtual ~ISnapshotBuilder() = default;
    virtual Snapshot Build() = 0;
};

} // namespace core::snapshot