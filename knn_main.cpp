#include "knn_main.h"
#include "ap_int.h"
#include "training_data.h"

// Top function
ap_uint<4> knn_main(ap_uint<49> input) {
  ap_uint<6> knn_distance[10][K_CONST];

  // Initialize the knn set
  initialize_loop_1:
  for (int i = 0; i < 10; ++i) {
	initialize_loop_2:
    for (int k = 0; k < K_CONST; ++k) {
      // assume max distance is 49
      knn_distance[i][k] = 50; // initialize the array
    }
  }

  knn_for_loop_1:
  for (int i = 0; i < TRAINING_SIZE; ++i) {
	distance_calculation_and_update:
    for (int j = 0; j < 10; j++) {
      ap_uint<49> training_instance = training_data[j * TRAINING_SIZE + i];
      // Update the KNN set
      update_knn(input, training_instance, knn_distance[j]);
    }
  }

  // Find min node for distance
  ap_uint<4> result = find_min(knn_distance);
  return result;
}


// Given the test instance and a (new) training instance, this
// function maintains/updates an array of K minimum
// distances per training set.

void update_knn(ap_uint<49> test, ap_uint<49> train_data, ap_uint<6> min_knn_distance_for_node[3]) {
  // Calculate difference by bitwise XOR
  ap_uint<49> diff = test ^ train_data;

  // max distance is 50
  ap_uint<6> dist = 0;
  // Count the number of set bits
  total_dis_cal:
  for (int i = 0; i < 49; i = i + 1) {
    dist = dist + diff[i];
  }

  // check if it is the nearest neighbor
//  // when index is changing
//  int index = 0;
//  while (index < K_CONST){
//	  if (dist > min_knn_distance_for_node[index]){
//		  index ++;
//		  continue;
//	  }else {
//		  while(index > 0) {
//			  min_knn_distance_for_node[index] = min_knn_distance_for_node[index-1];
//			  index = index -1;
//		  }
//		  min_knn_distance_for_node[0] = dist;
//	  }
//  }

  // when index is 3
  if (dist <= min_knn_distance_for_node[0]){
    min_knn_distance_for_node[2] = min_knn_distance_for_node[1];
    min_knn_distance_for_node[1] = min_knn_distance_for_node[0];
    min_knn_distance_for_node[0] = dist;
  }else if (dist <= min_knn_distance_for_node[1]) { // second nearest
    min_knn_distance_for_node[2] = min_knn_distance_for_node[1];
    min_knn_distance_for_node[1] = dist;
  }else if(dist <= min_knn_distance_for_node[2]){ // third nearest
    min_knn_distance_for_node[2] = dist;
  } // else do nothing, not a neighbor

}


ap_uint<4> find_min(ap_uint<6> knn_distance[10][K_CONST]) {
  int result;
  int total_distance = 0;
  int min_total_distance = K_CONST * 1000; // initialize to be long
  cal_min_path_loop_1:
  for (int i = 0; i < 10; i++) {
	cal_min_path_loop_2:
    for (int j = 0; j < K_CONST; j++) {
      total_distance = total_distance + knn_distance[i][j];
    }

    if (total_distance < min_total_distance) {
      result = i;
      min_total_distance = total_distance; // update min distance
    }
    total_distance = 0;
  }
  return result;
}
