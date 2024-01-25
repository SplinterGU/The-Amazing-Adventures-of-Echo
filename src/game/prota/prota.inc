process prota (x2, y2)
private
    //posición
    int x3;             //temporal, añade resolución
    int y3;             //temporal, añade resolución
    
    int resolution3;    //define el tamaño de cada pixel (evitar decimales)
    
    //arma
    int mi_arma;
    double temp_x, temp_y;
	
	//interacción externa
	int ant_plataforma;
    
    //variables temporales
    int prota_tile_ant;
    int temp_desp;      //indica hasta donde se desplazará el personaje
    int p_libre;        //indica si se puede avanzar en esa dirección (comprobación de movimiento)
	int temp;
	
	int antx,anty;
begin
    priority = -99;

    /*
    write_var(0, 10, 10, 0, p_dur[0][0]);
    write_var(0, 10, 20, 0, p_dur[0][1]);
    write_var(0, 10, 30, 0, p_dur[0][2]);
    write_var(0, 30, 10, 0, p_dur[1][0]);
    write_var(0, 30, 20, 0, p_dur[1][1]);
    write_var(0, 30, 30, 0, p_dur[1][2]);
    write_var(0, 50, 10, 0, p_dur[2][0]);
    write_var(0, 50, 20, 0, p_dur[2][1]);
    write_var(0, 50, 30, 0, p_dur[2][2]);
    */

    /*
    write_var(0, 100, 10, 0, info_prota.vel_horiz);
    write_var(0, 100, 20, 0, info_prota.vel_vert);
    write_var(0, 100, 35, 0, p_dir);
    
    write_var(0, 150, 10, 0, info_prota.p_offsx);
    write_var(0, 150, 20, 0, info_prota.p_offsy);
    write_var(0, 150, 35, 0, info_prota.estado);
    
    write_var(0, 200, 10, 0, teclas[k_jump][2]);
    */
    
    //x3 = 100;
    //y3 = 1150;
    //id_tscroll.camera_x = 10;
    //id_tscroll.camera_y = 110;
    id_tscroll.camera_x = (x2 * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    id_tscroll.camera_y = (y2 * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    mi_arma = arma(id);
    
    info_prota.id_prota = id;
	info_prota.id_plataforma = -1;
	ant_plataforma = -1;
    //z = -100;
    z = 2;
    file = prota_file;
    resolution3 = 10;
    x3 = id_tscroll.camera_x * resolution3;
    y3 = id_tscroll.camera_y * resolution3;

    loop
        //esto es por si movemos al personaje externamente
        //x3 = x2;
        //y3 = y2;
        //say("frame");
		//Si una plataforma nos ha "atrapado" nos habrá recolocado, y tendremos que reajustar la posición
		if ((info_prota.id_plataforma != -1) && (ant_plataforma != info_prota.id_plataforma) && exists(info_prota.id_plataforma))
			say("¡¡PLATAFORMA!!");
			x3 = x2 * resolution3;
			y3 = y2 * resolution3;
			info_prota.estado = CTE_PROTA_ESTADO_PARADO;
			info_prota.vel_vert = 0;
			ant_plataforma = info_prota.id_plataforma;
			//y3 = (info_prota.id_plataforma.y2 - 1) * resolution3;
		end

		if ((info_prota.id_plataforma != -1) && (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO))
			info_prota.estado = CTE_PROTA_ESTADO_PARADO;
		end
		
		info_prota.x2_ant = x2;
		info_prota.y2_ant = y2;

		//Añadiendo velocidades externas al movimiento
		/*if (info_prota.ext_velx != 0)
			x3 += info_prota.ext_velx;
			info_prota.ext_velx = 0;
		end
		if (info_prota.ext_vely != 0)
			y3 += info_prota.ext_vely;
			info_prota.ext_vely = 0;
		end*/
		
        //localizamos la posición actual
        info_prota.p_tilex = (x3 / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        info_prota.p_tiley = (y3 / resolution3) / id_tscroll.tmapa[0].alto_tile;
        info_prota.p_offsx = (x3 / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        info_prota.p_offsy = (y3 / resolution3) % id_tscroll.tmapa[0].alto_tile;

        //leemos durezas de su alrededor
        p_dur[0][0] = obtener_tile(&durezas, info_prota.p_tilex - 1, info_prota.p_tiley - 1, 0);
        p_dur[1][0] = obtener_tile(&durezas, info_prota.p_tilex    , info_prota.p_tiley - 1, 0);
        p_dur[2][0] = obtener_tile(&durezas, info_prota.p_tilex + 1, info_prota.p_tiley - 1, 0);
        p_dur[0][1] = obtener_tile(&durezas, info_prota.p_tilex - 1, info_prota.p_tiley    , 0);
        p_dur[1][1] = obtener_tile(&durezas, info_prota.p_tilex    , info_prota.p_tiley    , 0);
        p_dur[2][1] = obtener_tile(&durezas, info_prota.p_tilex + 1, info_prota.p_tiley    , 0);
        p_dur[0][2] = obtener_tile(&durezas, info_prota.p_tilex - 1, info_prota.p_tiley + 1, 0);
        p_dur[1][2] = obtener_tile(&durezas, info_prota.p_tilex    , info_prota.p_tiley + 1, 0);
        p_dur[2][2] = obtener_tile(&durezas, info_prota.p_tilex + 1, info_prota.p_tiley + 1, 0);
        
        //Adecuación de velocidades a tipo de tile (normal o agua)
        switch (p_dur[1][1])
            case 50..99:
                var_prota_max_vel = CTE_PROTA_AGUA_MAX_VEL;
                var_prota_acelerac = CTE_PROTA_AGUA_ACELERAC;
                var_prota_salto = CTE_PROTA_AGUA_SALTO;
                var_prota_gravedad = CTE_PROTA_AGUA_GRAVEDAD;
                var_prota_max_gravedad = CTE_PROTA_AGUA_MAX_GRAVEDAD;
                if ((prota_tile_ant < 50) || (prota_tile_ant > 99))
                    //say("SPLASH");  //¿Por qué no entra aqui guardando en prota_tile_ant pdur[1][1]? *************
                    info_prota.vel_horiz = info_prota.vel_horiz / 2;
                    info_prota.vel_vert = info_prota.vel_vert / 2;
                end
            end
            default:
                var_prota_max_vel = CTE_PROTA_MAX_VEL;
                var_prota_acelerac = CTE_PROTA_ACELERAC;
                var_prota_salto = CTE_PROTA_SALTO;
                var_prota_gravedad = CTE_PROTA_GRAVEDAD;
                var_prota_max_gravedad = CTE_PROTA_MAX_GRAVEDAD;
            end
        end //switch
        
        //reconocimiento de teclas
        //movimiento lateral
        if (teclas[k_right][2] > 0)
            info_prota.vel_horiz += var_prota_acelerac;
            //if (info_prota.vel_horiz > var_prota_max_vel) info_prota.vel_horiz = var_prota_max_vel; end
            if (info_prota.vel_horiz > var_prota_max_vel) info_prota.vel_horiz -= var_prota_acelerac; end
        elsif (teclas[k_left][2] > 0)
            info_prota.vel_horiz -= var_prota_acelerac;
            //if (info_prota.vel_horiz < -var_prota_max_vel) info_prota.vel_horiz = -var_prota_max_vel; end
            if (info_prota.vel_horiz < -var_prota_max_vel) info_prota.vel_horiz += var_prota_acelerac; end
        else
            if (info_prota.vel_horiz > 0)
                if (info_prota.vel_horiz < var_prota_acelerac)
                    info_prota.vel_horiz = 0;
                else
                    info_prota.vel_horiz -= var_prota_acelerac;
                end
            elsif (info_prota.vel_horiz < 0)
                if (info_prota.vel_horiz > -var_prota_acelerac)
                    info_prota.vel_horiz = 0;
                else
                    info_prota.vel_horiz += var_prota_acelerac;
                end
            end
        end
        
			
        switch (info_prota.estado)
            case CTE_PROTA_ESTADO_PARADO, CTE_PROTA_ESTADO_ANDANDO:		//parado o andando
    			//OJO A LAS PLATAFORMAS. SACAR DE ELLAS AL SALTAR O AL APOYARSE SOBRE TILE SÓLIDO
                if (teclas[k_jump][2] == 1)       //si apretamos salto
                    info_prota.estado = CTE_PROTA_ESTADO_SALTANDO;
                    cont_salto = 0;
                    info_prota.vel_vert = -var_prota_salto;
    				
    				//Cancelamos estado en plataforma
    				info_prota.id_plataforma = -1;
    				ant_plataforma = -1;
                else                            //gravedad normal (quitar para debug)****************
    				if (info_prota.id_plataforma == -1)
    					info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
    					info_prota.vel_vert += var_prota_gravedad;
    				end
                end
            end
            case CTE_PROTA_ESTADO_SALTANDO:     //saltando
                if (teclas[k_jump][2] > 0)
                    cont_salto++;
                    if (cont_salto >= CTE_PROTA_MAX_SALTO)
                        info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
                        info_prota.vel_vert += var_prota_gravedad;
                        cont_salto = 0;
                    else
                        info_prota.vel_vert = -var_prota_salto;
                    end
                else
                    info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
                    info_prota.vel_vert += var_prota_gravedad;
                end
            end
            case CTE_PROTA_ESTADO_CAYENDO:     //cayendo
                info_prota.vel_vert += var_prota_gravedad;
                if (info_prota.vel_vert > var_prota_max_gravedad) info_prota.vel_vert = var_prota_max_gravedad; end
                //if (teclas[k_previous][2] > 0) info_prota.vel_vert = 0; info_prota.estado = 0; end
            end
        end //switch
		
		
		if (info_prota.ext_velx != 0)
			info_prota.vel_horiz += info_prota.ext_velx;
			//info_prota.ext_velx = 0;
		end
		if (info_prota.ext_vely != 0)
			info_prota.vel_vert += info_prota.ext_vely;
			//info_prota.ext_vely = 0;
		end
        
        //MOVIMIENTO ***********************************
        //Comprobamos cambio de tile
        /*p_dir = 5;
        temp_desp = (info_prota.p_offsx * resolution3) + var_vel;
        if (temp_desp > (id_tscroll.tmapa[0].ancho_tile * resolution3)) p_dir++; end
        if (temp_desp < 0) p_dir--; end
        temp_desp = (info_prota.p_offsy * resolution3) + info_prota.vel_vert;
        if (temp_desp > (id_tscroll.tmapa[0].alto_tile * resolution3)) p_dir -= 3; end
        if (temp_desp < 0) p_dir += 3; end*/
        //comprobamos si cambiamos de tile y en que direccion
        //***************************************************************
        info_prota.p_mover_h = 0;
		temp = (x3 + info_prota.vel_horiz) / (id_tscroll.tmapa[0].ancho_tile * resolution3);
        if (temp != info_prota.p_tilex)
           //comprobamos si pasamos a otro tile lateral y cuan lejos esta
           info_prota.p_mover_h = temp - info_prota.p_tilex;
        end
        //write(0, 630, 10, 2, p_mover_h);
        info_prota.p_mover_v = 0;
		temp = (y3 + info_prota.vel_vert) / (id_tscroll.tmapa[0].alto_tile * resolution3);
        if (temp != info_prota.p_tiley)
           //comprobamos si pasamos a otro tile vertical y cuan lejos esta
           info_prota.p_mover_v = temp - info_prota.p_tiley;
        end
		
         //miramos en que direccion cambiamos
        p_dir = 5;
        if (info_prota.p_mover_h > 0) p_dir++; end
        if (info_prota.p_mover_h < 0) p_dir--; end
        if (info_prota.p_mover_v > 0) p_dir -= 3; end      //hacia abajo
        if (info_prota.p_mover_v < 0) p_dir += 3; end      //hacia arriba
        p_dir_ini = p_dir;
		
        //OJO CON LA RAMPAS TRASPASABLES, PONER CASILLA A CERO SI ESTAMOS**********temporalmente disabled
        //EN EL SUELO
        /*if ((p_dur[1][1]==27 || p_dur[1][1]==77) &&
           (info_prota.p_rely>((id_tscroll.tmapa[0].alto_tile-1)*resolution3)-info_prota.p_relx))
           p_dur[1][1]=0;
        end
        if ((p_dur[1][1]==30 || p_dur[1][1]==80) &&
           (info_prota.p_rely>((id_tscroll.tmapa[0].alto_tile-1)*resolution3)-(info_prota.p_relx/2)))
           p_dur[1][1]=0;
        end
        if ((p_dur[1][3]==31 || p_dur[1][3]==81) &&
           (info_prota.p_rely>(((id_tscroll.tmapa[0].alto_tile/2)-1)*resolution3)-(info_prota.p_relx/2)))
           p_dur[1][1]=0;
        end
        if ((p_dur[1][1]==26 || p_dur[1][1]==76) && info_prota.p_rely>info_prota.p_relx)
           p_dur[1][1]=0;
        end
        if ((p_dur[1][1]==28 || p_dur[1][1]==78) &&
           ((info_prota.p_rely>((id_tscroll.tmapa[0].alto_tile/2)-1)*resolution3)+info_prota.p_relx/2))
           p_dur[1][1]=0;
        end
        if ((p_dur[1][1]==29 || p_dur[1][1]==79) && info_prota.p_rely>info_prota.p_relx/2)
           p_dur[1][1]=0;
        end*/
        
        //say("Estado antes: " + itoa(info_prota.estado));
        //Comprobamos si hay cambio
        
		//Movimiento a la derecha
		
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
                        x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
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
                                    ((15 + CTE_PROTA_MAX_AVANZAR_IZQUIERDA) * resolution3))
                                    
                                    //no podemos caer aun
                                    p_dir = 6;
                                else
                                    //si podemos caer
                                    info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
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
                                info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
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
                             //esto es mejor, ponemos una velocidad de la gravedad superior para traspasar la rampa,
                             //y luego nos recolocaremos
                             //say("   RAMPA: vel_horiz=" + info_prota.vel_horiz + "   vel_vert=" + info_prota.vel_vert);
                             if (info_prota.estado != CTE_PROTA_ESTADO_SALTANDO)
                                /*vel_vert = (info_prota.p_offsx * resolution3) + info_prota.vel_horiz -
                                            (id_tscroll.tmapa[0].ancho_tile * resolution3);*/
                                if (info_prota.vel_vert < abs(info_prota.vel_horiz))
                                    info_prota.vel_vert = info_prota.vel_horiz;
                                end
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
                             (CTE_PROTA_MAX_AVANZAR_IZQUIERDA * resolution3) )
                            p_libre = 2;
                        end
                        
                        //Y ACTUAMOS SEGUN ESTE MOVIMIENTO
                        switch (p_libre)
                        //no se puede avanzar
                        case 0:
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
                        end
                        //si se puede avanzar
                        case 1:
                            info_prota.p_mover_h--;
         //prueba rara
                             //quitamos tanta velocidad como pixels por subir
                            //info_prota.vel_vert -= ((15 - info_prota.p_offsx) * resolution3);
                            info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
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
                            //info_prota.vel_vert -= (info_prota.p_offsy * resolution3) + 10;
                            info_prota.vel_vert = 0;
                            y3 -= (info_prota.p_offsy + 1) * resolution3;
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
                            x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
                            //no hay que actualizar casilla actual
                        end
                        //si se puede
                        case 1:
                            info_prota.p_mover_h--;
         //prueba rara
                            //info_prota.vel_vert -= (info_prota.p_offsy - (id_tscroll.tmapa[0].ancho_tile / 2));
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
                            x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
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
                            if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
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
                                info_prota.estado = CTE_PROTA_ESTADO_PARADO;
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
                            x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
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
                        info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                        //comprobamos la casilla superior para ver si podemos avanzar en diagonal
         //prueba rara
                        //info_prota.vel_vert -= (info_prota.p_offsy * resolution3) + 20;
                        info_prota.vel_vert = 0;
                        y3 -= (info_prota.p_offsy + 1) * resolution3;
                        info_prota.p_offsy = -1;
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
                            //info_prota.vel_vert = -(info_prota.vel_horiz - (info_prota.vel_horiz % 2)) / 2;
                            y3 -= (info_prota.vel_horiz - (info_prota.vel_horiz % 2)) / 2;
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
                            //info_prota.vel_vert += (info_prota.vel_horiz / 2);
                            y3 += (info_prota.vel_vert / 2);
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
                            x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
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
                        x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
                        //no hay que actualizar casilla actual
                        //atencion, si ibamos en diagonal hacia abajo, es posible que aun nos podamos
                        //mover hacia abajo
                        if (p_dir_ini == 3) p_dir = 2; end
                    end //sin rampa
                    
                    end //switch estamos en rampa
                end //casilla lateral obstruida
                
                end //switch dureza lateral
            end //movimiento lateral************************************
            
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
                    x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
                    //no hay que actualizar casilla actual
                    p_dir = 8;
                end
            end
        
        end //movimiento a la derecha
        
        //***************************************************************
        //***************************************************************
        
        //Movimiento a la izquierda
		
        if (info_prota.vel_horiz < 0)  //movimiento a la izquierda
        
            if (p_dir == 1) //movim diagonal hacia abajo
                //say("p_dir = 1");
                switch (p_dur[0][2])
                //casos en los que no se puede descender
                case 1,4,5,25,51,54,55,75,  //normales
                     105:                   //especiales (extra)
                    p_dir = 4;
                    //vel_vert = (15 * resolution3) - (info_prota.p_offsy * resolution3);
                end
                //casos en los que SI
                default:
                    //comprobamos si el que hay a la derecha nos deja avanzar
                    switch (p_dur[0][1])
                    //casos en los que si se puede avanzar
                    case 0,5,25,50,55,75,                   //normales
                         27,30,31,32,33,77,80,81,82,83,     //extras
                         100,104,105,                       //especiales (extra)
                         150..255:                          //otras
                        p_libre = 1;
                    end
                    //casos en los que, aunque libre, se avanza en otra dir
                    case 2,13,52,63,                        //normales
                         26,28,76,78:                       //extras
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
                        x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                        p_dir = 2;
                    end
                    //si se puede
                    case 1:
                        info_prota.p_mover_v--;
                        info_prota.p_mover_h++;
                        //si el tile diagonal esta vacio podemos caer*******************************
                        switch (p_dur[0][2])
                        case 0,2,13,14,15,50,52,63,64,65,                   //normales
                             26,28,29,30,32,33,34,76,78,79,80,82,83,84,     //extras
                             100,104,                                       //especiales (extra)
                             150..255:                                      //otras
                            
                            //todo listo para caer... pero no si estamos sobre el borde de una caida
                            switch (p_dur[1][2])
                            case 1,2,4,5,14,25,51,52,54,55,64,75,       //normales
                                 26,29,76,79,                           //extras
                                 105:                                   //especiales (extra)
                                
                                if (((info_prota.p_offsx * resolution3) + info_prota.vel_horiz) >= 
                                    (-CTE_PROTA_MAX_AVANZAR_IZQUIERDA * resolution3))
                                    //no podemos caer aun
                                    p_dir = 4;
                                else
                                    //si podemos caer
                                    info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
                                    //actualizamos casilla actual
                                    p_dur[2][0] = p_dur[1][1];
                                    p_dur[2][1] = p_dur[1][2];
                                    p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley+2,0);
                                    p_dur[1][0] = p_dur[0][1];
                                    p_dur[1][1] = p_dur[0][2];
                                    p_dur[1][2] = obtener_tile(&durezas,info_prota.p_tilex-1,info_prota.p_tiley+2,0);
                                    p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                                    p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                                    p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-2,0);
                                end //if al borde
                            end
                            default:
                                //si podemos caer
                                info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
                                //actualizamos casilla actual
                                p_dur[2][0] = p_dur[1][1];
                                p_dur[2][1] = p_dur[1][2];
                                p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley+2,0);
                                p_dur[1][0] = p_dur[0][1];
                                p_dur[1][1] = p_dur[0][2];
                                p_dur[1][2] = obtener_tile(&durezas,info_prota.p_tilex-1,info_prota.p_tiley+2,0);
                                p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                                p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                                p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-2,0);
                            end
                            end //switch suelo
                        end
                        case 3,53:
                            //rampa: nos movemos y perdemos toda la velocidad, con esto se acaba el movimiento
                            //esto es mejor, ponemos una velocidad de la gravedad superior para traspasar la rampa, y luego nos recolocaremos
                            if (info_prota.estado != CTE_PROTA_ESTADO_SALTANDO)
                               /*vel_vert=(info_prota.p_offsx*resolution3)+info_prota.vel_horiz-
                                           (id_tscroll.tmapa[0].ancho_tile*resolution3);*/
         //prueba rara
                                if (info_prota.vel_vert < abs(info_prota.vel_horiz))
                                    info_prota.vel_vert = -info_prota.vel_horiz;
                                end
                            end
                            //actualizamos casilla actual
                            p_dur[2][0] = p_dur[1][1];
                            p_dur[2][1] = p_dur[1][2];
                            p_dur[2][2] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley+2,0);
                            p_dur[1][0] = p_dur[0][1];
                            p_dur[1][1] = p_dur[0][2];
                            p_dur[1][2] = obtener_tile(&durezas,info_prota.p_tilex-1,info_prota.p_tiley+2,0);
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                            p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-2,0);
                        end
                        end
                        //actualizamos casilla actual           
                        //lo hemos hecho antes, hay un caso especial que contemplar
                    end
                    //hay una rampa
                    case 2:
                        p_dir = 4;
                    end
                    end //switch
                end
                end //switch
            end //movimiento diagonal******
            
            if (p_dir == 4)   //movimiento lateral
                //say("p_dir=4");
                switch (p_dur[0][1])            
                
                //si permite el paso normal
                case 0,2,5,13,25,50,52,52,63,75,    //normales
                     26..32,33,76..82,83,           //extras
                     100,104,105,                   //especiales (extras)
                     150..255:                      //otras
                    //comprobamos la casilla actual, podríamos estar en una rampa ascendente y dejarnos en
                    //un tile superior en lugar del tile de al lado
                    
                    switch (p_dur[1][1])
                    
                    //estamos en rampa o media rampa superior
                    case 2,14,52,64,                //normales
                         26,29,76,79:               //extras
                        //comprobamos el techo izquierdo. Aqui pueden pasar tres cosas que almacenaremos en p_libre
                        //0: No se permite el paso
                        //1: Se permite el paso, nos movemos lateralmente
                        //2: Se permite el paso PERO un tile nos obliga a permanecer en el superior
                        switch (p_dur[0][0])
                        //parte superior libre
                        case 0,25,50,75,                            //normales
                             27,29,30,31,32,33,77,79,80,81,82,83,   //extras
                             100,104,105,                           //especiales (extras)
                             150..255:                              //otras
                            p_libre = 1;
                        end
                        //caso especial, hay una rampa que obliga a ir diagonal
                        case 2,13,52,63,            //normales
                             26,28,76,78:           //extras
                            p_libre = 2;
                        end
                        //parte superior ocupada
                        default:
                            p_libre = 0;
                        end
                        end //switch comprobando sig techo
                        
                        //caso especial: la siguiente casilla permite atravesarse en todas direcciones menos
                        //               hacia abajo
                        switch (p_dur[0][1])
                        case 25,75,105:             //extras
                            p_libre = 2;
                        end
                        end //switch, caso especial tile izquierdo
                        //caso especial: no nos hemos movido lo suficiente a la izquierda para caernos, nos
                        //               sujeta la esquina del gráfico.
                        if ( ((x3 + info_prota.vel_horiz) % (id_tscroll.tmapa[0].ancho_tile * resolution3)) > 
                             (CTE_PROTA_MAX_AVANZAR_DERECHA * resolution3) )
                            p_libre = 2;
                        end
                        
                        //Y ACTUAMOS SEGUN ESTE MOVIMIENTO
                        switch (p_libre)
                        //no se puede avanzar
                        case 0:
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                        end
                        //si se puede avanzar
                        case 1:
                            info_prota.p_mover_h++;
         //prueba rara
                            //quitamos tanta velocidad como pixels por subir
                            //info_prota.vel_vert -= (info_prota.p_offsx * resolution3);
                            info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
                            //actualizamos casilla actual
                            p_dur[2][0] = p_dur[1][0];
                            p_dur[2][1] = p_dur[1][1];
                            p_dur[2][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[0][0];
                            p_dur[1][1] = p_dur[0][1];
                            p_dur[1][2] = p_dur[0][2];
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                            p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley+1,0);
                        end
                        //se avanza, pero se sube al mismo tiempo
                        case 2:
                            info_prota.p_mover_h++;
                            info_prota.p_mover_v--;
         //prueba rara
                            //info_prota.vel_vert-=(info_prota.p_offsy*resolution3)+10;
                            info_prota.vel_vert = 0;
                            y3 -= (info_prota.p_offsy + 1) * resolution3;
                            //actualizamos casilla actual
                            p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley-2,0);
                            p_dur[2][1] = p_dur[1][0];
                            p_dur[2][2] = p_dur[1][1];
                            p_dur[1][0] = obtener_tile(&durezas,info_prota.p_tilex-1,info_prota.p_tiley-2,0);
                            p_dur[1][1] = p_dur[0][0];
                            p_dur[1][2] = p_dur[0][1];
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-2,0);
                            p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                            //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                            switch (p_dur[1][1])
                            case 27,29,30,31,77,79,80,81:           //extras
                                p_dur[1][1]=0;
                            end
                            end //switch
                        end
                        end //switch dirección final de movimiento
                        
                    end //case rampa o media rampa superior
                                                                
                    //estamos en media rampa inferior
                    case 13,28,63,78:
                        //comprobamos si el techo nos deja avanzar
                        switch (p_dur[0][0])
                        //Si se puede
                        case 0,25,50,75,                    //normal (he eliminado las rampas de techo)
                             26..32,33,76..82,83,           //extras
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
                        case 0:
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                            //no hay que actualizar casilla actual
                        end
                        case 1:
                            info_prota.p_mover_h++;
         //prueba rara
                            //info_prota.vel_vert -= (info_prota.p_offsy - (id_tscroll.tmapa[0].ancho_tile / 2));
                            //actualizamos casilla actual
                            p_dur[2][0] = p_dur[1][0];
                            p_dur[2][1] = p_dur[1][1];
                            p_dur[2][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[0][0];
                            p_dur[1][1] = p_dur[0][1];
                            p_dur[1][2] = p_dur[0][2];
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                            p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley+1,0);
                            //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                            switch (p_dur[1][1])
                            case 27,31,77,81:           //extras
                                p_dur[1][1] = 0;
                            end
                            end //switch
                        end
                        end
                    end //case media rampa inferior
                    
                    //estamos en media rampa superior descendente
                    case 16,31,66,81:
                        //comprobamos si el techo nos deja avanzar
                        switch (p_dur[0][0])
                        //Si se puede
                        case 0,25,50,75,                    //normal (he eliminado las rampas de techo)
                             26..32,33,76..82,83,           //extras
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
                            info_prota.vel_horiz = 0;
                            x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                            //no hay que actualizar casilla actual
                        end
                        //si se puede
                        case 1:
                            //actualizamos casilla actual
                            p_dur[2][0] = p_dur[1][0];
                            p_dur[2][1] = p_dur[1][1];
                            p_dur[2][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[0][0];
                            p_dur[1][1] = p_dur[0][1];
                            p_dur[1][2] = p_dur[0][2];
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                            p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley+1,0);
                            //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                            switch (p_dur[1][1])
                            case 27,31,77,81:           //extras
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
                        switch (p_dur[0][0])
                        case 1,2,3,4,13,14,15,16,51,52,53,54,63,64,65,66,   //normales
                             34,84:                                         //extras
                            if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
                                p_libre = 0;
                            else
                                p_libre = 1;
                            end
                        end
                        default: p_libre = 1; end
                        end //switch
                        
                        //actuamos en consecuencia
                        if (p_libre)
                            info_prota.p_mover_h++;
                            if (p_dir_ini == 1)
                                info_prota.p_mover_v = 0;
                                info_prota.vel_vert = 0;
                                info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                            end
                            //actualizamos casilla actual
                            p_dur[2][0] = p_dur[1][0];
                            p_dur[2][1] = p_dur[1][1];
                            p_dur[2][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[0][0];
                            p_dur[1][1] = p_dur[0][1];
                            p_dur[1][2] = p_dur[0][2];
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                            p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley+1,0);
                            //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                            switch (p_dur[1][1])
                            case 27,29,30,31,77,79,80,81:           //extras
                                p_dur[1][1] = 0;
                            end
                            end //switch
                        else
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
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
                    case 2,14,52,64,                //normales
                         26,29,76,79:               //extras
                        info_prota.p_mover_v = 0;
                        info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                        //comprobamos la casilla superior para ver si podemos avanzar en diagonal
         //prueba rara
                        //info_prota.vel_vert -= (info_prota.p_offsy * resolution3) + 20;
                        info_prota.vel_vert = 0;
                        y3 -= (info_prota.p_offsy + 1) * resolution3;
                        p_dir = 7;
                    end //rampa y media rampa superior
                    
                    //media rampa inferior y media rampa superior en descenso
                    case 13,28,63,78,16,31,66,81:
                        //caso especial, pues se podria avanzar si la sig casilla
                        //fuera media rampa superior normal (las traspasables se
                        //contemplaron antes)
                        switch (p_dur[0][1])
                        case 14,64:
                            info_prota.p_mover_h++;
         //prueba rara
                            //info_prota.vel_vert=-(info_prota.vel_horiz-(info_prota.vel_horiz%2))/2;
                            y3 -= (info_prota.vel_horiz - (info_prota.vel_horiz % 2)) / 2;
                            //actualizamos casilla actual
                            p_dur[2][0] = p_dur[1][0];
                            p_dur[2][1] = p_dur[1][1];
                            p_dur[2][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[0][0];
                            p_dur[1][1] = p_dur[0][1];
                            p_dur[1][2] = p_dur[0][2];
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                            p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley+1,0);
                        end
                        case 15,65:
                            info_prota.p_mover_h++;
         //prueba rara
                            //info_prota.vel_vert+=(info_prota.vel_horiz/2);
                            y3 += (info_prota.vel_horiz / 2);
                            //actualizamos casilla actual
                            p_dur[2][0] = p_dur[1][0];
                            p_dur[2][1] = p_dur[1][1];
                            p_dur[2][2] = p_dur[1][2];
                            p_dur[1][0] = p_dur[0][0];
                            p_dur[1][1] = p_dur[0][1];
                            p_dur[1][2] = p_dur[0][2];
                            p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                            p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                            p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley+1,0);
                        end
                        default:    //no podemos pasar
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                            if (p_dir_ini == 1)
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
                        x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                        //no hay que actualizar casilla actual
                        //atencion, si ibamos en diagonal hacia abajo, es posible que aun nos podamos
                        //mover hacia abajo
                        if (p_dir_ini == 1) p_dir = 2; end
                    end //sin rampa
                    
                    end //switch estamos en rampa
                end //casilla lateral obstruida
                
                end //switch dureza lateral
            end //movimiento lateral*******
            
            if (p_dir == 7)
                //say("p_dir = 7");
                //comprobamos si la casilla está libre
                switch (p_dur[0][0])
                //casilla libre
                case 0,2,13,25,50,52,63,75,         //normal
                     26..32,33,76..82,83,           //extras
                     100,104,105,                   //especiales (extras)
                     150..255:                      //otras
                    p_libre = 1;
                end
                //casilla ocupada
                default:
                    p_libre = 0;
                end
                end //switch dureza diagonal
                
                if (p_libre)
                    info_prota.p_mover_v++;
                    info_prota.p_mover_h++;
                    //actualizamos casilla actual
                    p_dur[2][0] = obtener_tile(&durezas,info_prota.p_tilex  ,info_prota.p_tiley-2,0);
                    p_dur[2][1] = p_dur[1][0];
                    p_dur[2][2] = p_dur[1][1];
                    p_dur[1][0] = obtener_tile(&durezas,info_prota.p_tilex-1,info_prota.p_tiley-2,0);
                    p_dur[1][1] = p_dur[0][0];
                    p_dur[1][2] = p_dur[0][1];
                    p_dur[0][0] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-2,0);
                    p_dur[0][1] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley-1,0);
                    p_dur[0][2] = obtener_tile(&durezas,info_prota.p_tilex-2,info_prota.p_tiley  ,0);
                    //si avanzamos hasta rampa traspasable invertida, la atravesamos (la ponemos a cero)
                    switch (p_dur[1][1])
                    case 27,29,30,31,77,79,80,81:           //extras
                        p_dur[1][1] = 0;
                    end
                    end //switch
                else
                    info_prota.p_mover_h = 0;
                    info_prota.vel_horiz = 0;
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    //no hay que actualizar casilla actual
                    p_dir = 8;
                end
            end
        
        end //movimiento a la izquierda
        		
        //******************************************************
        //******************************************************
        
        //movimientos verticales
        //Movimientos verticales
        if (p_dir == 2)    //movimiento hacia abajo
            //say("p_dir = 2");
            switch (p_dur[1][2])
            //no se puede
            case 1,4,5,25,51,54,55,75,
                 105:                       //especial (extra) ********** CAMBIAR ********************************
                info_prota.p_mover_v = 0;
                info_prota.vel_vert = 0;
                //y3 += (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsy) * resolution3;
                /*y3 += (id_tscroll.tmapa[0].alto_tile * resolution3) -
                        (y3 % (id_tscroll.tmapa[0].alto_tile * resolution3)) -
                        CTE_PROTA_GRAVEDAD;*/   //Original, evitar el rebote
                
                //Segundo intento, evita el rebote, tres operaciones menos
                /*y3 += (id_tscroll.tmapa[0].alto_tile - info_prota.p_offsy) * resolution3;
                y3 -= (y3 % (id_tscroll.tmapa[0].alto_tile * resolution3)) + CTE_PROTA_GRAVEDAD;*/
                
                //Tercer intento, mucho mejor, elimina el rebote y reduce cálculos a menos de la mitad
                y3 = ((info_prota.p_tiley + 1) * id_tscroll.tmapa[0].alto_tile * resolution3) - var_prota_gravedad;
                
                if (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO)
                    info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                end
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
                    if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                        switch (p_dur[0][2])
                        case 1,3,4,5,16,25,51,53,54,55,66,75,           //normales
                             27,31,77,81:                               //extras
                            //excepción: debajo hay una rampa
                            switch (p_dur[1][2])
                            case 2,14,52,64,            //normales
                                 26,29,76,79:           //extras
                                p_libre = 1;
                            end
                            default: p_libre = 0; end
                            end //switch
                        end
                        end //switch
                    end
                    //pegado a la derecha
                    if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                        switch (p_dur[2][2])
                        case 1,2,4,5,14,25,51,52,54,55,64,75,           //normales
                             26,29,76,79:                               //extras
                            //excepción: debajo hay una rampa
                            switch (p_dur[1][2])
                            case 3,16,53,66,            //normales
                                 27,31,77,81:           //extras
                                p_libre = 1;
                            end
                            default: p_libre = 0; end
                            end //switch
                        end
                        end //switch
                    end
                end
                
                //y actuamos en consecuencia
                if (p_libre)
                    info_prota.p_mover_v--;
                    info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
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
                        if ((info_prota.vel_horiz < 0) &&
                            ((info_prota.p_offsx + (info_prota.vel_horiz / resolution3)) <
                                CTE_PROTA_MAX_AVANZAR_IZQUIERDA))
                            
                            /*say("DUR 2: Deplazamiento izquierda, " +
                                itoa(CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) + 
                                "      " + CTE_PROTA_MAX_AVANZAR_IZQUIERDA + " " + info_prota.p_offsx + 
                                " " + info_prota.vel_horiz);*/
                                
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                        end
                    end
                    end //switch
                    switch (p_dur[2][0])
                    case 1,2,3,5,13,14,15,16,51,52,53,55,63,64,65,66,   //normales
                         33,83:                                         //extras
                        if ((info_prota.vel_horiz > 0) &&
                            ((info_prota.p_offsx + (info_prota.vel_horiz / resolution3)) >
                                CTE_PROTA_MAX_AVANZAR_DERECHA))
                            info_prota.p_mover_h = 0;
                            info_prota.vel_horiz = 0;
                            x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
                            /*say("DUR 2: Deplazamiento derecha, " +
                                itoa(CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx));*/
                        end
                    end
                    end //switch
                else
                    info_prota.p_mover_v = 0;
                    info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                    info_prota.vel_vert = 0;
                    //y3 += (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsy) * resolution3;
                    y3 = ((info_prota.p_tiley + 1) * id_tscroll.tmapa[0].alto_tile * resolution3) - CTE_PROTA_GRAVEDAD;
                end
                
            end //si se puede
            end //switch mirar tile abajo
        end //movimiento hacia abajo
        
        //p_libre=1;
        if (p_dir == 8)       //movimiento hacia arriba
            //say("p_dir = 8");
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
                if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                    switch (p_dur[0][0])
                    case 1,3,4,14,15,16,51,53,54,64,65,66:              //normales
                         //32,82:                                         //extras
                        p_libre = 0;
                    end
                    //hay una excepción: estamos en una rampa y en diagonal hay otra que la continua
                    case 2,13,52,63,                                    //normales
                         32,82:                                         //extras
                        switch (p_dur[1][1])
                        case 2,14,52,64,                //normales
                             26,29,76,79:               //extras
                            p_libre = 1;
                        end
                        default: p_libre = 0; end
                        end //switch
                    end
                    end //switch
                end //pegado a la izquierda
                if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                    switch (p_dur[2][0])
                    case 1,2,5,13,14,16,51,52,55,63,64,66:              //normales
                         //32,82:                                         //extras
                        p_libre = 0;
                    end
                    //hay una excepción: estamos en una rampa y en diagonal hay otra que la continua
                    case 3,15,53,65,                                    //normales
                         32,82:                                         //extras
                        switch (p_dur[1][1])
                        case 3,16,53,66,                //normales
                             27,31,77,81:               //extras
                            p_libre = 1;
                        end
                        default: p_libre = 0; end
                        end //switch
                    end
                    end //switch
                end //pegado a la derecha
            end
            end //switch mirar tile arriba
            
            //say("p_libre = " + itoa(p_libre));
            //say("vel_vert = " + itoa(info_prota.vel_vert));
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
                y3 -= (info_prota.p_offsy + 2) * resolution3;
            end
            
        end

        //movimiento hacia arriba
        		
        //*********************************************************
        //  comprobación tile actual
        //*********************************************************
        
        //*********************************************************
        //  comprobación tile actual
        //*********************************************************
        
        //say("ya no influye p_dur: " + info_prota.vel_horiz + " " + info_prota.vel_vert);
        
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
            //comprobamos no chocarnos con una pared o la esquina de un techo
            if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                //pared
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                        info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end //pared
            
            
            if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                //esquina de un techo
                switch (p_dur[0][0])
                //no se puede subir
                case 1,2,3,4,13,14,15,16,51,52,53,54,63,64,65,66,   //normales
                     32,82:                                         //extras
                    if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
                        if (info_prota.vel_vert < 0) //chocamos con techo si estamos subiendo
                            y3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy) * resolution3;
                            info_prota.p_offsy += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy);
                            p_libre = 0;
                        end
                        //podemos chocar con techo también si hemos saltado y nos desplazamos de lado
                        //NO, YA ESTA HECHO EN IF ANTERIOR
                        if ((info_prota.p_offsx - info_prota.vel_horiz) >=
                            CTE_PROTA_MAX_AVANZAR_IZQUIERDA) 
                            x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                            info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                            //info_prota.vel_horiz = 0;
                        end
                    end
                end
                end //switch
            end
            
            if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                        info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end //pared
            
            if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                //esquina de un techo
                switch (p_dur[2][0])
                //no se puede subir
                case 1,2,3,5,13,14,15,16,51,52,53,55,63,64,65,66,   //normales
                     32,82:                                         //extras
                    if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
                        if (info_prota.vel_vert < 0)
                            y3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy) * resolution3;
                            info_prota.p_offsy += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy);
                            p_libre = 0;
                        end
                        if ((info_prota.p_offsx - info_prota.vel_horiz) <= CTE_PROTA_MAX_AVANZAR_DERECHA)
                            x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                            info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
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
                //say(itoa(info_prota.p_offsy));
                if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
                    y3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy) * resolution3;        //un cambio aqui****************
                    p_libre = 0;
                end
                //say("despues: " + itoa((y3 / resolution3) % id_tscroll.tmapa[0].alto_tile));
            end //techo liso
            //techo diagonal, parte baja a la derecha**********************************EL FALLO ESTA AQUI
            case 4,54:                                                               //quitar vel horiz
                if (info_prota.p_offsy < (info_prota.p_offsx - CTE_PROTA_DIFERENCIA_CON_TECHO))
                    y3 += (info_prota.p_offsx - CTE_PROTA_DIFERENCIA_CON_TECHO -
                            info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte baja a la derecha
            //techo diagonal, parte baja a la izquierda
            case 5,55:
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - info_prota.p_offsx -
                                            CTE_PROTA_DIFERENCIA_CON_TECHO))
                    y3 += (id_tscroll.tmapa[0].alto_tile - info_prota.p_offsx -
                            CTE_PROTA_DIFERENCIA_CON_TECHO - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte baja a la izquierda
            end //switch techo
        end //casilla libre
        
        //rampa, parte alta a la izquierda
        case 2,52,                  //normales
             26,76:                 //extras
            
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                switch (p_dur[0][0])    //miramos el superior
                //no se puede pasar (incluye medias rampas, para pasarlas tendríamos que estar en otro tile)
                case 1,3,4,14,15,16,51,53,54,64,65,66,          //normales
                     34,84:                                     //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
            end
            if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                        info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
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
                if (info_prota.p_offsx < CTE_PROTA_ALTURA_TECHO)
                    x3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsx) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
                    y3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy) * resolution3;
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
                if (info_prota.p_offsx <
                    ((id_tscroll.tmapa[0].ancho_tile / 2) - CTE_PROTA_DIFERENCIA_CON_TECHO))
                    
                    x3 += (((id_tscroll.tmapa[0].ancho_tile / 2) - CTE_PROTA_DIFERENCIA_CON_TECHO) -
                            info_prota.p_offsx) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < (id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx))
                    y3 += ((id_tscroll.tmapa[0].alto_tile - 1 - info_prota.p_offsx) - info_prota.p_offsy) *
                            resolution3;
                    p_libre = 0;
                end
            end //techo diagonal, parte izquierda abajo
            end //switch techo
            
            //say(itoa(info_prota.estado));
            
            //da igual el tipo de techo que tengamos, no podemos atravesar el suelo
            if (info_prota.p_offsy >= info_prota.p_offsx)
                //say("hola");
                //say("Y3 4: offsetx=" + info_prota.p_offsx + "    - offsety=" + info_prota.p_offsy);
                y3 += (info_prota.p_offsx - info_prota.p_offsy) * resolution3;
                if (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO)
                    info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                end
                info_prota.p_mover_v = 0;
                //info_prota.vel_vert = 0;
                info_prota.vel_vert = abs(info_prota.vel_horiz) + CTE_PROTA_ACELERAC;
            end
            
        end //está en rampa, parte alta a la izquierda
        
        //rampa, parte alta a la derecha
        case 3,53,                  //normales
             27,77:                 //extras
             
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                        info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                switch (p_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,              //normales
                     33,83:                                         //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
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
                if (info_prota.p_offsx > CTE_PROTA_DIFERENCIA_CON_TECHO)
                    x3 -= (info_prota.p_offsx - CTE_PROTA_DIFERENCIA_CON_TECHO) * resolution3;
                    info_prota.vel_horiz = 0;
                end
                if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
                    y3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy) * resolution3;
                    p_libre = 0;
                end
            end //techo liso
            //techo diagonal, parte derecha abajo
            case 4,54:
                //podemos avanzar sólo hasta casi la mitad, la distancia se cierra por momentos, aunque
                //inicialmente tenemos una altura de 2 tiles en la parte derecha
                if (info_prota.p_offsx >
                    ((id_tscroll.tmapa[0].ancho_tile / 2) + CTE_PROTA_DIFERENCIA_CON_TECHO))
                    
                    x3 -= (info_prota.p_offsx -
                                ((id_tscroll.tmapa[0].ancho_tile / 2) + CTE_PROTA_DIFERENCIA_CON_TECHO)) *
                            resolution3;
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
                if (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO)
                    info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                end
                info_prota.p_mover_v = 0;
                //info_prota.vel_vert = 0;
                info_prota.vel_vert = abs(info_prota.vel_horiz) + var_prota_acelerac;
            end
            
        end //está en rampa, parte alta a la derecha
        
        //media rampa baja, parte alta a la izquierda
        case 13,28,             //normales
             63,78:             //extras
             
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch tile lateral
                
                //miramos el tile superior
                switch (p_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,61,63,64,65,66,     //normales
                     34,84:                             //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 13,16,63,66:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                        info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
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
                if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
                    y3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy) * resolution3;
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
                y3 += ((((id_tscroll.tmapa[0].alto_tile / 2) - 1) + (info_prota.p_offsx / 2)) - info_prota.p_offsy)
                        *resolution3;
                if (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO)
                    info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                end
                info_prota.p_mover_v = 0;
                //info_prota.vel_vert = 0;
                info_prota.vel_vert = (abs(info_prota.vel_horiz) + var_prota_acelerac) / 2;
            end
            
        end //media rampa baja, parte alta a la izquierda
        
        //media rampa baja, parte alta a la derecha
        case 15,65,                 //normales
             30,80:                 //extras
            
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                //no se puede si no estamos a una altura mínima (medias rampas)
                case 14,15,64,65:
                    if (info_prota.p_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                        x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                        info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                        info_prota.vel_horiz = 0;
                    end
                end //no se puede si n estamos a una altura mínima (medias rampas)
                end //switch
            end
            if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el techo superior
                switch (p_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,  //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
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
                if (info_prota.p_offsy < CTE_PROTA_ALTURA_TECHO)
                    y3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsy) * resolution3;
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
                y3 += (((id_tscroll.tmapa[0].alto_tile - 1) - (info_prota.p_offsx / 2)) - info_prota.p_offsy)
                        * resolution3;
                if (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO)
                    info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                end
                info_prota.p_mover_v = 0;
                //info_prota.vel_vert = 0;
                info_prota.vel_vert = (abs(info_prota.vel_horiz) + var_prota_acelerac) / 2;
            end
            
        end //está en media rampa baja, parte alta a la derecha
        
        //media rampa alta, parte alta a la izquierda
        case 14,64,                         //normales
             29,79:                         //extras
             
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                switch (p_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,51,53,54,64,65,66,              //normales
                     34,84:                                         //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
            end
            if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                switch (p_dur[2][1])
                //no se puede pasar
                case 1,2,5,14,51,52,55,64,              //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el tile superior
                switch (p_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,  //normales
                     33,83:                             //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
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
                if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_IZQUIERDA) * resolution3;
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
                if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_DERECHA)
                    x3 += (CTE_PROTA_MAX_AVANZAR_DERECHA - info_prota.p_offsx) * resolution3;
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
                if (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO)
                    info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                end
                info_prota.p_mover_v = 0;
                //info_prota.vel_vert = 0;
                info_prota.vel_vert = (abs(info_prota.vel_horiz) + var_prota_acelerac) / 2;
            end
            
        end //media rampa alta, parte alta a la izquierda
        
        //media rampa alta, parte alta a la derecha
        case 16,66,                         //normales
             31,81:                         //extras
             
            //comprobamos no chocarnos con una pared
            if (info_prota.p_offsx < CTE_PROTA_MAX_AVANZAR_IZQUIERDA)
                switch (p_dur[0][1])
                //no se puede pasar
                case 1,3,4,16,51,53,54,66,              //normales
                     34,84:                             //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede
                end //switch
                
                //miramos el tile superior
                switch (p_dur[0][0])
                //no se puede pasar
                case 1,3,4,14,15,16,51,53,54,64,65,     //normales
                     34,84:                             //extras
                    x3 += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx) * resolution3;
                    info_prota.p_offsx += (CTE_PROTA_MAX_AVANZAR_IZQUIERDA - info_prota.p_offsx);
                    info_prota.vel_horiz = 0;
                end //no se puede pasar
                end //switch
            end
            if (info_prota.p_offsx > CTE_PROTA_MAX_AVANZAR_DERECHA)
                switch (p_dur[2][0])
                //no se puede pasar
                case 1,2,5,13,14,16,51,52,55,63,64,66,              //normales
                     33,83:                                         //extras
                    x3 -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA) * resolution3;
                    info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_MAX_AVANZAR_DERECHA);
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
                y3 += (((id_tscroll.tmapa[0].alto_tile / 2) - (info_prota.p_offsx / 2)) - info_prota.p_offsy)
                        * resolution3;
                if (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO)
                    info_prota.estado = CTE_PROTA_ESTADO_PARADO;
                end
                info_prota.p_mover_v = 0;
                //info_prota.vel_vert = 0;
                info_prota.vel_vert = (abs(info_prota.vel_horiz) + var_prota_acelerac) / 2;
            end
        end //media rampa alta, parte alta a la izquierda
        
        //techo, parte baja a la derecha
        case 4,54:
            //si nos movemos lateralmente chocaremos con el techo, no debemos poder avanzar
            if ((info_prota.vel_horiz > 0) &&
                (info_prota.p_offsx > CTE_PROTA_DIFERENCIA_CON_TECHO))
                
                x3 -= (info_prota.p_offsx - CTE_PROTA_DIFERENCIA_CON_TECHO) * resolution3;
                info_prota.p_offsx -= (info_prota.p_offsx - CTE_PROTA_DIFERENCIA_CON_TECHO);
                if (info_prota.vel_vert < 0)
                    info_prota.vel_vert = 0;
                    info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
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
            if ((info_prota.vel_horiz < 0) && (info_prota.p_offsx < CTE_PROTA_ALTURA_TECHO))
                x3 += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsx) * resolution3;
                info_prota.p_offsx += (CTE_PROTA_ALTURA_TECHO - info_prota.p_offsx);
                if (info_prota.vel_vert < 0)
                    info_prota.vel_vert = 0;
                    info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
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
        
        //comprobamos choque contra el techo
        if (!p_libre)
            if (info_prota.vel_vert < 0) info_prota.vel_vert = 0; end
            if (info_prota.estado == CTE_PROTA_ESTADO_SALTANDO) 
                cont_salto = CTE_PROTA_MAX_SALTO;
                info_prota.estado = CTE_PROTA_ESTADO_CAYENDO;
            end
            info_prota.p_mover_v = 0;
        end
                
        //**********************************************
        //  Zona de daños
        //**********************************************
        if (info_prota.dano_id != 0)
            if (info_prota.p_invencible == 0)
                info_prota.p_energ -= info_prota.dano_energia;
                if (info_prota.p_energ < 0) info_prota.p_energ = 0; end
                
                //refresh_interface_energy();
                
                cambiar_exp_arma (-info_prota.dano_exp);
                refresh_interface();
                
                info_prota.vel_horiz = info_prota.dano_vel_horiz;
                info_prota.vel_vert = -10;
                
                prota_control = 0;
                info_prota.dano_time = 25;
                info_prota.p_invencible = 151;
                
                if (info_prota.p_energ == 0) dead_event (); end
            end
            info_prota.dano_id = 0;
        end
        if (info_prota.dano_time > 0)
            info_prota.dano_time--;
            if (info_prota.dano_time == 0) prota_control = 1; end
        end
        
        if (info_prota.p_invencible > 0) info_prota.p_invencible--; end
        
		//**********************************************
        //  Zona de daños contínuos (lava, ácido, gases...)
        //**********************************************
		if (info_prota.dano_cont_id != 0)
			if (info_prota.dano_cont_ener >= 0)
				info_prota.p_energ -= info_prota.dano_cont_ener;
                if (info_prota.p_energ < 0) info_prota.p_energ = 0; end
				
				refresh_interface();
				
				if (info_prota.p_energ == 0) dead_event (); end
			else
				info_prota.dano_cont_time++;
				temp = info_prota.dano_cont_time % info_prota.dano_cont_ener;
				if (temp == 0)
					info_prota.p_energ --;
					refresh_interface();
					if (info_prota.p_energ == 0) dead_event (); end
				end
			end
			info_prota.dano_cont_id = 0;
		else
			if (info_prota.dano_cont_time > 0) info_prota.dano_cont_time = 0; end
		end
		
        //**********************************************
        //  Zona de animaciones
        //**********************************************
        //say("Estado después: " + itoa(info_prota.estado));
        //if (info_prota.vel_horiz < 0) flags = 1; end
        //if (info_prota.vel_horiz > 0) flags = 0; end
        if (teclas[k_left][2] == 1)  flags = 1; end
        if (teclas[k_right][2] == 1) flags = 0; end
        
		//Eliminamos las velocidades sumadas externamente para que no se acumulen a cada frame
		if (info_prota.ext_velx != 0)
			/*if (fps < 25)
				say("vel_horiz = " + info_prota.vel_horiz + "; ext x = " + info_prota.ext_velx);
			end*/
			if (abs(info_prota.ext_velx - info_prota.vel_horiz) > 0)
				info_prota.vel_horiz -= info_prota.ext_velx;
			else
				info_prota.vel_horiz = 0;
			end
		end
		if (info_prota.ext_vely != 0)
			if (abs(info_prota.vel_vert) > abs(info_prota.ext_vely))
				info_prota.vel_vert -= info_prota.ext_vely;
			else
				info_prota.vel_vert = 0;
			end
		end
		
		if (frame_info.fps < 25)
			say("vel_horiz = " + info_prota.vel_horiz + "; Estado = " + info_prota.estado + "; Plataforma = " + info_prota.id_plataforma + "; ext x = " + info_prota.ext_velx);
		end
		//if (info_prota.id_plataforma == -1)
			if ( (info_prota.vel_horiz != 0) && (info_prota.estado == CTE_PROTA_ESTADO_PARADO) )
				info_prota.estado = CTE_PROTA_ESTADO_ANDANDO;
			end
			if ( (info_prota.vel_horiz == 0) && (info_prota.estado == CTE_PROTA_ESTADO_ANDANDO) )
				info_prota.estado = CTE_PROTA_ESTADO_PARADO;
			end
		/*else
			if ( (info_prota.vel_horiz != 0) && (info_prota.estado == CTE_PROTA_ESTADO_PARADO) )
				if ((info_prota.id_plataforma != -1) || (info_prota.vel_horiz != info_prota.ext_velx))
					info_prota.estado = CTE_PROTA_ESTADO_ANDANDO;
				end
			end
			if ( (info_prota.estado == CTE_PROTA_ESTADO_ANDANDO) && (info_prota.vel_horiz != info_prota.ext_velx))
				info_prota.estado = CTE_PROTA_ESTADO_PARADO;
			end
		end*/
		
		/*if ((info_prota.id_plataforma != -1) && (info_prota.ext_vely > 0) && (info_prota.vel_vert <= 0))
			info_prota.id_plataforma = -1;
			info_prota.estado = CTE_PROTA_ESTADO_PARADO;
		end*/
        //say("Estado final: " + itoa(info_prota.estado));
        //say("inicio animación: " + itoa(search_animation(&animation_prota, info_prota.estado)));
        
        switch (info_prota.estado)
        case CTE_PROTA_ESTADO_PARADO:
            if (teclas[k_up][2] > 0) info_prota.anim = 4;
            else info_prota.anim = 0; end
        end
        case CTE_PROTA_ESTADO_ANDANDO:
            if (teclas[k_up][2] > 0) info_prota.anim = 5;
            else info_prota.anim = 1; end
        end
        case CTE_PROTA_ESTADO_SALTANDO:
            if (teclas[k_up][2] > 0) info_prota.anim = 6;
            else info_prota.anim = 2; end
        end
        case CTE_PROTA_ESTADO_CAYENDO:
            if (info_prota.vel_vert < 0) 
                if (teclas[k_up][2] > 0) info_prota.anim = 6;
                else info_prota.anim = 2; end
            else
                info_prota.anim = 3;
            end
        end
        default: info_prota.anim = info_prota.estado; end
        end //switch
        
        if (info_prota.anim != info_prota.anim_ant)
            animation_prota_data[0] = search_animation(&animation_prota, info_prota.anim) + 1;
            animation_prota_data[1] = animation_prota_data[0] + animation_prota[animation_prota_data[0] - 1] - 1;
            animation_prota_data[2] = animation_prota_data[0];
            animation_prota_cont = 0;
            //graph = animation_prota[animation_prota_data[2]];
        end
        if (animation_prota_cont == 5)
            animation_prota_cont = 0;
            if (animation_prota_data[2] == animation_prota_data[1])
                animation_prota_data[2] = animation_prota_data[0];
            else
                animation_prota_data[2]++;
            end
            //graph = animation_prota[animation_prota_data[2]];
        end
        graph = animation_prota[animation_prota_data[2]];
        animation_prota_cont++;
        
        info_prota.anim_ant = info_prota.anim;
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
		
		/*if ((abs(antx - x) > 1) || (abs(anty - y) > 1))
			say("DESPLAZAMIENTO EXTRA: " + itoa(antx -x) + " " + itoa(anty - y));
		end*/
		antx = x;
		anty = y;
		if (info_prota.ext_velx != 0) info_prota.ext_velx = 0; end
		if (info_prota.ext_vely != 0) info_prota.ext_vely = 0; end
        
        //posicionamiento del arma
        if (exists(mi_arma))
            get_real_point(1, &temp_x, &temp_y);  //punto de salida
            //buscamos desplazamiento en pixels
            temp_x -= x;
            temp_y -= y;
            mi_arma.x2 = x2 + temp_x;
            mi_arma.y2 = y2 + temp_y;
            mi_arma.z = z + 1;
            mi_arma.flags = flags;
            tscroll_get_screen_position(&id_tscroll, mi_arma.x2, mi_arma.y2, &mi_arma.x, &mi_arma.y);
        end
        
        //parpadeo de invencible: cambia cada 4 frames, y comprobamos si es par (se ve) o impar (no se ve)
        //debe ser aqui, pues el disparo depende del gráfico
        if ((info_prota.p_invencible & 4) == 4) graph = 0; end
        
        //Se guarda el tile anterior, por si cambia de tile, por ejemplo, a uno de agua
        //prota_tile_ant = p_dur[1][1];
        prota_tile_ant = obtener_tile(&durezas, info_prota.p_tilex, info_prota.p_tiley, 0);

        frame;
    end
end
