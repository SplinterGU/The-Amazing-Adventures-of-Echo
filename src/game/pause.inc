process pausa ()
private
    int hijos;
    int temp_prota_control;
begin
    x=160;
    y=120;
    z=-99;
    loop
        if (teclas[k_enter][2] == 1)
            switch (pausa_estado)
            case 1:
                if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_freeze_tree); end
                signal_items(s_freeze);
                signal_enemigos(s_freeze);
                signal_event_all(s_freeze);
                signal_sync(s_freeze);
                signal_tiles_especiales(s_freeze);
                graph = map_new(320, 240);
                map_clear(file, graph, rgb(0,0,0));
                for (alpha = 0; alpha < 100; alpha += 5) frame; end
                
                temp_prota_control = prota_control;
                prota_control = 1;
                global_opt = 0;
                hijos = global_menu(0, 1, "Continue", "Exit", "", "", "", "");
                while (exists(hijos)) frame; end
                
                //say("global_opt: "+itoa(global_opt));
                
                if (global_opt == 1)
                    global_opt = 3;
                    frame;
                    //say("hola");
                    hijos = global_menu(2, 3, "Sure?", "", "Yes", "No", "", "");
                    while (exists(hijos)) frame; end
                    
                    switch (global_opt)
                    case 2: global_opt = 1; end
                    case 3: global_opt = 0; end
                    end //switch
                end
                
                prota_control = temp_prota_control;
                
                switch (global_opt)
                case 0:
                    for (alpha = 100; alpha > 0; alpha -= 5) frame; end
                    map_unload(file, graph);
                    if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_wakeup_tree); end
                    signal_items(s_wakeup);
                    signal_enemigos(s_wakeup);
                    signal_event_all(s_wakeup);
                    signal_sync(s_wakeup);
                    signal_tiles_especiales(s_wakeup);
                    frame;
					alpha = 255;
                end
                case 1:
                    level_song = _CTE_MUSIC_NOMUSIC;
                    set_fps(20, cte_frameskip);
                    fade_off(1000);
                    while (fade_info.fading) frame; end
                    set_fps(50, cte_frameskip);
                    
                    //next_level=0;
                    //global_mode=0;
                    end_level = 3;
                end
                end //switch
            end
            end //switch
        end
        frame;
    end
end