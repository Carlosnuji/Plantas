/*******************************   JQUERY   *******************************/
$(document).ready(function(){

    $("#atras").click(function(){
        
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
            }
        }
        
    });

}); 
 
