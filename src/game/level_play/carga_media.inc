function cargar_graficos_enemigos (int cge_nivel, int cge_subnivel)
begin
    switch (cge_nivel)
    case 1:
        enem_grafs[0][cte_blobo] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/blobo.fpg");
        enem_grafs[0][cte_ghost_fly] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/hedghost.fpg");
        enem_grafs[0][cte_murcielago] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/murphy.fpg");
        enem_grafs[0][cte_spider] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/spider.fpg");
        enem_grafs[0][cte_volador1] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/corvo.fpg");
        enem_grafs[0][cte_hotta] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/hotta.fpg");
        
        enem_grafs[1][cte_blobo] = 1;
        enem_grafs[1][cte_ghost_fly] = 1;
        enem_grafs[1][cte_murcielago] = 1;
        enem_grafs[1][cte_spider] = 1;
        enem_grafs[1][cte_volador1] = 1;
        enem_grafs[1][cte_hotta] = 1;
    end
    case 3:
        enem_grafs[0][cte_guerrillero] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/guerrillero.fpg");
        enem_grafs[0][cte_spider] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/metal_spider.fpg");
        enem_grafs[0][cte_s_guerrillero] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/super_g.fpg");
        enem_grafs[0][cte_zenerg] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/zenerg.fpg");
        enem_grafs[0][cte_mina] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/mina.fpg");
        enem_grafs[0][cte_volador1] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/robcop.fpg");
        enem_grafs[0][cte_flozat] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/flozat.fpg");
        enem_grafs[0][cte_glotz] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/glotz.fpg");
        enem_grafs[0][cte_canon] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/canon.fpg");
        enem_grafs[0][cte_flerris] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/flerris.fpg");
        enem_grafs[0][cte_s_flerrus] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/s_flerrus.fpg");
        
        enem_grafs[1][cte_guerrillero] = 1;
        enem_grafs[1][cte_spider] = 1;
        enem_grafs[1][cte_s_guerrillero] = 1;
        enem_grafs[1][cte_zenerg] = 1;
        enem_grafs[1][cte_mina] = 1;
        enem_grafs[1][cte_volador1] = 1;
        enem_grafs[1][cte_flozat] = 1;
        enem_grafs[1][cte_glotz] = 1;
        enem_grafs[1][cte_canon] = 1;
        enem_grafs[1][cte_flerris] = 1;
        enem_grafs[1][cte_s_flerrus] = 1;
    end
    case 4:
		switch (cge_subnivel)
		case 0:
			enem_grafs[0][cte_blobo] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/sandbug.fpg");
			enem_grafs[0][cte_volador2] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/locust.fpg");
			enem_grafs[0][cte_volador1] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/minilocust.fpg");
			enem_grafs[0][cte_spikes] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/atl_spike.fpg");
			enem_grafs[0][cte_excaver] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/excaver01.fpg");
			enem_grafs[0][cte_vigilante] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/anubis.fpg");
			
			enem_grafs[1][cte_blobo] = 1;
			enem_grafs[1][cte_volador2] = 1;
			enem_grafs[1][cte_volador1] = 1;
			enem_grafs[1][cte_spikes] = 1;
			enem_grafs[1][cte_excaver] = 1;
			enem_grafs[1][cte_vigilante] = 1;
		end
		case 1:
			enem_grafs[0][cte_blobo] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/sandbug.fpg");
			enem_grafs[0][cte_volador2] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/locust.fpg");
			enem_grafs[0][cte_volador1] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/minilocust.fpg");
			enem_grafs[0][cte_zenerg] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/zenerg.fpg");
			enem_grafs[0][cte_vigilante] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/anubis.fpg");
			enem_grafs[0][cte_momia] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/mummy.fpg");
			
			enem_grafs[1][cte_blobo] = 1;
			enem_grafs[1][cte_volador2] = 1;
			enem_grafs[1][cte_volador1] = 1;
			enem_grafs[1][cte_zenerg] = 1;
			enem_grafs[1][cte_vigilante] = 1;
			enem_grafs[1][cte_momia] = 1;
		end
		case 2:
		end
		end //switch
    end
	case 5:
		enem_grafs[0][cte_blobo] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/sandbug.fpg");
		enem_grafs[0][cte_murcielago] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/murphy.fpg");
		enem_grafs[0][cte_spider] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/stomp.fpg");
		enem_grafs[0][cte_bolargy] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/bolargy.fpg");
		enem_grafs[0][cte_spikes] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/atl_spike.fpg");
		enem_grafs[0][cte_excaver] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/excaver01.fpg");
		enem_grafs[0][cte_rock] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/rock_lvl4.fpg");
		
		enem_grafs[1][cte_blobo] = 1;
		enem_grafs[1][cte_murcielago] = 1;
		enem_grafs[1][cte_spider] = 1;
		enem_grafs[1][cte_bolargy] = 1;
		enem_grafs[1][cte_spikes] = 1;
		enem_grafs[1][cte_excaver] = 1;
		enem_grafs[1][cte_rock] = 1;
	end
    end //switch
end

function unload_all_enem_fpgs()
private
    int cont;
begin
    for (cont = 0; cont < cte_enem_last; cont++)
        if (enem_grafs[1][cont])
            fpg_unload(enem_grafs[0][cont]);
            enem_grafs[1][cont] = 0;
        end
    end
