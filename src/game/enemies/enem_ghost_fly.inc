// ENEMIGO VOLADOR QUE ATRAVIESA LAS PAREDES
process ghost_fly (int enem_tx, int enem_ty, energia) //, int enem_despx)
private
    int enem_despx;
    int vel_horiz;
    int vel_vert;
    int x3,y3;
    int resolution3;
    int ini_x2, fin_x2;
    int ini_y2;
    
    int cont_anim;
    int cont;
    int temp;
    int temp_espada;
begin
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    enem_despx = obtener_tile(&durezas, enem_tx, enem_ty, 0);
    if ((enem_despx >= 150) && (enem_despx <= 250))
        enem_despx -= 150;
    else
        enem_despx = 0;
    end
    //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));

    x2 = enem_tx * id_tscroll.tmapa[0].ancho_tile;
    y2 = enem_ty * id_tscroll.tmapa[0].alto_tile;
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    //energia = 4;
    
    file = enem_grafs[0][cte_ghost_fly];
    graph = 1;
    z = 1;
    
    ini_x2 = x2;
    fin_x2 = x2 - (enem_despx * id_tscroll.tmapa[0].ancho_tile);
    ini_y2 = y2;
    vel_horiz = -25;
    
    loop
        if ((vel_horiz < 25) && (x2 < fin_x2))
            vel_horiz++;
            flags = 1;
        end
        if ((vel_horiz > -25) && (x2 > ini_x2))
            vel_horiz--;
            flags = 0;
        end
        
        x3 += vel_horiz;
        y3 = (ini_y2 * resolution3) + (50 * sin(cont * 1000));
        cont += 3;
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        cont_anim++;
        switch (cont_anim)
        case 3: graph = 2; end
        case 6: graph = 1; cont_anim = 0; end
        end //switch
        
        //choque con los disparos
        if (exists(info_prota.id_prota))
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                while (temp != 0)
                    energia -= temp.energia;
                    //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
                    //say("el disparo tenía energia: " + itoa(temp.energia));
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
        
        if (energia <= 0) break; end
        frame;
    end
    
    //explosion
    //suelta de items
    //shot_exp(x2, y2, 5, 10);
    random_item (2, x2, y2 - (id_tscroll.tmapa[0].ancho_tile / 2));
    enem_explos(x2, y2, 0, 0);
end