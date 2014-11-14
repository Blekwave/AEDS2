import subprocess
import os
from webapp import app


def mais_populares(num):
    """Retorna uma lista com os movie ids e imdb ids dos filmes mais
    populares. Faz isso através do módulo 'subprocess', chamando o pro-
    grama correspondente

    Argumentos:
    num -- Número de filmes a serem retornados
    """
    end_processo = os.path.join(
        app.config['BASEDIR'], app.config['G_POPULARES'])
    processo = subprocess.Popen([end_processo, app.config['G_CONFIG'], str(
        app.config['NUM_ASSISTIDOS'])], stdout=subprocess.PIPE)
    lista_filmes = []
    while True:
        linha = processo.stdout.readline()
        if not linha:  # eof
            break
        else:
            split = linha.split()
            lista_filmes.append((int(split[0]), int(split[1])))
    return lista_filmes


def sugestoes(assistidos, num):
    """Retorna uma lista com os movie_ids e imdb_ids dos filmes sugeri-
    dos para um usuário que assistiu determinados filmes.

    Argumentos:
    assistidos -- Lista de tuplas contendo o movie_id e o imdb_id de
                  cada filme assistido pelo usuário.
    num -- Número de filmes a serem retornados
    """
    end_processo = os.path.join(
        app.config['BASEDIR'], app.config['G_INDIVIDUAL'])
    str_assistidos = " ".join([str(x) for x in assistidos])
    p_params = [end_processo, app.config['G_CONFIG'],
                str(app.config['NUM_SUGESTOES']), str_assistidos]
    processo = subprocess.Popen(p_params, stdout=subprocess.PIPE)
    lista_filmes = []
    while True:
        linha = processo.stdout.readline()
        if not linha:  # eof
            break
        else:
            split = linha.split()
            lista_filmes.append((int(split[0]), int(split[1])))
    return lista_filmes
