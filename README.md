*******************************************
*Proyecto creador por Carlos Núñez Jiménez*
*******************************************

# Proyecto Plantas

El proyecto consiste en un programa cliente y uno servidor que se comunican entre
ellos mediante websocket y mensajes JSON.

Se almacenan datos de plantas y usuarios en una base de datos y se pueden crear
usuario y buscar plantas y agragarlas a favoritos.

## Pre-requisitos

Para el proyecto se necesita la libreria IXWebSocket para poder crear el servidor Websocket.
Descarga el [IXWebSocket](https://github.com/machinezone/IXWebSocket).

También se necesita una libreria para poder manejar JSON.
Descarga [nlohmann/json](https://github.com/nlohmann/json).

## Ejecutando las pruebas/tests

Para ejecutar las **pruebas** automatizadas del proyecto se debe entrar en la carpeta tests
y ejecutar el main.cpp

Los **test** analizan que se hagan bien los inserts, selects, delete... en la base de datos y
que los métodos de las clases funcionen correctamente y devuelvan el valor esperado.

## Construido con

**Servidor**
- C++ El lenguaje de programación elegido para el servidor.
- Qt El framework de c++ usado en el proyecto.

**Cliente**
- HTML Lenguaje de marca para crear la página del cliente.
- CSS Para darle diseño a la página.
- JS Para interactuar con el servidor y enviar peticiones.

## Gestión de errores

Usando la herramienta cppcheck y el compilador durante la creación del proyecto he ido detectando errores que he ido
solventando, algunos eran más sencillos y han sido rápidamente solucionados y otros han llevado más trabajo.
Uno de los errores que tuve fue al leer el archivo de configuración de la base de datos el cual lo leia mal y no
se conectaba a la misma, lo solucione creando un método que se encargará de leer de manera apropiada el archivo de configuración.
Con ayuda de los test he podido detectar algunos errores en las selects o inserts en la base de datos.

## Contribuyendo

Al contribuir a este repositorio, primero discuta el cambio que desea realizar a través de un problema, 
correo electrónico o cualquier otro método con los propietarios de este repositorio antes de realizar un cambio.

Tenga en cuenta que tenemos un código de conducta, sígalo en todas sus interacciones con el proyecto.

###### Código de conducta

En aras de fomentar un ambiente abierto y acogedor, nosotros, como colaboradores y mantenedores, 
nos comprometemos a hacer de la participación en nuestro proyecto y en nuestra comunidad una experiencia libre de acoso para todos, 
independientemente de su edad, tamaño corporal, discapacidad, origen étnico, identidad y expresión de género, nivel de experiencia, 
nacionalidad, apariencia personal, raza, religión o identidad y orientación sexual.

**Nuestras responsabilidades**

Los encargados del mantenimiento del proyecto son responsables de aclarar los estándares de comportamiento aceptable 
y se espera que tomen medidas correctivas apropiadas y justas en respuesta a cualquier caso de comportamiento inaceptable.

Los encargados del mantenimiento del proyecto tienen el derecho y la responsabilidad de eliminar, editar o rechazar comentarios, 
confirmaciones, códigos, ediciones de wiki, problemas y otras contribuciones que no estén alineadas con este Código de conducta, 
o de prohibir temporal o permanentemente a cualquier contribuyente por otros comportamientos que consideran inapropiados, amenazantes, ofensivos o dañinos.

## Autores

- Carlos Núñez (Desarrollo)
- Javier Miró (Documentación y ayuda)

## Licencia

**The MIT License (MIT)**

**Copyright (c) 2020-present Carlos Núñez**

Por la presente, se otorga permiso, de forma gratuita, a cualquier persona que obtenga una copia de este software y los archivos de documentación asociados (el "Software"),
para negociar el Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, modificación, fusión , publicar, distribuir, sublicenciar y / o vender copias del Software,
y permitir que las personas a quienes se les proporcione el Software lo hagan.
