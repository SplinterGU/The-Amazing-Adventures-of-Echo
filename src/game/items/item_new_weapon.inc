process new_weapon_img2 (file,graph,x,y,z)
begin
    while (alpha>0)
        alpha=clamp( alpha - 10, 0, 255 );
        size+=2;
        frame;
    end
end



process new_weapon (x3, y3, energia)
private
    int nw_hijos[4];
    savegame_item_got nw_item;
    
    int nw_echox, nw_echoy;
    int temp;
    int temp_weap;
    //int temp_flags;
begin
    priority = -99;
    file = item_grafs;
    
    switch (energia)
    case 0: graph = 21; end
    case 1: graph = 22; end
    case 2: graph = 23; end
    end //switch
    
    modificar_tile(&nivel, x3, y3, 0, 0);
    x2 = (x3 * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (y3 * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    
	nw_hijos[0] = 0;
    loop
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        if (exists(info_prota.id_prota))
            //if ( (collision(info_prota.id_prota)) && (teclas[k_down][2]==1) )
            if ( (abs(info_prota.id_prota.x - x) < 6) && (abs(info_prota.id_prota.y - y) < 10) )
				if ((nw_hijos[0] == 0) || (!exists(nw_hijos[0])))
					nw_hijos[0] = item_press_down (x2, y2 - 16);
				end
				
				if (teclas[k_down][2]==1) break; end
			else
				if ((nw_hijos[0] != 0) && (exists(nw_hijos[0])))
					signal(nw_hijos[0], s_kill);
					nw_hijos[0] = 0;
				end
            end
        end
        frame;
    end
	
	if ((nw_hijos[0] != 0) && (exists(nw_hijos[0])))
		signal(nw_hijos[0], s_kill);
		nw_hijos[0] = 0;
	end
    
    //añadimos a lista de items conseguidos
    nw_item.level = next_level;
    nw_item.sublevel = next_sublevel;
    nw_item.pos_x = x3;
    nw_item.pos_y = y3;
    nw_item.item = 226 + energia;
    savegame_item_got_list_add(nw_item);
    
    temp_weap = graph;
    //pausamos todo
    prota_control = 0;
	pausa_estado = 0;
    signal(info_prota.id_prota, s_freeze_tree);
    signal(get_id(type arma), s_sleep);
    signal_moving_items(s_freeze);
    signal_enemigos(s_freeze);
    signal_sync(s_freeze);
    signal_tiles_especiales(s_freeze);
    //oscurecemos pantalla
    alpha = 0;
    file = 0;
    graph = map_new(320, 240);
    map_clear(file, graph, rgb(0,0,0));
    center_set(file, graph, 0, 0);
    x = 0;
    y = 0;
    z = -10;
    info_prota.id_prota.z = -11;
    
    //music_fade_off(2500);
    level_song = _CTE_MUSIC_NOMUSIC;
    for (alpha = 0; alpha < 150; alpha++)
        frame;
    end
    
    //music_unload(level_song);
    //temp_flags=info_prota.id_prota.flags;
    info_prota.id_prota.graph = 30;
    info_prota.id_prota.flags = 0;
    info_prota.id_prota.z = 1;
    
    //fanfarria
    //play_level_music(100);
    level_song = _CTE_MUSIC_WEAPONGET;
    enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/wget.fpg");
    enem_grafs[1][cte_event] = 1;
    nw_hijos[0] = items_image(enem_grafs[0][cte_event], 1, info_prota.id_prota.x, info_prota.id_prota.y - 8, -15,
								25, 0);
	signal(info_prota.id_prota, s_sleep_tree);
    while ((nw_hijos[0].x != 150) || (nw_hijos[0].y != 75))
        if (nw_hijos[0].x < 150) nw_hijos[0].x++; end
        if (nw_hijos[0].x > 150) nw_hijos[0].x--; end
        if (nw_hijos[0].y < 75) nw_hijos[0].y++; end
        if (nw_hijos[0].y > 75) nw_hijos[0].y--; end
        if (nw_hijos[0].size < 100) nw_hijos[0].size++; end
        frame;
    end
    while (nw_hijos[0].size < 100)
        nw_hijos[0].size++;
        frame;
    end
    
    nw_hijos[1] = items_image(enem_grafs[0][cte_event], 5, 160, 135, -15, 100, 2);
    //region_define(2,75,127,174,16);
    temp = 18;
    while (temp < 200)
        temp += 2;
        switch(temp)
        case 20, 40, 60, 80, 94, 114, 134, 154, 174: region_define(2, 75, 127, temp, 16); end
        end //switch
        frame;
    end
    nw_hijos[2] = items_image(enem_grafs[0][cte_event], energia + 2, 196, 48, -16, 100, 0);
    new_weapon_img2(enem_grafs[0][cte_event], energia + 2, 196, 48, -16);
    
    nw_hijos[3] = items_image (enem_grafs[0][cte_event], energia + 6, 160, 190, -15, 100, 0);
    nw_hijos[4] = items_image (enem_grafs[0][cte_event], energia + 9, 160, 190, -16, 100, 0);
    nw_hijos[4].alpha = 0;
    temp = 0;
    energia = 30000;
    loop
        temp += energia;
        if (temp > 360000)
            temp -= 360000;
            energia = energia >> 1;
        end
        nw_hijos[3].size_y = abs(100 * sin(temp));
        if (sin(temp) < 0) nw_hijos[3].flags = 2; else nw_hijos[3].flags = 0; end
        if ((energia < 2000) && (nw_hijos[3].size_y == 100) && (nw_hijos[3].flags == 0)) break; end
        frame;
    end
    
    for (nw_hijos[4].alpha = 0; nw_hijos[4].alpha < 255; nw_hijos[4].alpha = clamp( nw_hijos[4].alpha + 32, 0, 255 ) ) frame; end
    for (nw_hijos[4].alpha = 255; nw_hijos[4].alpha > 0; nw_hijos[4].alpha = clamp( nw_hijos[4].alpha - 32, 0, 255 ) ) frame; end
    nw_hijos[4].alpha = 0;
        
    while (music_is_playing()) frame; end
    frame(10000);
    
    //añadimos el arma************************************
    temp = armas_get[1] || armas_get[2] || armas_get[3];    //Comprobamos si es el primer arma
    switch (temp_weap)
    case 21: armas_get[0] = 0; armas_get[1] = 1; end
    case 22: armas_get[0] = 0; armas_get[2] = 1; end
    case 23: armas_get[0] = 0; armas_get[3] = 1; end
    end //switch
    refresh_weapons();
    //Si es el primer arma, se selecciona
    if (!temp)
        select_first_weapon();
        refresh_interface();
    end
    //aclaramos la pantalla
	signal(info_prota.id_prota, s_freeze_tree);
    signal(nw_hijos[0], s_kill);
    signal(nw_hijos[1], s_kill);
    signal(nw_hijos[2], s_kill);
    signal(nw_hijos[3], s_kill);
    signal(nw_hijos[4], s_kill);
    for (alpha = 150; alpha > 0; alpha = clamp( alpha - 2, 0, 255 ) )
        frame;
    end
    //quitamos pausa
    signal(info_prota.id_prota, s_wakeup_tree);
    prota_control = 1;
    signal_moving_items(s_wakeup);
    signal_enemigos(s_wakeup);
    signal_sync(s_wakeup);
    signal_tiles_especiales(s_wakeup);
    map_unload(file, graph);
    fpg_unload(enem_grafs[0][cte_event]);
    enem_grafs[1][cte_event] = 0;
	pausa_estado = 1;
    
    //play_level_music(next_level);
    level_song = next_level;
end
