//**************************************************************************************************
//  LO QUE ACTIVAN LOS INTERRUPTORES
//**************************************************************************************************

process door (x3, y3, file, graph)
private
    int mi_activacion;
begin
    //say("puerta, grafico: " + itoa(graph));
    modificar_tile(&nivel, x3, y3, 0, 0);
    priority = -99;
    x2 = (x3 * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (y3 * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    
    mi_activacion = obtener_tile(&durezas, x3, y3, 0) - 150;
    //say("activacion: " + itoa(mi_activacion));
    modificar_tile(&durezas, x3, y3    , 0, 1);
    modificar_tile(&durezas, x3, y3 - 1, 0, 1);
    while (!interruptores[mi_activacion])
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    sound_play(sfx_id[0][cte_sfx_door], 0);
    //say("aqui no deberia estar");
    modificar_tile(&durezas, x3, y3    , 0, 0);
    modificar_tile(&durezas, x3, y3 - 1, 0, 0);
    modificar_tile(&nivel  , x3, y3    , 0, graph + 1);
    ts_actualiza_tiles(&id_tscroll);
end

process bridge (x3, y3, file, int graph2, int bridge_dir, int bridge_long, int bridge_on)
private
    int mi_activacion;
    int x2_ini;
    int vel_horiz;
    
    int cont1;
    int cont2;
begin
    z = 1;
    modificar_tile(&nivel, x3, y3, 0, 0);
    ts_actualiza_tiles(&id_tscroll);
    priority = -99;
    mi_activacion = obtener_tile(&durezas, x3, y3, 0) - 150;
    
    //say ("dureza: " + itoa(obtener_tile(&durezas, x3, y3 - 1, 0)));
    
    if (bridge_dir == 2)
        if (obtener_tile(&durezas, x3 - 1, y3, 0) == 1)
            bridge_dir = 0;
        else
            bridge_dir = 1;
        end
    end
    
    x2 = (x3 * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (y3 * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    switch (bridge_dir)
    case 0:
        x2 -= id_tscroll.tmapa[0].ancho_tile;
        vel_horiz = 1;
    end
    case 1:
        x2 += id_tscroll.tmapa[0].ancho_tile;
        vel_horiz = -1;
    end
    end //switch
    x2_ini = x2;
    
    while (!interruptores[mi_activacion] && !bridge_on)
        frame;
    end
    
    if (!bridge_on) sound_play(sfx_id[0][cte_sfx_bridge], bridge_long); end
    
    graph = graph2;
    for (cont1 = bridge_long; cont1 > 0; cont1--)     //repetimos tantas veces como longitud
        x2 = x2_ini;
        for (cont2 = 0; cont2 < id_tscroll.tmapa[0].ancho_tile; cont2++)  //movemos 16 veces
            x2 += vel_horiz;
            tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
            frame;
        end
        //tras mover, modificamos el mapa de durezas
        modificar_tile(&durezas, x3, y3, 0, 25);
        //y creamos otro trozo del puente
        if ((bridge_long > 1) && (cont1 == bridge_long))
            bridge (x3 + vel_horiz, y3, file, graph, bridge_dir, bridge_long - 1, 1);
        end
    end
    
    //y por último, cambiamos el gráfico en el mapa visible
    modificar_tile(&nivel, x3, y3, 0, graph);
    ts_actualiza_tiles(&id_tscroll);
end

//**************************************************************************************************
//  INTERRUPTORES
//**************************************************************************************************

process button (x3, y3, file, graph)
private
    int button_activate;
    int temp;
begin
    modificar_tile(&nivel, x3, y3, 0, 0);
    priority = -99;
    x2 = (x3 * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (y3 * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    
    button_activate = obtener_tile(&durezas, x3, y3, 0) - 150;
    
    loop
        temp = collision(type normal_shot);
        if (temp != 0)
            if (temp.graph != 527)
                temp.energia = 0;
                break;
            end
        end
        
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    modificar_tile(&nivel, x3, y3, 0, 101);
    ts_actualiza_tiles(&id_tscroll);
    interruptores[button_activate] = 1;
end