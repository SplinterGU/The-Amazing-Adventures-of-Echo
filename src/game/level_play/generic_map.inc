//**************************************************************************************************
//  FUNCIONES PRINCIPALES
//**************************************************************************************************

function int search_start_point (t_mapa pointer stp_nivel, t_mapa pointer stp_durezas, int n_start, int pointer stpx, int pointer stpy)
//Busca un tile de inicio de nivel (tile 100 en el mapa NIVEL) marcado con el número n_start
//(150+n_start en el mapa DUREZAS)
private
    int cont1;
    int cont2;
    int temp;
    int encontrado;
begin
    encontrado = 0;
    for(cont2 = 0; cont2 < [stp_nivel].filas; cont2++)
        for(cont1 = 0; cont1 < [stp_nivel].columnas; cont1++)
			temp = obtener_tile(stp_nivel, cont1, cont2, 0);
            if ((temp ==100) || (temp == 254))
                //say("encontrado inicio de nivel");
                say("encontrado subnivel " + (obtener_tile(stp_durezas,cont1,cont2,0)-150));
//				say(n_start);
            //if (253 == obtener_tile(&stp_nivel,cont1,cont2,0))
                if (n_start == (obtener_tile(stp_durezas, cont1, cont2, 0) - 150) )
                    say("encontrado! "+ cont1 + ", "+ cont2);
                    encontrado = 1;
                    *stpx = cont1;
                    *stpy = cont2;
                    //modificar_tile(&stp_nivel, cont1, cont2, 0, 0);
                    //modificar_tile(&stp_durezas, cont1, cont2, 0, 0);
                    break;
                end
            end
        end
        if (encontrado) break; end
    end
	
	return encontrado;
end

function borrar_items_conseguidos (int bic_lev1, int bic_lev2, t_mapa pointer bic_map)
//Busca la lista de objetos conseguidos (obtenida en el fichero de guardado), y los borra del
//mapa si existen
private
    savegame_item_got pointer aux_ptr;
begin
    aux_ptr = savegame_item_got_list;
    while (aux_ptr != null)
        if ((aux_ptr.level == bic_lev1) && (aux_ptr.sublevel == bic_lev2) &&
            (obtener_tile(bic_map, aux_ptr.pos_x, aux_ptr.pos_y, 0) == aux_ptr.item) )
            
            modificar_tile(bic_map, aux_ptr.pos_x, aux_ptr.pos_y, 0, 0);
        end
        
        aux_ptr = aux_ptr.sig;
    end
end

//**************************************************************************************************
//  BORRA UN TILE DETERMINADO DE TODO EL MAPA, por ejemplo, el tile de inicio una vez localizado
//  el que se buscaba entre todos los que hay
//**************************************************************************************************
function borrar_tile_de_todo_el_mapa (t_mapa pointer bttm_mapa, int n_tile)
private
    int cont1;
    int cont2;
begin
    for(cont2 = 0; cont2 < [bttm_mapa].filas; cont2++)
        for(cont1 = 0; cont1 < [bttm_mapa].columnas; cont1++)
            if (n_tile == obtener_tile(bttm_mapa, cont1, cont2, 0))
                modificar_tile(bttm_mapa, cont1, cont2, 0, 0);
            end
        end
    end
end

//**************************************************************************************************
//  BUSCA EL MAYOR NÚMERO DE TILES QUE SE PUEDEN AGRUPAR, devolviendo ancho y alto
//**************************************************************************************************
function grupo_tiles_mas_grande (t_mapa pointer gtmg_mapa, int posx, int posy, int posz,
                                 int pointer tamx, int pointer tamy)
private
    int gtmg_tiles[2][2];
    
    byte grupo12 = 0;
    byte grupo13 = 0;
    byte grupo21 = 0;
    byte grupo31 = 0;
    byte grupo22 = 0;
    byte grupo23 = 0;
    byte grupo32 = 0;
    byte grupo33 = 0;
