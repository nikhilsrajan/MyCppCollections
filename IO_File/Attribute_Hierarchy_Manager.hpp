#ifndef ATTRIBUTE_HIERARCHY_MANAGER_H
#define ATTRIBUTE_HIERARCHY_MANAGER_H

#include <vector>
#include <map>
#include <algorithm>

/**
 * @brief Attribute manager to handle hierarchy information, which node is parent to which node.
 *        This relation noted using the unique id of the nodes stored in a multimap.
 * @author nsr
 */
class Attribute_Hierarchy_Manager
{
public:
     Attribute_Hierarchy_Manager() = default;
    ~Attribute_Hierarchy_Manager() = default;

    Attribute_Hierarchy_Manager(const Attribute_Hierarchy_Manager& lhs)
        : parent_child_multimap_(lhs.parent_child_multimap_) {}

    Attribute_Hierarchy_Manager(Attribute_Hierarchy_Manager&& lhs)                              /* Rule of 5 (C++) */
        : parent_child_multimap_(std::move(lhs.parent_child_multimap_)) {}

    Attribute_Hierarchy_Manager& operator = (const Attribute_Hierarchy_Manager& lhs) {
        parent_child_multimap_ = lhs.parent_child_multimap_;
        return *this;
    }

    Attribute_Hierarchy_Manager& operator = (Attribute_Hierarchy_Manager&& lhs) {
        parent_child_multimap_ = std::move(lhs.parent_child_multimap_);
        return *this;
    }

    /**
     * @brief Records the nodes with ids parent_id and child_id as parent and child respectively.
     * @param parent_id Id of the node being set as parent.
     * @param child_id Id of the node being set as child.
     */
    void SetAsParentChild(const unsigned& parent_id, const unsigned& child_id);

    /**
     * @brief Removes the parent-child relationship recorded for nodes with ids parent_id and child_id.
     * @param parent_id Id of the node being removed as parent.
     * @param child_id Id of hte node being removed as child.
     */
    void RemoveAsParentChild(const unsigned& parent_id, const unsigned& child_id);

    /**
     * @brief Checks if the given node with id node_id has any children.
     *        A node can have multiple children.
     *        A node can be its own child.
     * @param node_id Id of the node being checked if it has children.
     * @return true, if the node with id node_id has at least one child.
     * @return false, if the node with id node_id has no children.
     */
    bool HasChildren(const unsigned& node_id);

    /**
     * @brief Checks if the given node with id node_id has a parent.
     *        A node can have multiple parents.
     *        A node can be its own parent.
     * @param node_id Id of the node being checked if it has a parent.
     * @return true, if the node with id node_id has a parent.
     * @return false, if the node with id node_id has no parent.
     */
    bool HasParent(const unsigned& node_id);

    /**
     * @brief Get all the children of the give node with id node_id as a vector of ids.
     * @param node_id Id of the node whose list of children is being returned.
     * @return vector of unsigned integers, vector of ids of nodes who are children of node with id node_id.
     */
    std::vector<unsigned> GetChildren(const unsigned& node_id);

	/**
	* @brief Get all the parents of the give node with id node_id as a vector of ids.
	* @param node_id Id of the node whose list of parents is being returned.
	* @return vector of unsigned integers, vector of ids of nodes who are parents of node with id node_id.
	*/
	std::vector<unsigned> GetParents(const unsigned& node_id);

    /**
     * @brief Erase all the records of the node with id node_id - records as a parent and as a child.
     * @param node_id Id of the node which is to be erased from the heirarchy manager.
     */
    void RemoveNodeFromHierarchy(const unsigned& node_id);

private:
    std::multimap<unsigned, unsigned> parent_child_multimap_;
};

#endif // ATTRIBUTE_HIERARCHY_MANAGER_H
