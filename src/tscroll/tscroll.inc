process tile (x2, y2, z2)
begin
     signal(id, s_freeze);
     frame;
end

//**************************************************************************************
//  FUNCIONES DE MANEJO DE LA LISTA DE TILES
//**************************************************************************************

function tscroll_obtener_tile (tscroll pointer ts_struct, int at_posx, int at_posy, int at_posz)
private
       int dato_a_devolver;
       int at_pos;
begin
     at_pos = (at_posz * [ts_struct].n_tiles_capa) +
              (((/*[ts_struct].camera_ty1*/ + at_posy) % [ts_struct].tmapa[0].filas) *
               [ts_struct].tmapa[0].columnas) +
              ((/*[ts_struct].camera_tx1*/ + at_posx) % [ts_struct].tmapa[0].columnas);
     dato_a_devolver = [ts_struct].tmapa[0].b_mapa[at_pos];
     return (dato_a_devolver);
end

function borrar_tiles_sobrantes (ptr_aux)
//Elimina los procesos tile del final de la lista. Se le pasa como parámetro el último
//tile VÁLIDO (este no se borra)
//NOTA: aprovecha la variable local ptr_sig
begin
     ptr_sig = ptr_aux.ptr_sig;
     ptr_aux.ptr_sig = 0;
     while (ptr_sig != 0)
           ptr_aux = ptr_sig;
           ptr_sig = ptr_sig.ptr_sig;
           signal (ptr_aux, s_kill);
     end
end


function ts_actualiza_tiles (tscroll pointer ts_struct)
// Refresca toda la lista de tiles: añade o quita según sea necesario, y los coloca
//en su posición, les asigna el gráfico...
private
       int temp_x;       //posición x del primer tile
       int temp_y;       //posición y del primer tile
       int cont_x;
       int cont_y;
       int cont_z;
       int ptr_aux;      //puntero auxiliar para leer los tiles de la lista
       int at_posx;
       int at_posy;
       int at_tile;      //almacena temporalmente el tile
       //byte first_tile;   //indica que hay que actualizar el primer tile de la lista
