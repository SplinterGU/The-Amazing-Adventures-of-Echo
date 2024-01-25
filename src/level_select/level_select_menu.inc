//***********************************************************************************************
//	FUNCIONES
//***********************************************************************************************
function int lsm_get_chapters (int lsm_episode)
private
	int dato_a_devolver;
begin
	switch (lsm_episode)
	case 1:	dato_a_devolver = 4; end
	case 2:	dato_a_devolver = -1; end
	case 3:	dato_a_devolver = 1; end
	case 4:	dato_a_devolver = 2; end
	default: dato_a_devolver = -1; end
	end //switch
	//say("El episodio " + lsm_episode + " tiene " + dato_a_devolver + " capitulos");
	return dato_a_devolver;
end

function int lsm_get_checkpoints (int lsm_episode, int lsm_chapter)
private
	int dato_a_devolver;
begin
	switch (lsm_episode)
	case 1:
		switch (lsm_chapter)
		case 1: dato_a_devolver = 2; end
		case 2: dato_a_devolver = 5; end
		case 3: dato_a_devolver = 6; end
		case 4: dato_a_devolver = 5; end
		end
	end
	case 3:	dato_a_devolver = 9; end
	case 4:	
		switch (lsm_chapter)
		case 1:	dato_a_devolver = 0; end
		case 2: dato_a_devolver = 2; end
		end //switch
	end
	default: dato_a_devolver = -1; end
	end //switch
	//say("El episodio " + lsm_episode + ", capítulo " + lsm_chapter + " tiene " + dato_a_devolver + " checkpoints");
	return dato_a_devolver;
end

//***********************************************************************************************
//	CURSORES
//***********************************************************************************************
process lsm_image (file, graph, x, y, z)
begin
	signal(id, s_freeze);
	frame;
end

//***********************************************************************************************
//	MAIN
//***********************************************************************************************

process level_select_menu ()
private
	int ls_file;
	int ls_text_labels[5];
	int ls_text_values[2];
	int ls_image_id[8];
	int ls_cursor_id[2];
	//ID procesos de capitulos
	int ls_chapter_label_id;
	int ls_episode_name_id[2];
	int ls_chapter_screenshot_id[3];
	
	//Variables de opciones elegidas
	global_savegame ls_global_savegame;
	int ls_energias;
	int ls_max_energias;
	int ls_energia_final;
	int ls_max_energia_final;
	int ls_armas_elegidas;
	int ls_vidas;
	int ls_level_selected[2];
	
	//Variables del menú
	int ls_ver_chapter_label;
	int ls_jugar;
	
	int ls_opcion1;
	int ls_opcion_armas;
	int ls_opcion_episodio;
	
	int temp;
	int cont;
