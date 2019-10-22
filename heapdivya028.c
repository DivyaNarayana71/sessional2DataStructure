#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "heapdivya028.h"
#include <math.h>
#include <stdio.h>


static void _swap_(int32_t *data1, int32_t *data2) {
	int32_t temp = *data1;
	*data1 = *data2;
	*data2 = temp;
}


// static void _heapify_ (detail *data, uint32_t len, uint32_t parent) {
// 	assert (len > 0 && len < HEAP_MAX_SIZE && parent > 0 );

// 	uint32_t child = 2 * parent;

// 	while (child <= len) {
// 		if (child + 1 <= len) {
// 			if (data[child+1]->time > data[child]->time){
// 				++child;
// 			}
// 		}
// 		if (data[parent]->time >= data[child]->time) {
// 			break;
// 		}
// 		_swap_(&data[parent]->time, &data[child]->time);
// 		parent = child;
// 		child = 2 * parent;
// 	}
// }


 //if detail struct is used then construct heap based on time. funtion above commented
static void _heapify_ (int32_t data[], uint32_t len, uint32_t parent) {
	assert (len > 0 && len < HEAP_MAX_SIZE && parent > 0 );

	uint32_t child = 2 * parent;

	while (child <= len) {
		if (child + 1 <= len) {
			if (data[child+1] > data[child]){
				++child;
			}
		}
		if (data[parent] >= data[child]) {
			break;
		}
		_swap_(&data[parent], &data[child]);
		parent = child;
		child = 2 * parent;
	}
}

static void _test_heap_(int32_t data[], uint32_t len) {

	for (uint32_t child = len; child > 1; --child) {
		assert(data[child] <= data[child/2]);
	}

}

Heap*	heap_test(Heap *heap)
{
	_test_heap_(heap->data, heap->size);
}

// Heap 	heap_new(deatil *data, uint32_t len) {
// 	assert (len > 0 && len < HEAP_MAX_SIZE);

// 	Heap heap;
// 	uint32_t idx = len/2;
// 	for (idx = len/2; idx > 0; --idx) {
// 		_heapify_(&data, len, idx);
// 	}
// 	heap.size = len;
// 	memcpy(heap.data, &data, (len+1) * sizeof(int32_t));
// 	_test_heap_(heap.data, heap.size);

// 	return heap;
// }

 //if detail struct is used then construct heap based on time. funtion above commented
Heap 	heap_new(int32_t data[], uint32_t len) {
	assert (len > 0 && len < HEAP_MAX_SIZE);

	Heap heap;
	uint32_t idx = len/2;
	for (idx = len/2; idx > 0; --idx) {
		_heapify_(data, len, idx);
	}
	heap.size = len;
	memcpy(heap.data, data, (len+1) * sizeof(int32_t));
	_test_heap_(heap.data, heap.size);

	return heap;
}

Heap*	heap_sort(Heap *heap) {
	assert (heap->size > 0 && heap->size < HEAP_MAX_SIZE);

	uint32_t idx = heap->size;

	for (idx = heap->size; idx > 1; idx--) {
		_swap_(&heap->data[idx], &heap->data[1]);
		_heapify_(heap->data, idx-1, 1);
	}
	return heap;
}


Heap*	heap_insert(Heap *heap, int32_t key)
{
	assert (heap->size > 0 && heap->size+1 < HEAP_MAX_SIZE);

	++heap->size;
	uint32_t parent = heap->size/2;
	uint32_t loc = heap->size;

	while ( loc > 1 && heap->data[parent] < key) {
		heap->data[loc] = heap->data[parent];
		loc = parent;
		parent = parent/2;
	}
	heap->data[loc] = key;
	return heap;

}

int32_t		heap_get_max(Heap *heap)
{
	assert (heap->size > 0 && heap->size < HEAP_MAX_SIZE);
	return heap->data[1];

}

int32_t		heap_extract_max(Heap *heap)
{
	assert (heap->size > 0 && heap->size < HEAP_MAX_SIZE);

	int32_t max = heap->data[1];	
	_swap_(&heap->data[1], &heap->data[heap->size]);
	--heap->size;
	_heapify_(heap->data, heap->size, 1);

	return max;
}

uint32_t	heap_size(Heap *heap)
{
	assert (heap->size > 0 && heap->size < HEAP_MAX_SIZE);
	return heap->size;
}

//function for level ordering this will print heap timestamp in ascending order
void printLevelbyLevel(Heap *heap)
{
	assert (heap->size > 0 && heap->size < HEAP_MAX_SIZE);
	// int height = ceil(log2(heap->size + 1)) - 1;
	for(int i=0; i<=heap->size+1; i++)
	{
		printf("%d,", heap->data[i]);
	}
}