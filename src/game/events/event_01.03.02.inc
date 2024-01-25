process ladrillo_cae(int lc_tilex, int lc_tiley)
private
    int temblor;
begin
    file = id_tscroll.ts_file;
    graph = obtener_tile(&nivel, lc_tilex, lc_tiley, 0);
    x2 = (lc_tilex * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (lc_tiley * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    z = -2;
    
    modificar_tile(&nivel, lc_tilex, lc_tiley, 0, 0);
    ts_actualiza_tiles(&id_tscroll);
    tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
    
    temblor = enem_temblor2(id, 4);
    while (y2 < 512)
        if (!exists(temblor))
            energia++;
            if (energia > 5) energia = 5; end
            y2 += energia;
            modificar_tile(&durezas, lc_tilex, lc_tiley, 0, 0);
        end
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
end


process event_1_3_2 ()
private
    int fin_evento;
    int dragon_id[0];
    
    int ladrillos_id[19] = 5,3,2,1,1,2,3,5,3,2,1,1,2,3,5,3,2,1,1,1;
    
    int temp;
    int cont;
    int cont_ladrillo1, cont_ladrillo2;
begin
    level_song = _CTE_MUSIC_MIDBOSS;
	intro_boss_01_3_02();
    x2 = info_prota.id_prota.x2;
    y2 = info_prota.id_prota.y2;
    id_tscroll.id_target = id;
    while ((x2 != 3680) || (y2 != 176))
        if (x2 < 3680) x2++; end
        if (x2 > 3680) x2--; end
        if (y2 < 176) y2++; end
        if (y2 > 176) y2--; end
        frame;
    end
    
    fin_evento = 1;
    prota_control = 0;
    while (get_id(type normal_shot)) frame; end
    //say("esperados disparos");
    
    enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/gravor.fpg");
    enem_grafs[1][cte_event] = 1;
    
    dragon_id[0] = dragon_body(enem_grafs[0][cte_event], 1, 3840 + 68, 296 + 68, 10);
    
    while (dragon_id[0].energia == 0) frame; end
    
    modificar_tile(&nivel, 219, 8, 0, 0);
    ts_actualiza_tiles(&id_tscroll);
    
    while (exists(dragon_id[0]))
        //say("tres");
        frame;
    end
    
    while (info_prota.id_prota.y2 != y2)
        if (y2 < info_prota.id_prota.y2) y2++; end
        if (y2 > info_prota.id_prota.y2) y2--; end
        frame;
    end
    
    level_song = next_level;
    temp = 0;
    while (!temp)
        //tiramos un ladrillo
        cont_ladrillo1 = rand(1, 19);
        while (cont_ladrillo1 > 0)
            cont_ladrillo2++;
            if (cont_ladrillo2 > 19) cont_ladrillo2 = 0; end
            if (ladrillos_id[cont_ladrillo2] > 0)
                cont_ladrillo1--;
            end
        end
        
        ladrillos_id[cont_ladrillo2]--;
        ladrillo_cae(220 + cont_ladrillo2, 16 + ladrillos_id[cont_ladrillo2]);
        //comprobamos que se han caido los ladrillos
        temp = 1;
        for (cont = 0; cont < 20; cont++)
            if (ladrillos_id[cont] > 0) temp = 0; break; end
        end
        
        for (cont = 0; cont < 25; cont++)
            y2 = info_prota.id_prota.y2;
            frame;
        end
    end
    
    while (info_prota.id_prota.x2 != x2)
        y2 = info_prota.id_prota.y2;
        if (x2 < info_prota.id_prota.x2) x2++; end
        if (x2 > info_prota.id_prota.x2) x2--; end
        frame;
    end
    id_tscroll.id_target = info_prota.id_prota;
    modificar_tile(&durezas, 239, 30, 0, 0);
    modificar_tile(&durezas, 239, 29, 0, 0);
    modificar_tile(&durezas, 239, 28, 0, 0);
    modificar_tile(&durezas, 239, 27, 0, 0);
    modificar_tile(&durezas, 239, 26, 0, 0);
    modificar_tile(&durezas, 239, 25, 0, 0);
end