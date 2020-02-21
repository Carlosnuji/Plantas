class Usuario {
    
    constructor(id, nombre, pass, email) {
        this._id = id;
        this._nombre = nombre;
        this._pass = pass;
        this._email = email;
    }
    
    get id()
    {
        return this._id;
    }
    
    get nombre()
    {
        return this._nombre;
    }
    
    get email()
    {
        return this._email;
    }
    
}

var usuario;

function cerrarMenu(){
	document.getElementById("miMenu").style.width = "0%";
	document.getElementById("listaMenu").style.display = "none";
}

function abrirMenu(){
	document.getElementById("miMenu").style.width = "100%";
	setTimeout(function() {
		document.getElementById("listaMenu").style.display = "block";
	}, 500);
}

function buscar(){
	document.getElementsByTagName("HEADER")[0].style.display = "none";
	document.getElementsByClassName("search")[0].style.display = "flex";
	document.getElementById("buscar").focus();
}

function cerrarBuscar(){
	document.getElementsByTagName("HEADER")[0].style.display = "grid";
	document.getElementsByClassName("search")[0].style.display = "none";
}

function crearArticles(item, section)
{
    
    var seccion = document.getElementsByClassName(section)[0];
    var articulo = document.createElement("ARTICLE");
            
    var figure = document.createElement("FIGURE");
    var imagen = document.createElement("IMG");
    imagen.setAttribute("src", "img/margarita.jpg");
    figure.appendChild(imagen);
            
    var lista = document.createElement("UL");
    var nombre = document.createElement("LI");
    nombre.innerHTML = item.nombre;
    lista.appendChild(nombre);
    var nombreCientifico = document.createElement("LI");
    nombreCientifico.innerHTML = item.nombreCientifico;
    lista.appendChild(nombreCientifico);
    var tiempo = document.createElement("LI");
    var icono = document.createElement("I");
    icono.setAttribute("class", "fas fa-history");
    tiempo.appendChild(icono);
    var tiempoTexto = document.createTextNode("Hace 3 horas");
    tiempo.appendChild(tiempoTexto);
    lista.appendChild(tiempo);
            
    articulo.appendChild(figure);
    articulo.appendChild(lista);
    seccion.appendChild(articulo);
    
    //Cargar ficha planta y cargar favoritos
    articulo.onclick = function(){
        
        // Cargar ficha
        // 1) Crear el JSON que se envia al servidor
        var idMensaje = dameId();
        var obj = {action:"cargarPlanta", id:idMensaje, nombre:item.nombre, nombreCientifico:item.nombreCientifico};
        socket.send(JSON.stringify(obj));
        
        // 2) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
        mensaje = new mensajeEspera(idMensaje);
    
        mensaje.funcionEjecutar = function(resultado)
        {
            
            resultado.forEach(mostarBusqueda);
            
            function mostarBusqueda(item, index)
            {
                cargarFichaPlanta(item);
            }
            
        }
        mensajesEsperandoRespuesta.push(mensaje); 
        
        // Cargar favoritos
        // 1) Crear el JSON que se envia al servidor
        var idMensaje = dameId();
        var idUsuario = usuario.id;
        var obj = {action:"cargarFavorito", id:idMensaje, nombre:item.nombre, nombreCientifico:item.nombreCientifico, idUsuario:idUsuario};
        socket.send(JSON.stringify(obj));
        
        // 2) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
        mensaje = new mensajeEspera(idMensaje);
        mensaje.funcionEjecutar = function(resultado)
        {
            
            resultado.forEach(mostarBusqueda);
            
            function mostarBusqueda(item, index)
            {
                var id = item.idUsuario;
                
                if(id == 0) document.getElementById("like").style.color = "#ffffff";
                else document.getElementById("like").style.color = "#374e19";
            }
            
        }
        mensajesEsperandoRespuesta.push(mensaje); 
        
        };
    
}

function vaciarSection()
{
    
    var seccion = document.getElementsByClassName("busquedas")[0];
    
    seccion.innerHTML = '';
    
}

function register()
{   
    document.getElementsByClassName("login")[0].style.display = "none"; 
    document.getElementsByClassName("register")[0].style.display = "block"; 
}

function cargarFichaPlanta(item)
{
      document.getElementsByClassName("busquedas")[0].style.display = "none";
      document.getElementsByClassName("listaFavoritos")[0].style.display = "none"; 
      document.getElementsByClassName("data")[0].style.display = "block";
      document.getElementById("like").style.display = "inline";
      
      var nombre = document.getElementById("nombrePlanta");
      var nombreCientifico = document.getElementById("nombreCientifico");
      var descripcion = document.getElementById("descPlanta");
      
      nombre.textContent = item.nombre;
      nombreCientifico.textContent = item.nombreCientifico;
      descripcion.textContent = item.descripcion;
}

