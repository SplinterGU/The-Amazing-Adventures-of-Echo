process tile_lava (int obj_tx, int obj_ty, z, file, n, int obj_alt, int obj_dano)
//	obj_tx: 	pos tile x
//	obj_ty:		pos tile y
//	z:			z
//	file:		file
//	n:			número de la animación empezando por 0
private
	int temp_tile;
	int ini_anim, fin_anim, frames_anim;
    int temp;
	
	int mdistx, mdisty;
	int mcol;
begin
	alpha = 190;
	priority = -100;
    //Se busca el inicio y el final de la animación
    temp = 0;
    fin_anim = 0;
    repeat
        ini_anim = fin_anim + 1;  //Se pone el inicio en el siguiente gráfico de la última búsqueda
        //Se busca la siguiente imagen
        while (!map_exists(file, ini_anim))
            ini_anim++;
        end
        fin_anim = ini_anim;    //se pone el fin en el primer gráfico de la serie
        //Se busca un hueco tras la serie de gráficos
        while (map_exists(file, fin_anim))
            fin_anim++;
        end
        //fin_anim--; //Se retrocede a la posición anterior, que no es el hueco
        frames_anim = fin_anim - ini_anim;
        
        temp++;
    until (temp >= n + 1)
	say("ini animm: " + ini_anim + "   fin ani: " + fin_anim + "    n frames: " + frames_anim);
	
	//se posiciona en el mapa
    x2 = (obj_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (obj_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    //Se borra el tile que hubiese antes
    temp_tile = obtener_tile(&nivel, obj_tx, obj_ty, 0);
    modificar_tile(&nivel, obj_tx, obj_ty, 0, 0);
		
	//Se anima el elemento
    graph = ini_anim;
    loop
		if (exists(info_prota.id_prota))
			mdistx = info_prota.id_prota.x2 - x2;
			mdisty = info_prota.id_prota.y2 - y2;
			if ((info_prota.id_prota.x2 >= x2 - (id_tscroll.tmapa[0].ancho_tile / 2)) &&
				(info_prota.id_prota.x2 < x2 + (id_tscroll.tmapa[0].ancho_tile / 2)) &&
				(info_prota.id_prota.y2 <= y2) && (info_prota.id_prota.y2 >= y2 - obj_alt))
				
				info_prota.dano_cont_id = id;
				info_prota.dano_cont_ener = obj_dano;
				mcol = 1;
			else
				mcol = 0;
			end
		end
        //if (graph < fin_anim) graph++; else graph = ini_anim; end
		graph = ini_anim + (sincronizacion % frames_anim);
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        //si sale de pantalla se borra
        if ((x > 370) || (x < -50) || (y <= -50) || (y >= 290))
            break;
        end
        frame;
    end
    
    modificar_tile(&nivel, obj_tx, obj_ty, 0, temp_tile);
end