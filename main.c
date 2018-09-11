#include "enot.h"
# include <stdio.h>

// Вставка пикселя на surface
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	if (x >= 0 && x < WINDOW_W)
	{
		Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
		*(Uint32 *)target_pixel = pixel;
	}
}

// Выход
void	exit_x(t_sdl *iw)
{
	free(iw->walls);
	free(iw->sectors);
	SDL_DestroyRenderer(iw->ren);
	SDL_DestroyWindow(iw->win);
	/*IMG_Quit();*/
	SDL_Quit();
	system("leaks doom-nukem");
	exit(0);
}

// Прототип функции обновления экрана
void	update(t_sdl *iw);

// Хук на нажатие
void	key_down(int code, t_sdl *iw)
{
	printf("keydown = %d\n", code);
	if (code == 41)
		exit_x(iw);
	else if (code == 79)
	{
		iw->p.rot = (iw->p.rot >= 359) ? 1 : iw->p.rot + 2;
		update(iw);
	}
	else if (code == 80)
	{
		iw->p.rot = (iw->p.rot <= 1) ? 359 : iw->p.rot - 2;
		update(iw);
	}
	else if (code == 20)
	{
		iw->p.z -= 20;
		update(iw);
	}
	else if (code == 8)
	{
		iw->p.z += 20;
		update(iw);
	}
	else if (code == 7)
	{
		iw->p.x += 10 * cos((double)(iw->p.rot) * (3.14159265 / 180.0));
		iw->p.y += 10 * sin((double)(iw->p.rot) * (3.14159265 / 180.0));
		update(iw);
	}
	else if (code == 4)
	{
		iw->p.x -= 10 * cos((double)(iw->p.rot) * (3.14159265 / 180.0));
		iw->p.y -= 10 * sin((double)(iw->p.rot) * (3.14159265 / 180.0));
		update(iw);
	}
	else if (code == 22)
	{
		iw->p.x -= 20 * cos((double)(iw->p.rot - 90) * (3.14159265 / 180.0));
		iw->p.y -= 20 * sin((double)(iw->p.rot - 90) * (3.14159265 / 180.0));
		update(iw);
	}
	else if (code == 26)
	{
		iw->p.x += 20 * cos((double)(iw->p.rot - 90) * (3.14159265 / 180.0));
		iw->p.y += 20 * sin((double)(iw->p.rot - 90) * (3.14159265 / 180.0));
		update(iw);
	}
	else if (code == 82)
	{
		iw->p.x += 20 * cos((double)(iw->p.rot - 90) * (3.14159265 / 180.0));
		iw->p.y += 20 * sin((double)(iw->p.rot - 90) * (3.14159265 / 180.0));
		update(iw);
	}
	else if (code == 81)
	{
		iw->p.x -= 20 * cos((double)(iw->p.rot - 90) * (3.14159265 / 180.0));
		iw->p.y -= 20 * sin((double)(iw->p.rot - 90) * (3.14159265 / 180.0));
		update(iw);
	}
	/*else if (code == 44)
	{
		projection(iw, 1);
	}*/
	printf("rot = %d\n x %d y %d z %d\n\n", iw->p.rot, iw->p.x, iw->p.y, iw->p.z);
}

// Хук на отжатие
void	key_up(int code, t_sdl *iw)
{
	//printf("keyup = %d\n", code);
}

// потом...
void	loop(t_sdl *iw)
{

}

// если мышь на экране сдвинулать сюда передаются значения на сколько она сдвинулась по осям
void	mouse_move(int dx, int dy, t_sdl *iw)
{
	if (dx > 0)
	{
		iw->p.rot = (iw->p.rot >= 359) ? 1 : iw->p.rot + 1;
		update(iw);
	}
	else if (dx < 0)
	{
		iw->p.rot = (iw->p.rot <= 1) ? 359 : iw->p.rot - 1;
		update(iw);
	}
	//printf("xrel = %d yrel = %d\n", dx, dy);
}

// Бесконечный цикл откуда вызываются хуки
void	main_loop(t_sdl *iw)
{
	SDL_Event e;

	iw->quit = 0;
	while (!iw->quit)
	{
		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
				iw->quit = 1;
			else if (e.type == SDL_KEYDOWN)//&& e.key.repeat == 0)
				key_down(e.key.keysym.scancode, iw);
			else if (e.type == SDL_KEYUP)
				key_up(e.key.keysym.scancode, iw);
			else if (e.type == SDL_MOUSEMOTION)
				mouse_move(e.motion.xrel, e.motion.yrel, iw);
		loop(iw);
	}
}

//void	get_map(t_sdl *iw)
//{
//	iw->walls = (t_wall *)malloc((4) * sizeof(t_wall));
//	iw->sectors = (t_sector *)malloc(1 * sizeof(t_sector));
//	iw->v.numSectors = 1;
//	iw->v.last_sector = 0;
//
//	iw->sectors[0].startWall = 0;
//	iw->sectors[0].numWalls = 4;
//
//	iw->walls[0].x = 0;
//	iw->walls[0].y = 0;
//	iw->walls[0].zd = 0;
//	iw->walls[0].zu = 1000;
//	iw->walls[0].nextsector = -1;
//	iw->walls[1].x = 4000;
//	iw->walls[1].y = 0;
//	iw->walls[1].zd = 0;
//	iw->walls[1].zu = 1000;
//	iw->walls[1].nextsector = -1;
//	iw->walls[2].x = 4000;
//	iw->walls[2].y = 4000;
//	iw->walls[2].zd = 0;
//	iw->walls[2].zu = 1000;
//	iw->walls[2].nextsector = -1;
//	iw->walls[3].x = 0;
//	iw->walls[3].y = 4000;
//	iw->walls[3].zd = 0;
//	iw->walls[3].zu = 1000;
//	iw->walls[3].nextsector = -1;
//}

