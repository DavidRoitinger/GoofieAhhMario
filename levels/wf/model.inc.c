
Vtx wf_dl_Cube_mesh_layer_1_vtx_cull[8] = {
	{{ {-592, -100, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-592, 100, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-592, 100, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-592, -100, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {592, -100, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {592, 100, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {592, 100, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {592, -100, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx wf_dl_Cube_mesh_layer_1_vtx_0[24] = {
	{{ {592, 100, -400}, 0, {624, 496}, {0, 127, 0, 0} }},
	{{ {-592, 100, -400}, 0, {880, 496}, {0, 127, 0, 0} }},
	{{ {-592, 100, 400}, 0, {880, 240}, {0, 127, 0, 0} }},
	{{ {592, 100, 400}, 0, {624, 240}, {0, 127, 0, 0} }},
	{{ {592, -100, 400}, 0, {368, 240}, {0, 0, 127, 0} }},
	{{ {592, 100, 400}, 0, {624, 240}, {0, 0, 127, 0} }},
	{{ {-592, 100, 400}, 0, {624, -16}, {0, 0, 127, 0} }},
	{{ {-592, -100, 400}, 0, {368, -16}, {0, 0, 127, 0} }},
	{{ {-592, -100, 400}, 0, {368, 1008}, {129, 0, 0, 0} }},
	{{ {-592, 100, 400}, 0, {624, 1008}, {129, 0, 0, 0} }},
	{{ {-592, 100, -400}, 0, {624, 752}, {129, 0, 0, 0} }},
	{{ {-592, -100, -400}, 0, {368, 752}, {129, 0, 0, 0} }},
	{{ {-592, -100, -400}, 0, {112, 496}, {0, 129, 0, 0} }},
	{{ {592, -100, -400}, 0, {368, 496}, {0, 129, 0, 0} }},
	{{ {592, -100, 400}, 0, {368, 240}, {0, 129, 0, 0} }},
	{{ {-592, -100, 400}, 0, {112, 240}, {0, 129, 0, 0} }},
	{{ {592, -100, -400}, 0, {368, 496}, {127, 0, 0, 0} }},
	{{ {592, 100, -400}, 0, {624, 496}, {127, 0, 0, 0} }},
	{{ {592, 100, 400}, 0, {624, 240}, {127, 0, 0, 0} }},
	{{ {592, -100, 400}, 0, {368, 240}, {127, 0, 0, 0} }},
	{{ {-592, -100, -400}, 0, {368, 752}, {0, 0, 129, 0} }},
	{{ {-592, 100, -400}, 0, {624, 752}, {0, 0, 129, 0} }},
	{{ {592, 100, -400}, 0, {624, 496}, {0, 0, 129, 0} }},
	{{ {592, -100, -400}, 0, {368, 496}, {0, 0, 129, 0} }},
};

Gfx wf_dl_Cube_mesh_layer_1_tri_0[] = {
	gsSPVertex(wf_dl_Cube_mesh_layer_1_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Vtx wf_dl_Plane_mesh_layer_1_vtx_cull[8] = {
	{{ {-800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx wf_dl_Plane_mesh_layer_1_vtx_0[4] = {
	{{ {-800, 0, 400}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {800, 0, 400}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {800, 0, -400}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-800, 0, -400}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx wf_dl_Plane_mesh_layer_1_tri_0[] = {
	gsSPVertex(wf_dl_Plane_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Vtx wf_dl_Plane_001_mesh_layer_1_vtx_cull[8] = {
	{{ {-800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx wf_dl_Plane_001_mesh_layer_1_vtx_0[4] = {
	{{ {-800, 0, 400}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {800, 0, 400}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {800, 0, -400}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-800, 0, -400}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx wf_dl_Plane_001_mesh_layer_1_tri_0[] = {
	gsSPVertex(wf_dl_Plane_001_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Vtx wf_dl_Plane_002_mesh_layer_1_vtx_cull[8] = {
	{{ {-800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx wf_dl_Plane_002_mesh_layer_1_vtx_0[4] = {
	{{ {-800, 0, 400}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {800, 0, 400}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {800, 0, -400}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-800, 0, -400}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx wf_dl_Plane_002_mesh_layer_1_tri_0[] = {
	gsSPVertex(wf_dl_Plane_002_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Vtx wf_dl_Plane_003_mesh_layer_1_vtx_cull[8] = {
	{{ {-800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, 400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {800, 0, -400}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx wf_dl_Plane_003_mesh_layer_1_vtx_0[4] = {
	{{ {-800, 0, 400}, 0, {-16, 1008}, {0, 127, 0, 255} }},
	{{ {800, 0, 400}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {800, 0, -400}, 0, {1008, -16}, {0, 127, 0, 255} }},
	{{ {-800, 0, -400}, 0, {-16, -16}, {0, 127, 0, 255} }},
};

Gfx wf_dl_Plane_003_mesh_layer_1_tri_0[] = {
	gsSPVertex(wf_dl_Plane_003_mesh_layer_1_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_wf_dl_f3dlite_material[] = {
    gsSPLightColor(LIGHT_1, 0xffffffff),
    gsSPLightColor(LIGHT_2, 0x7f7f7fff),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx wf_dl_Cube_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(wf_dl_Cube_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_wf_dl_f3dlite_material),
	gsSPDisplayList(wf_dl_Cube_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx wf_dl_Plane_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(wf_dl_Plane_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_wf_dl_f3dlite_material),
	gsSPDisplayList(wf_dl_Plane_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx wf_dl_Plane_001_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(wf_dl_Plane_001_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_wf_dl_f3dlite_material),
	gsSPDisplayList(wf_dl_Plane_001_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx wf_dl_Plane_002_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(wf_dl_Plane_002_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_wf_dl_f3dlite_material),
	gsSPDisplayList(wf_dl_Plane_002_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx wf_dl_Plane_003_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(wf_dl_Plane_003_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_wf_dl_f3dlite_material),
	gsSPDisplayList(wf_dl_Plane_003_mesh_layer_1_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

