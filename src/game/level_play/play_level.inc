process play_level (int pl_lev1, int pl_lev2, int pl_lev3, int pl_intro,
					int pl_show_saved, int pointer pl_return_end_level)
// pl_lev1:     nivel de juego (episodio)
// pl_lev2:     subnivel (capítulo)
// pl_lev3:		punto de inicio (checkpoint)
// pl_intro:    si vale 1, iniciar presentación antes del nivel
private
    int pl_loaded;
    //int init_level;
    int id_sync;
	int id_background;
	int id_foreground;
begin
	say("Jugando nivel " + pl_lev1 + "-" + pl_lev2 + "-" + pl_lev3);
    switch (pl_lev1)
    case 1:
        //indicación de gráficos de los objetos que se mueven al activar botones
        obj_interruptor[cte_door] = 41;
        obj_interruptor[cte_bridge] = 40;
        
        set_interface();
        refresh_interface();
        
        //carga del mapa y del entorno
        pl_loaded = 0;
        switch (pl_lev2)
        case 0:
            if (load_tmf(dreamcast_ruta + "levels/lvl1_0_castlehorror.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl1_0_castlehorror_x2.tmf", &nivel) )
                
                pl_loaded = 1;
                //game_draw_background(1);
            end
        end
        case 1:
            if (load_tmf(dreamcast_ruta + "levels/lvl1_1_castlehorror.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl1_1_castlehorror.tmf", &nivel) )
                
                pl_loaded = 1;
                //map_clear(background.file, background.graph, rgb(0, 0, 0));
            end
        end
        case 2:
            if (load_tmf(dreamcast_ruta + "levels/lvl1_2_castlehorror.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl1_2_castlehorror.tmf", &nivel) )
                
                pl_loaded = 1;
                //game_draw_background(1);
            end
        end
        case 3:
            if (load_tmf(dreamcast_ruta + "levels/lvl1_3_castlehorror.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl1_3_castlehorror.tmf", &nivel) )
                
                pl_loaded = 1;
                //map_clear(background.file, background.graph,rgb(0, 0, 0));
            end
        end
        default: pl_loaded = 0; end
        end //switch
        
        if (pl_loaded)
            borrar_items_conseguidos(pl_lev1, pl_lev2, &nivel);
        end
    end
    case 3:
        //indicación de gráficos de los objetos que se mueven al activar botones
        obj_interruptor[cte_door] = 60;
        obj_interruptor[cte_bridge] = 62;
        
        set_interface();
        refresh_interface();
        
        //carga del mapa y del entorno
        pl_loaded = 0;
        if ((pl_lev2 <= 2) &&
            load_tmf(dreamcast_ruta + "levels/lvl3_city.dur.tmf", &durezas) &&
            load_tmf(dreamcast_ruta + "levels/lvl3_city.tmf", &nivel)     )
        
            pl_loaded = 1;
            //map_clear(background.file, background.graph, rgb(255, 96, 0));
            
            borrar_items_conseguidos(pl_lev1, pl_lev2, &nivel);
        else
            pl_loaded = 0;
        end
    end
    case 4:
        //indicación de gráficos de los objetos que se mueven al activar botones
        obj_interruptor[cte_door] = 98;
        obj_interruptor[cte_bridge] = 97;
        
        set_interface();
        refresh_interface();
        
        //carga del mapa y del entorno
        pl_loaded = 0;
        switch (pl_lev2)
        case 0:
            if (load_tmf(dreamcast_ruta + "levels/lvl4_1_egyptianlegend.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl4_1_egyptianlegend.tmf", &nivel) )
                
                pl_loaded = 1;
                //map_clear(background.file, background.graph, rgb(184, 255, 235));
                
                borrar_items_conseguidos(pl_lev1, pl_lev2, &nivel);
            end
        end
		case 1:
            if (load_tmf(dreamcast_ruta + "levels/lvl4_2_egyptianlegend.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl4_2_egyptianlegend.tmf", &nivel) )
                
                pl_loaded = 1;
                //map_clear(background.file, background.graph, rgb(184, 255, 235));
                
                borrar_items_conseguidos(pl_lev1, pl_lev2, &nivel);
            end
        end
		case 2:
			if (load_tmf(dreamcast_ruta + "levels/lvl4_3_egyptianlegend.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl4_3_egyptianlegend.tmf", &nivel) )
                
                pl_loaded = 1;
                //map_clear(background.file, background.graph, rgb(184, 255, 235));
                
                borrar_items_conseguidos(pl_lev1, pl_lev2, &nivel);
            end
		end
		case 3:
			if (load_tmf(dreamcast_ruta + "levels/lvl4_4_egyptianlegend.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl4_4_egyptianlegend.tmf", &nivel) )
                
                pl_loaded = 1;
                //map_clear(background.file, background.graph, rgb(184, 255, 235));
                
                borrar_items_conseguidos(pl_lev1, pl_lev2, &nivel);
            end
		end
        default:
            pl_loaded = 0;
        end
        end //switch
    end
	case 5:
		//indicación de gráficos de los objetos que se mueven al activar botones
        obj_interruptor[cte_door] = 98;
        obj_interruptor[cte_bridge] = 97;
        
        set_interface();
        refresh_interface();
        
        //carga del mapa y del entorno
        pl_loaded = 0;
		switch (pl_lev2)
        case 0:
            if (load_tmf(dreamcast_ruta + "levels/lvl5_caves.dur.tmf", &durezas) &&
                load_tmf(dreamcast_ruta + "levels/lvl5_caves.tmf", &nivel) )
            /*if (load_tmf("D:/Fenix/Proyectos/Tileador/Echo3/lvl4_2c_atlantida.dur.tmf",&durezas) &&
                load_tmf("D:/Fenix/Proyectos/Tileador/Echo3/lvl4_2c_atlantida.tmf",&nivel) )*/
                
                pl_loaded = 1;
                //map_clear(background.file, background.graph, rgb(0, 0, 0));
                
				borrar_items_conseguidos(pl_lev1, pl_lev2, &nivel);
                //borrar_items_conseguidos(pl_lev1, 1, &nivel);
                //borrar_items_conseguidos(pl_lev1, 2, &nivel);
                //borrar_items_conseguidos(pl_lev1, 3, &nivel);
            end
        end
        default:
            pl_loaded = 0;
        end
        end //switch
	end
    end //switch
    
    if (pl_loaded)
        //borramos los items ya conseguidos (esto se hace por mapa, porque algunos se dividen en subniveles)
        //borrar_items_conseguidos(pl_lev1,pl_lev2,&nivel);
        //optimizamos los tiles de agua
        //add_tiles_agua (&nivel,&durezas);
        //seguimos la ejecución normal
        start_tscroll(&id_tscroll, &nivel, 0, 0, 0, 320, 240, 4, 4, 16, 16, 0);
        switch (pl_lev1)
            case 1:
                id_tscroll.ts_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level01.fpg");
                //init_level = 0;
            end
            case 3:
                id_tscroll.ts_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level03.fpg");
                //init_level = pl_lev3;
            end
            case 4:
                switch (pl_lev2)
                    case 0:
                        id_tscroll.ts_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level04_1.fpg");
                        //init_level = 0;
                    end
        			case 1:
                        id_tscroll.ts_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level04_1.fpg");
                        //init_level = 0;
                    end
        			case 2:
        				id_tscroll.ts_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level04_3.fpg");
        			end
        			case 3:
        				id_tscroll.ts_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level04_4.fpg");
        			end
                end //switch
                //init_level = pl_lev2;
            end
    		case 5:
    			id_tscroll.ts_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level05.fpg");
    		end
        end //switch
		
		//Lineas para ejecutar el scroll tileado a base de un gráfico sobre el scroll de Bennu
		/*scroll[0].z = -1;
        start_graph_tscroll(&id_tscroll, &nivel, 0, 0, 0, 320, 240, 4, 4, 16, 16, 0, 1, 0);*/
		//************************************************************************************
        ts_actualiza_tiles(&id_tscroll);
        
        if (search_start_point(&nivel, &durezas, pl_lev3, &x2, &y2))
            //modificar_tile(&nivel, x2, y2, 0, 0);     //no es necesario, basta con borrar el tile del fpg
            borrar_tile_de_todo_el_mapa(&nivel, 100);
            
            //Se optimiza el mapa con tiles más grandes
            optimice_map (&nivel, pl_lev1, pl_lev2, id_tscroll.ts_file);
            
            ts_actualiza_tiles(&id_tscroll);
            id_tscroll.id_target = prota(x2, y2);
            //id_tscroll.id_target = prota_moto(x2, y2);
            
			//Musica
            switch (pl_lev1)
                case 1,3:
                    level_song = pl_lev1;
                end
                case 4:
                    switch (pl_lev2)
                        //case 1..3: level_song = _CTE_MUSIC_LEVEL04_2; end
                    end //switch
                end
                case 5:
				    level_song = _CTE_MUSIC_LEVEL04_2;
                end
                default:
                    level_song = pl_lev1;
                end
            end //switch
			
			//fondos
			if (game_background_scroll)
				region_define(CTE_REGION_FONDOS, 0, 0, 320, 240);
				switch (pl_lev1)
    				case 1:
    					switch (pl_lev2)
        					case 0,2:
                                id_background = fondo_autoscroll(dreamcast_ruta + "grafs/" + graph_dir + "/level0101bg.fpg", CTE_REGION_FONDOS, -2, 0, 50);
        					end
        					case 1:
                                id_background = fondo_followscroll(dreamcast_ruta + "grafs/" + graph_dir + "/level0102bg.fpg", CTE_REGION_FONDOS, 50);
        					end
        					case 3:
                                id_background = fondo_followscroll(dreamcast_ruta + "grafs/" + graph_dir + "/level0104bg.fpg", CTE_REGION_FONDOS, 50);
        					end
    					end //switch
    				end
    				case 3:
    					id_background = fondo_percentscroll(dreamcast_ruta + "grafs/" + graph_dir + "/level0301bg.fpg", CTE_REGION_FONDOS, id_tscroll.ancho_mapa, id_tscroll.alto_mapa);
    				end
    				case 4:
    					switch (pl_lev2)
    					    case 0:
                                map_clear(background.file, background.graph, rgb(184, 255, 235));
                            end
    					    default:
                                map_clear(background.file, background.graph, rgb(0, 0, 0));
                            end
    					end //switch
    				end
    				case 5:
    					id_background = fondo_percentscroll(dreamcast_ruta + "grafs/" + graph_dir + "/level0402bg.fpg", CTE_REGION_FONDOS, id_tscroll.ancho_mapa, id_tscroll.alto_mapa);
    				end
    			end //switch
			else
				switch (pl_lev1)
    				case 1:
    					switch (pl_lev2)
    					    case 0,2:
                                game_draw_background(1);
                            end
    					    default:
                                map_clear(background.file, background.graph, rgb(0, 0, 0));
                            end
    					end //switch
    				end
    				case 3:
    					map_clear(background.file, background.graph, rgb(255, 96, 0));
    				end
    				case 4:
    					switch (pl_lev2)
    					    case 0:
                                map_clear(background.file, background.graph, rgb(184, 255, 235));
                            end
    					    default:
                                map_clear(background.file, background.graph, rgb(0, 0, 0));
                            end
    					end //switch
    				end
    				case 5:
    					map_clear(background.file, background.graph, rgb(0, 0, 0));
    				end
				end //switch
			end
			
			if (game_foreground_scroll)
				region_define(CTE_REGION_FONDOS, 0, 0, 320, 240);
				switch (pl_lev1)
    				case 1:
    					switch (pl_lev2)
        					case 0,1,2:
        						id_foreground = foreground_autoscroll (dreamcast_ruta + "grafs/" + graph_dir + "/level01fg.fpg", CTE_REGION_FONDOS, 1, 0, 16 + 4, 50);
        					end
    					end //switch
    				end
				end //switch
			end
            
            //say("next sublevel: "+itoa(next_sublevel));

            if (pl_intro)
                //evento de presentación de nivel
                switch (pl_lev1)
                case 1: intro_nivel(1); end
                case 3: intro_nivel(2); end
                case 4: intro_nivel(3); end
				case 5: intro_nivel(3); end
                end //switch
                signal(id, s_freeze);
                frame;
            else
                fade_on(300);
                while (fade_info.fading); frame; end
            end

            if (pl_show_saved) game_saved_graph(); end
            
            prota_control = 1;
            pausa_estado = 1;
        else
            say("error: no hay inicio");
        end
        
        id_sync = sync_counter();
        end_level = 0;
        while (end_level == 0)
            /*if (teclas[k_esc][2]==1)
                end_level=3;
                global_mode=100;
            end
            if (key(_f12))
                end_level=3;
            end*/
            frame;
        end

        fpg_unload(id_tscroll.ts_file);
        stop_tscroll(&id_tscroll);
        if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_kill_tree); end
        if (exists(id_sync)) signal(id_sync, s_kill); end
		if ((id_background != 0) && exists(id_background))
			signal(id_background, s_kill);
			id_background = 0;
		end
		if ((id_foreground != 0) && exists(id_foreground))
			signal(id_foreground, s_kill);
			id_foreground = 0;
		end
        //signal_tiles_especiales(s_kill);
        //unload_tmf**********************************************************************
        //unload_tmf**********************************************************************
    else
        say("no se encuentra el mapa");
        end_level = 3;
    end
    
    //return (end_level); //0: jugando 1: ganas 2: mueres 3: salir
    *pl_return_end_level = end_level;
    signal(father,s_wakeup);
    frame;
end