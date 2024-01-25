//************************************************************************************
//  FUNCIONES AUXILIARES
//************************************************************************************
function init_weapons ()
begin
    //no_weapon
    armas_level[0][1] = 10;   //max nivel 1 (si se sobrepasa, el arma sube a nivel 2)
    armas_level[0][2] = 25;   //max nivel 2 (si se sobrepasa, el arma sube a nivel 3)
    armas_level[0][3] = 35;   //max nivel 3 (no se puede sobrepasar)
    armas_damage[0][0] = 0;   //daño nivel 1
    armas_damage[0][1] = 0;   //daño nivel 2
    armas_damage[0][2] = 0;   //daño nivel 3
    
    //normal shot
    armas_level[1][1] = 20;   //max nivel 1 (si se sobrepasa, el arma sube a nivel 2) 15
    armas_level[1][2] = 50;   //max nivel 2 (si se sobrepasa, el arma sube a nivel 3) 25
    armas_level[1][3] = 60;   //max nivel 3 (no se puede sobrepasar) 35
    armas_damage[1][0] = 2;   //daño nivel 1
    armas_damage[1][1] = 3;   //daño nivel 2
    armas_damage[1][2] = 5;   //daño nivel 3
    
    //espada
    armas_level[2][1] = 35;   //max nivel 1 (si se sobrepasa, el arma sube a nivel 2)
    armas_level[2][2] = 75;   //max nivel 2 (si se sobrepasa, el arma sube a nivel 3)
    armas_level[2][3] = 85;   //max nivel 3 (no se puede sobrepasar)
    armas_damage[2][0] = 2;   //daño nivel 1
    armas_damage[2][1] = 4;   //daño nivel 2
    armas_damage[2][2] = 8;   //daño nivel 3
    
    //gatling
    armas_level[3][1] = 30;   //max nivel 1 (si se sobrepasa, el arma sube a nivel 2)
    armas_level[3][2] = 60;   //max nivel 2 (si se sobrepasa, el arma sube a nivel 3)
    armas_level[3][3] = 75;   //max nivel 3 (no se puede sobrepasar)
    armas_damage[3][0] = 1;   //daño nivel 1
    armas_damage[3][1] = 2;   //daño nivel 2
    armas_damage[3][2] = 4;   //daño nivel 3
    
    //bombas
    armas_level[4][1] = 5;    //max nivel 1 (si se sobrepasa, el arma sube a nivel 2)
    armas_level[4][2] = 10;   //max nivel 2 (si se sobrepasa, el arma sube a nivel 3)
    armas_level[4][3] = 15;   //max nivel 3 (no se puede sobrepasar)
    armas_damage[4][0] = 20;   //daño nivel 1
    armas_damage[4][1] = 20;   //daño nivel 2
    armas_damage[4][2] = 25;   //daño nivel 3
    
    //inicializacion total
    armas_level[0][0] = 0;
    armas_level[1][0] = 0;
    armas_level[2][0] = 0;
    armas_level[3][0] = 0;
    armas_level[4][0] = 0;
    
end

function say_weapons ()
private
	int cont1;
	int cont2;
begin
	for (cont1 = 0; cont1 <= CTE_LAST_WEAPON; cont1++)
		say("ARMA " + cont1 + ":  Nivel 0: " + armas_level[cont1][0]);
		for (cont2 = 1; cont2 <= 3; cont2++)
			say("         Nivel " + cont2 + ": " + armas_level[cont1][cont2]);
		end
	end
end

//************************************************************************************
//  EXPLOSIONES DEL DISPARO
//************************************************************************************
process normal_explosion (file, int graph1, int graph2, x2, y2)
private
    int cont;
begin
    priority = -99;
    z = -99;
    graph = graph1;
    tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
    frame;
    while (graph < graph2)
        if (cont == 3)
            graph++;
            cont = 0;
        else
            cont++;
        end
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
end
    

//************************************************************************************
//  DISPAROS DEL ARMA
//************************************************************************************
process normal_shot (file, int ns_animation, x2, y2, angle2, energia, int shot_vel, int ns_distance)
private
    int x3, y3;
    int resolution3;
    int vel_x, vel_y;
    int ns_animation_data[2];
    
    //variables temporales
    int cont;
    int shot_tile;
    int shot_tilex, shot_tiley;
    int shot_offsx, shot_offsy;
