process dragon_part (file, graph, x2, y2, z)
private
    int temp;
begin
    energia = 30;
    
    switch (graph)
    case 2,3:
        loop
            if (exists(info_prota.id_prota))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 4;
                    info_prota.dano_exp = 2;
                    
                    if (info_prota.id_prota.x > x) info_prota.dano_vel_horiz = 30;
                    else info_prota.dano_vel_horiz = -30;
                    end
                    //say(itoa(info_prota.id_prota.x) + " " + itoa(x));
                end
            end
            frame;
        end
    end
    case 6:
        loop
            if (exists(info_prota.id_prota))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 2;
                    info_prota.dano_exp = 2;
                    
                    if (info_prota.id_prota.x > x) info_prota.dano_vel_horiz = 30;
                    else info_prota.dano_vel_horiz = -30;
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
    case 7,8:
        loop
            temp = collision(type normal_shot);
            while (temp != 0)
                temp.energia = 0;
                temp = collision(type normal_shot);
            end
            frame;
        end
    end
    default:
        signal(id, s_freeze);
        frame;
    end
    end //switch
end


process dragon_body (file, graph, x2, y2, z)
private
    int dragon_id[9];
    int x_orig, y_orig;
    
    int enem_estado;        //0: cabeceando
                            //1: cambio de color
                            //2: abre boca para disparo
                            //3: disparo básico (3 bolas / homing)
                            //4: disparo fuerte (lluvia de fuego / megarrayo)
                            //5: comer
                            //6: dolor
    int enem_estado2;
    int cont_estado;
    
    double temp_x, temp_y;
    double temp_x2, temp_y2;
    int temp_disp1, temp_disp2;
    int temp_angle;
    int temp_espada;
    int cont1;
    int cont2;
