#include "IO_File.hpp"

IO_File::IO_File(const IO_File &lhs)
        : next_node_id_(lhs.next_node_id_)
        , id_node_map_(lhs.id_node_map_)
        , hierarchy_manager_(lhs.hierarchy_manager_)
		, attributes_manager_(lhs.attributes_manager_) {}

IO_File::IO_File(IO_File &&lhs)
	: next_node_id_(std::move(lhs.next_node_id_))
    , id_node_map_(std::move(lhs.id_node_map_))
    , hierarchy_manager_(std::move(lhs.hierarchy_manager_))
	, attributes_manager_(std::move(lhs.attributes_manager_)) {}

IO_File &IO_File::operator = (const IO_File &lhs)
{
    if(this == &lhs) {
        return *this;
    }
    next_node_id_ = lhs.next_node_id_;
    id_node_map_ = lhs.id_node_map_;
    hierarchy_manager_ = lhs.hierarchy_manager_;
	attributes_manager_ = lhs.attributes_manager_;
    return *this;
}

IO_File &IO_File::operator = (IO_File &&lhs)
{
    if(this == &lhs) {
        return *this;
    }
    next_node_id_ = std::move(lhs.next_node_id_);
    id_node_map_ = std::move(lhs.id_node_map_);
    hierarchy_manager_ = std::move(lhs.hierarchy_manager_);
	attributes_manager_ = std::move(lhs.attributes_manager_);
    return *this;
}

IO_Node IO_File::CreateIONode()
{
	io_file::Id node_id = AssignId_();
    IO_Node node(node_id);
    id_node_map_[node_id] = node;
    return node;
}

void IO_File::DestroyIONode(const IO_Node& node)
{
    hierarchy_manager_.RemoveNodeFromHierarchy(node.GetId());
	attributes_manager_.RemoveNodeFromAllAttributes(node.GetId());
    id_node_map_.erase(node.GetId());
    return;
}

std::vector<IO_Node> IO_File::GetTopLevelNodes()
{
	std::vector<IO_Node> top_level_nodes; 
	for (auto it = this->begin(); it != this->end(); ++it) {
		if (!this->HasParent(GetIONode(it))) {
			top_level_nodes.emplace_back(GetIONode(it));
        }
    }
	return top_level_nodes;
}

io_file::Id IO_File::AssignId_()
{
    return next_node_id_++;
}

/* ------------- Attribute : Hierarchy ------------- */

void IO_File::SetAsParentChild(const IO_Node& parent, const IO_Node& child)
{
    return hierarchy_manager_.SetAsParentChild(parent.GetId(), child.GetId());
}

void IO_File::RemoveAsParentChild(const IO_Node& parent, const IO_Node& child)
{
    return hierarchy_manager_.RemoveAsParentChild(parent.GetId(), child.GetId());
}

bool IO_File::HasChildren(const IO_Node& node)
{
    return hierarchy_manager_.HasChildren(node.GetId());
}

bool IO_File::HasParent(const IO_Node& node)
{
    return hierarchy_manager_.HasParent(node.GetId());
}

std::vector<IO_Node> IO_File::GetChildren(const IO_Node& node)
{
    std::vector<IO_Node> ionode_vec;
    auto id_vec = hierarchy_manager_.GetChildren(node.GetId());

    for(auto it = id_vec.begin(); it != id_vec.end(); ++it) {
        ionode_vec.push_back(id_node_map_[*it]);
    }

    return ionode_vec;
}

std::vector<IO_Node> IO_File::GetParents(const IO_Node & node)
{
	std::vector<IO_Node> ionode_vec;
	auto id_vec = hierarchy_manager_.GetParents(node.GetId());

	for (auto it = id_vec.begin(); it != id_vec.end(); ++it) {
		ionode_vec.push_back(id_node_map_[*it]);
    }

	return ionode_vec;
}

void IO_File::RemoveIONodeFromHierarchy_(const IO_Node& node)
{
    return hierarchy_manager_.RemoveNodeFromHierarchy(node.GetId());
}