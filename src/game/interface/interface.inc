function load_interface ()
private
    int temp_fpg;
    int cont;
begin
    temp_fpg = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/interface.fpg");
    //copiamos los números para poder usar luego map_put o similares
    for (cont = 0; cont < 10; cont++)
        interfaz_grafs[cont] = map_clone(temp_fpg, cont + 1);
    end

    //creamos el cuadro estático de la interfaz (no cambia, contiene nombres y las barras)
    interfaz_grafs[INTERFAZ_FONDO_BLANCO] = map_new(244, 17);
    center_set(0, interfaz_grafs[INTERFAZ_FONDO_BLANCO], 0, 0);
	
    //colocamos los nombres
    map_put(0, interfaz_grafs[INTERFAZ_FONDO_BLANCO], temp_fpg, 11, 0, 0);
    map_put(0, interfaz_grafs[INTERFAZ_FONDO_BLANCO], temp_fpg, 12, 0, 9);

    //dibujamos las barras	
    drawing_map(0, interfaz_grafs[INTERFAZ_FONDO_BLANCO]);
    drawing_color(rgb(255, 255, 255));
    draw_rectangle(40, 0, 243-40, 6);
    draw_rectangle(41, 0, 242-41, 6);
    draw_rectangle(40, 9, 243-40, 15-9);
    draw_rectangle(41, 9, 242-41, 15-9);
    
    //y creamos los gráficos que contienen los valores numéricos
    interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA] = map_clone(temp_fpg, 13);
    interfaz_grafs[INTERFAZ_NUMEROS_EXP] = map_clone(temp_fpg, 13);
    interfaz_grafs[INTERFAZ_FONDO_FPG] = map_clone(temp_fpg, 14);
    
    //por último, guardamos en memoria una copia de los símbolos de las armas
    region_define(CTE_REGION_INTERFAZ_ARMAS,0, 217, 73, 22);
    interfaz_grafs[INTERFAZ_ARMA1] = map_clone(temp_fpg, 21);
    interfaz_grafs[INTERFAZ_ARMA2] = map_clone(temp_fpg, 22);
    interfaz_grafs[INTERFAZ_ARMA3] = map_clone(temp_fpg, 23);
    interfaz_grafs[INTERFAZ_ARMA4] = map_clone(temp_fpg, 24);
    
    //mapas para la energía del enemigo
    interfaz_grafs[INTERFAZ_ENEM_ENER] = map_clone(temp_fpg, 15);
    
    //mapas para el savegame
    interfaz_grafs[INTERFAZ_SALVADO1] = map_clone(temp_fpg, 18);
    interfaz_grafs[INTERFAZ_SALVADO2] = map_clone(temp_fpg, 19);
    
    fpg_unload(temp_fpg);
end

function refresh_interface_energy ()
private
    int temp;
begin
    temp = (info_prota.p_energ * 200) / info_prota.p_max_energ;
    //say(itoa(temp));
    drawing_map(0, interfaz_grafs[INTERFAZ_FONDO_BLANCO]);
    if (temp > 0)
        //Coloreando de rojo la parte de energía que se tiene
        drawing_color(rgb(255, 0, 0));
        draw_rectangle_filled(42, 1, /*41 +*/ temp, 5-1);
    end
    if (temp < 200)
        //Coloreando de transparente la parte de energía que falta
        drawing_color(0 /*rgb(0, 0, 0)*/);
        draw_rectangle_filled(42 + temp, 1, 241-42, 5-1);
    end
	
    //energia actual (numeros)
    map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA], interfaz_grafs[info_prota.p_energ % 10], 7, 0, 0, 100, B_NOCOLORKEY);
    if (info_prota.p_energ < 10)
        drawing_map(0, interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA]);
        drawing_color(0);
        draw_rectangle_filled(0, 0, 6, 6);
    else
        map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA], interfaz_grafs[info_prota.p_energ / 10], 0, 0, 0, 100, B_NOCOLORKEY);
    end
	
    //energia máxima (numeros)
    if (info_prota.p_max_energ < 10)
        map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA], interfaz_grafs[info_prota.p_max_energ], 27, 0, 0, 100, B_NOCOLORKEY);
        drawing_map(0, interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA]);
        drawing_color(0);
        draw_rectangle_filled(20, 0, 27-20, 6);
    else
        map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA], interfaz_grafs[info_prota.p_max_energ % 10], 27, 0, 0, 100, B_NOCOLORKEY);
        map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA], interfaz_grafs[info_prota.p_max_energ / 10], 20, 0, 0, 100, B_NOCOLORKEY);
    end
