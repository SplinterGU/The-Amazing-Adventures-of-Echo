CONST
	//constantes de las armas
    CTE_LAST_WEAPON = 4;	//Indica el número de armas disponibles en el juego
END
	
GLOBAL
	int  armas_file;
    byte armas_get[CTE_LAST_WEAPON] = 1,0,0,0,0;
    //byte armas_get[3] = 0,1,1,1;
    int  armas_select;
    int  armas_curr_level;
	
	int  armas_level[CTE_LAST_WEAPON][3];         //0:nivel del arma  1:max nivel 1   2:max nivel 2   3:max nivel 3
    byte armas_damage[CTE_LAST_WEAPON][2];        //daño que hace cada arma
	
	int  armas_animation[]=0,                             //sin arma
                           0,                             //sin arma
                           0,                             //sin_arma
                           0,                             //sin arma, vertical
                           0,                             //sin arma, vertical
                           0,                             //sin_arma, vertical
                           1,501,                           //normal shot lvl 1
                           1,502,                           //normal shot lvl 2
                           1,503,                           //normal shot lvl 3
                           1,504,                           //normal shot lvl 1, vertical
                           1,505,                           //normal shot lvl 2, vertical
                           1,506,                           //normal shot lvl 3, vertical
                           8,512,513,514,514,514,514,513,512,   //espada lvl 1
                           8,515,516,517,517,517,517,516,515,   //espada lvl 2
                           8,518,519,520,520,520,520,519,518,   //espada lvl 3
                           1,527,                               //espada slash
                           0,
                           0,
                           1,521,                           //normal shot lvl 1
                           1,522,                           //normal shot lvl 2
                           1,523,                           //normal shot lvl 3
                           1,524,                           //normal shot lvl 1, vertical
                           1,525,                           //normal shot lvl 2, vertical
                           1,526,                           //normal shot lvl 3, vertical
                           0,                             //bomba lvl 1
                           0,                             //bomba lvl 2
                           0,                             //bomba lvl 3
                           0,                             //bomba lvl 1, vertical
                           0,                             //bomba lvl 2, vertical
                           0;                             //bomba lvl 3, vertical
	
	//Sonido
    int disparo_wav[1][2];
END