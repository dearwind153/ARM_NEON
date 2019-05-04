#include <stdio.h>

#include <arm_neon.h>

void add3 (uint8x16_t *data) {
    /* Set each sixteen values of the vector to 3.
     *
     * Remark: a 'q' suffix to intrinsics indicates
     * the instruction run for 128 bits registers.
     */
    uint8x16_t three = vmovq_n_u8 (3);

    /* Add 3 to the value given in argument. */
    *data = vaddq_u8 (*data, three);
}

void print_uint8 (uint8x16_t data, char* name) {
    int i;
    static uint8_t p[16];

    vst1q_u8 (p, data);

    printf ("%s = ", name);
    for (i = 0; i < 16; i++) {
	printf ("%02x ", p[i]);
    }
    printf ("\n");
}

void print_uint8_second_ver (uint8x8x2_t data, char* name) {
    int i;
    static uint8_t p[16];

    vst1_u8 (p, data.val[0]);
	vst1_u8 (p+8, data.val[1]);

    printf ("%s = ", name);
    for (i = 0; i < 16; i++) {
	printf ("%02x ", p[i]);
    }
    printf ("\n");
}

void print_uint32 (uint32x4_t data, char* name) {
    int i;
    static uint32_t p[4];

    vst1q_u32 (p, data);

    printf ("%s = ", name);
    for (i = 0; i < 4; i++) {
	printf ("%08x ", p[i]);
    }
    printf ("\n");
}

void print_uint32_third_ver (uint32x2_t data, char* name) {
    int i;
    static uint32_t p[2];

    vst1_u32 (p, data);

    printf ("%s = ", name);
    for (i = 0; i < 2; i++) {
	printf ("%08x ", p[i]);
    }
    printf ("\n");
}

void print_uint32_second_ver (uint32x4x2_t data, char* name) {
    int i;
    static uint32_t p[8];

    vst1q_u32 (p, data.val[0]);
	vst1q_u32 (p+4, data.val[1]);

    printf ("%s = ", name);
    for (i = 0; i < 8; i++) {
	printf ("%08x ", p[i]);
    }
    printf ("\n");
}

