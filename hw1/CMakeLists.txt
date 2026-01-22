cmake_minimum_required(VERSION 3.28)

project(MyCProject LANGUAGES C)


# set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(TASKS task0 task1 task2 task3 task4 task5 task6 task7 task8 task9 task10)
          
foreach(task IN LISTS TASKS)
    add_executable(${task} ${task}.c)
endforeach()
