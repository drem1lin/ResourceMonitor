add_library(core STATIC
  src/core.cpp
  src/snapshot_builder.cpp
  private_include/snapshot_builder.h
  include/core/snapshot.h
  include/core/structs.h
  include/core/providers.h
)

target_include_directories(core 
  PRIVATE private_include
  PUBLIC include)
target_compile_features(core PUBLIC cxx_std_20)
