function signal_items (int si_signal)
private
    int temp;
begin
    temp = get_id(type bridge);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type bridge);
    end
    
    temp = get_id(type door);
    while (temp)
        signal(temp ,si_signal);
        temp = get_id(type door);
    end
    
    temp = get_id(type item_add_energy);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_add_energy);
    end
    
    temp = get_id(type shot_exp);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type shot_exp);
    end
    
    temp = get_id(type item_energy);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_energy);
    end
    
    temp = get_id(type new_weapon);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type new_weapon);
    end
    
    temp = get_id(type button);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type button);
    end
    
    temp = get_id(type item_end_sublevel);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_end_sublevel);
    end
    
    temp = get_id(type item_end_level);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_end_level);
    end
	
	temp = get_id(type item_checkpoint);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_checkpoint);
    end
	
	temp = get_id(type item_press_down);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_press_down);
    end
    
    temp = get_id(type event);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type event);
    end
end

function signal_moving_items (int si_signal)
private
    int temp;
begin
    
    /*temp = get_id(type item_add_energy);
    while (temp)
        signal(temp,si_signal);
        temp = get_id(type item_add_energy);
    end*/
    
    temp = get_id(type shot_exp);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type shot_exp);
    end
    
    temp = get_id(type item_energy);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_energy);
    end
    
    temp = get_id(type button);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type button);
    end
    
    /*temp = get_id(type item_end_sublevel);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_end_sublevel);
    end*/
    
    /*temp = get_id(type item_end_level);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type item_end_level);
    end*/
    
    temp = get_id(type event);
    while (temp)
        signal(temp, si_signal);
        temp = get_id(type event);
    end
end



process signal_enemigos (int se_signal)
private
    int temp;
begin
    //procesos que usan enemigos
    temp = get_id(type enem_temblor);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type enem_temblor);
    end
    
    temp = get_id(type enem_temblor2);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type enem_temblor2);
    end
    
    temp = get_id(type enem_xtemblor);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type enem_xtemblor);
    end
    
    temp = get_id(type enem_smoke);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type enem_smoke);
    end
    
    temp = get_id(type visual_fx);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type visual_fx);
    end
    
    temp = get_id(type enem_explos);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type enem_explos);
    end
    
    //disparos
    temp = get_id(type enem_normal_shot);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type enem_normal_shot);
    end
    
    temp = get_id(type enem_normal_shot2);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type enem_normal_shot2);
    end
    
    temp = get_id(type enem_canon_shot);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type enem_canon_shot);
    end
    
    //enemigos
    temp = get_id(type blobo);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type blobo);
    end
    
    temp = get_id(type canon);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type canon);
    end
    
    temp = get_id(type corvo);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type corvo);
    end
    
    temp = get_id(type flozat);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type flozat);
    end
    
    temp = get_id(type ghost_fly);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type ghost_fly);
    end
    
    temp = get_id(type ghost_fly_invencible);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type ghost_fly_invencible);
    end
    
    temp = get_id(type glotz);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type glotz);
    end
    
    temp = get_id(type guerrillero);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type guerrillero);
    end
    
    temp = get_id(type invencible_enem);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type invencible_enem);
    end
    
    temp = get_id(type mina);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type mina);
    end
    
    temp = get_id(type murcielago);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type murcielago);
    end
    
    temp = get_id(type spider);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type spider);
    end
    
    temp = get_id(type super_guerrillero);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type super_guerrillero);
    end
    
    temp = get_id(type volador1);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type volador1);
    end
    
    temp = get_id(type volador2);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type volador2);
    end
    
    temp = get_id(type excaver);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type excaver);
    end
    
    temp = get_id(type roca_lanzador);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type roca_lanzador);
    end
    
    temp = get_id(type roca_rodante);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type roca_rodante);
    end
    
    temp = get_id(type vigilante_horus);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type vigilante_horus);
    end
    
end

process signal_sync (int ss_signal)
private
    int temp;
begin
    //procesos que usan enemigos
    temp = get_id(type sync_counter);
    while (temp)
        signal(temp, ss_signal);
        temp = get_id(type sync_counter);
    end
end

process signal_tiles_especiales (int ste_signal)
private
    int temp;
begin
    //tiles animados
    temp = get_id(type objeto_animado_sincronizado);
    while (temp)
        signal(temp, ste_signal);
        temp = get_id(type objeto_animado_sincronizado);
    end
    
    //tiles de agua
    temp = get_id(type tile_agua);
    while (temp)
        signal(temp, ste_signal);
        temp = get_id(type tile_agua);
    end
	
	//tiles de lava
	temp = get_id(type tile_lava);
    while (temp)
        signal(temp, ste_signal);
        temp = get_id(type tile_lava);
    end
	
	//plataformas desaparecen
	temp = get_id(type plataforma_auto_desaparece);
    while (temp)
        signal(temp, ste_signal);
        temp = get_id(type plataforma_auto_desaparece);
    end
	
	temp = get_id(type plataforma_auto_desaparece2);
    while (temp)
        signal(temp, ste_signal);
        temp = get_id(type plataforma_auto_desaparece2);
    end
	
	temp = get_id(type plataforma_solida_desaparece);
    while (temp)
        signal(temp, ste_signal);
        temp = get_id(type plataforma_solida_desaparece);
    end
	
	temp = get_id(type plataforma_atravesable_desaparece);
    while (temp)
        signal(temp, ste_signal);
        temp = get_id(type plataforma_atravesable_desaparece);
    end
	
	temp = get_id(type plataforma_movil_por_contacto);
    while (temp)
        signal(temp, ste_signal);
        temp = get_id(type plataforma_movil_por_contacto);
    end
	
end