begin
     //Antes que nada, vamos a ver dónde se pone el tile de la esquina superior izqu
     temp_x = [ts_struct].tileador_posx - [ts_struct].camera_x_tile;
     temp_y = [ts_struct].tileador_posy - [ts_struct].camera_y_tile;
     //Ponemos el puntero auxiliar señalando el primer tile de la lista
     //ptr_aux = [ts_struct].id_tscroll;
     ptr_aux = 0;

     //y ahora recorremos tantas posiciones como tiles quepan en pantalla
     for (cont_z = 0; cont_z < [ts_struct].tmapa[0].capas; cont_z++)
         for (cont_y = 0; cont_y < [ts_struct].n_filas; cont_y++)
             //comprobamos si el scroll es cíclico: si no lo es evitaremos los tiles fuera
             //del mapa y ahorraremos cálculos; si lo es, los cálculos son más sencillos
             if (([ts_struct].tscroll_flags & 2) == 0)
                //scroll no cíclico en y
                at_posy = [ts_struct].visible_ty + cont_y;
                if ((at_posy >= 0) && (at_posy < [ts_struct].tmapa[0].filas))
                   //dentro del mapa en y
                   
                   //***********************************************************
                   for (cont_x = 0; cont_x < [ts_struct].n_columnas; cont_x++)
                       //comprobamos si el scroll es cíclico: si no lo es evitaremos los
                       //tiles fuera del mapa y ahorraremos cálculos; si lo es,
                       //los cálculos son más sencillos
                       if (([ts_struct].tscroll_flags & 1) == 0)
                          //scroll no cíclico en x
                          at_posx = [ts_struct].visible_tx + cont_x;
                          if ((at_posx >= 0) && (at_posx < [ts_struct].tmapa[0].columnas))
                             //dentro del mapa en x
                             
                             include "src/tscroll/add_tile.inc";
                          end
                          if (at_posx >= [ts_struct].tmapa[0].columnas)
                             //hemos salido del mapa, pongamos el contador x al final de la cuenta para avanzar
                             //al próximo ciclo en y
                             cont_x = [ts_struct].n_columnas;
                          end
                       else
                           //scroll cíclico en x
                           at_posx = [ts_struct].visible_tx1 + cont_x;
                           //if (at_posx < 0) at_posx += [ts_struct].tmapa[0].columnas; end   //nunca sera negativo
                           at_posx = at_posx % [ts_struct].tmapa[0].columnas;
                           
                           include "src/tscroll/add_tile.inc";
                       end
                   end  //for x
                   //***********************************************************
                   
                end //if dentro mapa
                if (at_posy >= [ts_struct].tmapa[0].filas)
                   //hemos salido del mapa, pongamos el contador y al final de la cuenta para avanzar
                   //al próximo ciclo en z
                   cont_y = [ts_struct].n_filas;
                end
             else
                 //scroll cíclico en y
                 at_posy = [ts_struct].visible_ty1 + cont_y;
                 //if (at_posy < 0) at_posy += [ts_struct].tmapa[0].filas; end  //nunca será negativo
                 at_posy = at_posy % [ts_struct].tmapa[0].filas;
                 
                 //copy/paste de x
                 //***********************************************************
                 for (cont_x = 0; cont_x < [ts_struct].n_columnas; cont_x++)
                     //comprobamos si el scroll es cíclico: si no lo es evitaremos los
                     //tiles fuera del mapa y ahorraremos cálculos; si lo es,
                     //los cálculos son más sencillos
                     if (([ts_struct].tscroll_flags & 1) == 0)
                        //scroll no cíclico en x
                        at_posx = [ts_struct].visible_tx + cont_x;
                        if ((at_posx >= 0) && (at_posx < [ts_struct].tmapa[0].columnas))
                           //dentro del mapa en x

                           include "src/tscroll/add_tile.inc";
                        end
                        if (at_posx >= [ts_struct].tmapa[0].columnas)
                           //hemos salido del mapa, pongamos el contador x al final de la cuenta para avanzar
                           //al próximo ciclo en y
                           cont_x = [ts_struct].n_columnas;
                        end
                     else
                         //scroll cíclico en x
                         at_posx = [ts_struct].visible_tx1 + cont_x;
                         //if (at_posx < 0) at_posx += [ts_struct].tmapa[0].columnas; end    //nunca será negativo
                         at_posx = at_posx % [ts_struct].tmapa[0].columnas;

                         include "src/tscroll/add_tile.inc";
                     end
                 end  //for x
                 //***********************************************************
                 
             end
         end  //for y
     end  //for z
     
     //en este punto, ptr_aux apunta a la última posición, si hay tiles de más sobran,
     //y hay que borrarlos
     if (ptr_aux != 0)                            //el puntero señala al ultimo tile válido
        if (ptr_aux.ptr_sig != 0)                 //borramos los siguientes (si existen)
           borrar_tiles_sobrantes(ptr_aux);
        end
     else                                               //el puntero no señala ningun tile válido
        if ([ts_struct].id_tscroll != 0)                  //comprobamos que hay tiles en la lista
           if ([ts_struct].id_tscroll.ptr_sig != 0)       //y que hay más de uno
              borrar_tiles_sobrantes([ts_struct].id_tscroll);
           end
           signal([ts_struct].id_tscroll, s_kill);
           [ts_struct].id_tscroll = 0;
        end
     end
end


function ts_desplaza_tiles(tscroll pointer ts_struct, int dt_posx, int dt_posy)
private
       int ptr_aux;
begin
     ptr_aux = [ts_struct].id_tscroll;
     while (ptr_aux != 0)
           ptr_aux.x += dt_posx;
           ptr_aux.y += dt_posy;
           ptr_aux = ptr_aux.ptr_sig;
     end
end

//**************************************************************************************
//  FUNCIÓN:    tscroll_control
//              Maneja los procesos tile del scroll, así como su gestión, evitando que
//              estos tengan que ejecutar código alguno (quizás la animación)
//  PARÁMETROS: ts_struct: estructura que almacena los datos del scroll. Si queremos
//                         modificar algo del scroll tendremos que cambiar sus variables,
//                         este proceso ya se encargará de que se cumpla.
//**************************************************************************************
process tscroll_control (tscroll pointer ts_struct)
private
       int camera_tx_ant;
       int camera_ty_ant;
       int camera_x_tile_ant;
       int camera_y_tile_ant;
