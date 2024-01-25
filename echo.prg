PROGRAM The_amazing_adventures_of_Echo;

include "src/import.inc";

#define init_bgd1_background_emulation() background.file = 0; background.graph = map_new(320,240)
#define put_screen(f,g) map_clear(0, background.graph ); map_put(0, background.graph, f, g, 160, 120)
#define clear_screen() map_clear(0, background.graph )
#define put( f, g, x, y ) map_put(0, background.graph, f, g, x, y)
#define map_xput(fdst,gdst,gsrc,x,y,angle,size,flags) map_put(fdst, gdst, fdst, gsrc, x, y, angle, size, size, flags, 255, 255, 255, 255)

include "src/main.h";

include "src/tscroll/tmapa.h";
include "src/tscroll/tscroll.h";
//include "src/tscroll/graph_tscroll.h";
include "src/input/jkey.h";
include "src/game/level_play/generic_map.h";
include "src/main_menu/configuration.h";
include "src/save/global_save.h";

include "src/level_select/level_select_menu.h";

include "src/sound/sound.h";
include "src/game/enemies/enemigos.h";
include "src/game/prota/weapons.h";
include "src/game/game.h";
include "src/game/prota/prota.h";
include "src/game/prota/prota_moto.h";
include "src/sound/volume_control.h";
include "src/sound/music_control.h";
include "src/game/interface/interfaz.h";
include "src/save/savegame.h";

//KEY INPUT CODE
include "src/input/jkey.inc";
// include "src/input/jkey_gp2x.inc";
// include "src/input/jkey_dingux.inc";

//SOUND CODE
include "src/sound/volume_control.inc";
include "src/sound/music_control.inc";
//MENUS CODE
include "src/main_menu/default_menu.inc";
//TILED SCROLL CODE
include "src/tscroll/load_tmap.inc";
include "src/tscroll/tscroll.inc";
//include "src/tscroll/graph_tscroll.inc";
include "src/tscroll/tmapa.inc";
//SIGNALS CODE
include "src/game/signals.inc";
include "src/game/signals_event.inc";
include "src/game/pause.inc";
//BOSSES CODE
include "src/game/bosses/level01/boss_01.3.01.inc";
include "src/game/bosses/level01/boss_01.3.02.inc";
include "src/game/bosses/level01/boss_01.3.02_weapons.inc";
include "src/game/bosses/level01/boss_01.4.01.inc";
include "src/game/bosses/level03/boss_03.1.01.inc";
include "src/game/bosses/level03/boss_03.1.02.inc";
include "src/game/bosses/level04/boss_04.4.01.inc";
//EVENTS CODE
include "src/game/bosses/level01/boss_01_intro.inc";
include "src/game/bosses/level03/boss_03_intro.inc";
include "src/game/events/event_01.03.01.inc";
include "src/game/events/event_01.03.02.inc";
include "src/game/events/event_01.04.01.inc";
include "src/game/events/event_03.01.inc";
include "src/game/events/event_03.02.inc";
include "src/game/events/event_03.03.inc";
include "src/game/events/event_04.04.inc";
include "src/game/events/event_05.01.inc";
include "src/game/events/events.inc";
include "src/game/events/events_game.inc";
//OTHERS CODE
include "src/game/common/shot_collision.inc";