// Создание карты!
void	get_map(t_sdl *iw)
{
	iw->walls = (t_wall *)malloc((6 + 8) * sizeof(t_wall));
	iw->sectors = (t_sector *)malloc(2 * sizeof(t_sector));
	iw->v.numSectors = 2;
	iw->v.last_sector = 0;

	iw->sectors[0].startWall = 0;
	iw->sectors[0].numWalls = 6;
	iw->sectors[1].startWall = 6;
	iw->sectors[1].numWalls = 8;

	iw->walls[0].x = 0;
	iw->walls[0].y = 1000;
	iw->walls[0].zd = -500;
	iw->walls[0].zu = 1500;
	iw->walls[0].nextsector = -1;
	iw->walls[1].x = 3000;
	iw->walls[1].y = 1000;
	iw->walls[1].zd = 0;
	iw->walls[1].zu = 1000;
	iw->walls[1].nextsector = -1;
	iw->walls[2].x = 3000;
	iw->walls[2].y = 2000;
	iw->walls[2].zd = 0;
	iw->walls[2].zu = 1000;
	iw->walls[2].nextsector = 1;
	iw->walls[3].x = 3000;
	iw->walls[3].y = 3000;
	iw->walls[3].zd = 0;
	iw->walls[3].zu = 1000;
	iw->walls[3].nextsector = -1;
	iw->walls[4].x = 3000;
	iw->walls[4].y = 4000;
	iw->walls[4].zd = 0;
	iw->walls[4].zu = 1000;
	iw->walls[4].nextsector = -1;
	iw->walls[5].x = 0;
	iw->walls[5].y = 4000;
	iw->walls[5].zd = -500;
	iw->walls[5].zu = 1000;
	iw->walls[5].nextsector = -1;

	iw->walls[6].x = 3000;
	iw->walls[6].y = 2000;
	iw->walls[6].zd = 200;
	iw->walls[6].zu = 800;
	iw->walls[6].nextsector = -1;
	iw->walls[7].x = 4000;
	iw->walls[7].y = 2000;
	iw->walls[7].zd = 200;
	iw->walls[7].zu = 800;
	iw->walls[7].nextsector = -1;
	iw->walls[8].x = 4000;
	iw->walls[8].y = 200;
	iw->walls[8].zd = 200;
	iw->walls[8].zu = 800;
	iw->walls[8].nextsector = -1;
	iw->walls[9].x = 6000;
	iw->walls[9].y = 200;
	iw->walls[9].zd = 200;
	iw->walls[9].zu = 800;
	iw->walls[9].nextsector = -1;
	iw->walls[10].x = 7000;
	iw->walls[10].y = 5000;
	iw->walls[10].zd = 200;
	iw->walls[10].zu = 800;
	iw->walls[10].nextsector = -1;
	iw->walls[11].x = 4000;
	iw->walls[11].y = 5000;
	iw->walls[11].zd = 200;
	iw->walls[11].zu = 800;
	iw->walls[11].nextsector = -1;
	iw->walls[12].x = 4000;
	iw->walls[12].y = 3000;
	iw->walls[12].zd = 200;
	iw->walls[12].zu = 800;
	iw->walls[12].nextsector = -1;
	iw->walls[13].x = 3000;
	iw->walls[13].y = 3000;
	iw->walls[13].zd = 200;
	iw->walls[13].zu = 800;
	iw->walls[13].nextsector = 0;
}

// Получения направления луча (xdir ydir) из поворота который варьируется от 0 до 360
void	get_dir(t_draw *d)
{
	if ((d->ang > 0 && d->ang < 180) || (d->ang > 360))
		d->xdir = 1;
	else
		d->xdir = -1;
	if ((d->ang > 90 && d->ang < 270) || (d->ang > 450))
		d->ydir = 1;
	else
		d->ydir = -1;
}

// получение коефициента наклона прямой из ang, который от 0 до 360
float	get_k(float ang)
{
	float	k;

	if (ang < 90)
		k = 90 + ang;
	else if (ang < 180)
		k = ang - 90;
	else if (ang < 270)
		k = ang - 90;
	else
		k = ang - 270;
	return (k);
}

// Получения всего что нужно, бросая луч из координаты по Х на экране(int i)
void	get_ray(t_draw *d, int ix2, t_sdl *iw)
{
	d->i = ix2 / 2;
	d->ang = (float)iw->p.rot - (float)iw->p.angle +
		((float)ix2 * (float)iw->p.angle / (float)WINDOW_W);
	if (d->ang == 0.0f)
		d->ang += 0.00001f;
	else if (d->ang == 90.0f)
		d->ang -= 0.00001f;
	get_dir(d);
	d->k = get_k(d->ang);
	d->k = tanf(d->k * 0.0174533);
	d->b = (float)iw->p.y - d->k * (float)iw->p.x;
}

// Получение значения, для стены, она вертикальна, или горизонтальна, или под углом
void	get_hv(int wall, int wall2, t_sdl *iw)
{
	if (iw->walls[wall].x == iw->walls[wall2].x)
		iw->walls[wall].hv = 1;
	else if (iw->walls[wall].y == iw->walls[wall2].y)
		iw->walls[wall].hv = -1;
	else
		iw->walls[wall].hv = 0;
}

