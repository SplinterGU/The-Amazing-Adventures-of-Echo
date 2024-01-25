//*******************************************************************************
//  SELECT FILE MENU
//*******************************************************************************
function get_sfm_graph (savegame pointer ptr_sav, int temp, int gsg_font,
                        int graph1, int graph2, int graph3, int graph4)
//Genera un gráfico a modo de vista previa de la información almacenada en un fichero de
//partida guardada para el menú de selección de partida a cargar
//	ptr_sav:	Estructura de datos de la partida guardada en el fichero
//	temp:		Posición en la lista de partidas que se pueden cargar
//	gsg_font:	Fuente de letras a usar en los textos
//	graph1..graph3:	Armas conseguidas
//	graph4:		Little cute Echo para indicar las vidas restantes
private
    int final_graph;
    int temp_graph;
    
    string temp_string;
begin
    final_graph = map_new(225, 18);
    //escribiendo número de fichero
    write_in_map(file, final_graph, gsg_font, 0, 14, itoa(temp) + ".", 6);
//    map_put(file, final_graph, 0, temp_graph, 0, 14);
//    map_unload(0, temp_graph);
    
    //escribiendo nivel
    /*switch (ptr_sav.level)
    case 1: temp_string = "Lvl 1-" + itoa(ptr_sav.sublevel + 1); end
    case 3: temp_string = "Lvl 2-" + itoa(ptr_sav.sublevel + 1); end
    case 4: temp_string = "Lvl 3-" + itoa(ptr_sav.sublevel + 1); end
    end //switch*/
	temp_string = "Lvl " + itoa(ptr_sav.level) + "-" + itoa(ptr_sav.sublevel + 1) + "-" + itoa(ptr_sav.init_level + 1);
    write_in_map(file, final_graph, gsg_font, 22, 14, temp_string, 6);
//    map_put(file, final_graph, 0, temp_graph, 22, 14);
//    map_unload(0, temp_graph);
    
    //escribiendo dificultad
    switch (ptr_sav.difficulty)
    case 0: temp_string = "Easy"; end
    case 1: temp_string = "Medium"; end
    case 2: temp_string = "Hard"; end
    end //switch
    write_in_map(file, final_graph, gsg_font, 92, 14, temp_string, 6);
//    map_put(file, final_graph, 0, temp_graph, 92, 14);
//    map_unload(0, temp_graph);

	//Dibujando las armas disponibles
    if ((ptr_sav.armas & 2) == 2) map_put(file, final_graph, 0, graph1, 147, 9); end
    if ((ptr_sav.armas & 4) == 4) map_put(file, final_graph, 0, graph2, 159, 9); end
    if ((ptr_sav.armas & 8) == 8) map_put(file, final_graph, 0, graph3, 171, 9); end
    
	//Poniendo las vidas con un mono icono de Echo sentado
    map_put(file, final_graph, 0, graph4, 189, 16);
    write_in_map(file, final_graph, gsg_font, 200, 14, "x " + itoa(ptr_sav.lives), 6);
//    map_put(file, final_graph, 0, temp_graph, 200, 14);
//    map_unload(0, temp_graph);
    
    //say("Grafico creado = " +  final_graph);
    return (final_graph);
end


//***************************************************************************************************
//	EL MENÚ EN SÍ MISMO
//***************************************************************************************************
process select_file_menu_img (file, graph, x, y, z)
begin
    signal(id,s_freeze);
    frame;
end


process select_file_menu (int max_opcion, int load_menu)
//	max_opcion:	Nº de ficheros de guardado que se pueden seleccionar
//	load_menu:	Indica si el menú es de carga (1) o de guardado (0)
private
    int gm_font;
    int gm_ancho_map, gm_alto_map;
    
    int gm_text[0];
    int gm_graph[10];
    int gm_hijos[11];
    
    savegame temp_sav;
    int temp_map[3];
    int file2;
    int file3;
    int temp;
    int cont;