int main () {
    /* Create custom arbitrary data. */
    const uint8_t uint8_data[] = { 1, 2, 3, 4, 5, 6, 7, 8,
				   9, 10, 11, 12, 13, 14, 15, 16 };

    /* Create the vector with our data. */
    uint8x16_t data;

    /* Load our custom data into the vector register. */
    data = vld1q_u8 (uint8_data);

    print_uint8 (data, "data");
    
    /* Call of the add3 function. */
    add3(&data);

    print_uint8 (data, "data (new)");
	
	/*float a[16] = {12.78, 258.35, -10.69, 0, 
				  200.89, 255.0, -1009.87, 3.936,
				  -9.8, 300.02, 99.0, 44.88,
				  0.0, 3.98, -22.7, 255.6};*/
#if 1
	float a[16] = {1, 2,  3, 4, 
				   5,  6,  7, 8,
				   9, 10, 11, 12,
				  13, 14, 15, 16};			  
	
	float32x4_t vec_f_4  = vld1q_f32(a);
	
	//uint32x4_t  vec_u_32 = vcvtq_n_u32_f32(vec_f_4, 8);
	uint32x4_t  vec_u_32 = vcvtq_u32_f32(vec_f_4);
	
	uint32x4_t  vec_boundary  = vmovq_n_u32(255);
	uint32x4_t  vec_result_0 = vminq_u32(vec_u_32, vec_boundary);
	uint32x4_t  vec_result_0_no_shift = vminq_u32(vec_u_32, vec_boundary);
	print_uint32(vec_result_0_no_shift, "vec_result_0");
	vec_f_4  = vld1q_f32(a+4);
	vec_u_32 = vcvtq_u32_f32(vec_f_4);
	uint32x4_t  vec_result_1_no_shift = vminq_u32(vec_u_32, vec_boundary);
	print_uint32(vec_result_1_no_shift, "vec_result_1");
	uint32x4_t  vec_result_1 = vshlq_n_u32(vminq_u32(vec_u_32, vec_boundary), 8);
	
	//uint32x4x2_t vec_result_0_1_reverse = vtrnq_u32(vec_result_0_no_shift, vec_result_1_no_shift);
	//print_uint32_second_ver(vec_result_0_1_reverse, "vec_result_0_1_reverse");
	
	
	vec_f_4  = vld1q_f32(a+8);
	vec_u_32 = vcvtq_u32_f32(vec_f_4);
	uint32x4_t  vec_result_2_no_shift = vminq_u32(vec_u_32, vec_boundary);
	uint32x4_t  vec_result_2 = vshlq_n_u32(vminq_u32(vec_u_32, vec_boundary),16);
	print_uint32(vec_result_2_no_shift, "vec_result_2");
	vec_f_4  = vld1q_f32(a+12);
	vec_u_32 = vcvtq_u32_f32(vec_f_4);
	uint32x4_t  vec_result_3_no_shift = vminq_u32(vec_u_32, vec_boundary);
	uint32x4_t  vec_result_3 = vshlq_n_u32(vminq_u32(vec_u_32, vec_boundary), 24);
	print_uint32(vec_result_3_no_shift, "vec_result_3");
	
	uint32x4_t vec_result = vaddq_u32(vaddq_u32(vec_result_0, vec_result_1), vaddq_u32(vec_result_2, vec_result_3)); 
	//print_uint32(vec_result, "vec_result");
	
	//uint32x4x2_t vec_result_2_3_reverse = vtrnq_u32(vec_result_2_no_shift, vec_result_3_no_shift);
	//print_uint32_second_ver(vec_result_2_3_reverse, "vec_result_2_3_reverse");
	
	//uint32x4_t vec_result_second = vaddq_u32(vaddq_u32(vec_result_0_1_reverse.val[0], vshlq_n_u32(vec_result_2_3_reverse.val[0], 8)), vaddq_u32(vshlq_n_u32(vec_result_0_1_reverse.val[1], 16), vshlq_n_u32(vec_result_2_3_reverse.val[0], 24))); 
	//print_uint32(vec_result_second, "vec_result_second");
	
	
	//print_uint32(vrev64q_u32(vec_result), "Reverse vec_result");
	
	uint8x16_t final_result = vreinterpretq_u8_u32(vec_result);
	print_uint8(final_result, "final_result");
	
	uint8x8x2_t two_part = { vget_low_u8(final_result), vget_high_u8(final_result) };
	//uint8_t data8[16];
	//vst1q_u8(data8, final_result);
	//uint8x8x2_t two_part = vld2_u8(data8);
	
	two_part = vzip_u8(two_part.val[0], two_part.val[1]);
	two_part = vzip_u8(two_part.val[0], two_part.val[1]);
	//two_part = vzip_u8(two_part.val[0], two_part.val[1]);
	
	uint8x16_t final_result_new = vcombine_u8(two_part.val[0], two_part.val[1]);
	
	print_uint8(final_result_new, "final_result_new");
	
	
	
	//uint8x8_t _part1_ = vget_high_u8(final_result);
	//uint8x8_t _part2_ = vget_low_u8(final_result);
	
	//uint8x8x2_t reverse_result = vtrn_u8(_part1_, _part2_);
	//reverse_result = vtrn_u8(reverse_result.val[0], reverse_result.val[1]);
	//reverse_result = vtrn_u8(reverse_result.val[0], reverse_result.val[1]);

    //print_uint8_second_ver(reverse_result, "reverse_result");
	
	
	
	
	/*uint8_t data_5[8] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
	uint8_t data_6[8] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17};
	
	uint8x8_t data_5_8x8 = vld1_u8(data_5);
	uint8x8_t data_6_8x8 = vld1_u8(data_6);
	
	uint8x8x2_t data_5_6_result = vzip_u8(data_5_8x8, data_6_8x8);
	data_5_6_result = vzip_u8(data_5_6_result.val[0], data_5_6_result.val[1]);
	data_5_6_result = vzip_u8(data_5_6_result.val[0], data_5_6_result.val[1]);
	print_uint8_second_ver(data_5_6_result, "data_5_6_result");*/

#endif
	
#if 0
	float data_7[] = {0x00,0x01,0x02,0x03,
						 0x04,0x05,0x06,0x07,
						 0x10,0x11,0x12,0x13,
						 0x14,0x15,0x16,0x17,
						 0x20,0x21,0x22,0x23,
						 0x24,0x25,0x26,0x27,
						 0x30,0x31,0x32,0x33,
						 0x34,0x35,0x36,0x37};
						 
	float32x4_t vec_B_0, vec_B_1, vec_B_2, vec_B_3;
	float32x4_t vec_A    = vmovq_n_f32(1);
	float32x4_t vec_bias = vmovq_n_f32(0);
	uint32x4_t  vec_boundary  = vmovq_n_u32(255);
	uint32x4_t  vec_result_0, vec_result_1, vec_result_2, vec_result_3;
	uint32x2_t  vec_result_0_get, vec_result_1_get, vec_result_2_get, vec_result_3_get, vec_result_4, vec_result_5, vec_result;
	
	vec_B_0 = vld1q_f32(data_7);
	vec_B_1 = vld1q_f32(data_7+4);
	vec_B_2 = vld1q_f32(data_7+8);
	vec_B_3 = vld1q_f32(data_7+12);
	
	vec_result_0 = vminq_u32(vcvtq_u32_f32(vmlaq_f32(vec_bias, vec_A, vec_B_0)), vec_boundary);
	print_uint32(vec_result_0, "vec_result_0");
	vec_result_0_get = vget_low_u32(vec_result_0);
	print_uint32_third_ver(vec_result_0_get, "vec_result_0_get");
	
	vec_result_1 = vminq_u32(vcvtq_u32_f32(vmlaq_f32(vec_bias, vec_A, vec_B_1)), vec_boundary);
	print_uint32(vec_result_1, "vec_result_1");
	vec_result_1_get = vget_low_u32(vec_result_1);
	print_uint32_third_ver(vec_result_1_get, "vec_result_1_get");
	
	vec_result_2 = vminq_u32(vcvtq_u32_f32(vmlaq_f32(vec_bias, vec_A, vec_B_2)), vec_boundary);
	print_uint32(vec_result_2, "vec_result_2");
	vec_result_2_get = vget_low_u32(vec_result_2);
	print_uint32_third_ver(vec_result_2_get, "vec_result_2_get");
	
	vec_result_3 = vminq_u32(vcvtq_u32_f32(vmlaq_f32(vec_bias, vec_A, vec_B_3)), vec_boundary);
	print_uint32(vec_result_3, "vec_result_3");
	vec_result_3_get = vget_low_u32(vec_result_3);
	print_uint32_third_ver(vec_result_3_get, "vec_result_3_get");
	
	uint32x4_t vec_result_0_1_combine = vcombine_u32(vec_result_0_get, vec_result_1_get);
	uint32x4_t vec_result_2_3_combine = vcombine_u32(vec_result_2_get, vec_result_3_get);
	
	print_uint32(vec_result_0_1_combine,"vec_result_0_1_combine");
	print_uint32(vec_result_2_3_combine,"vec_result_2_3_combine");
	
	vec_result_4 = vget_low_u32(vec_result_0_1_combine);
	vec_result_5 = vget_low_u32(vec_result_2_3_combine);
	
	print_uint32_third_ver(vec_result_4, "vec_result_4");
	print_uint32_third_ver(vec_result_5, "vec_result_5");
	
	uint32x4_t vec_result_0_1_2_3_combine = vcombine_u32(vec_result_4, vec_result_5);
	
	print_uint32(vec_result_0_1_2_3_combine ,"vec_result_0_1_2_3_combine");
	
	uint8x16_t new_final_result = vreinterpretq_u8_u32(vec_result_0_1_2_3_combine);
	
	print_uint8(new_final_result, "new_final_result");
	//print_uint32(vec_result, "float32 to uint32");

#endif
	
    return 0;
}
