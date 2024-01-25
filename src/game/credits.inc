//************************************************************************************
//      CRÉDITOS
//************************************************************************************

process credits_img (x2, y, file, graph, alpha)
private
    int cont;
begin
    x = -320;
    cont = 0;
    while (x < x2)
        x += 10;
        cont++;
        if ((cont == 8) && (alpha >= 150))
            credits_img(x2, y, file, graph, alpha-50);
        end
        frame;
    end
	
    frame(20000);
	
    while (x < 330)
        x += 10;
        frame;
    end
end

process credits_img2 (file, graph, x, y, z)
begin
    signal(id, s_freeze);
    frame;
end

process credits ()
private
	int file2;
    int temp, temp2;
	int cont;
begin
	file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/names.fpg");
	file2 = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/names2.fpg");
    //enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/names.fpg");
    //enem_grafs[1][cte_event] = 1;
    
    clear_screen();
//    fade(100, 100, 100, 255);
    frame;
    
    //musica
    level_song = _CTE_MUSIC_CREDITS;
    
    frame(20000);
    //dirigido por
    credits_img(30, 100, file, 1, 255);
    frame(2500);
    temp=credits_img(20, 140, file, 9, 255);
    while (exists(temp)) frame; end
    
    //programado por
    credits_img(30, 100, file, 2, 255);
    frame(2500);
    temp = credits_img(20, 140, file, 9, 255);
    while (exists(temp)) frame; end
    
    //musica por
    credits_img(30, 100, file, 3, 255);
    frame(2500);
    credits_img(20, 140, file, 10, 255);
    frame(1000);
    temp = credits_img(20, 170, file, 9, 255);
    while (exists(temp)) frame; end
    
    //efectos sonoros
    credits_img(30, 100, file, 4, 255);
    frame(2500);
    credits_img(20, 140, file, 10, 255);
    frame(1000);
    temp = credits_img(20, 170, file, 9, 255);
    while (exists(temp)) frame; end
    
    //gráficos por
    credits_img(30, 100, file, 5, 255);
    frame(2500);
    credits_img(20, 160, file, 19, 255);
    frame(1000);
    temp = credits_img(20, 190, file, 9, 255);
    while (exists(temp)) frame; end
    
    //diseño de niveles
    credits_img(30, 100, file, 6, 255);
    frame(2500);
    temp = credits_img(20, 140, file, 9, 255);
    while (exists(temp)) frame; end
    
    //programación adicional
    credits_img(30, 80, file, 7, 255);
    frame(2500);
    credits_img(20, 120, file, 11, 255);
    frame(1000);
    credits_img(20, 150, file, 12, 255);
    frame(1000);
    credits_img(20, 180, file, 13, 255);
    frame(1000);
    temp = credits_img(20, 210, file, 14, 255);
    while (exists(temp)) frame; end
    
    //gracias
    credits_img(30, 80, file, 8, 255);
    frame(2500);
	credits_img(20, 120, file, 15, 255);
    frame(1000);
	credits_img(20, 150, file, 14, 255);
    frame(1000);
	credits_img(20, 180, file, 13, 255);
    frame(1000);
	temp = credits_img(20, 210, file, 10, 255);
	cont = 0;
    while (exists(temp))
		//say("Ultimo proceso: " + temp + ",    " + cont);
		//cont++;
		frame;
	end
    
    //gracias
    credits_img(30, 80, file, 8, 255);
    frame(2500);
	credits_img(20, 120, file, 12, 255);
    frame(1000);
	credits_img(20, 150, file, 11, 255);
    frame(1000);
	credits_img(20, 180, file, 16, 255);
    frame(1000);
	temp = credits_img(20, 210, file, 17, 255);
    while (exists(temp)) frame; end
    
	//final
    frame(10000);
    temp = credits_img2(file2, 1, 319, 0, 0);
    temp.alpha = 0;
//    alpha_steps = 64;
    for (temp.alpha = 0; temp.alpha < 255; temp.alpha++) frame; end
    //frame(10000);
	while (level_song == _CTE_MUSIC_CREDITS) frame; end
    
	level_song = _CTE_MUSIC_THE_END;
    //put_screen(file, 18);
	put(file2, 2, graphic_info(file, 18, G_WIDTH) / 2, graphic_info(file, 18, G_HEIGHT) / 2);
    //temp.resolution = 10;
    //temp.x *= 10;
    //temp.y *= 10;
    //temp.graph = 0;
    while (temp.size > 50)
        temp.size--;
        //temp.x += (2700 - temp.x) / 75;
        //temp.y += (500 - temp.y) / 75;
        frame(200);
    end
    
    
    //debug
    frame(30000);
	temp2 = credits_img2(file2, 3, 319, 239, 0);
	temp2.alpha = 0;
	temp2.flags = B_ABLEND;
	for (temp2.alpha = 0; temp2.alpha < 255; temp2.alpha++) frame; end
//	alpha_steps = 16;
	
	while( level_song == _CTE_MUSIC_THE_END && teclas[k_enter][2] != 1 && teclas[k_jump][2] != 1 && teclas[k_fire][2] != 1 )
		frame;
	end
    
    set_fps(20, cte_frameskip);
//    fade(0, 0, 0, 1);
//    while (fade_info.fading) frame; end
	
    clear_screen();
    if (exists(temp)) signal(temp, s_kill); end
    set_fps(50, cte_frameskip);
    
    prota_control = 1;
    fpg_unload(file);
	fpg_unload(file2);
    //enem_grafs[1][cte_event] = 0;
    global_mode = CTE_GLOBAL_MODE_PORTADA;
    signal(father, s_wakeup);
    frame;
end