end

//**************************************************************************************************

function cargar_sfx_nivel (int csn_nivel)
begin
    switch (csn_nivel)
    case 1:
        sfx_id[0][cte_sfx_door] = sound_load(dreamcast_ruta + "sfx/door.wav");
        sfx_id[0][cte_sfx_bridge] = sound_load(dreamcast_ruta + "sfx/bridge.wav");
        
        sfx_id[1][cte_sfx_door] = 1;
        sfx_id[1][cte_sfx_bridge] = 1;
    end
    case 3:
        sfx_id[0][cte_sfx_shot] = sound_load(dreamcast_ruta + "sfx/shot.wav");
        sfx_id[0][cte_sfx_door] = sound_load(dreamcast_ruta + "sfx/door.wav");
        sfx_id[0][cte_sfx_bridge] = sound_load(dreamcast_ruta + "sfx/bridge.wav");
        
        sfx_id[1][cte_sfx_shot] = 1;
        sfx_id[1][cte_sfx_door] = 1;
        sfx_id[1][cte_sfx_bridge] = 1;
    end
    case 4:
        sfx_id[0][cte_sfx_door] = sound_load(dreamcast_ruta + "sfx/door.wav");
        sfx_id[0][cte_sfx_bridge] = sound_load(dreamcast_ruta + "sfx/bridge.wav");
        
        sfx_id[1][cte_sfx_door] = 1;
        sfx_id[1][cte_sfx_bridge] = 1;
    end
    end //switch
end

function descargar_sfx_nivel (int csn_nivel)
begin
    switch (csn_nivel)
    case 1:
        sound_unload(sfx_id[0][cte_sfx_door]);
        sound_unload(sfx_id[0][cte_sfx_bridge]);
        
        sfx_id[1][cte_sfx_door] = 0;
        sfx_id[1][cte_sfx_bridge] = 0;
    end
    case 3:
        sound_unload(sfx_id[0][cte_sfx_shot]);
        sound_unload(sfx_id[0][cte_sfx_door]);
        sound_unload(sfx_id[0][cte_sfx_bridge]);
            
        sfx_id[1][cte_sfx_shot] = 0;
        sfx_id[1][cte_sfx_door] = 0;
        sfx_id[1][cte_sfx_bridge] = 0;
    end
    case 4:
		sound_unload(sfx_id[0][cte_sfx_door]);
        sound_unload(sfx_id[0][cte_sfx_bridge]);
        
        sfx_id[1][cte_sfx_door] = 0;
        sfx_id[1][cte_sfx_bridge] = 0;
    end
    end //switch
end

//**************************************************************************************************

function cargar_sfx_arma ()
begin
    switch (armas_select)               //y después cargamos los nuevos
    case 1:
        disparo_wav[0][0] = sound_load(dreamcast_ruta + "sfx/laser0.wav");
        disparo_wav[0][1] = sound_load(dreamcast_ruta + "sfx/laser1.wav");
        disparo_wav[0][2] = sound_load(dreamcast_ruta + "sfx/laser2.wav");
        disparo_wav[1][0] = 1;
        disparo_wav[1][1] = 1;
        disparo_wav[1][2] = 1;
    end
    case 2:
        disparo_wav[0][0] = sound_load(dreamcast_ruta + "sfx/leafblade0.wav");
        disparo_wav[0][1] = sound_load(dreamcast_ruta + "sfx/leafblade1.wav");
        disparo_wav[0][2] = sound_load(dreamcast_ruta + "sfx/leafblade2.wav");
        disparo_wav[1][0] = 1;
        disparo_wav[1][1] = 1;
        disparo_wav[1][2] = 1;
    end
    case 3:
        disparo_wav[0][0] = sound_load(dreamcast_ruta + "sfx/greencat0.wav");
        disparo_wav[0][1] = sound_load(dreamcast_ruta + "sfx/greencat1.wav");
        disparo_wav[0][2] = sound_load(dreamcast_ruta + "sfx/greencat2.wav");
        disparo_wav[1][0] = 1;
        disparo_wav[1][1] = 1;
        disparo_wav[1][2] = 1;
    end
    case 4:
        disparo_wav[0][0] = sound_load(dreamcast_ruta + "sfx/BOMBA.wav");
        disparo_wav[0][1] = sound_load(dreamcast_ruta + "sfx/BOMBA.wav");
        disparo_wav[0][2] = sound_load(dreamcast_ruta + "sfx/BOMBA.wav");
        disparo_wav[1][0] = 1;
        disparo_wav[1][1] = 1;
        disparo_wav[1][2] = 1;
    end
    end //switch
end

function descargar_sfx_arma ()
begin
    //carga de sonidos
    if (disparo_wav[1][0])              //primero descargamos los anteriores
        sound_unload(disparo_wav[0][0]);
        disparo_wav[1][0] = 0;
    end
    if (disparo_wav[1][1])
        sound_unload(disparo_wav[0][1]);
        disparo_wav[1][1] = 0;
    end
    if (disparo_wav[1][2])
        sound_unload(disparo_wav[0][2]);
        disparo_wav[1][2] = 0;
    end
end

function cambiar_sfx_arma ()
begin
    descargar_sfx_arma();
    cargar_sfx_arma();
end
