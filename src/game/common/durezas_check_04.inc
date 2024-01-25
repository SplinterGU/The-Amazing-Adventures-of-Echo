        //*********************************************************
        //  comprobación tile actual
        //*********************************************************
        
        //p_dur indica los tiles actuales que rodean al personaje
        //vel_vert e vel_horiz indica las posiciones que nos podemos mover
        
        x3 += vel_horiz;   //actualizamos posición
        y3 += vel_vert;
        
        enem_offsx = (x3 / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        enem_offsy = (y3 / resolution3) % id_tscroll.tmapa[0].alto_tile;
        
        //say(itoa(enem_offsy));
        
        //y ahora nos movemos dentro del propio tile
        p_libre = 1;
        switch (enem_dur[1][1])
        //el tile está libre
        case 0,25,50,75,                    //normal
             33,34,83,84,                   //extras
             100,104,105,                   //especiales (extras)
             150..255:                      //otras
            
            p_libre = 1;
            //comprobamos no chocarnos con una pared o la esquina de un techo
            if (enem_offsx < VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                //pared
                switch (enem_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (enem_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                        enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                        vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end //pared
            
            
            if (enem_offsx < VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                //esquina de un techo
                switch (enem_dur[0][0])
                //no se puede subir
                case 1,2,3,4,13,14,15,16,51,52,53,54,63,64,65,66,   //normales
                     32,82:                                         //extras
                    if (enem_offsy < VAR_ENEM_ALTURA_TECHO)
                        if (vel_vert < 0) //chocamos con techo si estamos subiendo
                            y3 += (VAR_ENEM_ALTURA_TECHO - enem_offsy) * resolution3;
                            enem_offsy += (VAR_ENEM_ALTURA_TECHO - enem_offsy);
                            p_libre = 0;
                        end
                        //podemos chocar con techo también si hemos saltado y nos desplazamos de lado
                        if ((enem_offsx - vel_horiz) >= VAR_ENEM_MAX_AVANZAR_IZQUIERDA) 
                            x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                            enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                            //vel_horiz = 0;
                        end
                    end
                end
                end //switch
            end
            
            if (enem_offsx > VAR_ENEM_MAX_AVANZAR_DERECHA)
                switch (enem_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (enem_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                        enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                        vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end //pared
            
            if (enem_offsx > VAR_ENEM_MAX_AVANZAR_DERECHA)
                //esquina de un techo
                switch (enem_dur[2][0])
                //no se puede subir
                case 1,2,3,5,13,14,15,16,51,52,53,55,63,64,65,66,   //normales
                     32,82:                                         //extras
                    if (enem_offsy < VAR_ENEM_ALTURA_TECHO)
                        if (vel_vert < 0)
                            y3 += (VAR_ENEM_ALTURA_TECHO - enem_offsy) * resolution3;
                            enem_offsy += (VAR_ENEM_ALTURA_TECHO - enem_offsy);
                            p_libre = 0;
                        end
                        if ((enem_offsx - vel_horiz) <= VAR_ENEM_MAX_AVANZAR_DERECHA)
                            x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                            enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                            //vel_horiz = 0;
                        end
                    end
                end
                end //switch
            end
            //p_libre = 1;
            
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (enem_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                if (enem_offsy < VAR_ENEM_ALTURA_TECHO)
                    y3 += (VAR_ENEM_ALTURA_TECHO - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte baja a la derecha**********************************EL FALLO ESTA AQUI
            case 4,54:                                                               //quitar vel horiz
                if (enem_offsy < (enem_offsx - VAR_ENEM_DIFERENCIA_CON_TECHO))
                    y3 += (enem_offsx - VAR_ENEM_DIFERENCIA_CON_TECHO - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte baja a la derecha
            //techo diagonal, parte baja a la izquierda
            case 5,55:
                if (enem_offsy < (id_tscroll.tmapa[0].alto_tile - enem_offsx - VAR_ENEM_DIFERENCIA_CON_TECHO))
                    y3 += (id_tscroll.tmapa[0].alto_tile - enem_offsx -
							VAR_ENEM_DIFERENCIA_CON_TECHO - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte baja a la izquierda
            end //switch techo
        end //casilla libre
        
        //rampa, parte alta a la izquierda
        case 2,52,                  //normales
             26,76:                 //extras
            
            //comprobamos no chocarnos con una pared
            if (enem_offsx < VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                switch (enem_dur[0][0])    //miramos el superior
                //no se puede pasar (incluye medias rampas, para pasarlas tendríamos que estar en otro tile)
                case 1,3,4,14,15,16,51,53,54,64,65,66,          //normales
                     34,84:                                     //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede
                end //switch
            end
            if (enem_offsx > VAR_ENEM_MAX_AVANZAR_DERECHA)
                switch (enem_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (enem_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                        enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                        vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            p_libre = 1;
            
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (enem_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //la distancia es menor hacia la izquierda, apenas podemos avanzar
                if (enem_offsx < VAR_ENEM_ALTURA_TECHO)
                    x3 += (VAR_ENEM_ALTURA_TECHO - enem_offsx) * resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < VAR_ENEM_ALTURA_TECHO)
                    y3 += (VAR_ENEM_ALTURA_TECHO - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos estar a todo lo ancho del tile, pues la distancia es constante: un tile de altura
                if (enem_offsy < (enem_offsx - 1))
                    y3 += ((enem_offsx - 1) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (enem_offsx < ((id_tscroll.tmapa[0].ancho_tile / 2) - VAR_ENEM_DIFERENCIA_CON_TECHO))
				
                    x3 += (((id_tscroll.tmapa[0].ancho_tile / 2) - VAR_ENEM_DIFERENCIA_CON_TECHO) - enem_offsx) *
							resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //say(itoa(enem_estado));
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (enem_offsy >= enem_offsx)
                //say("hola");
                y3 += (enem_offsx - enem_offsy) * resolution3;
                if (enem_estado == 3) enem_estado = 0; end
                enem_mover_v = 0;
                //vel_vert = 0;
                vel_vert = abs(vel_horiz);// + cte_prota_acelerac;
            end
            
        end //está en rampa, parte alta a la izquierda
        
        //rampa, parte alta a la derecha
        case 3,53,                  //normales
             27,77:                 //extras
             
            //comprobamos no chocarnos con una pared
            if (enem_offsx < VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                switch (enem_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (enem_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                        enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                        vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            if (enem_offsx > VAR_ENEM_MAX_AVANZAR_DERECHA)
                switch (enem_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,              //normales
                     33,83:                                         //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede
                end //switch
            end
            p_libre = 1;
            
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (enem_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //la distancia es menor hacia la derecha, apenas podemos avanzar
                if (enem_offsx > VAR_ENEM_DIFERENCIA_CON_TECHO)
                    x3 -= (enem_offsx - VAR_ENEM_DIFERENCIA_CON_TECHO) * resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < VAR_ENEM_ALTURA_TECHO)
                    y3 += (VAR_ENEM_ALTURA_TECHO - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (enem_offsx > ((id_tscroll.tmapa[0].ancho_tile / 2) + VAR_ENEM_DIFERENCIA_CON_TECHO))
				
                    x3 -= (enem_offsx - ((id_tscroll.tmapa[0].ancho_tile / 2) + VAR_ENEM_DIFERENCIA_CON_TECHO)) *
							resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < (enem_offsx - 1))
                    y3 += ((enem_offsx - 1) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //podemos estar a todo lo ancho del tile, pues la distancia es constante: un tile de altura
                if (enem_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (enem_offsy >= (id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx))
                y3 += (id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx - enem_offsy) * resolution3;
                if (enem_estado == 3) enem_estado = 0; end
                enem_mover_v = 0;
                //vel_vert = 0;
                vel_vert = abs(vel_horiz);// + cte_enem_gravedad;
            end
            
        end //está en rampa, parte alta a la derecha
        
        //media rampa baja, parte alta a la izquierda
        case 13,28,             //normales
             63,78:             //extras
             
            //comprobamos no chocarnos con una pared
            if (enem_offsx < VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                switch (enem_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede
                end //switch tile lateral
                
                //miramos el tile superior
                switch (enem_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,61,63,64,65,66,     //normales
                     34,84:                             //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            if (enem_offsx > VAR_ENEM_MAX_AVANZAR_DERECHA)
                switch (enem_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (enem_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                        enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                        vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            p_libre = 1;
             
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (enem_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //la distancia es menor hacia la izquierda, apenas podemos avanzar
                if (enem_offsx < 12)
                    x3 += (12 - enem_offsx) * resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < VAR_ENEM_ALTURA_TECHO)
                    y3 += (VAR_ENEM_ALTURA_TECHO - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos estar a todo lo ancho del tile, pues la distancia es casi constante: un tile de altura
                if (enem_offsy < (enem_offsx - 1))
                    y3 += ((enem_offsx - 1) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (enem_offsx < ((id_tscroll.tmapa[0].ancho_tile / 2) - 4))
                    x3 += (((id_tscroll.tmapa[0].ancho_tile / 2) - 4) - enem_offsx) * resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (enem_offsy >= (((id_tscroll.tmapa[0].alto_tile / 2) - 1) + (enem_offsx / 2)))
                y3 += ((((id_tscroll.tmapa[0].alto_tile / 2) - 1) + (enem_offsx / 2)) - enem_offsy) * resolution3;
                if (enem_estado == 3) enem_estado = 0; end
                enem_mover_v = 0;
                //vel_vert = 0;
                vel_vert = abs(vel_horiz) / 2;
            end
            
        end //media rampa baja, parte alta a la izquierda
        
        //media rampa baja, parte alta a la derecha
        case 15,65,                 //normales
             30,80:                 //extras
            
            //comprobamos no chocarnos con una pared
            if (enem_offsx < VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                switch (enem_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (enem_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                        enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                        vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            if (enem_offsx > VAR_ENEM_MAX_AVANZAR_DERECHA)
                switch (enem_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el techo superior
                switch (enem_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,  //normales
                     33,83:                             //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            p_libre = 1;
            
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (enem_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //la distancia es menor hacia la derecha, apenas podemos avanzar
                if (enem_offsx > 3)
                    x3 -= (enem_offsx - 3) * resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < VAR_ENEM_ALTURA_TECHO)
                    y3 += (VAR_ENEM_ALTURA_TECHO - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (enem_offsx > ((id_tscroll.tmapa[0].ancho_tile / 2) + 4))
                    x3 -= (enem_offsx - ((id_tscroll.tmapa[0].ancho_tile / 2) + 4)) * resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < (enem_offsx - 1))
                    y3 += ((enem_offsx - 1) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //podemos estar a todo lo ancho del tile, pues la distancia es constante: un tile de altura
                if (enem_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (enem_offsy >= ((id_tscroll.tmapa[0].alto_tile - 1) - (enem_offsx / 2)))
                y3 += (((id_tscroll.tmapa[0].alto_tile - 1) - (enem_offsx / 2)) - enem_offsy) * resolution3;
                if (enem_estado == 3) enem_estado = 0; end
                enem_mover_v = 0;
                //vel_vert = 0;
                vel_vert = abs(vel_horiz) / 2;
            end
            
        end //está en media rampa baja, parte alta a la derecha
        
        //media rampa alta, parte alta a la izquierda
        case 14,64,                         //normales
             29,79:                         //extras
             
            //comprobamos no chocarnos con una pared
            if (enem_offsx < VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                switch (enem_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,51,53,54,64,65,66,              //normales
                     34,84:                                         //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede
                end //switch
            end
            if (enem_offsx > VAR_ENEM_MAX_AVANZAR_DERECHA)
                switch (enem_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el tile superior
                switch (enem_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,  //normales
                     33,83:                             //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            p_libre = 1;
             
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (enem_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //imposible estar aqui, lo empujamos fuera
                if (enem_offsx < 15)
                    x3 += (15 - enem_offsx) * resolution3;
                    vel_horiz = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //dificil cálculo. Se puede estar hasta poco más allá de la mitad, la distancia va 
                //desde un tile hasta medio tile
                if (enem_offsx > VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_IZQUIERDA) * resolution3;
                    p_libre = 0;
                end
                if (enem_offsy < (enem_offsx - 1))
                    y3 += ((enem_offsx - 1) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //la distancia va desde cero hasta tile y medio
                if (enem_offsx < VAR_ENEM_MAX_AVANZAR_DERECHA)
                    x3 += (VAR_ENEM_MAX_AVANZAR_DERECHA - enem_offsx) * resolution3;
                    vel_horiz = 0;
                end
                if (enem_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (enem_offsy >= (enem_offsx / 2))
                y3 += ((enem_offsx / 2) - enem_offsy) * resolution3;
                if (enem_estado == 3) enem_estado = 0; end
                enem_mover_v = 0;
                //vel_vert = 0;
                vel_vert = abs(vel_horiz) / 2;
            end
            
        end //media rampa alta, parte alta a la izquierda
        
        //media rampa alta, parte alta a la derecha
        case 16,66,                         //normales
             31,81:                         //extras
             
            //comprobamos no chocarnos con una pared
            if (enem_offsx < VAR_ENEM_MAX_AVANZAR_IZQUIERDA)
                switch (enem_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el tile superior
                switch (enem_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,51,53,54,64,65,     //normales
                     34,84:                             //extras
                    x3 += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx) * resolution3;
                    enem_offsx += (VAR_ENEM_MAX_AVANZAR_IZQUIERDA - enem_offsx);
                    vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            if (enem_offsx > VAR_ENEM_MAX_AVANZAR_DERECHA)
                switch (enem_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,              //normales
                     33,83:                                         //extras
                    x3 -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA) * resolution3;
                    enem_offsx -= (enem_offsx - VAR_ENEM_MAX_AVANZAR_DERECHA);
                    vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                end //switch
            end
            p_libre = 1;
             
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (enem_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //imposible estar aqui, lo empujamos fuera
                if (enem_offsx >= 0)
                    x3 -= (enem_offsx + 1) * resolution3;
                    vel_horiz = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //la distancia va desde tile y medio hasta cero
                if (enem_offsx > 5)
                    x3 -= (enem_offsx - 5) * resolution3;
                    vel_horiz = 0;
                end
                
                if (enem_offsy < (enem_offsx - 1))
                    y3 += ((enem_offsx - 1) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //dificil cálculo. Se puede estar hasta poco más allá de la mitad, la distancia va 
                //desde un medio tile hasta un tile
                if (enem_offsx < 13)
                    x3 += (13 - enem_offsx) * resolution3;
                    p_libre = 0;
                end
                if (enem_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - enem_offsx) - enem_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (enem_offsy >= ((id_tscroll.tmapa[0].alto_tile / 2) - (enem_offsx / 2)))
                y3 += (((id_tscroll.tmapa[0].alto_tile / 2) - (enem_offsx / 2)) - enem_offsy) * resolution3;
                if (enem_estado == 3) enem_estado = 0; end
                enem_mover_v = 0;
                //vel_vert = 0;
                vel_vert = abs(vel_horiz) / 2;
            end
        end //media rampa alta, parte alta a la izquierda
        
        //techo, parte baja a la derecha
        case 4,54:
            //si nos movemos lateralmente chocaremos con el techo, no debemos poder avanzar
            if ((vel_horiz > 0) && (enem_offsx > VAR_ENEM_DIFERENCIA_CON_TECHO))
			
                x3 -= (enem_offsx - VAR_ENEM_DIFERENCIA_CON_TECHO) * resolution3;
                enem_offsx -= (enem_offsx - VAR_ENEM_DIFERENCIA_CON_TECHO);
                if (vel_vert < 0)
                    vel_vert = 0;
                    enem_estado = 3;
                    enem_mover_v = 0;
                end
            end
            //da igual la dirección en la que nos movamos, no podemos atravesar el techo
            if (enem_offsy < (id_tscroll.tmapa[0].alto_tile + enem_offsx - 3))
                y3 += ((id_tscroll.tmapa[0].alto_tile + enem_offsx - 3) - enem_offsy) * resolution3;
                p_libre = 0;
            end
        end //techo parte baja a la derecha
        
        //techo, parte baja a la izquierda
        case 5,55:
            //si nos movemos lateralmente chocaremos con el techo, no debemos poder avanzar
            if ((vel_horiz < 0) && (enem_offsx < VAR_ENEM_ALTURA_TECHO))
                x3 += (VAR_ENEM_ALTURA_TECHO - enem_offsx) * resolution3;
                enem_offsx += (VAR_ENEM_ALTURA_TECHO - enem_offsx);
                if (vel_vert < 0)
                    vel_vert = 0;
                    enem_estado = 3;
                    enem_mover_v = 0;
                end
            end
            //da igual la dirección en la que nos movamos, no podemos atravesar el techo
            if (enem_offsy < ((2 * id_tscroll.tmapa[0].alto_tile) - 3 - enem_offsx))
                y3 += (((2 * id_tscroll.tmapa[0].alto_tile) - 3 - enem_offsx) - enem_offsy) * resolution3;
                p_libre = 0;
            end
        end //techo parte baja a la izquierda
        
        end //switch propio tile
        
        //comprobamos choque contra el techo
        if (!p_libre)
            if (vel_vert < 0) vel_vert = 0; end
            if (enem_estado == 2) 
                //cont_salto = cte_prota_max_salto;
                enem_estado = 3;
            end
            enem_mover_v = 0;
        end