// Получение для каждой стены HV, или уравнения прямой
void	get_walls_lines(t_sdl *iw)
{
	int sec;
	int wall;

	sec = -1;
	while (++sec < iw->v.numSectors)
	{
		wall = iw->sectors[sec].startWall - 1;
		while (++wall < iw->sectors[sec].startWall + iw->sectors[sec].numWalls - 1)
		{
			get_hv(wall, wall + 1, iw);
			if (iw->walls[wall].hv != 0)
				continue;
			iw->walls[wall].k = (float)(iw->walls[wall + 1].y - iw->walls[wall].y) /
				(float)(iw->walls[wall + 1].x - iw->walls[wall].x - 1);
			iw->walls[wall].b = (float)iw->walls[wall].y - iw->walls[wall].k * (float)iw->walls[wall].x;
		}
		get_hv(wall, iw->sectors[sec].startWall, iw);
		if (iw->walls[wall].hv != 0)
			continue;
		iw->walls[wall].k = (float)(iw->walls[iw->sectors[sec].startWall].y - iw->walls[wall].y) /
			(float)(iw->walls[iw->sectors[sec].startWall].x - iw->walls[wall].x - 1);
		iw->walls[wall].b = (float)iw->walls[wall].y - iw->walls[wall].k * (float)iw->walls[wall].x;
	}
}

// Определения внутри ли сектора "sector" игрок (по x,y) (возвращается 0, если нет)
int inside_sector(int sector, t_sdl *iw)
{
	long int i, x1, y1, x2, y2;
	unsigned long int wallCrossed;

	//Quick check if the sector ID is valid.

	wallCrossed = 0;
	i = iw->sectors[sector].startWall - 1;
	while (++i < iw->sectors[sector].startWall + iw->sectors[sector].numWalls - 1)
	{
		y1 = iw->walls[i].y - iw->p.y;
		y2 = iw->walls[i + 1].y - iw->p.y;
		if ((y1 ^ y2) < 0)
		{
			x1 = iw->walls[i].x - iw->p.x;
			x2 = iw->walls[i + 1].x - iw->p.x;
			if ((x1 ^ x2) >= 0)
				wallCrossed ^= x1;
			else
				wallCrossed ^= (x1 * y2 - x2 * y1) ^ y2;
		}
	}
	y1 = iw->walls[i].y - iw->p.y;
	y2 = iw->walls[iw->sectors[sector].startWall].y - iw->p.y;
	if ((y1 ^ y2) < 0)
	{
		x1 = iw->walls[i].x - iw->p.x;
		x2 = iw->walls[iw->sectors[sector].startWall].x - iw->p.x;
		if ((x1 ^ x2) >= 0)
			wallCrossed ^= x1;
		else
			wallCrossed ^= (x1 * y2 - x2 * y1) ^ y2;
	}
	return (wallCrossed >> 31);
}

// Тупое определение внутри ли сектора по Z игрок
int		inside_sectorZ(int sector, t_sdl *iw)
{
	int		maxz;
	int		minz;
	int		i;

	i = iw->sectors[sector].startWall;
	maxz = iw->walls[i].zu;
	minz = iw->walls[i].zd;
	while (++i < iw->sectors[sector].startWall + iw->sectors[sector].numWalls)
	{
		if (iw->walls[i].zu > maxz)
			maxz = iw->walls[i].zu;
		if (iw->walls[i].zd < minz)
			minz = iw->walls[i].zd;
	}
	if (iw->p.z <= maxz && iw->p.z >= minz)
		return (1);
	return (0);
}

// Функция возвращает сектор в котором находится игрок, или -1, если ни в каком
int		get_sector(t_sdl *iw)
{
	int sec;

	sec = iw->v.last_sector - 1;
	while (++sec < iw->v.numSectors)
		if (inside_sector(sec, iw) != 0 && inside_sectorZ(sec, iw) == 1)
			return (sec);
	sec = -1;
	while (++sec < iw->v.last_sector)
		if (inside_sector(sec, iw) != 0 && inside_sectorZ(sec, iw) == 1)
			return (sec);
	return (-1);
}

// -
int		getminWallX(int wall, t_draw *d, t_sdl *iw)
{
	if (wall < iw->sectors[d->curr_sector].startWall + iw->sectors[d->curr_sector].numWalls - 1)
	{
		if (iw->walls[wall].x < iw->walls[wall + 1].x)
			return (iw->walls[wall].x);
		else
			return (iw->walls[wall + 1].x);
	}
	else
		if (iw->walls[wall].x < iw->walls[iw->sectors[d->curr_sector].startWall].x)
			return (iw->walls[wall].x);
		else
			return (iw->walls[iw->sectors[d->curr_sector].startWall].x);
}

// -
int		getmaxWallX(int wall, t_draw *d, t_sdl *iw)
{
	if (wall < iw->sectors[d->curr_sector].startWall + iw->sectors[d->curr_sector].numWalls - 1)
	{
		if (iw->walls[wall].x <= iw->walls[wall + 1].x)
			return (iw->walls[wall + 1].x);
		else
			return (iw->walls[wall].x);
	}
	else
		if (iw->walls[wall].x <= iw->walls[iw->sectors[d->curr_sector].startWall].x)
			return (iw->walls[iw->sectors[d->curr_sector].startWall].x);
		else
			return (iw->walls[wall].x);
}

