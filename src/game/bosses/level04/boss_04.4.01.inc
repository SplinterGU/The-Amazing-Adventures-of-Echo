// FUNCIONES QUE ALTERAN EL ESCENARIO *************************************************
function boss0404_modificar_escenario (int b44_fase)
private
	int max_x, max_y;
	int cont_x, cont_y;
begin
	max_x = nivel.columnas;
	max_y = nivel.filas;
	//say("Fase: " + b44_fase);
	//say("mapa: " + max_x + " " + max_y);
	switch (b44_fase)
	case 1:
		for (cont_y = 0; cont_y < max_y; cont_y++)
			cont_x = 0;
			for (cont_x = 0; cont_x < max_x; cont_x++)
				//say(cont_x + "," + cont_y + ": " + obtener_tile(&nivel, cont_x, cont_y, 0));
				switch (obtener_tile(&nivel, cont_x, cont_y, 0))
				case 1: modificar_tile(&nivel, cont_x, cont_y, 0, 11); end
				case 2: modificar_tile(&nivel, cont_x, cont_y, 0, 12); end
				case 3: modificar_tile(&nivel, cont_x, cont_y, 0, 13); end
				end //switch
			end
		end
		ts_actualiza_tiles(&id_tscroll);
	end
	case 2:
		for (cont_y = 0; cont_y < max_y; cont_y++)
			cont_x = 0;
			for (cont_x = 0; cont_x < max_x; cont_x++)
				switch (obtener_tile(&nivel, cont_x, cont_y, 0))
				case 11: modificar_tile(&nivel, cont_x, cont_y, 0, 21); end
				case 12: modificar_tile(&nivel, cont_x, cont_y, 0, 22); end
				case 13: modificar_tile(&nivel, cont_x, cont_y, 0, 23); end
				end //switch
			end
		end
		ts_actualiza_tiles(&id_tscroll);
	end
	case 3:
		for (cont_y = 0; cont_y < max_y; cont_y++)
			cont_x = 0;
			for (cont_x = 0; cont_x < max_x; cont_x++)
				switch (obtener_tile(&nivel, cont_x, cont_y, 0))
				case 21: modificar_tile(&nivel, cont_x, cont_y, 0, 31); end
				case 22: modificar_tile(&nivel, cont_x, cont_y, 0, 32); end
				case 23: modificar_tile(&nivel, cont_x, cont_y, 0, 33); end
				end //switch
			end
		end
		ts_actualiza_tiles(&id_tscroll);
	end
	end //switch
end


// FUNCIONES DE LOS ENEMIGOS *******************************************************************
function boss44_get_next_mummy_direction (x2, y2)
// devuelve:	0 = arriba
//				1 = abajo
//				2 = izquierda
//				3 = derecha
private
	int enem_tilex, enem_tiley;
	int dist_horiz, dist_vert;
	int enem_pdir[3];
	int enem_pdur[3];
	int lim_max, lim_min;
	int dato_a_devolver;
	
	int cont;
