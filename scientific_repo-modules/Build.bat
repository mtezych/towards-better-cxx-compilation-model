
@echo off

mkdir build
cd    build


cl /nologo                                                                     ^
   /std:c++latest                                                              ^
   /experimental:module                                                        ^
   /EHsc                                                                       ^
   /GR                                                                         ^
   /MDd                                                                        ^
   /W4                                                                         ^
   /Od /Ob0                                                                    ^
   /module:interface                                                           ^
   /c ..\async_task_library\itrf\task_queue.ixx

cl /nologo                                                                     ^
   /std:c++latest                                                              ^
   /experimental:module                                                        ^
   /EHsc                                                                       ^
   /GR                                                                         ^
   /MDd                                                                        ^
   /W4                                                                         ^
   /Od /Ob0                                                                    ^
   /module:interface                                                           ^
   /module:reference atl-task_queue.ifc                                        ^
   /c ..\async_task_library\itrf\task_system.ixx

cl /nologo                                                                     ^
   /std:c++latest                                                              ^
   /experimental:module                                                        ^
   /EHsc                                                                       ^
   /GR                                                                         ^
   /MDd                                                                        ^
   /W4                                                                         ^
   /Od /Ob0                                                                    ^
   /module:interface                                                           ^
   /module:reference atl-task_queue.ifc                                        ^
   /module:reference atl-task_system.ifc                                       ^
   /c ..\async_task_library\itrf\async_task_library.ixx

cl /nologo                                                                     ^
   /std:c++latest                                                              ^
   /experimental:module                                                        ^
   /EHsc                                                                       ^
   /GR                                                                         ^
   /MDd                                                                        ^
   /W4                                                                         ^
   /Od /Ob0                                                                    ^
   /module:reference atl-task_queue.ifc                                        ^
   /c ..\async_task_library\impl\task_queue.cxx                                ^
   /Fo"task_queue.cxx.obj"

cl /nologo                                                                     ^
   /std:c++latest                                                              ^
   /experimental:module                                                        ^
   /EHsc                                                                       ^
   /GR                                                                         ^
   /MDd                                                                        ^
   /W4                                                                         ^
   /Od /Ob0                                                                    ^
   /module:reference atl-task_queue.ifc                                        ^
   /module:reference atl-task_system.ifc                                       ^
   /c ..\async_task_library\impl\task_system.cxx                               ^
   /Fo"task_system.cxx.obj"

lib /NOLOGO                                                                    ^
    task_queue.obj                                                             ^
    task_system.obj                                                            ^
    async_task_library.obj                                                     ^
    task_queue.cxx.obj                                                         ^
    task_system.cxx.obj                                                        ^
    /OUT:"async-task-library.lib"


cl /nologo                                                                     ^
   /std:c++latest                                                              ^
   /experimental:module                                                        ^
   /EHsc                                                                       ^
   /GR                                                                         ^
   /MDd                                                                        ^
   /W4                                                                         ^
   /Od /Ob0                                                                    ^
   /module:interface                                                           ^
   /c ..\physics_simulation\itrf\physics_simulation.ixx

cl /nologo                                                                     ^
   /std:c++latest                                                              ^
   /experimental:module                                                        ^
   /EHsc                                                                       ^
   /GR                                                                         ^
   /MDd                                                                        ^
   /W4                                                                         ^
   /Od /Ob0                                                                    ^
   /module:reference phy_sim.ifc                                               ^
   /module:reference atl-task_queue.ifc                                        ^
   /module:reference atl-task_system.ifc                                       ^
   /module:reference atl.ifc                                                   ^
   /c ..\physics_simulation\impl\physics_simulation.cxx                        ^
   /Fo"physics_simulation.cxx.obj"

link /NOLOGO                                                                   ^
     async-task-library.lib                                                    ^
     physics_simulation.obj                                                    ^
     physics_simulation.cxx.obj                                                ^
     /OUT:"physics-simulation.exe"


cd ..
