process croquis (x2, y2, int vel_horiz, int vel_vert, int croquis_max_vel)
private
    //int vel_horiz, vel_vert;
    //int croquis_max_vel;
    int cont_anim;
    int temp;
    int temp_espada;
begin
    priority = father.priority-1;
    resolution = 100;
    x = x2 * resolution;
    y = y2 * resolution;
    alpha = 0;
    file = father.file;
    cont_anim = 4;
    energia = 24;
    //croquis_max_vel=220;
    //say("velocidad: "+itoa(croquis_max_vel));
	
	//Revoloteando alrededor del GHYPPO
    while (graph != 52)
        alpha = clamp( alpha + 2, 0, 255 );
        if ((father.x + 20) < x2)
            vel_horiz -= 8;
            if (vel_horiz < -croquis_max_vel) vel_horiz = -croquis_max_vel; end
        end
        if ((father.x - 20) > x2)
            vel_horiz += 8;
            if (vel_horiz > croquis_max_vel) vel_horiz = croquis_max_vel; end
        end
        if ((father.y + 20) < y2)
            vel_vert -= 8;
            if (vel_vert < -croquis_max_vel) vel_vert = -croquis_max_vel; end
        end
        if ((father.y - 20) > y2)
            vel_vert += 8;
            if (vel_vert > croquis_max_vel) vel_vert = croquis_max_vel; end
        end
        
        if (vel_horiz > 0) flags = 0; end
        if (vel_horiz < 0) flags = 1; end
        
        x += vel_horiz;
        y += vel_vert;
        x2 = x / resolution;
        y2 = y / resolution;
        
        //zona de graficos
        cont_anim++;
        switch (cont_anim)
        case 5: graph = 51; end
        case 10: graph = 50; cont_anim = 0; end
        end //switch
        
        //**************************************
        //  ZONA DE IMPACTOS
        //**************************************
        //impacto con las balas
        temp = collision(type normal_shot);
        while (temp != 0)
            energia -= temp.energia;
            //say("enemigo (" + itoa(enem_tx) + "," + itoa(enem_ty) + "): energía: " + itoa(energia));
            //say("el disparo tenía energia: " + itoa(temp.energia));
            temp.energia = 0;
            if ((mi_temblor != 0) && exists(mi_temblor))
                mi_temblor.energia = 3;
            else
                mi_temblor = enem_temblor(id, 3);
            end
            temp = collision(type normal_shot);
        end
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
        if (energia <= 0) break; end
        
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 2;
                info_prota.dano_exp = 2;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        
        frame;
    end
    
    if (energia > 0)
        //se está lanzando
        if (exists(info_prota.id_prota))
            angle = fget_angle(x2, y2, info_prota.id_prota.x, info_prota.id_prota.y);
            flags = 0;
        end
        
        loop
            advance(400);
            if (region_out(id, 0)) break; end
            
            //impacto con el prota
            if (exists(info_prota.id_prota))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 4;
                    info_prota.dano_exp = 2;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                    else info_prota.dano_vel_horiz = -20;
                    end
                end
            end
            
            frame;
        end
    end
end

process ghyppo_head (x, y, z, file, alpha)
private
    int temp;
    int temp_espada;
begin
    graph = 2;
    //size = 200;
    loop
        //ZONA DE COLISIONES
        //say(itoa(alpha));
        if (alpha == 255)
            //impacto con las balas
            temp = collision(type normal_shot);
            while (temp != 0)
                father.energia -= temp.energia + 1;
                temp.energia = 0;
                temp = collision(type normal_shot);
            end
            temp = collision(type espadazo);
            if ((temp != 0) && (temp != temp_espada))
                father.energia -= temp.energia + 1;
                temp_espada = temp;
            end
            
            //impacto con el prota
            if (exists(info_prota.id_prota))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 2;
                    info_prota.dano_exp = 2;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                    else info_prota.dano_vel_horiz = -20;
                    end
                end
            end
        end
        
        frame;
    end