begin
    gtmg_tiles[0][0] = obtener_tile(gtmg_mapa, posx  , posy  , posz);
    gtmg_tiles[1][0] = obtener_tile(gtmg_mapa, posx+1, posy  , posz);
    gtmg_tiles[2][0] = obtener_tile(gtmg_mapa, posx+2, posy  , posz);
    gtmg_tiles[0][1] = obtener_tile(gtmg_mapa, posx  , posy+1, posz);
    gtmg_tiles[1][1] = obtener_tile(gtmg_mapa, posx+1, posy+1, posz);
    gtmg_tiles[2][1] = obtener_tile(gtmg_mapa, posx+2, posy+1, posz);
    gtmg_tiles[0][2] = obtener_tile(gtmg_mapa, posx  , posy+2, posz);
    gtmg_tiles[1][2] = obtener_tile(gtmg_mapa, posx+1, posy+2, posz);
    gtmg_tiles[2][2] = obtener_tile(gtmg_mapa, posx+2, posy+2, posz);
    
    if (gtmg_tiles[0][1] == gtmg_tiles[0][0]) grupo12 = 1; end
    if (grupo12 && (gtmg_tiles[0][2] == gtmg_tiles[0][0])) grupo13 = 1; end
    
    if (gtmg_tiles[1][0] == gtmg_tiles[0][0]) grupo21 = 1; end
    if (grupo21 && (gtmg_tiles[2][0] == gtmg_tiles[0][0])) grupo31 = 1; end
    
    if (grupo12 && grupo21 && (gtmg_tiles[1][1] == gtmg_tiles[0][0])) grupo22 = 1; end
    
    if (grupo13 && grupo22 && (gtmg_tiles[1][2] == gtmg_tiles[0][0])) grupo23 = 1; end
    if (grupo31 && grupo22 && (gtmg_tiles[2][1] == gtmg_tiles[0][0])) grupo32 = 1; end
    
    if (grupo23 && grupo32 && (gtmg_tiles[2][2] == gtmg_tiles[0][0])) grupo33 = 1; end
    
    switch (1)
    case grupo33: *tamx = 3; *tamy = 3; end
    case grupo23: *tamx = 2; *tamy = 3; end
    case grupo32: *tamx = 3; *tamy = 2; end
    case grupo22: *tamx = 2; *tamy = 2; end
    case grupo13: *tamx = 1; *tamy = 3; end
    case grupo31: *tamx = 3; *tamy = 1; end
    case grupo12: *tamx = 1; *tamy = 2; end
    case grupo21: *tamx = 2; *tamy = 1; end
    default: *tamx = 1; *tamy = 1; end
    end //switch
end

