add_executable(monitord
  src/main.cpp
)

target_compile_features(monitord PRIVATE cxx_std_20)

target_link_libraries(monitord
  PRIVATE core
)
