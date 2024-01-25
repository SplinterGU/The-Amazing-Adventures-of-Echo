type tscroll
	//datos del scroll
	int ts_file;		//fpg cargado para el scroll
	int n_columnas;		//nº de tiles de ancho del mapa visible
	int n_filas;		//nº de tiles de alto del mapa visible
	int n_capas;		//nº de tiles de altura del mapa visible
	int tiles_extra_x;	//tiles que no se verán a los lados, pero que estan por si
						//cargan información, por ejemplo, generan enemigos...
                        //un valor de 4 hace que haya 2 tiles a cada lado que no se
                        //ven
	int tiles_extra_y; //idem por arriba y por abajo
	
	int ts_region;    //nº de region usada por este scroll
	int ini_reg_x;    //pos x de la esquina superior izquierda de la region
	int ini_reg_y;    //pos y de la esquina superior izquierda de la region
	int ancho_reg;    //ancho en pixels de la region
	int alto_reg;     //alto en pixels de la region
	int tscroll_flags;      //1= scroll cíclico horizontalmente
							//2= scroll cíclico verticalmente
	  
	//int zoom;			//zoom del mapa de tiles (200 hace que los tiles se vean el doble de grandes)
	//int z1;			//Z de la capa 0 de tiles
	//int zn;			//incrementos de cada capa (capa1 = z1+zn, capa2 = z1+(2*zn), capaN = z1+(N*zn))
	int estado;		//Estado del scroll: 0 = ACTIVO		1 = INACTIVO(pausa)		-1 = MUERTO
	int forzar_refresco;	//poner a 1 si se quiere refrescar toda la info
      
	//datos del mapa
	t_mapa pointer tmapa;  //indica la estructura del mapa que va a usar
	
	//variables de camara
	int camera_x;    //posicion x de la camara
	int camera_y;    //posicion y de la camara
	int camera_x1;   //posición x de la camara en el primer mapa
	int camera_y1;   //posición y de la camara en el primer mapa
	int camera_tx;   //posicion tile x de la camara
	int camera_ty;   //posicion tile y de la camara
	int camera_tx1;  //posicion tile x de la camara en el primer mapa
	int camera_ty1;  //posicion tile y de la camara en el primer mapa
	int camera_x_tile; //posicion de la camara dentro de un tile (modulo)
	int camera_y_tile; //posicion de la camara dentro de un tile (modulo)
	//variables del proceso a seguir con la cámara
	int id_target;   //id del proceso a seguir con la camara
	int cam_desp_x;  //indica cuanto debe ir la camara por delante del id_target
	int cam_desp_y;  //indica cuanto debe ir la camara por encima del id_target
							
	//variables que manejan los procesos para el scroll
	//int id_tscroll;  //id del proceso de la posicion (0,0,0)
	int id_control;  //id del prodeso de control (coordenadas del mapa 1...)

	//variables de los mapas usados para dibujar los tiles sobre ellos
	int mapadibujo_ancho;	//Ancho de los mapas
	int mapadibujo_alto;	//Alto de los mapas
	int mapadibujo_tx;		//Pos horizontal del tile que queda más arriba a la izquierda en el mapa
	int mapadibujo_ty;		//Pos vertical del tile que queda más arriba a la izquierda en el mapa
	int pointer ptr_array_tiles;	//puntero a array que indica qué tile se ha almacenado en cada posición
									//de los mapas de dibujado
	int n_filas_x_columnas;	//valor para ahorrar cálculos, que indica el número de tiles por capa del mapa visible
	//variables de los scrolls usados para poner los mapas
	int scroll_primero;
	int scroll_ultimo;
	
	//variables auxiliares para ahorrar cálculos
	int ancho_mapa;    //guarda el ancho del mapa cargado en pixels
	int alto_mapa;     //guarda el alto del mapa cargado en pixels
	int n_tiles_capa;  //almacena cuantos tiles hay por capa
	//int tileador_posx; //posicion inicial horizontal del array de procesos
	//int tileador_posy; //posicion inicial vertical del array de procesos
	//int visible_tx;    //posición x en el mapa del primer tile visible (esquina superior izquierda)
	//int visible_ty;    //posición y en el mapa del primer tile visible (esquina superior izquierda)
	//int visible_tx1;   //posición x en el mapa del primer tile visible, respecto al primer mapa
	//int visible_ty1;   //posición y en el mapa del primer tile visible, respecto al primer mapa
		
	int camera_tx_ant;	//Almacena posición de tile de cámara en el frame anterior
	int camera_ty_ant;	//Almacena posición de tile de cámara en el frame anterior
	int camera_x_tile_ant;	//Almacena posición absoluta de camara en frame anterior
	int camera_y_tile_ant;	//Almacena posición absoluta de camara en frame anterior
end


CONST
	CTE_TSCROLL_ESTADO_ACTIVO	= 0;
	CTE_TSCROLL_ESTADO_INACTIVO	= 1;
	CTE_TSCROLL_ESTADO_MUERTO	= -1;
END

LOCAL
     int x2;    //indica la coordenada x de cada proceso dentro del scroll tileado
     int y2;    //indica la coordenada y de cada proceso dentro del scroll tileado
     int z2;    //indica la coordenada z de cada proceso dentro del scroll tileado (scroll isométrico)
     int tscroll_ptr_sig;        //apunta al siguiente tile en la lista de tiles
END
