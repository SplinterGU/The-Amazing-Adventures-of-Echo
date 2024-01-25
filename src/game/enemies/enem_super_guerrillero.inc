process super_guerrillero (int enem_tx, int enem_ty, file, flags)
private
    byte enem_estado2;      //0: descansando (fumando)
                            //1: sorprendido (tras fumando)
                            //2: de guardia (no se mueve del sitio, pero te ve antes y ataca antes)
                            //3: andando derecha (patrullando)
                            //4: andando izquierda (patrullando)
                            //5: pausa andando (patrullando)
                            //6: persiguiendo (te ve y se lanza al ataque)
                            //7: en espera (como de guardia, pero si te ve, te persigue)
                            //8: saltando
    int x3, y3;
    int resolution3;
    
    int vel_horiz, vel_vert;
    int enem_gravedad;
    int enem_max_gravedad;
    int enem_salto;
    int enem_salto2;
	
	int var_enem_acelerac = 1;
    
    //int mi_temblor;
    
    int cont_estado;        //dice el tiempo que queda para cambiar de estado
    int cont_anim;          //cuenta el retardo entre frames
    int pos_anim;           //indica qué gráfico de animación de andar muestra
    byte enem_anim[3] = 1, 2, 1, 3;  //animación andar
    
    int temp;
    double temp_x1, temp_y1;
    int temp_angle;
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
	
	//"constantes" para la detección de durezas
	int VAR_ENEM_MAX_AVANZAR_DERECHA	= 11;
	int VAR_ENEM_MAX_AVANZAR_IZQUIERDA	= 4;
	int VAR_ENEM_ALTURA_TECHO			= 14;
	int VAR_ENEM_DIFERENCIA_CON_TECHO	= 2;
	
