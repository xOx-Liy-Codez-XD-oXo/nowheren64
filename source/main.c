#include <libdragon.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/gl_integration.h>
#include <rspq_profile.h>
#include <malloc.h>
#include <math.h>
#include <timer.h>

#define MATH_3D_IMPLEMENTATION 1
#include "math_3d.h"

#define f32 float

#include "mdl/lakeHairRegular_liym.h"
#include "mdl/lakeEars_liym.h"
#include "mdl/lakeHairTufts_liym.h"
#include "mdl/lakeHead_liym.h"
#include "mdl/lakeEye_liym.h"
#include "mdl/lakeEyebrow_liym.h"
#include "mdl/lakeTorso_liym.h"
#include "mdl/stage.h"        //combined
#include "mdl/lakeHairRipLeft_liym.h"
#include "mdl/lakeEarsRipLeft_liym.h"
#include "mdl/lakeHairTuftsRipLeft_liym.h"
#include "mdl/lakeHairRipRight_liym.h"
#include "mdl/lakeEarsRipRight_liym.h"
#include "mdl/lakeHairTuftsRipRight_liym.h"
#include "mdl/string_liym.h"     // no col
#include "mdl/scissor1_liym.h"
#include "mdl/scissor2_liym.h"
#include "mdl/clipping_liym.h"

#include "mdl/mouth/lakeMouthClose_liym.h"
#include "mdl/mouth/lakeMouthClosejawShoteef_liym.h"
#include "mdl/mouth/lakeMouthEh_liym.h"
#include "mdl/mouth/lakeMouthM_liym.h"
#include "mdl/mouth/lakeMouthO_liym.h"

#include "mdl/tex1_liym.h"
#include "mdl/tex2_liym.h"
#include "mdl/tex3_liym.h"

#include "anim/lakeHeadAnim.h"
#include "anim/lakeEyeAnim.h"
#include "anim/lakePupilAnim.h"
#include "anim/mouthAnims.h"
#include "anim/lakeEyebrowAnim.h"
#include "anim/lakeTorsoAnim.h"
#include "anim/lakeHairRipLeftAnim.h"
#include "anim/lakeHairRipRightAnim.h"
#include "anim/scissor1anim.h"
#include "anim/scissor2anim.h"
#include "anim/stringAnim.h"
#include "anim/lakeHairClippingAnim.h"

#include "anim/camAnim.h"
#include "anim/camFovAnim.h"

unsigned char frameadvance = 1;
int frame = 0;
int rframe = 0;
int dbgval = 0;
float accumulatedbehindtime = 0.0f;

rdpq_paragraph_t* par1;
rdpq_paragraph_t* par2;
rdpq_paragraph_t* par3;

#include "displaylist.h"
#include "liyt.h"

float ticksToMs(unsigned long long us) {
	return (float)TIMER_MICROS(us) * 0.001f;
}

void initDraw() {
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.33f, 0.576f, 0.835f, 1.0f);

	glDisable(GL_LIGHTING);
	glDisable(GL_NORMALIZE);
	glDisable(GL_CULL_FACE);

	glDisable(GL_RDPQ_TEXTURING_N64);
	glDisable(GL_RDPQ_MATERIAL_N64);
	glDisable(GL_TEXTURE_2D);
}

