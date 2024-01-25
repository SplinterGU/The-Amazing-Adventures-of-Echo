process item_checkpoint (x3,y3)
//Objeto checkpoint
private
	int ic_cogido;
	int ic_flags;
	
    savegame_item_got iae_item;
    int hijos;
    int temp1, temp2;
    int cont;
	int cont_anim;
begin
    priority = -99;
    file = checkpoint_grafs;
    graph = 1;
    
    modificar_tile(&nivel, x3, y3, 0, 0);
    x2 = (x3 * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (y3 * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    
	hijos = 0;
    loop
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        if (exists(info_prota.id_prota))
            //if ( (collision(info_prota.id_prota)) && (teclas[k_down][2]==1) )
            if ( (abs(info_prota.id_prota.x - x) < 6) && (abs(info_prota.id_prota.y - y) < 10) )
				if ((hijos == 0) || (!exists(hijos)))
					hijos = item_press_down (x2, y2 - 16);
				end
				
				if (teclas[k_down][2] == 1)
					ic_cogido = 1;
					init_level = obtener_tile(&durezas, x3, y3, 0) - 150;
				end
			else
				if ((hijos != 0) && (exists(hijos)))
					signal(hijos, s_kill);
					hijos = 0;
				end
            end
        end
		
		//Si sale de pantalla, se vuelve a colocar en el mapa
        if ((x < -40) || (x > 360) || (y < -40) || (y > 280)) break; end
		
		//Zona de gráficos
		cont_anim++;
		if (cont_anim >= 7) cont_anim = 0; end
		if (cont_anim < 4) graph = 1;
		else graph = 2; end
		if (ic_cogido) graph += 2; end
		if (info_prota.id_prota.x > x) graph += 4; end
        frame;
    end
	
	if ((hijos != 0) && (exists(hijos)))
		signal(hijos, s_kill);
		hijos = 0;
	end
	
	modificar_tile(&nivel, x3, y3, 0, 254);
    
    /*graph = 0;
    //pausamos todo
    prota_control = 0;
	pausa_estado = 0;
    signal(info_prota.id_prota, s_freeze_tree);
    signal_moving_items(s_freeze);
    signal_enemigos(s_freeze);
    signal_sync(s_freeze);
    signal_tiles_especiales(s_freeze);
    
    //say("pausado");
    //fanfarria
    for (cont = global_vol; cont >= 0; cont -= 2) music_set_volume(cont); frame; end
    music_pause();
    
    //say("musica fuera");
    enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/eget.fpg");
    enem_grafs[1][cte_event] = 1;
    
    //say("graf cargado");
    temp1 = sound_load(dreamcast_ruta + "music/ener_fanfare.wav");
    temp2 = sound_play(temp1, 0);
    
    //say("sonando musica");
    file = 0;
    graph = map_new(320, 50);
    map_clear(file, graph, rgb(0,0,0));
    x = 480;
    y = 120;
    z = -100;
    size_y = 16;
    for (x = 480; x > 160; x -= 10) frame; end
    for (size_y = 16; size_y < 100; size_y += 6)
        //say("contador 1: "+itoa((255*size_y)/100));
        map_clear(file, graph, rgb((255 * size_y) / 100, (255 * size_y) / 100, (255 * size_y) / 100) );
        frame;
    end
    size_y = 100;
    for (cont = 255; cont > 0; cont -= 18)
        //say("contador 2: "+itoa(cont));
        map_clear(file, graph, rgb(cont, cont, cont) );
        frame;
    end
    map_clear(file, graph, rgb(0,0,0));
    
    hijos = items_image(enem_grafs[0][cte_event], 1, 320, 98, -101, 100, 0);
    for (hijos.x = 320; hijos.x > -853; hijos.x -= 10) frame; end
    
    while (sound_is_playing(temp2)) frame; end
    sound_unload(temp1);
    signal(hijos, s_kill);
    
    frame(5000);
    
    for (size_y = 100; size_y > 0; size_y -= 6)
        map_clear(file, graph, rgb((255 * size_y) / 100,(255 * size_y) / 100,(255 * size_y) / 100) );
        frame;
    end
    map_unload(file, graph);
    
    music_resume();
    for (cont = 0; cont <= global_vol; cont += 2) music_set_volume(cont); frame; end
    //aumentamos energía
    info_prota.p_max_energ += 2;
    info_prota.p_energ += 2;
    refresh_interface_energy();
    //añadimos a lista de items conseguidos
    iae_item.level = next_level;
    iae_item.sublevel = next_sublevel;
    iae_item.pos_x = x3;
    iae_item.pos_y = y3;
    iae_item.item = 225;
    savegame_item_got_list_add(iae_item);
    //quitamos pausa
    fpg_unload(enem_grafs[0][cte_event]);
    enem_grafs[1][cte_event] = 0;
    
    prota_control = 1;
    signal(info_prota.id_prota, s_wakeup_tree);
    signal_moving_items(s_wakeup);
    signal_enemigos(s_wakeup);
    signal_sync(s_wakeup);
    signal_tiles_especiales(s_wakeup);
	pausa_estado = 1;*/
end
