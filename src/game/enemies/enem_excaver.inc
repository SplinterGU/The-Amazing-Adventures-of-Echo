process excaver (int enem_tx, int enem_ty, file)
private
    int x3, y3;
    int resolution3;
    
    int ini_x2, fin_x2;
    int vel_horiz, max_vel_horiz;
    
    int temp;
    int temp_tile;
    int cont_anim;
begin
    priority = -99;
    z = 1;
    resolution3 = 10;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    x3 = x2 * resolution3;
    
    //Se busca el límite derecho (se suenta un tile menos para la deceleracion)
    temp = enem_tx;
    while ((temp > 0) && (obtener_tile(&durezas, temp, enem_ty, 0) != 254))
        temp--;
    end
    ini_x2 = (temp + 2) * id_tscroll.tmapa[0].ancho_tile;
    //Se busca el límite izquierdo (se suenta un tile menos para la deceleracion)
    temp = enem_tx;
    while ((temp < (id_tscroll.tmapa[0].columnas - 2) ) && (obtener_tile(&durezas, temp, enem_ty, 0) != 253))
        temp++;
    end
    fin_x2 = (temp - 1) * id_tscroll.tmapa[0].ancho_tile;
    max_vel_horiz = 40;
    if (info_prota.id_prota.x2 < x2)
        vel_horiz = -max_vel_horiz;
    else
        vel_horiz = max_vel_horiz;
    end
    
    temp_tile = obtener_tile(&nivel, enem_tx, enem_ty, 0);
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    
    graph = 1;
    loop
        //say(x);
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        if ((vel_horiz < max_vel_horiz) && (x2 < fin_x2))
            vel_horiz += 2;
        end
        if ((vel_horiz > -max_vel_horiz) && (x2 > ini_x2))
            vel_horiz -= 2;
        end
        
        x3 += vel_horiz;
        
        x2 = x3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        //Zona de gráficos
        cont_anim++;
        if (cont_anim == 3)
            cont_anim = 0;
            if (graph < 3)
                graph++;
            else
                graph = 1;
            end
        end
        if (vel_horiz < 0) flags = 1; else flags = 0; end
        
        //choque con los disparos
        if (exists(info_prota.id_prota))
            //impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 5;
                    info_prota.dano_exp = 5;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                    else info_prota.dano_vel_horiz = -20;
                    end
                end
            end
        end
        
        //En espera si sale de la pantalla
        if (((x2 <= ini_x2) && (x > 370)) || ((x2 >= fin_x2) && (x < -50)) || (y <= -50) || (y >= 290))
            modificar_tile(&nivel, enem_tx, enem_ty, 0, temp_tile);
            break;
        end
        frame;
    end
end