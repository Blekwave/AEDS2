from flask.ext.wtf import Form
from wtforms.fields import HiddenField, FieldList


class SugestoesForm(Form):
    """Formulário responsável por transmitir os dados dos filmes visua-
    lizados pelo usuário.
    """
    assistidos = HiddenField()
