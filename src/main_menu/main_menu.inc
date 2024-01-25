//************************************************************************************
//      MENU PRINCIPAL
//************************************************************************************

process portada_img (file, graph, x, y, z)
begin
    signal(id, s_freeze);
    frame;
end

process portada_flecha1 (file, graph2, x2, y2)
private
    int angle2;
begin
    x = 60;
    y = 200;
    graph = graph2;
    loop
        angle2 += 8000;
        x = x2 - 14 * sin(angle2);
        frame;
    end
end

process portada_flecha2 (file, graph2, x2, y2)
private
    int angle2;
begin
    x = 260;
    y = 200;
    graph = graph2;
    loop
        angle2 += 8000;
        x = x2 + 14 * sin(angle2);
        frame;
    end
end

process portada ()
private
	int port_file;
    int port_let;
    int port_opt_id;
    int port_menu;
    global_savegame port_global_savegame;
    
    int vel_vert;
    int vel_rebote;
    
    int opt_mask[4] = 1, 0, 1, 0, 1;
    //int opt_mask[4]=1,1,1,1,1;
    int opt_select;
    
    int portada_flecha[1];
    
    int portada_salir;
    
    int cont;
begin
	say("Iniciando fichero de salvado global");
	init_global_sav();
	
    //enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/mmenu.fpg");
    //enem_grafs[1][cte_event] = 1;
	say("cargando fondo");
	port_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/mmenu.fpg");
    //put_screen(enem_grafs[0][cte_event], 1);
	say("Poniendo fondo");
	put(port_file, 1, graphic_info(port_file, 1, G_WIDTH) / 2, graphic_info(port_file, 1, G_HEIGHT) / 2);
	say("fading");
    set_fps(25, cte_frameskip);
    level_song = _CTE_MUSIC_MAINTITLE;

    fade_on(1000);
    while (fade_info.fading) frame; end

    set_fps(50, cte_frameskip);
	say("fading");
    frame(10000);
    
    port_let = portada_img(port_file, 2, 1600, -150, 0);
    port_let.resolution = 10;
    vel_vert = 80;
    vel_rebote = 80;
    while (vel_rebote > 10)
        vel_vert += 2;
        if (vel_vert > 60) vel_vert = 60; end
        port_let.y += vel_vert;
        if ((port_let.y >= 1650) && (vel_vert > 0))
            vel_rebote >>= 1;
            vel_vert = -vel_rebote;
        end
        frame;
    end
	say("Fin rebote");
    
    refresh_savegame_exists_file();
    //say(opt_mask[1]);
    /*for (cont=1;cont<=max_savefiles;cont++)
        say("fichero busqueda: "+ get_pref_path("bennugd.org", "echo") + "data0"+itoa(cont)+".sav "+fexists(get_pref_path("bennugd.org", "echo") + "data0"+itoa(cont)+".sav"));
        opt_mask[1]=opt_mask[1] || fexists(get_pref_path("bennugd.org", "echo") + "data0"+itoa(cont)+".sav");
        say(opt_mask[1]);
    end*/
    //for (cont=1;cont<=max_savefiles;cont++) say(glob("save/*.*")); end
    opt_mask[1] = 0;
    for (cont = 0; cont < max_savefiles; cont++)
        opt_mask[1] = opt_mask[1] || savegame_exists_file[cont];
        //say(opt_mask[1]);
    end
    
    region_define(2, 75, 190, 170, 20);
    port_opt_id = portada_img(port_file, 3, 340, 200, 0);
    port_opt_id.region = 2;
    
    while (port_opt_id.x > 160)
        port_opt_id.x -= 4;
        frame;
    end
    portada_flecha[0] = portada_flecha1(port_file, 10, 60, 200);
    portada_flecha[1] = portada_flecha2(port_file, 11, 260, 200);
    portada_flecha[0].graph = 0;
    
    portada_salir = 0;
    prota_control = 1;
    repeat
        while (teclas[k_enter][2] == 1 || teclas[k_fire][2] == 1 || teclas[k_jump][2] == 1) frame; end    //compas de espera a que se suelte el botón
        
        //DEBUG******************************************************
        /*while (!key(_g)) frame; end
        desbloquear_nivel(GS_DESBLOQUEO_NIVEL_3,GS_DESBLOQUEO_SUBNIVEL_1);
        while (!key(_h)) frame; end*/
        //***********************************************************
		
        cargar_global_sav(&port_global_savegame);
        if (port_global_savegame.level_select_desbloqueado)
            opt_mask[3] = 1;
        end
        
        
        while (teclas[k_enter][2] != 1 && teclas[k_fire][2] != 1 && teclas[k_jump][2] != 1)
            if ((teclas[k_right][2] == 1) && (opt_select < 4))
                //while (port_opt_id.x>-20)
                while (port_opt_id.x > 0)
                    port_opt_id.x -= 5;
                    frame;
                end
                repeat
                    if (opt_select == 4) opt_select = 0; else opt_select++; end
                until (opt_mask[opt_select])
                //port_opt_id.x=340;
                port_opt_id.x = 320;
                port_opt_id.graph = opt_select + 3;
                if (opt_select == 0) portada_flecha[0].graph = 0; else portada_flecha[0].graph = 10; end
                if (opt_select == 4) portada_flecha[1].graph = 0; else portada_flecha[1].graph = 11; end
                while (port_opt_id.x > 160)
                    port_opt_id.x -= 5;
                    frame;
                end
            end
            if ((teclas[k_left][2] == 1) && (opt_select > 0))
                //while (port_opt_id.x<340)
                while (port_opt_id.x < 320)
                    port_opt_id.x += 5;
                    frame;
                end
                repeat
                    if (opt_select == 0) opt_select = 4; else opt_select--; end
                until (opt_mask[opt_select])
                //port_opt_id.x=-20;
                port_opt_id.x = 0;
                port_opt_id.graph = opt_select + 3;
                if (opt_select == 0) portada_flecha[0].graph = 0; else portada_flecha[0].graph = 10; end
                if (opt_select == 4) portada_flecha[1].graph = 0; else portada_flecha[1].graph = 11; end
                while (port_opt_id.x < 160)
                    port_opt_id.x += 5;
                    frame;
                end
            end
            frame;
        end
        
        //Hemos hecho una selección del menú
        switch (opt_select)
        case 0:                 //START
            signal(portada_flecha[0], s_freeze);
            signal(portada_flecha[1], s_freeze);
            
            graph = map_new(320, 240);
            map_clear(file, graph, rgb(0,0,0));
            x = 160;
            y = 120;
            z = -99;
            for (alpha = 0; alpha < 100; alpha += 5) frame; end
            
            global_opt = 0;
            port_menu = global_menu(0, 2, "Easy (5 lives)", "Medium (3 lives)", "Hard (1 live)", "", "", "");
            while (exists(port_menu)) frame; end
            
            switch (global_opt)
            case 0: info_prota.vidas = 5; end
            case 1: info_prota.vidas = 3; end
            case 2: info_prota.vidas = 1; end
            end //switch
            
            dificultad = global_opt;
            
            //say("preparando menu de carga");
            while (teclas[k_enter][2] == 1 || teclas[k_fire][2] == 1 || teclas[k_jump][2] == 1) frame; end
            port_menu = select_file_menu(max_savefiles, 0);
            while (exists(port_menu)) frame; end
            //say("fin menu carga");
            
            
            set_fps(20, cte_frameskip);
            level_song = _CTE_MUSIC_NOMUSIC;
            fade_off(1000);
            while (fade_info.fading) frame; end

            map_unload(file, graph);
            set_fps(50, cte_frameskip);
            
            //inicializacion de datos
            load_default_gamedata(&game_global_sav, dificultad, info_prota.vidas);
            //load_filegame(&game_global_sav,3);
            load_actual_gamedata(&game_global_sav);
            //save_filegame(&game_global_sav,1);
            //armas_get[0]=1;
            //armas_get[1]=0;
            //armas_get[2]=0;
            //armas_get[3]=0;
            //init_level=0;
            //next_level=1;
            //next_sublevel=0;
            armas_select = 0;
            portada_salir = 1;
            
            global_mode = CTE_GLOBAL_MODE_JUEGO;
        end
        case 1:             //LOAD
            signal(portada_flecha[0], s_freeze);
            signal(portada_flecha[1], s_freeze);
            
            graph = map_new(320, 240);
            map_clear(file, graph, rgb(0,0,0));
            x = 160;
            y = 120;
            z = -99;
            for (alpha = 0; alpha < 100; alpha += 5) frame; end
            
            //say("preparando menu de carga");
            while (teclas[k_enter][2] == 1 || teclas[k_fire][2] == 1 || teclas[k_jump][2] == 1) frame; end
            port_menu = select_file_menu(6, 1);
            while (exists(port_menu)) frame; end
            //say("fin menu carga");
            
            if (global_opt != 0)
                
                set_fps(20, cte_frameskip);
                level_song = _CTE_MUSIC_NOMUSIC;
                fade_off(1000);
                while (fade_info.fading) frame; end
                map_unload(file, graph);
                set_fps(50, cte_frameskip);
                
                //load_default_gamedata(&game_global_sav,dificultad,info_prota.vidas);
                load_filegame(&game_global_sav, savegame_pos);
				load_actual_gamedata(&game_global_sav);
				
                armas_select = 0;
                portada_salir = 1;
                global_mode = CTE_GLOBAL_MODE_JUEGO;
            else
                for (alpha = 100; alpha > 0; alpha -= 5) frame; end
                map_unload(file, graph);
                
                signal(portada_flecha[0], s_wakeup);
                signal(portada_flecha[1], s_wakeup);
            end
        end
        case 2:             //CONFIGURACION
            signal(portada_flecha[0], s_freeze);
            signal(portada_flecha[1], s_freeze);
            
            graph = map_new(320, 240);
            map_clear(file, graph, rgb(0,0,0));
            x = 160;
            y = 120;
            z = -99;
            for (alpha = 0; alpha < 100; alpha += 5) frame; end
