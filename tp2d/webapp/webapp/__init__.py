from flask import Flask
from flask_bootstrap import Bootstrap

bootstrap = Bootstrap()

app = Flask(__name__)

# Por alguma razão, não consigo definir as configurações no run.py antes de in-
# vocar o MongoDB. Dessa forma, defini essas diretrizes (temporariamente) aqui.
app.config['MONGO_HOST'] = "localhost"
app.config['MONGO_PORT'] = 27017
app.config['MONGO_DBNAME'] = "tp2d"

bootstrap.init_app(app)

import webapp.views
