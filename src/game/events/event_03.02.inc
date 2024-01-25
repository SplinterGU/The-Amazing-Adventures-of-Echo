process event_3_2 ()                    //PURGA DE ENEMIGOS
private
    int temp;
begin
    //procesos que usan enemigos
    temp = get_id(type enem_temblor);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type enem_temblor);
    end
    
    temp = get_id(type enem_temblor2);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type enem_temblor2);
    end
    
    temp = get_id(type enem_xtemblor);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type enem_xtemblor);
    end
    
    temp = get_id(type enem_smoke);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type enem_smoke);
    end
    
    temp = get_id(type visual_fx);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type visual_fx);
    end
    
    //disparos
    temp = get_id(type enem_normal_shot);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type enem_normal_shot);
    end
    
    temp = get_id(type enem_normal_shot2);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type enem_normal_shot2);
    end
    
    temp = get_id(type enem_canon_shot);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type enem_canon_shot);
    end
    
    //enemigos
    temp = get_id(type blobo);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type blobo);
    end
    
    temp = get_id(type canon);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type canon);
    end
    
    temp = get_id(type corvo);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type corvo);
    end
    
    temp = get_id(type flozat);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type flozat);
    end
    
    temp = get_id(type ghost_fly);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type ghost_fly);
    end
    
    temp = get_id(type ghost_fly_invencible);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type ghost_fly_invencible);
    end
    
    temp = get_id(type glotz);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type glotz);
    end
    
    temp = get_id(type guerrillero);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type guerrillero);
    end
    
    temp = get_id(type invencible_enem);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type invencible_enem);
    end
    
    temp = get_id(type mina);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type mina);
    end
    
    temp = get_id(type murcielago);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type murcielago);
    end
    
    temp = get_id(type spider);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type spider);
    end
    
    temp = get_id(type super_guerrillero);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type super_guerrillero);
    end
    
    temp = get_id(type volador1);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type volador1);
    end
    
    temp = get_id(type volador2);
    while (temp)
        if (temp.x < -50) signal(temp, s_kill); end
        temp = get_id(type volador2);
    end
end