#if 0            
            switch (OS_ID)
			case OS_GP2X_WIZ, OS_CAANOO:
                global_opt = 2;
                while (global_opt != 5)
                    port_menu = global_menu(2, 4, "CONFIGURATION", "", "Game options", "Keys configuration",
											"Return", "");
                    while (exists(port_menu)) frame; end
                    
                    switch (global_opt)
                    case 2:
                        port_menu = game_options();
                        while (exists(port_menu)) frame; end
                    end
                    case 3:
                        port_menu = keys_configuration_gp2x();
                        while (exists(port_menu)) frame; end
                        //global_opt=0;
                    end
                    case 4:
                        global_opt = 5;
                    end
                    end //switch
                    frame;
                end
            end
			case OS_DINGUX_A320:
                global_opt = 2;
                while (global_opt != 5)
                    port_menu = global_menu(2, 4, "CONFIGURATION", "", "Game options", "Keys configuration",
											"Return", "");
                    while (exists(port_menu)) frame; end
                    
                    switch (global_opt)
                    case 2:
                        port_menu = game_options();
                        while (exists(port_menu)) frame; end
                    end
                    case 3:
                        port_menu = keys_configuration_dingux();
                        while (exists(port_menu)) frame; end
                        //global_opt=0;
                    end
                    case 4:
                        global_opt = 5;
                    end
                    end //switch
                    frame;
                end
            end
			default:
