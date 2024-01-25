//***********************************************************************************************
//	FUNCIONES
//***********************************************************************************************
function int lsm_next_weapon (int lsm_armas, int lsm_pos)
//Indica la próxima arma disponible. La primera arma es la posición 1, Blue Star.
//Devuelve la nueva posición, o -1 si no la ha encontrado
private
	int lsm_mask;
begin
	lsm_pos++;
	while (lsm_pos <= 32)
		lsm_mask = pow(2, lsm_pos - 1);
		if ((lsm_armas & lsm_mask) == lsm_mask)
			break;
		else
			lsm_pos++;
		end
	end
	
	if (lsm_pos > 32) lsm_pos = -1; end
	
	return lsm_pos;
end

function int lsm_prev_weapon (int lsm_armas, int lsm_pos)
//Indica la anterior arma disponible. La primera arma es la posición 1, Blue Star.
//Devuelve la nueva posición, o -1 si no la ha encontrado.
private
	int lsm_mask;
begin
	lsm_pos--;
	while (lsm_pos > 0)
		lsm_mask = pow(2, lsm_pos - 1);
		if ((lsm_armas & lsm_mask) == lsm_mask)
			break;
		else
			lsm_pos--;
		end
	end
	
	if (lsm_pos == 0) lsm_pos = -1; end
	
	return lsm_pos;
end

function int lsm_next_episode (int lsm_episodes, int lsm_pos)
//Indica el siguiente episodio disponible. El primero es la posición 1, Castle Horror.
//Devuelve la nueva posición, o -1 si no la ha encontrado
private
	int lsm_mask;
begin
	lsm_pos++;
	while (lsm_pos <= 32)
		lsm_mask = pow(2, lsm_pos - 1);
		if ((lsm_episodes & lsm_mask) == lsm_mask)
			break;
		else
			lsm_pos++;
		end
	end
	
	if (lsm_pos > 32) lsm_pos = -1; end
	
	return lsm_pos;
end

function int lsm_prev_episode (int lsm_episodes, int lsm_pos)
//Indica el episodio anterior disponible. El primero es la posición 1, Castle Horror.
//Devuelve la nueva posición, o -1 si no la ha encontrado.
private
	int lsm_mask;
begin
	lsm_pos--;
	while (lsm_pos > 0)
		lsm_mask = pow(2, lsm_pos - 1);
		if ((lsm_episodes & lsm_mask) == lsm_mask)
			break;
		else
			lsm_pos--;
		end
	end
	
	if (lsm_pos == 0) lsm_pos = -1; end
	
	return lsm_pos;
end

function int lsm_next_chapter (int lsm_chapter, int lsm_pos)
//Indica el próximo capítulo disponible. El primero es la posición 1.
//Devuelve la nueva posición, o -1 si no la ha encontrado
private
	int lsm_mask;
begin
	lsm_pos++;
	while (lsm_pos <= 32)
		lsm_mask = pow(2, lsm_pos - 1);
		if ((lsm_chapter & lsm_mask) == lsm_mask)
			break;
		else
			lsm_pos++;
		end
	end
	
	if (lsm_pos > 32) lsm_pos = -1; end
	
	return lsm_pos;
end

function int lsm_prev_chapter (int lsm_chapter, int lsm_pos)
//Indica el anterior capítulo disponible. El primero es la posición 1.
//Devuelve la nueva posición, o -1 si no la ha encontrado.
private
	int lsm_mask;
begin
	lsm_pos--;
	while (lsm_pos > 0)
		lsm_mask = pow(2, lsm_pos - 1);
		if ((lsm_chapter & lsm_mask) == lsm_mask)
			break;
		else
			lsm_pos--;
		end
	end
	
	if (lsm_pos == 0) lsm_pos = -1; end
	
	return lsm_pos;
end