// -
int		getminWallY(int wall, t_draw *d, t_sdl *iw)
{
	if (wall < iw->sectors[d->curr_sector].startWall + iw->sectors[d->curr_sector].numWalls - 1)
	{
		if (iw->walls[wall].y < iw->walls[wall + 1].y)
			return (iw->walls[wall].y);
		else
			return (iw->walls[wall + 1].y);
	}
	else
		if (iw->walls[wall].y < iw->walls[iw->sectors[d->curr_sector].startWall].y)
			return (iw->walls[wall].y);
		else
			return (iw->walls[iw->sectors[d->curr_sector].startWall].y);
}

// -
int		getmaxWallY(int wall, t_draw *d, t_sdl *iw)
{
	if (wall < iw->sectors[d->curr_sector].startWall + iw->sectors[d->curr_sector].numWalls - 1)
	{
		if (iw->walls[wall].y <= iw->walls[wall + 1].y)
			return (iw->walls[wall + 1].y);
		else
			return (iw->walls[wall].y);
	}
	else
		if (iw->walls[wall].y <= iw->walls[iw->sectors[d->curr_sector].startWall].y)
			return (iw->walls[iw->sectors[d->curr_sector].startWall].y);
		else
			return (iw->walls[wall].y);
}

// Используется в get_wall
void	get_rx_ry(int wall, t_draw *d, t_sdl *iw)
{
	if (iw->walls[wall].hv == 0)
	{
		d->rx = (int)((d->b - iw->walls[wall].b) / (iw->walls[wall].k - d->k));
		d->ry = iw->walls[wall].k * d->rx + iw->walls[wall].b;
	}
	else if (iw->walls[wall].hv == -1)
	{
		d->ry = iw->walls[wall].y;
		d->rx = (int)(((float)d->ry - d->b) / d->k);
	}
	else if (iw->walls[wall].hv == 1)
	{
		d->rx = iw->walls[wall].x;
		d->ry = (int)((float)d->rx * d->k + d->b);
	}
}

// Установка начальных значений массивов top и bottom
void	set_top_bottom(t_draw *d)
{
	int		i;

	i = -1;
	while (++i < WINDOW_W)
	{
		d->topY[i] = 0;
		d->bottomY[i] = WINDOW_H;
	}
}

// Берем индекс следующей стены в секторе
int get_next_wall(t_sdl *iw, int wall, int sector)
{
	if (wall < iw->sectors[sector].startWall + iw->sectors[sector].numWalls - 1)
		return (wall + 1);
	else
		return (iw->sectors[sector].startWall);
}

// Получаем стену в которую врезается луч
int		get_wall(t_draw *d, t_sdl *iw, const char b)
{
	int		wall;
	t_draw	minlend;
	int		minwall;

	minwall = -1;
	wall = iw->sectors[d->curr_sector].startWall - 1;
	d->rx = -1;
	d->ry = -1;
	while (++wall < iw->sectors[d->curr_sector].startWall + iw->sectors[d->curr_sector].numWalls)
	{
		if (d->k == iw->walls[wall].k)
			continue;
		if (b == 0 && ((iw->p.x - iw->walls[wall].x) * (iw->walls[get_next_wall(iw, wall, d->curr_sector)].y - iw->walls[wall].y) -
			(iw->p.y - iw->walls[wall].y) * (iw->walls[get_next_wall(iw, wall, d->curr_sector)].x - iw->walls[wall].x) >= 0))
			continue;
		get_rx_ry(wall, d, iw);
		if ((((d->rx - iw->p.x) * d->xdir) >= 0) && (((d->ry - iw->p.y) * d->ydir) >= 0) &&
			(d->rx >= getminWallX(wall, d, iw) && d->rx <= getmaxWallX(wall, d, iw)) &&
			(d->ry >= getminWallY(wall, d, iw) && d->ry <= getmaxWallY(wall, d, iw)))
		{
			d->len = (int)sqrtf(powf(d->rx - iw->p.x, 2) + powf(d->ry - iw->p.y, 2));
			if (minwall == -1 || d->len < minlend.len)
			{
				minlend = *d;
				minwall = wall;
			}
			//minlend.len = (int)sqrtf(powf(d->rx - iw->p.x, 2) + powf(d->ry - iw->p.y, 2));
		}
	}
	if (minwall == -1)
	{
		//printf("k %f b %f sec %d ang %f\n\n", d->k, d->b, d->curr_sector, d->ang);
		return (-1);
	}
	*d = minlend;
	return (minwall);
}

// Получаем координату по Х следующей стены на ЭКРАНЕ после wall (xleft - координата начала стены wall)
void	find_x_next_wall(int wall, int xleft, t_draw *d, t_sdl *iw)
{
	int		xright;
	int		sv;
	int		i;
	int		si;

	sv = wall;
	xright = d->xright;
	while (xleft < xright - 1)
	{
		get_ray(d, xleft + xright, iw);
		if (wall == get_wall(d, iw, 0))
			xleft = d->i;
		else if (wall != -1)
			xright = d->i;
		else
			xleft++;
	}
	d->i = xright;
	si = d->i;
	i = 0;
	while (1)
	{
		get_ray(d, xleft + xleft + i, iw);
		d->curr_wall = get_wall(d, iw, 0);
		i++;
		if ((d->curr_wall != sv && d->curr_wall != -1) || xleft * 2 + i >= d->xright * 2)
			break ;
	}
	if (get_next_wall(iw, sv, d->curr_sector) != d->curr_wall)
	{
		get_ray(d, xleft + xright - 2, iw);
		d->curr_wall = get_wall(d, iw, 0);
	}
	d->i = si;
}

