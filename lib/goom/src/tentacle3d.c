#include <stdlib.h>
#include <stdint.h>

#include "v3d.h"
#include "surf3d.h"
#include "goom.h"
#include "goom_tools.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "tentacle3d.h"

#define D 256.0f

#define nbgrid 5
#define y_increment 10
#define y_inc_mod 10
#define num_x 15
#define num_z 45
#define tentacle_offset_x 85
#define tentacle_mod_x 10
#define tentacle_offset_z 35
#define tentacle_mod_z 20

typedef struct _TENTACLE_FX_DATA {
	PluginParam enabled_bp;
	PluginParameters params;

	float cycle;
	grid3d *grille[nbgrid];
	float *vals;

#define NB_TENTACLE_COLORS 100
#define NUM_COLORS_IN_GROUP (NB_TENTACLE_COLORS/5)
	int colors[NB_TENTACLE_COLORS];

	int col;
	int dstcol;
	float lig;
	float ligs;

	/* statics from pretty_move */
	float distt;
	float distt2;
	float rot; /* entre 0 et 2 * M_PI */
	int happens;
	int rotation;
	int lock;
} TentacleFXData;

static void tentacle_new (TentacleFXData *data);
static void tentacle_update(PluginInfo *goomInfo, Pixel *buf, Pixel *back, int W, int H,
gint16 data[NUM_AUDIO_SAMPLES][AUDIO_SAMPLE_LEN], float, int drawit, TentacleFXData *fx_data);
static void tentacle_free (TentacleFXData *data);
static void init_colors(uint32_t *colors);

/* 
 * VisualFX wrapper for the tentacles
 */

static void tentacle_fx_init(VisualFX *_this, PluginInfo *info) {
	
	TentacleFXData *data = (TentacleFXData*)malloc(sizeof(TentacleFXData));
	
	data->enabled_bp = secure_b_param("Enabled", 1);
	data->params = plugin_parameters ("3D Tentacles", 1);
	data->params.params[0] = &data->enabled_bp;

	data->cycle = 0.0f;
	data->col = (0x28<<(ROUGE*8))|(0x2c<<(VERT*8))|(0x5f<<(BLEU*8));
	data->dstcol = 0;
	data->lig = 1.15f;
	data->ligs = 0.1f;
	
	data->distt = 10.0f;
	data->distt2 = 0.0f;
	data->rot = 0.0f; /* entre 0 et 2 * M_PI */
	data->happens = 0;
	
	data->rotation = 0;
	data->lock = 0;
	init_colors(data->colors);
	tentacle_new(data);

	_this->params = &data->params;
	_this->fx_data = (void*)data;
}

static void tentacle_fx_apply(VisualFX *_this, Pixel *src, Pixel *dest, PluginInfo *goomInfo)
{
	TentacleFXData *data = (TentacleFXData*)_this->fx_data;
	if (BVAL(data->enabled_bp)) {
		tentacle_update(goomInfo, dest, src, goomInfo->screen.width,
			goomInfo->screen.height, goomInfo->sound.samples,
			(float)goomInfo->sound.accelvar, goomInfo->curGState->drawTentacle, data);
	}
}

static void tentacle_fx_free(VisualFX *_this) {
	TentacleFXData *data = (TentacleFXData*)_this->fx_data;
	free(data->params.params);
	tentacle_free(data);
	free(_this->fx_data);
}

VisualFX tentacle_fx_create(void) {
	VisualFX fx;
	fx.init = tentacle_fx_init;
	fx.apply = tentacle_fx_apply;
	fx.free = tentacle_fx_free;
	return fx;
}

/* ----- */

static void tentacle_free (TentacleFXData *data) {
	/* TODO : un vrai FREE GRID!! */
	int tmp;
	for (tmp=0;tmp<nbgrid;tmp++){
		grid3d *g = data->grille[tmp];
		free (g->surf.vertex);
		free (g->surf.svertex);
		free (g);
	}
	free (data->vals);
}

static inline int get_rand_in_range(int n1, int n2)
{
	const int range_len = n2 - n1 + 1;
	return n1 + rand() % range_len;
}