begin
     //forzamos un refresco completo del scroll
     camera_tx_ant = [ts_struct].camera_tx + 1;
     camera_ty_ant = [ts_struct].camera_ty + 1;
     
     //write(0, 10, 300, 0, "flag vertical: " + ([ts_struct].tscroll_flags & 2));
     //write(0, 10, 310, 0, "flag horizontal: " + ([ts_struct].tscroll_flags & 1));
     loop
         //say("iniciada iteracion");
         //primero cogemos las coordenadas actuales del proceso target
         if ([ts_struct].id_target != 0)
            if (exists([ts_struct].id_target))
               [ts_struct].camera_x = [ts_struct].id_target.x2 + [ts_struct].cam_desp_x - ([ts_struct].ancho_reg / 2);
               [ts_struct].camera_y = [ts_struct].id_target.y2 + [ts_struct].cam_desp_y - ([ts_struct].alto_reg / 2);
               //Impedimos que se pase de los bordes del mapa si no es cíclico
               if (([ts_struct].tscroll_flags & 1) == 0)
                  //scroll no ciclico en x
                  if ([ts_struct].camera_x < 0) [ts_struct].camera_x = 0; end
                  if ([ts_struct].camera_x > ([ts_struct].ancho_mapa - [ts_struct].ancho_reg))
                     [ts_struct].camera_x = [ts_struct].ancho_mapa - [ts_struct].ancho_reg;
                  end
               end
               if (([ts_struct].tscroll_flags & 2) == 0)
                  //scroll no ciclico en y
                  if ([ts_struct].camera_y < 0) [ts_struct].camera_y = 0; end
                  if ([ts_struct].camera_y > ([ts_struct].alto_mapa - [ts_struct].alto_reg))
                     [ts_struct].camera_y = [ts_struct].alto_mapa - [ts_struct].alto_reg;
                  end
               end
            else
                [ts_struct].id_target = 0;
            end
         end
         //Tenemos las coordenadas (por un proceso o porque las ha puesto el usuario)
         //Vamos a calcular el tile en el que está la cámara (posición absoluta)
         if ([ts_struct].camera_x < 0)
            [ts_struct].camera_tx = ([ts_struct].camera_x + 1) / [ts_struct].tmapa[0].ancho_tile;
            [ts_struct].camera_tx--;
         else
             [ts_struct].camera_tx = [ts_struct].camera_x / [ts_struct].tmapa[0].ancho_tile;
         end
         if ([ts_struct].camera_y < 0)
            [ts_struct].camera_ty = ([ts_struct].camera_y + 1) / [ts_struct].tmapa[0].alto_tile;
            [ts_struct].camera_ty--;
         else
             [ts_struct].camera_ty = [ts_struct].camera_y / [ts_struct].tmapa[0].alto_tile;
         end
         //Y ahora las posiciones relativas a la esquina del mapa (como si sólo hubiera
         //un mapa no cíclico)
         [ts_struct].camera_x1 = ([ts_struct].camera_x % [ts_struct].ancho_mapa);
         if ([ts_struct].camera_x1 < 0)
            [ts_struct].camera_x1 += [ts_struct].ancho_mapa;
         end
         [ts_struct].camera_y1 = ([ts_struct].camera_y % [ts_struct].alto_mapa);
         if ([ts_struct].camera_y1 < 0)
            [ts_struct].camera_y1 += [ts_struct].alto_mapa;
         end
         //Los tiles los calcularemos con esta posición relativa, que ya es positiva
         [ts_struct].camera_tx1 = [ts_struct].camera_x1 / [ts_struct].tmapa[0].ancho_tile;
         [ts_struct].camera_ty1 = [ts_struct].camera_y1 / [ts_struct].tmapa[0].alto_tile;
         //Por si hace falta, calcularemos la posición dentro de un tile de la cámara
         [ts_struct].camera_x_tile = [ts_struct].camera_x1 % [ts_struct].tmapa[0].ancho_tile;
         [ts_struct].camera_y_tile = [ts_struct].camera_y1 % [ts_struct].tmapa[0].alto_tile;
         
         //EMPIEZA EL CONTROL DE LOS TILES**********************************
         //Si cambiamos de tile hay que refrescar toda la lista, porque hay tiles que
         //desaparecen y otros que aparecen.
         if (([ts_struct].camera_tx != camera_tx_ant) ||
             ([ts_struct].camera_ty != camera_ty_ant))

            //Primero buscamos a qué posición del mapa mira el tile superior izquierdo, ya que
            //recordemos que al meterle tiles extra estaremos leyendo unos tiles de más, y este tile
            //no coincidirá con la posición de la cámara
            [ts_struct].visible_tx = [ts_struct].camera_tx - ([ts_struct].tiles_extra_x / 2);
            [ts_struct].visible_ty = [ts_struct].camera_ty - ([ts_struct].tiles_extra_y / 2);
            [ts_struct].visible_tx1 = [ts_struct].camera_tx1 - ([ts_struct].tiles_extra_x / 2);
            if ([ts_struct].visible_tx1 < 0)
               [ts_struct].visible_tx1 += [ts_struct].tmapa[0].columnas;
            end
            [ts_struct].visible_ty1 = [ts_struct].camera_ty1 - ([ts_struct].tiles_extra_y / 2);
            if ([ts_struct].visible_ty1 < 0)
               [ts_struct].visible_ty1 += [ts_struct].tmapa[0].filas;
            end
            
            //y ahora si, actualicemos el mapa
            ts_actualiza_tiles(ts_struct);
			camera_tx_ant = [ts_struct].camera_tx;
            camera_ty_ant = [ts_struct].camera_ty;

            camera_x_tile_ant = [ts_struct].camera_x;
            camera_y_tile_ant = [ts_struct].camera_y;
         else
             //si hemos desplazado un poco los tiles, sin cambiar de tile de referencia
             //hacemos un desplazamiento sencillo
             if (([ts_struct].camera_x_tile != camera_x_tile_ant) ||
                 ([ts_struct].camera_y_tile != camera_y_tile_ant))
                 

                ts_desplaza_tiles(ts_struct,
                                  camera_x_tile_ant - [ts_struct].camera_x,
                                  camera_y_tile_ant - [ts_struct].camera_y);
                camera_x_tile_ant = [ts_struct].camera_x;
                camera_y_tile_ant = [ts_struct].camera_y;
             end
         end
         //say("completada iteracion");
         frame;
     end
