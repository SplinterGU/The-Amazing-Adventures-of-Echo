CONST
	_CTE_MUSIC_NOMUSIC		= 0;
	_CTE_MUSIC_LEVEL01		= 1;
	_CTE_MUSIC_LEVEL03		= 3;
	_CTE_MUSIC_LEVEL04_2	= 5;
	
	_CTE_MUSIC_MIDBOSS		= 25;
	_CTE_MUSIC_FINALBOSS	= 26;
	
	_CTE_MUSIC_MAINTITLE	= 50;
	
	_CTE_MUSIC_WEAPONGET	= 100;
	_CTE_MUSIC_ENDLEVEL		= 105;
	_CTE_MUSIC_GAMEOVER		= 106;
	_CTE_MUSIC_CREDITS		= 107;
	_CTE_MUSIC_THE_END		= 108;
END

GLOBAL
	string music_path_level01a; //= dreamcast_ruta + "music/horror.mp3";
	string music_path_level01b; //= dreamcast_ruta + "music/horror_loop.mp3";
	string music_path_level03a; //= dreamcast_ruta + "music/city.mp3";
	string music_path_level03b; //= dreamcast_ruta + "music/city_loop.mp3";
	string music_path_level0402a; //= dreamcast_ruta + "music/water_caves.mp3";
	
	string music_path_midboss_a; //= dreamcast_ruta + "music/mboss.mp3";
	string music_path_midboss_b; //= dreamcast_ruta + "music/mboss_loop.mp3";
	string music_path_finalboss_a; //= dreamcast_ruta + "music/fboss.mp3";
	string music_path_finalboss_b; //= dreamcast_ruta + "music/fboss_loop.mp3";
	
	string music_path_maintheme; //= dreamcast_ruta + "music/echo_theme.mp3";
	
	string music_path_weaponget; //= dreamcast_ruta + "music/wget.mp3";
	string music_path_endlevel; //= dreamcast_ruta + "music/end_level.mp3";
	string music_path_gameover; //= dreamcast_ruta + "music/game_over.mp3";
	string music_path_credits; //= dreamcast_ruta + "music/credits.mp3";
	string music_path_the_end; //= dreamcast_ruta + "music/the_end.mp3";
	
	int level_song;
	int level_song_id[1];           //0: id de la musica        1: hay una música cargada
END