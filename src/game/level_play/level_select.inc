process level_select_imagen (x, y, file, graph, region)
begin
    signal(id, s_freeze);
    frame;
end

process level_select_imagen_nivel (x, y, file, graph, int n, int pointer lsin_opcion)
begin
    loop
        if (*lsin_opcion == n)
            if (size > 70) size--; end
        else
            if (size < 100) size++; end
        end
        frame;
    end
end

process level_select_imagen_arma (x,y,file, graph, int n, int pointer lsia_opcion)
begin
    loop
        if (*lsia_opcion == n) flags = 0; else flags = 4; end
        frame;
    end
end

//**************************************************************************************************
process level_select_play_level () //(int lspl_lev1, int lspl_lev2, int lspl_intro, int pointer lspl_return_end_level)
private
	int lspl_lev1;
	int lspl_lev2;
	int lspl_lev3;
	int lspl_intro;
	
    int g_end_level;
    //int g_play_intro;
    //int g_show_saved;
    int pausa_id;
    int cont;
begin
	lspl_lev1 = next_level;
	lspl_lev2 = next_sublevel;
	lspl_lev3 = init_level;
	lspl_intro = 1;
    end_level = 0;
    
    prota_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/prota.fpg");
    armas_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/weapons.fpg");
    init_weapons();
    armas_curr_level = 0;
    
    item_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/items.fpg");
    checkpoint_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/checkpoint.fpg");
    explosion_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/explos.fpg");
    
    pausa_id = pausa();
    load_interface();
    
    //refresh_interface();
    pausa_estado = 0;
    select_first_weapon();
    
    loop
        //inicialización de los botones
        for (cont = 0; cont <= cte_interruptores; cont++)
            interruptores[cont] = 0;
        end
        info_prota.p_invencible = 2;
        
        next_level = lspl_lev1;
        switch (lspl_lev1)
        case 0:     //salir al menu
            break;
        end
        
        case 1:
            //carga de gráficos de enemigos
            cargar_graficos_enemigos(1,0);
            
            enem_grafs[0][cte_level] = fpg_load(dreamcast_ruta + "grafs/"+ graph_dir + "/level01bg.fpg");
            enem_grafs[1][cte_level] = 1;
            
            cargar_sfx_nivel(1);
            
            g_end_level = 0;
            play_level(lspl_lev1, lspl_lev2, lspl_lev3, lspl_intro, 0, &g_end_level);
            signal(id, s_sleep);
            frame;
            
			lspl_intro = 0;
            switch (g_end_level)
            case 1:     //nivel superado
                if (lspl_lev2 < 3)
                    lspl_lev2++;
					lspl_lev3 = 0;
                else
                    lspl_lev1 = 0;
                    lspl_lev2 = 0;
					lspl_lev3 = 0;
					lspl_intro = 1;
                end
            end
            case 2:     //muerto
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
            end
            case 3:     //salir
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
            end
            end
            //Este debe ser el único proceso que modifique lspl_lev1 y lspl_lev2**************
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
        end
        
        case 3:
            cargar_graficos_enemigos(3,0);
            cargar_sfx_nivel(3);
            
            g_end_level = 0;
            play_level(lspl_lev1, lspl_lev2, lspl_lev3, lspl_intro, 0, &g_end_level);
            signal(id,s_sleep);
            frame;
            
			lspl_intro = 0;
            switch (g_end_level)
            case 1:     //nivel superado
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
				lspl_intro = 1;
            end
            case 2:     //muerto
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
            end
            case 3:     //salir
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
            end
            end
            //Este debe ser el único proceso que modifique lspl_lev1 y lspl_lev2**************
            //Excepción: juego no lineal, es decir, que tenga más de un final de nivel, en ese caso,
            //el item de fin de nivel o subnivel es el encargado de cambiar estas variables para
            //decidir el siguiente nivel.
            //Excepción: evento intermedio para salvar a mitad de camino, que sólo puede modificar
            //lspl_lev2, e incluso no sería necesario.
            
            signal_items(s_kill);
            signal_enemigos(s_kill);
            signal_event_all(s_kill);
            signal_tiles_especiales(s_kill);
            
            unload_all_enem_fpgs();
            
            sound_stop(-1);
            descargar_sfx_nivel(3);
            
            unset_interface();
        end
        case 4:
            cargar_graficos_enemigos(4, lspl_lev2);
            cargar_sfx_nivel(4);
            
            enem_grafs[0][cte_tiles_agua] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/water_tiles04.fpg");
            enem_grafs[1][cte_tiles_agua] = 1;
			
			enem_grafs[0][cte_tiles_lava] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/lava_tiles04.fpg");
            enem_grafs[1][cte_tiles_lava] = 1;
			
            enem_grafs[0][cte_interactive_plaforms] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/interact_platf04.fpg");
            enem_grafs[1][cte_interactive_plaforms] = 1;
            
            g_end_level = 0;
            play_level(lspl_lev1, lspl_lev2, lspl_lev3, lspl_intro, 0, &g_end_level);
            signal(id, s_sleep);
            frame;
            
			lspl_intro = 0;
            switch (g_end_level)
            case 1:     //nivel superado
                if (lspl_lev2 < 1)
                    lspl_lev2++;
					lspl_lev3 = 0;
                else
                    lspl_lev1 = 0;
                    lspl_lev2 = 0;
					lspl_lev3 = 0;
					lspl_intro = 1;
                end
            end
            case 2:     //muerto
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
            end
            case 3:     //salir
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
            end
            end
            //Este debe ser el único proceso que modifique lspl_lev1 y lspl_lev2**************
            //Excepción: juego no lineal, es decir, que tenga más de un final de nivel, en ese caso,
            //el item de fin de nivel o subnivel es el encargado de cambiar estas variables para
            //decidir el siguiente nivel.
            //Excepción: evento intermedio para salvar a mitad de camino, que sólo puede modificar
            //lspl_lev2, e incluso no sería necesario.
            
            signal_items(s_kill);
            signal_enemigos(s_kill);
            signal_event_all(s_kill);
            signal_tiles_especiales(s_kill);
            
            unload_all_enem_fpgs();
            
            sound_stop(-1);
            descargar_sfx_nivel(4);
            
            unset_interface();
        end
		case 5:
            cargar_graficos_enemigos(5, lspl_lev2);
            cargar_sfx_nivel(4);
            
            enem_grafs[0][cte_anim_level] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/cascada01.fpg");
            enem_grafs[1][cte_anim_level] = 1;
            
            enem_grafs[0][cte_tiles_agua] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/water_tiles04.fpg");
            enem_grafs[1][cte_tiles_agua] = 1;
			
            //enem_grafs[0][cte_interactive_plaforms] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/interact_platf04.fpg");
            //enem_grafs[1][cte_interactive_plaforms] = 1;
            
            g_end_level = 0;
            play_level(lspl_lev1, lspl_lev2, lspl_lev3, lspl_intro, 0, &g_end_level);
            signal(id, s_sleep);
            frame;
            
			lspl_intro = 0;
            switch (g_end_level)
            case 1:     //nivel superado
                lspl_lev1 = 0;
				lspl_lev2 = 0;
				lspl_lev3 = 0;
				lspl_intro = 1;
            end
            case 2:     //muerto
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
            end
            case 3:     //salir
                lspl_lev1 = 0;
                lspl_lev2 = 0;
				lspl_lev3 = 0;
            end
            end
            //Este debe ser el único proceso que modifique lspl_lev1 y lspl_lev2**************
            //Excepción: juego no lineal, es decir, que tenga más de un final de nivel, en ese caso,
            //el item de fin de nivel o subnivel es el encargado de cambiar estas variables para
            //decidir el siguiente nivel.
            //Excepción: evento intermedio para salvar a mitad de camino, que sólo puede modificar
            //lspl_lev2, e incluso no sería necesario.
            
            signal_items(s_kill);
            signal_enemigos(s_kill);
            signal_event_all(s_kill);
            signal_tiles_especiales(s_kill);
            
            unload_all_enem_fpgs();
            
            sound_stop(-1);
            descargar_sfx_nivel(4);
            
            unset_interface();
        end
        
        default: break; end
        end //switch
    end //loop principal
    
    unload_interface();
    if (exists(pausa_id)) signal(pausa_id, s_kill); end
    pausa_estado = 0;
    
    fpg_unload(prota_file);
    fpg_unload(armas_file);
    fpg_unload(item_grafs);
	fpg_unload(checkpoint_grafs);
    fpg_unload(explosion_grafs);
    //descarga de sonidos de disparo (si procede)
    descargar_sfx_arma();
    
	global_mode = CTE_GLOBAL_MODE_PORTADA;
    
    signal(father,s_wakeup);
    frame;
