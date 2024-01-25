process fondo_autoscroll (string fichero, int region, int velx, int vely, int fa_porcentaje_perdida)
//Carga un FPG, y lo usa como fondo de scroll, con movimiento constante. Comprueba los gráficos que existen
//y los va colocando desde el primero hasta que encuentra un gráfico inexistente. Si detecta un gráfico 11,
//lo coloca como fondo de pantalla.
//	fichero:	Nombre del FPG que contiene los gráficos a cargar.
//	region:		Región donde colocar los scrolls.
//	velx:		Velocidad horizontal del primer plano de scroll.
//	vely:		Velocidad vertical del primer plano de scroll.
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
		fa_last_scroll = -1;
		while (map_exists(file, fa_check_map1) && !fa_no_more_maps)
			fa_scroll_flags = 0;
			if (graphic_info(file, fa_check_map1, G_WIDE) != 320) fa_scroll_flags += 1; end
			if (graphic_info(file, fa_check_map1, G_HEIGHT) != 240) fa_scroll_flags += 2; end
			
			fa_last_scroll++;
			if (map_exists(file, fa_check_map1 + 1))
				if (graphic_info(file, fa_check_map1 + 1, G_WIDE) != 320) fa_scroll_flags += 4; end
				if (graphic_info(file, fa_check_map1 + 1, G_HEIGHT) != 240) fa_scroll_flags += 8; end
				
				scroll_start(CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll, file, fa_check_map1, fa_check_map1 + 1,
							region, fa_scroll_flags);
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll].z = 512 + fa_last_scroll;
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll].ratio = 0;
			else
				fa_no_more_maps = 1;
				scroll_start(CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll, file, fa_check_map1, 0, region,
							fa_scroll_flags);
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll].z = 512 + fa_last_scroll;
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll].ratio = 0;
			end
			fa_check_map1 += 2;
		end
		
		if (fa_last_scroll >= 0)
			loop
				scroll[CTE_FIRST_BACKGROUND_SCROLL].x0 += velx;
				scroll[CTE_FIRST_BACKGROUND_SCROLL].y0 += vely;
				scroll[CTE_FIRST_BACKGROUND_SCROLL].x1 = (scroll[CTE_FIRST_BACKGROUND_SCROLL].x0 *
															fa_porcentaje_perdida) / 100;
				scroll[CTE_FIRST_BACKGROUND_SCROLL].y1 = (scroll[CTE_FIRST_BACKGROUND_SCROLL].y0 *
															fa_porcentaje_perdida) / 100;
				
				for (cont = CTE_FIRST_BACKGROUND_SCROLL + 1; cont <= CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll;
					cont++)
					
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
		for (cont = 0; cont <= fa_last_scroll; cont++)
			//say("deteniendo scroll " + cont);
			scroll_stop(CTE_FIRST_BACKGROUND_SCROLL + cont);
		end
		
		//say("End stop fondos");
	end
end

