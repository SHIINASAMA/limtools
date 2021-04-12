# IO相关
aux_source_directory(./io DIR_IO_SRCS)

# 网络相关
aux_source_directory(./net DIR_NET_SRCS)

# http协议相关
aux_source_directory(./net/http DIR_HTTP_SRCS)

# 线程相关
aux_source_directory(./thread DIR_THREAD_SRCS)

# Config文件相关
aux_source_directory(./file/config DIR_CONFIG_SRCS)

# Json文件相关
aux_source_directory(./file/json DIR_JSON_SRCS)

add_library(
    limtools
    ${DIR_IO_SRCS}
    ${DIR_NET_SRCS}
    ${DIR_HTTP_SRCS}
    ${DIR_THREAD_SRCS}
    ${DIR_CONFIG_SRCS}
    ${DIR_JSON_SRCS}
)