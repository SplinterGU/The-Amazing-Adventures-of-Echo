process corvo (int enem_tx, int enem_ty, file, energia)     //sigue un camino y persigue al prota
private
    int x3, y3;
    int resolution3;
    int enem_estado2;           //0: mover hacia arriba
                                //1: mover hacia abajo
                                //2: mover hacia izquierda
                                //3: mover hacia derecha
                                //4: acercarse a prota
                                //5: atacando a prota
                                //6: vigilando
    
    int vel_horiz, vel_vert;
	int enem_gravedad;
    int cont_anim;
    int cont_estado;
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
    //file = enem_grafs[cte_volador1];
    z = 1;
    
    x2 =(enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 =(enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    //energia = 20;
    
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    temp = obtener_tile(&durezas, enem_tx, enem_ty, 0);
    
    //estableciendo comportamiento inicial
    switch (temp)
    case 251: enem_estado2 = 0; end       //movemos hacia arriba
    case 252: enem_estado2 = 1; end       //movemos hacia abajo
    case 253: enem_estado2 = 2; end       //movemos hacia izquierda
    case 254: enem_estado2 = 3; end       //movemos hacia derecha
    default:  enem_estado2 = 6; graph = 7; end       //esperamos a que se acerque el prota
    end //switch
    
    //empieza
    loop
        enem_tx = (x3 / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        enem_ty = (y3 / resolution3) / id_tscroll.tmapa[0].alto_tile;
        
        switch (enem_estado2)
        case 0,1,2,3:	//Siguiendo ruta
            temp = obtener_tile(&durezas, enem_tx, enem_ty, 0);
            switch (temp)
            case 251: enem_estado2 = 0; end       //movemos hacia arriba
            case 252: enem_estado2 = 1; end       //movemos hacia abajo
            case 253: enem_estado2 = 2; end       //movemos hacia izquierda
            case 254: enem_estado2 = 3; end       //movemos hacia derecha
            end //switch
            //say("veo prota 2: " + itoa(veo_prota2(x3, y3, -100, -100, 100, 100)));
            if (veo_prota2(x2, y2, -50, -50, 50, 80))
                enem_estado2 = 4;
                cont_anim = 0;
            end
        end
        case 4:	//Acercándose a prota
            if (veo_prota2(x2, y2 + 64, -10, 0, 10, 100))
                enem_estado2 = 5;
                cont_anim = 0;
                cont_estado = 0;
            end
        end
        case 6:	//Vigilando
            if (exists(info_prota.id_prota))
                if (veo_prota2(x2, y2, -64, -50, 64, 50))
                    enem_estado2 = 4;
                    cont_anim = 0;
                end
            end
        end
        end //switch
        
        //establecemos velocidades
        switch (enem_estado2)
        case 0:
            if (vel_horiz < 0) vel_horiz++; end
            if (vel_horiz > 0) vel_horiz--; end
            if (vel_vert > -7) vel_vert--; end
        end
        case 1:
            if (vel_horiz < 0) vel_horiz++; end
            if (vel_horiz > 0) vel_horiz--; end
            if (vel_vert < 7) vel_vert++; end
        end
        case 2:
            if (vel_vert < 0) vel_vert++; end
            if (vel_vert > 0) vel_vert--; end
            if (vel_horiz > -7) vel_horiz--; end
        end
        case 3:
            if (vel_vert < 0) vel_vert++; end
            if (vel_vert > 0) vel_vert--; end
            if (vel_horiz < 7) vel_horiz++; end
        end
        case 4:
            if (exists(info_prota.id_prota))
                if (info_prota.id_prota.x2 > x2)
                    if (vel_horiz < 10) vel_horiz++; end
                else
                    if (vel_horiz > -10) vel_horiz--; end
                end
                if ((info_prota.id_prota.y2 - 64) < y2)
                    if (vel_vert > -10) vel_vert--; end
                else
                    if (vel_vert < 10) vel_vert++; end
                end
            else
                if (vel_horiz < 0) vel_horiz++; end
                if (vel_horiz > 0) vel_horiz--; end
                if (vel_vert < 0) vel_vert++; end
                if (vel_vert > 0) vel_vert--; end
            end
        end
        case 5:
            if (cont_estado < 50)
                cont_estado++;
                vel_horiz = 0;
                vel_vert = 0;
            else
                vel_vert = 15;
                if (exists(info_prota.id_prota))
                    if (info_prota.id_prota.x2 > x2)
                        if (vel_horiz < 10) vel_horiz++; end
                    else
                        if (vel_horiz > -10) vel_horiz--; end
                    end
                else
                    vel_horiz = 0;
                end
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
        if (enem_mover_v > 0) enem_p_dir-=3; end      //hacia abajo
        if (enem_mover_v < 0) enem_p_dir+=3; end      //hacia arriba
        enem_p_dir_ini = enem_p_dir;
        
        include "src/game/common/durezas_check.inc";
        
        
        //zona de gráficos
        switch (enem_estado2)
        case 0,1,2,3:
            cont_anim++;
            switch (cont_anim)
            case 10: graph = 2; end
            case 20:
                graph = 1;
                cont_anim = 0;
            end
            end //switch
            if (vel_horiz < 0) flags = 0; end
            if (vel_horiz > 0) flags = 1; end
        end
        case 4:
            cont_anim++;
            switch (cont_anim)
            case 5: graph = 2; end
            case 10:
                graph = 1;
                cont_anim = 0;
            end
            end //switch
            if (vel_horiz < 0) flags = 0; end
            if (vel_horiz > 0) flags = 1; end
        end
        case 5:
            if (cont_estado < 50)
                graph = 1;
                cont_estado++;
            else
                flags = 0;
                cont_anim++;
                switch (cont_anim)
                case 3: graph = 4; end
                case 6: graph = 5; end
                case 9: graph = 6; end
                case 12:
                    graph = 3;
                    cont_anim = 0;
                end
                end //switch
                
                if (vel_vert == 0)
                    cont_anim = 0;
                    cont_estado = 0;
                    enem_estado2 = 4;
                end
            end
        end
        case 6:
            if (exists(info_prota.id_prota))
                if (info_prota.id_prota.x2 < x2) flags = 0; else flags = 1; end
            end
            //graph = 7;
        end
        end //switch
        
        //**************************************
        //  ZONA DE IMPACTOS
        //**************************************
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
                    if (enem_estado2 == 5)
                        info_prota.dano_energia = 4;
                        info_prota.dano_exp = 3;
                    else
                        info_prota.dano_energia = 2;
                        info_prota.dano_exp = 2;
                    end
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                    else info_prota.dano_vel_horiz = -20;
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
    enem_explos(x2, y2, 0, 0);
end