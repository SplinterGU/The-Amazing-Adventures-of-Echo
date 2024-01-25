process end_level_event_image (x, y, z, file, graph)
begin
    signal(id, s_freeze);
    frame;
end

process end_level_event (int level)
private
    int hijos[3];
begin
    prota_control = 0;
    pausa_estado = 0;
    level_song = _CTE_MUSIC_ENDLEVEL;
    
    graph = map_new(320, 240);
    map_clear(file, graph, rgb(0,0,0));
    x = 160;
    y = 120;
    z = -10;
    alpha = 0;
    info_prota.id_prota.z = z - 1;
    
    for (alpha = 0; alpha < 255; alpha = clamp( alpha + 5, 0, 255 )) frame; end
    
    /*if (level == 1)
        if (savegame_pos != 0)
            refresh_actual_gamedata(&game_global_sav);
            save_filegame(&game_global_sav,savegame_pos);
            game_saved_graph();
        end
    end*/
    
    enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/chlevel.fpg");
    enem_grafs[1][cte_event] = 1;
    
    //musica
    frame(15000);
    hijos[0] = end_level_event_image(83, 25, z - 1, enem_grafs[0][cte_event], 20);
    frame(2500);
    hijos[1] = end_level_event_image(237, 25, z - 1, enem_grafs[0][cte_event], 21);
    frame(2500);
    hijos[2] = end_level_event_image(160, 55, z - 1, enem_grafs[0][cte_event], 22);
    frame(5000);
    hijos[3] = end_level_event_image(160, 133, z - 1, enem_grafs[0][cte_event], level);
    //echo has passed castle horror
    
    while (music_is_playing()) frame; end
    //loop frame; end
    
    set_fps(25, cte_frameskip);
    fade_off(1000);
    while (fade_info.fading) frame; end
    set_fps(50, cte_frameskip);
    
    signal(hijos[0], s_kill);
    signal(hijos[1], s_kill);
    signal(hijos[2], s_kill);
    signal(hijos[3], s_kill);
    map_unload(file, graph);
    fpg_unload(enem_grafs[0][cte_event]);
    enem_grafs[1][cte_event] = 0;
end

process dead_event ()
private
    int angle2;
    int de_echo;
    int de_espiritu;
    int de_vidas[CTE_GAME_MAX_VIDAS];
    
    int de_animacion[14]=36,36,36,36,36,36,36,36,37,36,37,36,36,36,36;
    
    //int temp_prota_graph;
    int temp_level_song;
    int cont;
    
