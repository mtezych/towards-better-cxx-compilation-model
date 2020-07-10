
cmake_minimum_required (VERSION 3.15)


add_executable            (physics-simulation)

target_compile_features   (physics-simulation PRIVATE cxx_std_17)

target_sources            (physics-simulation PRIVATE source/physics_simulation.cxx)

target_link_libraries     (physics-simulation PRIVATE async-task-library)
