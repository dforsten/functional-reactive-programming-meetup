file(GLOB accumulator_editable_SRC
    "sodium-qt/examples/accumulator_editable/*.h"
    "sodium-qt/examples/accumulator_editable/*.cpp"
)

file(GLOB swidgets_SRC
    "sodium-qt/swidgets/*.h"
    "sodium-qt/swidgets/*.cpp"
)

file(GLOB common_SRC
    "sodium-qt/examples/common/*.h"
    "sodium-qt/examples/common/*.cpp"
)

add_executable(accumulator_editable ${accumulator_editable_SRC} ${swidgets_SRC} ${common_SRC})

include_directories(sodium boost sodium-qt/swidgets sodium-qt/examples/common)

add_definitions(-DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}")

source_group(swidgets FILES ${swidgets_SRC})
source_group(common FILES ${common_SRC})

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
target_link_libraries(accumulator_editable sodium Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)

add_custom_command(
    TARGET accumulator_editable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:accumulator_editable>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:accumulator_editable>	
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:accumulator_editable>	
)
