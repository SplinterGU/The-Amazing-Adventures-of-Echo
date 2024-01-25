process vigilante_horus (int enem_tx, int enem_ty, file, flags)
private
    int enem_estado;        //0: sin mirar
                            //1: mirando
                            //2: preparando disparo
                            //3: disparo
                            //4: vuelta a la calma
    int cont_anim;
    int temp;
    int temp_tile;
begin
    priority = -99;
    z = 1;
    
    x2 = (enem_tx * id_tscroll.tmapa[0].ancho_tile) + (id_tscroll.tmapa[0].ancho_tile / 2);
    y2 = (enem_ty * id_tscroll.tmapa[0].alto_tile) + (id_tscroll.tmapa[0].alto_tile - 1);
    
    temp_tile = obtener_tile(&nivel, enem_tx, enem_ty, 0);
    modificar_tile(&nivel, enem_tx, enem_ty, 0, 0);
    
    graph = 1;
    loop
        cont_anim++;        
        switch (enem_estado)
        case 0:
            switch (cont_anim)
            case 0..5: graph = 1; end
            case 6..10: graph = 2; end
            case 11: graph = 3; end
            case 150:
                enem_estado = 1;
                cont_anim = 0;
            end
            end //switch
        end
        case 1:
            switch (cont_anim)
            case 0..5: graph = 3; end
            case 6..10: graph = 2; end
            case 11: graph = 1; end
            case 150:
                enem_estado = 0;
                cont_anim = 0;
            end
            default:
                if ((flags == 0) && (veo_prota2(x2, y2, -170, -48, 16, 32)))
					enem_estado = 2;
					cont_anim = 0;
				end
                if ((flags == 1) && (veo_prota2(x2, y2, -16, -48, 170, 32)))
					enem_estado = 2;
					cont_anim = 0;
				end
            end
            end //switch
        end
        case 2:
            if ((cont_anim & 3) == 3) graph = 1; else graph = 4; end
            if (cont_anim > 25)
                if (flags == 0) enem_normal_shot(file, 5, 5, x2, y2 - 6, 180000, 8); end
                if (flags == 1) enem_normal_shot(file, 5, 5, x2, y2 - 6, 0, 8); end
                enem_estado = 0;
                cont_anim = 0;
            end
        end
        end //switch
        
        
        tscroll_get_screen_position(&id_tscroll, x2, y2, &x, &y);
        
        //choque con los disparos
        if (exists(info_prota.id_prota))
            if ((abs(x - info_prota.id_prota.x) < 350) && (abs(y - info_prota.id_prota.y) < 350))
                temp = collision(type normal_shot);
                while (temp != 0)
                    temp.energia = 0;
                    temp = collision(type normal_shot);
                end
            end
            
            //impacto con el prota
        end
        
        if ((x < -50) || (x > 370) || (y < -50) || (y > 290)) break; end
        frame;
    end
    
    modificar_tile(&nivel, enem_tx, enem_ty, 0, temp_tile);
end