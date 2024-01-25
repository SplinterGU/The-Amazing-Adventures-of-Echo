//**************************************************************************************************
//  FUNCIONES AUXILIARES
//**************************************************************************************************


//**************************************************************************************************
//  ENEMIGOS (por orden alfabético)
//**************************************************************************************************





/*process fly (int enem_tx, int enem_ty, int enem_despx)
private
    int vel_horiz;
    int vel_vert;
    int x3,y3;
    int resolution3;
    int ini_x2,fin_x2;
    int ini_y2;
    
    int enem_dur[2][2];
    int enem_tilex, enem_tiley;
    int enem_offsx, enem_offsy;
    int enem_mover_h, enem_mover_v;
    int enem_p_dir, enem_p_dir_ini;
    int enem_estado;
    int p_libre;
begin
    x2=enem_tx*id_tscroll.tmapa[0].ancho_tile;
    y2=enem_ty*id_tscroll.tmapa[0].alto_tile;
    resolution3=10;
    x3=x2*resolution3;
    y3=y2*resolution3;
    energia=15;
    
    file=enem_grafs[0];
    graph=1;
    
    ini_x2=x2;
    fin_x2=x2-(enem_despx*id_tscroll.tmapa[0].ancho_tile);
    ini_y2=y2;
    vel_horiz=-25;
    
    loop
        if ((vel_horiz < 25) && (x2<fin_x2))
            vel_horiz++;
        end
        if ((vel_horiz > -25) && (x2>ini_x2))
            vel_horiz--;
        end
        
        //localizamos la posición actual
        enem_tilex= (x3/resolution3)/id_tscroll.tmapa[0].ancho_tile;
        enem_tiley= (y3/resolution3)/id_tscroll.tmapa[0].alto_tile;
        enem_offsx= (x3/resolution3)%id_tscroll.tmapa[0].ancho_tile;
        enem_offsy= (y3/resolution3)%id_tscroll.tmapa[0].alto_tile;
        //leemos durezas de su alrededor
        enem_dur[0][0]=obtener_tile(&durezas,enem_tilex-1,enem_tiley-1,0);
        enem_dur[1][0]=obtener_tile(&durezas,enem_tilex  ,enem_tiley-1,0);
        enem_dur[2][0]=obtener_tile(&durezas,enem_tilex+1,enem_tiley-1,0);
        enem_dur[0][1]=obtener_tile(&durezas,enem_tilex-1,enem_tiley  ,0);
        enem_dur[1][1]=obtener_tile(&durezas,enem_tilex  ,enem_tiley  ,0);
        enem_dur[2][1]=obtener_tile(&durezas,enem_tilex+1,enem_tiley  ,0);
        enem_dur[0][2]=obtener_tile(&durezas,enem_tilex-1,enem_tiley+1,0);
        enem_dur[1][2]=obtener_tile(&durezas,enem_tilex  ,enem_tiley+1,0);
        enem_dur[2][2]=obtener_tile(&durezas,enem_tilex+1,enem_tiley+1,0);
        //comprobamos si cambiamos de tile y en que direccion
        //***************************************************************
        enem_mover_h=0;
        if (((x3+vel_horiz)/(id_tscroll.tmapa[0].ancho_tile*resolution3))!=enem_tilex)
           //comprobamos si pasamos a otro tile lateral y cuan lejos esta
           enem_mover_h=((x3+vel_horiz)/(id_tscroll.tmapa[0].ancho_tile*resolution3))-enem_tilex;
        end
        
        enem_mover_v=0;
        if (((y3+vel_vert)/(id_tscroll.tmapa[0].alto_tile*resolution3))!=enem_tiley)
           //comprobamos si pasamos a otro tile vertical y cuan lejos esta
           enem_mover_v=((y3+vel_vert)/(id_tscroll.tmapa[0].alto_tile*resolution3))-enem_tiley;
        end
         //miramos en que direccion cambiamos
        enem_p_dir=5;
        if (enem_mover_h>0) enem_p_dir++; end
        if (enem_mover_h<0) enem_p_dir--; end
        if (enem_mover_v>0) enem_p_dir-=3; end      //hacia abajo
        if (enem_mover_v<0) enem_p_dir+=3; end      //hacia arriba
        enem_p_dir_ini=enem_p_dir;
        
        include "src/game/common/durezas_check.inc";
        
    end
end*/
