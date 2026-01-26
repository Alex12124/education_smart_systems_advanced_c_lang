cmake_minimum_required(VERSION 3.28)

project(MyCProject LANGUAGES C)


set(CMAKE_C_STANDARD_REQUIRED ON)
set(CURSES_NEED_NCURSES ON)
set(NCURSES_STATIC ON)
find_package(Curses)

add_executable(snake 
    main.c
    point_vector.c
    point_vector.h
    snake.c
    snake.h
    point.h

)
target_link_libraries(snake PRIVATE ${CURSES_LIBRARIES})
target_include_directories(snake PRIVATE ${CURSES_INCLUDE_DIRS})
