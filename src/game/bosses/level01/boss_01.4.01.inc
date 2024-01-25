process fuego_espiritual (file, x2, y2)
private
    int cont_anim;
    int temp;
begin
    graph = 9;
    while (graph != 11)
        cont_anim++;
        switch (cont_anim)
        case 5: graph = 10; end
        case 10: graph = 9; cont_anim = 0; end
        end //switch
        
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 2;
                info_prota.dano_exp = 4;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        
        temp = collision(type normal_shot);
        while (temp != 0)
            temp.energia = 0;
            temp = collision(type normal_shot);
        end
        
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    if (exists(info_prota.id_prota))
        angle = fget_angle(x, y, info_prota.id_prota.x, info_prota.id_prota.y);
    end
    resolution = 10;
    x *= 10;
    y *= 10;
    
    while (!region_out(id, 0))
        advance(50);
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 2;
                info_prota.dano_exp = 4;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        
        temp = collision(type normal_shot);
        while (temp != 0)
            temp.energia = 0;
            temp = collision(type normal_shot);
        end
        
        frame;
    end
end


process fuego_espiritual2 (file, x2, y2)
private
    int cont_anim;
    int temp;
begin
    graph = 9;
    while (graph != 12)
        cont_anim++;
        switch (cont_anim)
        case 5: graph = 10; end
        case 10: graph = 9; cont_anim = 0; end
        end //switch
        
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 2;
                info_prota.dano_exp = 4;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        
        temp = collision(type normal_shot);
        while (temp != 0)
            temp.energia = 0;
            temp = collision(type normal_shot);
        end
        
        //tscroll_get_screen_position(&id_tscroll,x2,y2,&x,&y);
        frame;
    end
    
    loop
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 2;
                info_prota.dano_exp = 4;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        
        temp = collision(type normal_shot);
        while (temp != 0)
            temp.energia = 0;
            temp = collision(type normal_shot);
        end
        
        frame;
    end
end

process fuego_boleadoras (x2, y2, int fb_hijo1, int fb_hijo2)
private
    int cont;
    int angle2;
begin
    tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
    for (cont = 0; cont <= 120; cont++)
        angle += 6000;
        if (angle > 360000) angle -= 360000; end
        fb_hijo1.x = x + ((cont / 12) * cos(angle));
        fb_hijo1.y = y + ((cont / 12) * sin(angle));
        fb_hijo2.x = x + ((cont / 12) * cos(angle + 180000));
        fb_hijo2.y = y + ((cont / 12) * sin(angle + 180000));
        
        if (cont == 96)
            //signal(fb_hijo1, s_freeze);
            //signal(fb_hijo2, s_freeze);
            fb_hijo1.graph = 12;
            fb_hijo2.graph = 12;
        end
        if (cont > 96)
            fb_hijo1.angle = -angle - 90000;
            fb_hijo2.angle = -angle + 90000;
        end
        frame;
    end
    for (cont = 0; cont < (energia / 5); cont++)
        angle += 6000;
        if (angle > 360000) angle -= 360000; end
        fb_hijo1.x = x + (10 * cos(angle));
        fb_hijo1.y = y + (10 * sin(angle));
        fb_hijo2.x = x + (10 * cos(angle + 180000));
        fb_hijo2.y = y + (10 * sin(angle + 180000));
        fb_hijo1.angle = -angle - 90000;
        fb_hijo2.angle = -angle + 90000;
        frame;
    end
    father.graph = 3;
    cont = 0;
    resolution = 10;
    //tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
    x *= 10;
    y *= 10;
    if (father.flags == 0) angle2 = 180000; end
    loop
        cont++;
        if (cont == 25) father.graph = 2; end
        if (exists(info_prota.id_prota))
            angle2 = near_angle(angle2, fget_angle(x / 10, y / 10, info_prota.id_prota.x, info_prota.id_prota.y),
													2000);
        end
        xadvance(angle2, 40);
        
        angle += 12000;
        if (angle > 360000) angle -= 360000; end
        fb_hijo1.x = (x / 10) + (10 * cos(angle));
        fb_hijo1.y = (y / 10) + (10 * sin(angle));
        fb_hijo2.x = (x / 10) + (10 * cos(angle + 180000));
        fb_hijo2.y = (y / 10) + (10 * sin(angle + 180000));
        fb_hijo1.angle = -angle - 90000;
        fb_hijo2.angle = -angle + 90000;
        
        if (cont > 250)
            alpha = clamp( alpha - 3, 0, 255 );
            fb_hijo1.alpha = alpha;
            fb_hijo2.alpha = alpha;
        end
        if (alpha <= 0) break; end
        frame;
    end
    
    signal(fb_hijo1, s_kill);
    signal(fb_hijo2, s_kill);
