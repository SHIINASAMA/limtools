aux_source_directory(./io DIR_IO_SRCS)
aux_source_directory(./net DIR_NET_SRCS)
aux_source_directory(./thread DIR_THREAD_SRCS)
aux_source_directory(./file/config DIR_CONFIG_SRCS)

add_library(
    limtools
    ${DIR_IO_SRCS}
    ${DIR_NET_SRCS}
    ${DIR_THREAD_SRCS}
    ${DIR_CONFIG_SRCS}
)