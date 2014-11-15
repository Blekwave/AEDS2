from webapp import app, mongo
from config import Config

app.config.from_object(Config)
mongo.init_app(app)
app.run()