//INTERFACE CODE
include "src/game/interface/interface.inc";
include "src/game/interface/interface_control.inc";
include "src/game/interface/interface_boss.inc";
include "src/game/interface/cartel_partida_guardada.inc";
//ITEMS CODE
include "src/game/items/item_press_down.inc";
include "src/game/items/items_functions.inc";
include "src/game/items/items.inc";
include "src/game/items/item_end_level.inc";
include "src/game/items/item_new_weapon.inc";
include "src/game/items/item_max_energy.inc";
include "src/game/items/item_checkpoint.inc";
//SPECIAL TILES CODE
include "src/game/special_tiles/animated_tiles.inc";
include "src/game/special_tiles/interactive_tiles.inc";
include "src/game/special_tiles/dissapearing_platforms.inc";
include "src/game/special_tiles/moving_platforms.inc";
include "src/game/special_tiles/damage_tiles.inc";
//ENEMIES CODE
include "src/game/enemies/enemigos_vision.inc";
include "src/game/enemies/enemigos_fx.inc";
include "src/game/enemies/enemigos_weapons.inc";
include "src/game/enemies/enemigos.inc";
include "src/game/enemies/enem_blobo.inc";
include "src/game/enemies/enem_canon.inc";
include "src/game/enemies/enem_corvo.inc";
include "src/game/enemies/enem_excaver.inc";
include "src/game/enemies/enem_flozat.inc";
include "src/game/enemies/enem_ghost_fly.inc";
include "src/game/enemies/enem_ghost_fly_invencible.inc";
include "src/game/enemies/enem_glotz.inc";
include "src/game/enemies/enem_guerrillero.inc";
include "src/game/enemies/enem_invencible.inc";
include "src/game/enemies/enem_mina.inc";
include "src/game/enemies/enem_murcielago.inc";
include "src/game/enemies/enem_roca_rodante.inc";
include "src/game/enemies/enem_spider.inc";
include "src/game/enemies/enem_spikes.inc";
include "src/game/enemies/enem_super_guerrillero.inc";
include "src/game/enemies/enem_vigilante_horus.inc";
include "src/game/enemies/enem_volador1.inc";
include "src/game/enemies/enem_volador2.inc";
include "src/game/enemies/enem_volador3.inc";
include "src/game/enemies/enem_momia.inc";
//PROTA CODE
include "src/game/prota/prota_tools.inc";
include "src/game/prota/weapons.inc";
include "src/game/prota/prota.inc";
include "src/game/prota/prota_moto.inc";
//LEVEL PLAY CODE
include "src/game/level_play/intro_nivel.inc";

//CREDITS
include "src/game/credits.inc";

//PRE-GAME CODE
include "src/params.inc";
include "src/pregame/logos.inc";
include "src/main_menu/main_menu.inc";
//SAVE CODE
include "src/game/level_play/sav_item_list.inc";
include "src/save/global_save.inc";
include "src/save/savegame.inc";
include "src/save/savegame_menu.inc";
//GAME CODE
include "src/game/level_play/generic_map.inc";
include "src/game/level_play/carga_media.inc";
include "src/game/sync_counter.inc";
include "src/game/game_background.inc";
include "src/game/level_play/backgrounds.inc";
include "src/game/level_play/foregrounds.inc";
include "src/game/level_play/play_level.inc";
include "src/game/level_play/level_select.inc";
//LEVEL SELECT CODE
include "src/level_select/level_select_menu_func_nextprev.inc";
include "src/level_select/level_select_menu_levels_images.inc";
include "src/level_select/level_select_menu_cursores.inc";
include "src/level_select/level_select_menu.inc";
//MAIN MENU
include "src/main_menu/configuration.inc";
include "src/main_menu/configuration_keys.inc";
include "src/main_menu/configuration_joy.inc";
include "src/main_menu/configuration_menu.inc";

include "src/game/game.inc";

PRIVATE
	int cont;
	int g_end_level;

BEGIN
	//say("INICIANDO ECHO");
    //primera inicialización
	//dump_type = 1;
	//restore_type = 1;
    //set_fps(50, cte_frameskip);
	//set_fps(3,0);
    //fpsdebug();
	leer_parametros();
    switch (os_id)
    case 0..3://,OS_WII:
		window_set_title("The amazing adventures of Echo v1.3.4");
        if (fexists(get_pref_path("bennugd.org", "echo") + "echo.cfg"))
            load_config();
        else
            create_default_config(0);
            save_config();
        end
        screen.fullscreen = 0;
		//scale_resolution=9600720;
//        scale_mode = scale_nofilter;
        inicia_teclas(0);
//		alpha_steps = 64;
		//mode_frameless
        GP2X_mode = 0;
    end
    case OS_GP2X_WIZ, OS_CAANOO:
        if (fexists(get_pref_path("bennugd.org", "echo") + "echo.cfg"))
            load_config();
        else
            create_default_config(1);
            save_config();
        end
        screen.fullscreen = 1;
        inicia_teclas(1);
        GP2X_mode = 1;
    end
	case OS_DC:
		dreamcast_ruta = "/dc/";
		if (fexists(get_pref_path("bennugd.org", "echo") +  "echo.cfg"))
            load_config();
        else
            create_default_config(0);
            save_config();
        end
		screen.fullscreen = 1;
//        scale_mode = scale_nofilter;
        inicia_teclas(0);
