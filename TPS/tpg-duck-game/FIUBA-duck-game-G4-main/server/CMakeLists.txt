file(GLOB_RECURSE SOURCES_SERVER "*.cpp")
file(GLOB_RECURSE SOURCES_HEDER_SERVER "*.h")

target_sources(taller_server
    PRIVATE
    # .cpp files
   ${SOURCES_SERVER}
   
    PUBLIC
    # .h files
    ${SOURCES_HEDER_SERVER}
    )
