#pragma once
#include "box.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char name[64];
	float prob;
	int x_size;
	int y_size;
	float x_box;
	float y_box;
	float w_box;
	float h_box;
} dn_object_t;

int dn_push(dn_object_t *o);

dn_object_t *dn_pop();

#ifdef __cplusplus
}
#endif


