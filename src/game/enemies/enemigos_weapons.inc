//************************************************************************************
//  DISPAROS DE ENEMIGOS
//************************************************************************************
process enem_normal_shot (file, int graph1, int graph2, x2, y2, angle, energia);
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
    z = 1;
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    vel_x = 50 * cos(angle);
    vel_y = -50 * sin(angle);
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
        
        vel_x = shot_colision_lateral(shot_offsx, shot_offsy, shot_tile, vel_x, resolution3);
        vel_y = shot_colision_vertical(shot_offsx, shot_offsy, shot_tile, vel_y, resolution3);
        
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
                info_prota.dano_exp = energia;
                //say(itoa(angle));
                if (vel_x > 0) info_prota.dano_vel_horiz = 20;
                elsif (vel_x < 0) info_prota.dano_vel_horiz = -20;
                else
                    if (x2 > info_prota.id_prota.x2) info_prota.dano_vel_horiz = -20;
                    else info_prota.dano_vel_horiz = 20; end
                end
                energia = 0;
            end
        end
        
        if (energia == 0) break; end
        if (region_out(id, 0)) break; end
        frame;
    end
    
    //animacion explosion
    frame;
end

process enem_normal_shot2 (file, int graph1, int graph2, x2, y2, angle, int angle2, energia, int ens_velocidad);
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
    z = 1;
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
        
        vel_x = shot_colision_lateral(shot_offsx, shot_offsy, shot_tile, vel_x, resolution3);
        vel_y = shot_colision_vertical(shot_offsx, shot_offsy, shot_tile, vel_y, resolution3);
        
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
                info_prota.dano_exp = energia;
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
        if (region_out(id, 0)) break; end
        frame;
    end
    
    //animacion explosion
    frame;
end

process enem_short_power_shot (file, graph1, graph2, x2, y2, angle, energia, esps_dist)
private
    int x3, y3;
    int resolution3;
    int vel_x, vel_y;
    int esps_animation_data[1];
    int vel_shot;
    
    //variables temporales
    int cont;
    int shot_tile;
    int shot_tilex, shot_tiley;
    int shot_offsx, shot_offsy;
begin
    //say("CHOY UN MICHILLL");
    
    z = -255;
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    vel_shot = 40;
    vel_x = vel_shot * cos(angle);
    vel_y = -vel_shot * sin(angle);
    if (angle == 180000)
        angle = 0;
        flags = 1;
    end
    
    //calculamos cuanto alpha pierde en cada frame
    esps_dist = esps_dist / vel_shot;
    //say(itoa(esps_dist));
    esps_dist = alpha / esps_dist;
    //say(itoa(esps_dist));
    
    //graph = 501;
    esps_animation_data[0] = graph1;
    esps_animation_data[1] = graph2;
    graph = graph1;
    loop
        shot_tilex = ((x3 + vel_x) / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        shot_tiley = ((y3 + vel_y) / resolution3) / id_tscroll.tmapa[0].alto_tile;
        shot_offsx = ((x3 + vel_x) / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        shot_offsy = ((y3 + vel_y) / resolution3) % id_tscroll.tmapa[0].alto_tile;
        shot_tile = obtener_tile(&durezas, shot_tilex, shot_tiley, 0);
        
        vel_x = shot_colision_lateral(shot_offsx, shot_offsy, shot_tile, vel_x, resolution3);
        vel_y = shot_colision_vertical(shot_offsx, shot_offsy, shot_tile, vel_y, resolution3);
        
        x3 += vel_x;
        y3 += vel_y;
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        if (cont == 5)
            cont = 0;
            if (graph == esps_animation_data[1])
                graph = esps_animation_data[0];
            else
                graph++;
            end
        end
        cont++;
        
        alpha = clamp( alpha - esps_dist, 0, 255 );
        energia = alpha / 25;
        //say(itoa(esps_dist) + " " + itoa(alpha));
        
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = alpha / 25;
                info_prota.dano_exp = alpha / 25;
                if (vel_x > 0) info_prota.dano_vel_horiz = 60;
                elsif (vel_x < 0) info_prota.dano_vel_horiz = -60;
                else
                    if (x2 > info_prota.id_prota.x2) info_prota.dano_vel_horiz = -60;
                    else info_prota.dano_vel_horiz = 60; end
                end
            end
        end
        
        //say("michil frame");
        if (energia <= 0) break; end
        if (region_out(id, 0)) break; end
        frame;
    end
    
    //animacion explosion
    frame;
end

process enem_canon_shot (file,graph, x2, y2, flags, energia)
private
    int vel_x, vel_y;
    
    //variables temporales
    //int cont;
    int shot_tile;
    int shot_tilex, shot_tiley;
    int shot_offsx, shot_offsy;
begin
    z = 2;
    if (flags == 1)
        vel_x = -4;
    else
        vel_x = 4;
    end
    
    shot_tiley = (y2 + vel_y) / id_tscroll.tmapa[0].alto_tile;
    shot_offsy = (y2 + vel_y) % id_tscroll.tmapa[0].alto_tile;
    loop
        shot_tilex = (x2 + vel_x) / id_tscroll.tmapa[0].ancho_tile;
        shot_offsx = (x2 + vel_x) % id_tscroll.tmapa[0].ancho_tile;
        
        shot_tile = obtener_tile(&durezas, shot_tilex, shot_tiley, 0);
        
        vel_x = shot_colision_lateral(shot_offsx, shot_offsy, shot_tile, vel_x, 1);
        //vel_y = shot_colision_vertical(shot_offsx, shot_offsy, shot_tile, vel_y, 1);
        
        x2 += vel_x;
        y2 += vel_y;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = energia;
                info_prota.dano_exp = energia;
                //say(itoa(angle));
                if (vel_x > 0) info_prota.dano_vel_horiz = 30;
                else info_prota.dano_vel_horiz = -30;
                end
                //energia = 0;
            end
        end
        
        if (energia == 0) break; end
        //if (region_out(id, 0)) break; end
        frame;
    end
    
    //animacion explosion
    frame;
end