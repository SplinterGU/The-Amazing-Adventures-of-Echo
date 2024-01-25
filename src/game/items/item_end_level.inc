//***************************************************************************
//  ITEMS ESPECIALES: FIN DE PANTALLA Y NIVEL
//***************************************************************************

process item_end_sublevel (x3, y3)
begin
    modificar_tile(&nivel, x3, y3, 0, 0);
    //file = item_grafs;
    //graph = 51;
    
    x2 = (x3 * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (y3 * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    
    loop
        if (exists(info_prota.id_prota))
            //if (collision(info_prota.id_prota)) break; end
            if ( (abs(info_prota.id_prota.x2 - x2) < (id_tscroll.tmapa[0].ancho_tile / 2)) &&
                 (abs(info_prota.id_prota.y2 - y2) < (id_tscroll.tmapa[0].alto_tile / 2))   )
                break;
            end
        end
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    pausa_estado = 0;
    prota_control = 0;
    if (exists(info_prota.id_prota)) signal(info_prota.id_prota, s_freeze_tree); end
    signal_moving_items(s_freeze);
    signal_enemigos(s_freeze);
    signal_tiles_especiales(s_freeze);
    
    fade_off(300);
    while (fade_info.fading) frame; end
    
    //next_sublevel = obtener_tile(&durezas, x3, y3, 0) - 150;
    
    /*if (savegame_pos != 0)
        refresh_actual_gamedata(&game_global_sav);
        save_filegame(&game_global_sav, savegame_pos);
        game_saved_graph();
    end*/
    
    end_level = 1;
end

process item_end_level (x3, y3)
begin
    modificar_tile(&nivel, x3, y3, 0, 0);
    file = item_grafs;
    graph = 52;
    //alpha = 0;
    
    x2 = (x3 * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (y3 * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    
    loop
        if (exists(info_prota.id_prota))
            //if (collision(info_prota.id_prota)) break; end
            if ( (abs(info_prota.id_prota.x2 - x2) < (id_tscroll.tmapa[0].ancho_tile / 2)) &&
                 (abs(info_prota.id_prota.y2 - y2) < (id_tscroll.tmapa[0].alto_tile / 2))   )
                break;
            end
        end
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    //next_level = obtener_tile(&durezas, x3, y3, 0) - 150;
    //say(next_level);
    end_level = 1;
end