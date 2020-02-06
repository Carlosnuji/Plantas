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
        
    })

}); 



 
