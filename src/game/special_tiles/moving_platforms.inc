process plataforma_movil_por_contacto (x3,y3,z2,file, int graph1, int graph2, int lon)
//plataforma que comienza a desplazarse al pisarla
//x3, y3: posición en el mapa de tiles
//graph1: primer gráfico de animación de la plataforma
//graph2: último gráfico de animación de la plataforma (si es igual que graph1, no habrá animación)
//lon:	  número de tiles de ancho de la plataforma

//Por hacer
//* Movimiento en las 4 direcciones
//- Al pararse, ¿sustituir durezas por suelo atravesable?
//- ¿Puede volver al inicio?
//- ¿Sustituir posiciones iniciales por durezas de suelo atravesable, guardando temporalmente dureza-flecha inicial?
//  No, porque cuando esté en movimiento también tiene que bloquear al prota en caida
//* En prota, recolocarse sobre plataforma sólo en el momento en que se posa
//* En prota, salir de modo plataforma al saltar (linea 137)
//- En prota, salir de modo plataforma al alejarse demasiado de esta
//* En prota, poner gravedad a cero si estamos en pltaforma (linea 141)
//- En prota, salir de modo plataforma si al bajar la plataforma, el prota se posa en suelo firme (o choca con rampa)
//- Arreglar retardo entre movimiento de plataforma y de prota
//- Arreglar atravesar paredes si está en modo plataforma
//- ¿Matar al prota al aplastar contra el techo?
//* Añadir include a lista de ficheros.
//* Añadir tiles especiales en add_tile.inc
private
    int estado; //0: en espera    1: en movimiento    2:fin de trayecto
	int estado2;	//0: arriba	 1: abajo	2: izquierda	3: derecha
	int resolution3;
	int temp_dir;
    int cont;
    int temp;
