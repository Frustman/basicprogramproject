#include <CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")

#include <stdio.h>
#include <cmath>

#define M_PI 3.14159265358979323846

BlockID B_quartz = createBlock(BLOCK_NETHER_QUARTZ);
BlockID B_bone = createBlock(BLOCK_BONE);
BlockID B_glowstone = createBlock(BLOCK_GLOWSTONE);
BlockID B_WhiteGlass = createBlock(BLOCK_STAINED_GLASS);
BricksID B_brick = createBricks(BRICKS_STONE);
BlockID B_water = createWater(true);


void circle(int radius, BlockID block, int x, int y, int z) {
	for (int deg = 0; deg < 360; deg += 5) {
		locateBlock(block, x + radius * sin(M_PI / 180 * deg), y, z + radius * cos(M_PI / 180 * deg));
	}
}

void hcyl(BlockID block, int radius, int height, int x, int y, int z) {
	for (int h = 0; h < height; h++) {
		for (int deg = 0; deg < 360; deg += 5) {
			locateBlock(block, x + radius * sin(M_PI / 180 * deg), y + h, z + radius * cos(M_PI / 180 * deg));
		}
	}
}

void cyl(BlockID block, int radius, int height, int x, int y, int z) {
	for (int h = 0; h < height; h++) {
		for (int r = radius; r >= 0; r--) {
			for (int deg = 0; deg < 360; deg += 5) {
				locateBlock(block, x + r * sin(M_PI / 180 * deg), y + h, z + r * cos(M_PI / 180 * deg));
			}
		}
	}
}

void Brick_hcyl(BricksID brick, int radius, int height, int x, int y, int z) {
	for (int h = 0; h < height; h++) {
		for (int deg = 0; deg < 360; deg += 5) {
			locateBricks(brick, x + radius * sin(M_PI / 180 * deg), y + h, z + radius * cos(M_PI / 180 * deg));
		}
	}
}

void slab_hcyl(SlabID slab, int radius, int height, int x, int y, int z) {
	for (int h = 0; h < height; h++) {
		for (int deg = 0; deg < 360; deg += 5) {
			locateSlab(slab, x + radius * sin(M_PI / 180 * deg), y + h, z + radius * cos(M_PI / 180 * deg));
		}
	}
}

SlabID slab_height(SlabType type, SlabSize size) {
	SlabID slab = createSlab(type, size);
	return slab;
}



void walls(BlockID block, int x1, int y1, int z1, int x2, int y2, int z2) {
	int x = (x1 < x2) ? x1 : x2, y = (y1 < y2) ? y1 : y2, z = (z1 < z2) ? z1 : z2;
	for (int i = 0; i < ((y1 - y2 == 0) ? 1 : abs(y1 - y2)); i++) {
		for (int j = 0; j <= ((x1 - x2 == 0) ? 1 : abs(x1 - x2)); j++) {
			locateBlock(block, x + j, y + i, z1);
			locateBlock(block, x + j, y + i, z2);
		}
		for (int k = 0; k <= ((z1 - z2 == 0) ? 1 : abs(z1 - z2)); k++) {
			locateBlock(block, x1, y + i, z + k);
			locateBlock(block, x2, y + i, z + k);
		}
	}
}

void slab_walls(SlabID slab, int x1, int y1, int z1, int x2, int y2, int z2) {
	int x = (x1 < x2) ? x1 : x2, y = (y1 < y2) ? y1 : y2, z = (z1 < z2) ? z1 : z2;
	for (int i = 0; i < ((y1 - y2 == 0) ? 1 : abs(y1 - y2)); i++) {
		for (int j = 0; j <= ((x1 - x2 == 0) ? 1 : abs(x1 - x2)); j++) {
			locateSlab(slab, x + j, y + i, z1);
			locateSlab(slab, x + j, y + i, z2);
		}
		for (int k = 0; k <= ((z1 - z2 == 0) ? 1 : abs(z1 - z2)); k++) {
			locateSlab(slab, x1, y + i, z + k);
			locateSlab(slab, x2, y + i, z + k);
		}
	}
}

