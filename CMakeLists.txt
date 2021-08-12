cmake_minimum_required(VERSION 3.17)
project(HTM)

find_package(PythonLibs 3)
find_package(Boost COMPONENTS python REQUIRED)

include_directories(/usr/include/python3.9)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/module)
set(CMAKE_CXX_STANDARD 20)

PYTHON_ADD_MODULE(HTM
        src/Region.h
        src/Region.cpp
        src/Cell.h
        src/Cell.cpp
        src/Segment.h
        src/Segment.cpp
        py_module/py_module.cpp
)
target_link_libraries(HTM Boost::python)

#add_executable(HTM
#        main.cpp
#        src/Region.h
#        src/Region.cpp
#        src/Cell.h
#        src/Cell.cpp
#        src/Segment.h
#        src/Segment.cpp)