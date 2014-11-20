from flask import Flask
from flask_bootstrap import Bootstrap

def create_app(Config):
    app = Flask(__name__)
    app.config.from_object(Config)

    Bootstrap(app)

    from webapp.db import mongo
    mongo.init_app(app)

    from webapp.views import views
    app.register_blueprint(views)

    return app
