process keys_configuration ()
private
    int gm_font;
    int gm_hijos;
    
    int gm_ancho_map, gm_alto_map;
    int gm_text[26];
    string gm_key1, gm_key2, gm_key3, gm_key4, gm_key5, gm_key6;
	string gm_key7, gm_key8, gm_key9, gm_key10, gm_key11, gm_key12;
    
    int max_opcion;
    int kc_opcion;
    int temp_keys[11];
    int temp;
    int cont;
begin
    max_opcion = 12;
    gm_font = fnt_load(dreamcast_ruta + "fonts/menu1.fnt");
    gm_ancho_map = 230;
    
    gm_ancho_map += 20;
    gm_alto_map = 15 * ((max_opcion / 2) + 2) + 30;
    
    graph = configuration_menu_crear_fondo(gm_ancho_map, gm_alto_map);
    
    x = 160;
    y = 120;
    z = -100;
    
    //Escribimos los textos fijos
    gm_text[0] = write(gm_font, 160, y - (gm_alto_map / 2) + 14, 4, "KEY CONFIGURATION");
    
    gm_text[1] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 30, 3, "Up:");
    gm_text[2] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 30, 3, "Down:");
    gm_text[3] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 45, 3, "Left:");
    gm_text[4] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 45, 3, "right:");
    gm_text[5] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 60, 3, "Jump:");
    gm_text[6] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 60, 3, "Fire:");
    gm_text[7] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 75, 3, "Prev. weapon:");
    gm_text[8] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 75, 3, "Next weapon:");
    gm_text[9] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 90, 3, "Enter:");
    gm_text[10] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 90, 3, "Esc:");
    gm_text[11] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 105, 3, "Vol. up:");
    gm_text[12] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 105, 3, "Vol. down:");
    gm_text[13] = write(gm_font, 160 - (gm_ancho_map / 6), y - (gm_alto_map / 2) + 14 + 120, 4, "OK");
    gm_text[14] = write(gm_font, 160 + (gm_ancho_map / 6), y - (gm_alto_map / 2) + 14 + 120, 4, "CANCEL");
    
    //Escribimos los textos cambiantes
    gm_text[15] = write_var(gm_font, 150, y - (gm_alto_map / 2) + 14 + 30, 5, gm_key1);
    gm_text[16] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 30, 5, gm_key2);
    gm_text[17] = write_var(gm_font, 150, y - (gm_alto_map / 2) + 14 + 45, 5, gm_key3);
    gm_text[18] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 45, 5, gm_key4);
    gm_text[19] = write_var(gm_font, 150, y - (gm_alto_map / 2) + 14 + 60, 5, gm_key5);
    gm_text[20] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 60, 5, gm_key6);
    gm_text[21] = write_var(gm_font, 150, y - (gm_alto_map / 2) + 14 + 75, 5, gm_key7);
    gm_text[22] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 75, 5, gm_key8);
    gm_text[23] = write_var(gm_font, 150, y - (gm_alto_map / 2) + 14 + 90, 5, gm_key9);
    gm_text[24] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 90, 5, gm_key10);
    gm_text[25] = write_var(gm_font, 150, y - (gm_alto_map / 2) + 14 + 105, 5, gm_key11);
    gm_text[26] = write_var(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 105, 5, gm_key12);
    
    //Rellenamos los datos temporales con los datos antiguos
    for (cont = 0; cont < k_last; cont++)
        temp_keys[cont] = teclas[cont][0];
    end
    //Y los escribimos
    key_to_string(temp_keys[0]);
    gm_key1 = nombre_tecla;
    key_to_string(temp_keys[1]);
    gm_key2 = nombre_tecla;
    key_to_string(temp_keys[2]);
    gm_key3 = nombre_tecla;
    key_to_string(temp_keys[3]);
    gm_key4 = nombre_tecla;
    key_to_string(temp_keys[4]);
    gm_key5 = nombre_tecla;
    key_to_string(temp_keys[5]);
    gm_key6 = nombre_tecla;
    key_to_string(temp_keys[6]);
    gm_key7 = nombre_tecla;
    key_to_string(temp_keys[7]);
    gm_key8 = nombre_tecla;
    key_to_string(temp_keys[8]);
    gm_key9 = nombre_tecla;
    key_to_string(temp_keys[9]);
    gm_key10 = nombre_tecla;
    key_to_string(temp_keys[10]);
    gm_key11 = nombre_tecla;
    key_to_string(temp_keys[11]);
    gm_key12 = nombre_tecla;
    
    //creamos el cursor
    gm_hijos = global_menu_img (0, map_new((gm_ancho_map - 10) / 2, 14), 160 - ((gm_ancho_map - 10) / 4), y - (gm_alto_map / 2) + 14 + 30, z - 1);
    map_clear(file, gm_hijos.graph, rgb(0, 0, 128));
    
    kc_opcion = 0;
    //espera hasta que no se pulse ninguna tecla
    while (teclas[k_enter][2] > 0 || teclas[k_fire][2] > 0 || teclas[k_jump][2] > 0) frame; end
    loop
        //movimientos del cursor
        if (teclas[k_up][2] == 1)
            kc_opcion -= 2;
            if (kc_opcion < 0) kc_opcion += max_opcion + 2; end
        end
        if (teclas[k_down][2] == 1)
            kc_opcion += 2;
            if (kc_opcion >= max_opcion + 2) kc_opcion -= max_opcion + 2; end
        end
        if ((teclas[k_left][2] == 1) && (kc_opcion & 1))     //comprobamos que esté a la derecha
            kc_opcion--;
        end
        if ((teclas[k_right][2] == 1) && ((kc_opcion & 1) == 0))     //comprobamos que esté a la izquierda
            kc_opcion++;
        end
        //colocamos el cursor en su posición
        if (kc_opcion & 1)
            gm_hijos.x = 160 + ((gm_ancho_map - 10) / 4);
        else
            gm_hijos.x = 160 - ((gm_ancho_map - 10) / 4);
        end
        gm_hijos.y = y - (gm_alto_map / 2) + 14 + 30 + (15 * (kc_opcion / 2));
        
        
        //ahora comprobamos si se decide cambiar la tecla
        if (teclas[k_enter][2] == 1 || teclas[k_fire][2] == 1 || teclas[k_jump][2] == 1)
            if (kc_opcion < max_opcion)     //Vamos a cambiar una tecla
                //paso 1: borrar el texto para indicar que estamos a la espera
                switch (kc_opcion)
                case 0: gm_key1 = ""; end
                case 1: gm_key2 = ""; end
                case 2: gm_key3 = ""; end
                case 3: gm_key4 = ""; end
                case 4: gm_key5 = ""; end
                case 5: gm_key6 = ""; end
                case 6: gm_key7 = ""; end
                case 7: gm_key8 = ""; end
                case 8: gm_key9 = ""; end
                case 9: gm_key10 = ""; end
                case 10: gm_key11 = ""; end
                case 11: gm_key12 = ""; end
                end //switch
                //paso 2: esperar a que no se esté pulsando ninguna tecla
                while (keyboard.scan_code != 0) frame; end
                //paso 3: esperar la pulsacion de una tecla
                temp = 0;
                while (temp == 0)
                    temp = keyboard.scan_code;
                    frame;
                end
                //paso 4: asignar la pulsacion a su lugar
                temp_keys[kc_opcion] = temp;
                //paso 5: escribir el nuevo nombre
                key_to_string(temp);
                switch (kc_opcion)
                case 0: gm_key1 = nombre_tecla; end
                case 1: gm_key2 = nombre_tecla; end
                case 2: gm_key3 = nombre_tecla; end
                case 3: gm_key4 = nombre_tecla; end
                case 4: gm_key5 = nombre_tecla; end
                case 5: gm_key6 = nombre_tecla; end
                case 6: gm_key7 = nombre_tecla; end
                case 7: gm_key8 = nombre_tecla; end
                case 8: gm_key9 = nombre_tecla; end
                case 9: gm_key10 = nombre_tecla; end
                case 10: gm_key11 = nombre_tecla; end
                case 11: gm_key12 = nombre_tecla; end
                end //switch
            else
                switch (kc_opcion)
                case max_opcion:        //OK
                    //Rellenamos los datos antiguos con los datos nuevos
                    for (cont = 0; cont < k_last; cont++)
                        teclas[cont][0] = temp_keys[cont];
                        config_data.teclas[cont][0] = teclas[cont][0];
                    end
                    //y salvamos los cambios
                    save_config();
                    //y salimos
                    break;
                end
                case max_opcion + 1:      //CANCEL
                    //simplemente salimos
                    break;
                end
                end //switch
            end
        end
        
        frame;
    end
    
    if (exists(gm_hijos))
        map_unload(gm_hijos.file, gm_hijos.graph);
        signal(gm_hijos, s_kill);
    end
    for (cont = 0; cont <= 26; cont++)
        write_delete(gm_text[cont]);
    end
    fnt_unload(gm_font);
    map_unload(file, graph);
end