//		alpha_steps = 64;
		//mode_frameless
        GP2X_mode = 0;
	end
	case OS_DINGUX_A320:
		if (fexists(get_pref_path("bennugd.org", "echo") + "echo.cfg"))
			load_config();
        else
			create_default_config(3);
            save_config();
        end
        screen.fullscreen = 1;
        inicia_teclas(0);
		GP2X_mode = 0;
    end
    default:
        if (fexists(get_pref_path("bennugd.org", "echo") + "echo.cfg"))
            load_config();
        else
            create_default_config(2);
            save_config();
        end
        screen.fullscreen = 1;
        inicia_teclas(0);
        GP2X_mode = 0;
    end
    end //switch
	say("INICIO DE LA CONFIGURACION");
    
    //Carga de la configuración salvada
    switch (config_data.tipo_graficos)
    case 1: graph_dir = "stylish"; end
    default: graph_dir = "classic"; end
    end //switch
    cte_frameskip = config_data.cte_frameskip;
    set_fps(50, cte_frameskip);
    game_background_scroll = config_data.usar_scroll_fondo;
    game_foreground_scroll = config_data.usar_scroll_frontal;
    
    screen.scale_resolution = 06400480;
//    screen.scale_resolution_aspectratio = SRA_PRESERVE;

    set_mode(320, 240);

	say("SET MODE COMPLETE");

    init_bgd1_background_emulation();
    
    /*frame;
    say("OS_ID: "+os_id);
    for (energia=0;energia<k_last;energia++)
        say(teclas[energia][1]);
    end*/
    
    
    prota_control = 1;
//    if (GP2X_mode)
//        ctrl_teclas_gp2x();
//    else
        ctrl_teclas();