end


process ghyppo_tail (z, file, alpha)
private
    int temp;
    int temp_espada;
begin
    graph = 3;
    //size = 200;
    loop
        //ZONA DE COLISIONES
        //say(itoa(alpha));
        if (alpha == 255)
            //impacto con las balas
            temp = collision(type normal_shot);
            while (temp != 0)
                father.energia -= temp.energia / 2;
                temp.energia = 0;
                temp = collision(type normal_shot);
            end
            temp = collision(type espadazo);
            if ((temp != 0) && (temp != temp_espada))
                father.energia -= temp.energia / 2;
                temp_espada = temp;
            end
            
            //impacto con el prota
            if (exists(info_prota.id_prota))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id = id;
                    info_prota.dano_energia = 2;
                    info_prota.dano_exp = 2;
                    if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                    else info_prota.dano_vel_horiz = -20;
                    end
                end
            end
        end
        frame;
    end
end


process ghyppo_bomb (z, file)
begin
    while (graph != 22)
        frame;
    end
    //se está lanzando
    if (exists(info_prota.id_prota))
        angle = fget_angle(x, y, info_prota.id_prota.x, info_prota.id_prota.y);
        flags = 0;
    end
    
    resolution = 100;
    x *= resolution;
    y *= resolution;
    loop
        advance(900);
        if (region_out(id, 0)) break; end
        
        //impacto con el prota
        if (exists(info_prota.id_prota))
            if (collision(info_prota.id_prota))
                info_prota.dano_id = id;
                info_prota.dano_energia = 8;
                info_prota.dano_exp = 4;
                if (info_prota.id_prota.x2 > x2) info_prota.dano_vel_horiz = 20;
                else info_prota.dano_vel_horiz = -20;
                end
            end
        end
        
        frame;
    end
end


process ghyppo (file)
private
    int ghyppo_head_id;
    int ghyppo_tail_id;
    int ghyppo_bomb_id;
    int ghyppo_croquis[9];
    int num_croquis;
    int cont_croquis;
    
    int angle2;     //para el movimiento de flotación
    int angle3;     //para el recolocamiento de las partes
    int head_offsx, head_offsy;
    int tail_offsx, tail_offsy;
    
    int energia_ant;
    int ghyppo_temblor[2];
    
    int x3,y3;
    int vel_horiz, vel_vert;
    int enem_estado;    //0: moviendo derecha
                        //1: moviendo invisible derecha
                        //2: moviendo izquierda
                        //3: moviendo invisible izquierda
                        //4: ataque croquis
                        //5: ataque bomba
                        //6: ataque lanzamiento
    int enem_estado2;
                        
    int ghyppo_posv[2]=68,124,180;
    int ghyppo_dir;
    
    int cont;
    int cont_estado;
    double temp_x, temp_y;
    int temp;   //buscar en zona de colisiones
    int temp_espada;
