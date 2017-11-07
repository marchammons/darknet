
#include <dn_queue.h>
#include <malloc.h>
#include <queue>
#include <mutex>

using namespace std;
queue <dn_object_t *> _dn_queue;
mutex _dn_mutex;

void dn_push(dn_object_t *o) {
	_dn_mutex.lock();
	_dn_queue.push(o);
	_dn_mutex.unlock();
}

dn_object_t* dn_pop() {
	dn_object_t *o = NULL;
	_dn_mutex.lock();
	if (!_dn_queue.empty()) {
		o = _dn_queue.front();
		_dn_queue.pop();
	}
	_dn_mutex.unlock();
	return o;
}

int dn_queue_empty() {
	return _dn_queue.empty();
}

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
		float box_blue) {

	dn_object_t *o = NULL;
	o = (dn_object_t*) malloc(sizeof(dn_object_t));

	strcpy(o->name,name);
	o->prob = prob;
	o->x_size = x_size;
	o->y_size = y_size;
	o->x_box = x_box;
	o->y_box = y_box;
	o->w_box = w_box;
	o->h_box = h_box;
	o->box_red = box_red;
	o->box_green = box_green;
	o->box_blue = box_blue;

	return(o);
}

void destroy_obj(dn_object_t *o) {
	if(o) free(o);
	return;
}
