process tile ()
begin
     signal(id,s_freeze);
     frame;
end

function tscroll_generar_no_tile (tscroll pointer ts_struct, int ts_tile, int ts_posx, int ts_posy, int cont_z)
begin
	switch (ts_tile)
    //enemigos
    case 150: guerrillero(ts_posx,ts_posy,enem_grafs[0][cte_guerrillero],0); end    //si cambias cte,cambia en enem
    case 151: guerrillero(ts_posx,ts_posy,enem_grafs[0][cte_guerrillero],1); end    //si cambias cte,cambia en enem
    case 152: spider(ts_posx,ts_posy,7); end
    case 153: super_guerrillero(ts_posx,ts_posy,enem_grafs[0][cte_s_guerrillero],0); end
    case 154: volador1(ts_posx,ts_posy,enem_grafs[0][cte_volador1],3); end
    case 155: corvo(ts_posx,ts_posy,enem_grafs[0][cte_volador1],3); end
    case 156: volador1(ts_posx,ts_posy,enem_grafs[0][cte_murcielago],3); end
    case 157: murcielago(ts_posx,ts_posy,3); end
    case 158: blobo(ts_posx,ts_posy,enem_grafs[0][cte_blobo],9); end
    case 159: ghost_fly(ts_posx,ts_posy,7); end
    case 160: ghost_fly_invencible(ts_posx,ts_posy); end
    case 161: invencible_enem(ts_posx,ts_posy,enem_grafs[0][cte_hotta]); end
    case 162: mina(ts_posx,ts_posy); end
    case 163: flozat (ts_posx,ts_posy,enem_grafs[0][cte_flozat],9); end
    case 164: volador1(ts_posx,ts_posy,enem_grafs[0][cte_volador1],7); end
    case 165: corvo(ts_posx,ts_posy,enem_grafs[0][cte_volador1],7); end
    case 166: glotz(ts_posx,ts_posy,enem_grafs[0][cte_glotz],9); end
    case 167: canon(ts_posx,ts_posy,enem_grafs[0][cte_canon],0); end
    case 168: canon(ts_posx,ts_posy,enem_grafs[0][cte_canon],1); end
    case 169: guerrillero(ts_posx,ts_posy,enem_grafs[0][cte_flerris],0); end    //si cambias cte,cambia en enem
    case 170: guerrillero(ts_posx,ts_posy,enem_grafs[0][cte_flerris],1); end    //si cambias cte,cambia en enem
    case 171: super_guerrillero(ts_posx,ts_posy,enem_grafs[0][cte_s_flerrus],0); end
    case 172: spikes(ts_posx,ts_posy,enem_grafs[0][cte_spikes]); end
    case 173: excaver(ts_posx,ts_posy,enem_grafs[0][cte_excaver]); end
    case 174: roca_lanzador (ts_posx,ts_posy,enem_grafs[0][cte_rock],0); end
    case 175: vigilante_horus (ts_posx,ts_posy,enem_grafs[0][cte_vigilante],0); end
    case 176: vigilante_horus (ts_posx,ts_posy,enem_grafs[0][cte_vigilante],1); end
    case 177: blobo(ts_posx,ts_posy,enem_grafs[0][cte_blobo],22); end   //Blobo poderoso
    case 178: volador1(ts_posx,ts_posy,enem_grafs[0][cte_volador2],15); end   //volador nivel 3
    case 179: corvo(ts_posx,ts_posy,enem_grafs[0][cte_volador2],15); end      //volador nivel 3
    
    //puertas
    case 200: door(ts_posx,ts_posy,id_tscroll.ts_file,obj_interruptor[cte_door]); end
    case 201: bridge(ts_posx,ts_posy,id_tscroll.ts_file,obj_interruptor[cte_bridge],2,1,0); end
    case 202: bridge(ts_posx,ts_posy,id_tscroll.ts_file,obj_interruptor[cte_bridge],2,2,0); end
    case 203: bridge(ts_posx,ts_posy,id_tscroll.ts_file,obj_interruptor[cte_bridge],2,3,0); end
    case 204: bridge(ts_posx,ts_posy,id_tscroll.ts_file,obj_interruptor[cte_bridge],2,4,0); end
    
    //items importantes 
    case 225: item_add_energy(ts_posx,ts_posy); end
    case 226: new_weapon(ts_posx,ts_posy,0); end
    case 227: new_weapon(ts_posx,ts_posy,1); end
    case 228: new_weapon(ts_posx,ts_posy,2); end
    
    //interruptores
    case 249: button(ts_posx,ts_posy,item_grafs,249); end
    
    //cambio nivel
    case 251: item_end_sublevel(ts_posx,ts_posy); end
    case 252: item_end_level(ts_posx,ts_posy); end
    case 253: event(ts_posx,ts_posy); end
    
    //objetos animados
    case 275: objeto_animado_sincronizado(ts_posx,ts_posy,(-cont_z*2)-1,enem_grafs[0][cte_anim_level],0,
                                          0,1); end  //sin transparencia, anim 0
    case 276: objeto_animado_sincronizado(ts_posx,ts_posy,(-cont_z*2)-1,enem_grafs[0][cte_anim_level],160,
                                          0,1); end  //con transparencia, anim 0
    //case 275: objeto_animado(ts_posx,ts_posy,(-cont_z*2)-1,enem_grafs[0][cte_anim_level],0,0); end  //sin transparencia, anim 0
    //case 276: objeto_animado(ts_posx,ts_posy,(-cont_z*2)-1,enem_grafs[0][cte_anim_level],160,0); end  //con transparencia, anim 0
	
	//Plataformas
	case 300: plataforma_auto_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 1); end
	case 301: plataforma_auto_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 2); end
	case 302: plataforma_auto_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 3); end
	case 303: plataforma_auto_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 5); end
	case 304: plataforma_auto_desaparece2 (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 1); end
	case 305: plataforma_auto_desaparece2 (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 2); end
	case 306: plataforma_auto_desaparece2 (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 3); end
	case 307: plataforma_auto_desaparece2 (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 5); end
	
	case 310: plataforma_solida_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 11, 16, 20); end
	case 311: plataforma_atravesable_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 11, 16, 20); end
    end //switch
