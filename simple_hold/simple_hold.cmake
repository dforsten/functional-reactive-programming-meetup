file(GLOB simple_hold_SRC
    "simple_hold/*.h"
    "simple_hold/*.cpp"
)

file(GLOB swidgets_SRC
    "swidgets/*.h"
    "swidgets/*.cpp"
)

add_executable(simple_hold ${simple_hold_SRC} ${swidgets_SRC})

include_directories(sodium boost swidgets)

add_definitions(-DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}")

source_group(swidgets FILES ${swidgets_SRC})

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
target_link_libraries(simple_hold sodium Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)

add_custom_command(
    TARGET simple_hold POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:simple_hold>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:simple_hold>	
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:simple_hold>	
)
