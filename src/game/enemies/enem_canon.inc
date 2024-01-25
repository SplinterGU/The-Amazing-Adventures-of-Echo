process canon (int enem_tx, int enem_ty, file, flags)
private
    int cont_estado;
    double temp_x, temp_y;
    
    int temp;
    int temp_espada;
begin
    priority = -99;
    graph = 1;
    z = 0;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    energia = 100;
    
    if (flags == 1) temp_x = -16; else temp_x = 16; end
    temp_y = -6;
    
    loop
        cont_estado++;
        switch (cont_estado)
        case 150:
			enem_canon_shot(file, 2, x2 + temp_x, y2 + temp_y, flags, 10);
		end
        case 153,156,159,162,165,168,171,174,177:
			enem_canon_shot(file, 3, x2 + temp_x, y2 + temp_y, flags, 10);
		end
        case 180:
			enem_canon_shot(file, 4, x2 + temp_x, y2 + temp_y, flags, 10);
			cont_estado = 0;
		end
        end //switch
        
        //*************************
        //  ZONA DE IMPACTOS
        //*************************
        if (exists(info_prota.id_prota))
            //impacto con las balas
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                while (temp)
                    energia -= temp.energia;
                    //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
                    //say("el disparo tenía energia: " + itoa(temp.energia));
                    temp.energia = 0;
                    if (mi_temblor != 0 && exists(mi_temblor))
                        mi_temblor.energia = 1;
                    else
                        mi_temblor = enem_temblor(id, 1);
                    end
                    temp = collision(type normal_shot);
                end
            end
            
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                temp = collision(type espadazo);
                if ((temp != 0) && (temp != temp_espada))
                    energia -= temp.energia;
                    if (mi_temblor != 0 && exists(mi_temblor))
                        mi_temblor.energia = 1;
                    else
                        mi_temblor = enem_temblor(id, 1);
                    end
                    temp_espada = temp;
                end
            end
                
            if (energia <= 0) break; end
        end
        
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        frame;
    end
    
    modificar_tile(&durezas, enem_tx, enem_ty, 0, 0);
    modificar_tile(&durezas, enem_tx, enem_ty - 1, 0, 0);
    if (flags == 1)
        modificar_tile(&durezas, enem_tx + 1, enem_ty, 0, 0);
        modificar_tile(&durezas, enem_tx + 1, enem_ty - 1, 0, 0);
    else
        modificar_tile(&durezas, enem_tx - 1, enem_ty, 0, 0);
        modificar_tile(&durezas, enem_tx - 1, enem_ty - 1, 0, 0);
    end
    
    enem_explos(x2, y2 - 8, 0, 0);
    for (temp = 0; temp < 25; temp++)
        frame;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
    end
    //frame(2500);
    enem_explos(x2 - 16, y2 - 24, 0, 0);
    for (temp = 0; temp < 25; temp++)
        frame;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
    end
    //frame(2500);
    enem_explos(x2 + 16, y2 - 16, 0, 0);
    for (temp = 0; temp < 25; temp++)
        frame;
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
    end
    //frame(2500);
    enem_explos(x2 - 8, y2 - 8, 0, 0);
    enem_explos(x2, y2, 1, 1);
    enem_explos(x2, y2 - 16, 1, -1);
    enem_explos(x2 - 8, y2, -1, 1);
    enem_explos(x2 - 8, y2 - 16, -1, -1);
end