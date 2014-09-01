include_directories(${TP0_SOURCE_DIR}/src)
link_directories(${TP0_BINARY_DIR}/src)

add_library(usuario Usuario.c)
add_library(filme Filme.c)
add_library(lista Lista.c Nodo.c)
add_library(sugestoes Sugestoes.c)
add_library(arquivo Arquivo.c)

add_executable(TP0 Main.c)

target_link_libraries(TP0 arquivo sugestoes lista filme usuario)