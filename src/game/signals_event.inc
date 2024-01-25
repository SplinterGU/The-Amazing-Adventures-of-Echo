//*******************************************************
//  SEÑALES EVENTO 1 3 1
//*******************************************************
function signal_event_1_3_1 (int se_signal)
private
    int temp;
begin
    temp = get_id(type croquis);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type croquis);
    end
    temp = get_id(type ghyppo_head);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type ghyppo_head);
    end
    temp = get_id(type ghyppo_tail);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type ghyppo_tail);
    end
    temp = get_id(type ghyppo_bomb);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type ghyppo_bomb);
    end
    temp = get_id(type ghyppo);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type ghyppo);
    end
	temp = get_id(type intro_boss_01_3_01);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type intro_boss_01_3_01);
    end
    temp = get_id(type event_1_3_1);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type event_1_3_1);
    end
end
//*******************************************************
//  SEÑALES EVENTO 1 3 2
//*******************************************************
function signal_event_1_3_2 (int se_signal)
private
    int temp;
begin
    if ((se_signal == s_kill) || (se_signal == s_kill_tree))
        temp = get_id(type dragon_part);
        while (temp)
            signal(temp, se_signal);
            temp = get_id(type dragon_part);
        end
    end
    
    temp = get_id(type dragon_fire);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type dragon_fire);
    end
    temp = get_id(type dragon_laser);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type dragon_laser);
    end
    temp = get_id(type dragon_homing);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type dragon_homing);
    end
    temp = get_id(type ladrillo_cae);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type ladrillo_cae);
    end
    temp = get_id(type dragon_body);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type dragon_body);
    end
    temp = get_id(type intro_boss_01_3_02);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type intro_boss_01_3_02);
    end
	temp = get_id(type event_1_3_2);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type event_1_3_2);
    end
end
//*******************************************************
//  SEÑALES EVENTO 1 3
//*******************************************************
function signal_event_1_4_1_accesories (int se_signal)
private
    int temp;
begin
    if ((se_signal == s_kill) || (se_signal == s_kill_tree))
        temp = get_id(type satavamp_fuego);
        while (temp)
            signal(temp, se_signal);
            temp = get_id(type satavamp_fuego);
        end
    end
    
    temp = get_id(type fuego_espiritual);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type fuego_espiritual);
    end
    temp = get_id(type fuego_espiritual2);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type fuego_espiritual2);
    end
    temp = get_id(type fuego_boleadoras);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type fuego_boleadoras);
    end
    temp = get_id(type lanza_fuego);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type lanza_fuego);
    end
    
end

function signal_event_1_4_1 (int se_signal)
private
    int temp;
begin
    signal_event_1_4_1_accesories (se_signal);
    
    if ((se_signal == s_kill) || (se_signal == s_kill_tree))
        temp = get_id(type satavamp_capa);
        while (temp)
            signal(temp, se_signal);
            temp = get_id(type satavamp_capa);
        end
    end
        
    temp = get_id(type satavamp);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type satavamp);
    end
	temp = get_id(type intro_boss_01_4);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type intro_boss_01_4);
    end
    temp = get_id(type event_1_4_1);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type event_1_4_1);
    end
end
//*******************************************************
//  SEÑALES EVENTO 3 1
//*******************************************************
function signal_event_3_1 (int se_signal)
private
    int temp;
begin
    temp = get_id(type nave_evento);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type nave_evento);
    end
    temp = get_id(type event_3_1);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type event_3_1);
    end
end
//*******************************************************
//  SEÑALES EVENTO 3 2
//*******************************************************

//*******************************************************
//  SEÑALES EVENTO 3 3
//*******************************************************

function signal_event_3_3 (int se_signal)
private
    int temp;
begin
    temp = get_id(type bblom_shot);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type bblom_shot);
    end
    temp = get_id(type blom);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type blom);
    end
    temp = get_id(type big_blom);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type big_blom);
    end
	temp = get_id(type intro_boss_03_02);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type intro_boss_03_02);
    end
    temp = get_id(type event_3_3);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type event_3_3);
    end
end

//*******************************************************
//  SEÑALES EVENTO 3 3
//*******************************************************

function signal_event_4_4 (int se_signal)
private
    int temp;
begin
    temp = get_id(type event_4_4);
    while (temp)
        signal(temp, se_signal);
        temp = get_id(type event_4_4);
    end
end
//*******************************************************
//  SEÑALES TODOS LOS EVENTOS
//*******************************************************
process signal_event_all (int se_signal)
begin
    signal_event_1_3_1(se_signal);
    signal_event_1_3_2(se_signal);
    signal_event_1_4_1(se_signal);
    signal_event_3_1(se_signal);
    signal_event_3_3(se_signal);
end
