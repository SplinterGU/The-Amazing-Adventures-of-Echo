process roca_rodante (int enem_tx, int enem_ty, file, z)
private
    int enem_gravedad;
    int enem_max_gravedad;
    
    int resolution3, x3, y3;
    
    int vel_horiz, vel_vert;
	
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
    
    int temp;
begin
    //z = -999;
    priority = -99;
    graph = 1;
    enem_gravedad = 2;
    enem_max_gravedad = 30;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    
    
    //Descendemos el primer tile llevados por la gravedad, sí o sí
    temp = y2;
    while (y2 < (temp + id_tscroll.tmapa[0].alto_tile))
        //gravedad
        vel_vert += enem_gravedad;
        if (vel_vert > enem_max_gravedad) vel_vert = enem_max_gravedad; end
        y3 += vel_vert;
        
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        y -= 8;
        
        if (exists(info_prota.id_prota))
            //impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 5;
                    info_prota.dano_exp = 7;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 26;
                    else info_prota.dano_vel_horiz = -26;
                    end
                end
            end
        end
        frame;
    end
    
    
    energia = 1;
    while (energia > 0)
    
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
            
        //if (enem_gravedad=0)
            switch (enem_dur[1][1])
            case 2,52:
                vel_horiz += 2;
                if (vel_vert < abs(vel_horiz)) vel_vert = abs(vel_horiz); end
            end
            case 3,53:
                vel_horiz -= 2;
                if (vel_vert < abs(vel_horiz)) vel_vert = abs(vel_horiz); end
            end
            case 13,14,63,64:
                vel_horiz += 1;
                if (vel_vert < abs(vel_horiz)) vel_vert = abs(vel_horiz); end
            end
            case 15,16,65,66:
                vel_horiz -= 1;
                if (vel_vert < abs(vel_horiz)) vel_vert = abs(vel_horiz); end
            end
            end //switch
            
            if (vel_horiz > 30) vel_horiz = 30; end
            if (vel_horiz < -30) vel_horiz = -30; end
            
            //vel_vert=abs(vel_horiz);
        //else
            //gravedad
            vel_vert += enem_gravedad;
            if (vel_vert > enem_max_gravedad) vel_vert = enem_max_gravedad; end
        //end
        
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
        
        //Si se para totalmente sobre un tile que indica su rotura
        if ((vel_horiz == 0) && (vel_vert == 0) && (enem_dur[1][1] == 255))
			energia = 0;
		end
        if (energia <= 0) break; end
            
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        y -= 8;
        angle += -7000 * vel_horiz / resolution3;
        
        if (exists(info_prota.id_prota))
            //impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 5;
                    info_prota.dano_exp = 7;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 26;
                    else info_prota.dano_vel_horiz = -26;
                    end
                end
            end
        end
        frame;
    end
end

process roca_lanzador (int enem_tx, int enem_ty, file, z)
private
    int tile_nivel;
    
    int rl_espera;
    int cont;
begin
    tile_nivel = obtener_tile(&nivel, enem_tx, enem_ty, 0);
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    //temp1 = obtener_tile(&durezas, enem_tx, enem_ty, 0);
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile);

    rl_espera = 3 * 50;
    //Debe sincronizarse
    cont = rl_espera - (sincronizacion % rl_espera);
    
    loop
        cont--;
        if (cont < 0)
            cont = rl_espera;
            roca_rodante (enem_tx, enem_ty-1, file, z);
            tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
            //say("lanzador ID: " + id + "  pos(" + x + "," + y + ")");
        end
        
        if ( ((x < -50) || (x > 370) || (y < -50) || (y > 290)) && (get_id(type roca_rodante) == 0))
            break;
        end
        frame;
    end
    
    modificar_tile(&nivel, enem_tx, enem_ty, 0, tile_nivel);
end