// Записываем в массив lines значение yu, yd и х
void	put_wall_line(t_brez *b, int x, int y)
{
	if (b->prev_x != x)
	{
		b->lines[b->indx].x = x;
		b->prev_x = x;
		if (b->dest == 1)
			b->lines[b->indx].yu = y;
		else
			b->lines[b->indx].yd = y;
		(b->indx)++;
	}
}

// Брезенхем
void	def_brez(t_wall_line *lines, t_draw_line line, char dest, t_brez *b)
{
	b->lines = lines;
	b->dest = dest;
	b->indx = 0;
	b->prev_x = -1;
	put_wall_line(b, line.x0, line.y0);
}

// Брезенхем
void	print_brez(t_brez *b, int d, int d1, int d2)
{
	int i;

	if (b->k <= 0)
		b->dx = b->dy;
	i = 0;
	while (++i <= b->dx)
	{
		if (d > 0)
		{
			d += d2;
			b->y += b->sy;
		}
		else
			d += d1;
		if (b->k > 0)
			put_wall_line(b, b->x, b->y);
		else
			put_wall_line(b, b->y, b->x);
		b->x += b->sx;
	}
}

// Брезенхем. 
void	brez_wall_line(t_wall_line *lines, t_draw_line line, char dest)
{
	t_brez	b;

	def_brez(lines, line, dest, &b);
	b.sx = (line.x1 >= line.x0) ? (1) : (-1);
	b.sy = (line.y1 >= line.y0) ? (1) : (-1);
	b.dx = (line.x1 > line.x0) ? (line.x1 - line.x0) : (line.x0 - line.x1);
	b.dy = (line.y1 > line.y0) ? (line.y1 - line.y0) : (line.y0 - line.y1);
	if (abs(line.y1 - line.y0) < abs(line.x1 - line.x0))
	{
		b.x = line.x0 + b.sx;
		b.y = line.y0;
		b.k = 1;
		print_brez(&b, (b.dy * 2) - b.dx, b.dy * 2, (b.dy - b.dx) * 2);
	}
	else
	{
		b.x = line.y0 + b.sy;
		b.y = line.x0;
		b.sy = (line.x1 >= line.x0) ? (1) : (-1);
		b.sx = (line.y1 >= line.y0) ? (1) : (-1);
		b.k = 0;
		print_brez(&b, (b.dx * 2) - b.dy, b.dx * 2, (b.dx - b.dy) * 2);
	}
}

// Рисуем стену из массива lines
void	draw_wall(t_wall_line *lines, t_sdl *iw, t_draw *d, int len)
{
	int		i;
	int		j;

	i = -1;
	//printf("draw_wall_start\n");
	while (++i < len)
	{
		if (d->topY[lines[i].x] >= d->bottomY[lines[i].x])
			continue;
		//printf("d1\n");
		j = d->topY[lines[i].x];
		//printf("draw %d\n", lines[i].x);
		while (++j < d->bottomY[lines[i].x])
			set_pixel(iw->sur, lines[i].x, j, 0x00FF00);
		///printf("d2\n");
		d->topY[lines[i].x] = d->bottomY[lines[i].x];
		//printf("d3\n");
	}
}

// Рисуем пол из массива lines
void	draw_floor(t_wall_line *lines, t_sdl *iw, t_draw *d, int len)
{
	int		i;
	int		j;

	i = -1;
	while (++i < len)
	{
		if (d->topY[lines[i].x] >= d->bottomY[lines[i].x])
			continue;
		if (lines[i].yd < d->bottomY[lines[i].x])
		{
			j = lines[i].yd - 1;
			while (++j < d->bottomY[lines[i].x])
				if (j >= d->topY[lines[i].x])
					set_pixel(iw->sur, lines[i].x, j, 0xFFFF00);
			d->bottomY[lines[i].x] = lines[i].yd;
		}
	}
}

// Рисуем потолок из массива lines
void	draw_ceil(t_wall_line *lines, t_sdl *iw, t_draw *d, int len)
{
	int		i;
	int		j;

	i = -1;
	while (++i < len)
	{
		if (d->topY[lines[i].x] >= d->bottomY[lines[i].x])
			continue;
		if (lines[i].yu >= d->topY[lines[i].x])
		{
			j = lines[i].yu + 1;
			while (--j >= d->topY[lines[i].x])
				if (j < d->bottomY[lines[i].x])
					set_pixel(iw->sur, lines[i].x, j, 0x0000FF);
			d->topY[lines[i].x] = lines[i].yu + 1;
		}
	}
}

// Бесполезные фиолетовые линии для разделения между стенами
void	draw_walls_lines(t_wall_line *lines, t_sdl *iw)
{
	int		j;

	j = lines[0].yu;
	if (j < 0)
		j = 0;
	while (j < lines[0].yd && ++j < WINDOW_H)
		set_pixel(iw->sur, lines[0].x, j, 0xFF00FF);
}

// Очистить лист стен, которые идут подряд и находятся на одной прямой
void	free_save(t_save_wall_list **l)
{
	t_save_wall_list *tmp;
	t_save_wall_list *tmp2;

	tmp = *l;
	while (tmp != 0)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	*l = 0;
}

