process event_4_4 ()
private
	int fase_evento;
    int fin_evento;
    int temp;
begin
	//say("Hey!! soy el evento 4-4.");
    //level_song = _CTE_MUSIC_FINALBOSS;
	/*intro_boss_01_3_01();
    x2 = info_prota.id_prota.x2;
    y2 = info_prota.id_prota.y2;
    id_tscroll.id_target = id;
    while ((x2 != 256) || (y2 != 400))
        if (x2 < 256) x2++; end
        if (x2 > 256) x2--; end
        if (y2 < 400) y2++; end
        if (y2 > 400) y2--; end
        frame;
    end*/
    //say("camara movida");
    
    fin_evento = 0;
	energia = 0;
	fase_evento = 0;
    
    //comienza la juerga
    //enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/ghyppo.fpg");
    //enem_grafs[1][cte_event] = 1;
    //temp = ghyppo(enem_grafs[0][cte_event]);
    //enem_ener_interface(temp);
    
    //while (temp.alpha < 255) frame; end     //esperamos a que aparezca
    
    while (!fin_evento)
		if (teclas[k_next][2] == 1) energia++; end
		
		if (energia != fase_evento)
			say("Cambiando a fase " + fase_evento + 1);
			fase_evento++;
			energia = fase_evento;
			boss0404_modificar_escenario(fase_evento);
		end
		frame;
	end
    
    //fin de la juerga
    level_song = 0;
    if (exists(info_prota.id_prota))
        prota_control = 0;
		//Se mueve la cámara hacia el jefe que se muere
		
		//volvemos a mover la cámara hasta el prota
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
    
    //fpg_unload(enem_grafs[0][cte_event]);
    //enem_grafs[1][cte_event] = 0;
end