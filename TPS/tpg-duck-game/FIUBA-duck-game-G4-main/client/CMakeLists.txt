project(duck-game-2 VERSION 0.1 LANGUAGES CXX)
# Habilita AUTOMOC y AUTOUIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Configura el proyecto con Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE SOURCES_CLIENT "*.cpp")
file(GLOB_RECURSE SOURCES_HEDER_CLIENT "*.h")
file(GLOB_RECURSE SOURCES_UI_CLIENT "*.ui")


# Incluye el archivo de recursos
set(qrc_files lobby_screens/resources.qrc)

target_sources(taller_client
    PRIVATE
    # .cpp files
   ${SOURCES_CLIENT}
   
    PUBLIC
    # .h files
    ${SOURCES_HEDER_CLIENT}
    # .ui files
    ${SOURCES_UI_CLIENT}
    ${qrc_files}
    )