// Промежуточные линии между секторами
void	draw_between_sectors_walls(t_wall_line *lines, t_sdl *iw, t_draw *d, int len)
{
	int i;
	int j;

	i = -1;
	//printf("l0 %d ll %d\n", lines[0].yu, lines[len - 10].yu);
	while (++i < len)
	{
		if (d->topY[lines[i].x] >= d->bottomY[lines[i].x])
			continue;
		if (lines[i].yu >= d->topY[lines[i].x])
		{
			j = lines[i].yu + 1;
			while (--j >= d->topY[lines[i].x])
				if (j < d->bottomY[lines[i].x])
					set_pixel(iw->sur, lines[i].x, j, 0x00FF00);
			d->topY[lines[i].x] = lines[i].yu + 1;
		}
		if (lines[i].yd < d->bottomY[lines[i].x])
		{
			j = lines[i].yd - 1;
			while (++j < d->bottomY[lines[i].x])
				if (j >= d->topY[lines[i].x])
					set_pixel(iw->sur, lines[i].x, j, 0x00FF00);
			d->bottomY[lines[i].x] = lines[i].yd;
		}
	}
}

void	draw_next_wall(t_draw *d, t_sdl *iw);

void	get_wall_lines(t_draw *d, t_draw *d2, t_sdl *iw, const char b);

void	get_zd_zu(t_draw *d, t_sdl *iw, int wall);

// Функция, которая рекурсивно рисует то что внутри портала
void	draw_next_sector(t_sdl *iw, t_draw d, int sector, int i)
{
	t_draw d2;

	d.curr_sector = sector;
	get_ray(&d, (i + 1) * 2, iw);
	d.curr_wall = get_wall(&d, iw, 1);
	d2.p = d.p;
	d2.curr_sector = sector;
	get_ray(&d2, (d.xright - 1) * 2, iw);
	d2.curr_wall = get_wall(&d2, iw, 1);
	get_zd_zu(&d, iw, d.curr_wall);
	get_zd_zu(&d2, iw, d2.curr_wall);
	get_wall_lines(&d, &d2, iw, 1);
	while (d.i < d.xright)
		draw_next_wall(&d, iw);
}

// Сложна...
void	get_real_portal_trapeze(t_draw *d, t_sdl *iw)
{
	get_ray(d, (d->p->xleft + 1) * 2, iw);
	d->curr_wall = get_wall(d, iw, 1);
	get_zd_zu(d, iw, d->curr_wall);
	d->len = (int)(sqrt(powf((float)(d->rx - iw->p.x), 2) + powf((float)(d->ry - iw->p.y), 2))) + 1;
	d->p->yd1 = WINDOW_H * (iw->p.z + d->len / 2 - d->zd) / d->len;
	d->p->yu1 = WINDOW_H * (iw->p.z + d->len / 2 - d->zu) / d->len;
	get_ray(d, (d->p->xright - 1) * 2, iw);
	d->curr_wall = get_wall(d, iw, 1);
	get_zd_zu(d, iw, d->curr_wall);
	d->len = (int)(sqrt(powf((float)(d->rx - iw->p.x), 2) + powf((float)(d->ry - iw->p.y), 2))) + 1;
	d->p->yd2 = WINDOW_H * (iw->p.z + d->len / 2 - d->zd) / d->len;
	d->p->yu2 = WINDOW_H * (iw->p.z + d->len / 2 - d->zu) / d->len;
}

// Рисование всего
void	draw_all(t_wall_line *lines, t_sdl *iw, t_draw *d, int len)
{
	t_save_wall_list *tmp;
	t_save_wall_list *tmp2;
	int				z;
	int				xr;
	//printf("drfloor\n");
	draw_floor(lines, iw, d, len);
	//printf("drceil\n");
	draw_ceil(lines, iw, d, len);
	tmp = iw->l;
	tmp2 = tmp;
	z = 0;
	//printf("drwall\n");
	while (tmp != 0)
	{
		if (tmp->wall < 0)
		{
			z += tmp->i - lines[z].x;
			tmp = tmp->next;
			continue ;
		}
		//printf("tmpwall = %d\n", tmp->wall);
		if (iw->walls[tmp->wall].nextsector == -1)
			draw_wall(lines + z, iw, d, tmp->i - lines[z].x);
		else
		{
			//printf("else\n");
			xr = d->xright;
			d->xright = lines[z + tmp->i - lines[z].x].x;
			d->p = (t_draw_portal *)malloc(sizeof(t_draw_portal));
			d->p->xleft = lines[z].x;
			d->p->xright = d->xright;
			d->p->pyu1 = lines[z].yu;
			d->p->pyd1 = lines[z].yd;
			d->p->pyu2 = lines[z + tmp->i - lines[z].x].yu;
			d->p->pyd2 = lines[z + tmp->i - lines[z].x].yd;
			get_real_portal_trapeze(d, iw);
			//get_center_sz(d, iw);
			// d->p->center_sz = (d->p->yd1 + ((d->p->xright + d->p->xleft) / 2  - d->p->xleft) * (d->p->yd1 - d->p->yd2) / (d->p->xright - d->p->xleft)) -
			// 	(d->p->yu1 - ((d->p->xright + d->p->xleft) / 2 - d->p->xleft) * (d->p->yu1 - d->p->yu2) / (d->p->xright - d->p->xleft));

			draw_next_sector(iw, *d, iw->walls[tmp->wall].nextsector, lines[z].x + 1);
			d->xright = xr;
			free(d->p);
			d->p = 0;
		}
		draw_walls_lines(lines + z, iw);
		z += tmp->i - lines[z].x;
		//printf("z %d\n", z);
		tmp = tmp->next;
	}
	free_save(&tmp2);
	//printf("draw done\n\n");
}