end
//**************************************************************************************
//  FUNCIONES DE MANEJO DE LA LISTA DE TILES
//**************************************************************************************

function tscroll_obtener_tile (tscroll pointer ts_struct, int at_posx, int at_posy, int at_posz)
private
	int dato_a_devolver;
    int at_pos;
begin
    at_pos = (at_posz * [ts_struct].n_tiles_capa)+
              ((at_posy % [ts_struct].tmapa[0].filas) * [ts_struct].tmapa[0].columnas)+
               (at_posx % [ts_struct].tmapa[0].columnas);
	//say("pos mapa: " + at_pos);	
	dato_a_devolver = [ts_struct].tmapa[0].b_mapa[at_pos];
    return (dato_a_devolver);
end

/*function borrar_tiles_sobrantes (ptr_aux)
//Elimina los procesos tile del final de la lista. Se le pasa como parámetro el último
//tile VÁLIDO (este no se borra)
//NOTA: aprovecha la variable local tscroll_ptr_sig
begin
	if (ptr_aux != 0)
		tscroll_ptr_sig = ptr_aux.tscroll_ptr_sig;
		ptr_aux.tscroll_ptr_sig = 0;
		while (tscroll_ptr_sig != 0)
			ptr_aux = tscroll_ptr_sig;
			tscroll_ptr_sig = tscroll_ptr_sig.tscroll_ptr_sig;
			if (exists(ptr_aux))
				signal (ptr_aux,s_kill);
			end
		end
	end
end*/

function ts_actualiza_tiles (tscroll pointer ts_struct)
private
	int n_tiles;
	int cont;
begin
	[ts_struct].forzar_refresco = 1;
	
	memset([ts_struct].ptr_array_tiles, 0,
				[ts_struct].n_columnas * [ts_struct].n_filas * [ts_struct].n_capas);// * sizeof(int));
end