void set(BlockID block, int x1, int y1, int z1, int x2, int y2, int z2) {
	int x = (x1 < x2) ? x1 : x2, y = (y1 < y2) ? y1 : y2, z = (z1 < z2) ? z1 : z2;
	for (int i = 0; i < ((y1 - y2 == 0) ? 1 : abs(y1 - y2)); i++) {
		for (int j = 0; j <= ((x1 - x2 == 0) ? 1 : abs(x1 - x2)); j++) {
			for (int k = 0; k <= ((z1 - z2 == 0) ? 1 : abs(z1 - z2)); k++) {
				locateBlock(block, x + j, y + i , z + k);
			}
		}
	}
}

void set_slab(SlabID slab, int x1, int y1, int z1, int x2, int y2, int z2) {
	int x = (x1 < x2) ? x1 : x2, y = (y1 < y2) ? y1 : y2, z = (z1 < z2) ? z1 : z2;
	for (int i = 0; i < ((y1 - y2 == 0) ? 1 : abs(y1 - y2)); i++) {
		for (int j = 0; j <= ((x1 - x2 == 0) ? 1 : abs(x1 - x2)); j++) {
			for (int k = 0; k <= ((z1 - z2 == 0) ? 1 : abs(z1 - z2)); k++) {
				locateSlab(slab, x + j, y + i, z + k);
			}
		}
	}
}

void column(int x, int y, int z, int dx, int dy, int dz) {
	int radius = ((dx > dz) ? dx : dz) / 15 - 1;
	int height = dy - ((dx < dz) ? dx : dz) / 5 - 1;

	hcyl(B_quartz, radius, height, x, y, z);

	if (radius <= 2) {
		slab_hcyl(slab_height(SLAB_STONE_BRICK, SLAB_LOWER), radius + 1, 1, x, y, z   );
	}

	if (radius > 2) {
		hcyl(B_brick, radius + 1, 1, x, y, z);
		slab_hcyl(slab_height(SLAB_STONE_BRICK, SLAB_LOWER), radius + 2, 1, x, y, z);
		slab_hcyl(slab_height(SLAB_STONE_BRICK, SLAB_LOWER), radius + 1, 1, x, y + 1, z);
	}

	if (radius <= 2) {
		slab_hcyl(slab_height(SLAB_STONE_BRICK, SLAB_UPPER), radius + 1, 1, x, y + height, z);
	}

	if (radius > 2) {
		Brick_hcyl(B_brick, radius + 1, 1, x, y + height, z);
		slab_hcyl(slab_height(SLAB_STONE_BRICK, SLAB_UPPER), radius + 2, 1, x, y + height, z);
		slab_hcyl(slab_height(SLAB_STONE_BRICK, SLAB_UPPER), radius + 1, 1, x, y + height - 1, z);
	}

	for (int i = 0; i < height + 1; i++) {
		if (i % 3 == 0) {
			circle(radius, B_WhiteGlass, x, y + i, z);
		}
		if (i % 4 == 0) {
			circle(radius, B_glowstone, x, y + i, z);
		}
		if (i % 5 == 0) {
			circle(radius, B_WhiteGlass, x, y + i, z);
		}
	}
}

