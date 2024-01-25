// ENEMIGO VOLADOR QUE ATRAVIESA LAS PAREDES Y ES INVENCIBLE
process ghost_fly_invencible (int enem_tx, int enem_ty) //, int enem_despx)
private
    int enem_despx;
    int vel_horiz;
    int vel_vert;
    int x3, y3;
    int resolution3;
    int ini_x2, fin_x2;
    int ini_y2;
    
    int cont_anim;
    int cont;
    int temp;
    int temp_tile;
begin
    temp_tile = obtener_tile(&nivel, enem_tx, enem_ty, 0);
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
    energia = 4;
    
    file = enem_grafs[0][cte_ghost_fly];
    graph = 1;
    flags = 4;
    z = -1;
    
    ini_x2 = x2;
    fin_x2 = x2 - (enem_despx * id_tscroll.tmapa[0].ancho_tile);
    ini_y2 = y2;
    vel_horiz = -25;
    
    loop
        if ((vel_horiz < 25) && (x2 < fin_x2))
            vel_horiz++;
            flags = 1 + 4;
        end
        if ((vel_horiz > -25) && (x2 > ini_x2))
            vel_horiz--;
            flags = 4;
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
                if (temp != 0)
                    //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
                    //say("el disparo tenía energia: " + itoa(temp.energia));
                    temp.energia = 0;
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
        
        if ( (abs(id_tscroll.camera_x - x2) > 480) || (abs(id_tscroll.camera_y - y2) > 360) ) break; end
        frame;
    end
    
    modificar_tile(&nivel, enem_tx, enem_ty, 0, temp_tile);
end