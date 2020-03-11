#include "Attribute_Hierarchy_Manager.hpp"

void Attribute_Hierarchy_Manager::SetAsParentChild(const unsigned& parent_id, const unsigned& child_id)
{
    parent_child_multimap_.emplace(parent_id, child_id);
    return;
}

void Attribute_Hierarchy_Manager::RemoveAsParentChild(const unsigned& parent_id, const unsigned& child_id)
{
    auto iterpair = parent_child_multimap_.equal_range(parent_id);
    for(auto it = iterpair.first; it != iterpair.second; ++it)
    {
        if(it->second == child_id)
        {
            parent_child_multimap_.erase(it);
            break;
        }
    }
    return;
}

bool Attribute_Hierarchy_Manager::HasChildren(const unsigned& node_id)
{
    return parent_child_multimap_.find(node_id) != parent_child_multimap_.end() ? true : false;
}

bool Attribute_Hierarchy_Manager::HasParent(const unsigned& node_id)
{
    bool has_parent = false;

    for(auto it = parent_child_multimap_.begin(); it != parent_child_multimap_.end() && !has_parent; ++it)
        if(it->second == node_id)
            has_parent = true;

    return has_parent;
}

std::vector<unsigned> Attribute_Hierarchy_Manager::GetChildren(const unsigned& node_id)
{
    std::vector<unsigned> children_vec;
    auto result =  parent_child_multimap_.equal_range(node_id);
    children_vec.reserve(std::distance(result.first, result.second));
    for(auto it = result.first; it != result.second; ++it)
        children_vec.emplace_back(it->second);
    return children_vec;
}

std::vector<unsigned> Attribute_Hierarchy_Manager::GetParents(const unsigned & node_id)
{
	std::vector<unsigned> parents_vec;
	for (auto it = parent_child_multimap_.begin(); it != parent_child_multimap_.end(); ++it)
		if (it->second == node_id)
			parents_vec.emplace_back(it->first);
	return parents_vec;
}

void Attribute_Hierarchy_Manager::RemoveNodeFromHierarchy(const unsigned& node_id)
{
    for(auto it = parent_child_multimap_.begin(); it != parent_child_multimap_.end(); ++it)
    {
        if(it->first == node_id)
            parent_child_multimap_.erase(it);
        else
        if(it->second == node_id)
            parent_child_multimap_.erase(it);
    }
    return;
}
