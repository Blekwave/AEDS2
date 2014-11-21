import os
basedir = os.path.abspath(os.path.dirname(__file__))

class Config(object):
    """Configurações a serem fornecidas ao objeto principal do Flask."""
    PROJECT_NAME = "tp2d"
    DEBUG = True
    BASEDIR = basedir
    IMDB_API_URL = "http://www.omdbapi.com/?"
    GERADORES_END = "geradores/"
    G_POPULARES = os.path.join(GERADORES_END, "Populares.exe")
    G_INDIVIDUAL = os.path.join(GERADORES_END, "Individual.exe")
    G_CONFIG = os.path.join(GERADORES_END, "config.ini")
    WTF_CSRF_ENABLED = False
    NUM_ASSISTIDOS = 20
    NUM_SUGESTOES = 6
    MONGO_HOST = "localhost"
    MONGO_PORT = 27017
    MONGO_DBNAME = "tp2d"
    APPLICATION_ROOT = "/"
