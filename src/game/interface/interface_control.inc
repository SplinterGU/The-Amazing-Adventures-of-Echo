//**************************************************************************************************
//  PROCESOS QUE MUESTRAN LA INTERFAZ
//**************************************************************************************************

process interface_fix_image (graph, x, y, z)
begin
    //z = -5;
    signal(id, s_freeze);
    frame;
end

process interface_weap_image (x, y, z)
begin
    region = CTE_REGION_INTERFAZ_ARMAS;
    //z = -5;
    signal(id, s_freeze);
    frame;
end

function set_interface ()
begin
    interface_fix_image(interfaz_grafs[INTERFAZ_FONDO_BLANCO], 1, 2, -6);
    interface_fix_image(interfaz_grafs[INTERFAZ_NUMEROS_ENERGIA], 246, 2, -6);
    interface_fix_image(interfaz_grafs[INTERFAZ_NUMEROS_EXP], 246, 11, -6);
    interface_fix_image(interfaz_grafs[INTERFAZ_FONDO_FPG], 0, 0, -5).flags = 4;
    
    
    interfaz_armas_id[0] = interface_weap_image(11, 229, -5);
    interfaz_armas_id[1] = interface_weap_image(35, 229, -5);
    interfaz_armas_id[2] = interface_weap_image(59, 229, -5);
    interfaz_armas_id[3] = interface_weap_image(83, 229, -5);
    
    refresh_weapons();
end

function unset_interface ()
private
    int temp;
begin
    temp = get_id(type interface_fix_image);
    while (temp)
        signal(temp, s_kill);
        temp = get_id(type interface_fix_image);
    end
    
    temp = get_id(type interface_weap_image);
    while (temp)
        signal(temp, s_kill);
        temp = get_id(type interface_weap_image);
    end
end

//**************************************************************************************************


process mover_iconos_armas_interfaz ()
private
    int miai_desplazar;
    int cont;
    int temp_id;
begin
    //Primero eliminamos cualquiero otro proceso igual anterior creado
    temp_id = get_id(type mover_iconos_armas_interfaz);   //buscamos otro proceso igual que no sea este
    if (temp_id == id) temp_id = get_id(type mover_iconos_armas_interfaz); end
    
    if ((temp_id != 0) && (temp_id != id))
        signal(temp_id, s_kill);
        frame;
        while (exists(temp_id)) frame; end
    end
    
    switch (armas_select)
    case 0,1:
        miai_desplazar = 11 - interfaz_armas_id[0].x;
    end
    case CTE_LAST_WEAPON:
        miai_desplazar = 11 - ((CTE_LAST_WEAPON - 3) * 24) - interfaz_armas_id[0].x;
    end
    default:
        miai_desplazar = 11 - interfaz_armas_id[0].x - ((armas_select -2) * 24);
    end
    end //switch
    
    while (miai_desplazar > 0)
        for (cont = 0; cont < CTE_LAST_WEAPON; cont++)
            interfaz_armas_id[cont].x++;
        end
        miai_desplazar--;
        frame;
    end
    while (miai_desplazar < 0)
        for (cont=0; cont < CTE_LAST_WEAPON; cont++)
            interfaz_armas_id[cont].x--;
        end
        miai_desplazar++;
        frame;
    end
end