end

process lanza_fuego (file, x, y, angle)
private
    int temp;
begin
    graph = 11;
    resolution = 10;
    x *= 10;
    y *= 10;
    while (!region_out(id, 0))
        advance(60);
        
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 2;
                info_prota.dano_exp = 4;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        //impacto con balas
        temp = collision(type normal_shot);
        while (temp)
            temp.energia = 0;
            temp = collision(type normal_shot);
        end
        
        frame;
    end
end

process satavamp_fuego (file, graph, x, y)
begin
    z = father.z + 1;
    flags = 4;
    signal(id, s_freeze);
    frame;
end

process satavamp_capa (file, graph, z)
begin
    signal(id, s_freeze);
    frame;
end


process satavamp ()
private
    int x3, y3;
    int angle2;             //sirve para flotar
    int angle3;
    int enem_estado;        //0: en espera
                            //1: teletransporte
                            //2: lanzamiento
                            //3: anillo de fuego
                            //4: boleadoras
                            //5: 3 bolas de fuego
    int enem_estado2;
    int cont_estado;
    
    int satavamp_capa_id;
    int satavamp_fuego_id;
    int hijos[5];
    
    int temp;               //usado en colision con las balas
    int cont;
    int temp_espada;
begin
    file = enem_grafs[0][cte_event];
    graph = 1;
    z = 1;
    x3 = 768;
    y3 = -30;
    x2 = x3;
    y2 = y3;
    satavamp_capa_id = satavamp_capa(file, 0, z + 1);
    while (y3 < 48)
        y3++;
        y2 = y3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    for (cont_estado = 0; cont_estado < 200; cont_estado++)
        angle2 += 4000;
        y2 = y3 + (4 * sin(angle2));
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    graph = 2;
    satavamp_capa_id.x = x;
    satavamp_capa_id.y = y;
    satavamp_capa_id.graph = 20;
    energia = 500;
    enem_ener_interface(id);
    frame(10000);
    
    prota_control = 1;
    angle2 = 0;
    
    loop
        switch (enem_estado)
        case 0:                     //espera
            graph = 1;
            cont_estado++;
            angle2 += 4000;
            y2 = y3 + (4 * sin(angle2));
            if (cont_estado == 400)
                cont_estado = 0;
                angle2 = 0;
                y3 = y2;
                enem_estado = rand(1, 5);          //****************************************************
            end
        end
        case 1:                     //teletransporte
            switch (enem_estado2)
            case 0:         //desaparece
                graph = 3;
                if (alpha > 2)
                    alpha = clamp( alpha - 3, 0, 255 );
                else
                    alpha = 0;
                    enem_estado2 = 1;
                    cont_estado = 50 * rand(0, energia / 100);
                end
                angle2 += 4000;
                y2 = y3 + (4 * sin(angle2));
            end
            case 1:         //espera
                if (cont_estado > 0) cont_estado--;
                else
                    enem_estado2 = 2;
                    x3 = (rand(32, 49) * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
                    y3 = (rand(3, 10) * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
                    x2 = x3;
                    y2 = y3;
                    graph = 2;
                end
            end
            case 2:         //reaparece
                if (alpha < 253) alpha = clamp( alpha + 3, 0, 255 );
                else
                    alpha = 255;
                    enem_estado2 = 3;
                    cont_estado = 25 + (energia / 10);
                end
                angle2 += 4000;
                y2 = y3 + (4 * sin(angle2));
            end
            case 3:         //distraido
                if (cont_estado > 0) cont_estado--;
                else
                    enem_estado2 = 0;
                    cont_estado = 0;
                    enem_estado = rand(0, 2);          //****************************************************
                end
            end
            end //switch
        end
        
        case 2:                 //lanzamiento
            switch (enem_estado2)
            case 0:         //saliendo de pantalla
                if (x3 < 656)//160)
                    x3--;
                    if (x3 < 480)
                        enem_estado2 = 1;
                        y3 = (rand(3, 10) * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
                        y2 = y3;
                        cont_estado = 4;
                        satavamp_fuego_id = satavamp_fuego(file, 8, -100, -100);
                    end
                else
                    x3++;
                    if (x3 > 832)
                        enem_estado2 = 2;
                        y3 = (rand(3, 10) * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
                        y2 = y3;
                        cont_estado = 4;
                        satavamp_fuego_id = satavamp_fuego(file, 8, -100, -100);
                    end
                end
                graph = 2;
                x2 = x3;
                //flotar
                angle2 += 4000;
                y2 = y3 + (4 * sin(angle2));
            end
            case 1:         //volar hacia la derecha
                flags = 1;
                cont_estado++;
                switch (cont_estado)
                case 5:  graph = 4; end
                case 10: graph = 5; end
                case 15: graph = 6; end
                case 20: graph = 7; cont_estado = 0; end
                end
                x3 += 7;
                x2 = x3;
                if (x2 > 862)
                    cont_estado = 0;
                    angle2 = 0;
                    enem_estado = rand(0, 2);
                    //say("nuevo enem estado: " + itoa(enem_estado));
                    //siguiente estado, primero hay que recolocarse... si procede
                    switch (enem_estado)
                    case 0:                 //pasamos a estado de recolocación a la derecha
                        enem_estado = 2;
                        enem_estado2 = 3;
                        y3 = (rand(3, 10) * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
                        y2 = y3;
                        if (exists(satavamp_fuego_id)) signal(satavamp_fuego_id, s_kill); end
                    end
                    case 1:                 //teletransporte, saltamos a la espera
                        enem_estado2 = 1;
                        alpha = 0;
                        if (exists(satavamp_fuego_id)) signal(satavamp_fuego_id, s_kill); end
                    end
                    case 2:                 //lanzamiento, ya que estamos en un lado...
                        enem_estado2 = 2;
                        y3 = (rand(3, 10) * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
                        y2 = y3;
                        cont_estado = 4;
                    end
                    end //switch
                end
            end
            case 2:         //volar hacia la izquierda
                flags = 0;
                cont_estado++;
                switch (cont_estado)
                case 5:  graph = 4; end
                case 10: graph = 5; end
                case 15: graph = 6; end
                case 20: graph = 7; cont_estado = 0; end
                end
                x3 -= 7;
                x2 = x3;
                if (x2 < 450)
                    cont_estado = 0;
                    angle2 = 0;
                    enem_estado = rand(0, 2);
                    //say("nuevo enem estado: " + itoa(enem_estado));
                    //siguiente estado, primero hay que recolocarse... si procede
                    switch (enem_estado)
                    case 0:                 //pasamos a estado de recolocación a la izquierda
                        enem_estado = 2;
                        enem_estado2 = 4;
                        y3 = (rand(3, 10) * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
                        y2 = y3;
                        if (exists(satavamp_fuego_id)) signal(satavamp_fuego_id, s_kill); end
                    end
                    case 1:                 //teletransporte, saltamos a la espera
                        enem_estado2 = 1;
                        alpha = 0;
                        if (exists(satavamp_fuego_id)) signal(satavamp_fuego_id, s_kill); end
                    end
                    case 2:                 //lanzamiento, ya que estamos en un lado...
                        enem_estado2 = 1;
                        y3 = (rand(3, 10) * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile / 2);
                        y2 = y3;
                        cont_estado = 4;
                    end
                    end //switch
                end
            end
            case 3:         //recolocar a la derecha
                //say("RIGHT x3: " + itoa(x3));
                if (x3 > 768)
                    graph = 2;
                    flags = 0;
                    x3--;
                    x2 = x3;
                    //flotar
                    angle2 += 4000;
                    y2 = y3 + (4 * sin(angle2));
                else
                    enem_estado = 0;
                    enem_estado2 = 0;
                end
            end
            case 4:         //recolocar a la izquierda
                //say("LEFT x3: " + itoa(x3));
                if (x3 < 544)
                    graph = 2;
                    flags = 1;
                    x3++;
                    x2 = x3;
                    //flotar
                    angle2 += 4000;
                    y2 = y3 + (4 * sin(angle2));
                else
                    enem_estado = 0;
                    enem_estado2 = 0;
                end
            end
            end //switch
        end
        
        case 3:                 //anillo de fuego
            switch (enem_estado2)
            case 0:             //generando el círculo
                graph = 2;
                angle3 += 4000;
                if (angle3 == 60000)
                    angle3 = 0;
                    hijos[cont] = fuego_espiritual(file, 
													x3 + (35 * cos((60000 * cont) + 30000 )),
													y3 + (35 * sin((60000 * cont) + 30000 )) );
                    cont++;
                    if (cont == 6)
                        enem_estado2 = 1;
                        angle3 = 30000;
                        cont =0;
                    end
                end
                //flotar
                angle2 += 4000;
                y2 = y3 + (4 * sin(angle2));
            end
            case 1:             //dando vueltas y lanzando
                angle3 += 6000;
                cont_estado++;
                if (angle3 > 360000) angle3 -= 360000; end
                
                //al llegar a la cuenta, buscamos un fuego para lanzarlo
                if (cont_estado >= (14 + (energia >> 2)))
                    for (cont = 0; cont < 6; cont++)
                        if (hijos[cont] != 0)
                            hijos[cont].graph = 11;
                            hijos[cont] = 0;
                            cont_estado = 0;
                            break;
                        end
                    end
                end
                
                //recorremos de nuevo la lista, actualizando valores del resto.
                //si no hay, cambia de estado2
                enem_estado2 = 2;
                for (cont = 0; cont < 6; cont++)
                    if (hijos[cont] != 0)
                        hijos[cont].x2 = x3 + (35 * cos(angle3 + (60000 * cont)));
                        hijos[cont].y2 = y3 + (35 * sin(angle3 + (60000 * cont)));
                        enem_estado2 = 1;
                    end
                end
                
                //enem_estado2 vale 2 si no quedan hijos, de lo contrario, vale 1
                //flotar
                angle2 += 4000;
                y2 = y3 + (4 * sin(angle2));
            end
            case 2:
                if (get_id(type fuego_espiritual))
                    //flotar
                    angle2 += 4000;
                    y2 = y3 + (4 * sin(angle2));
                else
                    enem_estado2 = 0;
                    cont = 0;
                    angle3 = 0;
                    cont_estado = 0;
                    enem_estado = rand(0, 1);          //***************************************
                end
            end
            end //switch
        end
        case 4:                     //boleadoras
            switch (enem_estado2)
            case 0:             //generando bolas
                graph = 2;
                cont_estado++;
                if (cont_estado >= (energia / 10))
                    if (cont <= 1)
                        hijos[cont] = fuego_espiritual2(file, x3 + 25, y3 - 14);
                        cont++;
                    else
                        cont = 0;
                        cont_estado = 0;
                        enem_estado2 = 1;
                        hijos[2] = fuego_boleadoras(x3 + 25, y3 - 14, hijos[0], hijos[1]);
                    end
                end
                //flotar
                angle2 += 4000;
                y2 = y3 + (4 * sin(angle2));
            end
            case 1:
                if (exists(hijos[2]))
                    //flotar
                    angle2 += 4000;
                    y2 = y3 + (4 * sin(angle2));
                else
                    cont = 0;
                    cont_estado = 0;
                    enem_estado2 = 0;
                    enem_estado = rand(0, 1);      //*************************************************
                end
            end
            end
        end
        case 5:                 //bolas de fuego
            switch (enem_estado2)
            case 0:     //inicializacion
                cont = rand(1, 5);
                enem_estado2 = 1;
            end
            case 1:
                graph = 3;
                cont_estado++;
                if (cont_estado >= ((25 + (energia / 4)) >> 1) )
                    if (exists(info_prota.id_prota))
                        angle3 = fget_angle(x3, y3, info_prota.id_prota.x2, info_prota.id_prota.y2);
                    end
                    lanza_fuego (file, x, y, angle3);
                    lanza_fuego (file, x, y, angle3 + 15000);
                    lanza_fuego (file, x, y, angle3 - 15000);
                    cont_estado = 0;
                    cont--;
                    enem_estado2 = 2;
                end
                //flotar
                angle2 += 4000;
                y2 = y3 + (4 * sin(angle2));
            end
            case 2:
                graph = 2;
                cont_estado++;
                if (cont_estado >= (25 + (energia / 4)) )
                    if (cont == 0)
                        enem_estado = rand(0, 1);          //**********************************************
                        enem_estado2 = 0;
                        angle3 = 0;
                    else
                        enem_estado2 = 1;
                    end
                    //enem_estado2 = 1;
                    cont_estado = 0;
                end
                //flotar
                angle2 += 4000;
                y2 = y3 + (4 * sin(angle2));
            end
            end //switch
        end
        end //switch
        
        //**************************************
        //  ZONA DE IMPACTOS
        //**************************************
        //impacto con las balas
        if (alpha == 255)
            temp = collision(type normal_shot);
            while (temp != 0)
                if ((graph != 1) && (graph != 3))
                    //say("GOLPE");
                    energia -= temp.energia;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                end
                temp.energia = 0;
                temp = collision(type normal_shot);
            end
			
            temp = collision(type espadazo);
            if ((temp != 0) && (temp != temp_espada))
                if ((graph != 1) && (graph != 3))
                    energia -= temp.energia;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                end
                temp_espada = temp;
            end
            if (energia <= 0) break; end
        end
        
        //impacto con el prota
        if (exists(info_prota.id_prota) && (alpha == 255))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 5;
                info_prota.dano_exp = 2;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        
        if (enem_estado != 2)
            if (exists(info_prota.id_prota))
                if (info_prota.id_prota.x < x)
					flags = 0;
				else
					flags = 1;
				end
            end
        end
        
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        if (graph == 2)
            satavamp_capa_id.x = x;
            satavamp_capa_id.y = y;
            satavamp_capa_id.graph = 20;
            satavamp_capa_id.alpha = alpha;
            satavamp_capa_id.flags = flags;
        else
            satavamp_capa_id.graph = 0;
        end
        if ((satavamp_fuego_id != 0) && exists(satavamp_fuego_id))
            satavamp_fuego_id.x = x;
            satavamp_fuego_id.y = y;
            satavamp_fuego_id.flags = 4 + flags;
        end
        frame;
    end
    
    signal_event_1_4_1_accesories (s_kill);
    
    fade(255, 255, 255, 255, 100);
    frame(300);
    fade_on(100);
    graph = 2;
    frame(5000);
    for (cont = 0; cont < 250; cont++)
        satavamp_capa_id.x = x;
        satavamp_capa_id.y = y;
        satavamp_capa_id.graph = 20;
        satavamp_capa_id.alpha = alpha;
        satavamp_capa_id.flags = flags;
        if ((mi_temblor != 0) && exists(mi_temblor))
            mi_temblor.energia = cont / 50;
        else
            mi_temblor = enem_temblor(id, cont / 50);
        end
        frame;
    end
    while (!region_out(id, 0))
        x += 2;
        y -= 2;
        angle -= 6000;
        satavamp_capa_id.x = x;
        satavamp_capa_id.y = y;
        satavamp_capa_id.angle = angle;
        frame;
    end
    if (exists(satavamp_capa_id)) signal(satavamp_capa_id, s_kill); end
    
    frame(10000);
end