// Определение двух точек соседних стен на экране, проведение верхней и нижней линии между ними и вызов функции рисования
void	get_wall_lines(t_draw *d, t_draw *d2, t_sdl *iw, const char b)
{
	t_wall_line *lines;
	t_draw_line line;
	int			len;
	//int			winh;

	lines = (t_wall_line *)malloc((d2->i - d->i + 1) * sizeof(t_wall_line));
	if (lines == 0)
		return ;
	lines[0].x = d->i;
	lines[d2->i - d->i - 1].x = d2->i;
	d->len = (int)(sqrt(powf((float)(d->rx - iw->p.x), 2) + powf((float)(d->ry - iw->p.y), 2))) + 1;
	d2->len = (int)(sqrt(powf((float)(d2->rx - iw->p.x), 2) + powf((float)(d2->ry - iw->p.y), 2))) + 1;
	lines[0].yu = WINDOW_H * (iw->p.z + d->len / 2 - d->zu) / d->len;// + ((d->p != 0) ? d->p->uplus : 0);
	lines[0].yd = WINDOW_H * (iw->p.z + d->len / 2 - d->zd) / d->len;//- ((d->p != 0) ? d->p->dplus : 0);
	if (d->p != 0)
	{
		d->p->yd = d->p->yd1 - (d->i - d->p->xleft) * (d->p->yd1 - d->p->yd2) / (d->p->xright - d->p->xleft);
		d->p->yu = d->p->yu1 - (d->i - d->p->xleft) * (d->p->yu1 - d->p->yu2) / (d->p->xright - d->p->xleft);
		d->p->pyd = d->p->pyd1 - (d->i - d->p->xleft) * (d->p->pyd1 - d->p->pyd2) / (d->p->xright - d->p->xleft);
		d->p->pyu = d->p->pyu1 - (d->i - d->p->xleft) * (d->p->pyu1 - d->p->pyu2) / (d->p->xright - d->p->xleft);
		lines[0].yu = (d->p->pyu * (d->p->yd - lines[0].yu) + d->p->pyd * (lines[0].yu - d->p->yu)) / (d->p->yd - d->p->yu);
		lines[0].yd = (d->p->pyu * (d->p->yd - lines[0].yd) + d->p->pyd * (lines[0].yd - d->p->yu)) / (d->p->yd - d->p->yu);
	}
	lines[d2->i - d->i - 1].yu = WINDOW_H * (iw->p.z + d2->len / 2 - d2->zu) / d2->len;// + ((d->p != 0) ? d->p->uplus : 0);
	lines[d2->i - d->i - 1].yd = WINDOW_H * (iw->p.z + d2->len / 2 - d2->zd) / d2->len;// + ((d->p != 0) ? d->p->dplus : 0);
	if (d->p != 0)
	{
		d->p->yd = d->p->yd1 - (d2->i - d->p->xleft) * (d->p->yd1 - d->p->yd2) / (d->p->xright - d->p->xleft);
		d->p->yu = d->p->yu1 - (d2->i - d->p->xleft) * (d->p->yu1 - d->p->yu2) / (d->p->xright - d->p->xleft);
		d->p->pyd = d->p->pyd1 - (d2->i - d->p->xleft) * (d->p->pyd1 - d->p->pyd2) / (d->p->xright - d->p->xleft);
		d->p->pyu = d->p->pyu1 - (d2->i - d->p->xleft) * (d->p->pyu1 - d->p->pyu2) / (d->p->xright - d->p->xleft);
		lines[d2->i - d->i - 1].yu = (d->p->pyu * (d->p->yd - lines[d2->i - d->i - 1].yu) + d->p->pyd * (lines[d2->i - d->i - 1].yu - d->p->yu)) / (d->p->yd - d->p->yu);
		lines[d2->i - d->i - 1].yd = (d->p->pyu * (d->p->yd - lines[d2->i - d->i - 1].yd) + d->p->pyd * (lines[d2->i - d->i - 1].yd - d->p->yu)) / (d->p->yd - d->p->yu);
	}
	line.x0 = d->i;
	line.x1 = d2->i;
	line.y0 = lines[0].yd;
	line.y1 = lines[d2->i - d->i - 1].yd;
	brez_wall_line(lines, line, 0);
	line.y0 = lines[0].yu;
	line.y1 = lines[d2->i - d->i - 1].yu;
	brez_wall_line(lines, line, 1);
	if (b == 0)
		draw_all(lines, iw, d, d2->i - d->i);
	else
		draw_between_sectors_walls(lines, iw, d, d2->i - d->i);
	free(lines);
}

// Берем верхнюю и нижнюю координату по Z из rx,ry(туда, куда попал луч)
void	get_zd_zu(t_draw *d, t_sdl *iw, int wall)
{
	int		wall2;
	float	walllen;
	float	raywalllen;

	wall2 = get_next_wall(iw, wall, d->curr_sector);
	if (iw->walls[wall].zd == iw->walls[wall2].zd && iw->walls[wall].zu == iw->walls[wall2].zu)
	{
		d->zd = iw->walls[wall].zd;
		d->zu = iw->walls[wall].zu;
		return;
	}
	walllen = (int)sqrtf(powf((float)(iw->walls[wall].x - iw->walls[wall2].x), 2) + powf((float)(iw->walls[wall].y - iw->walls[wall2].y), 2));
	raywalllen = (int)sqrtf(powf((float)(iw->walls[wall].x - d->rx), 2) + powf((float)(iw->walls[wall].y - d->ry), 2));
	d->zd = iw->walls[wall].zd + (int)((float)(iw->walls[wall2].zd - iw->walls[wall].zd) * raywalllen / walllen);
	d->zu = iw->walls[wall].zu + (int)((float)(iw->walls[wall2].zu - iw->walls[wall].zu) * raywalllen / walllen);
}

