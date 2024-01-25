process items_image (file, graph, x, y, z, size, region)
begin
    //z=-15;
    signal(id,s_freeze);
    frame;
end


//***************************************************************************
//  PROCESOS GRÁFICOS DE ITEMS
//***************************************************************************

process shot_exp (x2, y2, energia, int vel_horiz)
private
    int item_gravedad;
    int item_max_gravedad;
    int item_lifetime;
    
    int x3, y3;
    int resolution3;
    int vel_horiz_ant;
    int vel_vert;
	
	int var_enem_acelerac = 1;
	
    //variables para la detección de durezas
    int enem_dur[2][2];
    int enem_tilex, enem_tiley;
    int enem_offsx, enem_offsy;
    int enem_mover_h, enem_mover_v;
	int enem_gravedad;
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
    file = item_grafs;
    graph = 1;
    if (energia >= 5) graph++; end
    if (energia >= 10) graph++; end
    
    item_gravedad = 1;
	enem_gravedad = item_gravedad;
    item_max_gravedad = 20;
    item_lifetime = 750;
    resolution3 = 10;
    
    //say("x2,y2: "+itoa(x2)+" "+itoa(y2));
    
    x3 = x2 * resolution3;
    switch (graph)
    case 1: y3 = (y2 + 6) * resolution3; end
    case 2: y3 = (y2 + 5) * resolution3; end
    case 3: y3 = (y2 + 4) * resolution3; end
    end //switch
    
    vel_horiz_ant = vel_horiz;
    enem_estado = 3;
    
    /*write(0, 10, 10, 0, &enem_dur[0][0]);
    write(0, 10, 20, 0, &enem_dur[0][1]);
    write(0, 10, 30, 0, &enem_dur[0][2]);
    write(0, 30, 10, 0, &enem_dur[1][0]);
    write(0, 30, 20, 0, &enem_dur[1][1]);
    write(0, 30, 30, 0, &enem_dur[1][2]);
    write(0, 50, 10, 0, &enem_dur[2][0]);
    write(0, 50, 20, 0, &enem_dur[2][1]);
    write(0, 50, 30, 0, &enem_dur[2][2]);*/
    
    loop
        vel_vert += item_gravedad;
        if (vel_vert > item_max_gravedad) vel_vert = item_max_gravedad; end
        angle -= vel_horiz * 1000;
        
        //DETECCION DE DUREZAS
        //localizamos la posición actual
        enem_tilex = (x3 / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        enem_tiley = (y3 / resolution3) / id_tscroll.tmapa[0].alto_tile;
        enem_offsx = (x3 / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        enem_offsy = (y3 / resolution3) % id_tscroll.tmapa[0].alto_tile;
        //leemos durezas de su alrededor
        enem_dur[0][0] = obtener_tile(&durezas, enem_tilex -1, enem_tiley -1, 0);
        enem_dur[1][0] = obtener_tile(&durezas, enem_tilex   , enem_tiley -1, 0);
        enem_dur[2][0] = obtener_tile(&durezas, enem_tilex +1, enem_tiley -1, 0);
        enem_dur[0][1] = obtener_tile(&durezas, enem_tilex -1, enem_tiley   , 0);
        enem_dur[1][1] = obtener_tile(&durezas, enem_tilex   , enem_tiley   , 0);
        enem_dur[2][1] = obtener_tile(&durezas, enem_tilex +1, enem_tiley   , 0);
        enem_dur[0][2] = obtener_tile(&durezas, enem_tilex -1, enem_tiley +1, 0);
        enem_dur[1][2] = obtener_tile(&durezas, enem_tilex   , enem_tiley +1, 0);
        enem_dur[2][2] = obtener_tile(&durezas, enem_tilex +1, enem_tiley +1, 0);
        //comprobamos si cambiamos de tile y en que direccion
        //***************************************************************
        enem_mover_h = 0;
        if (((x3 + vel_horiz) / (id_tscroll.tmapa[0].ancho_tile * resolution3)) != enem_tilex)
           //comprobamos si pasamos a otro tile lateral y cuan lejos esta
           enem_mover_h = ((x3 + vel_horiz) / (id_tscroll.tmapa[0].ancho_tile * resolution3)) - enem_tilex;
        end
        
        enem_mover_v = 0;
        if (((y3 + vel_vert) / (id_tscroll.tmapa[0].alto_tile * resolution3)) != enem_tiley)
           //comprobamos si pasamos a otro tile vertical y cuan lejos esta
           enem_mover_v = ((y3 + vel_vert) / (id_tscroll.tmapa[0].alto_tile * resolution3)) - enem_tiley;
        end
         //miramos en que direccion cambiamos
        enem_p_dir = 5;
        if (enem_mover_h > 0) enem_p_dir++; end
        if (enem_mover_h < 0) enem_p_dir--; end
        if (enem_mover_v > 0) enem_p_dir -= 3; end      //hacia abajo
        if (enem_mover_v < 0) enem_p_dir += 3; end      //hacia arriba
        enem_p_dir_ini = enem_p_dir;
        
        include "src/game/common/durezas_check.inc";
        
        if (vel_horiz == 0) vel_horiz =- vel_horiz_ant; end
        vel_horiz_ant =- vel_horiz_ant;
        if (enem_estado == 0)
            vel_vert = -20;
            enem_estado = 3;
        end
        
        switch (graph)
        case 1: y2 = (y3 / resolution3) - 6; end
        case 2: y2 = (y3 / resolution3) - 5; end
        case 3: y2 = (y3 / resolution3) - 4; end
        end //switch
        //y2 = y3 / resolution3;
        x2 = x3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        if (collision(type prota) || collision(type prota_moto))
            cambiar_exp_arma(energia);
            break;
        end
        
        //tiempo de vida (desaparece al rato)
        item_lifetime--;
        if (item_lifetime < 127) alpha = clamp( 2 * item_lifetime, 0, 255 ); end
        if (item_lifetime == 0) break; end
        frame;
    end
end

process item_energy (x2, y2, energia)
private
    int cont;
begin
    priority = -99;
    file = item_grafs;
    if (energia <= 5) graph = 4;
    elsif (energia <= 15) graph = 5;
    else graph = 6;
    end
    
    y2 += 8 - (y2 % id_tscroll.tmapa[0].alto_tile);
    loop
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        if (collision (type prota) || collision(type prota_moto))
            info_prota.p_energ += energia;
            if (info_prota.p_energ > info_prota.p_max_energ)
                info_prota.p_energ = info_prota.p_max_energ;
            end
            refresh_interface_energy();
            break;
        end
        
        cont++;
        if (cont >= 750) break; end
        
        frame;
    end
end