end

function refresh_interface_wexp()
private
    int temp1;
    int temp2;
    int temp3;
begin
	//say_weapons();
	//say("Arma seleccionada: " + armas_select + ". Armas curr level:" + armas_curr_level);
    if (armas_curr_level == 0)
		temp1 = 0;
	else
		temp1 = armas_level[armas_select][armas_curr_level];
	end
    temp2 = armas_level[armas_select][armas_curr_level + 1];
	//say(temp1 + "," + temp2);
    //calculamos el porcentaje
    temp3 = ((armas_level[armas_select][0] - temp1) * 200) / (temp2 - temp1);
	//say("Porcentaje: " + temp3);
    
    //pintamos la barra
    drawing_map(0, interfaz_grafs[INTERFAZ_FONDO_BLANCO]);
    if (temp3 > 0)
        switch (armas_curr_level)
        case 0: drawing_color(rgb(0, 0, 255)); end
        case 1: drawing_color(rgb(0, 128, 255)); end
        case 2: drawing_color(rgb(117, 217, 255)); end
        end //switch
        draw_rectangle_filled(42, 10, 41 + temp3 - 42, 14 - 10);
    end
    if (temp3 < 200)
        switch (armas_curr_level)
        case 0: drawing_color(rgb(0, 0, 0)); end
        case 1: drawing_color(rgb(0, 0, 255)); end
        case 2: drawing_color(rgb(0, 128, 255)); end
        end //switch
        draw_rectangle_filled(42 + temp3, 10, 241 - 42, 14 - 10);
    end
    
    //pintamos energía actual
    temp3 = armas_level[armas_select][0] - temp1;
    map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_EXP], interfaz_grafs[temp3 % 10], 7, 0, 0, 100, B_NOCOLORKEY);
    if (temp3 < 10)
        drawing_map(0, interfaz_grafs[INTERFAZ_NUMEROS_EXP]);
        drawing_color(0);
        draw_rectangle_filled(0, 0, 6, 6);
    else
        map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_EXP], interfaz_grafs[temp3 / 10], 0, 0, 0, 100, B_NOCOLORKEY);
    end
	
    //pintamos max energía del nivel
    temp3 = temp2 - temp1;
    if (temp3 < 10)
        map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_EXP], interfaz_grafs[temp3], 27, 0, 0, 100, B_NOCOLORKEY);
        drawing_map(0, interfaz_grafs[INTERFAZ_NUMEROS_EXP]);
        drawing_color(0);
        draw_rectangle_filled(20, 0, 27-20, 6);
    else
        map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_EXP], interfaz_grafs[temp3 % 10], 27, 0, 0, 100, B_NOCOLORKEY);
        map_xput(0, interfaz_grafs[INTERFAZ_NUMEROS_EXP], interfaz_grafs[temp3 / 10], 20, 0, 0, 100, B_NOCOLORKEY);
    end
end

function refresh_weapons ()
private
    int cont;
begin
    for (cont = 1; cont <= CTE_LAST_WEAPON; cont++)
        if (armas_get[cont])
            interfaz_armas_id[cont - 1].graph = interfaz_grafs[INTERFAZ_ARMA1 - 1 + cont];
            if (armas_select == cont)
				interfaz_armas_id[cont - 1].flags = 0;
			else
				interfaz_armas_id[cont - 1].flags = 4;
			end
        else
            interfaz_armas_id[cont - 1].graph = 0;
        end
    end
    
    mover_iconos_armas_interfaz();
end

function refresh_interface ()
begin
    refresh_interface_energy();
    refresh_interface_wexp();
    refresh_weapons();
end

function unload_interface ();
private
    int cont;
begin
    for (cont = 0; cont < INTERFAZ_LAST; cont++)
        map_unload(0, interfaz_grafs[cont]);
    end
end
