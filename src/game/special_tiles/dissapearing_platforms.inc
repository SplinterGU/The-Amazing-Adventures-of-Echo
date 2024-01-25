process plataforma_auto_desaparece (x3,y3,file, int graph1, int graph2, tiempo)
//Plataforma de 1 tile de ancho que se atraviesa, que aparece durante TIEMPO segundos y desaparece
//otros TIEMPO segundos, con un retardo de MI_RETARDO, definido por el valor del mapa de durezas.
private
    int mi_retardo;
    int pad_cont;
    
    int temp;
begin
    //se ordenan de menor a mayor los gráficos de inicio y final (por si acaso)
    if (graph2 < graph1)
        temp = graph2;
        graph2 = graph1;
        graph1 = temp;
    end
    
    //Se coloca el tile
    modificar_tile(&nivel,x3,y3,0,0);
    priority=-99;
    x2=(x3*id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile/2);
    y2=(y3*id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile/2);
    
    mi_retardo=obtener_tile(&durezas,x3,y3,0)-150;  //Esto indica el retraso que lleva en el ciclo
                                                    //aparecer/desaparecer respecto a otros bloques con la misma
                                                    //cadencia (tiempo)
    //say("activacion: "+itoa(mi_activacion));
    //Se averigua cual es el estado inicial del bloque en función del tiempo que haya pasado
    temp = sincronizacion - (mi_retardo*50);    //se retarda el reloj de sincronizacion
    //say(x3 + "     cont: " + temp);
    while (temp < 0)    //se busca el valor positivo equivalente al estado, en caso de que fuese negativo
        temp += tiempo*50*2;
    end
    temp = temp % (50*tiempo*2);    //el 2 es porque está "tiempo" aparecido + "tiempo" desaparecido
    
    if ((temp > 0) && (temp <= tiempo*50))
        modificar_tile(&durezas,x3,y3,0,25);
        graph = graph1;
    else
        modificar_tile(&durezas,x3,y3,0,0);
        graph = graph2;
    end
    
    pad_cont = temp;    //se ajusta el contador respecto al reloj de sincronizacion
    tiempo = tiempo * 50; //Se convierte el tiempo de segundos a frames
    //frame;
    
    //say(x3 + "     pad_cont: " + pad_cont);
    loop
        //Se incrementa el contador interno
        pad_cont++;
        if (pad_cont >= tiempo*2)
            pad_cont -= (tiempo*2);
        end
        
        //hay 4 estados de la plataforma: apareciendo, aparecida, desapareciendo y desaparecida
        if ((pad_cont >= 0) && (pad_cont < graph2-graph1))  //apareciendo
            graph = graph2 - pad_cont;
            //say(graph2 + " " + pad_cont + " " + (tiempo+mi_retardo));
            //say("Estado: 0     cont: "+pad_cont+"     graph: "+graph);
        elsif (pad_cont == graph2-graph1) //primer frame de aparecido
            graph = graph1;
            modificar_tile(&durezas,x3,y3,0,25);
            //say("Estado: 1");
        elsif ((pad_cont >= tiempo) && (pad_cont < tiempo+graph2-graph1))  //desapareciendo
            graph = graph1 + pad_cont - tiempo;
            //say("Estado: 2     cont: "+pad_cont);
        elsif (pad_cont == tiempo+graph2-graph1) //primer frame de desaparecido
            graph = graph2;
            modificar_tile(&durezas,x3,y3,0,0);
            //say("Estado: 3");
        end
        
        tscroll_get_screen_position(&id_tscroll,x2,y2,&x,&y);
        frame;
    end
end

process plataforma_auto_desaparece2 (x3,y3,file, int graph1, int graph2, tiempo)
//Plataforma de 2 tiles de ancho que se atraviesa, que aparece durante TIEMPO segundos y desaparece
//otros TIEMPO segundos, con un retardo de MI_RETARDO, definido por el valor del mapa de durezas.
private
    int mi_retardo;
    int pad_cont;
    
    int temp;
