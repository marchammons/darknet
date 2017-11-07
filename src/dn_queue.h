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
	float box_red;
	float box_green;
	float box_blue;
} dn_object_t;

void dn_push(dn_object_t *o);

dn_object_t *dn_pop();

dn_object_t * create_obj(char *name,
	float prob,
	int x_size,
	int y_size,
	float x_box,
	float y_box,
	float w_box,
	float h_box,
	float box_red,
	float box_green,
	float box_blue);

void destroy_obj(dn_object_t *o);

int dn_queue_empty();

#ifdef __cplusplus
}
#endif


