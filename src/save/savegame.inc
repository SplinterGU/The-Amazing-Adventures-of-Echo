function load_filegame (savegame pointer lf_data_ptr, int n)
//Carga un fichero de partida de juego
//	lf_data:	Estructura donde guardar los datos
//	n:			Número del fichero a leer
private
    string lf_file_name;
    int lf_file_id;
    int lf_data_readed;
    
	savegame lf_data;
    savegame_item_got lf_items;
    int32 dato;
    int dato_a_devolver;
    
    int cont1, cont2;
begin
    lf_file_name = get_pref_path("bennugd.org", "echo") + "data0" + itoa(n) + ".sav";
    if (fexists(lf_file_name) && (lf_data_ptr != NULL))
        lf_file_id = fopen(lf_file_name, o_read);
		
		//Leyendo datos salvados acerca del nivel/subnivel en el que se ha salvado
        lf_data_readed = fread(lf_file_id, lf_data);
        
		//say(itoa(lf_data_readed));
        if (lf_data_readed != sizeof(savegame))
            dato_a_devolver = 2;
			//say("Leido solo " + lf_data_readed + " datos.");
        end
		(*lf_data_ptr).level = lf_data.level;
		(*lf_data_ptr).sublevel = lf_data.sublevel;
		(*lf_data_ptr).init_level = lf_data.init_level;
		(*lf_data_ptr).difficulty = lf_data.difficulty;
		(*lf_data_ptr).lives = lf_data.lives;
		(*lf_data_ptr).armas = lf_data.armas;
		(*lf_data_ptr).max_energ = lf_data.max_energ;
		(*lf_data_ptr).energ = lf_data.energ;
		for (cont2 = 0; cont2 <= 3; cont2++)
			for (cont1= 0; cont1 <= CTE_LAST_WEAPON; cont1++)
				(*lf_data_ptr).armas_level[cont1][cont2] = lf_data.armas_level[cont1][cont2];
			end
		end
		
		
		//savegame_say(lf_data);
        
		//Número de items recogidos en el nivel
        fread(lf_file_id, dato);
        cont1 = dato;
        
		//Lectura de los objetos recogidos en el nivel
        //while (!feof(lf_file_id))
        for (cont2 = 0; cont2 < cont1; cont2++)
			//say(cont2 + "/" + cont1);
            fread(lf_file_id, dato);	//Nivel
            lf_items.level = dato;
            fread(lf_file_id, dato);	//Subnivel
            lf_items.sublevel = dato;
            fread(lf_file_id, dato);	//Pos x
            lf_items.pos_x = dato;
            fread(lf_file_id, dato);	//Pos y
            lf_items.pos_y = dato;
            fread(lf_file_id, dato);	//Número del item
            lf_items.item = dato;
            savegame_item_got_list_add(lf_items);	//Se añade a la lista global de objetos recogidos
			
			/*savegame_item_got_say(&lf_items);
			while (teclas[k_enter][2] != 1 && teclas[k_fire][2] != 1 && teclas[k_jump][2] != 1) frame; end
			teclas[k_enter][2] = 0;*/
            
            /*say("leido: lev"+lf_items.level+"-"+lf_items.sublevel+
                "   pos ("+lf_items.pos_x+","+lf_items.pos_y+
                ")   Item: "+lf_items.item);*/
        end
        //say("*************************************************************");
        
        fclose(lf_file_id);
    else
        dato_a_devolver = 1;
    end
    
    return (dato_a_devolver);   //1: fichero no encontrado
                                //2: tamaño incorrecto
end

function save_filegame (savegame pointer sf_data_ptr, int n)
//Guarda un fichero de partida de juego
//	sf_data:	Estructura donde se almacenan los datos de la partida
//	n:			Número del fichero a guardar
private
    string sf_file_name;
    int sf_file_id;
    int sf_data_readed;
    
	savegame sf_data;
    savegame_item_got pointer sf_ptr;
    int32 dato;
    int dato_a_devolver;
	
	int cont1, cont2;