begin
    //se ordenan de menor a mayor los gráficos de inicio y final (por si acaso)
    if (graph2 < graph1)
        temp = graph2;
        graph2 = graph1;
        graph1 = temp;
    end
    
    //Se coloca el tile
    modificar_tile(&nivel,x3,y3,0,0);
    priority=-99;
    x2=(x3*id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile/2);
    y2=(y3*id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile/2);
    
    mi_retardo=obtener_tile(&durezas,x3,y3,0)-150;  //Esto indica el retraso que lleva en el ciclo
                                                    //aparecer/desaparecer respecto a otros bloques con la misma
                                                    //cadencia (tiempo)
    //say("activacion: "+itoa(mi_activacion));
    //Se averigua cual es el estado inicial del bloque en función del tiempo que haya pasado
    temp = sincronizacion - (mi_retardo*50);    //se retarda el reloj de sincronizacion
    while (temp < 0)    //se busca el valor positivo equivalente al estado, en caso de que fuese negativo
        temp += tiempo*50*2;
    end
    temp = temp % (50*tiempo*2);    //el 2 es porque está "tiempo" aparecido + "tiempo" desaparecido
    
    if ((temp > 0) && (temp <= tiempo*50))
        modificar_tile(&durezas,x3,y3,0,1);
        modificar_tile(&durezas,x3+1,y3,0,25);
        graph = graph1;
    else
        modificar_tile(&durezas,x3,y3,0,0);
        modificar_tile(&durezas,x3+1,y3,0,0);
        graph = graph2;
    end
    
    pad_cont = temp;   //se ajusta el contador respecto al reloj de sincronizacion
    tiempo = tiempo * 50; //Se convierte el tiempo de segundos a frames
    //frame;
    
    loop
        //Se incrementa el contador interno
        pad_cont++;
        if (pad_cont >= tiempo*2)
            pad_cont -= (tiempo*2);
        end
        
        //hay 4 estados de la plataforma: apareciendo, aparecida, desapareciendo y desaparecida
        if ((pad_cont >= 0) && (pad_cont < graph2-graph1))  //apareciendo
            graph = graph2 - pad_cont;
        elsif (pad_cont == graph2-graph1) //primer frame de aparecido
            graph = graph1;
            modificar_tile(&durezas,x3,y3,0,25);
            modificar_tile(&durezas,x3+1,y3,0,25);
        elsif ((pad_cont >= tiempo) && (pad_cont < tiempo+graph2-graph1))  //desapareciendo
            graph = graph1 + pad_cont - tiempo;
        elsif (pad_cont == tiempo+graph2-graph1) //primer frame de desaparecido
            graph = graph2;
            modificar_tile(&durezas,x3,y3,0,0);
            modificar_tile(&durezas,x3+1,y3,0,0);
        end
        
        tscroll_get_screen_position(&id_tscroll,x2,y2,&x,&y);
        frame;
    end
end

//**************************************************************************************************

process plataforma_solida_desaparece (x3,y3,file, int graph1, int graph2, int graph3)
//plataforma que desparece al pisarla, tarda en desaparecer 0.2 segundos por cada frame de la animación
//de desaparecer
//x3, y3: posición en el mapa de tiles
//graph1: gráfico de tile en espera
//graph2: último gráfico de la animación de desaparecer
//graph3: último gráfico de la animación de reaparecer
private
    int estado; //0: en espera    1: desapareciendo    2:desparecido    3:reapareciendo
    int cont;
    int temp;
