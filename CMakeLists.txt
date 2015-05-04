set ( SOURCES 
    "src/virtual_controller.cpp"
    "src/interface.cpp"
)

set (HEADERS
    "include/virtual_controller.h"
)

include_directories("include")

add_library ( virtual_controller MODULE ${SOURCES} ${HEADERS})
target_link_libraries(virtual_controller PRIVATE lms sense_link gamepad_lib)