end

//**************************************************************************************************
process level_select ()
private
    global_savegame ls_datos_salvados;
    
    //int ls_nivel;
    //int ls_subnivel;
    //int ls_intro;
    //int ls_show_saved;
    int ls_estado_end_level;
    
    int ls_opcion;
begin
    cargar_global_sav(&ls_datos_salvados);
    
    //ZONA DEBUG *******************************************
    /*ls_nivel = 4;
    ls_subnivel = 0;
    ls_intro = 1;
    //ls_intro = 0;
    //ls_show_saved = 0;
    
    armas_select=0; 
    armas_get[0] = 0;
    armas_get[1] = 1;
    armas_get[2] = 1;
    armas_get[3] = 1;
    armas_get[4] = 0;
    info_prota.vidas = 3;
    
    info_prota.p_max_energ = 25;
    info_prota.p_energ = 25;*/
    
    //level_select_play_level (ls_nivel, ls_subnivel, ls_intro,  &ls_estado_end_level);
    //FIN ZONA DEBUG ***************************************
    
	ls_estado_end_level = 0;
    ls_opcion = 1;
    //ZONA VISIBLE DEL MENU ********************************
    while (ls_opcion != 3)
        switch (ls_opcion)
        case 0:
            fade_on(1000);
            while (fade_info.fading) frame; end
            
            fade_off(1000);
            while (fade_info.fading) frame; end
        end
        
        case 1:
            //level_select_play_level (next_level, next_sublevel, 1,  &ls_estado_end_level);
			level_select_play_level();
            signal(id, s_sleep);
            frame;
            
            ls_opcion = 3;
        end
        end //switch
    end //del level select
    
    global_mode = CTE_GLOBAL_MODE_PORTADA;
    
    signal(father, s_wakeup);
    frame;
end
