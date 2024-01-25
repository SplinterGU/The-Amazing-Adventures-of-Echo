process mina (int enem_tx, int enem_ty)
private
    int cont_anim;
    int temp;
    int temp_espada;
begin
    priority = -99;
    file = enem_grafs[0][cte_mina];
    energia = 6;
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    graph = 2;
    loop
        cont_anim++;
        switch (cont_anim)
        case 25: graph = 1; end
        case 50: graph = 2; cont_anim = 0; end
        end //switch
        
        //*****************************
        // ZONA DE IMPACTOS
        //*****************************
        if (exists(info_prota.id_prota))
            //impacto con las balas
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                while (temp != 0)
                    energia -= temp.energia;
                    temp.energia = 0;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                    temp = collision(type normal_shot);
                end
            end
            
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                temp = collision(type espadazo);
                if ((temp != 0) && (temp != temp_espada))
                    energia -= temp.energia;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                    temp_espada = temp;
                end
            end
            if (energia <= 0) break; end
            
            
            //impacto con el prota
            if ((abs(info_prota.id_prota.x2 - x2) < 30) && (abs(info_prota.id_prota.y2 - y2) < 16))
                break;
            end
        end
        
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    graph = 3;
    for (temp = 0; temp < 50; temp++)
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    size = 10;
    graph = 4;
    z = -1;
    while (size < 100)
        size += 2;
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 7;
                    info_prota.dano_exp = 5;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 30;
                    else info_prota.dano_vel_horiz = -30;
                    end
                end
            end
        end
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    size = 100;
    while (alpha > 0)
        alpha = clamp( alpha - 5, 0, 255 );
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 5;
                    info_prota.dano_exp = 5;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 30;
                    else info_prota.dano_vel_horiz = -30;
                    end
                end
            end
        end
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    if (energia <= 0)
		random_item (3, x2, y2 - (id_tscroll.tmapa[0].ancho_tile / 2));
	end
end