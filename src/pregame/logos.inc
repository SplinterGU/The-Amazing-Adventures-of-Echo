process logos_putlogo (string lp_logo)
private
	int temp;
	int cont;
begin
	temp = map_load(lp_logo);
	//center_set(0, temp, graphic_info(0, temp, G_WIDTH) / 2, graphic_info(0, temp, G_HEIGHT) / 2);
    put_screen(0, temp);
	//put(0, temp, graphic_info(0, temp, G_WIDTH) / 2, graphic_info(0, temp, G_HEIGHT) / 2);
    fade_on(300);
    while (fade_info.fading) frame; end
	
    for (cont = 0; cont < 150; cont++)
        if ((teclas[k_enter][2] == 1)  || (teclas[k_fire][2] == 1))
            if (fexists(get_pref_path("bennugd.org", "echo") + "echo.sav")) break; end
        end
        frame;
    end
    fade_off(300);
    while (fade_info.fading) frame; end
    map_unload(0, temp);
	
	signal(father, s_wakeup);
end

process logos ()
private
    int temp;
    int cont;
begin
    fade_off(0);
    
    /*logos_putlogo(dreamcast_ruta + "grafs/geca_concurso.png");
	signal(id, s_sleep);
	frame;*/
	
    logos_putlogo(dreamcast_ruta + "grafs/gph.png");
	signal(id, s_sleep);
	frame;
	
    logos_putlogo(dreamcast_ruta + "grafs/bennugd.png");
	signal(id, s_sleep);
	frame;
    
    logos_putlogo(dreamcast_ruta + "grafs/jpc.png");
	signal(id, s_sleep);
	frame;
    
    signal(father,s_wakeup);
end