begin
    //z = -255;
    z = 1;
    resolution3 = 10;
    x3 = x2 * resolution3;
    y3 = y2 * resolution3;
    vel_x = shot_vel * cos(angle2);
    vel_y = -shot_vel * sin(angle2);
    /*if (angle == 180000)
        angle = 0;
        flags = 1;
    end*/
    switch (angle2)
    case 180000: flags = 1; end
    case 90000: ns_animation += 3; end
    case -90000: ns_animation += 3; flags = 2; end
    end //switch
    //if (angle == 90000) size_y = 150; end
    
    //graph = 501;
    ns_animation_data[0] = search_animation(&armas_animation, ns_animation) + 1;
    ns_animation_data[1] = ns_animation_data[0] + armas_animation[ns_animation_data[0] - 1] - 1;
    ns_animation_data[2] = ns_animation_data[0];
    graph = armas_animation[ns_animation_data[2]];
    loop
        shot_tilex = ((x3 + vel_x) / resolution3) / id_tscroll.tmapa[0].ancho_tile;
        shot_tiley = ((y3 + vel_y) / resolution3) / id_tscroll.tmapa[0].alto_tile;
        shot_offsx = ((x3 + vel_x) / resolution3) % id_tscroll.tmapa[0].ancho_tile;
        shot_offsy = ((y3 + vel_y) / resolution3) % id_tscroll.tmapa[0].alto_tile;
        shot_tile = obtener_tile(&durezas, shot_tilex, shot_tiley, 0);
        
        vel_x = shot_colision_lateral(shot_offsx, shot_offsy, shot_tile, vel_x, resolution3);
        vel_y = shot_colision_vertical(shot_offsx, shot_offsy, shot_tile, vel_y, resolution3);
        
        x3 += vel_x;
        y3 += vel_y;
        
        x2 = x3 / resolution3;
        y2 = y3 / resolution3;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        if (cont == 5)
            cont = 0;
            if (ns_animation_data[2] == ns_animation_data[1])
                ns_animation_data[2] = ns_animation_data[0];
            else
                ns_animation_data[2]++;
            end
            graph = armas_animation[ns_animation_data[2]];
            //say(itoa(graph));
        end
        cont++;
        
        if (energia == 0) break; end
        ns_distance -= shot_vel;
        if (ns_distance < 0) break; end
        //if (region_out(id,0)) break; end
        frame;
    end
    
    energia = 0;
    //animacion explosion
    normal_explosion(file, 200, 203, x2, y2);
    frame;
end

process espadazo (file, x, y, z, int ns_animation, angle, energia)
private
    int ns_animation_data[2];
begin
    ns_animation_data[0] = search_animation(&armas_animation, ns_animation) + 1;
    ns_animation_data[1] = ns_animation_data[0] + armas_animation[ns_animation_data[0] - 1] - 1;
    ns_animation_data[2] = ns_animation_data[0];
    graph = armas_animation[ns_animation_data[2]];
    
    while (ns_animation_data[2] < ns_animation_data[1])
        graph = armas_animation[ns_animation_data[2]];
        ns_animation_data[2]++;
        frame;
    end
end

//************************************************************************************
//  PROCESO PRINCIPAL: ARMA QUE LLEVA ECHO
//************************************************************************************

process arma (int a_id)
private
    int disparos;
    //variables para la espada
    int hijos;
    int angle2;
    
    //variables de datos temporales
    double temp_x1, temp_y1;
    //double temp_x2, temp_y2;
    int temp_angle;             //indica ángulo de disparo
    int temp_anim;              //indica qué animación tendrá el disparo
    int temp_vel;               //indica la velocidad de movimiento de la bala
    //int temp_damag;             //indica que cantidad de daño hará el arma (busca nivel en el array de daño)
