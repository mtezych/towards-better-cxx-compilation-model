
cmake_minimum_required (VERSION 3.15)

project(AsyncTaskLibrary VERSION 1.0.0 LANGUAGES CXX)

find_package(Threads REQUIRED)


add_library               (async-task-library STATIC)

target_compile_features   (async-task-library PUBLIC  cxx_std_17)

target_include_directories(async-task-library PUBLIC  include)

target_link_libraries     (async-task-library PUBLIC ${CMAKE_THREAD_LIBS_INIT})

target_sources            (async-task-library PRIVATE include/atl/task_queue.hxx
                                                      include/atl/task_system.hxx
                                                           source/task_queue.cxx
                                                           source/task_system.cxx)
