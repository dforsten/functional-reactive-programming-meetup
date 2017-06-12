file(GLOB airline1_SRC
    "airline1/*.h"
    "airline1/*.cpp"
)

add_executable(airline1 ${airline1_SRC})

include_directories(sodium boost)

add_definitions(-DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}")

source_group(swidgets FILES ${swidgets_SRC})

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
target_link_libraries(airline1 sodium Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)

add_custom_command(
    TARGET airline1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:airline1>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:airline1>	
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:airline1>	
)
