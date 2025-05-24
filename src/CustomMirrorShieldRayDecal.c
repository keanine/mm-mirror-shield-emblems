#include "ultra64.h"
#include "global.h"
#include "texture_data.h"

Vtx CustomMirrorShieldRayDecal_CustomMirrorShieldRayDecal_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-1195, -804, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1195, -804, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1195, 905, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1195, 905, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {851, -804, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {851, -804, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {851, 905, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {851, 905, 0}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx CustomMirrorShieldRayDecal_CustomMirrorShieldRayDecal_mesh_layer_Opaque_vtx_0[11] = {
	{{ {-172, 50, 0}, 0, {1008, 1008}, {172, 172, 172, 172} }},
	{{ {88, -804, 0}, 0, {1952, 747}, {172, 172, 172, 172} }},
	{{ {-433, -804, 0}, 0, {1952, 1269}, {172, 172, 172, 172} }},
	{{ {640, -507, 0}, 0, {1624, 195}, {172, 172, 172, 172} }},
	{{ {851, 50, 0}, 0, {1008, -16}, {172, 172, 172, 172} }},
	{{ {640, 608, 0}, 0, {392, 195}, {172, 172, 172, 172} }},
	{{ {88, 905, 0}, 0, {63, 747}, {172, 172, 172, 172} }},
	{{ {-433, 905, 0}, 0, {63, 1269}, {172, 172, 172, 172} }},
	{{ {-985, 608, 0}, 0, {392, 1822}, {172, 172, 172, 172} }},
	{{ {-1195, 50, 0}, 0, {1008, 2032}, {172, 172, 172, 172} }},
	{{ {-985, -507, 0}, 0, {1624, 1822}, {172, 172, 172, 172} }},
};

Gfx CustomMirrorShieldRayDecal_CustomMirrorShieldRayDecal_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(CustomMirrorShieldRayDecal_CustomMirrorShieldRayDecal_mesh_layer_Opaque_vtx_0 + 0, 11, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(0, 4, 3, 0, 5, 4, 0, 0),
	gsSP2Triangles(6, 5, 0, 0, 7, 6, 0, 0),
	gsSP2Triangles(7, 0, 8, 0, 0, 9, 8, 0),
	gsSP2Triangles(10, 9, 0, 0, 10, 0, 2, 0),
	gsSPEndDisplayList(),
};

Gfx mat_CustomMirrorShieldRayDecal_f3dlite_material_002[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 3, G_AC_NONE | G_ZS_PIXEL),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 1, gCustomMirrorShieldRayTexture_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 2047, 256),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_MIRROR, 6, 0, G_TX_CLAMP | G_TX_MIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 508, 508),
	gsSPEndDisplayList(),
};

Gfx CustomMirrorShieldRayDecal[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(CustomMirrorShieldRayDecal_CustomMirrorShieldRayDecal_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_CustomMirrorShieldRayDecal_f3dlite_material_002),
	gsSPDisplayList(CustomMirrorShieldRayDecal_CustomMirrorShieldRayDecal_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

