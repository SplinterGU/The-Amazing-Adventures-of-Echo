CONST
    INTERFAZ_FONDO_BLANCO = 10;
    INTERFAZ_NUMEROS_ENERGIA = 11;
    INTERFAZ_NUMEROS_EXP = 12;
    INTERFAZ_FONDO_FPG = 13;
    INTERFAZ_ENEM_ENER = 14;//17;
    INTERFAZ_SALVADO1 = 15;//18;
    INTERFAZ_SALVADO2 = 16;//19;
    //Intercambia los valores de las armas para que estén al final
    INTERFAZ_ARMA1 = 17;
    INTERFAZ_ARMA2 = 18;
    INTERFAZ_ARMA3 = 19;
    INTERFAZ_ARMA4 = 20;
    
    INTERFAZ_LAST = 21;
END

GLOBAL
    int interfaz_grafs[INTERFAZ_LAST-1];
	int interfaz_armas_id[cte_last_weapon-1];               //procesos de la interfaz
END