begin
    //se ordenan de menor a mayor los gráficos de inicio y final (por si acaso)
	if (graph1 != graph2)
		if (graph2 < graph1)
			temp = graph2;
			graph2 = graph1;
			graph1 = temp;
		end
	end
    
    //Se coloca el tile
    modificar_tile(&nivel,x3,y3,z2,0);
    //modificar_tile(&durezas,x3,y3,0,25);
	temp_dir = obtener_tile(&durezas, x3, y3, 0);
    
    //estableciendo comportamiento inicial
    switch (temp_dir)
    case 251: estado2 = 0; end       //movemos hacia arriba
    case 252: estado2 = 1; end       //movemos hacia abajo
    case 253: estado2 = 2; end       //movemos hacia izquierda
    case 254: estado2 = 3; end       //movemos hacia derecha
    end //switch
	if ((info_prota.id_prota != 0) && exists(info_prota.id_prota))
		priority = info_prota.id_prota - 1;
	else
		priority=-100;
	end
    x2 = (x3 * id_tscroll.tmapa[0].ancho_tile);
    y2 = (y3 * id_tscroll.tmapa[0].alto_tile);
    
	resolution3 = 10;
	x3 = x2 * resolution3;
	y3 = y2 * resolution3;
	
    graph = graph1;
    loop
	
		//Primero comprobamos si el prota no está pisando esta plataforma
		if ((info_prota.id_prota != 0) && exists(info_prota.id_prota))
			if (info_prota.id_plataforma != id)
				//Comprobamos, tras el movimiento del prota, si entre su anterior posición (según su velocidad vertical)
				//y la actual ha intentado atravesar esta plataforma.
				if ((info_prota.y2_ant <= y2) && (info_prota.id_prota.y2 > y2) &&
					(info_prota.id_prota.x2 > x2 - cte_prota_max_avanzar_izquierda) &&
					(info_prota.id_prota.x2 < x2 + (lon * id_tscroll.tmapa[0].ancho_tile) + cte_prota_max_avanzar_izquierda))
					
					info_prota.id_plataforma = id;
					//Forzamos un reajuste de posición del prota antes de que acabe el frame
					say("Pos prota antes: " + info_prota.id_prota.y2 + ",  " + info_prota.id_prota.y);
					info_prota.id_prota.y2 = y2 - 1;
					tscroll_get_screen_position(&id_tscroll,info_prota.id_prota.x2,info_prota.id_prota.y2,
												&info_prota.id_prota.x,&info_prota.id_prota.y);
					say("Pos prota despues: " + info_prota.id_prota.y2 + ",  " + info_prota.id_prota.y);
					//Y ahora nos ejecutaremos siempre antes que el prota
					priority = 99;
					
				end
			else
				//Si no está pisando la plataforma, lo liberamos de ataduras
				if ((info_prota.id_prota.x2 < x2 - cte_prota_max_avanzar_izquierda) ||
					(info_prota.id_prota.x2 > x2 + (lon * id_tscroll.tmapa[0].ancho_tile) + cte_prota_max_avanzar_izquierda))
					info_prota.id_plataforma = -1;
				end
			end
		end
		//Si no está pisando la plataforma, la prioridad debe ser muy baja, debe ejecutarse después del prota
		if ((info_prota.id_plataforma != id) && (priority != -100)) priority = -100; end
		
		switch (estado)
        case 0: //esperando a ser pisado
            if ((info_prota.id_prota != 0) && exists(info_prota.id_prota) && (info_prota.id_plataforma == id))
				estado = 1;
				cont = 0;
            end
        end
        case 1: //en movimiento
			//si se llega a la esquina de un tile, hemos cambiado de tile y puede haber un cambio de dirección
			if (((x2 % id_tscroll.tmapa[0].ancho_tile) == 0) && ((y2 % id_tscroll.tmapa[0].alto_tile) == 0))
				temp_dir = obtener_tile(&durezas,
										x2 / id_tscroll.tmapa[0].ancho_tile,
										y2 / id_tscroll.tmapa[0].alto_tile, 0);
				
				//estableciendo nueva dirección
				switch (temp_dir)
				case 251: estado2 = 0; end       //movemos hacia arriba
				case 252: estado2 = 1; end       //movemos hacia abajo
				case 253: estado2 = 2; end       //movemos hacia izquierda
				case 254: estado2 = 3; end       //movemos hacia derecha
				case 255:	//tile fin del camino (si no, habría que comprobar todos los tiles a lo ancho de la
							//plataforma, y no podríamos atravesar bloques que impiden el paso al prota)
					estado2 = -1;
					estado = 2;
				end
				end //switch
			end
			
			switch (estado2)
			case 0: //moviendo hacia arriba
				y3 -= resolution3 /2;
				y2 = y3 / resolution3;
				if ((info_prota.id_prota != 0) && exists(info_prota.id_prota) && (info_prota.id_plataforma == id))
					info_prota.ext_vely = - resolution3 / 2;
				end
			end
			case 1:	//moviendo hacia abajo
				y3 += resolution3 /2;
				y2 = y3 / resolution3;
				if ((info_prota.id_prota != 0) && exists(info_prota.id_prota) && (info_prota.id_plataforma == id))
					info_prota.ext_vely = resolution3 / 2;
				end
			end
			case 2: //moviendo hacia izquierda
				x3 -= resolution3 /2;
				x2 = x3 / resolution3;
				if ((info_prota.id_prota != 0) && exists(info_prota.id_prota) && (info_prota.id_plataforma == id))
					info_prota.ext_velx = - resolution3 / 2;
				end
			end
			case 3:	//moviendo hacia derecha
				x3 += resolution3 /2;
				x2 = x3 / resolution3;
				if ((info_prota.id_prota != 0) && exists(info_prota.id_prota) && (info_prota.id_plataforma == id))
					info_prota.ext_velx = resolution3 / 2;
				end
			end
			end //switch
        end
        case 2: //fin de trayecto
            /*cont++;
            if (cont >= 300)
                modificar_tile(&durezas,x3,y3,0,25);
                estado = 3;
                cont = 0;
            end*/
        end
        end //switch
        
		if (priority > 0) frame(0); end	//Con esto nos aseguramos de que el scroll se refresca antes
        tscroll_get_screen_position(&id_tscroll,x2,y2,&x,&y);
        frame;
    end
end