end

//**************************************************************************************
//  FUNCION:    start_tscroll
//              Crea un scroll tileado que se mostrará usando un proceso por cada tile
//              visible en pantalla
//  PARÁMETROS: ts_struct: estructura que almacena los datos sobre el tscroll, debes crear
//                         la variable desde fuera y dejarla vacía, pues este proceso ya
//                         se encarga de rellenarlos. Se hace de esta forma porque no se
//                         puede devolver una estructura y así puedes leer los datos
//                         desde otros procesos.
//              ts_mapa: estructura que almacena los datos del mapa al cargarlo
//              ts_region: region en la que se mostrará el tscroll
//              ts_ini_regionx: posicion x de la esquina superior izquierda de la region
//              ts_ini_regiony: posicion y de la esquina superior izquierda de la region
//              ts_ancho_region: ancho de la region
//              ts_alto_region: alto de la region
//              tiles_extra_x: tiles que no se verán a los lados, pero que estan por si
//                             cargan información, por ejemplo, generan enemigos...
//                             un valor de 4 hace que haya 2 tiles a cada lado que no se
//                             ven
//              tiles_extra_y: idem por arriba y por abajo
//              ts_ancho_tile: especifica el ancho de un tile en pixels, necesario cuando
//                             se carga un tmf. Usando tpr este valor da igual.
//              ts_alto_tile: igual que el anterior, pero con la altura de un tile.
//              ts_flags: flags de las propiedades del scroll
//                        1= scroll cíclico horizontalmente
//                        2= scroll cíclico verticalmente
//**************************************************************************************
process start_tscroll (tscroll pointer ts_struct, t_mapa pointer ts_mapa,
                       int ts_region,
                       int ts_ini_regionx, int ts_ini_regiony,
                       int ts_ancho_region, int ts_alto_region,
                       int tiles_extra_x, int tiles_extra_y,
                       int ts_ancho_tile, int ts_alto_tile,
                       int ts_flags)
