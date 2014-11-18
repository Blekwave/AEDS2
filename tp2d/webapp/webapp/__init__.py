from flask import Flask
from flask_bootstrap import Bootstrap
from flask.ext.pymongo import PyMongo

mongo = PyMongo()
app = Flask(__name__)
Bootstrap(app)

import webapp.views
