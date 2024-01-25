process blobo (int enem_tx, int enem_ty, file, int energia)
private
    int resolution3;
    int x3,y3;
    
    int enem_estado2;       //0: en pausa
                            //1: andando izquierda
                            //2: andando derecha
                            //3: persiguiendo
                            
	int enem_gravedad;
    int enem_max_gravedad;
    int enem_salto;
    
    int vel_horiz,vel_vert;
    int vel_horiz_ant;
    
    int cont_anim;
    int temp;
    int temp_espada;
	
	int var_enem_acelerac = 1;
    
    //variables para la detección de durezas
    int enem_dur[2][2];
    int enem_tilex, enem_tiley;
    int enem_offsx, enem_offsy;
    int enem_mover_h, enem_mover_v;
    int enem_p_dir, enem_p_dir_ini;
    int enem_estado;
    int p_libre;
	
	//"constantes" para la detección de durezas
	int VAR_ENEM_MAX_AVANZAR_DERECHA	= 11;
	int VAR_ENEM_MAX_AVANZAR_IZQUIERDA	= 4;
	int VAR_ENEM_ALTURA_TECHO			= 14;
	int VAR_ENEM_DIFERENCIA_CON_TECHO	= 2;
	
begin
    priority = -99;
    //file = enem_grafs[0][cte_blobo];
    z = 1;
    enem_gravedad = 2;
    enem_max_gravedad = 30;
    enem_salto = 40;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    //energia = 4;
    
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    temp = obtener_tile(&durezas, enem_tx, enem_ty, 0);
    
    //estableciendo comportamiento inicial
    switch (temp)
    case 255: enem_estado2 = 0; end   //0: en pausa
    case 253: enem_estado2 = 1; end   //1: andando izquierda
    case 254: enem_estado2 = 2; end   //2: andando derecha
    default: enem_estado2 = 1; end    //1: andando izquierda
    end //switch
    
    loop
        //cambios de estado
        switch (enem_estado2)
        case 0:		//en pausa
            if (veo_prota(x2, y2, 2, 50, 20))
                enem_estado2 = 3;
            end
        end
        case 1:		//andando izquierda
            vel_horiz--;
            if (vel_horiz < -10) vel_horiz = -10; end
        end
        case 2:		//andando derecha
            vel_horiz++;
            if (vel_horiz > 10) vel_horiz = 10; end
        end
        case 3:		//persiguiendo a prota
            if (exists(info_prota.id_prota))
                if (info_prota.id_prota.x2 <= x2)
                    vel_horiz--;
                    if (vel_horiz < -10) vel_horiz = -10; end
                else
                    vel_horiz++;
                    if (vel_horiz > 10) vel_horiz = 10; end
                end
                //si llegamos a un borde, damos un salto
                if ((info_prota.id_prota.y2 - y2) <= 0)
                    switch (enem_dur[1][2])
                    case 0,50,32,33,34,82,83,84,100,104:
                        if ((enem_estado == 0) || (enem_estado == 1))
                            vel_vert = -enem_salto;
                            enem_estado = 3;
                        end
                    end
                    end //switch
                end
            else
                if (vel_horiz > 0) vel_horiz--; end
                if (vel_horiz < 0) vel_horiz++; end
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
        
        enem_mover_v = 0;
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
        case 1:                     //andando izquierda
            switch (enem_dur[1][1])
            case 254:
                enem_estado2 = 2;
                //cont_estado = 0;
            end
            case 251:       //flecha hacia arriba (salta)
                if ((enem_estado == 1) || (enem_estado == 0))
                    vel_vert = -enem_salto;
                    enem_estado = 3;
                end
            end
            default:       //choque con pared
                if ((vel_horiz_ant != 0) && (vel_horiz == 0)) enem_estado2 = 2; end
            end
            end //switch
        end
        case 2:                     //andando derecha
            switch (enem_dur[1][1])
            case 253:
                enem_estado2 = 1;
                //cont_estado = 0;
            end
            case 251:       //flecha hacia arriba (salta)
                if ((enem_estado == 1) || (enem_estado == 0))
                    vel_vert = -enem_salto;
                    enem_estado = 3;
                end
            end
            default:       //choque con pared
                if ((vel_horiz_ant != 0) && (vel_horiz == 0)) enem_estado2 = 1; end
            end
            end //switch
        end
        case 3:
            //si se para porque choca con una pared, comprueba si puede seguir con un salto
            if (vel_horiz == 0)
                if (vel_horiz_ant > 0)
                    switch (enem_dur[2][0])
                    case 1,2,5,14,51,52,55,64:
                        p_libre = 0;
                    end
                    default: p_libre = 1; end
                    end //switch
                    
                    switch (obtener_tile(&durezas, enem_tilex + 1,enem_tiley - 2, 0))
                    case 1,2,5,14,51,52,55,64:
                        p_libre = (p_libre || 0);
                    end
                    default: p_libre = 1; end
                    end //switch
                end
                if (vel_horiz_ant < 0)
                    switch (enem_dur[0][0])
                    case 1,3,4,16,51,53,54,66:
                        p_libre = 0;
                    end
                    default: p_libre = 1; end
                    end //switch
                    
                    switch (obtener_tile(&durezas, enem_tilex - 1, enem_tiley - 2, 0))
                    case 1,3,4,16,51,53,54,66:
                        p_libre = (p_libre || 0);
                    end
                    default: p_libre = 1; end
                    end //switch
                end
                if (vel_horiz_ant == 0) p_libre = 0; end
            
                // si se puede, pues salta
                if (p_libre && ((enem_estado == 1) || (enem_estado == 0)))
                    vel_vert = -enem_salto;
                    enem_estado = 3;
                end
            end
        end
        end //switch
        
        //zona de gráficos
        switch (enem_estado2)
        case 0: graph = 1; end
        default:
            if (vel_horiz < 0) flags = 0; end
            if (vel_horiz > 0) flags = 1; end
            switch (enem_estado)
            case 0: graph = 1; end
            case 1:
                cont_anim++;
                if (cont_anim == 5)
					graph++;
					cont_anim = 0;
				end
                if (graph > 8) graph = 2; end
            end
            case 3: 
                if (vel_vert < 0)
					graph = 9;
				else
					graph = 10;
				end
                cont_anim = 4;
            end
            end //switch
        end
        end //switch
        
        //*************************
        //  ZONA DE IMPACTOS
        //*************************
        if (exists(info_prota.id_prota))
            //impacto con las balas
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                while (temp != 0)
                    energia -= temp.energia;
                    //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
                    //say("el disparo tenía energia: " + itoa(temp.energia));
                    temp.energia = 0;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                    temp = collision(type normal_shot);
                end
            end
            
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                temp = collision(type espadazo);
                if ((temp != 0) && (temp != temp_espada))
                    energia -= temp.energia;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                    temp_espada = temp;
                end
            end
                
            if (energia <= 0) break; end
        
            //impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 3;
                    info_prota.dano_exp = 3;
                    if (info_prota.id_prota.x2 > x2)
						info_prota.dano_vel_horiz = 20;
                    else
						info_prota.dano_vel_horiz = -20;
                    end
                end
            end
        end
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    random_item (2, x2, y2 - (id_tscroll.tmapa[0].ancho_tile / 2));
    enem_explos(x2, y2 - 8, 0, 0);
end