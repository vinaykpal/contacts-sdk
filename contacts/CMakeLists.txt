cmake_minimum_required(VERSION 3.4.1)

file(GLOB_RECURSE SOURCE_FILES
    "src/main/cpp/*.h"
    "src/main/cpp/*.cpp"
        "src/main/cpp/*.hpp"
)
add_library(${CONTACTS_LIBRARY} SHARED ${SOURCE_FILES})
find_library( log-lib log )
target_link_libraries(${CONTACTS_LIBRARY} ${log-lib})
