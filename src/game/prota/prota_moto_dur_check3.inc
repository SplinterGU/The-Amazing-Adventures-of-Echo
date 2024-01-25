		//movimientos verticales
        if (p_dir == 2)    //movimiento hacia abajo
            switch (p_dur[1][2])
            //no se puede
            case 1,4,5,25,51,54,55,75,
                 105:                       //especial (extra) ********** CAMBIAR ********************************
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                y3 += (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsy) * resolution3;
                if (info_prota.estado == 3) info_prota.estado = 0; end
            end //no se puede
            //si se puede
            default:
                //ATENCIÓN, puede que estemos tan abajo (por ejemplo, en el pico de una rampa) que parezca que
                //podemos bajar, así que, antes, hay que evitar esto
                switch (p_dur[1][1])
                //estamos en peligro de atravesar el suelo
                case 2,3,13,15,52,53,63,65:
                    p_libre = 0;
                end
                //caso especial: rampas transpasables, debemos asegurarnos que no vamos por debajo
                case 26,76:
                    if (info_prota.p_offsy < info_prota.p_offsx)
                        p_libre = 0;
                    else
                        p_libre = 1;
                    end
                end
                case 27,77:
                    if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                        p_libre = 0;
                    else
                        p_libre = 1;
                    end
                end
                case 28,78:
                    if (info_prota.p_offsy < ((id_tscroll.tmapa[0].alto_tile / 2) - 1 + (info_prota.p_offsx / 2)) )
                        p_libre = 0;
                    else
                        p_libre = 1;
                    end
                end
                case 29,79:
                    if (info_prota.p_offsy < (info_prota.p_offsx / 2) )
                        p_libre = 0;
                    else
                        p_libre = 1;
                    end
                end
                case 30,80:
                    if (info_prota.p_offsy < ((id_tscroll.tmapa[0].alto_tile - 1) -
                        ((id_tscroll.tmapa[0].alto_tile / 2) - 1 + (info_prota.p_offsx / 2))) )
                        p_libre = 0;
                    else
                        p_libre = 1;
                    end
                end
                case 31,81:
                    if (info_prota.p_offsy < ((id_tscroll.tmapa[0].alto_tile - 1) - (info_prota.p_offsx / 2)) )
                        p_libre = 0;
                    else
                        p_libre = 1;
                    end
                end
                //no hay peligro
                default:
                    p_libre = 1; 
                end
                end
                
                //ahora hay que mirar que no estemos pisando un borde de las casillas diagonales bajas
                if (p_libre)
                    //pegado a la izquierda
                    if (info_prota.p_offsx < 4)
                        switch (p_dur[0][2])
                        case 1,3,4,5,16,25,51,53,54,55,66,75,           //normales
                             27,31,77,81:                               //extras
                            p_libre = 0;
                        end
                        end //switch
                    end
                    //pegado a la derecha
                    if (info_prota.p_offsx > 11)
                        switch (p_dur[2][2])
                        case 1,2,4,5,14,25,51,52,54,55,64,75,           //normales
                             26,29,76,79:                               //extras
                            p_libre = 0;
                        end
                        end //switch
                    end
                end
                
                //y actuamos en consecuencia
                if (p_libre)
                    info_prota.p_mover_v--;
                    info_prota.estado = 3;
                    //actualizamos casilla actual
                    p_dur[0][0] = p_dur[0][1];
                    p_dur[1][0] = p_dur[1][1];
                    p_dur[2][0] = p_dur[2][1];
                    p_dur[0][1] = p_dur[0][2];
                    p_dur[1][1] = p_dur[1][2];
                    p_dur[2][1] = p_dur[2][2];
                    p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-1,info_prota.p_tiley+2,0);
                    p_dur[1][2] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley+2,0);
                    p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+1,info_prota.p_tiley+2,0);
                    //limitamos movimientos laterales si el nuevo techo no nos deja avanzar
                    switch (p_dur[0][0])
                    case 1,2,3,4,13,14,15,16,51,52,53,54,63,64,65,66,   //normales
                         34,84:                                         //extras
                        if ((info_prota.vel_horiz < 0) && ((info_prota.p_offsx + info_prota.vel_horiz) < 4))
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (4 - info_prota.p_offsx) * resolution3;
                        end
                    end
                    end //switch
                    switch (p_dur[2][0])
                    case 1,2,3,5,13,14,15,16,51,52,53,55,63,64,65,66,   //normales
                         33,83:                                         //extras
                        if ((info_prota.vel_horiz > 0) && ((info_prota.p_offsx + info_prota.vel_horiz) > 11))
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (11 - info_prota.p_offsx) * resolution3;
                        end
                    end
                    end //switch
                else
                    info_prota.p_mover_v = 0;
                    info_prota.estado = 0;
                    info_prota.vel_vert = 0;
                    y3 += (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsy) * resolution3;
                end
                
            end //si se puede
            end //switch mirar tile abajo
        end //movimiento hacia abajo
        
        if (p_dir == 8)       //movimiento hacia arriba
            //comprobamos la casilla superior
            switch (p_dur[1][0])
            //no se puede
            case 1,2,3,13,14,15,16,51,52,53,63,64,65,66,        //normales
                 32,82:                                         //extras
                p_libre = 0;
            end //no se puede
            //se puede
            default:
                p_libre = 1;
                //comprobando no chocarse con los bordes de las casillas diagonales
                if (info_prota.p_offsx < 4)
                    switch (p_dur[0][0])
                    case 1,2,3,4,13,14,15,16,51,52,53,54,63,64,65,66,   //normales
                         32,82:                                         //extras
                        p_libre = 0;
                    end
                    end //switch
                end //pegado a la izquierda
                if (info_prota.p_offsx > 11)
                    switch (p_dur[2][0])
                    case 1,2,3,5,13,14,15,16,51,52,53,55,63,64,65,66,   //normales
                         32,82:                                         //extras
                        p_libre = 0;
                    end
                    end //switch
                end //pegado a la derecha
            end
            end //switch mirar tile arriba
            
            //y actuamos en consecuencia
            if (p_libre)
                info_prota.p_mover_v++;
                //actualizamos casilla actual
                p_dur[0][2] = p_dur[0][1];
                p_dur[1][2] = p_dur[1][1];
                p_dur[2][2] = p_dur[2][1];
                p_dur[0][1] = p_dur[0][0];
                p_dur[1][1] = p_dur[1][0];
                p_dur[2][1] = p_dur[2][0];
                p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-1,info_prota.p_tiley-2,0);
                p_dur[1][0] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley-2,0);
                p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+1,info_prota.p_tiley-2,0);
            else
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                y3 -= info_prota.p_offsy * resolution3;
            end
            
        end //movimiento hacia arriba
        