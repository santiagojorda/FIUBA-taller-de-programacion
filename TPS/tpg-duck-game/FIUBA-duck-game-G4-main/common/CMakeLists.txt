file(GLOB_RECURSE SOURCES_COMMON "*.cpp")
file(GLOB_RECURSE  "*.h")

target_sources(taller_common
    PRIVATE
    # .cpp files
    ${SOURCES_COMMON}

    PUBLIC
    # .h files
    ${SOURCES_HEDER_COMMON}
    )