/*function ts_actualiza_tiles (tscroll pointer ts_struct)
// Refresca toda la lista de tiles: añade o quita según sea necesario, y los coloca
//en su posición, les asigna el gráfico...
private
    int temp_x;       //posición x del primer tile
    int temp_y;       //posición y del primer tile
    int cont_x;
    int cont_y;
    int cont_z;
    int ptr_aux;      //puntero auxiliar para leer los tiles de la lista
    int at_posx;
    int at_posy;
    int at_tile;      //almacena temporalmente el tile
    //byte first_tile;   //indica que hay que actualizar el primer tile de la lista
begin
	//debug;
	if (ts_struct != NULL)
		if ([ts_struct].estado == CTE_TSCROLL_ESTADO_ACTIVO)
			//Antes que nada, vamos a ver dónde se pone el tile de la esquina superior izqu
			temp_x = [ts_struct].tileador_posx - [ts_struct].camera_x_tile;
			temp_y = [ts_struct].tileador_posy - [ts_struct].camera_y_tile;
			//Ponemos el puntero auxiliar señalando el primer tile de la lista
			//ptr_aux=[ts_struct].id_tscroll;
			ptr_aux = 0;

			//y ahora recorremos tantas posiciones como tiles quepan en pantalla
			for (cont_z = 0; cont_z < [ts_struct].tmapa[0].capas; cont_z++)
				for (cont_y = 0; cont_y < [ts_struct].n_filas; cont_y++)
					//comprobamos si el scroll es cíclico: si no lo es evitaremos los tiles fuera
					//del mapa y ahorraremos cálculos; si lo es, los cálculos son más sencillos
					if (([ts_struct].tscroll_flags & 2) == 0)
						//scroll no cíclico en y
						at_posy = [ts_struct].visible_ty + cont_y;
						if ((at_posy >= 0) && (at_posy < [ts_struct].tmapa[0].filas))
							//dentro del mapa en y
						   
							//***********************************************************
							for (cont_x = 0; cont_x < [ts_struct].n_columnas; cont_x++)

								//comprobamos si el scroll es cíclico: si no lo es evitaremos los
								//tiles fuera del mapa y ahorraremos cálculos; si lo es,
								//los cálculos son más sencillos
								if (([ts_struct].tscroll_flags & 1) == 0)
									//scroll no cíclico en x
									at_posx = [ts_struct].visible_tx + cont_x;
									if ((at_posx >= 0) && (at_posx < [ts_struct].tmapa[0].columnas))
										//dentro del mapa en x

										include "procesos_zoom/add_tile.inc";
										
									end
									if (at_posx >= [ts_struct].tmapa[0].columnas)
										//hemos salido del mapa, pongamos el contador x al final de la cuenta para avanzar
										//al próximo ciclo en y
										cont_x = [ts_struct].n_columnas;
									end
								else
									//scroll cíclico en x
									at_posx = [ts_struct].visible_tx1 + cont_x;
									//if (at_posx<0) at_posx+=[ts_struct].tmapa[0].columnas; end   //nunca sera negativo
									at_posx = at_posx % [ts_struct].tmapa[0].columnas;
								   
									include "procesos_zoom/add_tile.inc";
								end
							end  //for x
							//***********************************************************
						   
						end //if dentro mapa
						if (at_posy >= [ts_struct].tmapa[0].filas)
							//hemos salido del mapa, pongamos el contador y al final de la cuenta para avanzar
							//al próximo ciclo en z
							cont_y = [ts_struct].n_filas;
						end
					else
						//scroll cíclico en y
						at_posy = [ts_struct].visible_ty1 + cont_y;
						//if (at_posy<0) at_posy+=[ts_struct].tmapa[0].filas; end  //nunca será negativo
						at_posy = at_posy % [ts_struct].tmapa[0].filas;
						 
						//copy/paste de x
						//***********************************************************
						for (cont_x = 0; cont_x < [ts_struct].n_columnas; cont_x++)

							//comprobamos si el scroll es cíclico: si no lo es evitaremos los
							//tiles fuera del mapa y ahorraremos cálculos; si lo es,
							//los cálculos son más sencillos
							if (([ts_struct].tscroll_flags & 1) == 0)
								//scroll no cíclico en x
								at_posx = [ts_struct].visible_tx + cont_x;
								if ((at_posx >= 0) && (at_posx < [ts_struct].tmapa[0].columnas))
									//dentro del mapa en x
									
									include "procesos_zoom/add_tile.inc";
								end
								if (at_posx >= [ts_struct].tmapa[0].columnas)
									//hemos salido del mapa, pongamos el contador x al final de la cuenta para avanzar
									//al próximo ciclo en y
									cont_x = [ts_struct].n_columnas;
								end
							else
								//scroll cíclico en x
								at_posx = [ts_struct].visible_tx1 + cont_x;
								//if (at_posx<0) at_posx+=[ts_struct].tmapa[0].columnas; end    //nunca será negativo
								at_posx = at_posx % [ts_struct].tmapa[0].columnas;

								include "procesos_zoom/add_tile.inc";
							end
						end  //for x
						//***********************************************************
						 
					end
				end  //for y
			end  //for z
			 
			//en este punto, ptr_aux apunta a la última posición, si hay tiles de más sobran,
			//y hay que borrarlos
			if (ptr_aux != 0)                            //el puntero señala al ultimo tile válido
				if (ptr_aux.tscroll_ptr_sig != 0)                 //borramos los siguientes (si existen)
					borrar_tiles_sobrantes(ptr_aux);
				end
			else                                               //el puntero no señala ningun tile válido
				if ([ts_struct].id_tscroll != 0)                  //comprobamos que hay tiles en la lista
					if ([ts_struct].id_tscroll.tscroll_ptr_sig != 0)       //y que hay más de uno
						borrar_tiles_sobrantes([ts_struct].id_tscroll);
					end
					signal([ts_struct].id_tscroll, s_kill);
					[ts_struct].id_tscroll = 0;
				end
			end
		end
	end
	
	[ts_struct].camera_tx_ant = [ts_struct].camera_tx;
	[ts_struct].camera_ty_ant = [ts_struct].camera_ty;

	[ts_struct].camera_x_tile_ant = [ts_struct].camera_x;
	[ts_struct].camera_y_tile_ant = [ts_struct].camera_y;
end*/


/*function ts_desplaza_tiles(tscroll pointer ts_struct, int dt_posx, int dt_posy)
private
	int ptr_aux;
begin
    ptr_aux = [ts_struct].id_tscroll;
    while (ptr_aux != 0)
		ptr_aux.x += dt_posx;
        ptr_aux.y += dt_posy;
        ptr_aux = ptr_aux.tscroll_ptr_sig;
    end
end*/

//**************************************************************************************
//  FUNCIÓN:    tscroll_control
//              Maneja los procesos tile del scroll, así como su gestión, evitando que
//              estos tengan que ejecutar código alguno (quizás la animación)
//  PARÁMETROS: ts_struct: estructura que almacena los datos del scroll. Si queremos
//                         modificar algo del scroll tendremos que cambiar sus variables,
//                         este proceso ya se encargará de que se cumpla.
//**************************************************************************************
process tscroll_control (tscroll pointer ts_struct)
private
	/*int camera_tx_ant;	//Se han añadido estas variables a la struct de tscroll para que al actualizar
    int camera_ty_ant;		//desde otro proceso, este no provoque un desplazamiento no deseado, porque al
    int camera_x_tile_ant;	//ser privadas almacenan la posición del frame anterior sin tener en cuenta el
    int camera_y_tile_ant;*/	//desplazamiento del proceso externo
	
	int tsc_pos_array;
	int tsc_ant_tile;
	int tsc_new_tile;
	
	int tsc_pos_tmapa_x, tsc_pos_tmapa_y;
	int contx, conty, contz;
	int tempx, tempy, tempz;