begin
    prota_control = 0;
    pausa_estado = 0;
    if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_freeze); end
    signal_items(s_freeze);
    signal_enemigos(s_freeze);
    signal_event_all(s_freeze);
    signal_sync(s_freeze);
    signal_tiles_especiales(s_freeze);
    
    temp_level_song = level_song;
    level_song = _CTE_MUSIC_NOMUSIC;
    
	//Fundido a semi negro
    graph = map_new(320, 240);
    map_clear(file, graph, rgb(0,0,0));
    x = 160;
    y = 120;
    z = -99;
    alpha=0;
    //info_prota.id_prota.z=-4;
    //info_prota.id_prota.graph=4;
    //temp_prota_graph=info_prota.id_prota.graph;
    //info_prota.id_prota.graph=0;
    if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_sleep); end
    de_echo = end_level_event_image(info_prota.id_prota.x, info_prota.id_prota.y, -100, info_prota.id_prota.file, 20);
    
    for (alpha = 0; alpha < 200; alpha = clamp( alpha + 5, 0, 200 )) frame; end
    
	//desplazando copia de Echo al centro de la pantalla
    while ((de_echo.x != 160) || (de_echo.y != 185))
        if (de_echo.x < 160) de_echo.x += 2; end
        if (de_echo.x > 160) de_echo.x -= 2; end
        if (de_echo.y < 185) de_echo.y += 2; end
        if (de_echo.y > 185) de_echo.y -= 2; end
        frame;
		
		if (abs(de_echo.x - 160) < 2) de_echo.x = 160; end
		if (abs(de_echo.y - 185) < 2) de_echo.y = 185; end
    end
    
	//Subiendo espíritu de Echo al cielo
    de_echo.graph = 35;
    frame(5000);
    enem_grafs[0][cte_dead] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/gover.fpg");
    enem_grafs[1][cte_dead] = 1;
    de_espiritu = end_level_event_image(de_echo.x, de_echo.y, -100, enem_grafs[0][cte_dead], 1);
    de_espiritu.alpha = 0;
    
    while (de_espiritu.y > -15)
        de_espiritu.y--;
        if (de_espiritu.alpha < 255) de_espiritu.alpha = clamp( de_espiritu.alpha + 5, 0, 255 ); end
        angle2 += 6000;
        if (angle2 > 360000) angle2 -= 360000; end
        de_espiritu.x = 160 + (17 * sin(angle2));
        frame;
    end
    
	//Aparecen las vidas
    for (cont = 0; cont < info_prota.vidas; cont++)
        de_vidas[cont] = end_level_event_image(150 - (22 * (info_prota.vidas - 1)) + (44 * cont),
												-16, -100, enem_grafs[0][cte_dead], 3);
    end
    
    while (de_vidas[0].y < 70)
        for (cont = 0; cont < info_prota.vidas; cont++)
            de_vidas[cont].y++;
        end
        frame;
    end
    frame(5000);
    
	//Desaparece una vida
    for (cont = 4; cont <= 8; cont++)
        de_vidas[info_prota.vidas-1].graph = cont;
        frame(300);
    end
    de_vidas[info_prota.vidas-1].graph = 0;
    signal(de_vidas[info_prota.vidas-1], s_kill);
    frame(2000);
    
    
    info_prota.vidas--;
    
    //Comprobamos si es el GAME OVER
    if (info_prota.vidas == 0)
		frame(3000);
        //animacion de la muerte, etc
        level_song = _CTE_MUSIC_GAMEOVER;
        
		//Se oscurece la pantalla
        for (alpha = 200; alpha < 255; alpha = clamp( alpha + 5, 0, 255 )) frame; end
        
        //cartel de game over descendiendo
        de_espiritu.x = 160;
        de_espiritu.y = -15;
        de_espiritu.graph = 9;
        while (de_espiritu.y < 70) de_espiritu.y++; frame; end
        
        while (music_is_playing()) frame; end
        frame(10000);
        fade_off(500);
        while (fade_info.fading) frame; end
        signal(de_espiritu, s_kill);
        signal(de_echo, s_kill);
        next_level = 0;
        global_mode = CTE_GLOBAL_MODE_PORTADA;
        end_level = 2;
        frame;
    else
		//Echo se levanta perplejo
        for (cont = 0; cont <= 14; cont++)
            de_echo.graph = de_animacion[cont];
            frame(500);
        end
        de_echo.graph = 1;	//Echo de pie
        frame(2000);
        de_echo.graph = 15;
        
		//Vidas desaparecen por el lateral
        while (de_vidas[0].x < 350)
            for (cont = 0; cont < info_prota.vidas; cont++)
                de_vidas[cont].x += 5;
            end
            frame;
        end
        
		//Se eliminan los procesos vidas
        for (cont = 0; cont < 5; cont++)
            if (exists(de_vidas[cont])) signal(de_vidas[cont],s_kill); end
        end
        frame(5000);
        de_echo.graph = 2;
        frame(2500);
        
		//Caida del espíritu
        de_espiritu.x = 160;
        de_espiritu.y = -100;
        de_espiritu.graph = 2;
        cont = 0;
        while (de_espiritu.y < de_echo.y)
            de_espiritu.y += 2;
            de_espiritu.angle += 9000;
            de_espiritu.alpha = clamp( (de_echo.y - de_espiritu.y) * 2, 0, 255 );
            cont++;
            switch (cont)
            case 3: de_echo.graph = 38; end
            case 6: de_echo.graph = 39; cont = 0; end
            end //switch
            
            frame;
        end
        
        signal(de_espiritu, s_kill);
        de_echo.graph = 2;
        frame(1000);
        de_echo.graph = 1;
        frame(7000);
        de_echo.graph = 30;
        frame(2500);
        
		//Devolvemos la copia de Echo a la posición del original
        while ((de_echo.x != info_prota.id_prota.x) || (de_echo.y != info_prota.id_prota.y))
            if (de_echo.x < info_prota.id_prota.x) de_echo.x += 2; end
            if (de_echo.x > info_prota.id_prota.x) de_echo.x -= 2; end
            if (de_echo.y < info_prota.id_prota.y) de_echo.y += 2; end
            if (de_echo.y > info_prota.id_prota.y) de_echo.y -= 2; end
            frame;
			
			if (abs(de_echo.x - info_prota.id_prota.x) < 2) de_echo.x = info_prota.id_prota.x; end
			if (abs(de_echo.y - info_prota.id_prota.y) < 2) de_echo.y = info_prota.id_prota.y; end
        end
        
        //loop frame; end
		de_echo.x = info_prota.id_prota.x;
		de_echo.y = info_prota.id_prota.y;
        de_echo.graph = info_prota.id_prota.graph;
		
		//Se restaura a Echo los datos iniciales de una vida nueva
        info_prota.p_energ = info_prota.p_max_energ;
        refresh_interface();
        for (alpha = 200; alpha > 0; alpha = clamp( alpha - 5, 0, 255 )) frame; end
        
		//Se restaura el juego
        signal(de_echo, s_kill);
        if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_wakeup); end
        signal_items(s_wakeup);
        signal_enemigos(s_wakeup);
        signal_event_all(s_wakeup);
        signal_sync(s_wakeup);
        signal_tiles_especiales(s_wakeup);
        prota_control = 1;
        pausa_estado = 1;
        level_song = temp_level_song;
        
        frame;
    end
    
    fpg_unload(enem_grafs[0][cte_dead]);
    enem_grafs[1][cte_dead] = 0;
    map_unload(file, graph);
end