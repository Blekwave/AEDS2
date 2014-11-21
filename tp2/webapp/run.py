import webapp
from config import Config

app = webapp.create_app(Config)
if __name__ == "__main__":
    app.run()
