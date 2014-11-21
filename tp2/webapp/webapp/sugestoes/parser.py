import requests
import os
from webapp.db import mongo
from flask import current_app, url_for

IMDBID_NUMDIGITOS = 7  # Usado para preencher zeros à esquerda

def obter_poster(imdb_id, poster_url):
    poster_filename = 'posters/%s.jpg' % (imdb_id)
    local_url = url_for('static', filename=poster_filename)
    new_file_location = os.path.join(current_app.config['BASEDIR'],
        current_app.config['POSTERS_END'] + '\\%s.jpg' % (imdb_id))

    if not os.path.exists(new_file_location):
        query = requests.get(poster_url)
        if query.status_code == 200:
            with open(new_file_location, 'wb') as f:
                for chunk in query.iter_content(1024):
                    if not chunk:
                        break
                    f.write(chunk)
                f.close()
        else:
            return False

    return local_url

def obter_dados(imdb_id):
    """Obtém os dados de um filme da API do IMDB ou do cache (MongoDB).
    Adiciona dados ao cache caso ainda não estejam presentes nele. Re-
    torna um dicionário com os campos do pedido.

    Argumentos:
    imdb_id -- String correspondente ao imdbID já formatado.
               Formato: tt####### (# = [0-9])
    """
    imdb_data = mongo.db.imdb_data
    query = imdb_data.find_one({"imdbID": imdb_id})
    if query is None:
        url = current_app.config['IMDB_API_URL'] + "i=" + imdb_id
        query = requests.get(url).json()
        imdb_data.insert(query)
    return query


def obter_lista_filmes(lista_filmes):
    """Obtém dados de uma lista de filmes fornecida. Retorna uma lista
    de tuplas contendo o movie_id e os dados do filme.

    Argumentos:
    lista_filmes -- Lista de tuplas correspondentes a cada filme.
                    Formato: (movie_id, imdb_id)
                                         ^-(int, ainda não formatado)
    """
    lista_imdb_ids = [
        (x[0], "tt" + str(x[1]).zfill(IMDBID_NUMDIGITOS))
        for x in lista_filmes]
    dados = []
    for filme in lista_imdb_ids:
        filme_dados = obter_dados(filme[1])
        poster = obter_poster(filme[1], filme_dados['Poster'])
        dados.append((filme[0], obter_dados(filme[1]), poster))
    return dados
