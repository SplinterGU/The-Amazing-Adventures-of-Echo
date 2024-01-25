//***********************************************************************************************
//	CURSORES
//***********************************************************************************************
process lsm_cursor1 (file, graph, x, y, z)
private
	int angle2;
begin
	loop
		angle2 += 3000;
		size_y = 100 * abs(cos(angle2));
		frame;
	end
end

process lsm_cursor2 (file, graph, x, y, z)
private
	int angle2;
begin
	loop
		angle2 += 3000;
		size_x = 100 * abs(cos(angle2));
		frame;
	end
end

process lsm_cursor3 (file, graph, x, y2, z)
private
	int angle2;
begin
	loop
		angle2 += 3000;
		y = y2 + (4 * cos(angle2));
		frame;
	end
end