begin
	write_var(0,10,10,0, ([ts_struct].mapadibujo_tx));
	//write_var(0,30,10,0, ([ts_struct].n_columnas));
	//write_var(0,10,20,0, ([ts_struct].mapadibujo_ty));
	//write_var(0,30,20,0, ([ts_struct].n_filas));
	
	//forzamos un refresco completo del scroll
    [ts_struct].camera_tx_ant = [ts_struct].camera_tx + 1;
    [ts_struct].camera_ty_ant = [ts_struct].camera_ty + 1;

    //write(0,10,300,0,"flag vertical: "+([ts_struct].tscroll_flags & 2));
    //write(0,10,310,0,"flag horizontal: "+([ts_struct].tscroll_flags & 1));
    loop
		//say("iniciada iteracion");
		//primero cogemos las coordenadas actuales del proceso target
		if ([ts_struct].id_target != 0)
			if (exists([ts_struct].id_target))
				[ts_struct].camera_x = [ts_struct].id_target.x2 + [ts_struct].cam_desp_x - ([ts_struct].ancho_reg / 2);
				[ts_struct].camera_y = [ts_struct].id_target.y2 + [ts_struct].cam_desp_y - ([ts_struct].alto_reg / 2);
				//Impedimos que se pase de los bordes del mapa si no es cíclico
				if (([ts_struct].tscroll_flags & 1) == 0)
					//scroll no ciclico en x
					if ([ts_struct].camera_x < 0) [ts_struct].camera_x = 0; end
					if ([ts_struct].camera_x > ([ts_struct].ancho_mapa - [ts_struct].ancho_reg))
						[ts_struct].camera_x = [ts_struct].ancho_mapa - [ts_struct].ancho_reg;
					end
				end
				if (([ts_struct].tscroll_flags & 2) == 0)
					//scroll no ciclico en y
					if ([ts_struct].camera_y < 0) [ts_struct].camera_y = 0; end
					if ([ts_struct].camera_y > ([ts_struct].alto_mapa - [ts_struct].alto_reg))
						[ts_struct].camera_y = [ts_struct].alto_mapa - [ts_struct].alto_reg;
					end
				end
			else
				[ts_struct].id_target = 0;
			end
		end
		//Tenemos las coordenadas (por un proceso o porque las ha puesto el usuario)
		//Vamos a calcular el tile en el que está la cámara (posición absoluta)
		if ([ts_struct].camera_x < 0)
			[ts_struct].camera_tx = ([ts_struct].camera_x + 1) / [ts_struct].tmapa[0].ancho_tile;
			[ts_struct].camera_tx--;
		else
			[ts_struct].camera_tx = [ts_struct].camera_x / [ts_struct].tmapa[0].ancho_tile;
		end
        if ([ts_struct].camera_y < 0)
			[ts_struct].camera_ty = ([ts_struct].camera_y + 1) / [ts_struct].tmapa[0].alto_tile;
            [ts_struct].camera_ty--;
		else
            [ts_struct].camera_ty = [ts_struct].camera_y / [ts_struct].tmapa[0].alto_tile;
        end
        //Y ahora las posiciones relativas a la esquina del mapa (como si sólo hubiera
        //un mapa no cíclico)
        [ts_struct].camera_x1 = ([ts_struct].camera_x % [ts_struct].ancho_mapa);
        if ([ts_struct].camera_x1 < 0)
            [ts_struct].camera_x1 += [ts_struct].ancho_mapa;
        end
        [ts_struct].camera_y1 = ([ts_struct].camera_y % [ts_struct].alto_mapa);
        if ([ts_struct].camera_y1 < 0)
            [ts_struct].camera_y1 += [ts_struct].alto_mapa;
        end
        //Los tiles los calcularemos con esta posición relativa, que ya es positiva
        [ts_struct].camera_tx1 = [ts_struct].camera_x1 / [ts_struct].tmapa[0].ancho_tile;
        [ts_struct].camera_ty1 = [ts_struct].camera_y1 / [ts_struct].tmapa[0].alto_tile;
        //Por si hace falta, calcularemos la posición dentro de un tile de la cámara
        [ts_struct].camera_x_tile = [ts_struct].camera_x1 % [ts_struct].tmapa[0].ancho_tile;
        [ts_struct].camera_y_tile = [ts_struct].camera_y1 % [ts_struct].tmapa[0].alto_tile;
         
        //EMPIEZA EL CONTROL DE LOS TILES**********************************
        //Si cambiamos de tile hay que refrescar todos los mapas
        if (([ts_struct].camera_tx != [ts_struct].camera_tx_ant) ||
            ([ts_struct].camera_ty != [ts_struct].camera_ty_ant) ||
			[ts_struct].forzar_refresco)
			
			/*say([ts_struct].camera_tx + "," + [ts_struct].camera_tx_ant + "       " +
				[ts_struct].camera_ty + "," + [ts_struct].camera_ty_ant);*/
					
			//Primero buscamos la posición de los mapas que queda más arriba a la izquierda
			if ([ts_struct].camera_tx < 0)
				[ts_struct].mapadibujo_tx = ([ts_struct].camera_tx + 1) % [ts_struct].n_columnas;
				//[ts_struct].mapadibujo_tx--;
				[ts_struct].mapadibujo_tx += [ts_struct].n_columnas - 1;
			else
				[ts_struct].mapadibujo_tx = [ts_struct].camera_tx % [ts_struct].n_columnas;
			end
			if ([ts_struct].camera_ty < 0)
				[ts_struct].mapadibujo_ty = ([ts_struct].camera_ty + 1) % [ts_struct].n_filas;
				//[ts_struct].mapadibujo_ty--;
				[ts_struct].mapadibujo_ty += [ts_struct].n_filas - 1;
			else
				[ts_struct].mapadibujo_ty = [ts_struct].camera_ty % [ts_struct].n_filas;
			end
			
			//Recorremos todos los mapas, dibujando los tiles que hayan ido cambiando
			for (contz = 0; contz < [ts_struct].n_capas; contz++)
			//for (contz = 0; contz <= 0; contz++)
				tempy = [ts_struct].mapadibujo_ty;
				for (conty = 0; conty < [ts_struct].n_filas; conty++)
					tempx = [ts_struct].mapadibujo_tx;
					for (contx = 0; contx < [ts_struct].n_columnas; contx++)
						tsc_pos_tmapa_x =  [ts_struct].camera_tx1 + contx;
						if (tsc_pos_tmapa_x >= [ts_struct].tmapa[0].columnas)
							tsc_pos_tmapa_x -= [ts_struct].tmapa[0].columnas;
						end
						tsc_pos_tmapa_y =  [ts_struct].camera_ty1 + conty;
						if (tsc_pos_tmapa_y >= [ts_struct].tmapa[0].filas)
							tsc_pos_tmapa_y -= [ts_struct].tmapa[0].filas;
						end
						
						tsc_pos_array = ([ts_struct].n_filas_x_columnas * contz) +
										([ts_struct].n_columnas * tempy) +
										tempx;
						//say("pos array dibujo: " + tsc_pos_array);
						
						tsc_ant_tile = [ts_struct].ptr_array_tiles[tsc_pos_array];
						tsc_new_tile = tscroll_obtener_tile(ts_struct, tsc_pos_tmapa_x, tsc_pos_tmapa_y, contz);
						
						if (tsc_ant_tile != tsc_new_tile)
							/*say("[" + [ts_struct].mapadibujo_tx + "," + [ts_struct].mapadibujo_ty + "] " +
								"(" + tempx + "," + tempy + "): " + tsc_ant_tile + "->" + tsc_new_tile);*/
							if (tsc_new_tile == 0)	//borrar tile
								map_clear([ts_struct].ts_file, 999 - contz,
                                          tempx * [ts_struct].tmapa[0].ancho_tile,
										  tempy * [ts_struct].tmapa[0].alto_tile,
							              ((tempx + 1) * [ts_struct].tmapa[0].ancho_tile) - 1,
							              ((tempy + 1) * [ts_struct].tmapa[0].alto_tile) - 1);
							else
								if (tsc_new_tile >= 150)
									tscroll_generar_no_tile(ts_struct, tsc_new_tile,
															tsc_pos_tmapa_x, tsc_pos_tmapa_y, contz);
								else
									map_xput([ts_struct].ts_file, 999 - contz, tsc_new_tile,
											 (tempx*[ts_struct].tmapa[0].ancho_tile) +
												([ts_struct].tmapa[0].ancho_tile/2),
											 (tempy*[ts_struct].tmapa[0].alto_tile) +
												([ts_struct].tmapa[0].alto_tile/2),
											 0, 100, B_NOCOLORKEY);
								end
								
							end
							[ts_struct].ptr_array_tiles[tsc_pos_array] = tsc_new_tile;
						end
						
						//pasamos a la siguiente posición de X
						tempx++;
						if (tempx >= [ts_struct].n_columnas) tempx -= [ts_struct].n_columnas; end
					end
					
					//pasamos a la siguiente posición de Y
					tempy++;
					if (tempy >= [ts_struct].n_filas) tempy -= [ts_struct].n_filas; end
				end
			end
			
			[ts_struct].camera_tx_ant = [ts_struct].camera_tx;
            [ts_struct].camera_ty_ant = [ts_struct].camera_ty;
			if ([ts_struct].forzar_refresco) [ts_struct].forzar_refresco = 0; end
		
		end
		for (contx = [ts_struct].scroll_primero; contx <= [ts_struct].scroll_ultimo; contx++)
			scroll[contx].x0 = [ts_struct].camera_x;
			scroll[contx].y0 = [ts_struct].camera_y;
			scroll[contx].x1 = [ts_struct].camera_x;
			scroll[contx].y1 = [ts_struct].camera_y;
		end
		[ts_struct].camera_x_tile_ant = [ts_struct].camera_x;
		[ts_struct].camera_y_tile_ant = [ts_struct].camera_y;
        //say("completada iteracion");
        frame;
	end