int main() {
	int x1 = 0, y1 = 0, z1 = 0, x2= 0, y2 = 0, z2 = 0;
	printf("x1, y1, z1, x2, y2, z2를 순서대로 입력해주세요.\n");
	scanf_s("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
	int x_start = (x1 < x2) ? x1 : x2, y_start = (y1 < y2) ? y1 : y2, z_start = (z1 < z2) ? z1 : z2;
	int x_end = (x1 > x2) ? x1 : x2, y_end = (y1 > y2) ? y1 : y2, z_end = (z1 > z2) ? z1 : z2;
	int dx = abs(x1 - x2), dy = abs(y1 - y2), dz = abs(z1 - z2);
	int height = dy - ((dx < dz) ? dx : dz) / 5;

	int radius = ((dx > dz) ? dx : dz) / 15;

	slab_walls(slab_height(SLAB_QUARTZ, SLAB_LOWER), x_start, y_start, z_start, x_end, y_start, z_end);
	set(B_quartz, x_start + 1, y_start, z_start + 1, x_end - 1, y_start, z_end - 1);

	for (int i = 0; i < (int)((dx < dz) ? dx : dz) / 2 - 5 - 2 * radius; i++) {
		if (i % 4 == 0) {
			walls(B_WhiteGlass, x_start + 5 + 2 * radius + i, y_start, z_start + 5 + 2 * radius + i, x_end - 5 - 2 * radius - i, y_start, z_end - 5 - 2 * radius - i);
		}
		else if (i % 2 == 0) {
			walls(B_glowstone, x_start + 5 + 2 * radius + i, y_start, z_start + 5 + 2 * radius + i, x_end - 5 - 2 * radius - i, y_start, z_end - 5 - 2 * radius - i);
		}

	}

	
	for (int i = 0; i < (int)(((dx > dz) ? dx : dz) - 2 + 2 * radius) / (4 * radius + 1); i ++) {
		if (dx > dz) {
			column(x_start + 2 + radius + i * (4 * radius + 1), y_start + 1, z_start + 2 + radius, dx, dy, dz);
			column(x_end - 2 - radius - i * (4 * radius + 1), y_start + 1, z_end - 2 - radius, dx, dy, dz);
		}
		if (dx < dz) {
			column(x_start + 2 + radius, y_start + 1, z_start + 2 + radius + i * (4 * radius + 1), dx, dy, dz);
			column(x_end - 2 - radius, y_start + 1, z_end - 2 - radius - i * (4 * radius + 1), dx, dy, dz);
		}
	}

	for (int i = 0; i < (int)(((dx < dz) ? dx : dz) - 2 + 2 * radius) / (4 * radius + 1); i ++) {
		if (dx > dz) {
			column(x_start + 2 + radius, y_start + 1, z_start + 2 + radius + i * (4 * radius + 1), dx, dy, dz);
			column(x_end - 2 - radius, y_start + 1, z_end - 2 - radius - i * (4 * radius + 1), dx, dy, dz);
		}
		if (dx < dz) {
			column(x_start + 2 + radius + i * (4 * radius + 1), y_start + 1, z_start + 2 + radius, dx, dy, dz);
			column(x_end - 2 - radius - i * (4 * radius + 1), y_start + 1, z_end - 2 - radius, dx, dy, dz);
		}
	} // 기둥들

	for (int i = 0; i < (int)((dx < dz) ? dx : dz) / 2; i++) {
		if (i % 2 == 0) {
			walls(B_WhiteGlass, x_start + i, y_start + height + (dy - height)*i / (((dx < dz) ? dx : dz) / 2), z_start + i, x_end - i, y_start + height + (dy - height)*i / (((dx < dz) ? dx : dz) / 2), z_end - i);
		}
		if (i % 2 == 1) {
			walls(B_quartz, x_start + i, y_start + height + (dy - height)*i / (((dx < dz) ? dx : dz) / 2), z_start + i, x_end - i, y_start + height + (dy - height)*i / (((dx < dz) ? dx : dz) / 2), z_end - i);
		}
	} // 천장

	hcyl(B_quartz, ((dx < dz) ? dx : dz) / 8, 2, (x_start + x_end) / 2, y_start , (z_start + z_end) / 2);
	cyl(B_quartz, ((dx < dz) ? dx : dz) / 30, ((dx < dz) ? dx : dz) / 10, (x_start + x_end) / 2, y_start, (z_start + z_end) / 2);
	cyl(B_quartz, ((dx < dz) ? dx : dz) / 20, ((dx < dz) ? dx : dz) / 15, (x_start + x_end) / 2, y_start, (z_start + z_end) / 2);

	locateWater(B_water, (x_start + x_end) / 2, y_start + ((dx < dz) ? dx : dz) / 10 + 2, (z_start + z_end) / 2);
	locateWater(B_water, (x_start + x_end) / 2 + 1, y_start + ((dx < dz) ? dx : dz) / 10 + 1, (z_start + z_end) / 2 + 1);
	locateWater(B_water, (x_start + x_end) / 2 + 1, y_start + ((dx < dz) ? dx : dz) / 10 + 1, (z_start + z_end) / 2 - 1);
	locateWater(B_water, (x_start + x_end) / 2 - 1, y_start + ((dx < dz) ? dx : dz) / 10 + 1, (z_start + z_end) / 2 + 1);
	locateWater(B_water, (x_start + x_end) / 2 - 1, y_start + ((dx < dz) ? dx : dz) / 10 + 1, (z_start + z_end) / 2 - 1);
}