//    end
	init_musica();
    musica();
    volume_control();
	say("PROCESOS DE CONTROL ACTIVOS");
    
    //global_menu(1,"Continue","Exit","","","");
    //global_menu(2,"Easy (5 lives)","Medium (3 lives)","Hard (1 live)","","");
    
    //logos
    logos();
    signal(id,s_sleep);
    frame;
	say("LOGOS OK");
    
    //resto
    //global_mode = CTE_GLOBAL_MODE_DEBUG; //test
	global_mode = CTE_GLOBAL_MODE_PORTADA;
	//global_mode = CTE_GLOBAL_MODE_LEVELSELECT;
    //global_mode = CTE_GLOBAL_MODE_CREDITOS;
    loop
        switch (global_mode)
        case CTE_GLOBAL_MODE_PORTADA:     //MENU PRINCIPAL
			say("Iniciando portada *****************");
            portada();
            signal(id,s_sleep);
            frame;
        end
        /*case 1:     //MENU CONFIGURACION TECLAS
        end*/
        case CTE_GLOBAL_MODE_LEVELSELECT:     //MENU SELECCION NIVEL
            //level_select();
            level_select_menu();
            signal(id,s_sleep);
            frame;
        end
		case CTE_GLOBAL_MODE_PLAYLEVELSELECT:	//JUGAR NIVEL SELECCIONADO
			level_select_play_level();
            signal(id,s_sleep);
            frame;
		end
        case CTE_GLOBAL_MODE_JUEGO:     //JUEGO
            game();
            signal(id,s_sleep);
            frame;
            //say("Hola");
            //global_mode=0;
        end
        case CTE_GLOBAL_MODE_CREDITOS:     //CREDITOS
            credits();
            signal(id,s_sleep);
            frame;
        end
        case CTE_GLOBAL_MODE_SALIR:   //SALIR
            //say("final");
            break;
        end
        case CTE_GLOBAL_MODE_DEBUG:
            /*prota_file = fpg_load("grafs/"+ graph_dir + "/prota.fpg");
            armas_file = fpg_load("grafs/"+ graph_dir + "/weapons.fpg");
            init_weapons();
            armas_select = 1;
            enem_grafs[0][0] = fpg_load("grafs/"+ graph_dir + "/blobo.fpg");
            item_grafs = fpg_load("grafs/"+ graph_dir + "/items.fpg");
            //say("cargado "+itoa(prota_file));
            if (load_tmf("levels/CSal3.dur", &durezas))
            //if (load_tmf("../FenixLand/IFenix2.tmf",&durezas))
                start_tscroll(&id_tscroll, &durezas, 0, 0, 0, 320, 240, 4, 4, 16, 16, 0);
                id_tscroll.ts_file = fpg_load("levels/durezas.fpg");
                ts_actualiza_tiles(&id_tscroll);
                //id_tscroll.id_target=prota_moto();
                id_tscroll.id_target = prota(9, 2);
                global_mode = CTE_GLOBAL_MODE_SALIR;
                while (teclas[k_esc][2] == 0) frame; end
                
                fpg_unload(id_tscroll.ts_file);
                fpg_unload(prota_file);
            else
                say("no se encuentra el mapa");
                global_mode = CTE_GLOBAL_MODE_SALIR;
            end*/
			
			//for (global_opt = 0; global_opt < 9; global_opt++)
			/*global_opt = 3;
				say("LEYENDO FICHERO " + global_opt + " **************************");
				load_filegame (&game_global_sav, global_opt);
				savegame_item_got_list_say();
				savegame_item_got_list_delete(2);
				savegame_item_got_list_say();
				savegame_item_got_list_delete_all();
				savegame_item_got_list_say();
			//end*/
			
			next_level = 4;
			next_sublevel = 1;
			init_level = 0;
			//ls_intro = 1;
			//ls_intro = 0;
			//ls_show_saved = 0;
			//ls_estado_end_level = 0;
			
			armas_select=0; 
			armas_get[0]=0;
			armas_get[1]=1;
			armas_get[2]=1;
			armas_get[3]=1;
			armas_get[4] = 0;
			info_prota.vidas = 5;
			
			info_prota.p_max_energ = 64;
			info_prota.p_energ = 64;
			global_mode = CTE_GLOBAL_MODE_PLAYLEVELSELECT;
			
			//***************************************************************
			
			/*next_level = 4;
			next_sublevel = 1;
			init_level = 0;
			
			end_level = 0;
			
			prota_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/prota.fpg");
			armas_file = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/weapons.fpg");
			//init_weapons();
			armas_select = 0;
			armas_curr_level = 0;
			armas_select=1; 
			armas_get[0]=0;
			armas_get[1]=1;
			armas_get[2]=1;
			armas_get[3]=1;
			info_prota.vidas=1;
			
			item_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/items.fpg");
			checkpoint_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/checkpoint.fpg");
			explosion_grafs = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/explos.fpg");
			
			pausa();
			load_interface();
			
			for (cont = 0; cont <= cte_interruptores; cont++)
				interruptores[cont] = 0;
			end
			info_prota.p_invencible = 2;
			info_prota.p_energ = 10;
			info_prota.p_max_energ = 64;
			armas_level[0][0] = 1;
			armas_level[1][0] = 1;
			armas_level[2][0] = 1;
			armas_level[3][0] = 1;
			armas_level[0][1] = 1;
			armas_level[1][1] = 1;
			armas_level[2][1] = 1;
			armas_level[3][1] = 1;
			init_weapons();
			
			//carga de gráficos de enemigos
            cargar_graficos_enemigos(1);
            
            enem_grafs[0][cte_level] = fpg_load(dreamcast_ruta + "grafs/" + graph_dir + "/level01bg.fpg");
            enem_grafs[1][cte_level] = 1;
            
            
            cargar_sfx_nivel(1);
            //say("Datos cargados");
            
			g_end_level = 0;
            play_level(next_level, next_sublevel, init_level, 0, 0, &g_end_level);
            signal(id,s_sleep);
            frame;
			
			
			unload_interface();
			if (exists(get_id(type pausa))) signal(get_id(type pausa),s_kill); end
			pausa_estado = 0;
			
			signal_items(s_kill);
            signal_enemigos(s_kill);
            signal_event_all(s_kill);
            signal_tiles_especiales(s_kill);
            
            unload_all_enem_fpgs();
            
            sound_stop(-1);
            descargar_sfx_nivel(1);
            
            unset_interface();
			
			//say("Descargando fpgs");
			fpg_unload(prota_file);
			fpg_unload(armas_file);
			fpg_unload(item_grafs);
			fpg_unload(checkpoint_grafs);
			fpg_unload(explosion_grafs);
			//descarga de sonidos de disparo (si procede)
			//say("Descargando sfx arma");
			descargar_sfx_arma();
			
			global_mode = CTE_GLOBAL_MODE_SALIR;*/
        end
        end //switch
    end
    
    let_me_alone();
END

process fpsdebug ()
begin
    loop
        if (key(_f1)) set_fps(50,0); end
        if (key(_f2)) set_fps(3,0); end
        if (key(_f3)) set_fps(1,0); end
        
        if (key(_f5)) info_prota.p_energ--; refresh_interface_energy(); end
        if (key(_f6)) info_prota.p_energ++; refresh_interface_energy(); end
        if (teclas[k_previous][2] == 1)
            //search_start_point(&nivel, &durezas, 0, &x2, &y2);
            shot_exp(x2, y2, 5, 10);
            shot_exp(x2, 10, 1, 10);
        end
        //if (teclas[k_next][2]==1) shot_exp(x2,10,-1,10); end
        frame;
    end
end
