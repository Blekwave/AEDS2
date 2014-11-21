import subprocess
import os
from flask import current_app

def mais_populares(num):
    """Retorna uma lista com os movie ids e imdb ids dos filmes mais
    populares. Faz isso através do módulo 'subprocess', chamando o pro-
    grama correspondente

    Argumentos:
    num -- Número de filmes a serem retornados
    """
    end_processo = os.path.join(
        current_app.config['BASEDIR'], current_app.config['G_POPULARES'])
    # Invoca o subprocesso que calcula os filmes mais populares
    processo = subprocess.Popen([end_processo, current_app.config['G_CONFIG'], str(
        current_app.config['NUM_ASSISTIDOS'])], stdout=subprocess.PIPE)
    lista_filmes = []
    # Lê os filmes a partir do pipe da saída padrão até eof
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
        current_app.config['BASEDIR'], current_app.config['G_INDIVIDUAL'])
    # Os argumentos de subprocess são listas de strings, então é pre-
    # ciso converter a lista de assistidos.
    assistidos_str = [str(x) for x in assistidos]
    p_params = [end_processo, current_app.config['G_CONFIG'],
                str(current_app.config['NUM_SUGESTOES'])] + assistidos_str
    # Invoca o subprocesso que calcula os filmes sugeridos so usuário
    processo = subprocess.Popen(p_params, stdout=subprocess.PIPE)
    lista_filmes = []
    # Lê os filmes a partir do pipe da saída padrão até eof
    while True:
        linha = processo.stdout.readline()
        if not linha:  # eof
            break
        else:
            split = linha.split()
            lista_filmes.append((int(split[0]), int(split[1])))
    return lista_filmes
