from flask import Flask
from flask_bootstrap import Bootstrap
import os

def create_app(Config):
    app = Flask(__name__)
    app.config.from_object(Config)

    Bootstrap(app)

    from webapp.db import mongo
    mongo.init_app(app)

    from webapp.views import views
    app.register_blueprint(views)

    if not os.path.exists(app.config['POSTERS_END']):
        os.makedirs(app.config['POSTERS_END'])

    return app
