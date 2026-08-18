cmake_minimum_required(VERSION 3.16)

project(ConfigReader VERSION 1.0.0 LANGUAGES CXX)

# --------------------------------
# C++
# --------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# --------------------------------
# Library
# --------------------------------
add_library(ConfigReader
    src/ConfigReader.cpp
)

target_include_directories(ConfigReader
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<INSTALL_INTERFACE:include>
)

add_library(ConfigReader::ConfigReader ALIAS ConfigReader)

# --------------------------------
# Testing
# --------------------------------
enable_testing()
add_executable(test_app
    test/Test.cpp
)

target_link_libraries(test_app PRIVATE ConfigReader)
add_test(NAME test_app COMMAND test_app)

# Copy System.ini to build directory for testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/System.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



# --------------------------------
# Install rules (portable)
# --------------------------------
include(GNUInstallDirs)

install(TARGETS ConfigReader
    EXPORT ConfigReaderTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY includes/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# --------------------------------
# Package config (must be last)
# --------------------------------
install(EXPORT ConfigReaderTargets
    FILE ConfigReaderTargets.cmake
    NAMESPACE ConfigReader::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ConfigReader
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ConfigReaderConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ConfigReaderConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ConfigReaderConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ConfigReader
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ConfigReaderConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ConfigReaderConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ConfigReader
)