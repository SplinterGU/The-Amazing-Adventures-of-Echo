process event_1_4_1 ()
private
    int fin_evento;
    int id_boss;
begin
    level_song = _CTE_MUSIC_FINALBOSS;
	intro_boss_01_4();
    
    x2 = info_prota.id_prota.x2;
    y2 = info_prota.id_prota.y2;
    id_tscroll.id_target = id;
    while ((x2 != 656) || (y2 != 120))
        if (x2 < 656) x2++; end
        if (x2 > 656) x2--; end
        if (y2 < 120) y2++; end
        if (y2 > 120) y2--; end
        frame;
    end
    
    fin_evento = 0;
    prota_control = 0;
    while (get_id(type normal_shot)) frame; end
    signal_enemigos(s_kill);
    //say("esperados disparos");
    
    enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/satavamp.fpg");
    enem_grafs[1][cte_event] = 1;
    
    id_boss = satavamp();
    
    while (exists(id_boss)) frame; end
    
    fpg_unload(enem_grafs[0][cte_event]);
    enem_grafs[1][cte_event] = 0;
    
    prota_control = 0;
    pausa_estado=0;
    
    //next_level = 3;
    //next_sublevel = 0;
    end_level_event(1);    //************************************
    while (exists(type end_level_event)) frame; end
    
    
    end_level = 1;
    //fade(100, 100, 100, 255);
end