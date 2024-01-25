function int search_animation (int pointer anim_array, int anim_pos)
//Busca una animación en un array de datos. Cada animación consta de una primera posición, que indica de
//cuantos frames consta, y luego ese mismo número de posiciones, conteniendo el valor del gráfico en ese
//frame.
private
    int cont;
    int dato_a_devolver;
begin
    dato_a_devolver = 0;
    for (cont = 0; cont < anim_pos; cont++)
        dato_a_devolver += anim_array[dato_a_devolver] + 1;
    end
    return (dato_a_devolver);
end