/*******************************   WEBSOCKETS   *******************************/

//Conexión WebSocket con servidor
let socket = new WebSocket("wss://localhost:9990");

socket.onopen = function(event)
{
    
    /// 1) Pedir las últimas búsquedas
    console.log("Conexión con servidor, pedir últimas búsquedas");
    
    /// 2) Crear un id y el JSON que se envía al servidor
    var idMensaje = dameId();
    var pedirUltmasBusquedas = {action:"ultimasBusquedas", id:idMensaje};
    socket.send(JSON.stringify(pedirUltmasBusquedas));
    
    /// 3) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
    mensaje = new mensajeEspera(idMensaje);
    mensaje.funcionEjecutar = function(resultado)
    {
        resultado.forEach(mostrarUltimasBusquedas);
    
        function mostrarUltimasBusquedas(item, index)
        {
            console.log(item);
            
            crearArticles(item, "busquedas");
            
        }
    }
    mensajesEsperandoRespuesta.push(mensaje);
    
    /// Comprobar si hay token y enviar JSON
    var urlString = window.location.href;
    var url = new URL(urlString);
    var token = url.searchParams.get("token");
    
    
    if(token!=null)
    {
        
        var idMensaje = dameId();
        var obj = {action:"checkToken", id:idMensaje, token:token};
        socket.send(JSON.stringify(obj));
        
        mensaje = new mensajeEspera(idMensaje);
    
        mensaje.funcionEjecutar = function(resultado)
        {
            
            if(resultado[0].tokenCorrect == true)
            {
                document.getElementById("verificado").style.display = "block";
            }
            
        }
        mensajesEsperandoRespuesta.push(mensaje); 
            
    }
    
};

socket.onclose = function(event)
{
    console.log("Conexión cerrada")
};

socket.onerror = function(event)
{
    console.log("Error");
};

socket.onmessage = function(event)
{
    
    console.log(event.data);
    
    /// 1) Parsear el JSON
    var mensaje = JSON.parse(event.data);
    
    /// 2) Recorrer los mensajes en espera y si existe ejecutamos la funcion correspondiente
    if(mensaje != null)
    {
        
        mensajesEsperandoRespuesta.forEach(mostrarMensajes);
    
        function mostrarMensajes(item, index)
        {
            
            if(mensaje.id == item.id)
            {
                item.funcionEjecutar(mensaje.resultado); 
            }
            
        }
        
    }
    
    
};

//Busqueda
function buscarNombre()
{
    
    /// 1) Cogemos la búsqueda introducida por el usuario
    var textoBusqueda = document.getElementById("buscar").value;
    console.log("Texto a buscar: " + textoBusqueda);
    
    /// 2) Crear el JSON que se envia al servidor
    var idMensaje = dameId();
    var obj = {action:"buscar", id:idMensaje, busqueda:textoBusqueda};
    socket.send(JSON.stringify(obj));
    
    /// 3) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
    mensaje = new mensajeEspera(idMensaje);
    
    
    mensaje.funcionEjecutar = function(resultado)
    {
        
        vaciarSection();
        
        resultado.forEach(mostarBusqueda);
        
        function mostarBusqueda(item, index)
        {
            console.log(item);
            crearArticles(item, "busquedas");
        }
        
    }
    mensajesEsperandoRespuesta.push(mensaje); 
    
};

//Crear usuario
function crearUsuario()
{
    
    
    // 1) Coger los datos del registro
    var nombre = document.getElementById("nombre").value;
    var pass = document.getElementById("password").value;
    var email = document.getElementById("email2").value;
    
    // 2) Crear JSON que se envia al servidor
    var idMensaje = dameId();
    var obj = {action:"crearUsuario", id:idMensaje, nombre:nombre, pass:pass, email:email};
    socket.send(JSON.stringify(obj));
    
    // 3) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
    mensaje = new mensajeEspera(idMensaje);
    
    mensaje.funcionEjecutar = function(resultado)
    {
        
        resultado.forEach(usuarioNuevo);
        
        function usuarioNuevo(item, index)
        {
            usuario = new Usuario(item.id, item.nombre, item.pass, item.email);
            
            if(usuario.id == 0)
            {
                document.getElementById("errorSignIn").style.display = "flex";
            }
            else
            {
                document.getElementsByClassName("register")[0].style.display = "none";
                document.getElementsByClassName("busquedas")[0].style.display = "block";
                document.getElementById("menuUser").style.display = "block";
            }
        }
        
    }
    
    mensajesEsperandoRespuesta.push(mensaje);
    
}