begin
	ls_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level_select_menu.fpg");
	cargar_global_sav(&ls_global_savegame);
	ls_max_energias = ls_global_savegame.items_energia;
	ls_max_energia_final = 10 + (ls_max_energias * 2);
	
	ls_text_labels[0] = write(0, 20, 5, 0, "MAX ENERGY:");
	ls_text_values[0] = write_var(0, 101, 5, 0, ls_max_energia_final);
	ls_image_id[0] = lsm_image(ls_file, 12,
								80 + 1 + (230 * (10 + (ls_global_savegame.items_energia * 2)) /
												(10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
								16, -1);
	
	ls_text_labels[1] = write(0, 20, 20, 0, "ENERGY:");
	drawing_map(0,0);
	drawing_color(rgb(255,255,255));
	/*say(ls_global_savegame.items_energia + "/" + _CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA);
	say(itoa(240 * (10 + (ls_global_savegame.items_energia * 2)) /
							(10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))) + "/78");*/
	draw_rectangle(78,17,
				   /*78 +*/ 4 + (230 * (10 + (ls_global_savegame.items_energia * 2)) /
							(10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
				   30-17);
	draw_rectangle(79,18,
				   /*79 +*/ 2 + (230 * (10 + (ls_global_savegame.items_energia * 2)) /
							(10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
				   29-18);
	ls_energias = ls_global_savegame.items_energia;	//ls_energias valdrá el número de items de energia seleccionados
	ls_energia_final = 10 + (ls_energias * 2);
	ls_text_values[1] = write_var(0, 90, 20, 0, ls_energia_final);
	//ls_image_id[0] = lsm_image(ls_file, 11, 80, 4, -1);
	//ls_image_id[0].size_x = 100 + (ls_energias * 20);
	drawing_color(rgb(255,0,0));
	draw_rectangle_filled(80,19,
				          /*80 +*/ (230 * (10 + (ls_energias * 2)) / (10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
				          28-19);
	//Energia mínima: 10	energia máxima: 64		energia item: 2
	ls_text_labels[2] = write(0, 20, 35, 0, "WEAPONS:");
	if ((ls_global_savegame.armas_desbloqueadas & CTE_GS_DESBLOQUEO_BLUE_STAR) == CTE_GS_DESBLOQUEO_BLUE_STAR)
		ls_image_id[1] = lsm_image(ls_file, 21, 90, 35, -1);
		ls_image_id[1].flags = 4;
	end
	if ((ls_global_savegame.armas_desbloqueadas & CTE_GS_DESBLOQUEO_LEAF_BLADE) == CTE_GS_DESBLOQUEO_LEAF_BLADE)
		ls_image_id[2] = lsm_image(ls_file, 22, 112, 35, -1);
		ls_image_id[2].flags = 4;
	end
	if ((ls_global_savegame.armas_desbloqueadas & CTE_GS_DESBLOQUEO_GREEN_CAT) == CTE_GS_DESBLOQUEO_GREEN_CAT)
		ls_image_id[3] = lsm_image(ls_file, 23, 134, 35, -1);
		ls_image_id[3].flags = 4;
	end
	ls_text_labels[3] = write(0, 20, 60, 0, "LIVES:");
	ls_text_values[2] = write_var(0, 90, 60, 0, ls_vidas);
	//write(0, 20, 10, 0, "EPISODE:");
	ls_image_id[4] = lsm_image(ls_file, 31, 0, 115, -1);
	ls_image_id[5] = lsm_image(ls_file, 101, 199, 103, -3);
	ls_image_id[6] = lsm_image(ls_file, 101, 234, 103, -3);
	ls_image_id[7] = lsm_image(ls_file, 101, 269, 103, -3);
	
	ls_text_labels[4] = write(0, 80, 237, 7, "PLAY");
	ls_text_labels[5] = write(0, 240, 237, 7, "CANCEL");
	ls_image_id[8] = lsm_image(ls_file, 0, 0, 239, -1);
	
	ls_chapter_label_id = lsm_chapter_label(ls_file, 32, &ls_ver_chapter_label);
	ls_episode_name_id[0] = lsm_episode_name (ls_file, 51, &(ls_level_selected[0]), 1);
	ls_episode_name_id[1] = lsm_episode_name (ls_file, 53, &(ls_level_selected[0]), 3);
	ls_episode_name_id[2] = lsm_episode_name (ls_file, 54, &(ls_level_selected[0]), 4);
	ls_chapter_screenshot_id[0] = lsm_chapter_screenshot(ls_file, 201, &(ls_level_selected[1]), 1);
	ls_chapter_screenshot_id[1] = lsm_chapter_screenshot(ls_file, 202, &(ls_level_selected[1]), 2);
	ls_chapter_screenshot_id[2] = lsm_chapter_screenshot(ls_file, 203, &(ls_level_selected[1]), 3);
	ls_chapter_screenshot_id[3] = lsm_chapter_screenshot(ls_file, 204, &(ls_level_selected[1]), 4);
	
	//Inicializacion de variables
	ls_vidas = 3;
	ls_armas_elegidas = 0;
	ls_level_selected[0] = 1;
	ls_level_selected[1] = 1;
	ls_level_selected[2] = 1;
	ls_cursor_id[0] = lsm_cursor1(ls_file, 1, 1, 8, -2);
	ls_cursor_id[1] = lsm_cursor2(ls_file, 0, 100, 46, -2);
	ls_cursor_id[2] = lsm_cursor3(ls_file, 0, 199, 90, -2);
	ls_jugar = 1;
	
	//set_fps(25, cte_frameskip);
    level_song = _CTE_MUSIC_NOMUSIC;
    fade_on(1000);
    while (fade_info.fading) frame; end
    //set_fps(50, cte_frameskip);
	
	//Comienza el mogollón ****************************************
	ls_opcion1 = 0;
	while (ls_opcion1 >= 0)
		switch (ls_opcion1)
		case 0:	//MAX ENERGIAS
			if (teclas[k_down][2] == 1)
				ls_opcion1++;
				ls_cursor_id[0].y = 23;
				ls_cursor_id[0].graph = 1;
			end
			if ((teclas[k_left][2] == 1) && (ls_max_energias > 0))
				ls_max_energias--;
				ls_max_energia_final = 10 + (ls_max_energias * 2);
				ls_image_id[0].x = 81 + (230 * (10 + (ls_max_energias * 2)) /
										(10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2)));
				if (ls_energias > ls_max_energias)
					ls_energias = ls_max_energias;
					drawing_color(0);
					draw_rectangle_filled(80,19,
							              /*80 +*/ (230 * (10 + (ls_global_savegame.items_energia * 2)) /
										           (10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
										  28-19);
					drawing_color(rgb(255,0,0));
					draw_rectangle_filled(80,19,
								          /*80 +*/ (230 * (10 + (ls_energias * 2)) /
								          	       (10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
								          28-19);
					ls_energia_final = 10 + (ls_energias * 2);
				end
			end
			if ((teclas[k_right][2] == 1) && (ls_max_energias < ls_global_savegame.items_energia))
				ls_max_energias++;
				ls_max_energia_final = 10 + (ls_max_energias * 2);
				ls_image_id[0].x = 81 + (230 * (10 + (ls_max_energias * 2)) /
										(10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2)));
			end
		end
		case 1:	//ENERGIAS
			if ((teclas[k_left][2] == 1) && (ls_energias > 0))
				ls_energias--;
				//ls_image_id[0].size_x = 100 + (ls_energias * 20);
				drawing_color(0);
				draw_rectangle_filled(80,19,
						/*80 +*/ (230 * (10 + (ls_max_energias * 2)) / (10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
						28-19);
				drawing_color(rgb(255,0,0));
				draw_rectangle_filled(80,19,
							/*80 +*/ (230 * (10 + (ls_energias * 2)) / (10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
							28-19);
				ls_energia_final = 10 + (ls_energias * 2);
			end
			if ((teclas[k_right][2] == 1) && (ls_energias < ls_max_energias))
				ls_energias++;
				//ls_image_id[0].size_x = 100 + (ls_energias * 20);
				drawing_color(0);
				draw_rectangle_filled(80,19,
						/*80 +*/ (230 * (10 + (ls_max_energias * 2)) / (10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
						28);
				drawing_color(rgb(255,0,0));
				draw_rectangle_filled(80,19,
							/*80 +*/ (230 * (10 + (ls_energias * 2)) / (10 + (_CTE_LEVEL_SELECT_MAX_ITEMS_ENERGIA * 2))),
							28);
				ls_energia_final = 10 + (ls_energias * 2);
			end
			if (teclas[k_up][2] == 1)
				ls_opcion1--;
				ls_cursor_id[0].y = 8;
				ls_cursor_id[0].graph = 1;
			end
			if (teclas[k_down][2] == 1)
				ls_opcion1++;
				ls_cursor_id[0].y = 38;
				ls_cursor_id[0].graph = 2;
			end
		end
		case 2:	//ARMAS
			if ((teclas[k_left][2] == 1) && (ls_opcion_armas > 0))
				ls_opcion_armas = lsm_prev_weapon (ls_global_savegame.armas_desbloqueadas, ls_opcion_armas);
				if (ls_opcion_armas == -1)
					ls_opcion_armas = 0;
					ls_cursor_id[0].graph = 2;
					ls_cursor_id[1].graph = 0;
				else
					ls_cursor_id[1].x = 100 + (22 * (ls_opcion_armas - 1));
				end
			end
			if ((teclas[k_right][2] == 1) && (ls_opcion_armas < 3))
				temp = lsm_next_weapon (ls_global_savegame.armas_desbloqueadas, ls_opcion_armas);
				if (temp != -1)
					if (ls_opcion_armas == 0)
						ls_cursor_id[0].graph = 0;
						ls_cursor_id[1].graph = 4;
					end
					ls_opcion_armas = temp;
					
					ls_cursor_id[1].x = 100 + (22 * (ls_opcion_armas - 1));
				end
			end
			if (ls_opcion_armas == 0)
				if (teclas[k_up][2] == 1)
					ls_opcion1--;
					ls_cursor_id[0].y = 23;
					ls_cursor_id[0].graph = 1;
				end
				if (teclas[k_down][2] == 1)
					ls_opcion1++;
					ls_cursor_id[0].y = 63;
					ls_cursor_id[0].graph = 1;
				end
			else
				if ((teclas[k_up][2] == 1) || (teclas[k_down][2] == 1) || (teclas[k_fire][2] == 1))
					switch (ls_opcion_armas)
					case 1:
						if ((ls_armas_elegidas & CTE_GS_DESBLOQUEO_BLUE_STAR) == CTE_GS_DESBLOQUEO_BLUE_STAR)
							ls_armas_elegidas -= CTE_GS_DESBLOQUEO_BLUE_STAR;
							ls_image_id[1].flags = 4;
						else
							ls_armas_elegidas += CTE_GS_DESBLOQUEO_BLUE_STAR;
							ls_image_id[1].flags = 0;
						end
					end
					case 2:
						if ((ls_armas_elegidas & CTE_GS_DESBLOQUEO_LEAF_BLADE) == CTE_GS_DESBLOQUEO_LEAF_BLADE)
							ls_armas_elegidas -= CTE_GS_DESBLOQUEO_LEAF_BLADE;
							ls_image_id[2].flags = 4;
						else
							ls_armas_elegidas += CTE_GS_DESBLOQUEO_LEAF_BLADE;
							ls_image_id[2].flags = 0;
						end
					end
					case 3:
						if ((ls_armas_elegidas & CTE_GS_DESBLOQUEO_GREEN_CAT) == CTE_GS_DESBLOQUEO_GREEN_CAT)
							ls_armas_elegidas -= CTE_GS_DESBLOQUEO_GREEN_CAT;
							ls_image_id[3].flags = 4;
						else
							ls_armas_elegidas += CTE_GS_DESBLOQUEO_GREEN_CAT;
							ls_image_id[3].flags = 0;
						end
					end
					end	//switch
				end
			end
		end
		case 3:	//VIDAS
			if ((teclas[k_left][2] == 1) && (ls_vidas > 1))
				ls_vidas--;
			end
			if ((teclas[k_right][2] == 1) && (ls_vidas < 5))
				ls_vidas++;
			end
			if (teclas[k_up][2] == 1)
				ls_opcion1--;
				ls_cursor_id[0].y = 38;
				ls_cursor_id[0].graph = 2;
			end
			if (teclas[k_down][2] == 1)
				ls_opcion1++;
				ls_cursor_id[0].y = 88;
				ls_cursor_id[0].graph = 3;
			end
		end
		
		
		case 4:	//EPISODIO
			switch (ls_opcion_episodio)
			case 0:
				if (teclas[k_right][2] == 1)
					ls_cursor_id[0].graph = 0;
					ls_cursor_id[2].graph = 5;
					ls_opcion_episodio++;
				end
				if (teclas[k_up][2] == 1)
					ls_opcion1--;
					ls_cursor_id[0].y = 63;
					ls_cursor_id[0].graph = 1;
				end
				if (teclas[k_down][2] == 1)
					ls_opcion1++;
					ls_cursor_id[0].graph = 0;
					ls_image_id[8].graph = 9;
				end
			end
			case 1:
				if (teclas[k_left][2] == 1)
					ls_cursor_id[0].graph = 3;
					ls_cursor_id[2].graph = 0;
					ls_opcion_episodio--;
				end
				if (teclas[k_right][2] == 1)
					if (ls_level_selected[1] > 0)
						ls_cursor_id[2].x = 234;
						ls_opcion_episodio = 2;
						ls_ver_chapter_label = 1;
					elsif (ls_level_selected[2] > 0)
						ls_cursor_id[2].x = 269;
						ls_opcion_episodio = 3;
					end
				end
				if ((teclas[k_up][2] == 1) && (ls_level_selected[0] < 5))
					//Obteniendo episodio
					temp = lsm_next_episode(ls_global_savegame.niveles_desbloqueados, ls_level_selected[0]);
					if (temp != -1)
						ls_level_selected[0] = temp;
						ls_image_id[5].graph = 100 + ls_level_selected[0];
						//Obteniendo capítulo
						temp = lsm_get_chapters(ls_level_selected[0]);
						if (temp <= 0)
							ls_level_selected[1] = 0;
							ls_image_id[6].graph = 0;
						else
							ls_level_selected[1] = 1;
							ls_image_id[6].graph = 101;
						end
						//Obteniendo checkpoint
						temp = lsm_get_checkpoints(ls_level_selected[0], ls_level_selected[1]);
						if (temp <= 0)
							ls_level_selected[2] = 0;
							ls_image_id[7].graph = 0;
						else
							ls_level_selected[2] = 1;
							ls_image_id[7].graph = 101;
						end
						//Actualizamos screenshots
						for (cont = 0; cont < 4; cont++)
							ls_chapter_screenshot_id[cont].graph = 200 + ((ls_level_selected[0] - 1) * 10) + cont + 1;
						end
					end
				end
				if ((teclas[k_down][2] == 1) && (ls_level_selected[0] > 1))
					temp = lsm_prev_episode(ls_global_savegame.niveles_desbloqueados, ls_level_selected[0]);
					if (temp != -1)
						ls_level_selected[0] = temp;
						ls_image_id[5].graph = 100 + ls_level_selected[0];
						//Obteniendo capítulo
						temp = lsm_get_chapters(ls_level_selected[0]);
						if (temp <= 0)
							ls_level_selected[1] = 0;
							ls_image_id[6].graph = 0;
						else
							ls_level_selected[1] = 1;
							ls_image_id[6].graph = 101;
						end
						//Obteniendo checkpoint
						temp = lsm_get_checkpoints(ls_level_selected[0], ls_level_selected[1]);
						if (temp <= 0)
							ls_level_selected[2] = 0;
							ls_image_id[7].graph = 0;
						else
							ls_level_selected[2] = 1;
							ls_image_id[7].graph = 101;
						end
						//Actualizamos screenshots
						for (cont = 0; cont < 4; cont++)
							ls_chapter_screenshot_id[cont].graph = 200 + ((ls_level_selected[0] - 1) * 10) + cont + 1;
						end
					end
				end
			end
			case 2:
				if (teclas[k_left][2] == 1)
					ls_cursor_id[2].x = 199;
					ls_opcion_episodio = 1;
					ls_ver_chapter_label = 0;
				end
				if (teclas[k_right][2] == 1)
					if (ls_level_selected[2] > 0)
						ls_cursor_id[2].x = 269;
						ls_opcion_episodio = 3;
						//ls_ver_chapter_label = 0;
					end
				end
				if ((teclas[k_up][2] == 1) && (ls_level_selected[1] < lsm_get_chapters(ls_level_selected[0])))
					//Obteniendo capítulo
					temp = lsm_next_chapter(ls_global_savegame.subniveles_desbloqueados[ls_level_selected[0] - 1],
											ls_level_selected[1]);
					if (temp != -1)
						ls_level_selected[1] = temp;
						ls_image_id[6].graph = 100 + ls_level_selected[1];
						//Obteniendo checkpoint
						temp = lsm_get_checkpoints(ls_level_selected[0], ls_level_selected[1]);
						if (temp <= 0)
							ls_level_selected[2] = 0;
							ls_image_id[7].graph = 0;
						else
							ls_level_selected[2] = 1;
							ls_image_id[7].graph = 101;
						end
					end
				end
				if ((teclas[k_down][2] == 1) && (ls_level_selected[1] > 1))
					//Obteniendo capítulo
					temp = lsm_prev_chapter(ls_global_savegame.subniveles_desbloqueados[ls_level_selected[0] - 1],
											ls_level_selected[1]);
					if (temp != -1)
						ls_level_selected[1] = temp;
						ls_image_id[6].graph = 100 + ls_level_selected[1];
						//Obteniendo checkpoint
						temp = lsm_get_checkpoints(ls_level_selected[0], ls_level_selected[1]);
						if (temp <= 0)
							ls_level_selected[2] = 0;
							ls_image_id[7].graph = 0;
						else
							ls_level_selected[2] = 1;
							ls_image_id[7].graph = 101;
						end
					end
				end
			end
			case 3:
				if (teclas[k_left][2] == 1)
					if (ls_level_selected[1] > 0)
						ls_cursor_id[2].x = 234;
						ls_opcion_episodio = 2;
						//ls_ver_chapter_label = 1;
					else 
						ls_cursor_id[2].x = 199;
						ls_opcion_episodio = 1;
					end
				end
				if ((teclas[k_up][2] == 1) &&
					(ls_level_selected[2] < lsm_get_checkpoints(ls_level_selected[0], ls_level_selected[1])))
					//Obteniendo checkpoint
					ls_level_selected[2]++;
					ls_image_id[7].graph = 100 + ls_level_selected[2];
				end
				if ((teclas[k_down][2] == 1) && (ls_level_selected[2] > 1))
					//Obteniendo checkpoint
					ls_level_selected[2]--;
					ls_image_id[7].graph = 100 + ls_level_selected[2];
				end
			end
			end //switch
		end
		
		case 5:
			if (teclas[k_left][2] == 1)
				ls_jugar = 1;
				ls_image_id[8].x = 0;
			end
			if (teclas[k_right][2] == 1)
				ls_jugar = 0;
				ls_image_id[8].x = 160;
			end
			if (teclas[k_up][2] == 1)
				ls_opcion1--;
				ls_cursor_id[0].graph = 3;
				ls_image_id[8].graph = 0;
			end
			
			if ((teclas[k_fire][2] == 1) || (teclas[k_enter][2] == 1))
				ls_opcion1 = -1;
			end
		end
		end // switch
		//if (key(_ESC)) break; end
		frame;
	end
	//*************************************************************
	
	//set_fps(25, cte_frameskip);
	fade_off(1000);
	while (fade_info.fading) frame; end
	//set_fps(50, cte_frameskip);
	
	clear_screen();
	for (cont = 0; cont < 3; cont++)
		if ((ls_cursor_id[cont] != 0) && exists(ls_cursor_id[cont]))
			signal(ls_cursor_id[cont], s_kill);
		end
	end
	for (cont = 0; cont < 9; cont++)
		if ((ls_image_id[cont] != 0) && exists(ls_image_id[cont]))
			signal(ls_image_id[cont], s_kill);
		end
	end
	if ((ls_chapter_label_id != 0) && exists(ls_chapter_label_id))
		signal(ls_chapter_label_id, s_kill);
	end
	for (cont = 0; cont < 3; cont++)
		if ((ls_episode_name_id[cont] != 0) && exists(ls_episode_name_id[cont]))
			signal(ls_episode_name_id[cont], s_kill);
		end
	end
	for (cont = 0; cont < 4; cont++)
		if ((ls_chapter_screenshot_id[cont] != 0) && exists(ls_chapter_screenshot_id[cont]))
			signal(ls_chapter_screenshot_id[cont], s_kill);
		end
	end
	
	//Se borran los textos
	for (cont = 0; cont < 6; cont++)
		if (ls_text_labels[cont] != 0)
			write_delete(ls_text_labels[cont]);
		end
	end
	for (cont = 0; cont < 3; cont++)
		if (ls_text_values[cont] != 0)
			write_delete(ls_text_values[cont]);
		end
	end
	
	//*******************************************************************
	if (ls_jugar)
		next_level = ls_level_selected[0];
		next_sublevel = ls_level_selected[1] - 1;
		if (next_sublevel < 0) next_sublevel = 0; end
		init_level = ls_level_selected[2] - 1;
		if (init_level < 0) init_level = 0; end
		//ls_intro = 1;
		//ls_intro = 0;
		//ls_show_saved = 0;
		//ls_estado_end_level = 0;
		
		armas_select=0; 
		armas_get[0] = (ls_armas_elegidas == 0);
		armas_get[1] = ((ls_armas_elegidas & CTE_GS_DESBLOQUEO_BLUE_STAR) == CTE_GS_DESBLOQUEO_BLUE_STAR);
		armas_get[2] = ((ls_armas_elegidas & CTE_GS_DESBLOQUEO_LEAF_BLADE) == CTE_GS_DESBLOQUEO_LEAF_BLADE);
		armas_get[3] = ((ls_armas_elegidas & CTE_GS_DESBLOQUEO_GREEN_CAT) == CTE_GS_DESBLOQUEO_GREEN_CAT);
		armas_get[4] = 0;
		info_prota.vidas = ls_vidas;
		
		info_prota.p_max_energ = ls_max_energia_final;
		info_prota.p_energ = ls_energia_final;
		global_mode = CTE_GLOBAL_MODE_PLAYLEVELSELECT;
	else
		global_mode = CTE_GLOBAL_MODE_PORTADA;
	end
	
	signal(father, s_wakeup);
end