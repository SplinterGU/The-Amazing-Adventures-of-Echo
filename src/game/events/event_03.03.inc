process event_3_3 ()
private
    int fin_evento;
    int id_boss;
    
    int cont;
    int temp_wav, temp_canal;
begin
    level_song = _CTE_MUSIC_NOMUSIC;
    
    x2 = info_prota.id_prota.x2;
    y2 = info_prota.id_prota.y2;
    id_tscroll.id_target = id;
    while ((x2 != 14112) || (y2 != 224))
        if (x2 < 14112) x2++; end
        if (x2 > 14112) x2--; end
        if (y2 < 224) y2++; end
        if (y2 > 224) y2--; end
        frame;
    end
    
    modificar_tile(&durezas, 891, 18, 0, 253);
    modificar_tile(&durezas, 872, 18, 0, 254);
    
    fin_evento = 0;
    //prota_control = 0;
    while (get_id(type normal_shot)) frame; end
    signal_enemigos(s_kill);
    //say("esperados disparos");
    
    enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/blom.fpg");
    enem_grafs[1][cte_event] = 1;
    
    x = 160;
    y = 120;
    file = enem_grafs[0][cte_event];
    graph = 7;
    
    temp_wav = sound_load(dreamcast_ruta + "sfx/alarma.wav");
    temp_canal = sound_play(temp_wav,1);
    for (cont = 0; cont < 6; cont++)
        fade_on(300);
        while (fade_info.fading) frame; end
        fade_off(300);
        while (fade_info.fading) frame; end
    end
    graph = 0;
    if (sound_is_playing(temp_canal)) sound_stop(temp_canal); end
    sound_unload(temp_wav);
    
    level_song = _CTE_MUSIC_FINALBOSS;
    intro_boss_03_02();
	
    id_boss = big_blom();
    
    while (exists(id_boss)) frame; end
    
    fpg_unload(enem_grafs[0][cte_event]);
    enem_grafs[1][cte_event] = 0;
    
    prota_control = 0;
    pausa_estado = 0;
    
    end_level_event(3);    //************************************
    while (exists(type end_level_event)) frame; end
    
    //loop frame; end
    //next_level = 0;
    //next_sublevel = 0;
    //global_mode = 4;
    end_level = 1;
    //fade(100, 100, 100, 255);
end