//Cargar usuario
function cargarUsuario(idUsuario)
{
    
    // 1) Crear JSON que se envia al servidor
    var email = document.getElementById("email").value;
    var password = document.getElementById("pass").value;
    var idMensaje = dameId();
    var obj = {action:"cargarUsuario", id:idMensaje, email:email, pass:password};
    socket.send(JSON.stringify(obj));
    
    /// 2) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
    mensaje = new mensajeEspera(idMensaje);
    
    mensaje.funcionEjecutar = function(resultado)
    {
        
        resultado.forEach(usuarios);
        
        function usuarios(item, index)
        {
            usuario = new Usuario(item.id, item.nombre, item.pass, item.email);
            
            if(usuario.id == 0 || item.status==0)
            {
                document.getElementById("errorLogin").style.display = "flex";
            }
            else
            {
                document.getElementsByClassName("login")[0].style.display = "none";
                document.getElementsByClassName("busquedas")[0].style.display = "block";
                document.getElementById("menuUser").style.display = "block";
            }
        }
        
    }
    mensajesEsperandoRespuesta.push(mensaje); 
    
}

//Enviar queja
function enviarQueja()
{
    
    /// 1) Crear JSON que se envia al servidor
    var queja = document.getElementById("queja").value;
    var idUsuario = usuario.id;
    var idMensaje = dameId();
    var obj = {action:"queja", id:idMensaje, idUsuario:idUsuario, queja:queja};
    socket.send(JSON.stringify(obj));
    
    /// 2) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
    mensaje = new mensajeEspera(idMensaje);
    
    mensaje.funcionEjecutar = function(resultado)
    {
        
        document.getElementById("quejaExito").style.display = "block";
        
    }
    mensajesEsperandoRespuesta.push(mensaje); 
    
}

//Chequear like
function checkLike()
{
    
    /// 1) Crear JSON que se envia al servidor
    var idMensaje = dameId();
    var idUsuario = usuario.id;
    var nombrePlanta = document.getElementById("nombrePlanta").innerHTML;
    var nombreCientifico = document.getElementById("nombreCientifico").innerHTML;
    var obj = {action:"checkLike", id:idMensaje, idUsuario:idUsuario, nombrePlanta:nombrePlanta, nombreCientifico:nombreCientifico};
    socket.send(JSON.stringify(obj));
    
    /// 2) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
    mensaje = new mensajeEspera(idMensaje);
    
    mensaje.funcionEjecutar = function(resultado)
    {
        
        if(resultado[0].check == true) document.getElementById("like").style.color = "#ffffff";
        else document.getElementById("like").style.color = "#374e19";
        
    }
    mensajesEsperandoRespuesta.push(mensaje); 
    
}

//Cargar lista favoritos
function cargarListaFav()
{
    
    /// 1) Crear JSON que se envia al servidor
    var idMensaje = dameId();
    var idUsuario = usuario.id;
    var obj = {action:"listaFavoritos", id:idMensaje, idUsuario:idUsuario};
    socket.send(JSON.stringify(obj));
    
    /// 2) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
    mensaje = new mensajeEspera(idMensaje);
    mensaje.funcionEjecutar = function(resultado)
    {
        resultado.forEach(mostrarUltimasBusquedas);
    
        function mostrarUltimasBusquedas(item, index)
        {
            
            crearArticles(item, "listaFavoritos");
            
        }
    }
    mensajesEsperandoRespuesta.push(mensaje);
    
}

//Cargar perfil
function perfil()
{
    
    /// 1) Crear JSON que se envia al servidor
    var idMensaje = dameId();
    var idUsuario = usuario.id;
    var obj = {action:"perfil", id:idMensaje, idUsuario:idUsuario};
    socket.send(JSON.stringify(obj));
    
    /// 2) Crear el mensaje de respuesta que debe esperar el cliente y añadirlo a la lista de mensajes en espera
    mensaje = new mensajeEspera(idMensaje);
    mensaje.funcionEjecutar = function(resultado)
    {
        resultado.forEach(mostrarUltimasBusquedas);
    
        function mostrarUltimasBusquedas(item, index)
        {
            
            document.getElementById("nombreActual").value = usuario.nombre;
            document.getElementById("emailActual").value = usuario.email;
            
        }
    }
    mensajesEsperandoRespuesta.push(mensaje);
    
}

// Modificar perfil
function modificarPerfil()
{
    
    /// 1) Crear JSON que se envia al servidor
    var idMensaje = dameId();
    var idUsuario = usuario.id;
    var nombre = document.getElementById("nombreActual").value;
    var email = document.getElementById("emailActual").value;
    var obj = {action:"modificarUser", id:idMensaje, idUsuario:idUsuario, nombre:nombre, email:email};
    socket.send(JSON.stringify(obj));
    
}

//Mensajes JSON
function mensajeEspera(id)
{
    this.id = id;
}

var mensajesEsperandoRespuesta = [];

var g_ultimoId = 0;

function dameId()
{
    g_ultimoId++;
    return g_ultimoId;
}















