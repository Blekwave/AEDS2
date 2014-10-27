include_directories(${TP2_SOURCE_DIR}/src)

add_library(usuario Usuario.c)
add_library(filme Filme.c)
add_library(ldenc Ldenc.c Ndenc.c)
add_library(hashtable_abb HashTable_ABB.c ABBusca_m.c ABNodo.c)

# add_executable(TP2 Main.c)

# target_link_libraries(TP2 arquivo sugestoes lista filme usuario)