import webapp
from config import Config
from werkzeug.contrib.fixers import ProxyFix

# Inicializa o aplicativo com as configurações desejadas
app = webapp.create_app(Config)

# Configura o aplicativo para proxy reverso
app.wsgi_app = ProxyFix(app.wsgi_app)

# Condicional importante para não invocar o servidor de debugging
if __name__ == "__main__":
    app.run()
