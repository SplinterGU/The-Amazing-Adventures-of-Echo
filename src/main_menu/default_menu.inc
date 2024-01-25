//*****************************************************
//  MENU
//*****************************************************
process global_menu_img (file, graph, x, y, z)
begin
    signal(id, s_freeze);
    frame;
end

process global_menu (int min_opcion, int max_opcion, string opt1, string opt2, string opt3, string opt4, string opt5, string opt6)
private
    int gm_font;
    int gm_ancho_map, gm_alto_map;
    
    int gm_text[5];
    int gm_hijos;
    int cont;
begin
    gm_font = fnt_load(dreamcast_ruta + "fonts/menu1.fnt");
	//say("Fuente: " + gm_font);
    gm_ancho_map = text_width(gm_font, opt1);
    if (gm_ancho_map < text_width(gm_font, opt2)) gm_ancho_map = text_width(gm_font, opt2); end
    if (gm_ancho_map < text_width(gm_font, opt3)) gm_ancho_map = text_width(gm_font, opt3); end
    if (gm_ancho_map < text_width(gm_font, opt4)) gm_ancho_map = text_width(gm_font, opt4); end
    if (gm_ancho_map < text_width(gm_font, opt5)) gm_ancho_map = text_width(gm_font, opt5); end
    if (gm_ancho_map < text_width(gm_font, opt6)) gm_ancho_map = text_width(gm_font, opt6); end
    gm_ancho_map += 20;
    gm_alto_map = 15 * max_opcion + 30;
    
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
    
    //for (cont=0;cont<=max_opcion,cont++)
    gm_text[0] = write(gm_font, 160, y - (gm_alto_map / 2) + 14, 4, opt1);
    if (max_opcion > 0) gm_text[1] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 15, 4, opt2); end
    if (max_opcion > 1) gm_text[2] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 30, 4, opt3); end
    if (max_opcion > 2) gm_text[3] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 45, 4, opt4); end
    if (max_opcion > 3) gm_text[4] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 60, 4, opt5); end
    if (max_opcion > 4) gm_text[5] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 75, 4, opt6); end
    
    gm_hijos = global_menu_img (0, map_new(gm_ancho_map - 10, 14), 160, y - (gm_alto_map / 2) + 14, z - 1);
    map_clear(file, gm_hijos.graph, rgb(0, 0, 128));
    
    //global_opt=min_opcion;
    gm_hijos.y = y - (gm_alto_map / 2) + 14 + (global_opt * 15);
    loop
        if (teclas[k_up][2] == 1)
            if (global_opt == min_opcion)
				global_opt = max_opcion;
			else
				global_opt--;
			end
            gm_hijos.y = y - (gm_alto_map / 2) + 14 + (global_opt * 15);
        end
        if (teclas[k_down][2] == 1)
            if (global_opt == max_opcion)
				global_opt = min_opcion;
			else
				global_opt++;
			end
            gm_hijos.y = y - (gm_alto_map / 2) + 14 + (global_opt * 15);
        end
        if (teclas[k_enter][2] == 1 || teclas[k_fire][2] == 1 || teclas[k_jump][2] == 1)
            break;
        end
        frame;
    end
    
    for (cont = 0; cont < 6; cont++)
        if (gm_text[cont] != 0) write_delete(gm_text[cont]); end
    end
    map_unload(0, gm_hijos.graph);
    map_unload(file, graph);
    fnt_unload(gm_font);
    signal(gm_hijos, s_kill);
end