		//p_dur indica los tiles actuales que rodean al personaje
        //info_prota.vel_vert e info_prota.vel_horiz indica las posiciones que nos podemos mover
        
        x3 += info_prota.vel_horiz;   //actualizamos posición
        y3 += info_prota.vel_vert;
        
        info_prota.p_offsx = (x3 / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        info_prota.p_offsy = (y3 / resolution3) % id_tscroll.tmapa[0].alto_tile;
        
        //say(itoa(info_prota.p_offsy));
        
        //y ahora nos movemos dentro del propio tile
        p_libre = 1;
        switch (p_dur[1][1])
        //el tile está libre
        case 0,25,50,75,                    //normal
             33,34,83,84,                   //extras
             100,104,105,                   //especiales (extras)
             150..255:                      //otras
            
            p_libre = 1;
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < 4)
                //pared
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (4 - info_prota.p_offsx) * resolution3;
                        info_prota.p_offsx += (4 - info_prota.p_offsx);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end  //pared
            
                
            if (info_prota.p_offsx < 4)
                //esquina de un techo
                switch (p_dur[0][0])
                //no se puede subir
                case 1,2,3,4,13,14,15,16,51,52,53,54,63,64,65,66,   //normales
                     32,82:                                         //extras
                    if (info_prota.p_offsy < 14)
                        if (info_prota.vel_vert < 0) //TEST********
                            y3 += (14 - info_prota.p_offsy) * resolution3;
                            info_prota.p_offsy += (14 - info_prota.p_offsy);
                            p_libre = 0;
                        end
                        //podemos chocar con techo también si hemos saltado y nos desplazamos de lado
                        if ((info_prota.p_offsx - info_prota.vel_horiz) >= 4)
                            x3 += (4 - info_prota.p_offsx) * resolution3;
                            info_prota.p_offsx += (4 - info_prota.p_offsx);
                            //info_prota.vel_horiz = 0;
                        end
                    end
                end
                end //switch
            end //esquina de un techo
                
            if (info_prota.p_offsx > 11)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (info_prota.p_offsx - 11) * resolution3;
                        info_prota.p_offsx -= (info_prota.p_offsx - 11);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end //pared
            
            //esquina de un techo
            if (info_prota.p_offsx > 11)
                switch (p_dur[2][0])
                //no se puede subir
                case 1,2,3,5,13,14,15,16,51,52,53,55,63,64,65,66,   //normales
                     32,82:                                         //extras
                    if (info_prota.p_offsy < 14)
                        if (info_prota.vel_vert < 0)
                            y3 += (14 - info_prota.p_offsy) * resolution3;
                            info_prota.p_offsy += (14 - info_prota.p_offsy);
                            p_libre = 0;
                        end
                        if ((info_prota.p_offsx - info_prota.vel_horiz) <= 11)
                            x3 -= (info_prota.p_offsx - 11) * resolution3;
                            info_prota.p_offsx -= (info_prota.p_offsx - 11);
                            //info_prota.vel_horiz = 0;
                        end
                    end
                end
                end //switch
            end
            //p_libre=1;
            
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (p_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                 
                if (info_prota.p_offsy < 14)
                    y3 += (14 - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
                
            end //techo liso
            //techo diagonal, parte baja a la derecha
            case 4,54:
                if (info_prota.p_offsy < (info_prota.p_offsx - 2))
                    y3 += (info_prota.p_offsx - 2 - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte baja a la derecha
            //techo diagonal, parte baja a la izquierda
            case 5,55:
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - info_prota.p_offsx - 2))
                    y3 += (id_tscroll.tmapa[0].alto_tile - info_prota.p_offsx - 2 - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte baja a la izquierda
            end //switch techo
        end //casilla libre
        
        //rampa, parte alta a la izquierda
        case 2,52,                  //normales
             26,76:                 //extras
            
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < 4)
                switch (p_dur[0][0])    //miramos el superior
                //no se puede pasar (incluye medias rampas, para pasarlas tendríamos que estar en otro tile)
                case 1,3,4,14,15,16,51,53,54,64,65,66,          //normales
                     34,84:                                     //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
            end
            if (info_prota.p_offsx > 11)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (info_prota.p_offsx - 11) * resolution3;
                        info_prota.p_offsx -= (info_prota.p_offsx - 11);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            p_libre = 1;
            
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (p_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //la distancia es menor hacia la izquierda, apenas podemos avanzar
                if (info_prota.p_offsx < 13)
                    x3 += (13 - info_prota.p_offsx) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < 14)
                    y3 += (14 - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos estar a todo lo ancho del tile, pues la distancia es constante: un tile de altura
                if (info_prota.p_offsy < (info_prota.p_offsx - 1))
                    y3 += ((info_prota.p_offsx - 1) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (info_prota.p_offsx < ((id_tscroll.tmapa[0].ancho_tile / 2) - 2))
                    x3 += (((id_tscroll.tmapa[0].ancho_tile / 2) - 2) - info_prota.p_offsx) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (info_prota.p_offsy >= info_prota.p_offsx)
            
                y3 += (info_prota.p_offsx - info_prota.p_offsy) * resolution3;
                if (info_prota.estado == 3) info_prota.estado = 0; end
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                //info_prota.vel_vert = abs(info_prota.vel_horiz) + cte_prota_acelerac;
            end
            
        end //está en rampa, parte alta a la izquierda
        
        //rampa, parte alta a la derecha
        case 3,53,                  //normales
             27,77:                 //extras
             
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < 4)
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (4 - info_prota.p_offsx) * resolution3;
                        info_prota.p_offsx += (4 - info_prota.p_offsx);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            if (info_prota.p_offsx > 11)
                switch (p_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,              //normales
                     33,83:                                         //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
            end
            p_libre = 1;
            
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (p_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //la distancia es menor hacia la derecha, apenas podemos avanzar
                if (info_prota.p_offsx > 1)
                    x3 -= (info_prota.p_offsx - 1) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < 14)
                    y3 += (15 - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (info_prota.p_offsx > ((id_tscroll.tmapa[0].ancho_tile / 2) + 2))
                    x3 -= (info_prota.p_offsx - ((id_tscroll.tmapa[0].ancho_tile / 2) + 2)) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < (info_prota.p_offsx - 1))
                    y3 += ((info_prota.p_offsx - 1) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //podemos estar a todo lo ancho del tile, pues la distancia es constante: un tile de altura
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (info_prota.p_offsy >= (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                y3 += (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx - info_prota.p_offsy) * resolution3;
                if (info_prota.estado == 3) info_prota.estado = 0; end
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                //info_prota.vel_vert = abs(info_prota.vel_horiz) + cte_prota_acelerac;
            end
            
        end //está en rampa, parte alta a la derecha
        
        //media rampa baja, parte alta a la izquierda
        case 13,28,             //normales
             63,78:             //extras
             
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < 4)
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch tile lateral
                
                //miramos el tile superior
                switch (p_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,61,63,64,65,66,     //normales
                     34,84:                             //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            if (info_prota.p_offsx > 11)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (info_prota.p_offsx - 11) * resolution3;
                        info_prota.p_offsx -= (info_prota.p_offsx - 11);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            p_libre = 1;
             
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (p_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //la distancia es menor hacia la izquierda, apenas podemos avanzar
                if (info_prota.p_offsx < 12)
                    x3 += (12 - info_prota.p_offsx) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < 14)
                    y3 += (15 - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos estar a todo lo ancho del tile, pues la distancia es casi constante: un tile de altura
                if (info_prota.p_offsy < (info_prota.p_offsx - 1))
                    y3 += ((info_prota.p_offsx - 1) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (info_prota.p_offsx < ((id_tscroll.tmapa[0].ancho_tile / 2) - 4))
                    x3 += (((id_tscroll.tmapa[0].ancho_tile / 2) - 4) - info_prota.p_offsx) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (info_prota.p_offsy >= (((id_tscroll.tmapa[0].alto_tile / 2) - 1) + (info_prota.p_offsx / 2)))
                y3 += ((((id_tscroll.tmapa[0].alto_tile / 2) - 1) + (info_prota.p_offsx / 2)) - info_prota.p_offsy) *
                      resolution3;
                if (info_prota.estado == 3) info_prota.estado = 0; end
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                //info_prota.vel_vert = (abs(info_prota.vel_horiz) + cte_prota_acelerac) / 2;
            end
            
        end //media rampa baja, parte alta a la izquierda
        
        //media rampa baja, parte alta a la derecha
        case 15,65,                 //normales
             30,80:                 //extras
            
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < 4)
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (4 - info_prota.p_offsx) * resolution3;
                        info_prota.p_offsx += (4 - info_prota.p_offsx);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            if (info_prota.p_offsx > 11)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el techo superior
                switch (p_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,  //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            p_libre = 1;
            
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (p_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //la distancia es menor hacia la derecha, apenas podemos avanzar
                if (info_prota.p_offsx > 3)
                    x3 -= (info_prota.p_offsx - 3) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < 14)
                    y3 += (15 - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (info_prota.p_offsx > ((id_tscroll.tmapa[0].ancho_tile / 2) + 4))
                    x3 -= (info_prota.p_offsx - ((id_tscroll.tmapa[0].ancho_tile / 2) + 4)) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < (info_prota.p_offsx - 1))
                    y3 += ((info_prota.p_offsx - 1) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //podemos estar a todo lo ancho del tile, pues la distancia es constante: un tile de altura
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (info_prota.p_offsy >= ((id_tscroll.tmapa[0].alto_tile - 1) - (info_prota.p_offsx / 2)))
                y3 += (((id_tscroll.tmapa[0].alto_tile - 1) - (info_prota.p_offsx / 2)) - info_prota.p_offsy) *
						resolution3;
                if (info_prota.estado == 3) info_prota.estado = 0; end
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                //info_prota.vel_vert = (abs(info_prota.vel_horiz) + cte_prota_acelerac) / 2;
            end
            
        end //está en media rampa baja, parte alta a la derecha
        
        //media rampa alta, parte alta a la izquierda
        case 14,64,                         //normales
             29,79:                         //extras
             
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < 4)
                switch (p_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,51,53,54,64,65,66,              //normales
                     34,84:                                         //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
            end
            if (info_prota.p_offsx > 11)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el tile superior
                switch (p_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,  //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            p_libre = 1;
             
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (p_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //imposible estar aqui, lo empujamos fuera
                if (info_prota.p_offsx < 15)
                    x3 += (15 - info_prota.p_offsx) * resolution3;
                    info_prota.vel_horiz = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //dificil cálculo. Se puede estar hasta poco más allá de la mitad, la distancia va 
                //desde un tile hasta medio tile
                if (info_prota.p_offsx > 4)
                    x3 -= (info_prota.p_offsx - 4) * resolution3;
                    p_libre = 0;
                end
                if (info_prota.p_offsy < (info_prota.p_offsx - 1))
                    y3 += ((info_prota.p_offsx - 1) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //la distancia va desde cero hasta tile y medio
                if (info_prota.p_offsx < 11)
                    x3 += (11 - info_prota.p_offsx) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (info_prota.p_offsy >= (info_prota.p_offsx / 2))
                y3 += ((info_prota.p_offsx / 2) - info_prota.p_offsy) * resolution3;
                if (info_prota.estado == 3) info_prota.estado = 0; end
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                //info_prota.vel_vert = (abs(info_prota.vel_horiz) + cte_prota_acelerac) / 2;
            end
            
        end //media rampa alta, parte alta a la izquierda
        
        //media rampa alta, parte alta a la derecha
        case 16,66,                         //normales
             31,81:                         //extras
             
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < 4)
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el tile superior
                switch (p_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,51,53,54,64,65,     //normales
                     34,84:                             //extras
                    x3 += (4 - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (4 - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            if (info_prota.p_offsx > 11)
                switch (p_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,              //normales
                     33,83:                                         //extras
                    x3 -= (info_prota.p_offsx - 11) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - 11);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                end //switch
            end
            p_libre = 1;
             
            //según el tipo de techo que tengamos, haremos una cosa u otra
            switch (p_dur[1][0])
            //techo liso
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,
                 32,82:
                //imposible estar aqui, lo empujamos fuera
                if (info_prota.p_offsx >= 0)
                    x3 -= (info_prota.p_offsx + 1) * resolution3;
                    info_prota.vel_horiz = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //la distancia va desde tile y medio hasta cero
                if (info_prota.p_offsx > 5)
                    x3 -= (info_prota.p_offsx - 5) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                
                if (info_prota.p_offsy < (info_prota.p_offsx - 1))
                    y3 += ((info_prota.p_offsx - 1) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte derecha abajo
            //techo diagonal, parte izquierda abajo
            case 5,55:
                //dificil cálculo. Se puede estar hasta poco más allá de la mitad, la distancia va 
                //desde un medio tile hasta un tile
                if (info_prota.p_offsx < 13)
                    x3 += (13 - info_prota.p_offsx) * resolution3;
                    p_libre = 0;
                end
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx) - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (info_prota.p_offsy >= ((id_tscroll.tmapa[0].alto_tile / 2) - (info_prota.p_offsx / 2)))
                y3 += (((id_tscroll.tmapa[0].alto_tile / 2) - (info_prota.p_offsx / 2)) - info_prota.p_offsy) *
						resolution3;
                if (info_prota.estado == 3) info_prota.estado = 0; end
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                //info_prota.vel_vert = (abs(info_prota.vel_horiz) + cte_prota_acelerac) / 2;
            end
        end //media rampa alta, parte alta a la izquierda
        
        //techo, parte baja a la derecha
        case 4,54:
            //si nos movemos lateralmente chocaremos con el techo, no debemos poder avanzar
            if ((info_prota.vel_horiz > 0) && (info_prota.p_offsx > 2))
                x3 -= (info_prota.p_offsx - 2) * resolution3;
                info_prota.p_offsx -= (info_prota.p_offsx - 2);
                if (info_prota.vel_vert < 0)
                    info_prota.vel_vert = 0;
                    info_prota.estado = 3;
                    info_prota.p_mover_v = 0;
                end
            end
            //da igual la dirección en la que nos movamos, no podemos atravesar el techo
            if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile + info_prota.p_offsx - 3))
                y3 += ((id_tscroll.tmapa[0].alto_tile + info_prota.p_offsx - 3) - info_prota.p_offsy) * resolution3;
                p_libre = 0;
            end
        end //techo parte baja a la derecha
        
        //techo, parte baja a la izquierda
        case 5,55:
            //si nos movemos lateralmente chocaremos con el techo, no debemos poder avanzar
            if ((info_prota.vel_horiz < 0) && (info_prota.p_offsx < 14))
                x3 += (14 - info_prota.p_offsx) * resolution3;
                info_prota.p_offsx += (14 - info_prota.p_offsx);
                if (info_prota.vel_vert < 0)
                    info_prota.vel_vert = 0;
                    info_prota.estado = 3;
                    info_prota.p_mover_v = 0;
                end
            end
            //da igual la dirección en la que nos movamos, no podemos atravesar el techo
            if (info_prota.p_offsy < ((2 * id_tscroll.tmapa[0].alto_tile) - 3 - info_prota.p_offsx))
                y3 += (((2 * id_tscroll.tmapa[0].alto_tile) - 3 - info_prota.p_offsx) - info_prota.p_offsy) *
						resolution3;
                p_libre = 0;
            end
        end //techo parte baja a la izquierda
        
        end //switch propio tile