void drawFrame() {
	surface_t *disp = display_get();
	//surface_t *zbuf = display_get_zbuf();
	rdpq_attach(disp, NULL);

	gl_context_begin();

	unsigned long long starttime = timer_ticks();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	unsigned int frame12 = frame * 12;
	unsigned int frame9 = frame * 9;
	mat4_t view = mat4(cameraAnim[frame12], cameraAnim[(frame12) + 1], cameraAnim[(frame12) + 2], cameraAnim[(frame12) + 3],
	                   cameraAnim[(frame12) + 4], cameraAnim[(frame12) + 5], cameraAnim[(frame12) + 6], cameraAnim[(frame12) + 7],
	                   cameraAnim[(frame12) + 8], cameraAnim[(frame12) + 9], cameraAnim[(frame12) + 10], cameraAnim[(frame12) + 11],
	                   0.0f, 0.0f, 0.0f, 1.0f);
	mat4_t model, modelview, model2, persp;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	persp = m4_perspective(cameraFovAnim[frame] * 1.6f, 1.333f, 0.5f, 30.0f);
	persp.m[2][1] += (VI_REGISTERS[13] & 33554432) ? 0.0 : 0.0041666666666666;
	glLoadMatrixf((float *)&persp);
	glMatrixMode(GL_MODELVIEW);

	char lakeFrontfacing = 1;
	if(frame >= 338 && frame <= 405) lakeFrontfacing = 0;
	if(frame >= 842 && frame <= 843) lakeFrontfacing = 0;
	if(frame >= 880 && frame <= 931) lakeFrontfacing = 0;
	if(frame >= 997 && frame <= 1034) lakeFrontfacing = 0;
	if(frame >= 1125 && frame <= 1179) lakeFrontfacing = 0;
	

	//Stage
	if(frame >= 1538) {
		model = genMtxPosRotScaleZyx(0.0f, 2.0f, 0.640f, 
		                             -1.571f, 0.0f, 3.141f, 
		                             2.0f, 2.0f, 8.0f);
	} else {
		model = genMtxPosRotScaleZyx(0.0f, 0.0f, -1.354f, 
		                             0.0f, 0.0f, 0.0f, 
		                             2.0f, 2.0f, 2.0f);
	}
	modelview = m4_mul(view, model);
	glLoadMatrixf((float *)&modelview);
	glCallList(dlStage);

	if(!lakeFrontfacing) {
		model2 = genMtxPosRotScaleZyx(lakeTorsoAnim[frame9], lakeTorsoAnim[frame9 + 1], lakeTorsoAnim[frame9 + 2], 
	                              lakeTorsoAnim[frame9 + 3], lakeTorsoAnim[frame9 + 4], lakeTorsoAnim[frame9 + 5], 
	                              lakeTorsoAnim[frame9 + 6], lakeTorsoAnim[frame9 + 7], lakeTorsoAnim[frame9 + 8]);
		model2 = m4_mul(view, model2);
		glLoadMatrixf((float *)&model2);
		glCallList(dlLakeTorso);
	}

	//head matrix
	model = genMtxPosRotScaleZyx(lakeHeadAnim[frame9], lakeHeadAnim[frame9 + 1], lakeHeadAnim[frame9 + 2], 
	                             lakeHeadAnim[frame9 + 3], lakeHeadAnim[frame9 + 4], lakeHeadAnim[frame9 + 5], 
	                             lakeHeadAnim[frame9 + 6], lakeHeadAnim[frame9 + 7], lakeHeadAnim[frame9 + 8]);
	modelview = m4_mul(view, model);
	glLoadMatrixf((float *)&modelview);
	if(frame < 1203) {
		if(lakeFrontfacing) {
			glCallList(dlLakeEars);
			glCallList(dlLakeHairTufts);
		}
		glCallList(dlLakeHair);
		if(!lakeFrontfacing) {
			glCallList(dlLakeEars);
		}
	} else {
		//Draw hair ripped halves
		model2 = genMtxPosRotScaleZyx(lakeHairRipLeftAnim[frame9], lakeHairRipLeftAnim[frame9 + 1], lakeHairRipLeftAnim[frame9 + 2], 
		                              lakeHairRipLeftAnim[frame9 + 3], lakeHairRipLeftAnim[frame9 + 4], lakeHairRipLeftAnim[frame9 + 5], 
		                              lakeHairRipLeftAnim[frame9 + 6], lakeHairRipLeftAnim[frame9 + 7], lakeHairRipLeftAnim[frame9 + 8]);
		model2 = m4_mul(view, model2);
		glLoadMatrixf((float *)&model2);
		glCallList(dlLakeEarsRipLeft);
		glCallList(dlLakeHairTuftsRipLeft);
		glCallList(dlLakeHairRipLeft);
		model2 = genMtxPosRotScaleZyx(lakeHairRipRightAnim[frame9], lakeHairRipRightAnim[frame9 + 1], lakeHairRipRightAnim[frame9 + 2], 
		                              lakeHairRipRightAnim[frame9 + 3], lakeHairRipRightAnim[frame9 + 4], lakeHairRipRightAnim[frame9 + 5], 
		                              lakeHairRipRightAnim[frame9 + 6], lakeHairRipRightAnim[frame9 + 7], lakeHairRipRightAnim[frame9 + 8]);
		model2 = m4_mul(view, model2);
		glLoadMatrixf((float *)&model2);
		glCallList(dlLakeEarsRipRight);
		glCallList(dlLakeHairTuftsRipRight);
		glCallList(dlLakeHairRipRight);
	}
	if(lakeFrontfacing) {
		model2 = genMtxPosRotScaleZyx(lakeTorsoAnim[frame9], lakeTorsoAnim[frame9 + 1], lakeTorsoAnim[frame9 + 2], 
		                              lakeTorsoAnim[frame9 + 3], lakeTorsoAnim[frame9 + 4], lakeTorsoAnim[frame9 + 5], 
		                              lakeTorsoAnim[frame9 + 6], lakeTorsoAnim[frame9 + 7], lakeTorsoAnim[frame9 + 8]);
		model2 = m4_mul(view, model2);
		glLoadMatrixf((float *)&model2);
		glCallList(dlLakeTorso);
		glLoadMatrixf((float *)&modelview);
		glCallList(dlLakeHead);
		switch(whichmouth[frame]) {
			case 0:
				glCallList(dlLakeMouthEh);
				break;
			case 1:
				glCallList(dlLakeMouthTeeth);
				break;
			case 2:
				glCallList(dlLakeMouthClose);
				break;
			case 3:
				glCallList(dlLakeMouthO);
				break;
			case 4:
				glCallList(dlLakeMouthM);
				break;
			default:
				break;
		}

		//eye
		model = genMtxPosRotScaleZyx(lakeEyeAnim[frame9], lakeEyeAnim[frame9 + 1], lakeEyeAnim[frame9 + 2], 
	 	                             lakeEyeAnim[frame9 + 3], lakeEyeAnim[frame9 + 4], lakeEyeAnim[frame9 + 5], 
	 	                             lakeEyeAnim[frame9 + 6], lakeEyeAnim[frame9 + 7], lakeEyeAnim[frame9 + 8]);
		modelview = m4_mul(view, model);
		glLoadMatrixf((float *)&modelview);
		glCallList(dlLakeEye);

		//pupil
		model = genMtxPosRotScaleZyx(lakePupilLAnim[frame9], lakePupilLAnim[frame9 + 1], lakePupilLAnim[frame9 + 2], 
	 	                             lakePupilLAnim[frame9 + 3], lakePupilLAnim[frame9 + 4], lakePupilLAnim[frame9 + 5], 
	 	                             lakePupilLAnim[frame9 + 6], lakePupilLAnim[frame9 + 7], lakePupilLAnim[frame9 + 8]);
		modelview = m4_mul(view, model);
		glLoadMatrixf((float *)&modelview);
		glCallList(dlLakePupil);
		model = genMtxPosRotScaleZyx(lakePupilRAnim[frame9], lakePupilRAnim[frame9 + 1], lakePupilRAnim[frame9 + 2], 
	 	                             lakePupilRAnim[frame9 + 3], lakePupilRAnim[frame9 + 4], lakePupilRAnim[frame9 + 5], 
	 	                             lakePupilRAnim[frame9 + 6], lakePupilRAnim[frame9 + 7], lakePupilRAnim[frame9 + 8]);
		modelview = m4_mul(view, model);
		glLoadMatrixf((float *)&modelview);
		glCallList(dlLakePupil);

		model = genMtxPosRotScaleZyx(lakeEyebrowAnim[frame9], lakeEyebrowAnim[frame9 + 1], lakeEyebrowAnim[frame9 + 2], 
	 	                             lakeEyebrowAnim[frame9 + 3], lakeEyebrowAnim[frame9 + 4], lakeEyebrowAnim[frame9 + 5], 
	 	                             lakeEyebrowAnim[frame9 + 6], lakeEyebrowAnim[frame9 + 7], lakeEyebrowAnim[frame9 + 8]);
		modelview = m4_mul(view, model);
		glLoadMatrixf((float *)&modelview);
		glCallList(dlLakeEyebrow);

		if(frame > 172 && frame < 339) {
			model = genMtxPosRotScaleZyx(scissor1Anim[frame9], scissor1Anim[frame9 + 1], scissor1Anim[frame9 + 2], 
	 		                             scissor1Anim[frame9 + 3], scissor1Anim[frame9 + 4], scissor1Anim[frame9 + 5], 
	 			                     scissor1Anim[frame9 + 6], scissor1Anim[frame9 + 7], scissor1Anim[frame9 + 8]);
			modelview = m4_mul(view, model);
			glLoadMatrixf((float *)&modelview);
			glCallList(dlscissor1);
			int lame9 = frame - 169;
			lame9 *= 9;
			model = genMtxPosRotScaleZyx(clippingAnim[lame9], clippingAnim[lame9 + 1], clippingAnim[lame9 + 2], 
	 		                             clippingAnim[lame9 + 3], clippingAnim[lame9 + 4], clippingAnim[lame9 + 5], 
	 			                     0.0625f, 0.0625f, 0.0625f);
			modelview = m4_mul(view, model);
			glLoadMatrixf((float *)&modelview);
			glCallList(dlLakeHairClipping);
			model = genMtxPosRotScaleZyx(scissor2Anim[frame9], scissor2Anim[frame9 + 1], scissor2Anim[frame9 + 2], 
	 		                             scissor2Anim[frame9 + 3], scissor2Anim[frame9 + 4], scissor2Anim[frame9 + 5], 
	 			                     scissor2Anim[frame9 + 6], scissor2Anim[frame9 + 7], scissor2Anim[frame9 + 8]);
			modelview = m4_mul(view, model);
			glLoadMatrixf((float *)&modelview);
			glCallList(dlscissor2);
		}
	}

	if(frame > 842 && frame < 1074) {
		model = genMtxPosRotScaleZyx(stringAnim[frame9], stringAnim[frame9 + 1], stringAnim[frame9 + 2], 
 		                             stringAnim[frame9 + 3], stringAnim[frame9 + 4], stringAnim[frame9 + 5], 
 			                     stringAnim[frame9 + 6], stringAnim[frame9 + 7], stringAnim[frame9 + 8]);
		modelview = m4_mul(view, model);
		glLoadMatrixf((float *)&modelview);
		glCallList(dlstring);
	}
	
	gl_context_end();

	if(frame > 1537 && frame < 1689) {
		rdpq_paragraph_render(par2, 120.0f, 100.0f);
		rdpq_paragraph_render(par1, 115.0f, 80.0f);
	}
	if(frame > 1688 && frame < 1850) {
		rdpq_paragraph_render(par3, 52.0f, 70.0f);
	}

	float cputimems = ticksToMs(timer_ticks() - starttime);

	if(dbgval) {
		rdpq_set_mode_fill(RGBA32(0, 0, 0, 255));
        	rdpq_fill_rectangle(20, 20, 130, 70);
	}
	rdpq_detach_wait();
	float frametimems = ticksToMs(timer_ticks() - starttime);
	float deltatime = display_get_delta_time() * 1000.0f;
	if(dbgval) {
		char timedisplay[100];
		snprintf(timedisplay, 100, "%.1f fps\n%.1f ms cpu\n%.1f ms gpu\n%.1f ms total", display_get_fps(), cputimems, frametimems, deltatime);
		graphics_draw_text(disp, 28, 24, timedisplay);
	}
	display_show(disp);

	if(frame > 1930) frameadvance = 0;
	if(frameadvance) {
		frame++;
		if(deltatime > 16.666667f) {
			accumulatedbehindtime += deltatime - 16.666667f;
			if(accumulatedbehindtime > 16.666667f) {
				frame++;
				accumulatedbehindtime -= 16.666667f;
			}
		}
	}
	rframe++;
}

