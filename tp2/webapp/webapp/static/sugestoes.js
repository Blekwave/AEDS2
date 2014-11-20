/**
 * Scripts da página de resultados (/sugestoes/)
 */

var colorirAvaliacoesIMDB = function(elemento){
    var jQueryObject = $(elemento);
    var valor = parseFloat(jQueryObject.text());
    if (valor >= 8.8)
        jQueryObject.addClass("btn-info");
    else if (valor >= 7.5)
        jQueryObject.addClass("btn-success");
    else if (valor >= 6.2)
        jQueryObject.addClass("btn-warning");
    else
        jQueryObject.addClass("btn-danger");
}

var colorirAvaliacoesMetacritic = function(elemento){
    var jQueryObject = $(elemento);
    var valor = parseInt(jQueryObject.text());
    if (valor >= 85)
        jQueryObject.addClass("btn-info");
    else if (valor >= 72)
        jQueryObject.addClass("btn-success");
    else if (valor >= 58)
        jQueryObject.addClass("btn-warning");
    else
        jQueryObject.addClass("btn-danger");
}

// Carrega as popovers dos elementos que as possuem
$(window).bind("load", function() {
    $('[data-toggle="popover"]').popover();
    $('[data-toggle="tooltip"]').tooltip();

    var ratings = $('.imdb_rating');
    for (i = 0; i < ratings.length; i++)
        colorirAvaliacoesIMDB(ratings[i]);

    var ratingsMetacritic = $('.metacritic_rating');
    for (i = 0; i < ratingsMetacritic.length; i++)
        colorirAvaliacoesMetacritic(ratingsMetacritic[i]);
});