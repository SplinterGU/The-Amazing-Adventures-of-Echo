process dragon_fire (file, graph, x, y, angle, int df_vel)
begin
    //say(itoa(x) + " " + itoa(y));
    resolution = 10;
    z = 8;
    while ((x > -100) && (y < 2500))
        advance(df_vel);
        
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 2;
                info_prota.dano_exp = 2;
                
                if (info_prota.id_prota.x > (x / 10)) info_prota.dano_vel_horiz = 30;
                else info_prota.dano_vel_horiz = -30;
                end
            end
        end
        
        frame;
    end
end

process dragon_laser (file, graph, x, y, angle)
begin
    resolution = 10;
    z = 8;
    flags = 16;
    size_y = 200;
    while (alpha > 0)
        alpha = clamp( alpha - 6, 0, 255 );
        
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 7;
                info_prota.dano_exp = 4;
                
                if (info_prota.id_prota.x > (x / 10)) info_prota.dano_vel_horiz = 40;
                else info_prota.dano_vel_horiz = -40;
                end
            end
        end
        
        frame;
    end
end

process dragon_homing (file, graph, x, y, int angle2)
private
    int cont;
begin
    resolution = 10;
    z = 8;
    loop
        angle += 20000;
        if (exists(info_prota.id_prota))
            angle2 = near_angle(angle2, fget_angle(x, y, info_prota.id_prota.x * 10, info_prota.id_prota.y * 10),
								2000);
            xadvance(angle2, 10);
            
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 3;
                info_prota.dano_exp = 3;
                
                if (info_prota.id_prota.x > (x / 10)) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        
        xadvance(angle2, 10);
        cont++;
        if (cont > 250) alpha = clamp( alpha - 5, 0, 255 ); end
        if (alpha <= 0) break; end
        
        frame;
    end
end