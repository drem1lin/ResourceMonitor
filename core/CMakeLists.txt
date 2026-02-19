add_library(core STATIC
  src/core.cpp
  include/core/core.h
)

target_include_directories(core 
  PRIVATE private_include
  PUBLIC include)
target_compile_features(core PUBLIC cxx_std_20)
