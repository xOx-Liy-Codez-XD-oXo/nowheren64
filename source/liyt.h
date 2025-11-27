mat4_t genMtxPosRotScaleZyx(float posx, float posy, float posz, 
                            float rotx, float roty, float rotz, 
                            float sclx, float scly, float sclz) {
	mat4_t model, mrx, mry, mrz;
	mrx = m4_rotation_x(rotx);
	mry = m4_rotation_y(roty);
	mrz = m4_rotation_z(rotz);
	model = m4_scaling((vec3_t){sclx, scly, sclz});
	
	mry = m4_mul_3x3(mrz, mry);
	mrx = m4_mul_3x3(mry, mrx);
	model = m4_mul_3x3(mrx, model);
	model.m[3][0] += posx;
	model.m[3][1] += posy;
	model.m[3][2] += posz;
	return model;
}