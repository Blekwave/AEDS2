include_directories(${TP2_SOURCE_DIR}/src)

add_library(usuario Usuario.c)
add_library(filme Filme.c)
add_library(lista Lista.c Nodo.c)
add_library(hashtable_abb HashTable_ABB.c ABBusca_m.c ABNodo.c)
add_library(arquivo Arquivo.c)
add_library(racional Racional.c)
add_library(sugestoes Sugestoes.c)
add_library(sugestoes_impressao Sugestoes_Impressao.c)
add_library(sugestoes_impressao_ids Sugestoes_Impressao_IDs.c)
add_library(bitstring BitString.c)

add_executable(TP2 Main.c)
add_executable(Populares Populares.c)
add_executable(Individual Individual.c)

target_link_libraries(TP2 arquivo sugestoes_impressao sugestoes hashtable_abb lista filme usuario racional bitstring m)
target_link_libraries(Populares arquivo sugestoes_impressao_ids sugestoes hashtable_abb lista filme usuario racional bitstring m)
target_link_libraries(Individual arquivo sugestoes_impressao_ids sugestoes hashtable_abb lista filme usuario racional bitstring m)
