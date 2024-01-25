process glotz (int enem_tx, int enem_ty, file, energia)
private
    int enem_estado;        //0: mirando a la izquierda
                            //1: mirando a la derecha
                            //2: girando a la derecha
                            //3 :girando a la izquierda
                            //4: disparando
    int cont_estado;
    int cont_anim;
    int temp;
    int temp_espada;
begin
    priority = -99;
    z = 1;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    
    graph = 1;
    cont_estado = 10;
    loop
        cont_anim++;
        if (cont_anim >= 5)
            switch (enem_estado)
            case 0:	//mirando a la izquierda
                cont_estado--;
                if (cont_estado <= 0) enem_estado = 2; end
                if (veo_prota2(x2, y2, -120, -48, 16, 32))
					enem_estado = 4;
					cont_estado = 0;
				end
            end
            case 1:	//mirando a la derecha
                cont_estado--;
                if (cont_estado <= 0) enem_estado = 3; end
                if (veo_prota2(x2, y2, -16, -48, 120, 32))
					enem_estado = 4;
					cont_estado = 0;
				end
            end
            case 2:	//girando a la derecha
                if (graph < 7)
                    graph++;
                else
                    enem_estado = 1;
                    cont_estado=rand(3, 30);
                end
            end
            case 3:	//girando a la izquierda
                if (graph > 1)
                    graph--;
                else
                    enem_estado = 0;
                    cont_estado = rand(3, 30);
                end
            end
            case 4:	//disparando
                switch (graph)
                case 1,2,3: graph++; end
                case 7,6,5: graph--; end
                case 4:
                    if (exists(info_prota.id_prota))
                        if (info_prota.id_prota.x2 < x2)
                            enem_normal_shot(file, 10, 10, x2, y2 - 5, 180000, 3);
                        else
                            enem_normal_shot(file, 10, 10, x2, y2 - 5, 0, 3);
                        end
                        graph = 8;
                        cont_estado = 0;
                    end
                end
                case 8:
                    cont_estado++;
                    if (cont_estado == 12) graph = 9; end
                end
                case 9:
                    graph = 4;
                    if (exists(info_prota.id_prota))
                        if (info_prota.id_prota.x2 < x2)
                            enem_estado = 3;
                        else
                            enem_estado = 2;
                        end
                    end
                end
                end //switch
            end
            end //switch
            cont_anim = 0;
        end
        
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        //choque con los disparos
        if (exists(info_prota.id_prota))
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                while (temp != 0)
                    energia -= temp.energia;
                    temp.energia = 0;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                    temp = collision(type normal_shot);
                end
            end
            
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                temp = collision(type espadazo);
                if ((temp != 0) && (temp != temp_espada))
                    energia -= temp.energia;
                    if ((mi_temblor != 0) && exists(mi_temblor))
                        mi_temblor.energia = 3;
                    else
                        mi_temblor = enem_temblor(id, 3);
                    end
                    temp_espada = temp;
                end
            end
            
            //impacto con el prota
            if ((abs(x - info_prota.id_prota.x) < 50) && (abs(y - info_prota.id_prota.y) < 50))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 5;
                    info_prota.dano_exp = 5;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                    else info_prota.dano_vel_horiz = -20;
                    end
                end
            end
        end
        
        if (energia <= 0) break; end
        frame;
    end
    
    random_item (2, x2, y2 - (id_tscroll.tmapa[0].ancho_tile / 2));
    enem_explos(x2, y2 - 8, 0, 0);
end