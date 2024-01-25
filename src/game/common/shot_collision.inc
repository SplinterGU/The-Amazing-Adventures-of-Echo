function shot_colision_lateral (int shot_offsx, int shot_offsy, int shot_tile, int vel_x, int resolution3)
begin
    if (vel_x > 0)
        switch (shot_tile)
        case 1,2,5,14,51,52,55,64:
            vel_x -= shot_offsx * resolution3;
            father.energia = 0;
        end
        case 3,53:
            if (shot_offsx > (id_tscroll.tmapa[0].alto_tile - shot_offsy))
                vel_x -= (shot_offsx - (id_tscroll.tmapa[0].alto_tile - shot_offsy)) * resolution3;
                father.energia = 0;
            end
        end
        case 4,54:
            if (shot_offsx > shot_offsy)
                vel_x -= (shot_offsx - shot_offsy) * resolution3;
                father.energia = 0;
            end
        end
        case 13,63:
            if (shot_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                vel_x -= shot_offsx * resolution3;
                father.energia = 0;
            end
        end
        case 15,65:
            if (shot_offsy > (id_tscroll.tmapa[0].alto_tile - (shot_offsx / 2)))
                //usamos una aproximación
                father.energia = 0;
            end
        end
        case 16,66:
            if (shot_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                vel_x -= shot_offsx * resolution3;
                father.energia = 0;
            elsif (shot_offsy > ((id_tscroll.tmapa[0].alto_tile - shot_offsx) / 2) )
            end
        end
        
        end //switch
    end
    if (vel_x < 0)
        switch (shot_tile)
        case 1,3,4,16,51,53,54,66:
            vel_x += (id_tscroll.tmapa[0].ancho_tile - shot_offsx) * resolution3;
            father.energia = 0;
        end
        case 2,52:
            if (shot_offsy > shot_offsx)
                vel_x += (shot_offsy - shot_offsx) * resolution3;
                father.energia = 0;
            end
        end
        case 5,55:
            if (shot_offsx < (id_tscroll.tmapa[0].alto_tile - shot_offsy))
                vel_x += (id_tscroll.tmapa[0].alto_tile - shot_offsy - shot_offsx) * resolution3;
                father.energia = 0;
            end
        end
        case 15,65:
            if (shot_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                vel_x += (id_tscroll.tmapa[0].ancho_tile - shot_offsx) * resolution3;
                father.energia = 0;
            end
        end
        case 13,63:
            if (shot_offsy > ((id_tscroll.tmapa[0].alto_tile / 2) + (shot_offsx / 2)))
                //usamos una aproximación
                father.energia = 0;
            end
        end
        case 14,64:
            if (shot_offsy > (id_tscroll.tmapa[0].alto_tile / 2))
                vel_x += (id_tscroll.tmapa[0].ancho_tile - shot_offsx) * resolution3;
                father.energia = 0;
            elsif (shot_offsy > (shot_offsx / 2))
                //otra aproximación
                father.energia = 0;
            end
        end
        
        end //switch
    end
    
    return (vel_x);
end

function shot_colision_vertical (int shot_offsx, int shot_offsy, int shot_tile, int vel_y, int resolution3)
begin
    if (vel_y > 0)        //hacia abajo
        switch (shot_tile)
        case 1,4,5,51,54,55:
            vel_y -= shot_offsy * resolution3;
            father.energia = 0;
        end
        case 2,52:
            if (shot_offsy > shot_offsx)
                vel_y -= (shot_offsy - shot_offsx) * resolution3;
                father.energia = 0;
            end
        end
        case 3,53:
            if (shot_offsy > (id_tscroll.tmapa[0].ancho_tile - shot_offsx))
                vel_y -= (shot_offsy - (id_tscroll.tmapa[0].ancho_tile - shot_offsx)) * resolution3;
                father.energia = 0;
            end
        end
        case 13,63:
            if (shot_offsy > ((id_tscroll.tmapa[0].alto_tile / 2) + (shot_offsx / 2)))
                vel_y -= (shot_offsy - ((id_tscroll.tmapa[0].alto_tile / 2) + (shot_offsx / 2))) * resolution3;
                father.energia = 0;
            end
        end
        case 14,64:
            if (shot_offsy > (shot_offsx / 2))
                vel_y -= (shot_offsy - (shot_offsx / 2)) * resolution3;
                father.energia = 0;
            end
        end
        case 15,65:
            if (shot_offsy > (id_tscroll.tmapa[0].alto_tile - (shot_offsx / 2)))
                vel_y -= (shot_offsy - (id_tscroll.tmapa[0].alto_tile - (shot_offsx / 2))) * resolution3;
                father.energia = 0;
            end
        end
        case 16,66:
            if (shot_offsy > ((id_tscroll.tmapa[0].alto_tile / 2) - (shot_offsx / 2)))
                vel_y -= (shot_offsy - ((id_tscroll.tmapa[0].alto_tile - shot_offsx) / 2)) * resolution3;
                father.energia = 0;
            end
        end
        
        end //switch
    end
    if (vel_y < 0)
        switch (shot_tile)
        case 1,2,3,13,14,15,16,51,52,53,63,64,65,66:
            vel_y += (id_tscroll.tmapa[0].ancho_tile - shot_offsy) * resolution3;
            father.energia = 0;
        end
        case 4,54:
            if (shot_offsy < shot_offsx)
                vel_y += (shot_offsx - shot_offsy) * resolution3;
                father.energia = 0;
            end
        end
        case 5,55:
            if (shot_offsy < (id_tscroll.tmapa[0].ancho_tile - shot_offsx))
                vel_y += (id_tscroll.tmapa[0].ancho_tile - shot_offsx - shot_offsy) * resolution3;
                father.energia = 0;
            end
        end
        end //switch
    end
    
    return (vel_y);
end