// Возвращает один если стены wall1, wall2 лежат на одной прямой
int		same_wall_direction(t_sdl *iw, int wall1, int wall2)
{
	if (iw->walls[wall1].hv != 0 && iw->walls[wall2].hv != 0 && iw->walls[wall1].hv == iw->walls[wall2].hv)
		return (1);
	if (iw->walls[wall1].hv == 0 && iw->walls[wall2].hv == 0)
		if (iw->walls[wall1].k == iw->walls[wall2].k && iw->walls[wall1].b == iw->walls[wall2].b)
			return (1);
	return (0);
}

// Сохраняет нужные данные стены в лист
void	save_wall(t_save_wall_list **l, int i, int wall)
{
	t_save_wall_list *tmp;
	t_save_wall_list *tmp2;

	tmp = (t_save_wall_list *)malloc(sizeof(t_save_wall_list));
	tmp->i = i;
	tmp->wall = wall;
	tmp->next = 0;
	if (*l == 0)
		*l = tmp;
	else
	{
		tmp2 = *l;
		while (tmp2->next != 0)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}

// Отрисовка "следующей" стены
void	draw_next_wall(t_draw *d, t_sdl *iw)
{
	t_draw	d2;
	int		pw;
	//t_draw	save;

	//printf("hell\n");
	iw->l = 0;
	d2.p = d->p;
	d2.curr_sector = d->curr_sector;
	d2.xright = d->xright;
	find_x_next_wall(d->curr_wall, d->i, &d2, iw);
	save_wall(&(iw->l), d2.i, d->curr_wall);
	pw = d->curr_wall;
	while (get_next_wall(iw, pw, d->curr_sector) == d2.curr_wall &&
	same_wall_direction(iw, d->curr_wall, d2.curr_wall) && d2.i < d2.xright)
	{
		pw = d2.curr_wall;
		find_x_next_wall(d2.curr_wall, d2.i, &d2, iw);
		save_wall(&(iw->l), d2.i, pw);
	}

	/*t_save_wall_list *tmp;
	tmp = iw->l;
	while (tmp != 0)
	{
		printf("i %d wall %d\n", tmp->i, tmp->wall);
		tmp = tmp->next;
	}
	printf("\n");*/
	//printf("rx %d ry %d\n", d2.rx, d2.ry);
	get_zd_zu(d, iw, d->curr_wall);
	get_zd_zu(&d2, iw, d2.curr_wall);
	//printf("zu %d zd %d\n", d2.zu, d);
	get_wall_lines(d, &d2, iw, 0);
	//free_save(&(iw->l));
	// if (d2.p != 0)
	// 	printf("3\n");
	d->p = d2.p;
	d->i = d2.i;
	d->curr_wall = d2.curr_wall;
	d->rx = d2.rx;
	d->ry = d2.ry;
}

// Функция "рисуй всё"
void	draw(t_sdl *iw)
{
	t_draw d;

	set_top_bottom(&d);
	if ((d.curr_sector = get_sector(iw)) == -1)
		return;
	get_ray(&d, 0, iw);
	d.curr_wall = get_wall(&d, iw, 0);
	d.xright = WINDOW_W;
	d.p = 0;
	while (d.i < WINDOW_W - 1)
		draw_next_wall(&d, iw);
}

// Обновление экрана с полной перерисовкой
void	update(t_sdl *iw)
{
	SDL_FreeSurface(iw->sur);
	SDL_DestroyTexture(iw->tex);
	iw->sur = SDL_CreateRGBSurface(0, WINDOW_W, WINDOW_H, 32, 0, 0, 0, 0);
	draw(iw);
	iw->tex = SDL_CreateTextureFromSurface(iw->ren, iw->sur);
	SDL_RenderClear(iw->ren);
	SDL_RenderCopy(iw->ren, iw->tex, 0, 0);
	SDL_RenderPresent(iw->ren);
}

// Начальные полиции, поворот игрока и угол обзора
void	get_def(t_sdl *iw)
{
	iw->p.x = 1000;
	iw->p.y = 2000;
	iw->p.z = 340;
	iw->p.rot = 91;
	iw->p.angle = 23 * WINDOW_W / WINDOW_H;
}

// Дарова!
int main(void)
{
	t_sdl	iw;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetRelativeMouseMode(0);
	iw.win = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
	iw.ren = SDL_CreateRenderer(iw.win, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC);
	iw.sur = SDL_CreateRGBSurface(0, WINDOW_W, WINDOW_H, 32, 0, 0, 0, 0);
	SDL_RenderClear(iw.ren);
	SDL_RenderPresent(iw.ren);
	get_def(&iw);
	get_map(&iw);
	get_walls_lines(&iw);
	draw(&iw);
	iw.tex = SDL_CreateTextureFromSurface(iw.ren, iw.sur);
	SDL_RenderClear(iw.ren);
	SDL_RenderCopy(iw.ren, iw.tex, 0, 0);
	SDL_RenderPresent(iw.ren);
	main_loop(&iw);
	free(iw.walls);
	free(iw.sectors);
	SDL_DestroyRenderer(iw.ren);
	SDL_DestroyWindow(iw.win);
	SDL_Quit();
	return (0);
}
