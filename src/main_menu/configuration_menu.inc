//**************************************************************************************************
//  MENUS DE CONFIGURACIÓN
//**************************************************************************************************
process configuration_menu_img (file, graph, x, y, z)
begin
    signal(id, s_freeze);
    frame;
end

function configuration_menu_crear_fondo (int gm_ancho_map, int gm_alto_map)
begin
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
    
    return graph;
end


process game_options ()
private
    int gm_font;
    int gm_hijos;
    
    int gm_ancho_map, gm_alto_map;
    int gm_text[10];
    string gm_opt1, gm_opt2, gm_opt3, gm_opt4;
    
    int max_opcion;
    int kgc_opcion;
    int temp_opcion[4];
    int cont;
begin
    max_opcion = 5;
    gm_font = fnt_load(dreamcast_ruta + "fonts/menu1.fnt");
    gm_ancho_map = 240;
    
    gm_ancho_map += 20;
    gm_alto_map = 15 * (max_opcion + 1) + 30;
    
    graph = configuration_menu_crear_fondo(gm_ancho_map, gm_alto_map);
    
    x = 160;
    y = 120;
    z = -100;
    
    //Escribimos los textos fijos
    gm_text[0] =write(gm_font, 160, y - (gm_alto_map / 2) + 14, 4, "GAME CONFIGURATION");
    
    gm_text[1] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 30, 3, "Graphics style:");
    gm_text[2] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 45, 3, "Frameskip:");
    gm_text[3] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 60, 3, "Background scroll:");
    gm_text[4] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 75, 3, "Foreground scroll:");
    gm_text[5] = write(gm_font, 160 - (gm_ancho_map / 6), y - (gm_alto_map / 2) + 14 + 90, 4, "OK");
    gm_text[6] = write(gm_font, 160 + (gm_ancho_map / 6), y - (gm_alto_map / 2) + 14 + 90, 4, "CANCEL");
    
    //Escribimos los textos cambiantes
    gm_text[7] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 30, 5, gm_opt1);
    gm_text[8] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map/2) + 14 + 45, 5, gm_opt2);
    gm_text[9] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map/2) + 14 + 60, 5, gm_opt3);
    gm_text[10] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 75, 5, gm_opt4);
    
    //Inicializamos los datos con los actuales
    if (graph_dir == "classic")
        temp_opcion[0] = 0;
    elsif
        temp_opcion[0] = 1;
    end
    temp_opcion[1] = cte_frameskip;
    temp_opcion[2] = game_background_scroll;
    temp_opcion[3] = game_foreground_scroll;
    
    //Inicializacion de las cadenas de texto
    switch (temp_opcion[0])
    case 0: gm_opt1 = "classic"; end
    case 1: gm_opt1 = "stylish"; end
    end //switch
    gm_opt2 = itoa(temp_opcion[1]);
    if (temp_opcion[2]) gm_opt3 = "Yes"; else gm_opt3 = "No"; end
    if (temp_opcion[3]) gm_opt4 = "Yes"; else gm_opt4 = "No"; end
    
    //creamos el cursor
    gm_hijos = global_menu_img (0, map_new((gm_ancho_map - 10), 14), 160, y - (gm_alto_map / 2) + 14 + 30, z - 1);
    map_clear(file, gm_hijos.graph, rgb(0, 0, 128));
    
    kgc_opcion = 0;
    //espera hasta que no se pulse ninguna tecla
    while (teclas[k_enter][2] > 0 || teclas[k_fire][2] > 0 || teclas[k_jump][2] > 0) frame; end
    loop
        //movimientos del cursor
        if (teclas[k_up][2] == 1)
            kgc_opcion--;
            if (kgc_opcion < 0) kgc_opcion += max_opcion; end
        end
        if (teclas[k_down][2] == 1)
            kgc_opcion++;
            if (kgc_opcion >= max_opcion) kgc_opcion -= max_opcion; end
        end
        //Si se mueve el cursor
        if ((teclas[k_up][2] == 1) || (teclas[k_down][2] == 1))
            gm_hijos.y = y - (gm_alto_map / 2) + 14 + 30 + (15 * kgc_opcion);
            // Si se mueve a la última opción, hay que modificarlo
            if (kgc_opcion == max_opcion - 1)
                gm_hijos.size_x = 50;
                /*if (temp_opcion[max_opcion-1])
                    gm_hijos.x = 160-((gm_ancho_map-10)/4);
                else
                    gm_hijos.x = 160-((gm_ancho_map-10)/4) + ((gm_ancho_map-10)/2);
                end*/
                gm_hijos.x = 160 - ((gm_ancho_map - 10) / 4) + (((gm_ancho_map - 10) / 2) * temp_opcion[4]);
            else
                gm_hijos.size_x = 100;
                gm_hijos.x = 160;
            end
        end
    
        if (teclas[k_left][2] == 1)
            switch (kgc_opcion)
            case 0, 2, 3, 4:
                if (temp_opcion[kgc_opcion] == 1) temp_opcion[kgc_opcion] = 0;
                else temp_opcion[kgc_opcion] = 1; end
            end
            case 1:
                if (temp_opcion[kgc_opcion] > 0) temp_opcion[kgc_opcion]--;
                else temp_opcion[kgc_opcion] = 10; end
            end
            end //switch
        end
        if (teclas[k_right][2] == 1)
            switch (kgc_opcion)
            case 0, 2, 3, 4:
                if (temp_opcion[kgc_opcion] == 1) temp_opcion[kgc_opcion] = 0;
                else temp_opcion[kgc_opcion] = 1; end
            end
            case 1:
                if (temp_opcion[kgc_opcion] < 10) temp_opcion[kgc_opcion]++;
                else temp_opcion[kgc_opcion] = 0; end
            end
            end //switch
        end
        //Si se cambia el valor de la opción, se debe reescribir su valor por texto
        if ((teclas[k_left][2] == 1) || (teclas[k_right][2] == 1))
            switch (kgc_opcion)
            case 0:
                switch (temp_opcion[kgc_opcion])
                case 0: gm_opt1 = "classic"; end
                case 1: gm_opt1 = "stylish"; end
                end //switch
            end
            case 1: gm_opt2 = itoa(temp_opcion[kgc_opcion]); end
            case 2:
                if (temp_opcion[kgc_opcion]) gm_opt3 = "Yes"; else gm_opt3 = "No"; end
            end
            case 3:
                if (temp_opcion[kgc_opcion]) gm_opt4 = "Yes"; else gm_opt4 = "No"; end
            end
            case 4:
                if (temp_opcion[max_opcion-1])
                    gm_hijos.x = 160 - ((gm_ancho_map - 10) / 4) + ((gm_ancho_map - 10) / 2);
                else
                    gm_hijos.x = 160 - ((gm_ancho_map - 10) / 4);
                end
            end
            end //switch
        end
        
        //Se pulsa intro ¿Es OK o CANCEL?
        if (teclas[k_enter][2] == 1 || teclas[k_fire][2] == 1 || teclas[k_jump][2] == 1)
            if (temp_opcion[max_opcion - 1] == 0)
                graph_dir = gm_opt1;
                cte_frameskip = temp_opcion[1];
                game_background_scroll = temp_opcion[2];
                game_foreground_scroll = temp_opcion[3];
                
                set_fps(50, cte_frameskip);
                
                config_data.tipo_graficos = temp_opcion[0];
                config_data.usar_scroll_fondo = temp_opcion[2];
                config_data.usar_scroll_frontal = temp_opcion[3];
                config_data.cte_frameskip = temp_opcion[1];
                
                save_config();
            end
            
            break;
        end
        frame;
    end
    
    if (exists(gm_hijos))
        map_unload(gm_hijos.file, gm_hijos.graph);
        signal(gm_hijos, s_kill);
    end
    for (cont = 0; cont <= 10; cont++)
        write_delete(gm_text[cont]);
    end
    fnt_unload(gm_font);
    map_unload(file, graph);
end