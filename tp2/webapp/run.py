import webapp
from config import Config

app = webapp.create_app(Config)
app.run()
