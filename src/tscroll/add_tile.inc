at_tile = tscroll_obtener_tile(ts_struct, at_posx, at_posy, cont_z);

//Añadido para dmp3y********************************************************************************
//Tiles normales de agua
if ((at_tile >= CTE_INICIO_TILES_AGUA) && (at_tile < CTE_INICIO_TILES_AGUA + 100))
    tile_agua(at_tile, at_posx, at_posy);
    at_tile -= CTE_INICIO_TILES_AGUA;
end
//Tiles optimizados de agua
//**************************************************************************************************

if ((at_tile > 0) && (at_tile < 150))
   if ([ts_struct].id_tscroll == 0) //la lista está vacía
      //say("primer tile");
      ptr_aux = tile(at_posx, at_posy, cont_z);
      //ptr_aux.flags = 4;
      [ts_struct].id_tscroll = ptr_aux;
      //say(ptr_aux);
   else
       if (ptr_aux == 0)                        //Si es el primer tile que tenemos que
          ptr_aux = [ts_struct].id_tscroll;      //actualizar, nos vamos al principio
       else
           if (ptr_aux.ptr_sig == 0)    //si estamos al final creamos
              ptr_aux.ptr_sig = tile(at_posx, at_posy, cont_z); //un nuevo tile
           end                        //si no, pues avanzamos
           ptr_aux = ptr_aux.ptr_sig;
       end
   end
   ptr_aux.file = [ts_struct].ts_file;
   ptr_aux.graph = at_tile;
   ptr_aux.x = temp_x + (cont_x * [ts_struct].tmapa[0].ancho_tile);
   ptr_aux.y = temp_y + (cont_y * [ts_struct].tmapa[0].alto_tile);
   ptr_aux.z = cont_z * 3;
   ptr_aux.region = [ts_struct].ts_region;
   //identificación para el tile (si no se va a buscar tiles en la lista se puede quitar)
   ptr_aux.x2 = at_posx;
   ptr_aux.y2 = at_posy;
   ptr_aux.z2 = cont_z;
end

