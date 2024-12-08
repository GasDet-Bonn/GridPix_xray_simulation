# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(gem)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
find_package(HDF5 REQUIRED COMPONENTS CXX)

# ---Build executables-----------------------------------------------------------
add_compile_options(-Wall -Wextra -Wpedantic)

# Executable for simulation
add_executable(simulation simulation.C)
target_link_libraries(simulation Garfield::Garfield ${HDF5_LIBRARIES})
target_include_directories(simulation PRIVATE ${HDF5_INCLUDE_DIRS})

# Executable for gasparameters
add_executable(gasparameters gasparameters.C)
target_link_libraries(gasparameters Garfield::Garfield ${HDF5_LIBRARIES})
target_include_directories(gasparameters PRIVATE ${HDF5_INCLUDE_DIRS})

# ---Copy all files locally to the build directory-------------------------------
foreach(_file degrad.run tpx3_config.h5 config_template/chip_1_board_0_fec_0_fsr.txt config_template/chip_1_board_0_fec_0_matrix.txt config_template/chip_1_board_0_fec_0_threshold.txt)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()
