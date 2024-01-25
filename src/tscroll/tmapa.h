type t_mapa
     //datos del mapa
     int version;
     int filas;
     int columnas;
     int capas;
     int tipo_dato;
     int ancho_tile;
     int alto_tile;
     int desplaz_tile;           //para scroll normal, desplazamiento vertical de cada capa
                                 //para scroll isométrico, altura hacia arriba
     string fpg;
     int16 tipo_mapa;
     //contenido del mapa
//     byte pointer b_mapa;
//     int16 pointer w_mapa;
//     int32 pointer i_mapa;
     int pointer b_mapa;
//     int pointer w_mapa;
//     int pointer i_mapa;
     int fpg_mapa;
     //gestion de mapas (por si se almacenan los datos en lista enlazada)
     int id;
// jjp    t_mapa pointer sig;
     int pointer sig;
     byte null2;
end