begin
    gm_font = fnt_load(dreamcast_ruta + "fonts/menu1.fnt");
    gm_ancho_map = 220;
    
	//Creando fondo del menu
    gm_ancho_map += 20;
    gm_alto_map = 20 * (max_opcion + 2) + 30;
    
    graph = map_new(gm_ancho_map, gm_alto_map);
    map_clear(file, graph, rgb(0,0,0));
    drawing_map(file, graph);
    drawing_color(rgb(255, 255, 255));
    draw_rectangle(0, 0, gm_ancho_map - 1, gm_alto_map - 1);
    draw_rectangle(1, 1, gm_ancho_map - 2, gm_alto_map - 2);
    
    draw_line(2, 2, 5, 2);
    draw_line(2, 3, 3, 3);
    draw_line(2, 4, 2, 5);
    
    draw_line(gm_ancho_map - 3, 2, gm_ancho_map - 3 - 3, 2);
    draw_line(gm_ancho_map - 3, 3, gm_ancho_map - 3 - 1, 3);
    draw_line(gm_ancho_map - 3, 4, gm_ancho_map - 3 - 0, 5);
    
    draw_line(2, gm_alto_map - 3, 5, gm_alto_map - 3);
    draw_line(2, gm_alto_map - 4, 3, gm_alto_map - 4);
    draw_line(2, gm_alto_map - 5, 2, gm_alto_map - 6);
    
    draw_line(gm_ancho_map - 3, gm_alto_map - 3, gm_ancho_map - 3 - 3, gm_alto_map - 3);
    draw_line(gm_ancho_map - 3, gm_alto_map - 4, gm_ancho_map - 3 - 1, gm_alto_map - 4);
    draw_line(gm_ancho_map - 3, gm_alto_map - 5, gm_ancho_map - 3 - 0, gm_alto_map - 6);
    
    drawing_color(0);
    draw_line(0, 0, 5, 0);
    draw_line(0, 1, 2, 1);
    draw_line(0, 2, 1, 2);
    draw_line(0, 3, 0, 5);
    
    draw_line(gm_ancho_map - 1, 0, gm_ancho_map - 1 - 5, 0);
    draw_line(gm_ancho_map - 1, 1, gm_ancho_map - 1 - 2, 1);
    draw_line(gm_ancho_map - 1, 2, gm_ancho_map - 1 - 1, 2);
    draw_line(gm_ancho_map - 1, 3, gm_ancho_map - 1 - 0, 5);
    
    draw_line(0, gm_alto_map - 1 - 0, 5, gm_alto_map - 1 - 0);
    draw_line(0, gm_alto_map - 1 - 1, 2, gm_alto_map - 1 - 1);
    draw_line(0, gm_alto_map - 1 - 2, 1, gm_alto_map - 1 - 2);
    draw_line(0, gm_alto_map - 1 - 3, 0, gm_alto_map - 1 - 5);
    
    draw_line(gm_ancho_map - 1, gm_alto_map - 1 - 0, gm_ancho_map - 1 - 5, gm_alto_map - 1 - 0);
    draw_line(gm_ancho_map - 1, gm_alto_map - 1 - 1, gm_ancho_map - 1 - 2, gm_alto_map - 1 - 1);
    draw_line(gm_ancho_map - 1, gm_alto_map - 1 - 2, gm_ancho_map - 1 - 1, gm_alto_map - 1 - 2);
    draw_line(gm_ancho_map - 1, gm_alto_map - 1 - 3, gm_ancho_map - 1 - 0, gm_alto_map - 1 - 5);
    
    x = 160;
    y = 120;
    z = -100;

    //carga de copia de gráficos para representar las armas que se tienen y el número de vidas
    file2 = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/items.fpg");
    temp_map[0] = map_clone(file2, 21);
    temp_map[1] = map_clone(file2, 22);
    temp_map[2] = map_clone(file2, 23);

    file3 = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/prota.fpg");
    temp_map[3] = map_clone(file3, 36);
    
    //generamos los mapas de cada linea
    gm_text[0] = write(gm_font, 160, y - (gm_alto_map / 2) + 14, 4, "SELECT FILE");
    for (cont = 1; cont <= max_opcion; cont++)
        temp = load_filegame(&temp_sav, cont);
        switch (temp)
        case 0:         //sin problemas
            gm_graph[cont] = get_sfm_graph(&temp_sav, cont, gm_font, temp_map[0], temp_map[1], temp_map[2], temp_map[3]);
        end
        case 1:         //no encontrado
            gm_graph[cont] = map_new(225, 18);          
            write_in_map(file, gm_graph[cont], gm_font, 0, 14, itoa(cont) + ".  -Empty-", 6);
        end
        case 2:
            gm_graph[cont] = map_new(225, 18);
            write_in_map(file, gm_graph[cont], gm_font, 0, 14, itoa(cont) + ".  -Corrupted file-", 6);
        end
        end
    end
   /* say("Max opcion: " + max_opcion) ;
    for (cont=1;cont<=max_opcion;cont++)
        say(gm_graph[cont]);
    end*/
    
    //borramos la lista de items que se ha creado
    savegame_item_got_list_delete_all();
    
    if (load_menu)
        gm_graph[0] = map_new(225, 18);
        write_in_map(file, gm_graph[0], gm_font, 0, 14, "Cancel.", 6);
    else
        gm_graph[0] = map_new(225, 18);
        write_in_map(file, gm_graph[0], gm_font, 0, 14, "No save.", 6);
    end
    
    //creamos los procesos que llevan cada imagen
    for (cont = 0; cont <= max_opcion; cont++)
        gm_hijos[cont] = select_file_menu_img(0, gm_graph[cont], 160, y - (gm_alto_map / 2) + 14 + (20 *(cont + 2)), z - 2);
    end
    
	//Creamos el proceso cursor
    gm_hijos[11] = select_file_menu_img (0, map_new(gm_ancho_map - 10, 20), 160, y - (gm_alto_map / 2) + 14, z - 1);
    map_clear(file, gm_hijos[11].graph, rgb(0, 0, 128));
    
    //empieza el control del menu
    global_opt = 0;
    gm_hijos[11].y = y - (gm_alto_map / 2) + 14 + 40 + (global_opt * 20);
    loop
        if (teclas[k_up][2] == 1)
            if (global_opt == 0)
				global_opt = max_opcion;
			else
				global_opt--;
			end
            gm_hijos[11].y = y - (gm_alto_map / 2) + 14 + 40 + (global_opt * 20);
        end
		
        if (teclas[k_down][2]==1)
            if (global_opt == max_opcion)
				global_opt = 0;
			else
				global_opt++;
			end
            gm_hijos[11].y = y - (gm_alto_map / 2) + 14 + 40 + (global_opt * 20);
        end
		
        if (teclas[k_enter][2] == 1 || teclas[k_fire][2] == 1 || teclas[k_jump][2] == 1)
            if (load_menu)          //para cargar el fichero seleccionado debe existir
                if (global_opt == 0)  //y no debemos haber seleccionado "cancel"
                    break;
                else
                    if (savegame_exists_file[global_opt - 1]) break; end
                end
            else                    //si no, no
                break;
            end
        end
        frame;
    end
    
    savegame_pos = global_opt;

    for (cont = 0; cont < 1; cont++)
        if (gm_text[cont] != 0) write_delete(gm_text[cont]); end
    end
    for (cont = 0; cont < 4; cont++)
        map_unload(0, temp_map[cont]);
    end
    for (cont = 0;cont <= max_opcion; cont++)
        map_unload(0, gm_graph[cont]);
    end
    map_unload(0, gm_hijos[11].graph);
    map_unload(file, graph);
    fnt_unload(gm_font);
    for (cont = 0; cont <= 11; cont++)
        if (exists(gm_hijos[cont])) signal(gm_hijos[cont], s_kill); end
    end

    fpg_unload(file2);
    fpg_unload(file3);

end

function refresh_savegame_exists_file ()
//Guarda en array del sistema si existen los diversos ficheros de partida guardada en la carpeta save
private
    int cont;
begin
    for (cont = 0; cont < max_savefiles; cont++)
        savegame_exists_file[cont] = fexists(get_pref_path("bennugd.org", "echo") + "data0" + itoa(cont + 1) + ".sav");
    end
end