process prota_moto (x2,y2)
private
    //posición
    int x3;             //temporal, añade resolución
    int y3;             //temporal, añade resolución
    
    int resolution3;    //define el tamaño de cada pixel (evitar decimales)
    //variables temporales
    int temp_desp;      //indica hasta donde se desplazará el personaje
    int p_libre;        //indica si se puede avanzar en esa dirección (comprobación de movimiento)
	int temp;
begin
    priority = -99;
    //write_var(0, 10, 10, 0, p_dur[0][0]);
    //write_var(0, 10, 20, 0, p_dur[0][1]);
    //write_var(0, 10, 30, 0, p_dur[0][2]);
    //write_var(0, 30, 10, 0, p_dur[1][0]);
    //write_var(0, 30, 20, 0, p_dur[1][1]);
    //write_var(0, 30, 30, 0, p_dur[1][2]);
    //write_var(0, 50, 10, 0, p_dur[2][0]);
    //write_var(0, 50, 20, 0, p_dur[2][1]);
    //write_var(0, 50, 30, 0, p_dur[2][2]);

    //write_var(0, 100, 10, 0, info_prota.vel_horiz);
    //write_var(0, 100, 20, 0, info_prota.vel_vert);
    //write_var(0, 100, 35, 0, p_dir);
    
    //write_var(0, 150, 10, 0, info_prota.p_offsx);
    //write_var(0, 150, 20, 0, info_prota.p_offsy);
    //write_var(0, 150, 35, 0, info_prota.estado);
    
    //write_var(0, 200, 10, 0, teclas[k_jump][2]);
    
    graph = 1;
    //z = -100;
    z = 1;
    
    //x3 = 100;
    //y3 = 1150;
    id_tscroll.camera_x = x2 * id_tscroll.tmapa[0].ancho_tile;
    id_tscroll.camera_y = y2 * id_tscroll.tmapa[0].alto_tile;
    
    info_prota.id_prota = id;
    resolution3 = 10;
    x3 = id_tscroll.camera_x * resolution3;
    y3 = id_tscroll.camera_y * resolution3;
    
    loop
        //esto es por si movemos al personaje externamente
        //x3 = x2;
        //y3 = y2;
        //say("frame");
        //localizamos la posición actual
        info_prota.p_tilex = (x3 / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        info_prota.p_tiley = (y3 / resolution3) / id_tscroll.tmapa[0].alto_tile;
        info_prota.p_offsx = (x3 / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        info_prota.p_offsy = (y3 / resolution3) % id_tscroll.tmapa[0].alto_tile;
        //leemos durezas de su alrededor
        p_dur[0][0] = obtener_tile(&durezas, info_prota.p_tilex - 1, info_prota.p_tiley - 1, 0);
        p_dur[1][0] = obtener_tile(&durezas, info_prota.p_tilex    , info_prota.p_tiley - 1, 0);
        p_dur[2][0] = obtener_tile(&durezas, info_prota.p_tilex + 1, info_prota.p_tiley - 1, 0);
        p_dur[0][1] = obtener_tile(&durezas, info_prota.p_tilex - 1, info_prota.p_tiley    , 0);
        p_dur[1][1] = obtener_tile(&durezas, info_prota.p_tilex    , info_prota.p_tiley    , 0);
        p_dur[2][1] = obtener_tile(&durezas, info_prota.p_tilex + 1, info_prota.p_tiley    , 0);
        p_dur[0][2] = obtener_tile(&durezas, info_prota.p_tilex - 1, info_prota.p_tiley + 1, 0);
        p_dur[1][2] = obtener_tile(&durezas, info_prota.p_tilex    , info_prota.p_tiley + 1, 0);
        p_dur[2][2] = obtener_tile(&durezas, info_prota.p_tilex + 1, info_prota.p_tiley + 1, 0);
        
        //reconocimiento de teclas
        //movimiento lateral
        if (teclas[k_right][2] > 0)
            info_prota.vel_horiz += CTE_MOTO_ACELERAC;
            if (info_prota.vel_horiz > CTE_MOTO_MAX_VEL) info_prota.vel_horiz = CTE_MOTO_MAX_VEL; end
            //info_prota.vel_horiz = info_prota.vel_horiz;
        elsif (teclas[k_left][2] > 0)
            info_prota.vel_horiz -= CTE_MOTO_ACELERAC;
            if (info_prota.vel_horiz < -CTE_MOTO_MAX_VEL) info_prota.vel_horiz = -CTE_MOTO_MAX_VEL; end
            //info_prota.vel_horiz = info_prota.vel_horiz;
        else
            if (info_prota.vel_horiz > 0)
                if (info_prota.vel_horiz < CTE_MOTO_ACELERAC)
                    info_prota.vel_horiz = 0;
                else
                    info_prota.vel_horiz -= CTE_MOTO_ACELERAC;
                end
            elsif (info_prota.vel_horiz < 0)
                if (info_prota.vel_horiz > -CTE_MOTO_ACELERAC)
                    info_prota.vel_horiz = 0;
                else
                    info_prota.vel_horiz += CTE_MOTO_ACELERAC;
                end
            end
        end
        //info_prota.vel_horiz = var_vel;
        //salto
        //test
        /*if (teclas[k_jump][2] == 1)
            say("Estado: " + itoa(info_prota.estado) + " Cont salto: " + itoa(cont_salto));
            graph++;
            if (graph > 4) graph = 1; end
        end*/
        //say(teclas[k_jump][2] == 1);
        
        switch (info_prota.estado)
        case 0,1:   //parado o andando
            if (teclas[k_jump][2] == 1)       //si apretamos salto
                info_prota.estado = 2;
                cont_salto = 0;
                info_prota.vel_vert = -CTE_MOTO_SALTO;        
            else                            //gravedad normal (quitar para debug)****************
                info_prota.estado = 3;
                info_prota.vel_vert += CTE_MOTO_GRAVEDAD;
            end
        end
        case 2:     //saltando
            if (teclas[k_jump][2] > 0)
                cont_salto++;
                if (cont_salto >= CTE_MOTO_MAX_SALTO)
                    info_prota.estado = 3;
                    info_prota.vel_vert += CTE_MOTO_GRAVEDAD;
                    cont_salto = 0;
                else
                    info_prota.vel_vert = -CTE_MOTO_SALTO;
                end
            else
                info_prota.estado = 3;
                info_prota.vel_vert += CTE_MOTO_GRAVEDAD;
            end
        end
        case 3:     //cayendo
            info_prota.vel_vert += CTE_MOTO_GRAVEDAD;
            if (info_prota.vel_vert > CTE_MOTO_MAX_GRAVEDAD) info_prota.vel_vert = CTE_MOTO_MAX_GRAVEDAD; end
            if (teclas[k_down][2] > 0) info_prota.vel_vert = 0; info_prota.estado = 0; end
        end
        end //switch
        
        //MOVIMIENTO ***********************************
        //Comprobamos cambio de tile
        /*p_dir = 5;
        temp_desp = (info_prota.p_offsx * resolution3) + var_vel;
        if (temp_desp > (id_tscroll.tmapa[0].ancho_tile * resolution3)) p_dir++; end
        if (temp_desp < 0) p_dir--; end
        temp_desp = (info_prota.p_offsy * resolution3) + info_prota.vel_vert;
        if (temp_desp > (id_tscroll.tmapa[0].alto_tile * resolution3)) p_dir -= 3; end
        if (temp_desp < 0) p_dir += 3; end*/
        //comprobamos si cambiamos de tile y en que direccion
        //***************************************************************
        info_prota.p_mover_h = 0;
		temp = (x3 + info_prota.vel_horiz) / (id_tscroll.tmapa[0].ancho_tile * resolution3);
        if (temp != info_prota.p_tilex)
           //comprobamos si pasamos a otro tile lateral y cuan lejos esta
           info_prota.p_mover_h = temp - info_prota.p_tilex;
        end
        //write(0, 630, 10, 2, p_mover_h);
        info_prota.p_mover_v = 0;
		temp = (y3 + info_prota.vel_vert) / (id_tscroll.tmapa[0].alto_tile * resolution3);
        if (temp != info_prota.p_tiley)
           //comprobamos si pasamos a otro tile vertical y cuan lejos esta
           info_prota.p_mover_v = temp - info_prota.p_tiley;
        end
         //miramos en que direccion cambiamos
        p_dir = 5;
        if (info_prota.p_mover_h > 0) p_dir++; end
        if (info_prota.p_mover_h < 0) p_dir--; end
        if (info_prota.p_mover_v > 0) p_dir -= 3; end      //hacia abajo
        if (info_prota.p_mover_v < 0) p_dir += 3; end      //hacia arriba
        p_dir_ini = p_dir;
        
        //OJO CON LA RAMPAS TRASPASABLES, PONER CASILLA A CERO SI ESTAMOS**********temporalmente disabled
        //EN EL SUELO
        /*if ((p_dur[1][1] == 27 || p_dur[1][1] == 77) &&
           (info_prota.p_rely > ((id_tscroll.tmapa[0].alto_tile - 1) * resolution3) - info_prota.p_relx))
           p_dur[1][1] = 0;
        end
        if ((p_dur[1][1] == 30 || p_dur[1][1] == 80) &&
           (info_prota.p_rely > ((id_tscroll.tmapa[0].alto_tile - 1) * resolution3) - (info_prota.p_relx / 2)))
           p_dur[1][1] = 0;
        end
        if ((p_dur[1][3] == 31 || p_dur[1][3] == 81) &&
           (info_prota.p_rely > (((id_tscroll.tmapa[0].alto_tile / 2) - 1) * resolution3) - (info_prota.p_relx / 2)))
           p_dur[1][1] = 0;
        end
        if ((p_dur[1][1] == 26 || p_dur[1][1] == 76) && info_prota.p_rely > info_prota.p_relx)
           p_dur[1][1] = 0;
        end
        if ((p_dur[1][1] == 28 || p_dur[1][1] == 78) &&
           ((info_prota.p_rely > ((id_tscroll.tmapa[0].alto_tile / 2) - 1) * resolution3) + info_prota.p_relx / 2))
           p_dur[1][1] = 0;
        end
        if ((p_dur[1][1] == 29 || p_dur[1][1] == 79) && info_prota.p_rely > info_prota.p_relx / 2)
           p_dur[1][1] = 0;
        end*/
        
        //Movimiento a la derecha
		
		include "src/game/prota/prota_moto_dur_check1.inc";

        //***************************************************************
        //***************************************************************
        
        //Movimiento a la izquierda
		
		include "src/game/prota/prota_moto_dur_check2.inc";
		
        //******************************************************
        //******************************************************
        
        //movimientos verticales
		include "src/game/prota/prota_moto_dur_check3.inc";
        
        //*********************************************************
        //  comprobación tile actual
        //*********************************************************
        
		include "src/game/prota/prota_moto_dur_check4.inc";
        
        
        //comprobamos choque contra el techo
        if (!p_libre)
            if (info_prota.vel_vert < 0) info_prota.vel_vert = 0; end
            if (info_prota.estado == 2) 
                cont_salto = CTE_MOTO_MAX_SALTO;
                info_prota.estado = 3;
            end
            info_prota.p_mover_v = 0;
        end
        
        //**********************************************
        //  Zona de daños
        //**********************************************
        if (info_prota.p_invencible > 0) info_prota.p_invencible--; end
        
        //**********************************************
        //  Zona de animaciones
        //**********************************************
        if (info_prota.vel_horiz < 0) flags = 1; end
        if (info_prota.vel_horiz > 0) flags = 0; end
        
        switch (p_dur[1][1])
        case 2:
            angle = -45000;
            if ((flags & 1) == 1) angle = -angle; end
        end
        case 3:
            angle = 45000;
            if ((flags & 1) == 1) angle = -angle; end
        end
        case 13,14:
            angle = -22500;
            if ((flags & 1) == 1) angle = -angle; end
        end
        case 15,16:
            angle = 22500;
            if ((flags & 1) == 1) angle = -angle; end
        end
        default:
            if ((info_prota.estado == 2) || (info_prota.estado == 3))
                angle = 22500;
            else
                angle = 0;
            end
        end
        end //switch
        
        file = prota_file;
        graph = 1;
        
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        //parpadeo de invencible: cambia cada 4 frames, y comprobamos si es par (se ve) o impar (no se ve)
        //debe ser aqui, pues el disparo depende del gráfico
        if ((info_prota.p_invencible & 4) == 4) graph = 0; end
        
        frame;
    end
end