begin
    priority = father.priority - 1;
    file = armas_file;
    loop
        while (exists(a_id))
            //el posicionamiento lo controla el proceso padre (prota o prota_moto)
            //priority = a_id - 1;
            
            //cambio de arma
            if (teclas[k_next][2] == 1)
                repeat
                    armas_select++;
                    if (armas_select > CTE_LAST_WEAPON) armas_select = 0; end
                until (armas_get[armas_select])
                armas_curr_level = 0;
                if (armas_level[armas_select][0] >= armas_level[armas_select][1]) armas_curr_level++; end
                if (armas_level[armas_select][0] >= armas_level[armas_select][2]) armas_curr_level++; end
                refresh_interface();
                
                //carga de sonidos
                cambiar_sfx_arma();
            end
            if (teclas[k_previous][2] == 1)
                repeat
                    armas_select--;
                    if (armas_select < 0) armas_select = cte_last_weapon; end
                until (armas_get[armas_select])
                armas_curr_level = 0;
                if (armas_level[armas_select][0] >= armas_level[armas_select][1]) armas_curr_level++; end
                if (armas_level[armas_select][0] >= armas_level[armas_select][2]) armas_curr_level++; end
                refresh_interface();
                
                //carga de sonidos
                cambiar_sfx_arma();
            end
            
            //gráfico del arma
            graph = armas_select * 2;
            //graph=1*2;
            //orientación del arma
            if (teclas[k_up][2] > 0)
                angle = 90000;
                temp_angle = 90000;
            elsif ((teclas[k_down][2] > 0) &&
					((info_prota.estado == CTE_PROTA_ESTADO_SALTANDO) ||
					 (info_prota.estado == CTE_PROTA_ESTADO_CAYENDO)))
					 
                //angle = -90000;
                angle = 0;
                z = a_id.z - 1;
                graph++;
                temp_angle = -90000;
            else
                angle = 0;
                if ((flags & 1) == 1)
					temp_angle = 180000;
				else
					temp_angle = 0;
				end
            end
            
            //disparo
            switch (armas_select)
            case 1:     //normal gun
                if (teclas[k_fire][2] == 1)
                    //get_real_point(0, &temp_x1, &temp_y1);  //referencia
                    get_real_point(father, 1, &temp_x1, &temp_y1);  //punto de salida
                    //buscamos desplazamiento en pixels
                    temp_x1 -= x;
                    temp_y1 -= y;
                    //creamos el disparo en coordenadas del scroll
                    temp_anim = (2 * 3 * armas_select) + armas_curr_level;
                    //say(itoa(temp_anim));
                    normal_shot(file, temp_anim, x2 + temp_x1, y2 + temp_y1, temp_angle, armas_damage[armas_select][armas_curr_level], 60, 1500);
                    normal_explosion(file, 200, 203, x2 + temp_x1, y2 + temp_y1);
                    
                    sound_play(disparo_wav[0][armas_curr_level], 0);
                    temp_anim = 0;
                end
            end
            case 2:
                z = father.z + 1;
                if (disparos > 0)
                    angle2 -= 45000;
                    if (angle2 == -135000)
                        disparos = 0;
                        //if (exists(hijos)) signal(hijos, s_kill); end
                    else
                        angle = angle2;
                        graph = 511;
                        if (exists(hijos))
                            hijos.x = x;
                            hijos.y = y;
                            hijos.angle = angle;
                            hijos.flags = flags;
                        end
                        if ((angle == -45000) && (armas_curr_level == 2))
                            if ((flags & 1) == 1)
								temp_angle = 180000;
							else
								temp_angle = 0;
							end
                            normal_shot(file, (2 * 3 * armas_select) + 3, father.x2, father.y2,
										temp_angle, 2, 70, 1000);
                        end
                    end
                else
                    if (teclas[k_fire][2] == 1) //&& (!get_id(type slash)))
                        temp_anim = 0;
                        angle2 = 135000;
                        angle = angle2;
                        graph = 511;
                        disparos = 1;
                        hijos = espadazo(file, x, y, z, (2 * 3 * armas_select) + armas_curr_level, angle,
											armas_damage[armas_select][armas_curr_level]);
                        sound_play(disparo_wav[0][armas_curr_level], 0);
                    else
                        if (temp_angle == 90000)
                            graph = 511;
                            //angle = 0;
                        end
                    end
                end
            end
            case 3:     //gatling
                if ((teclas[k_fire][2] % (5 + (armas_curr_level))) == 1)
                    //get_real_point(0, &temp_x1, &temp_y1);  //referencia
                    get_real_point(1, &temp_x1, &temp_y1);  //punto de salida
                    //buscamos desplazamiento en pixels
                    temp_x1 -= x;
                    temp_y1 -= y;
                    //creamos el disparo en coordenadas del scroll
                    temp_anim = (2 * 3 * armas_select) + armas_curr_level;
                    //say(itoa(temp_anim));
                    temp_vel = 70 - (armas_curr_level * 15);
                    normal_shot(file, temp_anim, x2 + temp_x1, y2 + temp_y1, temp_angle,
                                armas_damage[armas_select][armas_curr_level], temp_vel, 2700);
                    normal_explosion(file, 200, 203, x2 + temp_x1, y2 + temp_y1);
                    
                    sound_play(disparo_wav[0][armas_curr_level], 0);
                    temp_anim = 0;
                end
            end
            case 4:     //bomb
                if ((teclas[k_fire][2] == 1) && (armas_level[4][0] > 0))    //*********************************
                    cambiar_exp_arma(-1);
                    get_real_point(1, &temp_x1, &temp_y1);  //punto de salida
                    //buscamos desplazamiento en pixels
                    temp_x1 -= x;
                    temp_y1 -= y;
                    //creamos el disparo en coordenadas del scroll
                    //temp_anim = (2 * 3 * armas_select) + armas_curr_level;
                    temp_vel = 40;
                    //temp_angle
                    /*normal_shot(file, temp_anim, x2 + temp_x1, y2 + temp_y1, temp_angle,
								armas_damage[armas_select][armas_curr_level], temp_vel, 2700);*/
                end
            end
            end //switch comprobacion de arma
            
            tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
            frame;
        end
    end
end

//Debe refrescarse el interface para que los cambios tengan efecto.
//No se hace en la función porque el level select no ha hecho el set interface
//que se hace en play level al seleccionar el primer arma, cosa que el juego
//normal ya había hecho en el evento de coger el primer arma, que es donde se
//lama a esta función
function select_first_weapon ()
begin
    repeat
        armas_select++;
        if (armas_select > CTE_LAST_WEAPON) armas_select = 0; end
    until (armas_get[armas_select])
    armas_curr_level = 0;
    if (armas_level[armas_select][0] >= armas_level[armas_select][1]) armas_curr_level++; end
    if (armas_level[armas_select][0] >= armas_level[armas_select][2]) armas_curr_level++; end
    
    
    //carga de sonidos
    cambiar_sfx_arma();
end