begin
	if (sf_data_ptr != NULL)
		sf_file_name = get_pref_path("bennugd.org", "echo") + "data0" + itoa(n) + ".sav";
		sf_file_id = fopen(sf_file_name, o_write);
		
		//Copiando datos del puntero a la estructura de guardado
		sf_data.level = (*sf_data_ptr).level;
		sf_data.sublevel = (*sf_data_ptr).sublevel;
		sf_data.init_level = (*sf_data_ptr).init_level;
		sf_data.difficulty = (*sf_data_ptr).difficulty;
		sf_data.lives = (*sf_data_ptr).lives;
		sf_data.armas = (*sf_data_ptr).armas;
		sf_data.max_energ = (*sf_data_ptr).max_energ;
		sf_data.energ = (*sf_data_ptr).energ;
		for (cont2 = 0; cont2 <= 3; cont2++)
			for (cont1= 0; cont1 <= CTE_LAST_WEAPON; cont1++)
				sf_data.armas_level[cont1][cont2] = (*sf_data_ptr).armas_level[cont1][cont2];
			end
		end
		
		//Guardando datos salvados acerca del nivel/subnivel en el que se ha salvado
		sf_data_readed = fwrite(sf_file_id, sf_data);
		//say(itoa(sf_data_readed));
		if (sf_data_readed != sizeof(savegame))
			dato_a_devolver = 2;
		end
		
		//Número de items recogidos en el nivel
		dato = savegame_item_got_list_len();
		fwrite(sf_file_id, dato);
		
		//Lectura de los objetos recogidos en el nivel
		sf_ptr = savegame_item_got_list;
		while (sf_ptr != null)
			dato = sf_ptr.level;		//Nivel
			fwrite(sf_file_id, dato);
			dato = sf_ptr.sublevel;		//Subnivel
			fwrite(sf_file_id, dato);
			dato = sf_ptr.pos_x;		//Pos X
			fwrite(sf_file_id, dato);
			dato = sf_ptr.pos_y;		//Pos Y
			fwrite(sf_file_id, dato);
			dato = sf_ptr.item;			//Número de item
			fwrite(sf_file_id, dato);
			
			/*say("guardado: lev"+sf_ptr.level+"-"+sf_ptr.sublevel+
					"   pos ("+sf_ptr.pos_x+","+sf_ptr.pos_y+
					")   Item: "+sf_ptr.item);*/
					
			sf_ptr = sf_ptr.sig;
		end
		
		fclose(sf_file_id);
	else
		dato_a_devolver = 3;
	end
	
    return (dato_a_devolver);   //1: fichero no encontrado
                                //2: tamaño incorrecto
								//3: puntero vacío
end

//**************************************************************************
//  ESTRUCTURAS PARA EL JUEGO (PARTIDA EN CURSO)
//**************************************************************************

function refresh_actual_gamedata (savegame pointer rag_data)
//Almacena en una estructura de datos de salvar partida los datos de la partida en curso
private
    int cont1, cont2;
begin
    rag_data.level = next_level;
    rag_data.sublevel = next_sublevel;
    rag_data.init_level = init_level;
    
    rag_data.difficulty = dificultad;
    rag_data.lives = info_prota.vidas;
    
    rag_data.armas = 1;
    if (armas_get[1]) rag_data.armas = 2; end
    if (armas_get[2]) rag_data.armas += 4; end
    if (armas_get[3]) rag_data.armas += 8; end
    
    rag_data.max_energ = info_prota.p_max_energ;
    rag_data.energ = info_prota.p_energ;
    
    for (cont2 = 0; cont2 <= CTE_LAST_WEAPON; cont2++)
        for (cont1 = 0; cont1 <= 3; cont1++)
            rag_data.armas_level[cont2][cont1] = armas_level[cont2][cont1];
        end
    end
end

function load_actual_gamedata (savegame pointer lag_data)
//Carga en los datos globales de la partida (la que se va a jugar) los datos de una estructura de
//partida salvada (obtenida cn la carga de algún fichero)
private
    int cont1, cont2;
