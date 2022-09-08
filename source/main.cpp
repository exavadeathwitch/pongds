/******************************************************************************
*******************************************************************************
	Easy GL2D
	Sprites example
	Shows a some sprite capabilities of easy GL2D

	Relminator (Richard Eric M. Lope BSN RN)
	Http://Rel.Phatcode.Net

	Thanks to:
	Patater (Jaeden Amero) for the shuttle sprites

*******************************************************************************
******************************************************************************/

#include <nds.h>
#include <stdio.h>
#include <gl2d.h>
// GRIT auto-generated header
// can be found inside the /build directory
#include "title.h"
#include "num.h"
#include "over.h"
#include "uvcoord_num.h"
#include "uvcoord_over.h"
typedef struct ball_s {

    int x, y; /* position on the screen */
    int w, h; // ball width and height
    int dx, dy; /* movement vector */
} ball_t;

typedef struct paddle {

    int x, y;
    int w, h;
} paddle_t;

// Program globals
static ball_t ball;
static paddle_t paddle[2];
static int screensize[] = { 256, 192 };
int score[] = { 0,0 };

static void init_game() {

    ball.x = screensize[0] / 2;
    ball.y = screensize[1] / 2;
    ball.w = 10;
    ball.h = 10;
    ball.dy = 0;
    ball.dx = -2;

    paddle[0].x = 20;
    paddle[0].y = screensize[1] / 2;
    paddle[0].w = 10;
    paddle[0].h = 50;

    paddle[1].x = 256 - 20;
    paddle[1].y = screensize[1] / 2;
    paddle[1].w = 10;
    paddle[1].h = 50;
}

int check_score() {

    int i;

    //loop through player scores
    for (i = 0; i < 2; i++) {

        //check if score is @ the score win limit
        if (score[i] == 10) {

            //reset scores
            score[0] = 0;
            score[1] = 0;

            //return 1 if player 1 score @ limit
            if (i == 0) {

                return 1;

                //return 2 if player 2 score is @ limit
            }
            else {

                return 2;
            }
        }
    }

    //return 0 if no one has reached a score of 10 yet
    return 0;
}

int check_collision(ball_t a, paddle_t b) {

	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;

	left_a = a.x;
	right_a = a.x + a.w;
	top_a = a.y;
	bottom_a = a.y + a.h;

	left_b = b.x;
	right_b = b.x + b.w;
	top_b = b.y;
	bottom_b = b.y + b.h;


	if (left_a > right_b) {
		return 0;
	}

	if (right_a < left_b) {
		return 0;
	}

	if (top_a > bottom_b) {
		return 0;
	}

	if (bottom_a < top_b) {
		return 0;
	}

	return 1;
}

static void move_ball() {
	if (ball.dx > 20)
		ball.dx = 20;
	if (ball.dx < -20)
		ball.dx = -20;
	if (ball.dy > 20)
		ball.dy = 20;
	if (ball.dy < -20)
		ball.dy = -20;
	/* Move the ball by its motion vector. */
	ball.x += ball.dx;
	ball.y += ball.dy;

	/* Turn the ball around if it hits the edge of the screen. */
	if (ball.x < 0) {

		score[1] += 1;
		init_game();
	}

	if (ball.x > screensize[0] - 10) {

		score[0] += 1;
		init_game();
	}

	if (ball.y < 0) {
		ball.y = 0;
		ball.dy = -ball.dy;
	}
	if (ball.y > screensize[1] - 10) {
		ball.dy = -ball.dy;
	}

	//check for collision with the paddle
	int i;

	for (i = 0; i < 2; i++) {

		int c = check_collision(ball, paddle[i]);

		//collision detected	
		if (c == 1) {

			//ball moving left
			if (ball.dx < 0) {

				ball.dx -= 1;

				//ball moving right
			}
			else {

				ball.dx += 1;
			}

			//change ball direction
			ball.dx = -ball.dx;

			//change ball angle based on where on the paddle it hit
			int hit_pos = (paddle[i].y + paddle[i].h) - ball.y;

			if (hit_pos >= 0 && hit_pos < 7) {
				ball.dy = 4;
			}

			if (hit_pos >= 7 && hit_pos < 14) {
				ball.dy = 3;
			}

			if (hit_pos >= 14 && hit_pos < 21) {
				ball.dy = 2;
			}

			if (hit_pos >= 21 && hit_pos < 28) {
				ball.dy = 1;
			}

			if (hit_pos >= 28 && hit_pos < 32) {
				ball.dy = 0;
			}

			if (hit_pos >= 32 && hit_pos < 39) {
				ball.dy = -1;
			}

			if (hit_pos >= 39 && hit_pos < 46) {
				ball.dy = -2;
			}

			if (hit_pos >= 46 && hit_pos < 53) {
				ball.dy = -3;
			}

			if (hit_pos >= 53 && hit_pos <= 60) {
				ball.dy = -4;
			}

			//ball moving right
			if (ball.dx > 0) {

				//teleport ball to avoid mutli collision glitch
				if (ball.x < 30) {

					ball.x = 30;
				}

				//ball moving left
			}
			else {

				//teleport ball to avoid mutli collision glitch
				if (ball.x > 600) {

					ball.x = 600;
				}
			}
		}
	}
}

static void move_paddle_ai()
{
	if (ball.y > paddle[1].y)
		paddle[1].y += 3;
	if (ball.y < paddle[1].y)
		paddle[1].y -= 3;
	if (paddle[1].y + paddle[1].h > screensize[1])
		paddle[1].y = screensize[1] - paddle[1].h;
	if (paddle[1].y < 0)
		paddle[1].y = 0;
}

