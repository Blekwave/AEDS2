from flask import Flask
from flask_bootstrap import Bootstrap
from flask.ext.pymongo import PyMongo

mongo = PyMongo()
bootstrap = Bootstrap()
app = Flask(__name__)
bootstrap.init_app(app)

import webapp.views