begin
	//Medimos las distancias hasta el prota en cada una de las 4 direcciones (en positivo o en negativo)
	if (exists(info_prota.id_prota))
		dist_horiz = info_prota.id_prota.x2 - x2;
		dist_vert = info_prota.id_prota.y2 - y2;
		enem_pdir[0] = dist_vert;
		enem_pdir[1] = -dist_vert;
		enem_pdir[2] = dist_horiz;
		enem_pdir[3] = -dist_horiz;
	else
		enem_pdir[0] = 50;
		enem_pdir[1] = 50;
		enem_pdir[2] = 50;
		enem_pdir[3] = 50;
	end
	
	//Descartamos las direcciones que estén bloqueadas, poninendo una distancia no válida
	enem_tilex = x2 / id_tscroll.tmapa[0].ancho_tile;
	enem_tiley = y2 / id_tscroll.tmapa[0].alto_tile;
	enem_pdur[0] = obtener_tile(&durezas, enem_tilex    , enem_tiley - 1, 0);
	enem_pdur[1] = obtener_tile(&durezas, enem_tilex    , enem_tiley + 1, 0);
	enem_pdur[2] = obtener_tile(&durezas, enem_tilex - 1, enem_tiley    , 0);
	enem_pdur[3] = obtener_tile(&durezas, enem_tilex + 1, enem_tiley    , 0);
	
	if ((enem_pdur[0] > 0) && (enem_pdur[0] < 150)) enem_pdir[0] = 0; end
	if ((enem_pdur[1] > 0) && (enem_pdur[1] < 150)) enem_pdir[1] = 0; end
	if ((enem_pdur[2] > 0) && (enem_pdur[2] < 150)) enem_pdir[2] = 0; end
	if ((enem_pdur[3] > 0) && (enem_pdur[3] < 150)) enem_pdir[3] = 0; end
	
	//Usamos las distancias como límites máximos y mínimos (las positivas para el límite superior y las 
	//negativas para el inferior
	lim_max = 0;
	lim_min = 0;
	for (cont = 0; cont < 4; cont++)
		if (enem_pdir[cont] > 0)
			lim_max += enem_pdir[cont];
		else
			lim_min += enem_pdir[cont];
		end
	end
	
	//Obtenemos un valor aleatorio
	lim_min = lim_min / (dificultad + 1);	//cuanta más difícultad, menos posibilidades de que salga un valor negativo,
											//que es una dirección opuesta a la del prota
	repeat
		dato_a_devolver = rand(lim_min, lim_max);
	until (dato_a_devolver != 0)
		
	//Si el valor es positivo, nos movemos hacia el prota, si el valor es negativo nos movemos en dirección opuesta
	if (dato_a_devolver > 0)
		//El rand positivo es la suma de la distancia horiz y vertical. Comprobamos primero la horizontal
		if (dato_a_devolver <= abs(dist_horiz))
			if (dist_horiz < 0)
				dato_a_devolver = 2;
			else
				dato_a_devolver = 3;
			end
		else
			if (dist_vert < 0)
				dato_a_devolver = 0;
			else
				dato_a_devolver = 1;
			end
		end
	else
		if (dato_a_devolver <= (abs(dist_horiz) / (dificultad + 1)))
			if (dist_horiz < 0)
				dato_a_devolver = 3;
			else
				dato_a_devolver = 2;
			end
		else
			if (dist_vert < 0)
				dato_a_devolver = 1;
			else
				dato_a_devolver = 0;
			end
		end
	end
	
	return dato_a_devolver;
end


process master_mummy (int enem_tx, int enem_ty, file, graph, int imthemaster)
private
	int enem_estado2;		//0: andando arriba
							//1: andando abajo
                            //2: andando izquierda
							//3: andando derecha
                            //4: baile de sambito (arriba, abajo)
							//5: baile de sambito (izquierda, derecha)
	int enem_estado2_ant;
    int x3, y3;
    int resolution3;
	
	int cont_estado;        //dice el tiempo que queda para cambiar de estado
    int cont_anim;          //cuenta el retardo entre frames
    int pos_anim;           //indica qué gráfico de animación de andar muestra
    byte enem_anim_h[3] = 1, 2, 1, 3;	//animación andar
	byte enem_anim_v1[3] = 4, 5, 4, 5;  //animación andar arriba
	byte enem_anim_v2[3] = 6, 7, 6, 7;  //animación andar abajo
    
    int vel_horiz, vel_vert;
    int enem_gravedad;
    int enem_max_gravedad;
    int enem_salto;
	
	int temp;
	
	//variables para la detección de durezas
    int enem_dur[2][2];
    int enem_tilex, enem_tiley;
    int enem_offsx, enem_offsy;
    int enem_mover_h, enem_mover_v;
    int enem_p_dir, enem_p_dir_ini;
    int enem_estado;
    int p_libre;
	
	//"constantes" para la detección de durezas
	int VAR_ENEM_MAX_AVANZAR_DERECHA	= 15;
	int VAR_ENEM_MAX_AVANZAR_IZQUIERDA	= 0;
	int VAR_ENEM_ALTURA_TECHO			= 16;
	int VAR_ENEM_DIFERENCIA_CON_TECHO	= 0;
