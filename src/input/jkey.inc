//******************************************************************************
//  PROCESO DE CONTROL DE TECLAS
//******************************************************************************

process ctrl_teclas ()
private
    int cont;
    int pressed[k_last-1];
begin
    priority = 100;
    loop
        for (cont = 0;cont < k_last; cont++)
            pressed[cont] = 0;
            if (key(teclas[cont][0]))
                pressed[cont] = 1;
            end
        end

        int joy = joy_query( JOY_QUERY_FIRST_ATTACHED );
        if ( joy != -1 )
            if ( joy_query( joy, JOY_BUTTON_DPAD_UP        ) || joy_query( joy, JOY_AXIS_LEFTY ) < -16384   ) pressed[ K_UP        ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_DPAD_LEFT      ) || joy_query( joy, JOY_AXIS_LEFTX ) < -16384   ) pressed[ K_LEFT      ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_DPAD_DOWN      ) || joy_query( joy, JOY_AXIS_LEFTY ) > 16383    ) pressed[ K_DOWN      ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_DPAD_RIGHT     ) || joy_query( joy, JOY_AXIS_LEFTX ) > 16383    ) pressed[ K_RIGHT     ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_BACK           )                                                ) pressed[ K_ESC       ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_START          )                                                ) pressed[ K_ENTER     ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_LEFTSHOULDER   )                                                ) pressed[ K_VOL_DOWN  ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_RIGHTSHOULDER  )                                                ) pressed[ K_VOL_UP    ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_A              )                                                ) pressed[ K_JUMP      ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_B              )                                                ) pressed[ K_FIRE      ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_X              )                                                ) pressed[ K_NEXT      ] = 1; end
            if ( joy_query( joy, JOY_BUTTON_Y              )                                                ) pressed[ K_PREVIOUS  ] = 1; end
        end

        for (cont=0;cont < k_last; cont++)
            if ( pressed[cont] )
                teclas[cont][2]++;
            else
                teclas[cont][2] = 0;
            end
        end

        frame;
    end
end

//  CONFIGURACION DE TECLAS
//******************************************************************************
process inicia_teclas (k_sist)
begin
    teclas[k_up][0] = config_data.teclas[k_up][0];
    teclas[k_down][0] = config_data.teclas[k_down][0];
    teclas[k_left][0] = config_data.teclas[k_left][0];
    teclas[k_right][0] = config_data.teclas[k_right][0];
    teclas[k_jump][0] = config_data.teclas[k_jump][0];            //salto
    teclas[k_fire][0] = config_data.teclas[k_fire][0];            //disparo
    teclas[k_previous][0] = config_data.teclas[k_previous][0];    //arma anterior
    teclas[k_next][0] = config_data.teclas[k_next][0];            //arma_siguiente
    teclas[k_enter][0] = config_data.teclas[k_enter][0];          //pausa
    teclas[k_esc][0] = config_data.teclas[k_esc][0];              //salir
    teclas[k_vol_up][0] = config_data.teclas[k_vol_up][0];        //subir volumen
    teclas[k_vol_down][0] = config_data.teclas[k_vol_down][0];    //bajar volumen
    teclas_hat_seleccionado = config_data.usar_joy_hat;
    
    teclas[k_up][1] = config_data.teclas[k_up][1];
    teclas[k_down][1] = config_data.teclas[k_down][1];
    teclas[k_left][1] = config_data.teclas[k_left][1];
    teclas[k_right][1] = config_data.teclas[k_right][1];
    teclas[k_jump][1] = config_data.teclas[k_jump][1];            //salto
    teclas[k_fire][1] = config_data.teclas[k_fire][1];            //disparo
    teclas[k_previous][1] = config_data.teclas[k_previous][1];    //arma anterior
    teclas[k_next][1] = config_data.teclas[k_next][1];            //arma_siguiente
    teclas[k_enter][1] = config_data.teclas[k_enter][1];          //pausa
    teclas[k_esc][1] = config_data.teclas[k_esc][1];              //salir
    teclas[k_vol_up][1] = config_data.teclas[k_vol_up][1];        //subir volumen
    teclas[k_vol_down][1] = config_data.teclas[k_vol_down][1];    //bajar volumen
end

