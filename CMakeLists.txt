cmake_minimum_required(VERSION 3.5)

project(boost_template_app) # <-- change this for your name

set(BOOST_ROOT external/boost)

# Uncomment component that you want to use
set(BOOST_COMPONENTS
    #atomic
    #chrono
    #container
    #context
    #contract
    #coroutine
    #date_time
    #exception
    #fiber
    #filesystem
    #graph
    #graph_parallel
    #iostreams
    #json
    #locale
    #log
    #log_setup
    #math
    #mpi
    #nowide
    #program_options
    #python
    #random
    #regex
    #serialization
    spirit
    #stacktrace
    #system
    #test
    #thread
    #timer
    #type_erasure
    #url
    #wave
)

foreach(component IN LISTS BOOST_COMPONENTS)
    find_package(Boost QUIET COMPONENTS ${component})
    if(Boost_${component}_FOUND)
        list(APPEND FOUND_BOOST_COMPONENTS ${component})
    endif()
endforeach()

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
foreach(component IN LISTS FOUND_BOOST_COMPONENTS)
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::${component})
endforeach()

