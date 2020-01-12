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

function crearArticles(item)
{
    
    var seccion = document.getElementsByClassName("busquedas")[0];
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
    
}

function vaciarSection()
{
    
    var seccion = document.getElementsByClassName("busquedas")[0];
    var hijos = seccion.childNodes;
        
    hijos.forEach(eliminarHijos);
    function eliminarHijos(item, index)
    {
        item.remove();
    }
    
}

/*******************************   WEBSOCKETS   *******************************/

//Conexión WebSocket con servidor
let socket = new WebSocket("ws://127.0.0.1:9990");

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
            
            crearArticles(item);
            
        }
    }
    mensajesEsperandoRespuesta.push(mensaje);
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
    mensajesEsperandoRespuesta.forEach(mostrarMensajes);
    
    function mostrarMensajes(item, index)
    {
        
        if(mensaje.id == item.id)
        {
           item.funcionEjecutar(mensaje.resultado); 
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
            crearArticles(item);
        }
        
    }
    mensajesEsperandoRespuesta.push(mensaje); 
    
};

//Crear Usuario
function crearUsuario(nombre, pass, email)
{
    
    // 1) Crear JSON que se envia al servidor
    var idMensaje = dameId();
    var obj = {action:"crearUsuario", id:idMensaje, nombre:nombre, pass:pass, email:email};
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


















