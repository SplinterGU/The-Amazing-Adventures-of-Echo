process event_1_3_1 ()
private
    int fin_evento;
    int temp;
begin
    modificar_tile(&durezas, 5, 29, 0, 1);
    modificar_tile(&durezas, 5, 28, 0, 1);
    modificar_tile(&durezas, 5, 27, 0, 1);
    modificar_tile(&durezas, 5, 26, 0, 1);
    modificar_tile(&durezas, 5, 25, 0, 1);
    modificar_tile(&durezas, 5, 24, 0, 1);
    modificar_tile(&durezas, 5, 23, 0, 1);
    modificar_tile(&durezas, 5, 22, 0, 1);
    modificar_tile(&durezas, 5, 21, 0, 1);
    modificar_tile(&durezas, 5, 20, 0, 1);
    modificar_tile(&durezas, 26, 29, 0, 1);
    modificar_tile(&durezas, 26, 28, 0, 1);
    modificar_tile(&durezas, 26, 27, 0, 1);
    modificar_tile(&durezas, 26, 26, 0, 1);
    modificar_tile(&durezas, 26, 25, 0, 1);
    modificar_tile(&durezas, 26, 24, 0, 1);
    modificar_tile(&durezas, 26, 23, 0, 1);
    modificar_tile(&durezas, 26, 22, 0, 1);
    modificar_tile(&durezas, 26, 21, 0, 1);
    modificar_tile(&durezas, 26, 20, 0, 1);
    
    level_song = _CTE_MUSIC_MIDBOSS;
	intro_boss_01_3_01();
    x2 = info_prota.id_prota.x2;
    y2 = info_prota.id_prota.y2;
    id_tscroll.id_target = id;
    while ((x2 != 256) || (y2 != 400))
        if (x2 < 256) x2++; end
        if (x2 > 256) x2--; end
        if (y2 < 400) y2++; end
        if (y2 > 400) y2--; end
        frame;
    end
    //say("camara movida");
    
    fin_evento = 0;
    prota_control = 0;
    while (get_id(type normal_shot)) frame; end
    //say("esperados disparos");
    
    //comienza la juerga
    enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/ghyppo.fpg");
    enem_grafs[1][cte_event] = 1;
    temp = ghyppo(enem_grafs[0][cte_event]);
    enem_ener_interface(temp);
    
    while (temp.alpha < 255) frame; end     //esperamos a que aparezca
    //frame(15000);                       //esperamos un poco
    
    //prota_control=1;
    while (exists(temp)) frame; end
    while (get_id(type croquis)) frame; end     //esperamos a que desaparezcan los mini-cocodrilos
    
    //fin de la juerga
    level_song = next_level;
    if (exists(info_prota.id_prota))
        prota_control = 0;
        while ((x2 != info_prota.id_prota.x2) || (y2 != info_prota.id_prota.y2))
            if (x2 < info_prota.id_prota.x2) x2++; end
            if (x2 > info_prota.id_prota.x2) x2--; end
            if (y2 < info_prota.id_prota.y2) y2++; end
            if (y2 > info_prota.id_prota.y2) y2--; end
            frame;
        end
        id_tscroll.id_target = info_prota.id_prota;
        prota_control = 1;
    end
    
    modificar_tile(&durezas, 5, 29, 0, 0);
    modificar_tile(&durezas, 5, 28, 0, 0);
    modificar_tile(&durezas, 5, 27, 0, 0);
    modificar_tile(&durezas, 5, 26, 0, 0);
    modificar_tile(&durezas, 5, 25, 0, 0);
    modificar_tile(&durezas, 5, 24, 0, 0);
    modificar_tile(&durezas, 5, 23, 0, 0);
    modificar_tile(&durezas, 5, 22, 0, 0);
    modificar_tile(&durezas, 5, 21, 0, 0);
    modificar_tile(&durezas, 5, 20, 0, 0);
    modificar_tile(&durezas, 26, 29, 0, 0);
    modificar_tile(&durezas, 26, 28, 0, 0);
    modificar_tile(&durezas, 26, 27, 0, 0);
    modificar_tile(&durezas, 26, 26, 0, 0);
    modificar_tile(&durezas, 26, 25, 0, 0);
    modificar_tile(&durezas, 26, 24, 0, 0);
    modificar_tile(&durezas, 26, 23, 0, 0);
    modificar_tile(&durezas, 26, 22, 0, 0);
    modificar_tile(&durezas, 26, 21, 0, 0);
    modificar_tile(&durezas, 26, 20, 0, 0);
    
    fpg_unload(enem_grafs[0][cte_event]);
    enem_grafs[1][cte_event] = 0;
end