begin
    //se ordenan de menor a mayor los gráficos de inicio y final (por si acaso)
    if (graph2 < graph1)
        temp = graph2;
        graph2 = graph1;
        graph1 = temp;
    end
    if (graph3 < graph2)
        temp = graph3;
        graph3 = graph2;
        graph2 = temp;
    end
    if (graph2 < graph1)
        temp = graph2;
        graph2 = graph1;
        graph1 = temp;
    end
    
    //Se coloca el tile
    modificar_tile(&nivel,x3,y3,0,0);
    modificar_tile(&durezas,x3,y3,0,1);
    priority=-99;
    x2=(x3*id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile/2);
    y2=(y3*id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile/2);
    
    graph = graph1;
    loop
        switch (estado)
        case 0: //esperando a ser pisado
            if (exists(info_prota.id_prota))
                if (((y2-info_prota.id_prota.y2) == ((id_tscroll.tmapa[0].alto_tile/2)+1)) &&
                    (abs(x2-info_prota.id_prota.x2) <= 
                        ((id_tscroll.tmapa[0].ancho_tile/2) + cte_prota_max_avanzar_izquierda))
                   )
                    estado = 1;
                    cont = 0;
                end
            end
        end
        case 1: //desapareciendo
            cont++;
            if (cont >= 10)
                graph++;
                if (graph == graph2)
                    estado = 2;
                    modificar_tile(&durezas,x3,y3,0,0);
                end
                cont = 0;
            end
        end
        case 2: //desaparecido, en espera para reaparecer
            cont++;
            if ((cont >= 300) && !((info_prota.p_tilex == x3) && (info_prota.p_tiley == y3)))
                modificar_tile(&durezas,x3,y3,0,1);
                estado = 3;
                cont = 0;
            end
        end
        case 3: //reapareciendo
            cont++;
            if (cont >= 10)
                graph++;
                if (graph > graph3)
                    graph = graph1;
                    estado = 0;
                end
                cont = 0;
            end
        end
        end //switch
        
        tscroll_get_screen_position(&id_tscroll,x2,y2,&x,&y);
        frame;
    end
end

process plataforma_atravesable_desaparece (x3,y3,file, int graph1, int graph2, int graph3)
//plataforma que desparece al pisarla, tarda en desaparecer 0.2 segundos por cada frame de la animación
//de desaparecer
//x3, y3: posición en el mapa de tiles
//graph1: gráfico de tile en espera
//graph2: último gráfico de la animación de desaparecer
//graph3: último gráfico de la animación de reaparecer
private
    int estado; //0: en espera    1: desapareciendo    2:desparecido    3:reapareciendo
    int cont;
    int temp;
begin
    //se ordenan de menor a mayor los gráficos de inicio y final (por si acaso)
    if (graph2 < graph1)
        temp = graph2;
        graph2 = graph1;
        graph1 = temp;
    end
    if (graph3 < graph2)
        temp = graph3;
        graph3 = graph2;
        graph2 = temp;
    end
    if (graph2 < graph1)
        temp = graph2;
        graph2 = graph1;
        graph1 = temp;
    end
    
    //Se coloca el tile
    modificar_tile(&nivel,x3,y3,0,0);
    modificar_tile(&durezas,x3,y3,0,25);
    priority=-99;
    x2=(x3*id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile/2);
    y2=(y3*id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile/2);
    
    graph = graph1;
    loop
        switch (estado)
        case 0: //esperando a ser pisado
            if (exists(info_prota.id_prota))
                if (((y2-info_prota.id_prota.y2) == ((id_tscroll.tmapa[0].alto_tile/2)+1)) &&
                    (info_prota.vel_vert >= 0) &&
                    (abs(x2-info_prota.id_prota.x2) <= 
                        ((id_tscroll.tmapa[0].ancho_tile/2) + cte_prota_max_avanzar_izquierda))
                   )
                    estado = 1;
                    cont = 0;
                end
            end
        end
        case 1: //desapareciendo
            cont++;
            if (cont >= 10)
                graph++;
                if (graph == graph2)
                    estado = 2;
                    modificar_tile(&durezas,x3,y3,0,0);
                end
                cont = 0;
            end
        end
        case 2: //desaparecido, en espera para reaparecer
            cont++;
            if (cont >= 300)
                modificar_tile(&durezas,x3,y3,0,25);
                estado = 3;
                cont = 0;
            end
        end
        case 3: //reapareciendo
            cont++;
            if (cont >= 10)
                graph++;
                if (graph > graph3)
                    graph = graph1;
                    estado = 0;
                end
                cont = 0;
            end
        end
        end //switch
        
        tscroll_get_screen_position(&id_tscroll,x2,y2,&x,&y);
        frame;
    end
end