process key_to_string (cont)
begin
     switch (cont)
     case _esc: nombre_tecla = "ESC"; end
     case _f1: nombre_tecla = "F1"; end
     case _f2: nombre_tecla = "F2"; end
     case _f3: nombre_tecla = "F3"; end
     case _f4: nombre_tecla = "F4"; end
     case _f5: nombre_tecla = "F5"; end
     case _f6: nombre_tecla = "F6"; end
     case _f7: nombre_tecla = "F7"; end
     case _f8: nombre_tecla = "F8"; end
     case _f9: nombre_tecla = "F9"; end
     case _f10: nombre_tecla = "F10"; end
     case _f11: nombre_tecla = "F11"; end
     case _f12: nombre_tecla = "F12"; end
     
     case _wave: nombre_tecla = "º"; end
     case _1: nombre_tecla = "1"; end
     case _2: nombre_tecla = "2"; end
     case _3: nombre_tecla = "3"; end
     case _4: nombre_tecla = "4"; end
     case _5: nombre_tecla = "5"; end
     case _6: nombre_tecla = "6"; end
     case _7: nombre_tecla = "7"; end
     case _8: nombre_tecla = "8"; end
     case _9: nombre_tecla ="9"; end
     case _0: nombre_tecla = "0"; end
     case _minus: nombre_tecla = "?"; end
     case _plus: nombre_tecla = "¿"; end
     
     case _backspace: nombre_tecla = "<-"; end
     case _tab: nombre_tecla = "TAB"; end
     case _q: nombre_tecla = "Q"; end
     case _w: nombre_tecla = "W"; end
     case _e: nombre_tecla = "E"; end
     case _r: nombre_tecla = "R"; end
     case _t: nombre_tecla = "T"; end
     case _y: nombre_tecla = "Y"; end
     case _u: nombre_tecla = "U"; end
     case _i: nombre_tecla = "I"; end
     case _o: nombre_tecla = "O"; end
     case _p: nombre_tecla = "P"; end
     case _l_bracket: nombre_tecla = "["; end
     case _r_bracket: nombre_tecla = "]"; end
     case _enter: nombre_tecla = "ENTER"; end
     
     case _caps_lock: nombre_tecla = "CAPS LOCK"; end
     case _a: nombre_tecla = "A"; end
     case _s: nombre_tecla = "S"; end
     case _d: nombre_tecla = "D"; end
     case _f: nombre_tecla = "F"; end
     case _g: nombre_tecla = "G"; end
     case _h: nombre_tecla = "H"; end
     case _j: nombre_tecla = "J"; end
     case _k: nombre_tecla = "K"; end
     case _l: nombre_tecla = "L"; end
     case _semicolon: nombre_tecla = "Ñ"; end
     case _apostrophe: nombre_tecla = "¨"; end
     case _backslash: nombre_tecla = "<"; end
     
     case _l_shift: nombre_tecla = "L SHIFT"; end
     case _z: nombre_tecla = "Z"; end
     case _x: nombre_tecla = "X"; end
     case _c: nombre_tecla = "C"; end
     case _v: nombre_tecla = "V"; end
     case _b: nombre_tecla = "B"; end
     case _n: nombre_tecla = "N"; end
     case _m: nombre_tecla = "M"; end
     case _comma: nombre_tecla = ","; end
     case _point: nombre_tecla = "."; end
     case _slash: nombre_tecla = "-"; end
     case _r_shift: nombre_tecla = "R SHIFT"; end
     
     case _control: nombre_tecla = "CONTROL"; end
     case _alt: nombre_tecla = "ALT"; end
     case _space: nombre_tecla = "SPACE"; end
     
     case _ins: nombre_tecla = "INSERT"; end
     case _home: nombre_tecla = "HOME"; end
     case _pgup: nombre_tecla = "PG. UP"; end
     case _del: nombre_tecla = "DEL"; end
     case _end: nombre_tecla = "END"; end
     case _pgdn: nombre_tecla = "PG. DOWN"; end
     
     case _up: nombre_tecla = "UP"; end
     case _down: nombre_tecla = "DOWN"; end
     case _left: nombre_tecla = "LEFT"; end
     case _right: nombre_tecla = "RIGHT"; end
     
     case _c_backslash: nombre_tecla = "NUM /"; end
     case _c_asterisk: nombre_tecla = "NUM *"; end
     case _c_minus: nombre_tecla = "NUM -"; end
     case _c_home: nombre_tecla = "NUM 7"; end
     case _c_up: nombre_tecla = "NUM 8"; end
     case _c_pgup: nombre_tecla = "NUM 9"; end
     case _c_left: nombre_tecla = "NUM 4"; end
     case _c_center: nombre_tecla = "NUM 5"; end
     case _c_right: nombre_tecla = "NUM 6"; end
     case _c_end: nombre_tecla = "NUM 1"; end
     case _c_down: nombre_tecla = "NUM 2"; end
     case _c_pgdn: nombre_tecla = "NUM 3"; end
     case _c_ins: nombre_tecla = "NUM 0"; end
     case _c_del: nombre_tecla = "NUM ."; end
     case _c_plus: nombre_tecla = "NUM +"; end
     case _c_enter: nombre_tecla = "NUM ENTER"; end
     
     default: cont = -1; end
     end
     
     return (cont);
end