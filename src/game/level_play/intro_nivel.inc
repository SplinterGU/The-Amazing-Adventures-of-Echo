//*****************************************************
//  INTRO NIVEL
//*****************************************************
process in_graf_mov (file, graph, x, y, z, alpha)
begin
    while (x < 140)
        x += 10;
        frame;
    end
    signal(id, s_freeze);
    frame;
    while (!region_out(id, 0))
        x += 10;
        frame;
    end
end

process in_graf (file, graph, x, y, z, alpha, region)
begin
    signal(id, s_freeze);
    frame;
end

process intro_nivel (n)
private
    int hijos[6];
    int cont1, cont2;
begin
    if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_sleep_tree); end
    signal_items(s_sleep);
    signal_enemigos(s_sleep);
    signal_event_all(s_sleep);
    signal_sync(s_sleep);
    signal_tiles_especiales(s_sleep);
    
    enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/chlevel.fpg");
    enem_grafs[1][cte_event] = 1;
    
    fade_on(0);
    graph = map_new(320, 240);
    map_clear(file, graph, rgb(0,0,0));
    x = 160;
    y = 120;
    z = -110;
    frame(5000);
    //say("primer hijo");
    hijos[0] = in_graf_mov(enem_grafs[0][cte_event], 10, -60, 86, -111, 255);
    frame(800);
    hijos[1] = in_graf_mov(enem_grafs[0][cte_event], 10, -60, 86, -111, 200);
    frame(800);
    hijos[2] = in_graf_mov(enem_grafs[0][cte_event], 10, -60, 86, -111, 150);
    frame(800);
    hijos[3] = in_graf_mov(enem_grafs[0][cte_event], 10, -60, 86, -111, 100);
    frame(800);
    hijos[4] = in_graf(enem_grafs[0][cte_event], 10 + n, 230, 80, -111, 255, 0);
    hijos[5] = in_graf(enem_grafs[0][cte_event], 10 + n, 230, 80, -111, 0, 0);
    for (hijos[5].alpha = 155; hijos[5].alpha > 0; hijos[5].alpha = clamp( hijos[5].alpha - 2, 0, 255 ) )
        hijos[5].size = 255 - hijos[5].alpha;
        frame;
    end
    signal(hijos[5], s_kill);
    
    switch (n)
    case 1:
        hijos[6] = in_graf(enem_grafs[0][cte_event], n, 160, 150, -111, 0, 0);
        for (hijos[6].alpha = 0; hijos[6].alpha < 255; hijos[6].alpha += 1)
			frame;
		end
        hijos[6].alpha = 255;
        frame;
    end
    case 2:
        region_define(2, 25, 141, 1, 19);
        hijos[6] = in_graf(enem_grafs[0][cte_event], 3, 160, 150, -111, 255, 2);
        frame;
        for(cont1 = 0; cont1 <= 19; cont1++)
            switch(cont1)
            case 0:  region_define(2, 25, 141, 12, 19); end
            case 1:  region_define(2, 25, 141, 32, 19); end
            case 2:  region_define(2, 25, 141, 44, 19); end
            case 3:  region_define(2, 25, 141, 56, 19); end
            case 4:  region_define(2, 25, 141, 64, 19); end
            case 5:  region_define(2, 25, 141, 70, 19); end
            case 6:  region_define(2, 25, 141, 87, 19); end
            case 7:  region_define(2, 25, 141, 104, 19); end
            case 8:  region_define(2, 25, 141, 111, 19); end
            case 9:  region_define(2, 25, 141, 127, 19); end
            case 10: region_define(2, 25, 141, 144, 19); end
            case 11: region_define(2, 25, 141, 150, 19); end
            case 12: region_define(2, 25, 141, 158, 19); end
            case 13: region_define(2, 25, 141, 175, 19); end
            case 14: region_define(2, 25, 141, 195, 19); end
            case 15: region_define(2, 25, 141, 212, 19); end
            case 16: region_define(2, 25, 141, 229, 19); end
            case 17: region_define(2, 25, 141, 237, 19); end
            case 18: region_define(2, 25, 141, 253, 19); end
            case 19: region_define(2, 25, 141, 270, 19); end
            end //switch
            frame(1200);
        end
        hijos[6].region=0;
        region_define(2, 0, 0, 1, 1);
    end
    case 3:
        hijos[6] = in_graf(enem_grafs[0][cte_event], 4, 160, 150, -111, 0, 0);
        for (hijos[6].alpha = 0; hijos[6].alpha < 255; hijos[6].alpha += 1)
			frame;
		end
        hijos[6].alpha = 255;
        frame;
    end
    end //switch
    
    frame(15000);
    cont1 = 0;
    cont2 = 1;
    signal(hijos[0], s_wakeup);
    for (hijos[4].alpha = 255; hijos[4].alpha > 0; hijos[4].alpha = clamp( hijos[4].alpha - 2, 0, 255 ) )
        hijos[4].size++;
        hijos[6].x -= 10;
        cont1++;
        if ((cont1 == 8) && (cont2 <= 3))
            cont1 = 0;
            signal(hijos[cont2], s_wakeup);
            cont2++;
        end
        frame;
    end
    while (cont2 <= 3)
        hijos[6].x -= 10;
        cont1++;
        if (cont1 == 8)
            cont1 = 0;
            signal(hijos[cont2],s_wakeup);
            cont2++;
        end
        frame;
    end
    while (exists(hijos[3]))
        hijos[6].x -= 10;
        frame;
    end
    
    for (cont1 = 0; cont1 <= 6; cont1++)
        if (exists(hijos[cont1])) signal(hijos[cont1], s_kill); end
    end
    
    //finalizando
    if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_wakeup_tree); end
    signal_items(s_wakeup);
    signal_enemigos(s_wakeup);
    signal_event_all(s_wakeup);
    signal_sync(s_wakeup);
    signal_tiles_especiales(s_wakeup);
    
    signal(father, s_wakeup);
    while (x < 480)
        x += 10;
        frame;
    end
    
    fpg_unload(enem_grafs[0][cte_event]);
    enem_grafs[1][cte_event] = 0;
    //fade(0,0,0,255);
    map_unload(file, graph);
    
end