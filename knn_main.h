#ifndef KNN_MAIN_H
#define KNN_MAIN_H

#include "training_data.h"
#include "ap_int.h"

// The K_CONST value: number of nearest neighbors
#ifndef K_CONST
#define K_CONST 3
#endif

// Top function
ap_uint<4> knn_main( ap_uint<49> input );

// Given the testing instance and a (new) training instance,
// this function is expected to maintain/update an array of
// K minimum distances per training set
void update_knn( ap_uint<49> test_inst, ap_uint<49> train_inst, ap_uint<6> min_distances[K_CONST] );

// Find the node which has the min total distance
ap_uint<4> find_min( ap_uint<6> min_distances[10][K_CONST] );

#endif
