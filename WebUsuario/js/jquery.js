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
            
            if($(".listaFavoritos").is(":visible"))
            {
                $(".listaFavoritos").fadeOut();
                $(".busquedas").delay(800).fadeIn();
            }
            
            if($(".profile").is(":visible"))
            {
                $(".profile").fadeOut();
                $(".busquedas").delay(800).fadeIn();
            }
            
            if($(".listaUsuarios").is(":visible"))
            {
                $(".listaUsuarios").fadeOut();
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
        
        if($(".profile").is(":visible"))
        {
            $(".profile").fadeOut();
            $(".quejas").delay(800).fadeIn();
        }
        
        if($(".listaFavoritos").is(":visible"))
        {
            $(".listaFavoritos").fadeOut();
            $(".quejas").delay(800).fadeIn();
        }
        
        if($(".listaUsuarios").is(":visible"))
        {
            $(".listaUsuarios").fadeOut();
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
        
        if($(".profile").is(":visible"))
        {
            $(".profile").fadeOut();
            $(".listaFavoritos").delay(800).fadeIn();
        }
        
        if($(".quejas").is(":visible"))
        {
            $(".quejas").fadeOut();
            $(".listaFavoritos").delay(800).fadeIn();
        }
        
        if($(".listaUsuarios").is(":visible"))
        {
            $(".listaUsuarios").fadeOut();
            $(".listaFavoritos").delay(800).fadeIn();
        }
        
    })
    
    // Botón perfil
    $("#perfil").click(function()
    {
     
        if($(".busquedas").is(":visible"))
        {
            $(".busquedas").fadeOut();
            $(".profile").delay(800).fadeIn();
        }
        
        if($(".data").is(":visible"))
        {
            $(".data").fadeOut();
            $(".profile").delay(800).fadeIn();
            $("#like").hide();
        }
        
        if($(".listaFavoritos").is(":visible"))
        {
            $(".listaFavoritos").fadeOut();
            $(".profile").delay(800).fadeIn();
        }
        
        if($(".quejas").is(":visible"))
        {
            $(".quejas").fadeOut();
            $(".profile").delay(800).fadeIn();
        }
        
        if($(".listaUsuarios").is(":visible"))
        {
            $(".listaUsuarios").fadeOut();
            $(".profile").delay(800).fadeIn();
        }
        
    })
    
    // Botón listaFavoritos
    $("#listaUsers").click(function()
    {
        
        if($(".busquedas").is(":visible"))
        {
            $(".busquedas").fadeOut();
            $(".listaUsuarios").delay(800).fadeIn();
        }
        
        if($(".data").is(":visible"))
        {
            $(".data").fadeOut();
            $(".listaUsuarios").delay(800).fadeIn();
            $("#like").hide();
        }
        
        if($(".listaFavoritos").is(":visible"))
        {
            $(".listaFavoritos").fadeOut();
            $(".listaUsuarios").delay(800).fadeIn();
        }
        
        if($(".quejas").is(":visible"))
        {
            $(".quejas").fadeOut();
            $(".listaUsuarios").delay(800).fadeIn();
        }
        
        if($(".profile").is(":visible"))
        {
            $(".profile").fadeOut();
            $(".listaUsuarios").delay(800).fadeIn();
        }
        
    })

}); 



 





















