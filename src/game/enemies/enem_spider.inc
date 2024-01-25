process spider (int enem_tx, int enem_ty, energia)
private
    int enem_estado2;       //0: suelo, en espera
                            //1: iniciando salto
                            //2: en salto
                            //3: tocando suelo
    int cont_anim;
    int pos_anim;
    int enem_anim[3] = 2, 3, 2, 4;
    
    int temp1;
    int temp2;
    int temp_espada;
    
    int enem_gravedad;
    int enem_max_gravedad;
    int enem_salto;
    int resolution3;
    int x3, y3;
    
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
	
begin
    priority = -99;
    file = enem_grafs[0][cte_spider];
    graph = 1;
    z = 1;
    enem_gravedad = 2;
    enem_max_gravedad = 20;
    enem_salto = 40;
    
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    temp1 = obtener_tile(&durezas, enem_tx, enem_ty, 0);
    //say("modificado tile");
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile);
    switch (temp1)
    case 251:
        x2 += (id_tscroll.tmapa[0].ancho_tile / 2);
        angle = 180000;
    end
    case 252:
        x2 += (id_tscroll.tmapa[0].ancho_tile / 2);
        y2 += (id_tscroll.tmapa[0].alto_tile - 1);
    end
    case 253:
        y2 += ((id_tscroll.tmapa[0].alto_tile / 2) - 1);
        angle = -90000;
    end
    case 254:
        x2 += (id_tscroll.tmapa[0].ancho_tile - 1);
        y2 += ((id_tscroll.tmapa[0].alto_tile / 2) - 1);
        angle = 90000;
    end
    default:
        x2 += (id_tscroll.tmapa[0].ancho_tile / 2);
        y2 += (id_tscroll.tmapa[0].alto_tile - 1);
    end
    end //switch
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    //energia = 4;
    //say("comienza código");
    
    loop
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        if (veo_prota(x2, y2, 2, 100, 100)) break; end
        
        if (exists(info_prota.id_prota))
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp2 = collision(type normal_shot);
                while (temp2 != 0)
                    energia -= temp2.energia;
                    //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
                    //say("el disparo tenía energia: " + itoa(temp.energia));
                    temp2.energia = 0;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                    temp2 = collision(type normal_shot);
                end
            end
            
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                temp2 = collision(type espadazo);
                if ((temp2 != 0) && (temp2 != temp_espada))
                    energia -= temp2.energia;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                    temp_espada = temp2;
                end
            end
            
            //impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 3;
                    info_prota.dano_exp = 4;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 26;
                    else info_prota.dano_vel_horiz = -26;
                    end
                end
            end
        end
        
        if (energia <= 0) break; end
        
        frame;
    end
    //say("cayendo");
    
    //iniciamos caida
    if (energia > 0)
        //movimiento
        switch (temp1)
        case 253: vel_horiz = 10; end
        case 254: vel_horiz = -10; end
        end
        enem_estado = 3;
        
        while ((angle != 0) || (enem_estado != 0))
            //say(itoa(temp2) + " " + itoa(vel_horiz));
            angle = near_angle(angle, 0, 10000);
            
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
			temp2 = (x3 + vel_horiz) / (id_tscroll.tmapa[0].ancho_tile * resolution3);
            if (temp2 != enem_tilex)
               //comprobamos si pasamos a otro tile lateral y cuan lejos esta
               enem_mover_h = temp2 - enem_tilex;
            end
            
            enem_mover_v = 0;
			temp2 = (y3 + vel_vert) / (id_tscroll.tmapa[0].alto_tile * resolution3);
            if (temp2 != enem_tiley)
               //comprobamos si pasamos a otro tile vertical y cuan lejos esta
               enem_mover_v = temp2 - enem_tiley;
            end
             //miramos en que direccion cambiamos
            enem_p_dir = 5;
            if (enem_mover_h > 0) enem_p_dir++; end
            if (enem_mover_h < 0) enem_p_dir--; end
            if (enem_mover_v > 0) enem_p_dir -= 3; end      //hacia abajo
            if (enem_mover_v < 0) enem_p_dir += 3; end      //hacia arriba
            enem_p_dir_ini = enem_p_dir;
            
            include "src/game/common/durezas_check.inc";
            
            if (exists(info_prota.id_prota))
                //impacto con las armas
                if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                    temp2 = collision(type normal_shot);
                    while (temp2 != 0)
                        energia -= temp2.energia;
                        //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
                        //say("el disparo tenía energia: " + itoa(temp.energia));
                        temp2.energia = 0;
                        if ((mi_temblor != 0) && exists(mi_temblor))
                            mi_temblor.energia = 3;
                        else
                            mi_temblor = enem_temblor(id, 3);
                        end
                        temp2 = collision(type normal_shot);
                    end
                end
                
                if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                    temp2 = collision(type espadazo);
                    if ((temp2 != 0) && (temp2 != temp_espada))
                        energia -= temp2.energia;
                        if ((mi_temblor != 0) && exists(mi_temblor))
                            mi_temblor.energia = 3;
                        else
                            mi_temblor = enem_temblor(id, 3);
                        end
                        temp_espada = temp2;
                    end
                end
                
                //impacto con el prota
                if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                    if (collision(info_prota.id_prota))
                        info_prota.dano_id = id;
                        info_prota.dano_energia = 3;
                        info_prota.dano_exp = 4;
                        if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 26;
                        else info_prota.dano_vel_horiz = -26;
                        end
                    end
                end
            end
            
            if (energia <= 0) break; end
            
            x2 = x3 / resolution3;
            y2 = y3 / resolution3;
            tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
            frame;
        end
    end
    vel_horiz = 0;
    
    //say("actuando");
    //caida finalizada
    if (energia > 0)
        enem_estado2 = 0;
        
        loop
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
			
			if (enem_estado2 == 0)
				vel_horiz = 0;
				vel_vert = 0;
			else
				enem_mover_h = 0;
				temp2 = (x3 + vel_horiz) / (id_tscroll.tmapa[0].ancho_tile * resolution3);
				if (temp2 != enem_tilex)
				   //comprobamos si pasamos a otro tile lateral y cuan lejos esta
				   enem_mover_h = temp2 - enem_tilex;
				end
				
				enem_mover_v = 0;
				temp2 = (y3 + vel_vert) / (id_tscroll.tmapa[0].alto_tile * resolution3);
				if (temp2 != enem_tiley)
				   //comprobamos si pasamos a otro tile vertical y cuan lejos esta
				   enem_mover_v = temp2 - enem_tiley;
				end
				 //miramos en que direccion cambiamos
				enem_p_dir = 5;
				if (enem_mover_h > 0) enem_p_dir++; end
				if (enem_mover_h < 0) enem_p_dir--; end
				if (enem_mover_v > 0) enem_p_dir -= 3; end      //hacia abajo
				if (enem_mover_v < 0) enem_p_dir += 3; end      //hacia arriba
				enem_p_dir_ini = enem_p_dir;
				
				include "src/game/common/durezas_check.inc";
			
			end
            
            //zona de animaciones y cambio de estado
            switch (enem_estado2)
            case 0:
                if (cont_anim > 150) //&& veo_prota(x2, y2, 2, 100, 100))
                    enem_estado2 = 1;
                    cont_anim = 0;
                else
                    cont_anim++;
                end
            end
            case 1:
                if (cont_anim == 5)
                    pos_anim++;
                    graph = enem_anim[pos_anim];
                    if (pos_anim == 3)
                        enem_estado = 2;
                        enem_estado2 = 2;
                        vel_vert = -enem_salto;
                        if (exists(info_prota.id_prota))
                            if (info_prota.id_prota.x2 < x2)
                                vel_horiz = -10;
                            else
                                vel_horiz = 10;
                            end
                        end
                    end
                    cont_anim = 0;
                else
                    cont_anim++;
                end
            end
            case 2:
                if ((enem_estado != 2) && (enem_estado != 3))
                    vel_horiz = 0;
                    enem_estado2 = 3;
                end
            end
            case 3:
                vel_horiz = 0;
                if (cont_anim == 5)
                    pos_anim--;
                    graph = enem_anim[pos_anim];
                    if (pos_anim == 0)
                        enem_estado2 = 0;
                    end
                    cont_anim = 0;
                else
                    cont_anim++;
                end
            end
            end //switch
            
            //choque con las armas
            if (exists(info_prota.id_prota))
                if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                    temp2 = collision(type normal_shot);
                    while (temp2 != 0)
                        energia -= temp2.energia;
                        //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
                        //say("el disparo tenía energia: " + itoa(temp.energia));
                        temp2.energia = 0;
                        if ((mi_temblor != 0) && exists(mi_temblor))
                            mi_temblor.energia = 3;
                        else
                            mi_temblor = enem_temblor(id, 3);
                        end
                        temp2 = collision(type normal_shot);
                    end
                end
                
                if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                    temp2 = collision(type espadazo);
                    if ((temp2 != 0) && (temp2 != temp_espada))
                        energia -= temp2.energia;
                        if ((mi_temblor != 0) && exists(mi_temblor))
                            mi_temblor.energia = 3;
                        else
                            mi_temblor = enem_temblor(id, 3);
                        end
                        temp_espada = temp2;
                    end
                end
                //impacto con el prota
                if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                    if (collision(info_prota.id_prota))
                        info_prota.dano_id = id;
                        info_prota.dano_energia = 3;
                        info_prota.dano_exp = 4;
                        if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 26;
                        else info_prota.dano_vel_horiz = -26;
                        end
                    end
                end
            end
            
            if (energia <= 0) break; end
            
            x2 = x3 / resolution3;
            y2 = y3 / resolution3;
            tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
            frame;
        end
        
    end
    
    //explosion
    //shot_exp(x2, y2 - (id_tscroll.tmapa[0].ancho_tile / 2), 2, rand(-15, 15));
    random_item (2, x2, y2 - (id_tscroll.tmapa[0].ancho_tile / 2));
    enem_explos(x2, y2 - 7, 0, 0);
end