static void move_paddle(int d) {

	// if the down arrow is pressed move paddle down
	if (d == 0) {

		if (paddle[0].y >= 192 - paddle[0].h) {

			paddle[0].y = 192 - paddle[0].h;

		}
		else {

			paddle[0].y += 5;
		}
	}

	// if the up arrow is pressed move paddle up
	if (d == 1) {

		if (paddle[0].y <= 0) {

			paddle[0].y = 0;

		}
		else {

			paddle[0].y -= 5;
		}
	}
}

static void draw_net() {

	int netx = 256 / 2;
	int nety = 0;
	int netw = 5;
	int neth = 15;

	//draw the net
	int i, r;

	for (i = 0; i < 15; i++) {

		glBoxFilled(netx, nety, netx + netw, nety + neth, 0xffffffff);

		nety = nety + 30;
	}
}

static void draw_ball() {

	glBoxFilled(ball.x, ball.y, ball.x + ball.w, ball.y + ball.h, 0xffffffff);

}

glImage title[1];
glImage num[NUM_NUM_IMAGES];
glImage over[OVER_NUM_IMAGES];
static void draw_paddle() {

	int i;

	for (i = 0; i < 2; i++) {

		int srcx = paddle[i].x;
		int srcy = paddle[i].y;
		int srcw = paddle[i].w;
		int srch = paddle[i].h;

		glBoxFilled(srcx, srcy, srcx + srcw, srcy + srch, 0xffffffff);
	}
}
static void draw_score() {

	glSprite(0, 0, GL_FLIP_NONE, &num[score[0]]);
	glSprite(screensize[0] - 64, 0, GL_FLIP_NONE, &num[score[1]]);

}
void gameloop() {
	//paddle ai movement
	move_paddle_ai();

	//* Move the balls for the next frame. 
	move_ball();
}
void renderloop() {

	//draw net
	draw_net();

	//draw paddles
	draw_paddle();

	//* Put the ball on the screen.
	draw_ball();
	draw_score();
}

void initimages() {
	glLoadTileSet(title,            // pointer to glImage array
		256,                // sprite width
		128,                // sprite height
		256,                // bitmap image width
		128,                // bitmap image height
		GL_RGB16,        // texture type for glTexImage2D() in videoGL.h 16 colors
		TEXTURE_SIZE_256,    // sizeX for glTexImage2D() in videoGL.h
		TEXTURE_SIZE_128,    // sizeY for glTexImage2D() in videoGL.h
						 // Set texture params setting color 0 as transparent
		GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
		256,                    // Length of the palette to use (256 colors)
		(u16*)titlePal,    // Load our 16 color shuttle palette
		(u8*)titleBitmap  // image data generated by GRIT
	);
	glLoadSpriteSet(num,					// pointer to glImage array
		NUM_NUM_IMAGES, 		// Texture packer auto-generated #define
		num_texcoords,		// Texture packer auto-generated array
		GL_RGB256,				// texture type for glTexImage2D() in videoGL.h 
		TEXTURE_SIZE_1024,		// sizeX for glTexImage2D() in videoGL.h
		TEXTURE_SIZE_64,		// sizeY for glTexImage2D() in videoGL.h
		GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
		256,					// Length of the palette to use (256 colors)
		(u16*)numPal,		// Zero and Enemies share the same palette
		(u8*)numBitmap	 	// image data generated by GRIT
	);
	glLoadSpriteSet(over,					// pointer to glImage array
		OVER_NUM_IMAGES, 		// Texture packer auto-generated #define
		over_texcoords,		// Texture packer auto-generated array
		GL_RGB256,				// texture type for glTexImage2D() in videoGL.h 
		TEXTURE_SIZE_256,		// sizeX for glTexImage2D() in videoGL.h
		TEXTURE_SIZE_128,		// sizeY for glTexImage2D() in videoGL.h
		GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
		256,					// Length of the palette to use (256 colors)
		(u16*)overPal,		// Zero and Enemies share the same palette
		(u8*)overBitmap	 	// image data generated by GRIT
	);
}
int main(void)
{
    int state = 0;
    init_game();
    videoSetMode(MODE_5_3D);

	consoleDemoInit();
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankB(VRAM_B_TEXTURE);
    vramSetBankC(VRAM_C_TEXTURE);
	vramSetBankE(VRAM_E_TEX_PALETTE);

    // Initialize GL2D
    glScreen2D();


	initimages();

    int TextureSize = titleBitmapLen;


    int frame = 0;
	int pause = 0;
	int winner = 0;
	while (1)
	{

		// set up GL2D for 2d mode
		glBegin2D();
		switch (state) {
		case 0:
			glSprite(0, 0, GL_FLIP_NONE, title);
			break;
		case 1:
			if (pause != 1)
				gameloop();
			renderloop();
			if (score[0] > 9) {
				state = 2;
				winner = 0;
			}
			if (score[1] > 9) {
				state = 2;
				winner = 1;
			}
			break;

		case 2:
			glSprite(28, 50, GL_FLIP_NONE, &over[winner]);
			break;
		}
		// end 2D rendering mode
		glEnd2D();

		glFlush(0);
		swiWaitForVBlank();
		scanKeys();
		if (state == 1) {
			if (pause == 0) {
				if (keysHeld() & KEY_UP) {
					move_paddle(1);
				}
				if (keysHeld() & KEY_DOWN) {
					move_paddle(0);
				}
			}
			if (keysDown() & KEY_START) {
				if (pause == 1)
					pause = 0;
				else
					pause = 1;
			}
		}
		if (state == 0 || state == 2) {
			if (keysDown() & KEY_START) {
				state = 1;
				score[0] = 0;
				score[1] = 0;
			}
		}
		

	}
}