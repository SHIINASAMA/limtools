add_subdirectory(net)

aux_source_directory(. DIR_IO_SRCS)
add_library(io ${DIR_IO_SRCS})