begin
    priority = -99;
    //file = enem_grafs[0][cte_s_guerrillero];
    z = 1;
    enem_gravedad = 2;
    enem_max_gravedad = 30;
    enem_salto = 30;
    enem_salto2 = 40;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    energia = 20;
    
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    temp = obtener_tile(&durezas, enem_tx, enem_ty, 0);
    
    //estableciendo comportamiento inicial
    switch (temp)
    case 253: enem_estado2 = 4; end
    case 254: enem_estado2 = 3; end
    default: enem_estado2 = 4; end
    end //switch
    
    loop
        //cambios de estado
        switch (enem_estado2)
        case 2:         //de guardia
            if (veo_prota(x2, y2, (flags & 1), 150, 70))
                enem_estado2 = 6;
                cont_estado = 0;
            end
        end
        case 3:         //andando derecha
            cont_estado++;
            vel_horiz++;
            if (vel_horiz > 10) vel_horiz = 10; end
            if (veo_prota(x2, y2, 1, 150, 70))
                enem_estado2 = 6;
                cont_estado = 0;
            end
        end
        case 4:         //andando izquierda
            cont_estado++;
            vel_horiz--;
            if (vel_horiz < -10) vel_horiz = -10; end
            if (veo_prota(x2, y2, 0, 150, 70))
                enem_estado2 = 6;
                cont_estado = 0;
            end
        end
        case 6:
            if (exists(info_prota.id_prota))
                //comprobamos distancia con el prota
                temp = info_prota.id_prota.x2 - x2;
                //muy cerca, puñetazo
                if ((abs(temp) < 40) || (cont_estado > 0))
                    cont_estado++;
                    //**********************
                else
                    //un poco más lejos saltamos, si no, nos acercamos
                    if (temp > 32) 
                        vel_horiz = 10;
                    elsif (temp < -32) 
                        vel_horiz = -10;
                    end
                    if ((abs(temp) < 60) && ((enem_estado == 0) || (enem_estado == 1)))
                        enem_estado2 = 8;
                        vel_vert = -enem_salto2;
                        enem_estado = 3;
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
                end
                
                if (cont_estado > 0)
                    if (vel_horiz > 0) vel_horiz--; end
                    if (vel_horiz < 0) vel_horiz++; end
                    if (cont_estado == 31) //dispara
                        //say("quiero disparar");
                        //DISPARAMOS
                        get_real_point(1, &temp_x1, &temp_y1);  //punto de salida
                        //buscamos desplazamiento en pixels
                        temp_x1 -= x;
                        temp_y1 -= y;
                        //creamos el disparo en coordenadas del scroll
                        if ((flags & 1) == 1)
							temp_angle = 0;
						else
							temp_angle = 180000;
						end
                        enem_short_power_shot(file, 150, 150, x2 + temp_x1, y2 + temp_y1, temp_angle, 10, 500);
                    end
                    if (cont_estado == 140) cont_estado = 0; end
                end
            end
        end
        case 7:
            if (veo_prota(x2, y2, (flags & 1), 300, 200))
                enem_estado2 = 6;
            end
        end
        case 8:
            if ((flags & 1) == 1) vel_horiz = 10; else vel_horiz = -10; end
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
        case 3:
            switch (enem_dur[1][1])
            case 253:
                enem_estado2 = 4;
                cont_estado = 0;
            end
            case 251:       //flecha hacia arriba (salta)
                if ((enem_estado == 1) || (enem_estado == 0))
                    vel_vert = -enem_salto;
                    enem_estado = 3;
                end
            end
            end //switch
        end
        case 4:
            switch (enem_dur[1][1])
            case 254:
                enem_estado2 = 3;
                cont_estado = 0;
            end
            case 251:       //flecha hacia arriba (salta)
                if ((enem_estado == 1) || (enem_estado == 0))
                    vel_vert = -enem_salto;
                    enem_estado = 3;
                end
            end
            end //switch
        end
        case 6:
			temp = info_prota.id_prota.x2 - x2;
            if (temp > 0) flags = 1; else flags = 0; end
            
            //si se para porque choca con una pared, comprueba si puede seguir con un salto
            if (vel_horiz == 0)
                if (vel_horiz_ant > 0)
                    switch (enem_dur[2][0])
                    case 1,2,5,14,51,52,55,64:
                        p_libre = 0;
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
                end
                if (vel_horiz_ant == 0) p_libre = 0; end
            
                // si se puede, pues salta
                if (p_libre && ((enem_estado == 1) || (enem_estado == 0)))
                    enem_estado = 8;
                    vel_vert = -enem_salto;
                    enem_estado = 3;
                end
            end
        end
        case 8:
            if ((enem_estado == 1) || (enem_estado == 0))
                enem_estado2 = 6;
                cont_estado = 0;
            end
        end
        end //switch
        
        
        //zona de gráficos
        switch (enem_estado2)
        case 2,7:               //de guardia y en espera
            graph = 1;
        end
        case 3,4:
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
                    if (pos_anim == 3) pos_anim = 0; else pos_anim++; end
                    graph = enem_anim[pos_anim];
                end
            end
            case 2,3: graph = 5; end
            end //switch
        end
        case 5,6:   //patrullando y persiguiendo
            switch (enem_estado)
            case 0:
                if (cont_estado == 0)
                    graph = 1;
                else
                    if (cont_estado < 30) graph = 6; else graph = 7; end
                end
            end
            case 1:
                if (vel_horiz > 0) flags = 1; end
                if (vel_horiz < 0) flags = 0; end
                cont_anim++;
                if (cont_anim == 10)
                    cont_anim = 0;
                    if (pos_anim == 3) pos_anim = 0; else pos_anim++; end
                    graph = enem_anim[pos_anim];
                end
            end
            case 2,3: graph = 5; end
            end //switch
        end
        case 8:
            graph = 5;
        end
        end //switch
        
        //*********************************
        //  ZONA DE COLISIONES
        //*********************************
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if ((abs(x - info_prota.id_prota.x) < 65) && (abs(y - info_prota.id_prota.y) < 65))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 4;
                    info_prota.dano_exp = 4;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 26;
                    else info_prota.dano_vel_horiz = -26;
                    end
                end
            end
            
            //impacto con las balas
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                while (temp)
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
        end
        if (energia <= 0) break; end
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    random_item (15, x2, y2 - (id_tscroll.tmapa[0].ancho_tile / 2));
    enem_explos(x2, y2 - 24, -1, -1);
    enem_explos(x2, y2 - 24, 1, -1);
    enem_explos(x2, y2 - 8, -1, 1);
    enem_explos(x2, y2 - 8, 1, 1);
end