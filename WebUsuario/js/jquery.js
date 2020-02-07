/*******************************   JQUERY   *******************************/
$(document).ready(function(){

    // Botón atras
    $("#atras").click(function()
    {
        
        if($(".register").is(":visible"))
        {
            $(".register").fadeOut();
            $(".login").delay(800).fadeIn();
        }
        else
        {
            if($(".data").is(":visible"))
            {
                $(".data").fadeOut();
                $(".busquedas").delay(800).fadeIn();
                $("#like").hide();
            }
            
            if($(".quejas").is(":visible"))
            {
                $(".quejas").fadeOut();
                $(".busquedas").delay(800).fadeIn();
            }
            
            if($(".listaFavoritos").is(":visible"))
            {
                $(".listaFavoritos").fadeOut();
                $(".busquedas").delay(800).fadeIn();
            }
        }
        
    });
    
    // Botón quejas
    $("#quejas").click(function()
    {
        
        if($(".busquedas").is(":visible"))
        {
            $(".busquedas").fadeOut();
            $(".quejas").delay(800).fadeIn();
        }
        
        if($(".data").is(":visible"))
        {
            $(".data").fadeOut();
            $(".quejas").delay(800).fadeIn();
        }
        
        if($(".listaFavoritos").is(":visible"))
        {
            $(".listaFavoritos").fadeOut();
            $(".quejas").delay(800).fadeIn();
        }
        
    })
    
    // Botón listaFavoritos
    $("#favoritos").click(function()
    {
     
        if($(".busquedas").is(":visible"))
        {
            $(".busquedas").fadeOut();
            $(".listaFavoritos").delay(800).fadeIn();
        }
        
        if($(".data").is(":visible"))
        {
            $(".data").fadeOut();
            $(".listaFavoritos").delay(800).fadeIn();
            $("#like").hide();
        }
        
    })

}); 



 





















