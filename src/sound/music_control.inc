function init_musica ()
begin
	music_path_level01a = dreamcast_ruta + "music/horror.mp3";
	music_path_level01b = dreamcast_ruta + "music/horror_loop.mp3";
	music_path_level03a = dreamcast_ruta + "music/city.mp3";
	music_path_level03b = dreamcast_ruta + "music/city_loop.mp3";
	music_path_level0402a = dreamcast_ruta + "music/water_caves.mp3";
	
	music_path_midboss_a = dreamcast_ruta + "music/mboss.mp3";
	music_path_midboss_b = dreamcast_ruta + "music/mboss_loop.mp3";
	music_path_finalboss_a = dreamcast_ruta + "music/fboss.mp3";
	music_path_finalboss_b = dreamcast_ruta + "music/fboss_loop.mp3";
	
	music_path_maintheme = dreamcast_ruta + "music/echo_theme.mp3";
	
	music_path_weaponget = dreamcast_ruta + "music/wget.mp3";
	music_path_endlevel = dreamcast_ruta + "music/end_level.mp3";
	music_path_gameover = dreamcast_ruta + "music/game_over.mp3";
	music_path_credits = dreamcast_ruta + "music/credits.mp3";
	music_path_the_end = dreamcast_ruta + "music/the_end.mp3";
end

process musica ()
private
	int ant_musica;
begin
    loop
        switch (level_song)
		
		//LEVEL MUSIC ****************************************************************************************
        case _CTE_MUSIC_LEVEL01:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_level01a);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (ant_musica == level_song)
                music_unload(level_song_id[0]);
                level_song_id[0] = music_load(music_path_level01b);
                music_play(level_song_id[0], -1);
                
				while (ant_musica == level_song)
					frame;
				end
            end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
        case _CTE_MUSIC_LEVEL03:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_level03a);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (ant_musica == level_song)
                music_unload(level_song_id[0]);
                level_song_id[0] = music_load(music_path_level03b);
                music_play(level_song_id[0], -1);
				
                while (ant_musica == level_song)
					frame;
				end
            end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
        case _CTE_MUSIC_LEVEL04_2:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_level0402a);
            level_song_id[1] = 1;
            music_play(level_song_id[0],-1);
            while (ant_musica == level_song) frame; end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
		
        //BOSSES *******************************************************************************
        case _CTE_MUSIC_MIDBOSS:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_midboss_a);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (ant_musica == level_song)
                music_unload(level_song_id[0]);
                level_song_id[0] = music_load(music_path_midboss_b);
                music_play(level_song_id[0], -1);
				
                while (ant_musica == level_song)
					frame;
				end
            end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
        case _CTE_MUSIC_FINALBOSS:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_finalboss_a);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (ant_musica == level_song)
                music_unload(level_song_id[0]);
                level_song_id[0] = music_load(music_path_finalboss_b);
                music_play(level_song_id[0], -1);
				
                while (ant_musica == level_song)
					frame;
				end
            end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
		
        //PORTADA *****************************************************************************
        case _CTE_MUSIC_MAINTITLE:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_maintheme);
            level_song_id[1] = 1;
            music_play(level_song_id[0],-1);
            while (ant_musica == level_song) frame; end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
		
        //FANFARRIAS ***************************************************************************************
        case _CTE_MUSIC_WEAPONGET:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_weaponget);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            if (ant_musica == level_song)
                level_song = _CTE_MUSIC_NOMUSIC;
                ant_musica = 0;
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
        case _CTE_MUSIC_ENDLEVEL:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_endlevel);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            if (ant_musica == level_song)
                level_song = _CTE_MUSIC_NOMUSIC;
                ant_musica = 0;
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
        case _CTE_MUSIC_GAMEOVER:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_gameover);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            if (ant_musica == level_song)
                level_song = _CTE_MUSIC_NOMUSIC;
                ant_musica = 0;
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
        case _CTE_MUSIC_CREDITS:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_credits);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            if (ant_musica == level_song)
                level_song = _CTE_MUSIC_NOMUSIC;
                ant_musica = 0;
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
		case _CTE_MUSIC_THE_END:
            ant_musica = level_song;
            level_song_id[0] = music_load(music_path_the_end);
            level_song_id[1] = 1;
            music_play(level_song_id[0],0);
            while ((ant_musica == level_song) && (music_is_playing())) frame; end
            
            if (music_is_playing())
                music_fade_off(2500);
                frame (12500);
            end
            if (ant_musica == level_song)
                level_song = _CTE_MUSIC_NOMUSIC;
                ant_musica = 0;
            end
            music_unload(level_song_id[0]);
            level_song_id[1] = 0;
        end
        end //switch
        frame;
    end
end