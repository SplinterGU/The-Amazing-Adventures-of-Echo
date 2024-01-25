process foreground_autoscroll (string fichero, int region, int velx, int vely, int fa_flags, int fa_porcentaje_perdida)
//Carga un FPG, y lo usa como primer plano de scroll, con movimiento constante. Comprueba los gráficos que existen
//y los va colocando desde el primero hasta que encuentra un gráfico inexistente.
//	fichero:	Nombre del FPG que contiene los gráficos a cargar.
//	region:		Región donde colocar los scrolls.
//	velx:		Velocidad horizontal del primer plano de scroll.
//	vely:		Velocidad vertical del primer plano de scroll.
//	fa_flags:	Flags aplicables a las capas del scroll (sólo válidas 4 (transparencia) y 16 (flag aditivo))
//	fa_porcentaje_perdida:	porcentaje de velocidad que se pierde cada plano de scroll que está más al fondo.
//							50 significa que se pierde la mitad de la velocidad en cada plano de scroll.
//							200 significa que va el doble de rápido que el frente
private
	int fa_error;
	int fa_check_map1;
	int fa_no_more_maps;
	int fa_last_scroll;
	int fa_scroll_flags;
	
	int cont;
begin
	if (fexists(fichero))
		fa_error = 0;
		file = fpg_load(fichero);
		
		//Fixed background
		if (map_exists(file, 11)) put_screen(file, 11); end
		
		//Starting scrolls
		fa_check_map1 = 1;
		fa_no_more_maps = 0;
		fa_last_scroll = CTE_FIRST_FOREGROUND_SCROLL - 1;
		while (map_exists(file, fa_check_map1) && !fa_no_more_maps)
			fa_scroll_flags = 0;
			if (graphic_info(file, fa_check_map1, G_WIDE) != 320) fa_scroll_flags += 1; end
			if (graphic_info(file, fa_check_map1, G_HEIGHT) != 240) fa_scroll_flags += 2; end
			
			fa_last_scroll++;
			if (map_exists(file, fa_check_map1 + 1))
				if (graphic_info(file, fa_check_map1 + 1, G_WIDE) != 320) fa_scroll_flags += 4; end
				if (graphic_info(file, fa_check_map1 + 1, G_HEIGHT) != 240) fa_scroll_flags += 8; end
				
				scroll_start(fa_last_scroll, file, fa_check_map1, fa_check_map1 + 1, region, fa_scroll_flags);
				scroll[fa_last_scroll].z = -4 + fa_last_scroll - CTE_FIRST_FOREGROUND_SCROLL;
				scroll[fa_last_scroll].ratio = 0;
				
				scroll[fa_last_scroll].flags1 = fa_flags;
				scroll[fa_last_scroll].flags2 = fa_flags;
				
			else
				fa_no_more_maps = 1;
				scroll_start(fa_last_scroll, file, fa_check_map1, 0, region, fa_scroll_flags);
				scroll[fa_last_scroll].z = -4 + fa_last_scroll - CTE_FIRST_FOREGROUND_SCROLL;
				scroll[fa_last_scroll].ratio = 0;
				
				scroll[fa_last_scroll].flags1 = fa_flags;
			end
			fa_check_map1 += 2;
		end
		
		if (fa_last_scroll >= 0)
			loop
				scroll[CTE_FIRST_FOREGROUND_SCROLL].x0 += velx;
				scroll[CTE_FIRST_FOREGROUND_SCROLL].y0 += vely;
				scroll[CTE_FIRST_FOREGROUND_SCROLL].x1 = (scroll[0].x0 * fa_porcentaje_perdida) / 100;
				scroll[CTE_FIRST_FOREGROUND_SCROLL].y1 = (scroll[0].y0 * fa_porcentaje_perdida) / 100;
				
				for (cont = CTE_FIRST_FOREGROUND_SCROLL + 1; cont <= fa_last_scroll; cont++)
					scroll[cont].x0 = (scroll[cont - 1].x1 * fa_porcentaje_perdida) / 100;
					scroll[cont].y0 = (scroll[cont - 1].y1 * fa_porcentaje_perdida) / 100;
					scroll[cont].x1 = (scroll[cont].x0 * fa_porcentaje_perdida) / 100;
					scroll[cont].y1 = (scroll[cont].y0 * fa_porcentaje_perdida) / 100;
				end
				frame;
			end
		end
		
	else
		fa_error = 1;
	end
onexit
	if (!fa_error)
		fpg_unload(file);
		clear_screen();
		for (cont = CTE_FIRST_FOREGROUND_SCROLL; cont <= fa_last_scroll; cont++)
			//say("deteniendo scroll " + cont);
			scroll_stop(cont);
		end
		
		//say("End stop fondos");
	end
end
