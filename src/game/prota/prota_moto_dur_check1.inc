		//Comprobamos si hay cambio
        if (info_prota.vel_horiz > 0)  //movimiento a la derecha
        
            if (p_dir == 3) //movim diagonal hacia abajo          //ARREGLAR: SE COME LAS ESQUINAS (DEBE DESPLAZARSE
                //say("p_dir = 3");
                switch (p_dur[2][2])                            //MÁS ANTES DE CAER
                //casos en los que no se puede descender
                case 1,4,5,25,51,54,55,75,  //normales
                     105:                   //especiales (extra)
                    p_dir = 6;
                    //info_prota.vel_vert = (15 - info_prota.p_offsy) * resolution3;
                end
                //casos en los que SI
                default:
                    //comprobamos si el que hay a la derecha nos deja avanzar
                    switch (p_dur[2][1])
                    //casos en los que si se puede avanzar
                    case 0,4,25,50,54,75,                   //normales
                         26,28,29,32,34,76,78,79,82,84,     //extras
                         100,104,105,                       //especiales (extra)
                         150..255:                          //otras
                        p_libre = 1;
                    end
                    //casos en los que, aunque libre, e avanza en otra dir
                    case 3,15,53,65,                        //normales
                         27,30,77,80:                       //extras
                        p_libre = 2;
                    end
                    //casos en que no
                    default: p_libre = 0; end
                    end //switch
                    
                    //ahora, p_libre indica
                    //0: no se puede avanzar.
                    //1: se puede avanzar.
                    //2: hay una rampa a la misma altura
                    switch (p_libre)
                    //no se puede avanzar
                    case 0:
                        info_prota.p_mover_h = 0;
                        info_prota.vel_horiz = 0;
                        x3 += (11 - info_prota.p_offsx) * resolution3;
                        p_dir = 2;
                    end
                    //si se puede
                    case 1:
                        info_prota.p_mover_v--;
                        info_prota.p_mover_h--;
                        //si el tile diagonal esta vacio podemos caer*******************************
                        switch (p_dur[2][2])
                        case 0,3,13,15,16,50,53,63,65,66,               //normales
                             27,28,30,31,32,33,34,77,78,80,81,82,83,84, //extras
                             100,104,                                   //especiales (extra)
                             150..255:                                  //otras
                            
                            //todo listo para caer... pero no si estamos sobre el borde de una caida
                            switch (p_dur[1][2])
                            case 1,3,4,5,16,25,51,53,54,55,66,75,       //normales
                                 27,31,77,81,                           //extras
                                 105:                                   //especiales (extra)
                                
                                //say("estamos a "+itoa((info_prota.p_offsx*resolution3)+info_prota.vel_horiz));
                                if (((info_prota.p_offsx * resolution3) + info_prota.vel_horiz) <= 
                                    ((15 + 4) * resolution3))
                                    
                                    //no podemos caer aun
                                    p_dir = 6;
                                else
                                    //si podemos caer
                                    info_prota.estado = 3;
                                    //actualizamos los tiles
                                    p_dur[0][0] = p_dur[1][1];
                                    p_dur[0][1] = p_dur[1][2];
                                    p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley+2,0);
                                    p_dur[1][0] = p_dur[2][1];
                                    p_dur[1][1] = p_dur[2][2];
                                    p_dur[1][2] = obtener_tile(&durezas,info_prota.p_tilex+1,info_prota.p_tiley+2,0);
                                    p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                                    p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                                    p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+2,0);
                                end //if al borde
                            end
                            default:
                                info_prota.estado = 3;
                                //actualizamos los tiles
                                p_dur[0][0] = p_dur[1][1];
                                p_dur[0][1] = p_dur[1][2];
                                p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley+2,0);
                                p_dur[1][0] = p_dur[2][1];
                                p_dur[1][1] = p_dur[2][2];
                                p_dur[1][2] = obtener_tile(&durezas,info_prota.p_tilex+1,info_prota.p_tiley+2,0);
                                p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                                p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                                p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+2,0);
                            end
                            end //switch suelo
                        end
                        case 2,52:
                             //rampa: nos movemos y perdemos toda la velocidad, con esto se acaba el movimiento
                             //esto es mejor, ponemos una velocidad de la gravedad superior para traspasar la rampa, y luego nos recolocaremos
                             if (info_prota.estado != 2)
                                /*vel_vert = (info_prota.p_offsx * resolution3) + info_prota.vel_horiz -
                                             (id_tscroll.tmapa[0].ancho_tile * resolution3);*/
                                info_prota.vel_vert = info_prota.vel_horiz;
                             end
                             //actualizamos los tiles
                            p_dur[0][0] = p_dur[1][1];
                            p_dur[0][1] = p_dur[1][2];
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley+2,0);
                            p_dur[1][0] = p_dur[2][1];
                            p_dur[1][1] = p_dur[2][2];
                            p_dur[1][2] = obtener_tile(&durezas,info_prota.p_tilex+1,info_prota.p_tiley+2,0);
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                            p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+2,0);
                        end
                        end
                        //actualizamos casilla actual
                        //lo hemos hecho antes, hay un caso especial que contemplar
                        
                    end
                    //hay una rampa
                    case 2:
                        p_dir = 6;
                    end
                    end //switch
                end
                end //switch
            end //movimiento diagonal******
            
            if (p_dir == 6)   //movimiento lateral
                //say("p_dir = 6");
                
                switch (p_dur[2][1])
                //si permite el paso normal
                case 0,3,4,15,25,50,53,54,65,75,    //normales
                     26..32,34,76..82,84,           //extras
                     100,104,105,                   //especiales (extras)
                     150..255:                      //otras
                    //comprobamos la casilla actual, podríamos estar en una rampa ascendente y dejarnos en
                    //un tile superior en lugar del tile de al lado
                    
                    switch (p_dur[1][1])
                    
                    //estamos en rampa o media rampa superior
                    case 3,16,53,66,                //normales
                         27,31,77,81:               //extras
                        //comprobamos el techo derecho. Aqui pueden pasar tres cosas que almacenaremos en p_libre
                        //0: No se permite el paso
                        //1: Se permite el paso, nos movemos lateralmente
                        //2: Se permite el paso PERO un tile nos obliga a permanecer en el superior
                        switch (p_dur[2][0])
                        //parte superior libre
                        case 0,25,50,75,                            //normales
                             26,28,29,31,32,34,76,78,79,81,82,84,   //extras
                             100,104,105,                           //especiales (extras)
                             150..255:                              //otras
                            p_libre = 1;
                        end
                        //caso especial, hay una rampa que obliga a ir diagonal
                        case 3,15,53,65,            //normales
                             27,30,77,80:           //extras
                            p_libre = 2;
                        end
                        //parte superior ocupada
                        default:
                            p_libre = 0;
                        end
                        end //switch comprobando sig techo
                        
                        //caso especial: la siguiente casilla permite atravesarse en todas direcciones menos
                        //               hacia abajo
                        switch (p_dur[2][1])
                        case 25,75,105:             //extras
                            p_libre = 2;
                        end
                        end //switch, caso especial tile derecho
                        //caso especial: no nos hemos movido lo suficiente a la derecha para caernos, nos
                        //               sujeta la esquina del gráfico.
                        if ( ((x3 + info_prota.vel_horiz) % (id_tscroll.tmapa[0].ancho_tile * resolution3)) < 
                             (4 * resolution3) )
                            p_libre = 2;
                        end
                        
                        //Y ACTUAMOS SEGUN ESTE MOVIMIENTO
                        switch (p_libre)
                        //no se puede avanzar
                        case 0:
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (11 - info_prota.p_offsx) * resolution3;
                        end
                        //si se puede avanzar
                        case 1:
                            info_prota.p_mover_h--;
         //prueba rara
                            info_prota.vel_vert -= ((15 - info_prota.p_offsx) * resolution3); //quitamos tanta velocidad 
                                                                                        //como pixels por subir
                            info_prota.estado = 3;
                            //actualizamos casilla actual
                            p_dur[0][0] = p_dur[1][0];
                            p_dur[0][1] = p_dur[1][1];
                            p_dur[0][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[2][0];
                            p_dur[1][1] = p_dur[2][1];
                            p_dur[1][2] = p_dur[2][2];
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-1,0);
                            p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                        end
                        //se avanza, pero se sube al mismo tiempo
                        case 2:
                            info_prota.p_mover_h--;
                            info_prota.p_mover_v--;
         //prueba rara
                            info_prota.vel_vert -= (info_prota.p_offsy * resolution3) + 10;
                            //actualizamos casilla actual
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley-2,0);
                            p_dur[0][1] = p_dur[1][0];
                            p_dur[0][2] = p_dur[1][1];
                            p_dur[1][0] = obtener_tile(&durezas,info_prota.p_tilex+1,info_prota.p_tiley-2,0);
                            p_dur[1][1] = p_dur[2][0];
                            p_dur[1][2] = p_dur[2][1];
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-2,0);
                            p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-1,0);
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                            //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                            switch (p_dur[1][1])
                            case 26,28,29,31,76,78,79,81:           //extras
                                p_dur[1][1] = 0;
                            end
                            end //switch
                        end
                        end //switch dirección final de movimiento
                        
                    end //case rampa o media rampa superior
                    
                    //estamos en media rampa inferior
                    case 15,30,65,80:
                        //comprobamos si el techo nos deja avanzar
                        switch (p_dur[2][0])
                        //Si se puede
                        case 0,25,50,75,                    //normal (he eliminado las rampas de techo)
                             26..32,34,76..82,84,           //extras
                             100,104,105,                   //especiales (extras)
                             150..255:                      //otras
                            p_libre = 1;
                        end
                        default:
                            p_libre = 0;
                        end
                        end //switch comprobando sig techo
                        
                        //actuamos en consecuencia
                        switch (p_libre)
                        //no se puede
                        case 0:
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (11 - info_prota.p_offsx) * resolution3;
                            //no hay que actualizar casilla actual
                        end
                        //si se puede
                        case 1:
                            info_prota.p_mover_h--;
         //prueba rara
                            info_prota.vel_vert -= (info_prota.p_offsy - (id_tscroll.tmapa[0].ancho_tile / 2));
                            //actualizamos casilla actual
                            p_dur[0][0] = p_dur[1][0];
                            p_dur[0][1] = p_dur[1][1];
                            p_dur[0][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[2][0];
                            p_dur[1][1] = p_dur[2][1];
                            p_dur[1][2] = p_dur[2][2];
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-1,0);
                            p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                            //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                            switch (p_dur[1][1])
                            case 26,29,76,79:           //extras
                                p_dur[1][1] = 0;
                            end
                            end //switch
                        end
                        end
                    end //case media rampa inferior
                    
                    //estamos en media rampa superior descendente
                    case 14,29,64,79:
                        //comprobamos si el techo nos deja avanzar
                        switch (p_dur[2][0])
                        //Si se puede
                        case 0,25,50,75,                    //normal (he eliminado las rampas de techo)
                             26..32,34,76..82,84,           //extras
                             100,104,105,                   //especiales (extras)
                             150..255:                      //otras
                            p_libre = 1;
                        end
                        default:
                            p_libre = 0;
                        end
                        end //switch comprobando sig techo
                        
                        //actuamos en consecuencia
                        switch (p_libre)
                        //no se puede
                        case 0:
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (11 - info_prota.p_offsx) * resolution3;
                            //no hay que actualizar casilla actual
                        end
                        //si se puede
                        case 1:
                            info_prota.p_mover_h--;
                            //actualizamos casilla actual
                            p_dur[0][0] = p_dur[1][0];
                            p_dur[0][1] = p_dur[1][1];
                            p_dur[0][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[2][0];
                            p_dur[1][1] = p_dur[2][1];
                            p_dur[1][2] = p_dur[2][2];
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-1,0);
                            p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                            //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                            switch (p_dur[1][1])
                            case 26,29,76,79:           //extras
                                p_dur[1][1] = 0;
                            end
                            end //switch
                        end
                        end
                    end //case media rampa superior descendente
                    
                    //normal, sin rampa
                    default:
                        //ya sabemos que la sig casilla está libre
                        //es posible que por culpa de la altura, el techo no nos deje pasar
                        switch (p_dur[2][0])
                        case 1,2,3,5,13,14,15,16,51,52,53,55,63,64,65,66,   //normales
                             33,83:                                         //extras
                            if (info_prota.p_offsy < 14)
                                p_libre = 0;
                            else
                                p_libre = 1;
                            end
                        end
                        default: p_libre = 1; end
                        end //switch
                        
                        //actuamos en consecuencia
                        if (p_libre)
                            info_prota.p_mover_h--;
                            //venimos de caer en diagonal, hay que frenar la caida
                            if (p_dir_ini == 3)
                                info_prota.p_mover_v = 0;
                                info_prota.vel_vert = 0;
                                info_prota.estado = 0;
                            end
                            //actualizamos casilla actual
                            p_dur[0][0] = p_dur[1][0];
                            p_dur[0][1] = p_dur[1][1];
                            p_dur[0][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[2][0];
                            p_dur[1][1] = p_dur[2][1];
                            p_dur[1][2] = p_dur[2][2];
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-1,0);
                            p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                            //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                            switch (p_dur[1][1])
                            case 26,28,29,31,76,78,79,81:           //extras
                                p_dur[1][1] = 0;
                            end
                            end //switch
                        else
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (12 - info_prota.p_offsx) * resolution3;
                            //no hay que actualizar casilla actual
                        end
                    end //case sin rampa
                    
                    end //switch estamos en rampa
                end //casilla lateral libre
                
                //no se permite el paso
                default:
                    //comprobamos si estamos en casilla con rampa
                    switch (p_dur[1][1])
                    
                    //rampa y media rampa superior
                    case 3,16,53,66,                //normales
                         27,31,77,81:               //extras
                        info_prota.p_mover_v = 0;
                        info_prota.estado = 0;
                        //comprobamos la casilla superior para ver si podemos avanzar en diagonal
         //prueba rara
                        info_prota.vel_vert -= (info_prota.p_offsy * resolution3) + 20;
                        //info_prota.vel_vert = 0;
                        //y3 -= (info_prota.p_offsy + 1) * resolution3;
                        //info_prota.offsy = -1;
                        p_dir = 9;
                    end //rampa y media rampa superior
                    
                    //media rampa inferior y media rampa superior en descenso
                    case 15,30,65,80,14,29,64,79:
                        //caso especial, pues se podria avanzar si la sig casilla
                        //fuera media rampa superior normal (las traspasables se
                        //contemplaron antes)
                        switch (p_dur[2][1])
                        case 16,66:
                            info_prota.p_mover_h--;
         //prueba rara
                            info_prota.vel_vert = -(info_prota.vel_horiz - (info_prota.vel_horiz % 2)) / 2;
                            //actualizamos casilla actual
                            p_dur[0][0] = p_dur[1][0];
                            p_dur[0][1] = p_dur[1][1];
                            p_dur[0][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[2][0];
                            p_dur[1][1] = p_dur[2][1];
                            p_dur[1][2] = p_dur[2][2];
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-1,0);
                            p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                        end
                        case 13,63:
                            info_prota.p_mover_h--;
         //prueba rara
                            info_prota.vel_vert += (info_prota.vel_horiz / 2);
                            //actualizamos casilla actual
                            p_dur[0][0] = p_dur[1][0];
                            p_dur[0][1] = p_dur[1][1];
                            p_dur[0][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[2][0];
                            p_dur[1][1] = p_dur[2][1];
                            p_dur[1][2] = p_dur[2][2];
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-1,0);
                            p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley+1,0);
                        end
                        default:    //no podemos pasar
                            info_prota.p_mover_h--;
                            info_prota.vel_horiz = 0;
                            x3 += (11 - info_prota.p_offsx) * resolution3;
                            if (p_dir_ini == 3)
                                p_dir = 2;
                            end
                            //no hay que actualizar casilla actual
                        end
                        end //switch
                    end //media rampa inferior y media rampa superior en descenso
                    
                    //sin rampa
                    default:
                        info_prota.p_mover_h = 0;
                        info_prota.vel_horiz = 0;
                        x3 += (11 - info_prota.p_offsx) * resolution3;
                        //no hay que actualizar casilla actual
                        //atencion, si ibamos en diagonal hacia abajo, es posible que aun nos podamos
                        //mover hacia abajo
                        if (p_dir_ini == 3) p_dir = 2; end
                    end //sin rampa
                    
                    end //switch estamos en rampa
                end //casilla lateral obstruida
                
                end //switch dureza lateral
            end //movimiento lateral*******
            
            if (p_dir == 9)
                //say("p_dir = 9");
                //comprobamos si la casilla está libre
                switch (p_dur[2][0])
                //casilla libre
                case 0,3,15,25,50,53,65,75,         //normal
                     26..32,34,76..82,84,           //extras
                     100,104,105,                   //especiales (extras)
                     150..255:                      //otras
                    p_libre = 1;
                end
                //casilla ocupada
                default:
                    p_libre = 0;
                end
                end //switch dureza diagonal
                
                //say(itoa(info_prota.vel_vert));
                
                if (p_libre)
                    info_prota.p_mover_v++;
                    info_prota.p_mover_h--;
                    //actualizamos casilla actual
                    p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley-2,0);
                    p_dur[0][1] = p_dur[1][0];
                    p_dur[0][2] = p_dur[1][1];
                    p_dur[1][0] = obtener_tile(&durezas,info_prota.p_tilex+1,info_prota.p_tiley-2,0);
                    p_dur[1][1] = p_dur[2][0];
                    p_dur[1][2] = p_dur[2][1];
                    p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-2,0);
                    p_dur[2][1] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley-1,0);
                    p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex+2,info_prota.p_tiley  ,0);
                    //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                    switch (p_dur[1][1])
                    case 26,28,29,31,76,78,79,81:           //extras
                        p_dur[1][1] = 0;
                    end
                    end //switch
                else
                    info_prota.p_mover_h = 0;
                    info_prota.vel_horiz = 0;
                    x3 += (11 - info_prota.p_offsx) * resolution3;
                    //no hay que actualizar casilla actual
                    p_dir = 8;
                end
            end
        
        end //movimiento a la derecha
        