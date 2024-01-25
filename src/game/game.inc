process game ()
private
    int g_end_level;
    int g_play_intro;
    int g_show_saved;
    int pausa_id;
    int cont;
begin
    //init_level = 0;
    //next_level = 1;
    //next_sublevel = 0;
    end_level = 0;
    g_play_intro = 1;
    g_show_saved = 0;
    
    prota_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/prota.fpg");
    armas_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/weapons.fpg");
    //init_weapons();
    armas_select = 0;
    armas_curr_level = 0;
        //armas_select=1; 
        //armas_get[0]=0;
        //armas_get[1]=1;
        //armas_get[2]=1;
        //armas_get[3]=1;
        //info_prota.vidas=1;
    
    item_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/items.fpg");
	checkpoint_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/checkpoint.fpg");
    explosion_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/explos.fpg");
    
    pausa_id = pausa();
    load_interface();
    //say("Cargada interfaz");
    //inicializacion de datos
    //info_prota.p_max_energ=10;
    //info_prota.p_energ=10;
    //armas_level[0][0]=0;
    //armas_level[1][0]=0;
    //armas_level[2][0]=0;
    //armas_level[3][0]=0;
    
    //refresh_interface();
    //pausa_estado=1;                 //DEBUG*********************
    
    loop
        //inicialización de los botones
        for (cont = 0; cont <= cte_interruptores; cont++)
            interruptores[cont] = 0;
        end
        info_prota.p_invencible = 2;
        
        switch (next_level)
        case 0:     //salir al menu
            break;
        end
        
        case 1:
            //say("vamos bien, nivel 1");
            //debug lines
            //armas_select = 3;
            
            //carga de gráficos de enemigos
            cargar_graficos_enemigos(1,0);
            
            enem_grafs[0][cte_level] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level01bg.fpg");
            enem_grafs[1][cte_level] = 1;
            
            //enem_grafs[0][cte_ghyppo] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/ghyppo.fpg");
            
            cargar_sfx_nivel(1);
            //say("Datos cargados");
            
            //g_end_level = play_level(next_level, next_sublevel, g_play_intro);
            g_end_level = 0;
            play_level(next_level, next_sublevel, init_level, g_play_intro, g_show_saved, &g_end_level);
            signal(id,s_sleep);
            frame;
            
            g_play_intro = 0;
            g_show_saved = 0;
            switch (g_end_level)
            case 1:     //nivel superado
                if (next_sublevel < 3)
                    next_sublevel++;
					init_level = 0;
                else
                    next_level = 3;
                    next_sublevel = 0;
					init_level = 0;
                    g_play_intro = 1;
                end
                //Salvamos partida
                if (savegame_pos != 0)
                    refresh_actual_gamedata(&game_global_sav);
                    save_filegame(&game_global_sav, savegame_pos);
                    g_show_saved = 1;
                    //game_saved_graph();
                end
            end
            case 2:     //muerto
                next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                global_mode = 0;
            end
            case 3:     //salir
                next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                global_mode = 0;
            end
            end
            //Este debe ser el único proceso que modifique next_level y next_sublevel**************
            //Excepción: juego no lineal, es decir, que tenga más de un final de nivel, en ese caso,
            //el item de fin de nivel o subnivel es el encargado de cambiar estas variables para
            //decidir el siguiente nivel.
            
                
            signal_items(s_kill);
            signal_enemigos(s_kill);
            signal_event_all(s_kill);
            signal_tiles_especiales(s_kill);
            
            unload_all_enem_fpgs();
            
            sound_stop(-1);
            descargar_sfx_nivel(1);
            
            unset_interface();
            
            //main lines
            //search_start_point(&nivel,&durezas,0,&x2,&y2);
        end
        
        case 3:
            //debug lines
            //armas_select=1;
            
            cargar_graficos_enemigos(3,0);
            
            cargar_sfx_nivel(3);
            
            
            //g_end_level = play_level(next_level, next_sublevel, g_play_intro);
            g_end_level = 0;
            play_level(next_level, next_sublevel, init_level, g_play_intro, g_show_saved, &g_end_level);
            signal(id,s_sleep);
            frame;
            
            g_play_intro = 0;
            g_show_saved = 0;
            switch (g_end_level)
            case 1:     //nivel superado
                //next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                //global_mode=4;
                
                next_level = 4;
                g_play_intro = 1;
                
                //Salvamos partida
                if (savegame_pos != 0)
                    refresh_actual_gamedata(&game_global_sav);
                    save_filegame(&game_global_sav,savegame_pos);
                    g_show_saved = 1;
                    //game_saved_graph();
                end
            end
            case 2:     //muerto
                next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                global_mode = 0;
            end
            case 3:     //salir
                next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                global_mode = 0;
            end
            end
            //Este debe ser el único proceso que modifique next_level y next_sublevel**************
            //Excepción: juego no lineal, es decir, que tenga más de un final de nivel, en ese caso,
            //el item de fin de nivel o subnivel es el encargado de cambiar estas variables para
            //decidir el siguiente nivel.
            //Excepción: evento intermedio para salvar a mitad de camino, que sólo puede modificar
            //next_sublevel, e incluso no sería necesario.
            
            
            
            signal_items(s_kill);
            signal_enemigos(s_kill);
            signal_event_all(s_kill);
            signal_tiles_especiales(s_kill);
            
            unload_all_enem_fpgs();
            
            sound_stop(-1);
            descargar_sfx_nivel(3);
            
            unset_interface();
            
            //main lines
            //search_start_point(&nivel, &durezas, 0, &x2, &y2);
        end
        case 4:
            cargar_graficos_enemigos(4, next_sublevel);
            cargar_sfx_nivel(4);
            
            enem_grafs[0][cte_tiles_agua] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/water_tiles04.fpg");
            enem_grafs[1][cte_tiles_agua] = 1;
			
			enem_grafs[0][cte_tiles_lava] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/lava_tiles04.fpg");
            enem_grafs[1][cte_tiles_lava] = 1;
			
			enem_grafs[0][cte_interactive_plaforms] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/interact_platf04.fpg");
            enem_grafs[1][cte_interactive_plaforms] = 1;
            
            g_end_level = 0;
            play_level(next_level, next_sublevel, init_level, g_play_intro, g_show_saved, &g_end_level);
            signal(id, s_sleep);
            frame;
            
            g_play_intro = 0;
            g_show_saved = 0;
            switch (g_end_level)
            case 1:     //nivel superado
                if (next_sublevel < 1)
                    next_sublevel++;
					init_level = 0;
                    
                    //Salvamos partida
                    if (savegame_pos != 0)
                        refresh_actual_gamedata(&game_global_sav);
                        save_filegame(&game_global_sav,savegame_pos);
                        g_show_saved = 1;
                        //game_saved_graph();
                    end
                else
                    //next_level = 0;
					next_sublevel = 0;
					init_level = 0;
					
					next_level = 5;
					g_play_intro = 1;
					
					//Salvamos partida
					if (savegame_pos != 0)
						refresh_actual_gamedata(&game_global_sav);
						save_filegame(&game_global_sav,savegame_pos);
						g_show_saved = 1;
						//game_saved_graph();
					end
                end
            end
            case 2:     //muerto
                next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                global_mode = 0;
            end
            case 3:     //salir
                next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                global_mode = 0;
            end
            end
            //Este debe ser el único proceso que modifique next_level y next_sublevel**************
            //Excepción: juego no lineal, es decir, que tenga más de un final de nivel, en ese caso,
            //el item de fin de nivel o subnivel es el encargado de cambiar estas variables para
            //decidir el siguiente nivel.
            //Excepción: evento intermedio para salvar a mitad de camino, que sólo puede modificar
            //next_sublevel, e incluso no sería necesario.
            
			//say("Descargando items");
            signal_items(s_kill);
			//say("Descargando enemigos");
            signal_enemigos(s_kill);
			//say("Descargando eventos");
            signal_event_all(s_kill);
			//say("Descargando tiles especiales");
            signal_tiles_especiales(s_kill);
			//say("Descargando FPGs enemigos");
            
            unload_all_enem_fpgs();
            
            sound_stop(-1);
			//say("Descargando sfx nivel");
            descargar_sfx_nivel(4);
            
			//say("Unset interface");
            unset_interface();
            
            //main lines
            //search_start_point(&nivel,&durezas,0,&x2,&y2);
        end
		
		case 5:
            cargar_graficos_enemigos(5, next_sublevel);
            cargar_sfx_nivel(4);
            
            enem_grafs[0][cte_anim_level] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/cascada01.fpg");
            enem_grafs[1][cte_anim_level] = 1;
            
            enem_grafs[0][cte_tiles_agua] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/water_tiles04.fpg");
            enem_grafs[1][cte_tiles_agua] = 1;
			
			//enem_grafs[0][cte_interactive_plaforms] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/interact_platf04.fpg");
            //enem_grafs[1][cte_interactive_plaforms] = 1;
            
            g_end_level = 0;
            play_level(next_level, next_sublevel, init_level, g_play_intro, g_show_saved, &g_end_level);
            signal(id, s_sleep);
            frame;
            
            g_play_intro = 0;
            g_show_saved = 0;
            switch (g_end_level)
            case 1:     //nivel superado
                next_level = 0;
				next_sublevel = 0;
				init_level = 0;
				
				say("Evento en construccion");
				event_en_construccion();
				signal(id, s_sleep);
				frame;
				say("Fin evento");
				
				global_mode = 4;
            end
            case 2:     //muerto
                next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                global_mode = 0;
            end
            case 3:     //salir
                next_level = 0;
                next_sublevel = 0;
				init_level = 0;
                global_mode = 0;
            end
            end
            //Este debe ser el único proceso que modifique next_level y next_sublevel**************
            //Excepción: juego no lineal, es decir, que tenga más de un final de nivel, en ese caso,
            //el item de fin de nivel o subnivel es el encargado de cambiar estas variables para
            //decidir el siguiente nivel.
            //Excepción: evento intermedio para salvar a mitad de camino, que sólo puede modificar
            //next_sublevel, e incluso no sería necesario.
            
			//say("Descargando items");
            signal_items(s_kill);
			//say("Descargando enemigos");
            signal_enemigos(s_kill);
			//say("Descargando eventos");
            signal_event_all(s_kill);
			//say("Descargando tiles especiales");
            signal_tiles_especiales(s_kill);
			//say("Descargando FPGs enemigos");
            
            unload_all_enem_fpgs();
            
            sound_stop(-1);
			//say("Descargando sfx nivel");
            descargar_sfx_nivel(4);
            
			//say("Unset interface");
            unset_interface();
            
            //main lines
            //search_start_point(&nivel,&durezas,0,&x2,&y2);
        end
        
        default: break; end
        end //switch
    end //loop principal
    
	//say("quitando interfaz y pausa");
    unload_interface();
    if (exists(pausa_id)) signal(pausa_id,s_kill); end
    pausa_estado = 0;
    
	//say("Descargando fpgs");
    fpg_unload(prota_file);
    fpg_unload(armas_file);
    fpg_unload(item_grafs);
	fpg_unload(checkpoint_grafs);
    fpg_unload(explosion_grafs);
    //descarga de sonidos de disparo (si procede)
	//say("Descargando sfx arma");
    descargar_sfx_arma();
    
    
    signal(father,s_wakeup);
    frame;
end
