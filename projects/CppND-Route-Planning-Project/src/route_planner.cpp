#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    RouteModel::Node start_node_loc = m_Model.FindClosestNode(start_x, start_y);
    RouteModel::Node end_node_loc = m_Model.FindClosestNode(end_x, end_y);

    this -> start_node = &start_node_loc;
    this -> end_node = &end_node_loc;
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
   return node -> distance(*(this -> end_node));
}

// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node ->FindNeighbors();
    for(RouteModel::Node *neighbour_ptr: current_node ->neighbors) {
        neighbour_ptr -> h_value = this ->CalculateHValue(neighbour_ptr);
        neighbour_ptr -> g_value = (current_node -> g_value) + (current_node -> distance(*neighbour_ptr));
        neighbour_ptr -> visited = true;
        neighbour_ptr ->parent = current_node;
        this ->open_list.push_back(neighbour_ptr);
    }
}

// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.
bool compare(RouteModel::Node const *this_node, RouteModel::Node const *that_node) {
    float this_fvalue = (this_node -> g_value) + (this_node -> h_value);
    float that_fvalue = (that_node -> g_value) + (that_node -> h_value);
    return (this_fvalue < that_fvalue);
}

RouteModel::Node *RoutePlanner::NextNode() {
    std::sort(this -> open_list.begin(), this -> open_list.end(), compare);
    RouteModel::Node *nextNodePtr = *(this -> open_list.begin());
    this -> open_list.pop_back();
    return nextNodePtr;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}