<h1 align="left">Taller 4 - Comunicación Bidireccional con Pipe</h1>
<!-- Título del taller con alineación a la izquierda -->

<p align="left">Este programa permite la comunicación bidireccional entre un cliente y un servidor utilizando pipes. El cliente envía una cadena de caracteres, el servidor la recibe, invierte su orden y la reenvía al cliente, quien la muestra nuevamente.</p>
<!-- Breve descripción del funcionamiento del programa, explicando el flujo de comunicación entre cliente y servidor -->

<h2 align="left">Ejemplo de salida</h2>
<!-- Sección que muestra un ejemplo de cómo será la salida del programa -->

<p align="left"><strong>FIFOCLIENT:</strong> Envía mensajes indefinidamente, para terminar ingrese "end".</p>
<!-- Mensaje inicial del cliente indicando que se enviarán mensajes hasta que se introduzca "end" para finalizar -->

<p align="left"><strong>FIFOCLIENT:</strong> Ingrese cadena: Pepito</p>
<!-- El cliente solicita que el usuario ingrese una cadena -->

<p align="left"><strong>FIFOCLIENT:</strong> Cadena enviada: "Pepito", longitud: 6</p>
<!-- El cliente informa que ha enviado la cadena "Pepito" junto con su longitud -->

<p align="left"><strong>FIFOSERVER:</strong> Cadena recibida: "Pepito", longitud: 6</p>
<!-- El servidor confirma que ha recibido la cadena enviada por el cliente y muestra su longitud -->

<p align="left"><strong>FIFOSERVER:</strong> Cadena invertida enviada: "otipeP", longitud: 6</p>
<!-- El servidor envía la cadena invertida "otipeP" y muestra la longitud de la cadena invertida -->

<p align="left"><strong>FIFOCLIENT:</strong> Cadena recibida: "otipeP", longitud: 6</p>
<!-- El cliente muestra la cadena invertida recibida del servidor y su longitud -->

<p align="left"><strong>FIFOCLIENT:</strong> Ingrese cadena: end</p>
<!-- El cliente pide ingresar otra cadena, en este caso "end" para finalizar el ciclo -->

<p align="left"><strong>FIFOCLIENT:</strong> Cadena enviada: "end", longitud: 3</p>
<!-- El cliente informa que ha enviado la cadena "end" y su longitud -->

<p align="left"><strong>FIFOSERVER:</strong> Cadena recibida: "end", longitud: 3</p>
<!-- El servidor confirma que ha recibido la cadena "end", indicando que el cliente ha terminado de enviar mensajes -->

<h2 align="left">¡Gracias!</h2>
<!-- Mensaje de cierre para agradecer la ejecución del programa -->
