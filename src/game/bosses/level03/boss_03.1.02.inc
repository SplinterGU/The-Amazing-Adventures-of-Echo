process bblom_shot (file, int graph1, int graph2, x2, y2, angle, int angle2, energia, int ens_velocidad);
private
    int x3, y3;
    int resolution3;
    int vel_x, vel_y;
    int ens_animation_data[1];
    
    //variables temporales
    int cont;
    int shot_tile;
    int shot_tilex, shot_tiley;
    int shot_offsx, shot_offsy;
begin
    z = father.z - 1;
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    vel_x = ens_velocidad * cos(angle2);
    vel_y = -ens_velocidad * sin(angle2);
    if (angle == 180000)
        angle = 0;
        flags = 1;
    end
    
    //graph = 501;
    ens_animation_data[0] = graph1;
    ens_animation_data[1] = graph2;
    graph = graph1;
    loop
        shot_tilex = ((x3 + vel_x) / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        shot_tiley = ((y3 + vel_y) / resolution3) / id_tscroll.tmapa[0].alto_tile;
        shot_offsx = ((x3 + vel_x) / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        shot_offsy = ((y3 + vel_y) / resolution3) % id_tscroll.tmapa[0].alto_tile;
        shot_tile = obtener_tile(&durezas, shot_tilex, shot_tiley, 0);
        
        vel_x = shot_colision_lateral(shot_offsx , shot_offsy , shot_tile , vel_x , resolution3);
        vel_y = shot_colision_vertical(shot_offsx , shot_offsy , shot_tile , vel_y , resolution3);
        
        x3 += vel_x;
        y3 += vel_y;
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        if (cont == 5)
            cont = 0;
            if (graph == ens_animation_data[1])
                graph = ens_animation_data[0];
            else
                graph++;
            end
        end
        cont++;
        
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = energia;
                info_prota.dano_exp = energia * 2;
                //say(itoa(angle));
                if (vel_x > 0) info_prota.dano_vel_horiz = 20;
                elsif (vel_x < 0) info_prota.dano_vel_horiz = -20;
                else
                    if (x2 > info_prota.id_prota.x2) info_prota.dano_vel_horiz = -20;
                    else info_prota.dano_vel_horiz = 20; end
                end
            end
        end
        
        if (energia == 0) break; end
        //if (region_out(id,0)) break; end
        if ((x < -16) || (x > 336) || (y < -64) || (y > 256)) break; end
        
        frame;
    end
    
    //animacion explosion
    frame;
end

process blom (file, graph, x2, y2, energia, int max_y3, int min_y3, int vel_horiz, int blom_impulso,
				int max_gravedad, int aceleracion, int blomdano, int id_padre)
private
    int x3, y3;
    int resolution3;
    
    int vel_vert;
    //int bblom_gravedad;
    
    int enem_estado;            //0: cayendo
                                //1: deformando abajo
                                //2: deformando arriba
    
    int temp;
    int temp_espada;
begin
    z = -2;
    resolution3 = 100;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    
    id_padre.energia += energia;
    
    //vel_horiz = 150;
    loop
        switch (enem_estado)
        case 0:
            vel_vert += aceleracion;
            if (vel_vert > max_gravedad) vel_vert = max_gravedad; end
            y3 += vel_vert;
            if (y3 > 30300)
                y3 = 30300;
                enem_estado = 2;
            end
            
            if ((x3 > max_y3) || (x3 < min_y3)) vel_horiz = -vel_horiz; end
            x3 += vel_horiz;
        end
        case 2:
            vel_vert = -blom_impulso;
            enem_estado = 0;
        end
        end //switch
        
        //************************
        //  ZONA DE COLISIONES
        //************************
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = blomdano;
                info_prota.dano_exp = blomdano + 1;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        
            //impacto con las balas
            temp = collision(type normal_shot);
            while (temp != 0)
                energia -= temp.energia;
                id_padre.energia -= temp.energia;
                temp.energia = 0;
                if ((mi_temblor != 0) && exists(mi_temblor))
                    mi_temblor.energia = 3;
                else
                    mi_temblor = enem_temblor(id, 3);
                end
                temp = collision(type normal_shot);
            end
                        
            temp = collision(type espadazo);
            if ((temp != 0) && (temp != temp_espada))
                energia -= temp.energia;
                id_padre.energia -= temp.energia;
                if ((mi_temblor != 0) && exists(mi_temblor))
                    mi_temblor.energia = 3;
                else
                    mi_temblor = enem_temblor(id, 3);
                end
                temp_espada = temp;
            end
        end
        
        if (energia <= 0) break; end
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    switch (graph)
    case 3:
        blom (file, 4, x2, y2, 32, max_y3 + 1200, min_y3 - 1200, 110, 180, 300, 3, 4, id_padre);
        blom (file, 4, x2, y2, 32, max_y3 + 1200, min_y3 - 1200, -110, 180, 300, 3, 4, id_padre);
    end
    case 4:
        blom (file, 5, x2, y2, 16, max_y3 + 600, min_y3 - 600, 90, 210, 300, 4, 3, id_padre);
        blom (file, 5, x2, y2, 16, max_y3 + 600, min_y3 - 600, -90, 210, 300, 4, 3, id_padre);
    end
    case 5:
        blom (file, 6, x2, y2, 8, max_y3 + 300, min_y3 - 300, 90, 280, 300, 5, 2, id_padre);
        blom (file, 6, x2, y2, 8, max_y3 + 300, min_y3 - 300, -90, 280, 300, 5, 2, id_padre);
    end
    end //switch
end


process big_blom ()
private
    int x3, y3;
    int resolution3;
    
    int vel_horiz, vel_vert;
    //int bblom_gravedad;
    
    int enem_estado;            //0: cayendo
                                //1: deformando abajo
                                //2: deformando arriba
    int cont_estado;
    int bblom_ataque;
    int temp_angle;
    
    int temp;       //colisiones
    int temp_espada;
    
    int temp_wav, temp_canal;
begin
    file = enem_grafs[0][cte_event];
    graph = 1;
    x2 = 14180;
    y2 = 0;
    z = -2;
    
    while(y2 < 224)
        y2++;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    energia = 1000;
    enem_ener_interface(id);
    frame(10000);
    
    resolution3 = 100;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    
    //vel_horiz = 100;
    cont_estado = 300;
    
    loop
        switch (enem_estado)
        case 0:
            vel_vert += 1;
            if (vel_vert > 200) vel_vert = 200; end
            y3 += vel_vert;
            if (y3 > 30300)
                y3 = 30300;
                enem_estado = 1;
            end
            
            if ((x3 > 1422300) || (x3 < 1400100)) vel_horiz = -vel_horiz; end
            x3 += vel_horiz;
        end
        case 1:
            if (size_x < 125)
                size_x++;
                size_y--;
            else
                enem_estado = 2;
            end
        end
        case 2:
            if (size_x > 100)
                size_x--;
                size_y++;
            else
                vel_horiz = rand(-150, 150);
                vel_vert = -150;
                enem_estado = 0;
            end
        end
        end //switch
        
        //ataques
        cont_estado--;
        if (cont_estado <= 0)
            switch (bblom_ataque)
            case 0:
                bblom_ataque = rand(0, 9);
                switch(bblom_ataque)
                case 0..5: bblom_ataque = 1; end
                case 6,7: bblom_ataque = 2; end
                case 8,9: bblom_ataque = 3; end
                end //switch
                //bblom_ataque = 3;
            end
            case 1:
                temp_angle = fget_angle(x2, y2 - 96, info_prota.id_prota.x2, info_prota.id_prota.y2);
                bblom_shot (file, 8, 8, x2, y2 - 96, 0, temp_angle, 3, 45);
                bblom_shot (file, 8, 8, x2, y2 - 96, 0, temp_angle + 20000, 3, 45);
                bblom_shot (file, 8, 8, x2, y2 - 96, 0, temp_angle - 20000, 3, 45);
                bblom_shot (file, 8, 8, x2, y2 - 96, 0, temp_angle + 40000, 3, 45);
                bblom_shot (file, 8, 8, x2, y2 - 96, 0, temp_angle - 40000, 3, 45);
                bblom_ataque = 0;
                cont_estado = rand(2, 4 + (energia / 500)) * 50;
            end
            case 2:
                //if (y3 == 30300)
                    super_guerrillero(x2 / 16, y2 / 16, enem_grafs[0][cte_s_flerrus], 0);
                    energia -= 25;
                    bblom_ataque = 0;
                    //cont_estado = 200;
                    cont_estado = rand(2, 4 + (energia / 500)) * 50;
                //end
            end
            case 3:
                //if (y3 == 30300)
                    if (exists(info_prota.id_prota))
                        if (info_prota.id_prota.x < x)
							cont_estado = 0;
						else
							cont_estado = 1;
						end
                    else
                        cont_estado = rand(0, 1);
                    end
                    guerrillero(x2 / 16, y2 / 16, enem_grafs[0][cte_flerris], cont_estado);
                    energia -= 7;
                    bblom_ataque = 0;
                    //cont_estado = 200;
                    cont_estado = rand(2, 4 + (energia / 500)) * 50;
                //end
            end
            end //switch
        end
        
        //************************
        //  ZONA DE COLISIONES
        //************************
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 6;
                info_prota.dano_exp = 20;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        
            //impacto con las balas
            temp = collision(type normal_shot);
            while (temp != 0)
                energia -= temp.energia;
                temp.energia = 0;
                if ((mi_temblor != 0) && exists(mi_temblor))
                    mi_temblor.energia = 3;
                else
                    mi_temblor = enem_temblor(id, 3);
                end
                temp = collision(type normal_shot);
            end
                        
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
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    fade(255, 255, 255, 255, 100);
    frame(300);
    graph = 2;
    size_x = 100;
    size_y = 100;
    fade_on(100);
    frame(5000);
    for (cont_estado = 0; cont_estado < 250; cont_estado++)
        if ((mi_temblor != 0) && exists(mi_temblor))
            mi_temblor.energia = cont_estado / 50;
        else
            mi_temblor = enem_temblor(id, cont_estado / 50);
        end
        frame;
    end
    
    //cambio de tercio ********************************************************************************
    father.graph = 7;
    temp_wav = sound_load(dreamcast_ruta + "sfx/alarma.wav");
    temp_canal = sound_play(temp_wav, 1);
    for (cont_estado = 0; cont_estado < 6; cont_estado++)
        fade(255, 0, 0, 255, 300); // jjp
        while (fade_info.fading) frame; end
        fade_on(300);
        while (fade_info.fading) frame; end
    end
    if (sound_is_playing(temp_canal)) sound_stop(temp_canal); end
    sound_unload(temp_wav);
    father.graph = 0;
    
    //SUPER PANG
    vel_horiz = 150;
    enem_estado = 2;
    energia = 128;
    loop
        switch (enem_estado)
        case 0:
            vel_vert += 1;
            if (vel_vert > 200) vel_vert = 200; end
            y3 += vel_vert;
            if (y3 > 30300)
                y3 = 30300;
                enem_estado = 2;
            end
            
            if ((x3 > 1422300) || (x3 < 1400100)) vel_horiz = -vel_horiz; end
            x3 += vel_horiz;
        end
        case 2:
            vel_vert = -150;
            enem_estado = 0;
        end
        end //switch
        
        //************************
        //  ZONA DE COLISIONES
        //************************
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 6;
                info_prota.dano_exp = 10;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        
            //impacto con las balas
            temp = collision(type normal_shot);
            while (temp != 0)
                energia -= temp.energia;
                temp.energia = 0;
                if ((mi_temblor != 0) && exists(mi_temblor))
                    mi_temblor.energia = 3;
                else
                    mi_temblor = enem_temblor(id, 3);
                end
                temp = collision(type normal_shot);
            end
                        
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
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    graph = 0;
    
    blom (file, 3, x2, y2, 64, 1422300 + 2400, 1400100 - 2400, 130, 160, 230, 2, 5, id);
    blom (file, 3, x2, y2, 64, 1422300 + 2400, 1400100 - 2400, -130, 160, 230, 2, 5, id);
    
    while (get_id(type blom)) frame; end
    
    fade(255, 255, 255, 255, 100);
    frame(300);
    fade_on(100);
    
    frame(20000);
    //loop frame; end
end