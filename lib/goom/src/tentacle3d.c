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

#define nbgrid 6
#define num_x 10
#define num_z 10
#define num_x_mod 3
#define num_z_mod 3
#define x_increment 100
#define y_increment 100
#define z_increment 100
#define y_inc_mod 10
#define x_width num_x * x_increment
#define z_width num_z * z_increment
#define x_width_mod 10
#define z_width_mod 10

typedef struct _TENTACLE_FX_DATA {
	PluginParam enabled_bp;
	PluginParameters params;

	float cycle;
	grid3d *grille[nbgrid];
	float *vals;

#define NB_TENTACLE_COLORS 5
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
	data->colors[0] = (0x18<<(ROUGE*8))|(0x4c<<(VERT*8))|(0x2f<<(BLEU*8));
	data->colors[1] = (0x48<<(ROUGE*8))|(0x2c<<(VERT*8))|(0x6f<<(BLEU*8));
	data->colors[2] = (0x58<<(ROUGE*8))|(0x3c<<(VERT*8))|(0x0f<<(BLEU*8));
	data->colors[3] = (0x87<<(ROUGE*8))|(0x55<<(VERT*8))|(0x74<<(BLEU*8));
	data->colors[4] = (0x97<<(ROUGE*8))|(0x75<<(VERT*8))|(0x94<<(BLEU*8));
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
                    (float)goomInfo->sound.accelvar,
                    goomInfo->curGState->drawTentacle, data);
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
	const int len = n2 - n1;
	return n1 + rand() % (len + 1);
}

static void tentacle_new (TentacleFXData *data) {
	v3d center = {0, 0, 0};
	data->vals = (float*)malloc ((num_x+20)*sizeof(float));

	/* Start at bottom of grid, going up by 'y_increment' */
	float y = -0.5*(nbgrid * y_increment);
	for (int tmp=0;tmp<nbgrid;tmp++) {
		const int x_size = x_width + get_rand_in_range(-x_width_mod/2, x_width_mod/2);
		const int z_size = z_width + get_rand_in_range(-z_width_mod/2, z_width_mod/2);

		center.z = z_size;
		center.y = y + get_rand_in_range(-y_inc_mod/2, y_inc_mod/2);

                const int x_def = num_x + get_rand_in_range(-num_x_mod/2, num_x_mod/2);
                const int z_def = num_z + get_rand_in_range(-num_z_mod/2, num_z_mod/2);

		data->grille[tmp] = grid3d_new(x_size, x_def, z_size, z_def, center);

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

static void lightencolor (uint32_t *col, float power)
{
	uint8_t *color;

	color = (uint8_t *) col;
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

static int evolutecolor (unsigned int src,unsigned int dest,
                         unsigned int mask, unsigned int incr) {
	
	int color = src & (~mask);
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

	float tmp;

	/* many magic numbers here... I don't really like that. */
	if (fx_data->happens)
		fx_data->happens -= 1;
	else if (fx_data->lock == 0) {
		fx_data->happens = goom_irand(goomInfo->gRandom,200)?0:100+goom_irand(goomInfo->gRandom,60);
		fx_data->lock = fx_data->happens * 3 / 2;
	}
	else fx_data->lock --;

	tmp = fx_data->happens?8.0f:0;
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

static void tentacle_update(PluginInfo *goomInfo, Pixel *buf, Pixel *back, int W, int H,
                     gint16 data[NUM_AUDIO_SAMPLES][AUDIO_SAMPLE_LEN], float rapport, int drawit, TentacleFXData *fx_data) {
	
	int tmp;
	int tmp2;

	uint32_t color;
	uint32_t colorlow;

	float dist,dist2,rotangle;

	if ((!drawit) && (fx_data->ligs>0.0f))
		fx_data->ligs = -fx_data->ligs;

	fx_data->lig += fx_data->ligs;

	if (fx_data->lig > 1.01f) {
		if ((fx_data->lig>10.0f) || (fx_data->lig<1.1f)) fx_data->ligs = -fx_data->ligs;

		if ((fx_data->lig<6.3f)&&(goom_irand(goomInfo->gRandom,30)==0))
			fx_data->dstcol=goom_irand(goomInfo->gRandom,NB_TENTACLE_COLORS);

		fx_data->col = evolutecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xff,0x01);
		fx_data->col = evolutecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xff00,0x0100);
		fx_data->col = evolutecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xff0000,0x010000);
		fx_data->col = evolutecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xff000000,0x01000000);
		fx_data->col = evolutecolor(fx_data->col,fx_data->colors[fx_data->dstcol],0xf0000000,0x11000000);

		color = fx_data->col;
		colorlow = fx_data->col;

		lightencolor(&color,fx_data->lig * 2.0f + 2.0f);
		lightencolor(&colorlow,(fx_data->lig/3.0f)+0.67f);

		rapport = 1.0f + 2.0f * (rapport - 1.0f);
		rapport *= 1.2f;
		if (rapport > 1.12f)
			rapport = 1.12f;

		pretty_move (goomInfo, fx_data->cycle, &dist, &dist2, &rotangle, fx_data);

		for (tmp=0;tmp<nbgrid;tmp++) {
			for (tmp2=0;tmp2<num_x;tmp2++) {
				const float val = (float)(ShiftRight(data[0][goom_irand(goomInfo->gRandom,AUDIO_SAMPLE_LEN-1)],10)) * rapport;
				fx_data->vals[tmp2] = val;
			}

			grid3d_update (fx_data->grille[tmp], rotangle, fx_data->vals, dist2);
		}
		fx_data->cycle+=0.01f;
		int color_num = 0;
		for (tmp=0;tmp<nbgrid;tmp++) {
                   	int my_col = fx_data->colors[color_num] * color;
			color_num++;
			if (color_num > NB_TENTACLE_COLORS) color_num = 0;
			grid3d_draw (goomInfo, fx_data->grille[tmp],my_col,colorlow,dist,buf,back,W,H);
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