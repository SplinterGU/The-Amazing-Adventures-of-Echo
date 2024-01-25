process event_5_2y5_3 (int e_tilex, int e_tiley)
private
    savegame_item_got ev5253_item;
begin
    //say("salvando: " + e_tilex + "," + e_tiley);
    x2 = (e_tilex * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (e_tiley * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
    while ((info_prota.id_prota != 0) && exists(info_prota.id_prota) && (abs(info_prota.id_prota.x2 - x2) > 16))
        frame;
    end
    
    if ((info_prota.id_prota != 0) && exists(info_prota.id_prota))
        //next_sublevel++;
        
        //añadimos a lista de items conseguidos
        ev5253_item.level = next_level;
        ev5253_item.sublevel = next_sublevel;
        ev5253_item.pos_x = e_tilex;
        ev5253_item.pos_y = e_tiley;
        ev5253_item.item = 253;
        savegame_item_got_list_add(ev5253_item);
        
        //Salvamos partida
        if (savegame_pos != 0)
            refresh_actual_gamedata(&game_global_sav);
            save_filegame(&game_global_sav, savegame_pos);
            //g_show_saved = 1;
            game_saved_graph();
        end
    end
end