process fondo_followscroll (string fichero, int region, int fa_porcentaje_perdida)
//Carga un FPG, y lo usa como fondo de scroll, siguiendo a la cámara del TScroll. Comprueba los gráficos que
//existen y los va colocando desde el primero hasta que encuentra un gráfico inexistente. Si detecta un gráfico 11,
//lo coloca como fondo de pantalla.
//	fichero:	Nombre del FPG que contiene los gráficos a cargar.
//	region:		Región donde colocar los scrolls.
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
		fa_last_scroll = -1;
		while (map_exists(file, fa_check_map1) && !fa_no_more_maps)
			fa_scroll_flags = 0;
			if (graphic_info(file, fa_check_map1, G_WIDE) != 320) fa_scroll_flags += 1; end
			if (graphic_info(file, fa_check_map1, G_HEIGHT) != 240) fa_scroll_flags += 2; end
			
			fa_last_scroll++;
			if (map_exists(file, fa_check_map1 + 1))
				if (graphic_info(file, fa_check_map1 + 1, G_WIDE) != 320) fa_scroll_flags += 4; end
				if (graphic_info(file, fa_check_map1 + 1, G_HEIGHT) != 240) fa_scroll_flags += 8; end
				
				scroll_start(CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll, file, fa_check_map1, fa_check_map1 + 1,
							region, fa_scroll_flags);
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll].z = 512 + fa_last_scroll;
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll].ratio = 0;
			else
				fa_no_more_maps = 1;
				scroll_start(CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll, file, fa_check_map1, 0, region,
							fa_scroll_flags);
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll].z = 512 + fa_last_scroll;
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll].ratio = 0;
			end
			fa_check_map1 += 2;
		end
		
		if (fa_last_scroll >= 0)
			loop
				//if ((id_tscroll != 0) && exists(id_tscroll))
				scroll[CTE_FIRST_BACKGROUND_SCROLL].x0 = (id_tscroll.camera_x * fa_porcentaje_perdida) / 100;
				scroll[CTE_FIRST_BACKGROUND_SCROLL].y0 = (id_tscroll.camera_y * fa_porcentaje_perdida) / 100;;
				scroll[CTE_FIRST_BACKGROUND_SCROLL].x1 = (scroll[CTE_FIRST_BACKGROUND_SCROLL].x0 *
															fa_porcentaje_perdida) / 100;
				scroll[CTE_FIRST_BACKGROUND_SCROLL].y1 = (scroll[CTE_FIRST_BACKGROUND_SCROLL].y0 *
															fa_porcentaje_perdida) / 100;
				
				for (cont = CTE_FIRST_BACKGROUND_SCROLL + 1; cont <= CTE_FIRST_BACKGROUND_SCROLL + fa_last_scroll;
					cont++)
					
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
		for (cont = 0; cont <= fa_last_scroll; cont++)
			//say("deteniendo scroll " + cont);
			scroll_stop(CTE_FIRST_BACKGROUND_SCROLL + cont);
		end
		
		//say("End stop fondos");
	end
end


process fondo_percentscroll (string fichero, int region, int fp_tam_mapa_pixels_x, int fp_tam_mapa_pixels_y)
//Carga un FPG, y lo usa como fondo de scroll, siguiendo al scroll tileado, pero a una velocidad menor que
//depende del tamaño del mapa del scroll tileado y del mapa cargado. Comprueba los gráficos que existen
//y los va colocando desde el primero hasta que encuentra un gráfico inexistente. Si detecta un gráfico 11,
//lo coloca como fondo de pantalla.
//	fichero:	Nombre del FPG que contiene los gráficos a cargar.
//	region:		Región donde colocar los scrolls.
//	fp_tam_mapa_pixels_x:	Ancho del mapa de tiles en pixels (esta información se puede obtener del TSCROLL)
//	fp_tam_mapa_pixels_y:	Alto del mapa de tiles en pixels (esta información se puede obtener del TSCROLL)
private
	int fp_error;
	int fp_check_map1;
	int fp_no_more_maps;
	int fp_last_scroll;
	//int fp_last_map;
	
	int pointer fp_divisor_velocidad_x;
	int pointer fp_divisor_velocidad_y;
	
	int cont;
	int temp;