begin
	priority = -99;
    //file = enem_grafs[0][cte_guerrillero];
    z = 1;
    enem_gravedad = 2;
    enem_max_gravedad = 30;
    enem_salto = 40;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
	
	//estableciendo comportamiento inicial
	enem_estado2 = 4;
	enem_estado2_ant = boss44_get_next_mummy_direction (x2, y2);
	loop
		//cambios de estado
        switch (enem_estado2)
		case 0:         //andando arriba
            cont_estado++;
            vel_vert--;
            if (vel_vert < -7) vel_vert = -7; end
        end
		case 1:         //andando derecha
            cont_estado++;
            vel_vert++;
            if (vel_vert > 7) vel_vert = 7; end
        end
        case 2:         //andando izquierda
            cont_estado++;
            vel_horiz--;
            if (vel_horiz < -7) vel_horiz = -7; end
        end
		case 3:         //andando derecha
            cont_estado++;
            vel_horiz++;
            if (vel_horiz > 7) vel_horiz = 7; end
        end
		case 4:		//Baile de sambito arriba y abajo
			if (cont_anim >= 200)
				enem_estado2 = enem_estado2_ant;
				cont_anim = 0;
				cont_estado = 0;
			end
		end
		case 5:		//Baile de sambito izquierda y derecha
			if (cont_anim >= 200)
				enem_estado2 = enem_estado2_ant;
				cont_anim = 0;
				cont_estado = 0;
			end
		end
		end //switch
		
		
		//DETECCION DE DUREZAS
        //localizamos la posición actual
        enem_tilex = (x3 / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        enem_tiley = (y3 / resolution3) / id_tscroll.tmapa[0].alto_tile;
        enem_offsx = (x3 / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        enem_offsy = (y3 / resolution3) % id_tscroll.tmapa[0].alto_tile;
        //leemos durezas de su alrededor
        enem_dur[0][0] = obtener_tile(&durezas, enem_tilex - 1, enem_tiley - 1, 0);
        enem_dur[1][0] = obtener_tile(&durezas, enem_tilex    , enem_tiley - 1, 0);
        enem_dur[2][0] = obtener_tile(&durezas, enem_tilex + 1, enem_tiley - 1, 0);
        enem_dur[0][1] = obtener_tile(&durezas, enem_tilex - 1, enem_tiley    , 0);
        enem_dur[1][1] = obtener_tile(&durezas, enem_tilex    , enem_tiley    , 0);
        enem_dur[2][1] = obtener_tile(&durezas, enem_tilex + 1, enem_tiley    , 0);
        enem_dur[0][2] = obtener_tile(&durezas, enem_tilex - 1, enem_tiley + 1, 0);
        enem_dur[1][2] = obtener_tile(&durezas, enem_tilex    , enem_tiley + 1, 0);
        enem_dur[2][2] = obtener_tile(&durezas, enem_tilex + 1, enem_tiley + 1, 0);
        //comprobamos si cambiamos de tile y en que direccion
        //***************************************************************
        enem_mover_h = 0;
		temp = (x3 + vel_horiz) / (id_tscroll.tmapa[0].ancho_tile * resolution3);
        if (temp != enem_tilex)
           //comprobamos si pasamos a otro tile lateral y cuan lejos esta
           enem_mover_h = temp - enem_tilex;
        end
        
        enem_mover_v=0;
		temp = (y3 + vel_vert) / (id_tscroll.tmapa[0].alto_tile * resolution3);
        if (temp != enem_tiley)
           //comprobamos si pasamos a otro tile vertical y cuan lejos esta
           enem_mover_v = temp - enem_tiley;
        end
         //miramos en que direccion cambiamos
        enem_p_dir = 5;
        if (enem_mover_h > 0) enem_p_dir++; end
        if (enem_mover_h < 0) enem_p_dir--; end
        if (enem_mover_v > 0) enem_p_dir -= 3; end      //hacia abajo
        if (enem_mover_v < 0) enem_p_dir += 3; end      //hacia arriba
        enem_p_dir_ini = enem_p_dir;
        
        include "src/game/common/durezas_check.inc";
		
		
		x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
	end
	
end