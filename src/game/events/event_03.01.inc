process event_3_1 (x2, y2)
private
    //int x3, y3;
    //int contx, conty;
    //int array_naves[9][6];
    //int array_grafs[6] = 3,1,2,3,2,1,2;
    
    //int vel_horiz;
    //int cont_naves;     //cuenta las naves de la ultima fila
    //int event_filas;    //indica cual es la última fila de naves vivas
    
    //int cont_disp, cont_nave_disp;
    
    //int fin_evento;
	int temp;
begin
    modificar_tile(&nivel, x2, y2, 0, 0);
	if (init_level < 3)
		modificar_tile(&durezas, 231, 14, 0, 1);
		modificar_tile(&durezas, 231, 13, 0, 1);
		modificar_tile(&durezas, 231, 12, 0, 1);
		modificar_tile(&durezas, 231, 11, 0, 1);
		modificar_tile(&durezas, 210, 14, 0, 1);
		modificar_tile(&durezas, 210, 13, 0, 1);
		modificar_tile(&durezas, 210, 12, 0, 1);
		modificar_tile(&durezas, 210, 11, 0, 1);
		
		level_song = _CTE_MUSIC_MIDBOSS;
		x2 = info_prota.id_prota.x2;
		y2 = info_prota.id_prota.y2;
		id_tscroll.id_target = id;
		while ((x2 != 3536) || (y2 != 144))
			if (x2 < 3536) x2++; end
			if (x2 > 3536) x2--; end
			if (y2 < 144) y2++; end
			if (y2 > 144) y2--; end
			frame;
		end
		
		signal_enemigos(s_kill);
		
		enem_grafs[0][cte_event] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/ships.fpg");
		enem_grafs[1][cte_event] = 1;
		
		
		temp = space_invaders();
		while (exists(temp)) frame; end
		
		//while (get_id(type disparonave)) frame; end
		
		level_song = next_level;
		if (exists(info_prota.id_prota))
			prota_control = 0;
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
		modificar_tile(&durezas, 231, 14, 0, 0);
		modificar_tile(&durezas, 231, 13, 0, 0);
		modificar_tile(&durezas, 231, 12, 0, 0);
		modificar_tile(&durezas, 231, 11, 0, 0);
		modificar_tile(&durezas, 210, 14, 0, 0);
		modificar_tile(&durezas, 210, 13, 0, 0);
		modificar_tile(&durezas, 210, 12, 0, 0);
		modificar_tile(&durezas, 210, 11, 0, 0);
		
		fpg_unload(enem_grafs[0][cte_event]);
		enem_grafs[1][cte_event] = 0;
	end
end