end

//**************************************************************************************
//  FUNCION:    start_tscroll
//              Crea un scroll tileado que se mostrará usando un proceso por cada tile
//              visible en pantalla
//  PARÁMETROS: ts_struct: estructura que almacena los datos sobre el tscroll, debes crear
//                         la variable desde fuera y dejarla vacía, pues este proceso ya
//                         se encarga de rellenarlos. Se hace de esta forma porque no se
//                         puede devolver una estructura y así puedes leer los datos
//                         desde otros procesos.
//              ts_mapa: estructura que almacena los datos del mapa al cargarlo
//              ts_region: region en la que se mostrará el tscroll
//              ts_ini_regionx: posicion x de la esquina superior izquierda de la region
//              ts_ini_regiony: posicion y de la esquina superior izquierda de la region
//              ts_ancho_region: ancho de la region
//              ts_alto_region: alto de la region
//              tiles_extra_x: tiles que no se verán a los lados, pero que estan por si
//                             cargan información, por ejemplo, generan enemigos...
//                             un valor de 4 hace que haya 2 tiles a cada lado que no se
//                             ven
//              tiles_extra_y: idem por arriba y por abajo
//              ts_ancho_tile: especifica el ancho de un tile en pixels, necesario cuando
//                             se carga un tmf. Usando tpr este valor da igual.
//              ts_alto_tile: igual que el anterior, pero con la altura de un tile.
//				ts_scroll_primero: número del primer scroll que se va a usar
//				ts_n_fondos_por_scroll: número de capas que se van a usar en un único
//										scroll. Si se usa sólo uno se pueden controlar sus
//										z individualmente, si se usan 2 se pueden tener
//										hasta 20 capas (pero sus Z van de dos en dos)
//              ts_flags: flags de las propiedades del scroll
//                        1= scroll cíclico horizontalmente
//                        2= scroll cíclico verticalmente
//**************************************************************************************
process start_graph_tscroll (tscroll pointer ts_struct, t_mapa pointer ts_mapa,
                       int ts_region,
                       int ts_ini_regionx, int ts_ini_regiony,
                       int ts_ancho_region, int ts_alto_region,
                       int tiles_extra_x, int tiles_extra_y,
                       int ts_ancho_tile, int ts_alto_tile,
					   int ts_scroll_primero, int ts_n_fondos_por_scroll, int ts_flags)
