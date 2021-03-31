add_subdirectory(io)
add_subdirectory(net)
add_subdirectory(thread)

aux_source_directory(./io DIR_IO_SRCS)
aux_source_directory(./net DIR_NET_SRCS)
aux_source_directory(./thread DIR_THREAD_SRCS)

add_library(
    limtools
    ${DIR_IO_SRCS}
    ${DIR_NET_SRCS}
    ${DIR_THREAD_SRCS}
)