begin
    next_level = lag_data.level;
    next_sublevel = lag_data.sublevel;
    init_level = lag_data.init_level;
    
    dificultad = lag_data.difficulty;
    info_prota.vidas = lag_data.lives;
    
    if ((lag_data.armas & 1) == 1) armas_get[0] = 1; else armas_get[0] = 0; end
    if ((lag_data.armas & 2) == 2) armas_get[1] = 1; else armas_get[1] = 0; end
    if ((lag_data.armas & 4) == 4) armas_get[2] = 1; else armas_get[2] = 0; end
    if ((lag_data.armas & 8) == 8) armas_get[3] = 1; else armas_get[3] = 0; end
    
    info_prota.p_max_energ = lag_data.max_energ;
    info_prota.p_energ = lag_data.energ;
    
    init_weapons();
    for (cont2 = 0; cont2 <= CTE_LAST_WEAPON; cont2++)
        for (cont1 = 0; cont1 <= 3; cont1++)
			/*say("Copiando datos: Arma " + cont2 + " Nivel " + cont1 + "    Valor: " + 
				lag_data.armas_level[cont2][cont1]);*/
            armas_level[cont2][cont1] = lag_data.armas_level[cont2][cont1];
        end
    end
end

function load_default_gamedata (savegame pointer ldg_data, int ldg_dificultad, int ldg_vidas)
//Inicia los datos de una estructura de partida salvada con los valores de inicio de una partida cualquiera.
private
    int cont1, cont2;
begin
    ldg_data.level = 1;
    ldg_data.sublevel = 0;
    ldg_data.init_level = 0;
    
    ldg_data.difficulty = ldg_dificultad;
    ldg_data.lives = ldg_vidas;
    
    ldg_data.armas = 1;
    
    ldg_data.max_energ = 10;
    ldg_data.energ = 10;
    
    armas_level[0][0] = 0;
    armas_level[1][0] = 0;
    armas_level[2][0] = 0;
    armas_level[3][0] = 0;
    init_weapons();
    
    for (cont2 = 0; cont2 <= CTE_LAST_WEAPON; cont2++)
        for (cont1 = 0; cont1 <= 3; cont1++)
            ldg_data.armas_level[cont2][cont1] = armas_level[cont2][cont1];
        end
    end
    
    savegame_item_got_list_delete_all();
end

//******************************************************************************************************
//	DEBUG FUNCTIONS
//******************************************************************************************************
function savegame_say (savegame pointer ss_ptr)
private
	int cont;
begin
	if (ss_ptr != NULL)
		say("-> Level " + (*ss_ptr).level + "-" + (*ss_ptr).sublevel + "-" + (*ss_ptr).init_level +
			". Dif: " + (*ss_ptr).difficulty +
			". Lives: " + (*ss_ptr).lives + ". Energy: " + (*ss_ptr).energ + "/" + (*ss_ptr).max_energ);
		if (((*ss_ptr).armas & 1) == 1) say("    Blue Star."); end
		if (((*ss_ptr).armas & 2) == 2) say("    Leaf Blade."); end
		if (((*ss_ptr).armas & 4) == 4) say("    Green Cat."); end
		if (((*ss_ptr).armas & 8) == 8) say("    Sun Blaster."); end
		for (cont = 0; cont < CTE_LAST_WEAPON; cont++)
			say("    Weapon " + itoa(cont + 1) + " Level: " + (*ss_ptr).armas_level[cont][0] + "/" +
				(*ss_ptr).armas_level[cont][1] + "/" + (*ss_ptr).armas_level[cont][2] + "/" +
				(*ss_ptr).armas_level[cont][3] + ".");
		end
	else
		say("NO DATA");
	end
end

		
function savegame_item_got_say (savegame_item_got pointer sigs_ptr)
begin
	if (sigs_ptr != NULL)
		say("    -> Nivel " + (*sigs_ptr).level + "-" + (*sigs_ptr).sublevel + "  (" +
			(*sigs_ptr).pos_x + "," + (*sigs_ptr).pos_y + ") = " + (*sigs_ptr).item + ".");
	end
end