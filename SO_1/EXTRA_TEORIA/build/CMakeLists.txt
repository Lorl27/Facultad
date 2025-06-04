cmake_minimum_required(VERSION 3.15...3.25) #Version.ç

project(lector
    VERSION
        1.0
    DESCRIPTION
        "Example"
    LANGUAGES
    C)


add_library(RWLock rwlock-r.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(RWLock PUBLIC Threads::Threads)

add_executable(LEct lect.c)
target_link_libraries(LEct PUBLIC RWLock)


# cmake ..
# cmake --build . 

# cmake --build target clean // para borrar los archivos ejecutables