int main() {
	resolution_t lilyres = {320, 240, true};

	display_init(lilyres, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_DISABLED );
	
	rdpq_init();
	gl_init();
	makeDisplayLists();
	timer_init();
	joypad_init(); //not needed ... adds like 20k
	dfs_init(DFS_DEFAULT_LOCATION);
	audio_init(48000, 2);
	mixer_init(2);
	wav64_init_compression(3);

	rdpq_font_t *fontbigtime = rdpq_font_load("rom:/bigtime.font64");
	rdpq_text_register_font(1, fontbigtime);
	rdpq_font_t *fontmedtime = rdpq_font_load("rom:/medtime.font64");
	rdpq_text_register_font(2, fontmedtime);
	rdpq_font_style(fontmedtime, 0, &(rdpq_fontstyle_t){
		.color = RGBA32(192, 192, 192, 255),
	});

	int thenumberfourteen = 14;
	par1 = rdpq_paragraph_build(&(rdpq_textparms_t){
        	.align = ALIGN_CENTER,
        	.valign = VALIGN_CENTER,
		.disable_aa_fix = 1,
        }, 1, "nowhere to go", &thenumberfourteen);
	int thenumbernineteen = 19;
	par2 = rdpq_paragraph_build(&(rdpq_textparms_t){
        	.align = ALIGN_CENTER,
        	.valign = VALIGN_CENTER,
		.disable_aa_fix = 1,
        }, 2, "juno, Jane Remover", &thenumbernineteen);
	int thenumbertwentythree = 23;
	par3 = rdpq_paragraph_build(&(rdpq_textparms_t){
		.width = 250,
		.wrap = WRAP_WORD,
        	.align = ALIGN_CENTER,
        	.valign = VALIGN_CENTER,
		.disable_aa_fix = 1,
        }, 1, "animation by lliy 2024", &thenumbertwentythree);

	wav64_t song;
	wav64_open(&song, "rom:/song.wav64");
	wav64_play(&song, 0);

	initDraw();

	//rspq_profile_start();

	display_set_fps_limit(60.0f);

	while(1) {
		joypad_poll();
		joypad_buttons_t btns = joypad_get_buttons_pressed(0);
		if(btns.a && frameadvance == 0) { frame = 0; frameadvance = 1; mixer_ch_stop(0); wav64_play(&song, 0); }
		if(btns.b) dbgval ^= 1;
		drawFrame();
		mixer_try_play();
	}

	return 0;

}