//AÑADIDO PARA DOGGY!!!
//crea procesos interactivos como enemigos, tiles que se rompen...
if ((at_tile >= 150) && (at_tile < 1000))
    switch (at_tile)
    //enemigos
    case 150: guerrillero(at_posx,at_posy,enem_grafs[0][cte_guerrillero],0); end    //si cambias cte,cambia en enem
    case 151: guerrillero(at_posx,at_posy,enem_grafs[0][cte_guerrillero],1); end    //si cambias cte,cambia en enem
    case 152: spider(at_posx,at_posy,7); end
    case 153: super_guerrillero(at_posx,at_posy,enem_grafs[0][cte_s_guerrillero],0); end
    case 154: volador1(at_posx,at_posy,enem_grafs[0][cte_volador1],3); end
    case 155: corvo(at_posx,at_posy,enem_grafs[0][cte_volador1],3); end
    case 156: volador1(at_posx,at_posy,enem_grafs[0][cte_murcielago],3); end
    case 157: murcielago(at_posx,at_posy,3); end
    case 158: blobo(at_posx,at_posy,enem_grafs[0][cte_blobo],9); end
    case 159: ghost_fly(at_posx,at_posy,7); end
    case 160: ghost_fly_invencible(at_posx,at_posy); end
    case 161: invencible_enem(at_posx,at_posy,enem_grafs[0][cte_hotta]); end
    case 162: mina(at_posx,at_posy); end
    case 163: flozat (at_posx,at_posy,enem_grafs[0][cte_flozat],9); end
    case 164: volador1(at_posx,at_posy,enem_grafs[0][cte_volador1],7); end
    case 165: corvo(at_posx,at_posy,enem_grafs[0][cte_volador1],7); end
    case 166: glotz(at_posx,at_posy,enem_grafs[0][cte_glotz],9); end
    case 167: canon(at_posx,at_posy,enem_grafs[0][cte_canon],0); end
    case 168: canon(at_posx,at_posy,enem_grafs[0][cte_canon],1); end
    case 169: guerrillero(at_posx,at_posy,enem_grafs[0][cte_flerris],0); end    //si cambias cte,cambia en enem
    case 170: guerrillero(at_posx,at_posy,enem_grafs[0][cte_flerris],1); end    //si cambias cte,cambia en enem
    case 171: super_guerrillero(at_posx,at_posy,enem_grafs[0][cte_s_flerrus],0); end
    case 172: spikes(at_posx,at_posy,enem_grafs[0][cte_spikes]); end
    case 173: excaver(at_posx,at_posy,enem_grafs[0][cte_excaver]); end
    case 174: roca_lanzador (at_posx,at_posy,enem_grafs[0][cte_rock],0); end
    case 175: vigilante_horus (at_posx,at_posy,enem_grafs[0][cte_vigilante],0); end
    case 176: vigilante_horus (at_posx,at_posy,enem_grafs[0][cte_vigilante],1); end
    case 177: blobo(at_posx,at_posy,enem_grafs[0][cte_blobo],22); end   //Blobo poderoso
    case 178: volador1(at_posx,at_posy,enem_grafs[0][cte_volador2],15); end   //volador nivel 3
    case 179: corvo(at_posx,at_posy,enem_grafs[0][cte_volador2],15); end      //volador nivel 3
	  case 180: momia(at_posx,at_posy,enem_grafs[0][cte_momia]); end
    
    //puertas
    case 200: door(at_posx,at_posy,id_tscroll.ts_file,obj_interruptor[cte_door]); end
    case 201: bridge(at_posx,at_posy,id_tscroll.ts_file,obj_interruptor[cte_bridge],2,1,0); end
    case 202: bridge(at_posx,at_posy,id_tscroll.ts_file,obj_interruptor[cte_bridge],2,2,0); end
    case 203: bridge(at_posx,at_posy,id_tscroll.ts_file,obj_interruptor[cte_bridge],2,3,0); end
    case 204: bridge(at_posx,at_posy,id_tscroll.ts_file,obj_interruptor[cte_bridge],2,4,0); end
    
    //items importantes 
    case 225: item_add_energy(at_posx,at_posy); end
    case 226: new_weapon(at_posx,at_posy,0); end
    case 227: new_weapon(at_posx,at_posy,1); end
    case 228: new_weapon(at_posx,at_posy,2); end
    
    //interruptores
    case 249: button(at_posx,at_posy,item_grafs,249); end
    
    //cambio nivel
    case 251: item_end_sublevel(at_posx,at_posy); end
    case 252: item_end_level(at_posx,at_posy); end
    case 253: event(at_posx,at_posy); end
	  case 254: item_checkpoint(at_posx,at_posy); end
    
    //objetos animados
    case 275: objeto_animado_sincronizado(at_posx,at_posy,(-cont_z*2)-1,enem_grafs[0][cte_anim_level],0,
                                          0,1); end  //sin transparencia, anim 0
    case 276: objeto_animado_sincronizado(at_posx,at_posy,(-cont_z*2)-1,enem_grafs[0][cte_anim_level],160,
                                          0,1); end  //con transparencia, anim 0
    //case 275: objeto_animado(at_posx,at_posy,(-cont_z*2)-1,enem_grafs[0][cte_anim_level],0,0); end  //sin transparencia, anim 0
    //case 276: objeto_animado(at_posx,at_posy,(-cont_z*2)-1,enem_grafs[0][cte_anim_level],160,0); end  //con transparencia, anim 0
	
	  //Plataformas
	  case 400: plataforma_auto_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 1); end
	  case 401: plataforma_auto_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 2); end
	  case 402: plataforma_auto_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 3); end
	  case 403: plataforma_auto_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 5); end
	  case 404: plataforma_auto_desaparece2 (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 1); end
	  case 405: plataforma_auto_desaparece2 (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 2); end
	  case 406: plataforma_auto_desaparece2 (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 3); end
	  case 407: plataforma_auto_desaparece2 (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 1, 5, 5); end
	  
	  case 410: plataforma_solida_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 11, 16, 20); end
	  case 411: plataforma_atravesable_desaparece (at_posx,at_posy,enem_grafs[0][cte_interactive_plaforms], 21, 26, 30); end
	  	
	  case 420: plataforma_movil_por_contacto (at_posx,at_posy,cont_z,enem_grafs[0][cte_interactive_plaforms], 40, 40, 1); end
	  case 421: plataforma_movil_por_contacto (at_posx,at_posy,cont_z,enem_grafs[0][cte_interactive_plaforms], 41, 41, 2); end
	  case 422: plataforma_movil_por_contacto (at_posx,at_posy,cont_z,enem_grafs[0][cte_interactive_plaforms], 42, 42, 3); end
	  	
	  //Tiles de daño continuo
	  case 426: tile_lava (at_posx,at_posy,cont_z, enem_grafs[0][cte_tiles_lava], 0, 12, -3); end		//Superficie lava
	  case 427: tile_lava (at_posx,at_posy,cont_z, enem_grafs[0][cte_tiles_lava], 1, 15, -3); end		//Completo lava
    end //switch
end

//TILES OPTIMIZADOS
if ((at_tile > CTE_INICIO_TILES_OPTIMIZADOS) && (at_tile <= CTE_FIN_TILES_OPTIMIZADOS))
   if ([ts_struct].id_tscroll == 0) //la lista está vacía
      //say("primer tile");
      ptr_aux = tile(at_posx, at_posy, cont_z);
      //ptr_aux.flags = 4;
      [ts_struct].id_tscroll = ptr_aux;
      //say(ptr_aux);
   else
       if (ptr_aux == 0)                        //Si es el primer tile que tenemos que
          ptr_aux = [ts_struct].id_tscroll;      //actualizar, nos vamos al principio
       else
           if (ptr_aux.ptr_sig == 0)    //si estamos al final creamos
              ptr_aux.ptr_sig = tile(at_posx, at_posy, cont_z); //un nuevo tile
           end                        //si no, pues avanzamos
           ptr_aux = ptr_aux.ptr_sig;
       end
   end
   ptr_aux.file = 0;
   ptr_aux.graph = tiles_optimizados[at_tile - CTE_INICIO_TILES_OPTIMIZADOS];
   //say("Poner tile " + at_tile + " que es el " + tiles_optimizados[at_tile-CTE_INICIO_TILES_OPTIMIZADOS]);
   ptr_aux.x = temp_x + (cont_x * [ts_struct].tmapa[0].ancho_tile);
   ptr_aux.y = temp_y + (cont_y * [ts_struct].tmapa[0].alto_tile);
   ptr_aux.z = cont_z * 3;
   ptr_aux.region = [ts_struct].ts_region;
   //identificación para el tile (si no se va a buscar tiles en la lista se puede quitar)
   ptr_aux.x2 = at_posx;
   ptr_aux.y2 = at_posy;
   ptr_aux.z2 = cont_z;
end