private
	int st_error;
	
	int temp_map;
//	int temp;
	int cont;
begin
	st_error = 0;
	//empezamos cargando los datos por parámetros
    [ts_struct].ts_region = ts_region;
    [ts_struct].ini_reg_x = ts_ini_regionx;
    [ts_struct].ini_reg_y = ts_ini_regiony;
    [ts_struct].ancho_reg = ts_ancho_region;
    [ts_struct].alto_reg = ts_alto_region;
    [ts_struct].tscroll_flags = ts_flags;
    //seguimos cargando datos del mapa cargado
    [ts_struct].tmapa = ts_mapa;

    //calculos para ahorrar trabajo despues
    [ts_struct].n_tiles_capa = [ts_struct].tmapa[0].columnas * [ts_struct].tmapa[0].filas;
    //cargamos los datos adicionales por el propio tipo de fichero
    switch ([ts_mapa].tipo_mapa)
    case 2:
		//[ts_struct].ts_file = fpg_load([ts_mapa].fpg);
		if ([ts_struct].ts_file < 0)
			say("Error: no se ha podido cargar el FPG.");
			st_error = 2;
		end
    end
    default:
        if (ts_ancho_tile > 0)
			[ts_struct].tmapa[0].ancho_tile = ts_ancho_tile;
        else
			say("Error: el tamaño de tile no es válido");
			st_error = 1;
		end
        if (ts_alto_tile > 0)
			[ts_struct].tmapa[0].alto_tile = ts_alto_tile;
		else
			say("Error: el tamaño de tile no es válido");
			st_error = 1;
		end
		if ([ts_struct].ts_file < 0)
			say("Error: no se ha podido cargar el FPG.");
			st_error = 2;
		end
	end
	end //switch
	
	if (st_error == 0)
		//calculamos el tamaño total del mapa, para ahorrar cálculos
		[ts_struct].ancho_mapa = [ts_struct].tmapa[0].columnas * [ts_struct].tmapa[0].ancho_tile;
		[ts_struct].alto_mapa = [ts_struct].tmapa[0].filas * [ts_struct].tmapa[0].alto_tile;

		//calculamos los tiles que nos van a llevar el tscroll
		[ts_struct].n_columnas = ts_ancho_region / [ts_struct].tmapa[0].ancho_tile;
		if ((ts_ancho_region % [ts_struct].tmapa[0].ancho_tile) > 0)
			[ts_struct].n_columnas++;
		end
		[ts_struct].n_filas = ts_alto_region / [ts_struct].tmapa[0].alto_tile;
		if ((ts_alto_region % [ts_struct].tmapa[0].alto_tile) > 0)
			[ts_struct].n_filas++;
		end
		[ts_struct].tiles_extra_x = tiles_extra_x;
		[ts_struct].tiles_extra_y = tiles_extra_y;
		[ts_struct].n_columnas += tiles_extra_x;
		[ts_struct].n_filas += tiles_extra_y;
		[ts_struct].n_capas = [ts_mapa].capas;           //esto hay que definirlo
		[ts_struct].n_filas_x_columnas = [ts_struct].n_filas * [ts_struct].n_columnas;

		
		
		//creamos los mapas sobre los que vamos a dibujar los tiles
		[ts_struct].mapadibujo_ancho = [ts_struct].n_columnas * [ts_struct].tmapa[0].ancho_tile;
		[ts_struct].mapadibujo_alto = [ts_struct].n_filas * [ts_struct].tmapa[0].alto_tile;