//**************************************************************************************************
//  SUSTITUYE LOS TILES CON DUREZAS DE AGUA, de forma que en el mapa visible queden tiles especiales
//  que los identifican y generan el tile de agua más grande que pueden.
//**************************************************************************************************
process tile_agua (int ta_tile_ant, int ta_tilex, int ta_tiley)
begin
    file = enem_grafs[0][cte_tiles_agua];
    z = 1;
    //z = -2000;
    flags = 4;
    priority = -100;
    
    //say (ta_tile_ant);
    if (ta_tile_ant >= CTE_INICIO_TILES_AGUA)
        if (ta_tile_ant < CTE_INICIO_TILES_AGUA + 100)
            graph = obtener_tile(&durezas, ta_tilex, ta_tiley, 0);
			if (graph >= 150) graph = 1; end
            modificar_tile(&nivel, ta_tilex, ta_tiley, 0, ta_tile_ant - CTE_INICIO_TILES_AGUA);
        else
            
        end
    end
    
    x2 = (ta_tilex * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (ta_tiley * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    loop
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        //say("pos: " + x2 + "," + y2);
        //say("pos: " + x + "," + y + " graph: " + graph + " file: " + file);
        if ((x < -25) || (x > 345) || (y < -25) || (y > 265)) break; end
        frame;
    end
    
    modificar_tile(&nivel, ta_tilex, ta_tiley, 0, ta_tile_ant);
    //say("adios");
end

//Esto optimiza los tiles de agua
/*function add_tiles_agua (t_mapa pointer ata_nivel, t_mapa pointer ata_durezas)
private
    int ata_tile;
    int cont_fil, cont_col;
begin
    say("metiendo tiles de agua");
    for (cont_fil=0; cont_fil<[ata_durezas].filas; cont_fil++)
        for (cont_col=0; cont_col<[ata_durezas].columnas; cont_col++)
            ata_tile = obtener_tile(ata_durezas, cont_col, cont_fil, 0);
            switch (ata_tile)
            case 50:
                say("tile básico: " + cont_col + "," + cont_fil);
                ata_tile = obtener_tile(ata_nivel, cont_col, cont_fil, 0) + CTE_INICIO_TILES_AGUA;
                modificar_tile(ata_nivel,cont_col,cont_fil,0,ata_tile);
            end
            case 51..99:
                say("tile normal: " + cont_col + "," + cont_fil);
                ata_tile = obtener_tile(ata_nivel, cont_col, cont_fil, 0) + CTE_INICIO_TILES_AGUA;
                modificar_tile(ata_nivel,cont_col,cont_fil,0,ata_tile);
            end
            end //switch
        end
    end
end*/

//**************************************************************************************************
//  SUSTITUYE TILES REPETIDOS POR UN TILE. Coge hasta 3x3 tiles iguales y los sustituye por uno
//  que se ha creado copiando dicho tile esas veces.
//**************************************************************************************************
function crear_tiles_optimizados (int cto_tile, int cto_pos, int cto_ancho_tile, int cto_alto_tile, file)
private
    int cont_limite_fil, cont_limite_col;
    int cont_fil,cont_col;
    int cto_centro_x, cto_centro_y;
    
//    int temp_map;
begin
    //para cada tamaño de tile, desde 1x1 hasta 3x3
    for (cont_limite_fil = 1; cont_limite_fil <= 3; cont_limite_fil++)
        for (cont_limite_col = 1; cont_limite_col <= 3; cont_limite_col++)
            //Si no es el tile de 1x1
            if ((cont_limite_fil != 1) || (cont_limite_col != 1))
                //Se crea el nuevo mapa de tamaño x*y
                graph = map_new(cto_ancho_tile * cont_limite_col, cto_alto_tile * cont_limite_fil);
                //Y se rellena de copias del mismo mapa
                //Creamos una copia del tile para facilitar la creación
//                temp_map = map_clone(file, cto_tile);
                for (cont_fil = 0; cont_fil < cont_limite_fil; cont_fil++)
                    for (cont_col = 0; cont_col < cont_limite_col; cont_col++)
                        map_put(0, graph, file, cto_tile,
                                (cto_ancho_tile * cont_col) + graphic_info(file, cto_tile, G_CENTER_X),
                                (cto_alto_tile * cont_fil) + graphic_info(file, cto_tile, G_CENTER_Y)
                               );
                    end
                end
                //Se le añade el centro
                cto_centro_x = graphic_info(file, cto_tile, G_CENTER_X);
                cto_centro_y = graphic_info(file, cto_tile, G_CENTER_Y);
                if (cont_limite_col == 3) cto_centro_x += cto_ancho_tile; end
                if (cont_limite_fil == 3) cto_centro_y += cto_alto_tile; end
                center_set(0, graph, cto_centro_x, cto_centro_y);
                //Y se añade a los mapas especiales
                tiles_optimizados[(100 * cto_pos) + ((cont_limite_fil - 1) * 3) + cont_limite_col - 1] = graph;
            end
        end
    end
end

function optimice_map (t_mapa pointer om_mapa, int om_nivel, int om_subnivel, file)
private
    int tiles_a_optimizar[9];
    int om_max_col, om_max_fil;
    
    int cont_col, cont_fil, cont_capa;
    int cont_col2, cont_fil2;
    int cont_tile;
    int temp_tile;
    int temp_tilex, temp_tiley;
begin
    //Se seleccionan los tiles que requieren optimización, porque se repiten, según el nivel
    switch (om_nivel)
    case 1:
        tiles_a_optimizar[0] = 1;
        tiles_a_optimizar[1] = 12;
        tiles_a_optimizar[2] = 20;
        tiles_a_optimizar[3] = 50;
        tiles_a_optimizar[4] = 57;
        tiles_a_optimizar[5] = 30;
        tiles_a_optimizar[6] = 37;
        tiles_a_optimizar[7] = 60;
        tiles_a_optimizar[8] = 0;
        tiles_a_optimizar[9] = 0;
    end
    case 3:
        tiles_a_optimizar[0] = 1;
        tiles_a_optimizar[1] = 2;
        tiles_a_optimizar[2] = 20;
        tiles_a_optimizar[3] = 31;
        tiles_a_optimizar[4] = 45;
        tiles_a_optimizar[5] = 46;
        tiles_a_optimizar[6] = 47;
        tiles_a_optimizar[7] = 65;
        tiles_a_optimizar[8] = 71;
        tiles_a_optimizar[9] = 72;
    end
    case 4:
        switch (om_subnivel)
        case 0:
            tiles_a_optimizar[0] = 1;
            tiles_a_optimizar[1] = 18;
            tiles_a_optimizar[2] = 19;
            tiles_a_optimizar[3] = 34;
            tiles_a_optimizar[4] = 35;
            tiles_a_optimizar[5] = 38;
            tiles_a_optimizar[6] = 40;
            tiles_a_optimizar[7] = 41;
            tiles_a_optimizar[8] = 0;
            tiles_a_optimizar[9] = 0;
        end
		end //switch
	end
	case 5:
		switch (om_subnivel)
        case 0..3:
            tiles_a_optimizar[0] = 1;
            tiles_a_optimizar[1] = 25;
            tiles_a_optimizar[2] = 33;
            tiles_a_optimizar[3] = 34;
            tiles_a_optimizar[4] = 35;
            tiles_a_optimizar[5] = 30;
            tiles_a_optimizar[6] = 31;
            tiles_a_optimizar[7] = 57;
            tiles_a_optimizar[8] = 58;
            tiles_a_optimizar[9] = 0;
        end
        end //switch
    end
    end //switch
    
    //Se generan los gráficos de los tiles agrupados
    for (cont_tile = 0; cont_tile < 10; cont_tile++)
        if (tiles_a_optimizar[cont_tile] != 0)
            crear_tiles_optimizados (tiles_a_optimizar[cont_tile], cont_tile,
                                     [om_mapa].ancho_tile, [om_mapa].alto_tile, file);
        else
            break;
        end
    end
    
    //Se recorre el mapa entero optimizando
	for (cont_capa = 0; cont_capa < [om_mapa].capas; cont_capa++)
		for (cont_fil = 0; cont_fil < [om_mapa].filas; cont_fil++)
			for (cont_col = 0; cont_col < [om_mapa].columnas; cont_col++)
				
				temp_tile = obtener_tile(om_mapa, cont_col, cont_fil, cont_capa);
				//Si hay un tile, se comprueba si se puede optimizar
				if (temp_tile != 0)
					//Se comprueba si se trata de un tile optimizable
					cont_tile = 0;
					for (cont_tile = 0; cont_tile < 10; cont_tile++)
						//Si es un tile optimizable
						if (tiles_a_optimizar[cont_tile] == temp_tile)
							
							//Se busca el grupo más grande de tiles iguales a este
							grupo_tiles_mas_grande (om_mapa, cont_col, cont_fil, cont_capa, &om_max_col, &om_max_fil);
							//Comprobamos que no es un tile de 1x1
							if ((om_max_col != 1) && (om_max_fil != 1))
								//inicialmente ponemos todos a cero
								for (cont_fil2 = 0; cont_fil2 < om_max_fil; cont_fil2++)
									for (cont_col2 = 0; cont_col2 < om_max_col; cont_col2++)
										modificar_tile(om_mapa, cont_col + cont_col2, cont_fil + cont_fil2,
											cont_capa, 0);
									end
								end
								//y añadimos el tile nuevo en la posición adecuada
								if (om_max_col == 3)
									temp_tilex = cont_col + 1;
								else
									temp_tilex = cont_col;
								end
								if (om_max_fil == 3)
									temp_tiley = cont_fil + 1;
								else
									temp_tiley = cont_fil;
								end
								modificar_tile(om_mapa, temp_tilex, temp_tiley, cont_capa,
												CTE_INICIO_TILES_OPTIMIZADOS + cont_tile * 100 + 
												((om_max_fil - 1) * 3) + om_max_col - 1);
							end
							break;  //y salimos
						end
					end
				end
			end
		end
    end
	
    /*save_tmap_tmf(om_mapa,"D:\Fenix\Proyectos\Tileador\Echo3\prueba.tmf");
    file = new_fpg();
    for(cont_col = 0; cont_col < 999; cont_col++)
        if (tiles_optimizados[cont_col] != 0)
            fpg_add(file, cont_col + 1, 0, tiles_optimizados[cont_col]);
        end
    end
    save_fpg(file,"D:\Fenix\Proyectos\Tileador\Echo3\optim.fpg");*/
end

