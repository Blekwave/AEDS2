from flask import render_template, request, redirect, current_app, Blueprint
from webapp import forms
from webapp.sugestoes import engine, parser
import json

views = Blueprint('views', __name__)

@views.route('/')
def index():
    """Página principal do site."""
    return render_template("home.html")


@views.route('/form')
def form():
    """Formulário de seleção de filmes assistidos."""
    formulario = forms.SugestoesForm()
    dados = parser.obter_lista_filmes(
        engine.mais_populares(current_app.config['NUM_ASSISTIDOS']))

    return render_template("form.html", dados=dados, form=formulario)


@views.route('/sugestoes', methods=['POST', 'GET'])
def resultados():
    """Página de resultados, acessível apenas pelo formulário form().
    """
    formulario = forms.SugestoesForm()

    if formulario.validate_on_submit():
        # Obtém movie_ids inteiros do JSON fornecido pelo campo hidden
        movie_ids = [int(x) for x in json.loads(formulario.assistidos.data)]
        imdb_ids = engine.sugestoes(movie_ids, current_app.config['NUM_SUGESTOES'])
        dados = parser.obter_lista_filmes(imdb_ids)
        return render_template("sugestoes.html", dados=dados)

    return redirect('/form')