//		temp = 0;	//buscamos la profundidad de color del FPG cargado
//		cont = 1;
//		while (temp == 0)
//			if (map_exists([ts_struct].ts_file, cont))
//				temp = graphic_info([ts_struct].ts_file, cont, G_DEPTH);
//			end
//		end
		
		for (cont = 0; cont < [ts_struct].n_capas; cont++)
			//Se crea un mapa del tamaño definido, y la misma profundidad de color que el FPG de tiles
			temp_map = map_new([ts_struct].mapadibujo_ancho, [ts_struct].mapadibujo_alto);
			center_set(0, temp_map, 0, 0);
			//Se añade el mapa al FPG de los tiles, desde la última posición hacia el principio
			fpg_add([ts_struct].ts_file, 999 - cont, 0, temp_map);
			map_unload(0, temp_map);
		end
		
		//creamos el array sobre el que vamos a guardar los tiles pintados en cada posición de los mapas
		[ts_struct].ptr_array_tiles = alloc([ts_struct].n_columnas * [ts_struct].n_filas * [ts_struct].n_capas *
											sizeof(int));
		memset([ts_struct].ptr_array_tiles, 0,
				[ts_struct].n_columnas * [ts_struct].n_filas * [ts_struct].n_capas);// * sizeof(int));
		
		//Inicializamos los scrolls que vamos a usar
		/*temp = [ts_struct].tscroll_flags;
		if ([ts_struct].tscroll_flags & 1 == 1) temp += 4; end
		if ([ts_struct].tscroll_flags & 2 == 2) temp += 8; end*/
		
		[ts_struct].scroll_primero = ts_scroll_primero;
		
		switch (ts_n_fondos_por_scroll)
		case 1:
			for (cont = 0; cont < [ts_struct].n_capas; cont++)
				//say("Iniciando scroll: " + itoa([ts_struct].scroll_primero + cont ));
				start_scroll([ts_struct].scroll_primero + cont, [ts_struct].ts_file, 999 - cont, 0,
							[ts_struct].ts_region, 1+2);
				scroll[[ts_struct].scroll_primero + cont].ratio = 0;
			end
			
			[ts_struct].scroll_ultimo = [ts_struct].scroll_primero + [ts_struct].n_capas - 1;
		end
		case 2:
			for (cont = 0; cont < [ts_struct].n_capas; cont += 2)
				//say("Iniciando scroll: " + itoa([ts_struct].scroll_primero + (cont / 2)));
				if (cont + 1 == [ts_struct].n_capas)	//nos falta una capa para este scroll
					start_scroll([ts_struct].scroll_primero + (cont / 2),
									[ts_struct].ts_file, 999 - cont, 0,
									[ts_struct].ts_region, 1+2);
				else
					start_scroll([ts_struct].scroll_primero + (cont / 2),
									[ts_struct].ts_file, 999 - cont, 999 - cont - 1,
									[ts_struct].ts_region, 1+2+4+8);
				end
				scroll[[ts_struct].scroll_primero + (cont / 2)].ratio = 0;
			end
			
			[ts_struct].scroll_ultimo = [ts_struct].scroll_primero + (([ts_struct].n_capas - 1) / 2);
		end
		end //switch
			
		//calculamos la posición neutral del tile superior izquierdo, como referencia
		/*[ts_struct].tileador_posx = [ts_struct].ini_reg_x
									+ (([ts_struct].tmapa[0].ancho_tile * [ts_struct].zoom) / 100) / 2
									- ((tiles_extra_x / 2) *
										(([ts_struct].tmapa[0].ancho_tile * [ts_struct].zoom) / 100));
		[ts_struct].tileador_posy = [ts_struct].ini_reg_y
									+ (([ts_struct].tmapa[0].alto_tile * [ts_struct].zoom) / 100) / 2
									- ((tiles_extra_y / 2) *
										(([ts_struct].tmapa[0].alto_tile * [ts_struct].zoom) / 100));*/
		//la fórmula es: esquina de la region, mas medio tile (porque el 0,0 está en el
		//centro del tile) menos la mitad de los tiles extra que añadimos.
		 
		//[ts_struct].id_tscroll=crear_mapa([ts_struct].n_columnas,[ts_struct].n_filas,
		//                                  [ts_struct].n_capas,ts_struct);
		 
		//DEBUG
		//[ts_struct].id_tscroll=tile();
		//[ts_struct].id_tscroll.graph=1;

		//creamos el proceso de control del tscroll
		//[ts_struct].id_tscroll = 0;
		[ts_struct].estado = CTE_TSCROLL_ESTADO_ACTIVO;
		[ts_struct].id_control = tscroll_control(ts_struct);
	end
    //say("todo ok: " + st_error);
	return st_error;
end

//***************************************************************************************
//  FUNCIÓN:    stop_tscroll
//              Detiene el scroll tileado, eliminando todos los procesos tile, descargando
//              el fpg si se cargó desde un tpr y poniendo todo a cero. Pero esta función
//              no descarga el mapa de tiles porque podría estar siendo usado por otro
//              scroll.
//  PARÁMETROS: ts_struct: estructura que almacena los datos sobre el tscroll.
//***************************************************************************************

process stop_tscroll (tscroll pointer ts_struct)
private
	int cont;
