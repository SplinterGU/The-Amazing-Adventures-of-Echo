process joy_configuration ()
private
    int gm_font;
    //int gm_hijos;
    
    int gm_ancho_map, gm_alto_map;
    int gm_text[27];
    string gm_info;
    
    int max_opcion;
    int gm_max_buttons;
    int gm_max_hats;
    int temp_keys[11];
    int temp_use_hats;
    int temp;
    int cont;
begin
    max_opcion = 12;
    gm_font = fnt_load(dreamcast_ruta + "fonts/menu1.fnt");
    gm_ancho_map = 230;
    
    gm_ancho_map += 20;
    gm_alto_map = 15 * ((max_opcion / 2) + 3) + 30;
    
    graph = configuration_menu_crear_fondo(gm_ancho_map, gm_alto_map);
    
    x = 160;
    y = 120;
    z = -100;
    
    //Escribimos los textos fijos
    gm_text[0] = write (gm_font, 160, y - (gm_alto_map / 2) + 14, 4, "KEY CONFIGURATION");
    
    gm_text[27] = write_var(gm_font, 160, y - (gm_alto_map / 2) + 14 + 135, 4, gm_info);
    
    //Empezamos
    gm_max_buttons = joy_numbuttons(0);
    gm_max_hats = joy_numhats(0);
    //say("Joystick número: " + joy_number());
    //say("Numero de botones: " + gm_max_buttons);
    
    gm_text[1] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 30, 3, "Up:");
    gm_info = "Press UP key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        
        //comprobamos los hats
        if (!temp)
            for (cont = 0; cont < gm_max_hats; cont++)
                temp += joy_gethat(0, cont);
            end
        end
        //say("Tecla pulsada");
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        //comprobamos si existe un hat
        if (gm_max_hats > 0)
            cont = 0;
            temp = 0;
            //miramos todos los hats, a ver si hay alguna pulsación
            while ( (cont < gm_max_hats) && (temp == 0) )
                temp=joy_gethat(0, cont);
                cont++;
            end
        end
        
        if (temp > 0)
            //si se ha pulsado algún boton de algún hat, memorizamos el hat usado + 1
            temp_use_hats = cont;
        else
            temp = -1;
            for (cont = 0; cont < gm_max_buttons; cont++)
                if (joy_getbutton(0,cont)) temp = cont; end
                //say("Cont: " + cont + "   leido: " + joy_getbutton(0, cont));
            end
        end
        //say("Se está pulsando: " + temp);
        frame;
    end
    temp_keys[0] = temp;
    gm_text[15] = write(gm_font, 150, y - (gm_alto_map / 2) + 14 + 30, 5, temp);
    
    gm_text[2] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 30, 3, "Down:");
    gm_info = "Press DOWN key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        
        //comprobamos los hats
        if (temp_use_hats)
            temp = joy_gethat(0, temp_use_hats - 1);
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    //si había un hat seleccionado, lo comprobamos de este
    if (temp_use_hats)
        temp = 0;
        while (temp == 0)
            temp = joy_gethat(0, temp_use_hats - 1);
            frame;
        end
    else
        temp = -1;
        while (temp == -1)
            for (cont = 0; cont < gm_max_buttons; cont++)
                if (joy_getbutton(0, cont)) temp = cont; end
            end
            frame;
        end
    end
    temp_keys[1] = temp;
    gm_text[16] = write(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 30, 5, temp);
    
    gm_text[3] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 45, 3, "Left:");
    gm_info = "Press LEFT key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        
        //comprobamos los hats
        if (temp_use_hats)
            temp = joy_gethat(0, temp_use_hats - 1);
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    //si había un hat seleccionado, lo comprobamos de este
    if (temp_use_hats)
        temp = 0;
        while (temp == 0)
            temp = joy_gethat(0, temp_use_hats - 1);
            frame;
        end
    else
        temp = -1;
        while (temp == -1)
            for (cont = 0; cont < gm_max_buttons; cont++)
                if (joy_getbutton(0, cont)) temp = cont; end
            end
            frame;
        end
    end
    temp_keys[2] = temp;
    gm_text[17] = write(gm_font, 150, y - (gm_alto_map / 2) + 14 + 45, 5, temp);
    
    gm_text[4] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 45, 3, "right:");
    gm_info = "Press RIGHT key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        
        //comprobamos los hats
        if (temp_use_hats)
            temp = joy_gethat(0, temp_use_hats - 1);
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    //si había un hat seleccionado, lo comprobamos de este
    if (temp_use_hats)
        temp = 0;
        while (temp == 0)
            temp = joy_gethat(0, temp_use_hats - 1);
            frame;
        end
    else
        temp = -1;
        while (temp == -1)
            for (cont = 0; cont < gm_max_buttons; cont++)
                if (joy_getbutton(0, cont)) temp = cont; end
            end
            frame;
        end
    end
    temp_keys[3] = temp;
    gm_text[18] = write(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 45, 5, temp);
    
    gm_text[5] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 60, 3, "Jump:");
    gm_info = "Press JUMP key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end
    temp_keys[4] = temp;
    gm_text[19] = write(gm_font, 150, y - (gm_alto_map / 2) + 14 + 60, 5, temp);
    
    gm_text[6] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 60, 3, "Fire:");
    gm_info = "Press FIRE key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end
    temp_keys[5] = temp;
    gm_text[20] = write(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 60, 5, temp);
    
    gm_text[7] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 75, 3, "Prev. weapon:");
    gm_info = "Press PREVIOUS WEAPON key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end
    temp_keys[6] = temp;
    gm_text[21] = write(gm_font, 150, y - (gm_alto_map / 2) + 14 + 75, 5, temp);
    
    gm_text[8] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 75, 3, "Next weapon:");
    gm_info = "Press NEXT WEAPON key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end
    temp_keys[7] = temp;
    gm_text[22] = write(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 75, 5,temp);
    
    gm_text[9] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 90, 3, "Enter:");
    gm_info = "Press ENTER/PAUSE key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end
    temp_keys[8] = temp;
    gm_text[23] = write(gm_font, 150, y - (gm_alto_map / 2) + 14 + 90, 5, temp);
    
    gm_text[10] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 90, 3, "Esc:");
    gm_info = "Press ESC/CANCEL key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end
    temp_keys[9] = temp;
    gm_text[24] = write(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 90, 5, temp);
    
    gm_text[11] = write(gm_font, 160 - (gm_ancho_map / 2) + 10, y - (gm_alto_map / 2) + 14 + 105, 3, "Vol. up:");
    gm_info = "Press VOLUME UP key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end
    temp_keys[10] = temp;
    gm_text[25] = write(gm_font, 150, y - (gm_alto_map / 2) + 14 + 105, 5, temp);
    
    gm_text[12] = write(gm_font, 160, y - (gm_alto_map / 2) + 14 + 105, 3, "Vol. down:");
    gm_info = "Press VOLUME DOWN key.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end
    temp_keys[11] = temp;
    gm_text[26] = write(gm_font, 160 + (gm_ancho_map / 2) - 10, y - (gm_alto_map / 2) + 14 + 105, 5, temp);
    
    //Finalizando
    gm_info = "Press any key to finish.";
    repeat      //esperamos que no haya ningún botón pulsado
        temp = 0;
        for (cont = 0; cont < gm_max_buttons; cont++)
            temp = (temp || joy_getbutton(0, cont));
        end
        frame;
    until (!temp)
    //esperamos a que se pulse un boton
    temp = -1;
    while (temp == -1)
        for (cont = 0; cont < gm_max_buttons; cont++)
            if (joy_getbutton(0, cont)) temp = cont; end
        end
        frame;
    end


    //Rellenamos los datos antiguos con los datos nuevos
    for (cont = 0; cont < k_last; cont++)
        teclas[cont][1] = temp_keys[cont];
        config_data.teclas[cont][1] = temp_keys[cont];
    end
    teclas_hat_seleccionado = temp_use_hats;
    config_data.usar_joy_hat = temp_use_hats;
    //y salvamos los cambios
    save_config();
    
    
    for (cont = 0; cont <= 27; cont++)
        write_delete(gm_text[cont]);
    end
    fnt_unload(gm_font);
    map_unload(file, graph);
end