process spikes (int enem_tx, int enem_ty, file)
private
    int temp;
    int temp_tile;
begin
    priority = -99;
    z = 1;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    
    temp_tile = obtener_tile(&nivel, enem_tx, enem_ty, 0);
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    
    graph = 1;
    loop
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        //choque con los disparos
        if (exists(info_prota.id_prota))
            //impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 12) && (abs(y - info_prota.id_prota.y) < 16))
                //say(abs(x - info_prota.id_prota.x) + "  " + (y - info_prota.id_prota.y));
                //if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 20;
                    info_prota.dano_exp = 9;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                    else info_prota.dano_vel_horiz = -20;
                    end
					//end
            end
        end
        
        if ((x <= -50) || (x >= 370) || (y <= -50) || (y >= 290))
            modificar_tile(&nivel, enem_tx, enem_ty, 0, temp_tile);
            break;
        end
        frame;
    end
end
