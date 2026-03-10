add_library(platform STATIC)

target_link_libraries(platform
  PUBLIC core
)

target_compile_features(platform PUBLIC cxx_std_20)

target_include_directories(platform
  PUBLIC include
  PRIVATE private_include
)

if(UNIX)
  target_sources(platform PRIVATE
    linux/cpu_collector.cpp
    linux/memory_collector.cpp
    linux/process_collector.cpp
  )
endif()

if(WIN32)
  target_sources(platform PRIVATE
    windows/cpu_collector.cpp
    windows/memory_collector.cpp
    windows/process_collector.cpp
  )
endif()