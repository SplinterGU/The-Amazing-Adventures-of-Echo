process invencible_enem (int enem_tx, int enem_ty, file)     //sigue un camino
private
    int x3, y3;
    int resolution3;
    int enem_estado2;
    
    int graph2;
    
    int vel_horiz, vel_vert;
    int cont_anim;
    int temp;
begin
    priority = -99;
    z = 1;
    //file = enem_grafs[0][cte_volador1];
    //Se busca el último gráfico
    graph2 = 1;
    while (((graph2 + 1) < 1000) && map_exists(file, graph2 + 1))
        graph2++;
    end
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
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
    end //switch
    
    //empieza
    loop
        enem_tx = (x3 / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        enem_ty = (y3 / resolution3) / id_tscroll.tmapa[0].alto_tile;
        
        temp = obtener_tile(&durezas, enem_tx, enem_ty, 0);
        switch (temp)
        case 251: enem_estado2 = 0; end       //movemos hacia arriba
        case 252: enem_estado2 = 1; end       //movemos hacia abajo
        case 253: enem_estado2 = 2; end       //movemos hacia izquierda
        case 254: enem_estado2 = 3; end       //movemos hacia derecha
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
        end //switch
        
        x3 += vel_horiz;
        y3 += vel_vert;
        
        //zona de gráficos
        cont_anim++;
        if (cont_anim >= 5)
            if (graph < graph2) graph++; else graph = 1; end
            cont_anim =0;
        end
        if (vel_horiz < 0) flags = 0; end
        if (vel_horiz > 0) flags = 1; end
        
        //*****************************
        // ZONA DE IMPACTOS
        //*****************************
        if (exists(info_prota.id_prota))
            //impacto con las balas
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                if (temp)
                    temp.energia = 0;
                end
            end
            
            
            //impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 3;
                    info_prota.dano_exp = 4;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 30;
                    else info_prota.dano_vel_horiz = -30;
                    end
                end
            end
        end
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
end