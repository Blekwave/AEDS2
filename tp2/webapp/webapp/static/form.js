/**
 * Scripts do formulário de sugestões (/form/)
 */

// Carrega as tooltips dos elementos que as possuem
$(window).bind("load", function() {
   $('[data-toggle="tooltip"]').tooltip();
});

var thumbnails = $("a.thumbnail.filme");
var formulario = $("form[name=\"sugestoes\"]");
var assistidos = formulario.find("input[type=\"hidden\"]")
var botao_submit = formulario.find("button");

// Ao clicar uma miniatura de filme, ele é selecionado
thumbnails.bind("click", function (){
    $(this).toggleClass("selecionado");
    botao_submit.prop("disabled", false); // habilita o botão
});

// Ao clicar no botão de enviar, adiciona uma input oculta contendo a lista dos
// ids dos filmes selecionados.
botao_submit.bind("click", function(){
    var ids = [];
    for (i = 0; i < thumbnails.length; i++){
        if ($(thumbnails[i]).hasClass("selecionado")){
            ids.push($(thumbnails[i]).find("span.movie_id").html());
        }
    }
    var string = JSON.stringify(ids);
    assistidos.val(string);
});