begin
	if (fexists(fichero))
		fp_error = 0;
		file = fpg_load(fichero);
		
		//Fixed background
		if (map_exists(file, 11)) put_screen(file, 11); end
		
		//Starting scrolls
		fp_check_map1 = 1;
		fp_no_more_maps = 0;
		fp_last_scroll = -1;
		//fp_last_map = 0;
		while (map_exists(file, fp_check_map1) && !fp_no_more_maps)
			fp_last_scroll++;
			//fp_last_map++;
			if (map_exists(file, fp_check_map1 + 1))
				//fp_last_map++;
				scroll_start(CTE_FIRST_BACKGROUND_SCROLL + fp_last_scroll, file, fp_check_map1, fp_check_map1 + 1,
							region, 0);
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fp_last_scroll].z = 512 + fp_last_scroll;
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fp_last_scroll].ratio = 0;
			else
				fp_no_more_maps = 1;
				scroll_start(CTE_FIRST_BACKGROUND_SCROLL + fp_last_scroll, file, fp_check_map1, 0, region, 0);
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fp_last_scroll].z = 512 + fp_last_scroll;
				scroll[CTE_FIRST_BACKGROUND_SCROLL + fp_last_scroll].ratio = 0;
			end
			fp_check_map1 += 2;
		end
		
		//Creating percent movement data
		//say("creando " + itoa((fp_last_scroll + 1) * 2) + " espacios de memoria.");
		fp_divisor_velocidad_x = alloc((fp_last_scroll + 1) * 2 * sizeof(int));
		fp_divisor_velocidad_y = alloc((fp_last_scroll + 1) * 2 * sizeof(int));
		//Calculating
		for (cont = 0; cont < (fp_last_scroll + 1) * 2; cont++)
			//say("Cont: " + cont);
			temp = graphic_info(file, cont + 1, G_WIDE) - 320;
			if (temp > 0)
				fp_divisor_velocidad_x[cont] = (fp_tam_mapa_pixels_x - 320) / temp;
			else
				fp_divisor_velocidad_x[cont] = 0;
			end
			temp = graphic_info(file, cont + 1, G_HEIGHT) - 240;
			if (temp > 0)
				fp_divisor_velocidad_y[cont] = (fp_tam_mapa_pixels_y - 240) / temp;
			else
				fp_divisor_velocidad_y[cont] = 0;
			end
		end
		
		if (fp_last_scroll >= 0)
			loop
				if (fp_divisor_velocidad_x[0] > 0)
					//say("Scrolleando X0");
					scroll[CTE_FIRST_BACKGROUND_SCROLL].x0 = id_tscroll.camera_x / fp_divisor_velocidad_x[0];
				end
				if (fp_divisor_velocidad_y[0] > 0)
					//say("Scrolleando Y0");
					scroll[CTE_FIRST_BACKGROUND_SCROLL].y0 = id_tscroll.camera_y / fp_divisor_velocidad_y[0];
				end
				if (fp_divisor_velocidad_x[1] > 0)
					//say("Scrolleando X1");
					scroll[CTE_FIRST_BACKGROUND_SCROLL].x1 = id_tscroll.camera_x / fp_divisor_velocidad_x[1];
				end
				if (fp_divisor_velocidad_y[1] > 0)
					//say("Scrolleando Y1");
					scroll[CTE_FIRST_BACKGROUND_SCROLL].y1 = id_tscroll.camera_y / fp_divisor_velocidad_y[1];
				end
				
				for (cont = 1; cont <= fp_last_scroll; cont++)
					if (fp_divisor_velocidad_x[cont * 2] > 0)
						//say("Scrolleando X0 " + itoa(cont * 2));
						scroll[CTE_FIRST_BACKGROUND_SCROLL + cont].x0 = id_tscroll.camera_x /
																		fp_divisor_velocidad_x[cont * 2];
					end
					if (fp_divisor_velocidad_y[cont * 2] > 0)
						//say("Scrolleando Y0 " + itoa(cont * 2));
						scroll[CTE_FIRST_BACKGROUND_SCROLL + cont].y0 = id_tscroll.camera_y /
																		fp_divisor_velocidad_y[cont * 2];
					end
					if (fp_divisor_velocidad_x[(cont * 2) + 1] > 0)
						//say("Scrolleando X1 " + itoa((cont * 2) + 1));
						scroll[CTE_FIRST_BACKGROUND_SCROLL + cont].x1 = id_tscroll.camera_x /
																		fp_divisor_velocidad_x[(cont * 2) + 1];
					end
					if (fp_divisor_velocidad_y[(cont * 2) + 1] > 0)
						//say("Scrolleando Y1 " + itoa((cont * 2) + 1));
						scroll[CTE_FIRST_BACKGROUND_SCROLL + cont].y1 = id_tscroll.camera_y /
																		fp_divisor_velocidad_y[(cont * 2) + 1];
					end
				end
				frame;
			end
		end
		
	else
		fp_error = 1;
	end
onexit
	if (!fp_error)
		fpg_unload(file);
		clear_screen();
		for (cont = 0; cont <= fp_last_scroll; cont++)
			//say("deteniendo scroll " + cont);
			scroll_stop(CTE_FIRST_BACKGROUND_SCROLL + cont);
		end
		free(fp_divisor_velocidad_x);
		free(fp_divisor_velocidad_y);
		
		//say("End stop fondos");
	end
end