begin
    //x_orig = 3680 - 320;
    //y_orig = 176 - 240;
    x_orig = x2 - 68;
    y_orig = y2 - 68;
    dragon_id[0] = dragon_part(file, 2, x2, y2 - 190, 1);   //cabeza
    dragon_id[1] = dragon_part(file, 4, x2, y2 - 190, 2);   //boca
    dragon_id[2] = dragon_part(file, 7, x2, y2 - 190, 3);   //cabeza dur
    dragon_id[3] = dragon_part(file, 8, x2, y2 - 190, 4);   //boca dur
    dragon_id[4] = dragon_part(file, 5, x2, y2 - 190, 5);   //cuello
    dragon_id[5] = dragon_part(file, 5, x2, y2 - 190, 6);   //cuello
    dragon_id[6] = dragon_part(file, 5, x2, y2 - 190, 7);   //cuello
    dragon_id[7] = dragon_part(file, 5, x2, y2 - 190, 8);   //cuello
    //dragon_id[8] = dragon_part(file, 5, x2, y2 - 190, 8);   //cuello
    dragon_id[9] = dragon_part(file, 6, x2, y2 - 190, 1);   //brazo
    dragon_id[9].angle = -90000;
    
    //write_var(0, 320, 0, 2, dragon_id[0].energia);
    
	//Dragon rising
    cont1 = 0;
    while (cont1 < 68)
        cont1++;
        x2--;
        y2--;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        get_real_point(1, &temp_x, &temp_y);
        dragon_id[0].x = x - cont1;
        dragon_id[0].y = temp_y - 70;
        dragon_id[0].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[0].x, dragon_id[0].y) + 180000;
        dragon_id[1].x = x - cont1;
        dragon_id[1].y = temp_y - 70;
        dragon_id[1].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[0].x, dragon_id[0].y) + 180000;
        dragon_id[2].x = x - cont1;
        dragon_id[2].y = temp_y - 70;
        dragon_id[2].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[0].x, dragon_id[0].y) + 180000;
        dragon_id[3].x = x - cont1;
        dragon_id[3].y = temp_y - 70;
        dragon_id[3].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[0].x, dragon_id[0].y) + 180000;
                                      
        temp_x2 = temp_x - dragon_id[0].x;
        temp_y2 = temp_y - dragon_id[0].y;
        for (cont2 = 0; cont2 < 4; cont2++)
            dragon_id[4 + cont2].x = temp_x - ((temp_x2 * cont2) / 4);
            dragon_id[4 + cont2].y = temp_y - ((temp_y2 * cont2) / 4);
        end
        
        get_real_point(2, &temp_x, &temp_y);
        dragon_id[9].x = temp_x;
        dragon_id[9].y = temp_y;
        dragon_id[9].angle = near_angle(dragon_id[9].angle, 180000, 1500);
        
        frame;
    end
    
	//Waiting
    cont1 = 0;
    prota_control = 1;
    while (cont1 < 200)
        dragon_id[0].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[0].x, dragon_id[0].y) + 180000;
        dragon_id[1].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[1].x, dragon_id[1].y) + 180000;
        dragon_id[2].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[2].x, dragon_id[2].y) + 180000;
        dragon_id[3].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[3].x, dragon_id[3].y) + 180000;
        
        cont1++;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
	//Inicializando datos del dragón
    energia = 400;
    enem_ener_interface(id);
    get_real_point(1, &temp_x2, &temp_y2);
    temp_x2 *= 10;
    temp_y2 *= 10;
    //x_orig *= 10;
    //y_orig *= 10;
    for (cont2 = 0; cont2 < 8; cont2++)
        dragon_id[cont2].resolution = 10;
        dragon_id[cont2].x *= 10;
        dragon_id[cont2].y *= 10;
    end
    
	//COMIENZA EL COMBATE
    while (energia > 0)
        switch (enem_estado)
        case 0:                     //cabeceando
            if (cont_estado == 0)
                temp_x = rand(1600, 3000);
                temp_y = rand(600, 1100);
                cont_estado = 200;
            end
            dragon_id[0].x += (temp_x - dragon_id[0].x) / 50;
            dragon_id[0].y += (temp_y - dragon_id[0].y) / 50;
            dragon_id[1].x += (temp_x - dragon_id[1].x) / 50;
            dragon_id[1].y += (temp_y - dragon_id[1].y) / 50;
            dragon_id[2].x += (temp_x - dragon_id[2].x) / 50;
            dragon_id[2].y += (temp_y - dragon_id[2].y) / 50;
            dragon_id[3].x += (temp_x - dragon_id[3].x) / 50;
            dragon_id[3].y += (temp_y - dragon_id[3].y) / 50;
            if ( (abs(temp_x - dragon_id[0].x) < 50) && (abs(temp_y - dragon_id[0].y) < 50) )
                temp_x = rand(1600, 3000);
                temp_y = rand(600, 1100);
            end
            
            dragon_id[0].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
											dragon_id[0].x / 10, dragon_id[0].y / 10) + 180000;
            dragon_id[1].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
											dragon_id[1].x / 10, dragon_id[1].y / 10) + 180000;
            dragon_id[2].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
											dragon_id[2].x / 10, dragon_id[2].y / 10) + 180000;
            dragon_id[3].angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
											dragon_id[3].x / 10, dragon_id[3].y / 10) + 180000;
                                          
            //temp_x2 = temp_x - dragon_id[0].x;
            //temp_y2 = temp_y - dragon_id[0].y;
            for (cont2 = 0; cont2 < 4; cont2++)
                dragon_id[4 + cont2].x = temp_x2 + (((dragon_id[0].x - temp_x2) * cont2) / 4);
                dragon_id[4 + cont2].y = temp_y2 + (((dragon_id[0].y - temp_y2) * cont2) / 4);
                //dragon_id[4 + cont2].x = temp_x - ((temp_x2 * cont2) / 3);
                //dragon_id[4 + cont2].y = temp_y - ((temp_y2 * cont2) / 3);
            end
            
            cont_estado--;
            if (cont_estado == 1)
                cont_estado = 0;
                enem_estado = rand(2, 5);
                enem_estado2 = 0;
            end
        end
        case 1:                 //cambiando color
            switch (enem_estado2)
            case 0:
                cont_estado = rand(180, 221);
                enem_estado2 = 1;
                cont1 = 0;
            end
            case 1:
                cont1++;
                dragon_id[0].graph = (cont1 & 1) + 2;
                temp_angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[0].x / 10, dragon_id[0].y / 10) + 180000;
                
                dragon_id[0].angle = near_angle(dragon_id[0].angle, temp_angle, 2000);
                dragon_id[1].angle = near_angle(dragon_id[1].angle, temp_angle, 2000);
                dragon_id[2].angle = near_angle(dragon_id[2].angle, temp_angle, 2000);
                dragon_id[3].angle = near_angle(dragon_id[3].angle, temp_angle, 2000);
                if (cont1 == cont_estado)
                    cont1 = 0;
                    cont_estado = 0;
                    enem_estado = 0;
                    enem_estado2 = 0;
                end
            end
            end //switch
        end
        case 2:                 //ataque cargado
            switch (enem_estado2)
            case 0:             //posicionando
                temp_x = 2100;
                if (exists(info_prota.id_prota)) temp_y = (info_prota.id_prota.y - 8) * 10; end
                
                dragon_id[0].x += (temp_x - dragon_id[0].x) / 50;
                dragon_id[0].y += (temp_y - dragon_id[0].y) / 50;
                dragon_id[1].x += (temp_x - dragon_id[1].x) / 50;
                dragon_id[1].y += (temp_y - dragon_id[1].y) / 50;
                dragon_id[2].x += (temp_x - dragon_id[2].x) / 50;
                dragon_id[2].y += (temp_y - dragon_id[2].y) / 50;
                dragon_id[3].x += (temp_x - dragon_id[3].x) / 50;
                dragon_id[3].y += (temp_y - dragon_id[3].y) / 50;
                
                dragon_id[0].angle = near_angle(dragon_id[0].angle, 135000, 1000);
                dragon_id[1].angle = near_angle(dragon_id[1].angle, 225000, 1000);
                dragon_id[2].angle = near_angle(dragon_id[2].angle, 135000, 1000);
                dragon_id[3].angle = near_angle(dragon_id[3].angle, 225000, 1000);
                
                for (cont2 = 0; cont2 < 4; cont2++)
                    dragon_id[4 + cont2].x = temp_x2 + (((dragon_id[0].x - temp_x2) * cont2) / 4);
                    dragon_id[4 + cont2].y = temp_y2 + (((dragon_id[0].y - temp_y2) * cont2) / 4);
                end
                
                if ( (abs(temp_x - dragon_id[0].x) < 50) && (abs(temp_y - dragon_id[0].y) < 50) &&
                     (dragon_id[0].angle == 135000) )
                    enem_estado2 = 1;
                end
                
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x - 60)) < 60) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y)) < 60)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            case 1:         //persiguiendo
                if (exists(info_prota.id_prota))
                    dragon_id[0].y = (info_prota.id_prota.y - 8) * 10;
                    dragon_id[1].y = (info_prota.id_prota.y - 8) * 10;
                    dragon_id[2].y = (info_prota.id_prota.y - 8) * 10;
                    dragon_id[3].y = (info_prota.id_prota.y - 8) * 10;
                end
                for (cont2 = 0; cont2 < 4; cont2++)
                    dragon_id[4+cont2].x = temp_x2 + (((dragon_id[0].x - temp_x2) * cont2) / 4);
                    dragon_id[4+cont2].y = temp_y2 + (((dragon_id[0].y - temp_y2) * cont2) / 4);
                end
                
                cont_estado++;
                if (cont_estado == 50)
                    cont_estado = 0;
                    enem_estado2 = 2;
                end
                
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x - 60)) < 60) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y)) < 60)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            case 2:         //disparando
                cont_estado++;
                switch (cont_estado)
                case 50:
                    if (dragon_id[0].graph == 2)
                        dragon_fire (file, 9, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 45000, 60);
                    else
                        dragon_laser(file, 10, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 45000);
                    end
                end
                case 100,150,200:
                    if (dragon_id[0].graph == 2)
                        dragon_fire (file, 9, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 45000, 60);
                    end
                end
                case 300:
                    enem_estado2 = 3;
                    cont_estado = 0;
                end
                end //switch
                
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x - 60)) < 60) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y)) < 60)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            case 3:         //cerrando la boca
                dragon_id[0].angle = near_angle(dragon_id[0].angle, 180000, 1000);
                dragon_id[1].angle = near_angle(dragon_id[1].angle, 180000, 1000);
                dragon_id[2].angle = near_angle(dragon_id[2].angle, 180000, 1000);
                dragon_id[3].angle = near_angle(dragon_id[3].angle, 180000, 1000);
                if (dragon_id[0].angle == 180000)
                    enem_estado = rand(0, 1);
                    enem_estado2 = 0;
                    cont_estado = 0;
                end
                
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x - 40)) < 40) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y)) < 40)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            
            end //switch
        end
        case 3:		//Dsiparo básico (3 bolas de fuego / homing)
            switch (cont_estado)
            case 0:
                temp_angle = 0;
            end
            case 1..50:
                if (temp_angle < 45000) temp_angle += 1000; end
            end
            case 75:
                if (dragon_id[0].graph == 3) enem_estado2 = 1; end
            end
            case 100:
                if (dragon_id[0].graph == 2)
                    dragon_fire (file, 9, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 45000, 60);
                else
                    //dragon_laser(file, 10, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 45000);
                    dragon_homing(file, 11, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 45000);
                end
                enem_estado2 = 0;
            end
            case 150,200,250:
                if (dragon_id[0].graph == 2)
                    dragon_fire (file, 9, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 45000, 60);
                end
            end
            case 251..300:
                if (temp_angle > 0) temp_angle -= 1000; end
            end
            case 301:
                enem_estado = rand(0, 1);
                enem_estado2 = 0;
                cont_estado = 0;
            end
            end //switch
            cont_estado++;
            
            if (enem_estado2 == 0)
                dragon_id[0].angle = near_angle(dragon_id[0].angle,
												fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
												dragon_id[0].x / 10, dragon_id[0].y / 10) +
												180000 - temp_angle, 1000);
                dragon_id[1].angle = near_angle(dragon_id[1].angle,
												fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
												dragon_id[1].x / 10, dragon_id[1].y / 10) +
												180000 + temp_angle, 1000);
                dragon_id[2].angle = near_angle(dragon_id[2].angle,
												fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
												dragon_id[2].x / 10, dragon_id[2].y / 10) +
												180000 - temp_angle, 1000);
                dragon_id[3].angle = near_angle(dragon_id[3].angle,
												fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
												dragon_id[3].x / 10, dragon_id[3].y / 10) +
												180000 + temp_angle, 1000);
            end
            
            /*cont1 = get_id(type dragon_fire);
            if (cont1 != 0) signal(cont1, s_kill); end
            dragon_fire (file, 9, dragon_id[0].x + (80 * cos(dragon_id[0].angle - temp_angle)),
                                dragon_id[0].y + (80 * sin(dragon_id[0].angle - temp_angle)),
                         dragon_id[0].angle + 45000, 0);*/
            //choque con disparos
            cont1 = get_id(type normal_shot);
            while (cont1 != 0)
                if ( (abs((cont1.x * 10) - (dragon_id[0].x + (80 * cos(dragon_id[0].angle - temp_angle)))) < 80) &&
                     (abs((cont1.y * 10) - (dragon_id[0].y + (80 * sin(dragon_id[0].angle - temp_angle)))) < 80)    )
                    dragon_id[0].energia -= cont1.energia;
                    cont1.energia = 0;
                    if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                        dragon_id[0].mi_temblor.energia = 3;
                        dragon_id[1].mi_temblor.energia = 3;
                        dragon_id[2].mi_temblor.energia = 3;
                        dragon_id[3].mi_temblor.energia = 3;
                    else
                        dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                        dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                        dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                        dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                    end
                end
                cont1 = get_id(type normal_shot);
            end
            if (dragon_id[0].energia <= 0)
                enem_estado = 6;
                enem_estado2 = 0;
                cont_estado = 0;
                dragon_id[0].energia = 30;
            end
        end
        case 4:		//Disparo fuerte (lluvia de fuego, megarrayo)
            if (dragon_id[0].graph == 2)
                switch (cont_estado)
                case 0..70:
                    temp_x = 3100;
                    temp_y = 650;
                    temp_angle = 135000;
                    dragon_id[9].angle = near_angle(dragon_id[9].angle, 45000, 1000);
                    
                    if (dragon_id[0].angle > temp_angle - 15000) dragon_id[0].angle -= 2000; end
                    if (dragon_id[1].angle > temp_angle + 15000) dragon_id[1].angle -= 2000; end
                    if (dragon_id[2].angle > temp_angle - 15000) dragon_id[2].angle -= 2000; end
                    if (dragon_id[3].angle > temp_angle + 15000) dragon_id[3].angle -= 2000; end
                end
                case 100:
                    dragon_fire (file, 9, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 15000, 60);
                end
                case 150,175,200,225,250,275,300,325,350:
                    dragon_fire (file, 9, (160 * rand(0, 14)) + 80, -100, -90000, 40);
                end
                case 400:
                    enem_estado = rand(0, 1);
                    enem_estado2 = 0;
                    cont_estado = 0;
                end
                end //switch
            
                if (cont_estado > 100)
                    temp_x = 2520;
                    temp_y = 600;
                    temp_angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
											dragon_id[0].x / 10, dragon_id[0].y / 10) + 180000;
                    dragon_id[9].angle = near_angle(dragon_id[9].angle, 180000, 1000);
                    
                    dragon_id[0].angle = near_angle(dragon_id[0].angle, temp_angle, 2000);
                    dragon_id[1].angle = near_angle(dragon_id[1].angle, temp_angle, 2000);
                    dragon_id[2].angle = near_angle(dragon_id[2].angle, temp_angle, 2000);
                    dragon_id[3].angle = near_angle(dragon_id[3].angle, temp_angle, 2000);
                end
                
            else
                switch (cont_estado)
                case 0: temp_angle = 0; end
                case 1..50:
					if (temp_angle < 45000)
						temp_angle += 1000;
					end
				end
                case 75: enem_estado2 = 1; end
                case 100:
                    dragon_laser(file, 10, dragon_id[0].x, dragon_id[0].y, dragon_id[0].angle + 45000);
                    enem_estado2 = 0;
                end
                case 251..300:
                    if (temp_angle > 0) temp_angle -= 1000; end
                end
                case 301:
                    enem_estado = rand(0, 1);
                    enem_estado2 = 0;
                    cont_estado = 0;
                end
                end //switch
                
                if (enem_estado2 == 0)
                    dragon_id[0].angle = near_angle(dragon_id[0].angle,
													fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
													dragon_id[0].x / 10, dragon_id[0].y / 10) +
													180000 - temp_angle, 1000);
                    dragon_id[1].angle = near_angle(dragon_id[1].angle,
													fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
													dragon_id[1].x / 10, dragon_id[1].y / 10) +
													180000 + temp_angle, 1000);
                    dragon_id[2].angle = near_angle(dragon_id[2].angle,
													fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
													dragon_id[2].x / 10, dragon_id[2].y / 10) +
													180000 - temp_angle, 1000);
                    dragon_id[3].angle = near_angle(dragon_id[3].angle,
													fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
													dragon_id[3].x / 10, dragon_id[3].y / 10) + 
													180000 + temp_angle, 1000);
                end
                
                //choque con disparos
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x + (80 * cos(dragon_id[0].angle - temp_angle)))) < 80) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y + (80 * sin(dragon_id[0].angle - temp_angle)))) < 80)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            cont_estado++;
        end
        
        case 5:		//Comer
            switch (enem_estado2)
            case 0:             //posicionando
                temp_x = 2100;
                if (exists(info_prota.id_prota)) temp_y = (info_prota.id_prota.y - 8) * 10; end
                
                dragon_id[0].x += (temp_x - dragon_id[0].x) / 50;
                dragon_id[0].y += (temp_y - dragon_id[0].y) / 50;
                dragon_id[1].x += (temp_x - dragon_id[1].x) / 50;
                dragon_id[1].y += (temp_y - dragon_id[1].y) / 50;
                dragon_id[2].x += (temp_x - dragon_id[2].x) / 50;
                dragon_id[2].y += (temp_y - dragon_id[2].y) / 50;
                dragon_id[3].x += (temp_x - dragon_id[3].x) / 50;
                dragon_id[3].y += (temp_y - dragon_id[3].y) / 50;
                
                dragon_id[0].angle = near_angle(dragon_id[0].angle, 135000, 1000);
                dragon_id[1].angle = near_angle(dragon_id[1].angle, 225000, 1000);
                dragon_id[2].angle = near_angle(dragon_id[2].angle, 135000, 1000);
                dragon_id[3].angle = near_angle(dragon_id[3].angle, 225000, 1000);
                
                for (cont2 = 0; cont2 < 4; cont2++)
                    dragon_id[4 + cont2].x = temp_x2 + (((dragon_id[0].x - temp_x2) * cont2) / 4);
                    dragon_id[4 + cont2].y = temp_y2 + (((dragon_id[0].y - temp_y2) * cont2) / 4);
                end
                
                if ( (abs(temp_x - dragon_id[0].x) < 50) && (abs(temp_y - dragon_id[0].y) < 50) && 
                     (dragon_id[0].angle == 135000) )
                    enem_estado2 = 1;
                end
                
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x - 60)) < 60) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y)) < 60)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            case 1:         //persiguiendo
                if (exists(info_prota.id_prota))
                    dragon_id[0].y = (info_prota.id_prota.y - 8) * 10;
                    dragon_id[1].y = (info_prota.id_prota.y - 8) * 10;
                    dragon_id[2].y = (info_prota.id_prota.y - 8) * 10;
                    dragon_id[3].y = (info_prota.id_prota.y - 8) * 10;
                end
                for (cont2 = 0; cont2 < 4; cont2++)
                    dragon_id[4 + cont2].x = temp_x2 + (((dragon_id[0].x - temp_x2) * cont2) / 4);
                    dragon_id[4 + cont2].y = temp_y2 + (((dragon_id[0].y - temp_y2) * cont2) / 4);
                end
                
                cont_estado++;
                if (cont_estado == 50)
                    cont_estado = 0;
                    enem_estado2 = 2;
                end
                
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x - 60)) < 60) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y)) < 60)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            case 2:         //comiendo
                temp_x = 700;
                if (exists(info_prota.id_prota)) temp_y = (info_prota.id_prota.y - 8) * 10; end
                
                dragon_id[0].x += (temp_x - dragon_id[0].x) / 20;
                dragon_id[0].y += (temp_y - dragon_id[0].y) / 50;
                dragon_id[1].x += (temp_x - dragon_id[1].x) / 20;
                dragon_id[1].y += (temp_y - dragon_id[1].y) / 50;
                dragon_id[2].x += (temp_x - dragon_id[2].x) / 20;
                dragon_id[2].y += (temp_y - dragon_id[2].y) / 50;
                dragon_id[3].x += (temp_x - dragon_id[3].x) / 20;
                dragon_id[3].y += (temp_y - dragon_id[3].y) / 50;
                
                for (cont2 = 0; cont2 < 4; cont2++)
                    dragon_id[4 + cont2].x = temp_x2 + (((dragon_id[0].x - temp_x2) * cont2) / 4);
                    dragon_id[4 + cont2].y = temp_y2 + (((dragon_id[0].y - temp_y2) * cont2) / 4);
                end
                
                if ((dragon_id[0].x - temp_x) < 50)
					cont_estado = 0;
					enem_estado2 = 3;
				end
                
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x - 60)) < 60) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y)) < 60)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            case 3:         //cerrando la boca
                dragon_id[0].angle = near_angle(dragon_id[0].angle, 180000, 1000);
                dragon_id[1].angle = near_angle(dragon_id[1].angle, 180000, 1000);
                dragon_id[2].angle = near_angle(dragon_id[2].angle, 180000, 1000);
                dragon_id[3].angle = near_angle(dragon_id[3].angle, 180000, 1000);
                if (dragon_id[0].angle == 180000)
                    enem_estado = rand(0, 1);
                    enem_estado2 = 0;
                    cont_estado = 0;
                end
                
                cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x - 40)) < 40) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y)) < 40)    )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                            dragon_id[1].mi_temblor.energia = 3;
                            dragon_id[2].mi_temblor.energia = 3;
                            dragon_id[3].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
                            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
                            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end
                if (dragon_id[0].energia <= 0)
                    enem_estado = 6;
                    enem_estado2 = 0;
                    cont_estado = 0;
                    dragon_id[0].energia = 30;
                end
            end
            
            end //switch
        end
        
        case 6:		//dolor
            if (cont_estado < 70)
                temp_x = 3100;
                temp_y = 650;
                temp_angle = 60000;
                dragon_id[9].angle = near_angle(dragon_id[9].angle, 45000, 1000);
                
                if (dragon_id[0].angle > temp_angle - 45000) dragon_id[0].angle -= 2000; end
                if (dragon_id[1].angle > temp_angle + 45000) dragon_id[1].angle -= 2000; end
                if (dragon_id[2].angle > temp_angle - 45000) dragon_id[2].angle -= 2000; end
                if (dragon_id[3].angle > temp_angle + 45000) dragon_id[3].angle -= 2000; end
                /*dragon_id[0].angle = near_angle(dragon_id[0].angle, temp_angle - 45000, 2000);
                dragon_id[1].angle = near_angle(dragon_id[1].angle, temp_angle + 45000, 2000);
                dragon_id[2].angle = near_angle(dragon_id[2].angle, temp_angle - 45000, 2000);
                dragon_id[3].angle = near_angle(dragon_id[3].angle, temp_angle + 45000, 2000);*/
            elsif (cont_estado > 200)
                temp_x = 2520;
                temp_y = 600;
                temp_angle = fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
										dragon_id[0].x / 10, dragon_id[0].y / 10) + 180000;
                dragon_id[9].angle = near_angle(dragon_id[9].angle, 180000, 1000);
                
                if (dragon_id[0].angle < temp_angle - 45000) dragon_id[0].angle += 2000; end
                if (dragon_id[1].angle < temp_angle + 45000) dragon_id[1].angle += 2000; end
                if (dragon_id[2].angle < temp_angle - 45000) dragon_id[2].angle += 2000; end
                if (dragon_id[3].angle < temp_angle + 45000) dragon_id[3].angle += 2000; end
                /*dragon_id[0].angle = near_angle(dragon_id[0].angle, temp_angle, 2000);
                dragon_id[1].angle = near_angle(dragon_id[1].angle, temp_angle, 2000);
                dragon_id[2].angle = near_angle(dragon_id[2].angle, temp_angle, 2000);
                dragon_id[3].angle = near_angle(dragon_id[3].angle, temp_angle, 2000);*/
            end
            cont_estado++;
            
            dragon_id[0].x += (temp_x - dragon_id[0].x) / 50;
            dragon_id[0].y += (temp_y - dragon_id[0].y) / 50;
            dragon_id[1].x += (temp_x - dragon_id[1].x) / 50;
            dragon_id[1].y += (temp_y - dragon_id[1].y) / 50;
            dragon_id[2].x += (temp_x - dragon_id[2].x) / 50;
            dragon_id[2].y += (temp_y - dragon_id[2].y) / 50;
            dragon_id[3].x += (temp_x - dragon_id[3].x) / 50;
            dragon_id[3].y += (temp_y - dragon_id[3].y) / 50;
            
            
            for (cont2 = 0; cont2 < 4; cont2++)
                dragon_id[4 + cont2].x = temp_x2 + (((dragon_id[0].x - temp_x2) * cont2) / 4);
                dragon_id[4 + cont2].y = temp_y2 + (((dragon_id[0].y - temp_y2) * cont2) / 4);
            end
            
            if (cont_estado == 300)
                enem_estado = rand(0, 1);
                enem_estado2 = 0;
                cont_estado = 0;
                dragon_id[0].energia = 30;
            end
        end
        end //switch
        
                //para colisiones, falla con el ángulo
                /*cont1 = get_id(type normal_shot);
                while (cont1 != 0)
                    if ( (abs((cont1.x * 10) - (dragon_id[0].x + (60 * cos(dragon_id[0].angle)))) < 60) &&
                         (abs((cont1.y * 10) - (dragon_id[0].y + (60 * sin(dragon_id[0].angle)))) < 60) )
                        dragon_id[0].energia -= cont1.energia;
                        cont1.energia = 0;
                        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
                            dragon_id[0].mi_temblor.energia = 3;
                        else
                            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
                        end
                    end
                    cont1 = get_id(type normal_shot);
                end*/
        
        //movimiento del brazo
        if (enem_estado != 6)
            temp_disp1 = 0;
            temp_disp2 = get_id(type normal_shot);
            while (temp_disp2 != 0)
                if ((temp_disp1 != 0) && exists(temp_disp1) && (temp_disp1.energia>0))
                    if (temp_disp2.x > temp_disp1.x)
                        temp_disp1 = temp_disp2;
                    end
                else
                    temp_disp1 = temp_disp2;
                end
                temp_disp2 = get_id(type normal_shot);
            end
            
            if (temp_disp1 != 0)
                dragon_id[9].angle = near_angle(dragon_id[9].angle,
												fget_angle(temp_disp1.x, temp_disp1.y,
															dragon_id[9].x, dragon_id[9].y) +
												180000, 2000);
            else
                if (exists(info_prota.id_prota))
                    dragon_id[9].angle = near_angle(dragon_id[9].angle,
													fget_angle(info_prota.id_prota.x, info_prota.id_prota.y,
													dragon_id[9].x, dragon_id[9].y) +
													180000, 2000);
                end
            end
        else
            //impacto con las balas
            temp_disp1 = collision(type normal_shot);
            while (temp_disp1 != 0)
                energia -= temp_disp1.energia;
                temp_disp1.energia = 0;
                if ((mi_temblor != 0) && exists(mi_temblor))
                    mi_temblor.energia = 3;
                else
                    mi_temblor = enem_temblor2(id, 3);
                end
                temp_disp1 = collision(type normal_shot);
            end
			
            temp_disp1 = collision(type espadazo);
            if ((temp_disp1 != 0) && (temp_disp1 != temp_espada))
                energia -= temp_disp1.energia;
                if ((mi_temblor != 0) && exists(mi_temblor))
                    mi_temblor.energia = 3;
                else
                    mi_temblor = enem_temblor(id, 3);
                end
                temp_espada = temp_disp1;
            end
            
            //evitar que se desplace el cuerpo de su posición
            if ((mi_temblor != 0) && !exists(mi_temblor))
                mi_temblor = 0;
                x2 = x_orig;
                y2 = y_orig;
                tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
            end
        end
        
        frame;
    end
    
    fade(255, 255, 255, 255, 100);
    frame(300);
    fade_on(100);
    
    for (cont1 = 0; cont1 < 8; cont1++)
        signal(dragon_id[cont1], s_freeze);
    end
    signal(dragon_id[9], s_freeze);
    frame(5000);
    prota_control = 0;
    cont_estado = 0;
    while (cont_estado < 390)
        if ((mi_temblor != 0) && exists(mi_temblor))
            mi_temblor.energia = 3;
            dragon_id[9].mi_temblor.energia = 3;
        else
            mi_temblor = enem_temblor2(id, 3);
            dragon_id[9].mi_temblor = enem_temblor2(dragon_id[9], 3);
        end
        if ((dragon_id[0].mi_temblor != 0) && exists(dragon_id[0].mi_temblor))
            dragon_id[0].mi_temblor.energia = 3;
            dragon_id[1].mi_temblor.energia = 3;
            dragon_id[2].mi_temblor.energia = 3;
            dragon_id[3].mi_temblor.energia = 3;
            dragon_id[4].mi_temblor.energia = 3;
            dragon_id[5].mi_temblor.energia = 3;
            dragon_id[6].mi_temblor.energia = 3;
            dragon_id[7].mi_temblor.energia = 3;
        else
            dragon_id[0].mi_temblor = enem_xtemblor(dragon_id[0], 3, 10);
            dragon_id[1].mi_temblor = enem_xtemblor(dragon_id[1], 3, 10);
            dragon_id[2].mi_temblor = enem_xtemblor(dragon_id[2], 3, 10);
            dragon_id[3].mi_temblor = enem_xtemblor(dragon_id[3], 3, 10);
            dragon_id[4].mi_temblor = enem_xtemblor(dragon_id[4], 3, 10);
            dragon_id[5].mi_temblor = enem_xtemblor(dragon_id[5], 3, 10);
            dragon_id[6].mi_temblor = enem_xtemblor(dragon_id[6], 3, 10);
            dragon_id[7].mi_temblor = enem_xtemblor(dragon_id[7], 3, 10);
        end
        
        if (cont_estado > 150)
            y++;
            for (cont1 = 0; cont1 < 8; cont1++)
                dragon_id[cont1].y += 10;
            end
            dragon_id[9].y++;
        end
        
        cont_estado++;
        frame;
    end
    
    for (cont1 = 0; cont1 < 8; cont1++)
        signal(dragon_id[cont1], s_kill);
    end
    signal(dragon_id[9], s_kill);
    prota_control = 1;
end