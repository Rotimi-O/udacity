#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y) : m_Model(model)
{
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    RouteModel::Node *start_node_loc = &m_Model.FindClosestNode(start_x, start_y);
    RouteModel::Node *end_node_loc = &m_Model.FindClosestNode(end_x, end_y);

    this->start_node = start_node_loc;
    this->start_node->parent = nullptr;
    this->end_node = end_node_loc;
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node)
{
    float distance = node->distance(*(this->end_node));
    return distance;
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node)
{
    current_node->FindNeighbors();
    for (RouteModel::Node *neighbour_ptr : current_node->neighbors)
    {
        if (neighbour_ptr->visited == false)
        {
            neighbour_ptr->h_value = this->CalculateHValue(neighbour_ptr);
            neighbour_ptr->g_value = (current_node->g_value) + (current_node->distance(*neighbour_ptr));
            neighbour_ptr->visited = true;
            neighbour_ptr->parent = current_node;
            this->open_list.push_back(neighbour_ptr);
        }
    }
}

bool compare(RouteModel::Node const *this_node, RouteModel::Node const *that_node)
{
    float this_fvalue = (this_node->g_value) + (this_node->h_value);
    float that_fvalue = (that_node->g_value) + (that_node->h_value);
    return (this_fvalue > that_fvalue);
}

RouteModel::Node *RoutePlanner::NextNode()
{
    if (this->open_list.size() == 1) // no need to sort
    {
        RouteModel::Node *start = *(this->open_list.begin());
        this->open_list.pop_back();
        return start;
    }
    else
    {
        std::sort(this->open_list.begin(), this->open_list.end(), compare);
        this->open_list.pop_back();
        RouteModel::Node *start = *(this->open_list.begin());
        RouteModel::Node *end = *(this->open_list.end());
        return end;
    }
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node)
{
    distance = 0.0f;
    // Create path_found vector
    std::vector<RouteModel::Node> path_found;

    RouteModel::Node *current_node_loc = current_node;
    while (current_node_loc != nullptr)
    {
        path_found.push_back(*current_node_loc);
        current_node_loc = current_node_loc->parent;
    }

    for (RouteModel::Node node : path_found)
    {
        if (node.parent != nullptr)
        {
            RouteModel::Node parent = *(node.parent);
            distance = distance + node.distance(parent);
        }
    }
    this->distance = (distance * m_Model.MetricScale());
    std::reverse(path_found.begin(), path_found.end());

    return path_found;
}

void RoutePlanner::AStarSearch()
{
    RouteModel::Node *current_node = this->start_node;
    current_node->h_value = this->CalculateHValue(current_node);
    current_node->g_value = 0.0f;
    current_node->visited = true;
    this->AddNeighbors(current_node);

    while (current_node != this->end_node)
    {
        current_node = this->NextNode();
        this->AddNeighbors(current_node);
    }
    this->m_Model.path = this->ConstructFinalPath(current_node);
}