include_directories(${LDENC_SOURCE_DIR}/src)

add_library(ldenc Ldenc.c Ndenc.c)
add_library(valloc valloc.c)

add_executable(TP1 main.c)
add_executable(Teste1 teste1.c)

target_link_libraries(TP1 valloc ldenc)
target_link_libraries(Teste1 valloc ldenc)