static void tentacle_new (TentacleFXData *data) {
	v3d center = {0, 0, 0};
	data->vals = (float*)malloc ((num_x+20)*sizeof(float));

	/* Start at bottom of grid, going up by 'y_increment' */
	float y = -0.5*(nbgrid * y_increment);
	for (int tmp=0; tmp < nbgrid; tmp++) {
		const int x = tentacle_offset_x + get_rand_in_range(-tentacle_mod_x/2, tentacle_mod_x/2);
		const int z = tentacle_offset_z + get_rand_in_range(-tentacle_mod_z/2, tentacle_mod_z/2);

		center.y = y + get_rand_in_range(-y_inc_mod/2, y_inc_mod/2);
		center.z = z;
		
		data->grille[tmp] = grid3d_new (x, num_x + get_rand_in_range(-4, 4), 
										z, num_z + get_rand_in_range(-6, 6), center);
		
		y += y_increment;
	}
}

static inline unsigned char lighten (unsigned char value, float power)
{
	int val = value;
	float t = (float) val * log10(power) / 2.0;

	if (t > 0) {
		val = (int) t; /* (32.0f * log (t)); */
		if (val > 255)
			val = 255;
		if (val < 0)
			val = 0;
		return val;
	}
	else {
		return 0;
	}
}

static void init_colors(uint32_t *colors)
{
	for (int i=0; i < NB_TENTACLE_COLORS; i++) {
		const uint8_t red = get_rand_in_range(20, 90);
		const uint8_t green = get_rand_in_range(20, 90);
		const uint8_t blue = get_rand_in_range(20, 90);
		colors[i] = (red<<(ROUGE*8))|(green<<(VERT*8))|(blue<<(BLEU*8));
	}
}

static void lightencolor (uint32_t *col, float power)
{
	uint8_t *color = (uint8_t *) col;

	*color = lighten (*color, power);
	color++;
	*color = lighten (*color, power);
	color++;
	*color = lighten (*color, power);
	color++;
	*color = lighten (*color, power);
}

/* retourne x>>s , en testant le signe de x */
#define ShiftRight(_x,_s) ((_x<0) ? -(-_x>>_s) : (_x>>_s))

static int evolvecolor (unsigned int src,unsigned int dest, unsigned int mask, unsigned int incr) {
	const int color = src & (~mask);
	src &= mask;
	dest &= mask;

	if ((src!=mask)
			&&(src<dest))
		src += incr;

	if (src>dest)
		src -= incr;
	return (src&mask)|color;
}

static void pretty_move (PluginInfo *goomInfo, float cycle, float *dist, float *dist2, float *rotangle, TentacleFXData *fx_data) {
	/* many magic numbers here... I don't really like that. */
	if (fx_data->happens)
		fx_data->happens -= 1;
	else if (fx_data->lock == 0) {
		fx_data->happens = goom_irand(goomInfo->gRandom,200)?0:100+goom_irand(goomInfo->gRandom,60);
		fx_data->lock = fx_data->happens * 3 / 2;
	}
	else fx_data->lock --;

	float tmp = fx_data->happens?8.0f:0;
	*dist2 = fx_data->distt2 = (tmp + 15.0f*fx_data->distt2)/16.0f;

	tmp = 30+D-90.0f*(1.0f+sin(cycle*19/20));
	if (fx_data->happens)
		tmp *= 0.6f;

	*dist = fx_data->distt = (tmp + 3.0f*fx_data->distt)/4.0f;

	if (!fx_data->happens){
		tmp = M_PI*sin(cycle)/32+3*M_PI/2;
	}
	else {
		fx_data->rotation = goom_irand(goomInfo->gRandom,500)?fx_data->rotation:goom_irand(goomInfo->gRandom,2);
		if (fx_data->rotation)
			cycle *= 2.0f*M_PI;
		else
			cycle *= -1.0f*M_PI;
		tmp = cycle - (M_PI*2.0) * floor(cycle/(M_PI*2.0));
	}

	if (abs(tmp-fx_data->rot) > abs(tmp-(fx_data->rot+2.0*M_PI))) {
		fx_data->rot = (tmp + 15.0f*(fx_data->rot+2*M_PI)) / 16.0f;
		if (fx_data->rot>2.0*M_PI)
			fx_data->rot -= 2.0*M_PI;
		*rotangle = fx_data->rot;
	}
	else if (abs(tmp-fx_data->rot) > abs(tmp-(fx_data->rot-2.0*M_PI))) {
		fx_data->rot = (tmp + 15.0f*(fx_data->rot-2.0*M_PI)) / 16.0f;
		if (fx_data->rot<0.0f)
			fx_data->rot += 2.0*M_PI;
		*rotangle = fx_data->rot;
	}
	else
		*rotangle = fx_data->rot = (tmp + 15.0f*fx_data->rot) / 16.0f;
}

