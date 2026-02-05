cmake_minimum_required(VERSION 3.28)

project(MyCProject LANGUAGES C)


# set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(TASKS task0 task1 task2)
          
foreach(task IN LISTS TASKS)
    add_executable(${task} ${task}.c)
endforeach()