begin
    x3=32;
    y3=68;
    z=5;
    alpha=0;
    graph=1;
    //size=200;
    angle3=90000;
    
    energia=600;
    energia_ant=energia;
    
    //x3,y3 indican la posición donde debería estar
    //x2,y2 indica en la que están, contando con movimiento de flotación
    //x ,y  es la posición real, contando flotación e impacto
    x2=x3;
    y2=y3;
    x=x3;
    y=y3;
    
    ghyppo_head_id=ghyppo_head(x,y-24,z-1,file,alpha);
    ghyppo_tail_id=ghyppo_tail(z+1,file,alpha);
    head_offsx=0;
    head_offsy=-24;
    tail_offsx=-14;
    tail_offsy=16;
    ghyppo_tail_id.x=x2+tail_offsx;
    ghyppo_tail_id.y=y2+tail_offsy;
    
    for (alpha=0;alpha<255;alpha++)
        angle2+=3000;
        if (angle2>360000) angle2-=360000; end
        y2=y3+(4*sin(angle2));
        y=y2;
        ghyppo_head_id.alpha=alpha;
        ghyppo_head_id.y=y2+head_offsy;
        ghyppo_tail_id.alpha=alpha;
        ghyppo_tail_id.y=y2+tail_offsy;
        frame;
    end
    
    alpha=255;
    
    while (num_croquis<10)
        cont++;
        if (cont==25)
            cont=0;
            ghyppo_croquis[num_croquis]=croquis(rand(x-35,x+35),rand(y-40,y+40),5,5,rand(250,170));
            num_croquis++;
        end
        angle2+=3000;
        if (angle2>360000) angle2-=360000; end
        y2=y3+(4*sin(angle2));
        y=y2;
        ghyppo_head_id.alpha=alpha;
        ghyppo_head_id.y=y2+head_offsy;
        ghyppo_tail_id.alpha=alpha;
        ghyppo_tail_id.y=y2+tail_offsy;
        frame;
    end
    
    prota_control=1;
    
    while (energia>0)
        //say("cont estado: "+itoa(cont_estado));
        //say("numero croquis: "+itoa(num_croquis));
        switch (enem_estado)
        case 0:
            if (cont_estado<200)
                cont_estado++;
                if (cont_estado==200) ghyppo_dir=rand(0,2); end
            else
                if (x3<285)//273)
                    /*if (y3<ghyppo_posv[ghyppo_dir]) 
                        vel_vert++;
                        if (vel_vert>3) vel_vert=3; end
                    end
                    if (y3>ghyppo_posv[ghyppo_dir]) 
                        vel_vert--;
                        if (vel_vert<-3) vel_vert=-3; end
                    end*/
                    /*vel_vert=ghyppo_posv[ghyppo_dir]-y3;
                    if (vel_vert>1) vel_vert=1; end
                    if (vel_vert<-1) vel_vert=-1; end*/
                    if (y3<ghyppo_posv[ghyppo_dir]) vel_vert=1;
                    elsif (y3>ghyppo_posv[ghyppo_dir]) vel_vert=-1;
                    else vel_vert=0; end
                    vel_horiz++;
                    if (vel_horiz>2) vel_horiz=2; end
                else
                    if (vel_horiz>0)
                        vel_horiz--;
                    else
                        flags=1;
                        ghyppo_head_id.flags=1;
                        ghyppo_tail_id.flags=1;
                        tail_offsx=14;
                        enem_estado=rand(4,6);
                        //enem_estado=rand(2,3);
                        //enem_estado=6;
                        enem_estado2=0;
                        cont_estado=0;
                    end
                end
                x3+=vel_horiz;
                y3+=vel_vert;
            end
        end
        case 2:
            if (cont_estado<200)
                cont_estado++;
                if (cont_estado==200) ghyppo_dir=rand(0,2); end
            else
                if (x3>35)//47)
                    /*if (y3<ghyppo_posv[ghyppo_dir]) 
                        vel_vert++;
                        if (vel_vert>3) vel_vert=3; end
                    end
                    if (y3>ghyppo_posv[ghyppo_dir]) 
                        vel_vert--;
                        if (vel_vert<-3) vel_vert=-3; end
                    end*/
                    /*vel_vert=ghyppo_posv[ghyppo_dir]-y3;
                    if (vel_vert>2) vel_vert=2; end
                    if (vel_vert<-2) vel_vert=-2; end*/
                    if (y3<ghyppo_posv[ghyppo_dir]) vel_vert=1;
                    elsif (y3>ghyppo_posv[ghyppo_dir]) vel_vert=-1;
                    else vel_vert=0; end
                    vel_horiz--;
                    if (vel_horiz<-2) vel_horiz=-2; end
                else
                    if (vel_horiz<0)
                        vel_horiz++;
                    else
                        flags=0;
                        ghyppo_head_id.flags=0;
                        ghyppo_tail_id.flags=0;
                        tail_offsx=-14;
                        enem_estado=rand(4,6);
                        //enem_estado=rand(0,1);
                        //enem_estado=6;
                        enem_estado2=0;
                        cont_estado=0;
                    end
                end
                x3+=vel_horiz;
                y3+=vel_vert;
            end
        end
        case 1:
            if ((alpha>0) && (cont_estado==0))
                alpha--;
                ghyppo_head_id.alpha=alpha;
                ghyppo_tail_id.alpha=alpha;
                if (alpha==0) cont_estado=1; end
            end
            if ((alpha<255) && (cont_estado==2))
                alpha++;
                ghyppo_head_id.alpha=alpha;
                ghyppo_tail_id.alpha=alpha;
                if (alpha==255)
                    cont_estado=0;
                    enem_estado=rand(4,6);
                    //enem_estado=rand(2,3);
                    //enem_estado=6;
                    enem_estado2=0;
                end
            end
            if (cont_estado==1)
                if (x3<285)//273)
                    if (y3<ghyppo_posv[ghyppo_dir]) vel_vert=1;
                    elsif (y3>ghyppo_posv[ghyppo_dir]) vel_vert=-1;
                    else vel_vert=0; end
                    vel_horiz++;
                    if (vel_horiz>2) vel_horiz=2; end
                else
                    if (vel_horiz>0)
                        vel_horiz--;
                    else
                        flags=1;
                        ghyppo_head_id.flags=1;
                        ghyppo_tail_id.flags=1;
                        tail_offsx=14;
                        cont_estado=2;
                    end
                end
                x3+=vel_horiz;
                y3+=vel_vert;
            end
        end
        case 3:
            if ((alpha>0) && (cont_estado==0))
                alpha--;
                ghyppo_head_id.alpha=alpha;
                ghyppo_tail_id.alpha=alpha;
                if (alpha==0) cont_estado=1; end
            end
            if ((alpha<255) && (cont_estado==2))
                alpha++;
                ghyppo_head_id.alpha=alpha;
                ghyppo_tail_id.alpha=alpha;
                if (alpha==255)
                    cont_estado=0;
                    enem_estado=rand(4,6);
                    //enem_estado=rand(0,1);
                    //enem_estado=6;
                    enem_estado2=0;
                end
            end
            if (cont_estado==1)
                if (x3>35)//47)
                    /*if (y3<ghyppo_posv[ghyppo_dir]) 
                        vel_vert++;
                        if (vel_vert>3) vel_vert=3; end
                    end
                    if (y3>ghyppo_posv[ghyppo_dir]) 
                        vel_vert--;
                        if (vel_vert<-3) vel_vert=-3; end
                    end*/
                    /*vel_vert=ghyppo_posv[ghyppo_dir]-y3;
                    if (vel_vert>2) vel_vert=2; end
                    if (vel_vert<-2) vel_vert=-2; end*/
                    if (y3<ghyppo_posv[ghyppo_dir]) vel_vert=1;
                    elsif (y3>ghyppo_posv[ghyppo_dir]) vel_vert=-1;
                    else vel_vert=0; end
                    vel_horiz--;
                    if (vel_horiz<-2) vel_horiz=-2; end
                else
                    if (vel_horiz<0)
                        vel_horiz++;
                    else
                        flags=0;
                        ghyppo_head_id.flags=0;
                        ghyppo_tail_id.flags=0;
                        tail_offsx=-14;
                        cont_estado=2;
                    end
                end
                x3+=vel_horiz;
                y3+=vel_vert;
            end
        end
        case 4:
            switch (enem_estado2)
            case 0:
                cont_estado++;
                if (cont_estado==200)
                    cont_croquis=0;
                    enem_estado2=1;
                    cont_estado=0;
                    num_croquis=9;
                    //say("numero croquis inicial: "+itoa(num_croquis));
                end
            end
            case 1:
                cont_estado++;
                if (cont_estado==50)
                    cont_estado=0;
                    if (cont_croquis<=9)
                        if (exists(ghyppo_croquis[cont_croquis]))
                            ghyppo_croquis[cont_croquis].graph=52;
                        else
                            if (num_croquis>=0) num_croquis--; end
                            cont_estado=49;
                            //say("croquis no contado: "+itoa(cont_croquis));
                            //say("quedan: "+itoa(num_croquis));
                        end
                        cont_croquis++;
                    else
                        enem_estado2=2;
                        cont_croquis=0;
                        cont_estado=0;
                        if (num_croquis<9) num_croquis++; end
                    end
                end
            end
            case 2:
                cont_estado++;
                if (cont_estado==25)
                    cont_estado=0;
                    //say("numero final de croquis: "+itoa(num_croquis));
                    if (cont_croquis<=num_croquis)
                        ghyppo_croquis[cont_croquis]=croquis(rand(x-35,x+35),rand(y-40,y+40),5,5,rand(250,170));
                        cont_croquis++;
                    else
                        cont_croquis=0;
                        enem_estado2=0;
                        cont_estado=0;
                        if (x>160) enem_estado=rand(2,3); else enem_estado=rand(0,1); end
                     end
                end
            end
            end //switch
        end
        case 5:
            switch (enem_estado2)
            case 0:     //generando la bomba
                cont_estado++;
                switch (cont_estado)
                case 150:
                    ghyppo_bomb_id=ghyppo_bomb(z-1,file);
                    ghyppo_bomb_id.graph=20;
                end
                case 200: ghyppo_bomb_id.graph=21; end
                case 250:
                     ghyppo_bomb_id.graph=22;
                     enem_estado2=1;
                end
                end //switch
            end
            case 1:     //esperando a que desaparezca la bomba
                if (!exists(ghyppo_bomb_id))
                    enem_estado2=0;
                    cont_estado=0;
                    if (x>160) enem_estado=rand(2,3); else enem_estado=rand(0,1); end
                end
            end
            end //switch
        end
        case 6:
            switch (enem_estado2)
            case 0:     //obteniendo postura
                angle3-=2000;
                head_offsy=-24*sin(angle3);
                head_offsx=18*cos(angle3);
                if (ghyppo_head_id.flags==1)
                    head_offsx=-head_offsx;
                    point_get(file,graph,6,&temp_x,&temp_y);
                    //say(itoa(temp_x)+" "+itoa(temp_y));
                else
                    point_get(file,graph,5,&temp_x,&temp_y);
                end
                temp_x-=21;
                temp_y-=24;
                //say(itoa(temp_x)+" "+itoa(temp_y));
                
                if (tail_offsx<temp_x) tail_offsx++; end
                if (tail_offsx>temp_x) tail_offsx--; end
                if (tail_offsy<temp_y) tail_offsy++; end
                if (tail_offsy>temp_y) tail_offsy--; end
                //say(itoa(tail_offsx)+" "+itoa(tail_offsy));
                
                if ((angle3%8000)==0) y3++; end
                
                if (angle3==0) enem_estado2=1; end
            end
            case 1:
                cont_estado++;
                if (cont_estado==25)
                    cont_estado=0;
                    enem_estado2=2;
                end
            end
            case 2:
                if (ghyppo_head_id.flags==1)
                    x3-=5;
                    if (x3<-45) enem_estado2=3; end
                else
                    x3+=5;
                    if (x3>365) enem_estado2=3; end
                end
            end
            case 3:
                angle3=90000;
                head_offsx=0;
                head_offsy=-24;
                tail_offsy=16;
                if (ghyppo_head_id.flags==1)
                    flags=0;
                    ghyppo_head_id.flags=0;
                    ghyppo_tail_id.flags=0;
                    tail_offsx=-14;
                    enem_estado2=4;
                else
                    flags=1;
                    ghyppo_head_id.flags=1;
                    ghyppo_tail_id.flags=1;
                    tail_offsx=14;
                    enem_estado2=5;
                end
                y3-=11;
            end
            case 4:
                x3++;
                if (x3==35)
                    enem_estado2=0;
                    enem_estado=rand(0,1);
                end
            end
            case 5:
                x3--;
                if (x3==285)
                    enem_estado2=0;
                    enem_estado=rand(2,3);
                end
            end
            end //switch
        end
        end //switch
        
        //if (alpha>255) alpha=255; end
        
        x2=x3;
        x=x2;
        angle2+=3000;
        if (angle2>360000) angle2-=360000; end
        y2=y3+(6*sin(angle2));
        //y2=y3;
        y=y2;
        ghyppo_head_id.alpha=alpha;
        ghyppo_head_id.x=x2+head_offsx;
        ghyppo_head_id.y=y2+head_offsy;
        ghyppo_tail_id.alpha=alpha;
        ghyppo_tail_id.x=x2+tail_offsx;
        ghyppo_tail_id.y=y2+tail_offsy;
        if (exists(ghyppo_bomb_id))
            if (ghyppo_bomb_id.graph<22)
                ghyppo_bomb_id.x=x;
                ghyppo_bomb_id.y=y;
            end
        end
        
        //ZONA DE COLISIONES
        //say(itoa(alpha));
        if (alpha==255)
            //impacto con las balas
            temp=collision(type normal_shot);
            while (temp)
                energia-=temp.energia;
                temp.energia=0;
                temp=collision(type normal_shot);
            end
            temp=collision(type espadazo);
            if (temp && (temp!=temp_espada))
                energia-=temp.energia;
                temp_espada=temp;
            end
            if (energia_ant!=energia)
                if (ghyppo_temblor[0]!=0 && exists(ghyppo_temblor[0]))
                    ghyppo_temblor[0].energia=5;
                    ghyppo_temblor[1].energia=5;
                    ghyppo_temblor[2].energia=5;
                else
                    ghyppo_temblor[0]=enem_temblor(id,5);
                    ghyppo_temblor[1]=enem_temblor(ghyppo_head_id,5);
                    ghyppo_temblor[2]=enem_temblor(ghyppo_tail_id,5);
                end
                energia_ant=energia;
            end
            //energia_ant=energia;
            if (energia<=0) break; end
            
            //impacto con el prota
            if (exists(info_prota.id_prota))
                if (collision(info_prota.id_prota))
                    info_prota.dano_id=id;
                    if (enem_estado2==5)
                        info_prota.dano_energia=4;
                        info_prota.dano_exp=3;
                    else
                        info_prota.dano_energia=2;
                        info_prota.dano_exp=2;
                    end
                    if (info_prota.id_prota.x2>x2) info_prota.dano_vel_horiz=20;
                    else info_prota.dano_vel_horiz=-20;
                    end
                end
            end
        end
        
        frame;
        
    end
    
    /*loop
        angle2+=3000;
        if (angle2>360000) angle2-=360000; end
        y2=y3+(4*sin(angle2));
        y=y2;
        ghyppo_head_id.alpha=alpha;
        ghyppo_head_id.y=y2+head_offsy;
        ghyppo_tail_id.alpha=alpha;
        ghyppo_tail_id.y=y2+tail_offsy;
        frame;
    end*/
    
    fade(255, 255, 255, 255, 100);
    frame(300);
    fade_on(100);
    
    if (exists(ghyppo_bomb_id))
        signal(ghyppo_bomb_id,s_kill);
    end
    
    while (alpha>0)
        alpha--;
        ghyppo_head_id.alpha=alpha;
        ghyppo_tail_id.alpha=alpha;
        frame;
    end
    
    if (exists(ghyppo_head_id)) signal(ghyppo_head_id,s_kill); end
    if (exists(ghyppo_tail_id)) signal(ghyppo_tail_id,s_kill); end
    cont=get_id(type croquis);
    while (cont)
        cont.graph=52;
        cont=get_id(type croquis);
    end
end