begin
	//eliminamos el proceso de control
	if (([ts_struct].id_control != 0) && exists([ts_struct].id_control))
		signal([ts_struct].id_control, s_kill);
	end
    [ts_struct].id_control = 0;
	
	//Borramos los mapas creados
	for (cont = 0; cont < [ts_struct].n_capas; cont++)
		map_unload([ts_struct].ts_file, 999 - cont);
	end
	//Liberamos la memoria del array
	free([ts_struct].ptr_array_tiles);
	//detenemos los scrolls
	for (cont = [ts_struct].scroll_primero; cont <= [ts_struct].scroll_ultimo; cont++)
		stop_scroll(cont);
	end
	
    //************************************************
    //Estas lineas no son necesarias, si se quiere agilizar el proceso se pueden
    //eliminar, pero así se deja listo por si se va a usar la estructura con otro
    //scroll tileado
    [ts_struct].ts_region = 0;
    [ts_struct].ini_reg_x = 0;
    [ts_struct].ini_reg_y = 0;
    [ts_struct].ancho_reg = 0;
    [ts_struct].alto_reg = 0;
	//[ts_struct].zoom = 100;
    
    [ts_struct].camera_x = 0;
    [ts_struct].camera_y = 0;
    [ts_struct].camera_x1 = 0;
    [ts_struct].camera_y1 = 0;
    [ts_struct].camera_tx = 0;
    [ts_struct].camera_ty = 0;
    [ts_struct].camera_tx1 = 0;
    [ts_struct].camera_ty1 = 0;
    [ts_struct].camera_x_tile = 0;
    [ts_struct].camera_y_tile = 0;
    [ts_struct].id_target = 0;
    [ts_struct].cam_desp_x = 0;
    [ts_struct].cam_desp_y = 0;
    [ts_struct].tscroll_flags = 0;
     
    [ts_struct].n_columnas = 0;
    [ts_struct].n_filas = 0;
    [ts_struct].n_capas = 0;
    [ts_struct].tiles_extra_x = 0;
    [ts_struct].tiles_extra_y = 0;
     
    [ts_struct].ancho_mapa = 0;
    [ts_struct].alto_mapa = 0;
    [ts_struct].n_tiles_capa = 0;
    //[ts_struct].tileador_posx = 0;
    //[ts_struct].tileador_posy = 0;
	
     
    //si hemos cargado un tpr, descargamos el fpg que cargamos con él
    //if ([ts_struct].tmapa[0].tipo_mapa == 2) fpg_unload([ts_struct].ts_file); end
    [ts_struct].ts_file = 0;
    //eliminamos la lista de tiles
    /*borrar_tiles_sobrantes([ts_struct].id_tscroll);
    if ([ts_struct].id_tscroll != 0)
		if (exists([ts_struct].id_tscroll))
			signal([ts_struct].id_tscroll,s_kill);
		end
     	[ts_struct].id_tscroll = 0;
    end*/
	[ts_struct].estado = CTE_TSCROLL_ESTADO_MUERTO;
end


//***************************************************************************************
//  FUNCIÓN:    pause_tscroll
//              Detiene el scroll tileado, eliminando todos los procesos tile y el
//				proceso de control, pudiendo reanudarlo más tarde con los datos
//				actualizados.
//  PARÁMETROS: ts_struct: estructura que almacena los datos sobre el tscroll.
//***************************************************************************************

process pause_tscroll (tscroll pointer ts_struct)
begin
	if (ts_struct != NULL)
		//eliminamos el proceso de control
		if (([ts_struct].id_control != 0) && exists([ts_struct].id_control))
			signal([ts_struct].id_control, s_kill);
		end
		[ts_struct].id_control = 0;
		//************************************************
		
		//eliminamos la lista de tiles
		/*borrar_tiles_sobrantes([ts_struct].id_tscroll);
		if ([ts_struct].id_tscroll != 0)
			if (exists([ts_struct].id_tscroll))
				signal([ts_struct].id_tscroll,s_kill);
			end
			[ts_struct].id_tscroll = 0;
		end*/
		[ts_struct].estado = CTE_TSCROLL_ESTADO_INACTIVO;
	end
end

//***************************************************************************************
//  FUNCIÓN:    resume_tscroll
//              Reanuda el scroll tileado, volviendo a crear el proceso de control.
//				Él ya se encarga de llamar a actualizar tiles y volver a crearlos.
//  PARÁMETROS: ts_struct: estructura que almacena los datos sobre el tscroll.
//***************************************************************************************

process resume_tscroll (tscroll pointer ts_struct)
begin
	if (ts_struct != NULL)
		if ([ts_struct].estado == CTE_TSCROLL_ESTADO_INACTIVO)
			[ts_struct].estado = CTE_TSCROLL_ESTADO_ACTIVO;
			[ts_struct].id_control = tscroll_control(ts_struct);
		end
	end
end

//****************************************************************************************************
//  OTRAS FUNCIONES
//****************************************************************************************************

process tscroll_get_screen_position (tscroll pointer ts_struct, int x2, int y2, double pointer gsp_posx, double pointer gsp_posy)
//***************************************************************************
//  FUNCION:      tscroll_get_screen_position
//                se le pasan coordenadas del scroll y esta devuelve coordenadas
//                de pantalla.
//  PARAMETROS:   ts_struct: estructura con los datos del scroll donde queremos situarnos
//                x2: posición x dentro del scroll del proceso
//                y2: posicion y dentro del scroll del proceso
//                gps_posx: dirección donde queremos que se almacene la posición x en
//                          pantalla.
//                gps_posy: dirección donde queremos que se almacene la posición y en
//                          pantalla.
//***************************************************************************
begin
	[gsp_posx] = [ts_struct].ini_reg_x + (x2 - [ts_struct].camera_x);
    [gsp_posy] = [ts_struct].ini_reg_y + (y2 - [ts_struct].camera_y);
end
