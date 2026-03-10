include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

add_executable(tests
  test_snapshot_builder.cpp
  test_process_collector.cpp
)

if(UNIX)
  target_sources(tests PRIVATE
    test_platform_linux.cpp
  )
endif()

target_compile_features(tests PRIVATE cxx_std_20)

target_include_directories(tests PRIVATE
    ${PROJECT_SOURCE_DIR}/core/private_include
    ${PROJECT_SOURCE_DIR}/platform/private_include
    ${PROJECT_SOURCE_DIR}/platform/include
)

target_link_libraries(tests PRIVATE
  core
  platform
  GTest::gtest_main
  GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(tests)