begin
     //empezamos cargando los datos por parámetros
     [ts_struct].ts_region = ts_region;
     [ts_struct].ini_reg_x = ts_ini_regionx;
     [ts_struct].ini_reg_y = ts_ini_regiony;
     [ts_struct].ancho_reg = ts_ancho_region;
     [ts_struct].alto_reg = ts_alto_region;
     [ts_struct].tscroll_flags = ts_flags;
     //seguimos cargando datos del mapa cargado
     [ts_struct].tmapa = ts_mapa;

     //calculos para ahorrar trabajo despues
     //[ts_struct].n_tiles_mapa = [ts_struct].tmapa[0].columnas * [ts_struct].tmapa[0].filas *
     //                           [ts_struct].tmapa[0].capas;
     [ts_struct].n_tiles_capa = [ts_struct].tmapa[0].columnas * [ts_struct].tmapa[0].filas;

     //cargamos los datos adicionales por el propio tipo de fichero
     switch ([ts_mapa].tipo_mapa)
     case 2:
          [ts_struct].ts_file = fpg_load([ts_mapa].fpg);
     end
     default:
             if (ts_ancho_tile > 0)
				 [ts_struct].tmapa[0].ancho_tile = ts_ancho_tile;
             else
				 say("Error: el tamaño de tile no es válido");
				 exit();
			 end
             if (ts_alto_tile > 0)
				 [ts_struct].tmapa[0].alto_tile = ts_alto_tile;
             else
				 say("Error: el tamaño de tile no es válido");
				 exit();
			 end
             if ([ts_struct].ts_file < 0)
                say("Error: no se ha podido cargar el FPG.");
                exit();
             end
     end
     end
     //calculamos el tamaño total del mapa, para ahorrar cálculos
     [ts_struct].ancho_mapa = [ts_struct].tmapa[0].columnas * [ts_struct].tmapa[0].ancho_tile;
     [ts_struct].alto_mapa = [ts_struct].tmapa[0].filas * [ts_struct].tmapa[0].alto_tile;

     //calculamos los tiles que nos van a llevar el tscroll
     [ts_struct].n_columnas = ts_ancho_region / [ts_struct].tmapa[0].ancho_tile;
     if (ts_ancho_region % [ts_struct].tmapa[0].ancho_tile > 0)
        [ts_struct].n_columnas++;
     end
     [ts_struct].n_filas = ts_alto_region / [ts_struct].tmapa[0].alto_tile;
     if (ts_alto_region % [ts_struct].tmapa[0].alto_tile > 0)
        [ts_struct].n_filas++;
     end
     [ts_struct].tiles_extra_x = tiles_extra_x;
     [ts_struct].tiles_extra_y = tiles_extra_y;
     [ts_struct].n_columnas += tiles_extra_x;
     [ts_struct].n_filas += tiles_extra_y;
     [ts_struct].n_capas = [ts_mapa].capas;           //esto hay que definirlo

     //calculamos la posición neutral del tile superior izquierdo, como referencia
     [ts_struct].tileador_posx = [ts_struct].ini_reg_x
                                 + [ts_struct].tmapa[0].ancho_tile / 2
                                 - ((tiles_extra_x / 2) * [ts_struct].tmapa[0].ancho_tile);
     [ts_struct].tileador_posy=[ts_struct].ini_reg_y
                               + [ts_struct].tmapa[0].alto_tile / 2
                               - ((tiles_extra_y / 2) * [ts_struct].tmapa[0].alto_tile);
     //la fórmula es: esquina de la region, mas medio tile (porque el 0,0 está en el
     //centro del tile) menos la mitad de los tiles extra que añadimos.
     
     //[ts_struct].id_tscroll = crear_mapa([ts_struct].n_columnas, [ts_struct].n_filas,
     //                                    [ts_struct].n_capas, ts_struct);
     
     //DEBUG
     //[ts_struct].id_tscroll = tile();
     //[ts_struct].id_tscroll.graph = 1;


     //creamos el proceso de control del tscroll
     [ts_struct].id_control = tscroll_control(ts_struct);
     //say("todo ok");
