from webapp import app
from config import Config

app.config.from_object(Config)
app.run()