static inline uint32_t color_multiply(uint32_t col1, uint32_t col2)
{
	uint8_t *color1 = (uint8_t *) &col1;
	uint8_t *color2 = (uint8_t *) &col2;
	uint32_t col;
	uint8_t *color = (uint8_t *) &col;

	*color = (*color1) * (*color2) / 256;
	color++; color1++; color2++;
	*color = (*color1) * (*color2) / 256;
	color++; color1++; color2++;
	*color = (*color1) * (*color2) / 256;
	color++; color1++; color2++;
	*color = (*color1) * (*color2) / 256;

	return col;
}

static void tentacle_update(PluginInfo *goomInfo, Pixel *buf, Pixel *back, int W, int H,
							gint16 data[NUM_AUDIO_SAMPLES][AUDIO_SAMPLE_LEN], float rapport, int drawit, TentacleFXData *fx_data) {

	float dist,dist2,rotangle;

	if ((!drawit) && (fx_data->ligs>0.0f))
		fx_data->ligs = -fx_data->ligs;

	fx_data->lig += fx_data->ligs;

	if (fx_data->lig > 1.01f) {
		if ((fx_data->lig>10.0f) || (fx_data->lig<1.1f)) fx_data->ligs = -fx_data->ligs;

		if ((fx_data->lig<6.3f)&&(goom_irand(goomInfo->gRandom,30)==0))
			fx_data->dstcol=goom_irand(goomInfo->gRandom,NB_TENTACLE_COLORS);

		fx_data->col = evolvecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xff,0x01);
		fx_data->col = evolvecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xff00,0x0100);
		fx_data->col = evolvecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xff0000,0x010000);
		fx_data->col = evolvecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xff000000,0x01000000);
		uint32_t color = fx_data->col;
		uint32_t colorlow = fx_data->col;

		lightencolor(&color,fx_data->lig * 2.0f + 2.0f);
		lightencolor(&colorlow,(fx_data->lig/3.0f)+0.67f);

		rapport = 1.0f + 2.0f * (rapport - 1.0f);
		rapport *= 1.2f;
		if (rapport > 1.12f)
			rapport = 1.12f;

		pretty_move (goomInfo, fx_data->cycle, &dist, &dist2, &rotangle, fx_data);

		for (int tmp=0;tmp<nbgrid;tmp++) {
			for (int tmp2=0;tmp2<num_x;tmp2++) {
				const float val = (float)(ShiftRight(data[0][goom_irand(goomInfo->gRandom,AUDIO_SAMPLE_LEN-1)],10)) * rapport;
				fx_data->vals[tmp2] = val;
			}

			grid3d_update (fx_data->grille[tmp], rotangle, fx_data->vals, dist2);
		}
		fx_data->cycle+=0.01f;

		int tentacle_color = fx_data->colors[0] * color;
		int tentacle_colorlow = fx_data->colors[0] * colorlow;
		int color_num = 0;
		int num_colors_in_row = 0;
		for (int tmp=0;tmp<nbgrid;tmp++) {
			if (num_colors_in_row >= NUM_COLORS_IN_GROUP) {
				tentacle_color = color_multiply(fx_data->colors[color_num], color);
				tentacle_colorlow = color_multiply(fx_data->colors[color_num], colorlow);
				color_num++;
				if (color_num >= NB_TENTACLE_COLORS) color_num = 0;
				num_colors_in_row = 0;
			}
			num_colors_in_row++;
			grid3d_draw (goomInfo, fx_data->grille[tmp],tentacle_color,tentacle_colorlow,dist,buf,back,W,H);
		}
	}
	else {
		fx_data->lig = 1.05f;
		if (fx_data->ligs < 0.0f)
			fx_data->ligs = -fx_data->ligs;
		pretty_move (goomInfo, fx_data->cycle, &dist, &dist2, &rotangle, fx_data);
		fx_data->cycle+=0.1f;
		if (fx_data->cycle > 1000)
			fx_data->cycle = 0;
	}
}