end

//***************************************************************************************
//  FUNCIÓN:    stop_tscroll
//              Detiene el scroll tileado, eliminando todos los procesos tile, descargando
//              el fpg si se cargó desde un tpr y poniendo todo a cero. Pero esta función
//              no descarga el mapa de tiles porque podría estar siendo usado por otro
//              scroll.
//  PARÁMETROS: ts_struct: estructura que almacena los datos sobre el tscroll.
//***************************************************************************************

process stop_tscroll (tscroll pointer ts_struct)
begin
     //eliminamos el proceso de control
     signal([ts_struct].id_control, s_kill);
     [ts_struct].id_control = 0;
     //************************************************
     //Estas lineas no son necesarias, si se quiere agilizar el proceso se pueden
     //eliminar, pero así se deja listo por si se va a usar la estructura con otro
     //scroll tileado
     [ts_struct].ts_region = 0;
     [ts_struct].ini_reg_x = 0;
     [ts_struct].ini_reg_y = 0;
     [ts_struct].ancho_reg = 0;
     [ts_struct].alto_reg = 0;
     
     [ts_struct].camera_x = 0;
     [ts_struct].camera_y = 0;
     [ts_struct].camera_x1 = 0;
     [ts_struct].camera_y1 = 0;
     [ts_struct].camera_tx = 0;
     [ts_struct].camera_ty = 0;
     [ts_struct].camera_tx1 = 0;
     [ts_struct].camera_ty1 = 0;
     [ts_struct].camera_x_tile = 0;
     [ts_struct].camera_y_tile = 0;
     [ts_struct].id_target = 0;
     [ts_struct].cam_desp_x = 0;
     [ts_struct].cam_desp_y = 0;
     [ts_struct].tscroll_flags = 0;
     
     [ts_struct].n_columnas = 0;
     [ts_struct].n_filas = 0;
     [ts_struct].n_capas = 0;
     [ts_struct].tiles_extra_x = 0;
     [ts_struct].tiles_extra_y = 0;
     
     [ts_struct].ancho_mapa = 0;
     [ts_struct].alto_mapa = 0;
     [ts_struct].n_tiles_capa = 0;
     [ts_struct].tileador_posx = 0;
     [ts_struct].tileador_posy = 0;
     
     //si hemos cargado un tpr, descargamos el fpg que cargamos con él
     if ([ts_struct].tmapa[0].tipo_mapa == 2) fpg_unload([ts_struct].ts_file); end
     [ts_struct].ts_file = 0;
     //eliminamos la lista de tiles
     borrar_tiles_sobrantes([ts_struct].id_tscroll);
     if ([ts_struct].id_tscroll != 0)
     	signal([ts_struct].id_tscroll, s_kill);
     	[ts_struct].id_tscroll = 0;
     end
end







//****************************************************************************************************
//  OTRAS FUNCIONES
//****************************************************************************************************

process tscroll_get_screen_position (tscroll pointer ts_struct, int x2, int y2, double pointer gsp_posx, double pointer gsp_posy)
//***************************************************************************
//  FUNCION:      tscroll_get_screen_position
//                se le pasan coordenadas del scroll y esta devuelve coordenadas
//                de pantalla.
//  PARAMETROS:   ts_struct: estructura con los datos del scroll donde queremos situarnos
//                x2: posición x dentro del scroll del proceso
//                y2: posicion y dentro del scroll del proceso
//                gps_posx: dirección donde queremos que se almacene la posición x en
//                          pantalla.
//                gps_posy: dirección donde queremos que se almacene la posición y en
//                          pantalla.
//***************************************************************************
begin
     [gsp_posx] = [ts_struct].ini_reg_x + (x2 - [ts_struct].camera_x);
     [gsp_posy] = [ts_struct].ini_reg_y + (y2 - [ts_struct].camera_y);
end
