process objeto_animado (int obj_tx, int obj_ty, z, file, alpha, int n)
//Crea un objeto animado, basado en una secencia de mapas guardada en un FPG, que contiene varias
//animaciones. Buscamos la animación número N. La primera es la 0
private
    int ini_anim, fin_anim;
    int temp;
    int temp_tile;
begin
    //Se busca el inicio y el final de la animación n
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
        fin_anim--; //Se retrocede a la posición anterior, que no es el hueco
        
        temp++;
    until (temp >= n + 1)
    
    //se posiciona en el mapa
    x2 = (obj_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (obj_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    //Se borra el tile que hubiese antes
    temp_tile = obtener_tile(&nivel, obj_tx, obj_ty, 0);
    modificar_tile(&nivel, obj_tx, obj_ty, 0, 0);
    
    //Se anima el elemento
    graph = ini_anim;
    loop
        if (graph < fin_anim) graph++; else graph = ini_anim; end
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        //si sale de pantalla se borra
        if ((x > 370) || (x < -50) || (y <= -50) || (y >= 290))
            break;
        end
        frame;
    end
    
    modificar_tile(&nivel, obj_tx, obj_ty, 0, temp_tile);
end

process objeto_animado_sincronizado (int obj_tx, int obj_ty, z, file, alpha, int n, int oas_frames_por_imagen)
private
    int ini_anim, fin_anim, frames_anim;
    int total_cuenta_frames;
    int temp;
    int temp_tile;
begin
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
    
    //se posiciona en el mapa
    x2 = (obj_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (obj_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    //Se borra el tile que hubiese antes
    temp_tile = obtener_tile(&nivel, obj_tx, obj_ty, 0);
    modificar_tile(&nivel, obj_tx, obj_ty, 0, 0);
    
    //Se anima el elemento
    graph = ini_anim;
    total_cuenta_frames = frames_anim * oas_frames_por_imagen;
    loop
        //if (graph < fin_anim) graph++; else graph = ini_anim; end
        graph = ini_anim + ((sincronizacion % (total_cuenta_frames)) / oas_frames_por_imagen);
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        //si sale de pantalla se borra
        if ((x > 370) || (x < -50) || (y <= -50) || (y >= 290))
            break;
        end
        frame;
    end
    
    modificar_tile(&nivel, obj_tx, obj_ty, 0, temp_tile);
end