#endif
                global_opt = 2;
                while (global_opt != 4)
                    //global_opt=2;
                    port_menu = global_menu(2, 4, "CONFIGURATION", "", "Game options", "Keys configuration", "Return", "");
                    while (exists(port_menu)) frame; end
                    
                    switch (global_opt)
                    case 2:
                        port_menu = game_options();
                        while (exists(port_menu)) frame; end
                    end
                    case 3:
                        port_menu = keys_configuration();
                        while (exists(port_menu)) frame; end
                        //say("Global_opt=2");
                        //global_opt=0;
                    end
/*                    case 4:
                        if (joy_number())
                            port_menu = joy_configuration();
                            while (exists(port_menu)) frame; end
                        end
                        //say("Global_opt=3");
                        //global_opt=0;
                    end
*/
                    end //switch
                    frame;
                end
#if 0
            end
			end //switch
#endif
            //Fin del menu de configuración
            for (alpha = 100; alpha > 0; alpha -= 5) frame; end
            map_unload(file, graph);
            
            signal(portada_flecha[0], s_wakeup);
            signal(portada_flecha[1], s_wakeup);
        end
        case 3:
            signal(portada_flecha[0], s_freeze);
            signal(portada_flecha[1], s_freeze);
            
            set_fps(20, cte_frameskip);
            level_song = _CTE_MUSIC_NOMUSIC;
            fade_off(1000);
            while (fade_info.fading) frame; end
            set_fps(50, cte_frameskip);
            portada_salir = 1;
            global_mode = CTE_GLOBAL_MODE_LEVELSELECT;
        end
        case 4:             //EXIT
            signal(portada_flecha[0], s_freeze);
            signal(portada_flecha[1], s_freeze);
            
            set_fps(20, cte_frameskip);
            level_song = _CTE_MUSIC_NOMUSIC;
            fade_off(1000);
            while (fade_info.fading) frame; end
            portada_salir = 1;
            global_mode = CTE_GLOBAL_MODE_SALIR;
        end
        end //switch
    until (portada_salir)
    //loop frame; end
    
    clear_screen();
    if (exists(port_opt_id)) signal(port_opt_id, s_kill); end
    if (exists(port_let)) signal(port_let, s_kill); end
    if (exists(portada_flecha[0])) signal(portada_flecha[0], s_kill); end
    if (exists(portada_flecha[1])) signal(portada_flecha[1], s_kill); end
    //fpg_unload(enem_grafs[0][cte_event]);
    //enem_grafs[1][cte_event]=1;
	fpg_unload(port_file);
    signal(father, s_wakeup);
end
