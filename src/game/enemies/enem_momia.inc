process momia (int enem_tx, int enem_ty, file)
private
    int tile_inicial;
    int enem_estado2;       //0: andando derecha (patrullando)
                            //1: andando izquierda (patrullando)
                            //2: persiguiendo (te ve y se lanza al ataque)
                            //3: baile de sambito (arriba, abajo)
							//4: baile de sambito (izquierda, derecha)
	int enem_estado2_ant;
    int x3, y3;
    int resolution3;
    
    int vel_horiz, vel_vert;
    int enem_gravedad;
    int enem_max_gravedad;
    int enem_salto;
    
    int cont_estado;        //dice el tiempo que queda para cambiar de estado
    int cont_anim;          //cuenta el retardo entre frames
    int pos_anim;           //indica qué gráfico de animación de andar muestra
    byte enem_anim[3] = 1, 2, 1, 3;  //animación andar
    
    int temp;
    double temp_x1, temp_y1;
    int vel_horiz_ant;
    int temp_espada;
	
    //variables para la detección de durezas
    int enem_dur[2][2];
    int enem_tilex, enem_tiley;
    int enem_offsx, enem_offsy;
    int enem_mover_h, enem_mover_v;
    int enem_p_dir, enem_p_dir_ini;
    int enem_estado;
    int p_libre;
	
	int var_enem_acelerac = 1;
	
	//"constantes" para la detección de durezas
	int VAR_ENEM_MAX_AVANZAR_DERECHA	= 11;
	int VAR_ENEM_MAX_AVANZAR_IZQUIERDA	= 4;
	int VAR_ENEM_ALTURA_TECHO			= 14;
	int VAR_ENEM_DIFERENCIA_CON_TECHO	= 2;
	
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
    energia = 5;
    
    tile_inicial = obtener_tile(&nivel, enem_tx, enem_ty, 0);
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    temp = obtener_tile(&durezas, enem_tx, enem_ty, 0);
    
    //estableciendo comportamiento inicial
    switch (temp)
    case 253: enem_estado2 = 1; end
    case 254: enem_estado2 = 0; flags = 1; end
    default: enem_estado2 = 1; end
    end //switch
	
	loop
		//cambios de estado
        switch (enem_estado2)
		case 0:         //andando derecha
            cont_estado++;
            vel_horiz++;
            if (vel_horiz > 7) vel_horiz = 7; end
            if (veo_prota(x2, y2, 1, 110, 50)) enem_estado2 = 2; end
        end
        case 1:         //andando izquierda
            cont_estado++;
            vel_horiz--;
            if (vel_horiz < -7) vel_horiz = -7; end
            if (veo_prota(x2, y2, 0, 110, 50)) enem_estado2 = 2; end
        end
		case 2:		//persiguiendo al prota
            if (exists(info_prota.id_prota))
                //comprobamos distancia con el prota
                temp = info_prota.id_prota.x2 - x2;
                
				//un poco más lejos nos acercamos
				if (temp > 32) 
					vel_horiz = 7;
					//si llegamos a un borde, hacemos el baile de sambito y nos damos la vuelta
					switch (enem_dur[2][2])
					case 0,50,32,33,34,82,83,84,100,104:
						enem_estado2_ant = 1; 
						enem_estado2 = 3;
						cont_anim = 0;
					end
					end //switch
				elsif (temp < -32) 
					vel_horiz = -7;
					//si llegamos a un borde, hacemos el baile de sambito y nos damos la vuelta
					switch (enem_dur[0][2])
					case 0,50,32,33,34,82,83,84,100,104:
						enem_estado2_ant = 0; 
						enem_estado2 = 3;
						cont_anim = 0;
					end
					end //switch
				end
            end
        end
		case 3:		//Baile de sambito arriba y abajo
			if (cont_anim >= 200)
				enem_estado2 = enem_estado2_ant;
				cont_anim = 0;
				cont_estado = 0;
			end
		end
		case 4:		//Baile de sambito izquierda y derecha
			if (cont_anim >= 200)
				enem_estado2 = enem_estado2_ant;
				cont_anim = 0;
				cont_estado = 0;
			end
		end
		end //switch
		
		
		vel_horiz_ant = vel_horiz;
        
        //gravedad
        vel_vert += enem_gravedad;
        if (vel_vert > enem_max_gravedad) vel_vert = enem_max_gravedad; end
        
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
        
		//post análisis
        if ( (vel_horiz != 0) && (enem_estado == 0) )
            enem_estado = 1;
        end
        if ( (vel_horiz == 0) && (enem_estado == 1) )
            enem_estado = 0;
        end
        
        switch (enem_estado2)
        case 0:
            switch (enem_dur[1][1])
            case 253:
                enem_estado2 = 1;
                cont_estado = 0;
            end
            end //switch
        end
        case 1:
            switch (enem_dur[1][1])
            case 254:
                enem_estado2 = 0;
                cont_estado = 0;
            end
            end //switch
        end
        case 2:
			temp = info_prota.id_prota.x2 - x2;
            if (temp > 0)
				flags = 1;
			else
				flags = 0;
			end
            
            //si se para porque choca con una pared, comprueba si puede seguir con un salto
            if (vel_horiz == 0)
                if (vel_horiz_ant > 0)
                    enem_estado2_ant = 1; 
					enem_estado2 = 3;
                end
                if (vel_horiz_ant < 0)
                    enem_estado2_ant = 0; 
					enem_estado2 = 3;
                end
            end
        end
        end //switch
        
        
        //zona de gráficos
        switch (enem_estado2)
        case 0,1,2:   //patrullando y persiguiendo
            switch (enem_estado)
            case 0:
                graph = 1;
            end
            case 1:
                if (vel_horiz > 0) flags = 1; end
                if (vel_horiz < 0) flags = 0; end
                cont_anim++;
                if (cont_anim == 10)
                    cont_anim = 0;
                    if (pos_anim == 3)
						pos_anim = 0;
					else
						pos_anim++;
					end
                    graph = enem_anim[pos_anim];
                end
            end
            case 2,3: graph = 5; end
            end //switch
		end
		case 3:		//Baile de sambito arriba y abajo
			flags = 0;
			if (cont_anim % 30 == 0)
				graph = 7;
			else
				if (cont_anim % 15 == 0)
					graph = 4;
				end
			end
			cont_anim++;
		end
		case 4:		//Baile de sambito izquierda y derecha
			graph = 2;
			if (cont_anim % 50 == 0)
				flags = 0;
			else
				if (cont_anim % 25 == 0)
					flags = 1;
				end
			end
			cont_anim++;
		end
        end //switch
        
        //************************
        //  ZONA DE COLISIONES
        //************************
        if (exists(info_prota.id_prota))
			//Choque con disparos
			if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                while (temp != 0)
                    temp.energia = 0;
                    temp = collision(type normal_shot);
                end
            end
			
			//impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 5;
                    info_prota.dano_exp = 4;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                    else info_prota.dano_vel_horiz = -20;
                    end
                end
            end
        end
        
        if (energia <= 0) break; end
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
		
		//Si sale de pantalla, se vuelve a colocar en el mapa
        if ((x < -320) || (x > 640) || (y < -320) || (y > 640)) break; end
	end
	
	//if (energia <= 0)
    //    random_item (2, x2, y2 - (id_tscroll.tmapa[0].ancho_tile / 2));
    //    enem_explos(x2, y2 - 8, 0, 0);
    //else
        //Ha salido de pantalla, pero no ha muerto
        //Comprobamos si el tile actual está libre para permanecer en él de guardia
        if ((enem_estado2 == 6) && (obtener_tile(&nivel, enem_tilex, enem_tiley, 0) == 0))
            if (flags == 1)
				flags = 1;
			else
				flags = 0;
			end
			
            switch (tile_inicial) //REVISAR ****************************************************
            case 150,151:
                modificar_tile(&nivel, enem_tilex, enem_tiley, 0, 150 + flags);
            end
            case 169,170:
                modificar_tile(&nivel, enem_tilex, enem_tiley, 0, 169 + flags);
            end
			// *********************************************************************************
            end //switch
        else
			//si no, se coloca en su posición original, invisible, hasta que quede fuera de la cámara
			//y luego se vuelve a poner en el mapa
            graph = 0;
            x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
            y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
            repeat
                tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);	//pos inicial
                frame;
            until ((x < -32) || (x > 352) || (y < -32) || (y > 272))	//Espera a que la cámara se aleje
            modificar_tile(&nivel, enem_tx, enem_ty, 0, tile_inicial);	//Se coloca en su posición inicial
        end
    //end
end