//**************************************************************************************************
//  EVENTOS
//**************************************************************************************************


function event (x2,y2)
begin
    modificar_tile(&nivel,x2,y2,0,0);
    switch (next_level)
    case 1:
        switch (obtener_tile(&durezas,x2,y2,0)-150)
        case 1: event_1_3_1(); end
        case 2: event_1_3_2(); end
        case 3: event_1_4_1(); end
        end //switch
    end
    case 3:
        switch (obtener_tile(&durezas,x2,y2,0)-150)
        case 1: event_3_1(x2,y2); end
        case 2: //matar todos los enemigos con x<-50 e inidicar un nuevo inicio
            event_3_2();
            //next_sublevel++;
        end 
        case 3: event_3_3(); end //super pang
        end //switch
    end
	case 4:
		switch (next_sublevel)
		case 3: event_4_4(); end
		end // switch
	end
    case 5:
        switch (obtener_tile(&durezas,x2,y2,0)-150)
        case 2: event_5_2y5_3(x2,y2); end   //salva partida a mitad del nivel 4_2
        case 3: event_5_2y5_3(x2,y2); end   //salva partida a mitad del nivel 4_3
        end //switch
    end
    end //switch
end

//************************************************
//  DEBUG
//************************************************
process event_en_construccion ()
private
    string eec_cadena1;
    string eec_cadena2;
    string eec_cadena3;
    string eec_cadena4;
    string eec_cadena5;
    string eec_cadena6;
    
    int eec_textos[5];
    int cont;
begin
    graph = map_new(320,240);
    center_set(file,graph,0,0);
    map_clear(file, graph, rgb(0,0,0));
    x=0;
    y=0;
    z=-200;
    
    eec_cadena1 = "After finding the secret way into the";
    eec_cadena2 = "pyramid, Echo went through all the";
    eec_cadena3 = "dangers of the cave.";
    eec_cadena4 = "What will he find there?";
    eec_cadena5 = "What new adventure awaits there?";
    eec_cadena6 = "Stay tunned!! Same time, same channel.";
    
    eec_textos[0]=write(0,20,70,0,eec_cadena1);
    eec_textos[1]=write(0,20,80,0,eec_cadena2);
    eec_textos[2]=write(0,20,90,0,eec_cadena3);
    eec_textos[3]=write(0,20,100,0,eec_cadena4);
    eec_textos[4]=write(0,20,110,0,eec_cadena5);
    eec_textos[5]=write(0,20,130,0,eec_cadena6);
    
    fade_on(1000);
    while (fade_info.fading); frame; end
    while (teclas[k_enter][2] > 0 || teclas[k_fire][2] > 0 || teclas[k_jump][2] > 0) frame; end
    while (teclas[k_enter][2] == 0 || teclas[k_fire][2] == 0 || teclas[k_jump][2] == 0) frame; end
    fade_off(1000);
    while (fade_info.fading); frame; end
    
    for (cont=0; cont<6; cont++)
        write_delete(eec_textos[cont]);
    end
    map_unload(file,graph);
    
    signal(father, s_wakeup);
    frame;
end
