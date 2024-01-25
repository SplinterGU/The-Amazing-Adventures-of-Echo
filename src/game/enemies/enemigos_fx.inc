process enem_explos (x2, y2, int vel_horiz, int vel_vert)
private
    int cont_anim;
begin
    z = father.z - 1;
    file = explosion_grafs;
    graph = 1;
    while (graph <= 6)
        cont_anim++;
        if (cont_anim == 3)
            cont_anim = 0;
            graph++;
        end
        x2 += vel_horiz;
        y2 += vel_vert;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
end

process enem_temblor (int enem_id, energia)
//Agita enemigos al recibir daño, no importa que se desplace con esta funcion porque se
//ajustan ellos solos
private
    int cont;
begin
    if (exists(enem_id)) priority = enem_id.priority - 1; end
    while (energia > 0)
        if (exists(enem_id))
            angle += 90000;
            angle = angle % 360000;
            //say(itoa(angle) + " " + itoa(energia * sin(angle)));
            enem_id.x += energia * sin(angle);
            if (angle == 270000) energia--; end
            frame;
        else
            break;
        end
    end
end

process enem_temblor2 (int enem_id, energia)      //usar con enemigos estáticos
//Agita enemigos al recibir daño, esta función los mantiene fijos en una posición, sin que se desplacen
private
    int cont;
begin
    if (exists(enem_id))
        priority = enem_id.priority - 1;
        x = enem_id.x;
        //y = enem_id.y;
    end
    while (energia > 0)
        if (exists(enem_id))
            angle += 90000;
            angle = angle % 360000;
            //say(itoa(angle) + " " + itoa(energia * sin(angle)));
            enem_id.x = x + energia * sin(angle);
            if (angle == 270000) energia--; end
            frame;
        else
            break;
        end
    end
    if (exists(enem_id)) enem_id.x = x; end
end

process enem_xtemblor (int enem_id, energia, resolution)
//Agita enemigos al recibir daño, no importa que se desplace con esta funcion porque se
//ajustan ellos solos. tiene en cuenta la variable resolution?
private
    int cont;
begin
    if (exists(enem_id)) priority = enem_id.priority - 1; end
    while (energia > 0)
        if (exists(enem_id))
            angle += 90000;
            angle = angle % 360000;
            //say(itoa(angle) + " " + itoa(energia * sin(angle)));
            enem_id.x += energia * resolution * sin(angle);
            if (angle == 270000) energia--; end
            frame;
        else
            break;
        end
    end
end

process enem_smoke (file ,int graph1, int graph2, x2, y2, flags)
//Humo del tabaco que fuma el guerrillero
private
    int cont;
begin
    priority = -99;
    graph = graph1;
    loop
        if (cont == 10)
            if (graph < graph2) graph++; end
            cont = 0;
        end
        cont++;
        alpha = clamp( alpha - 1, 0, 255 );
        if (alpha == 0) break; end
        
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
end

process visual_fx (file, graph, x2, y2, int cont, flags)
//Imagen estática que dura unos segundos para el enemigo (ej, exclamación guerrilla)
begin
    priority = -99;
    loop
        if (cont == 0) break; end
        cont--;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
end
