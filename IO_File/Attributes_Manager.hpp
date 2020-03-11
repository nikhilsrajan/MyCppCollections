#ifndef ATTRIBUTES_MANAGER_H
#define ATTRIBUTES_MANAGER_H

#include "Attribute_Manager_Interface.hpp"
#include "Attribute_Manager.hpp"

#include <map>
#include <string>
#include <memory>
#include <vector>

#include <typeinfo>

/**
 * @brief Class to manage attribute managers.
 * @author nsr
 */
class Attributes_Manager
{
public:
    Attributes_Manager() = default;
    ~Attributes_Manager() = default;

    Attributes_Manager(const Attributes_Manager& lhs)
        : name_manager_map_(lhs.name_manager_map_)
        , name_type_map_(lhs.name_type_map_) {}

    Attributes_Manager(Attributes_Manager&& lhs)
        : name_manager_map_(std::move(lhs.name_manager_map_))                       /* Rule of 5 (C++) */
        , name_type_map_(std::move(lhs.name_type_map_)) {}

    Attributes_Manager& operator = (const Attributes_Manager& lhs) {
        name_manager_map_ = lhs.name_manager_map_;
        name_type_map_ = lhs.name_type_map_;
        return *this;
    }

    Attributes_Manager& operator = (Attributes_Manager&& lhs) {
        name_manager_map_ = std::move(lhs.name_manager_map_);
        name_type_map_ = std::move(lhs.name_type_map_);
        return *this;
    }

    /**
     * @brief Checks if the manager is managing an attribute manager with name attribute.
     * @param attribute Name of the attribute whose manager is being looked for.
     * @return true, if the manager is managing a manager for an attribute with name attribute.
     * @return false, if the manager is not managing a manager for an attribute with name attribute.
     */
    bool HasAttribute(std::string attribute) {
        return name_manager_map_.find(attribute) != name_manager_map_.end() ? true : false;
    }

    /**
     * @brief Adds a new attribute manager to manage by the name attribute.
     * @param attribute Name of the attribute whose manager is being added.
     * @param default_value Default value for those nodes which haven't been recorded by the attribute manager.
     * @return true, if manager for an attribute by the name attribute did not previously exist.
     * @return false, if manager for an attribute by the name attribute did exist.
     */
    template <class T>
    bool AddAttribute(std::string attribute, T default_value = T{}) {
        if(HasAttribute(attribute)) return false;
        name_manager_map_.emplace(attribute, std::make_shared<Attribute_Manager<T>>(default_value));
        name_type_map_.emplace(attribute, typeid(T).name());
        return true;
    }

    /**
     * @brief Removes attribute manager by the name attribute.
     * @param attribute Name of the attribute whose manager is being removed.
     * @return true, if manager for an attribute by the name attribute exists.
     * @return false, if manager for an attribute by the name attribute doesn't exist.
     */
    bool RemoveAttribute(std::string attribute) {
        if(!HasAttribute(attribute)) return false;
        name_manager_map_.erase(attribute);
        name_type_map_.erase(attribute);
        return true;
    }

    /**
     * @brief Updates the default value for the attribute by the name attribute for those nodes which
     *        haven't been recorded by the attribute manager.
     * @param attribute Name of the attribute whose default value is being set.
     * @param value New default value being set for the attribute by the name attribute.
     * @return true, if manager for an attribute by the name attribute exists.
     * @return false, if manager for an attribute by the name attribute doesn't exist.
     */
    template <class T>
    bool SetDefaultValueForAttribute(std::string attribute, T value) {
        if(!HasAttribute(attribute)) return false;
        auto p = std::dynamic_pointer_cast<Attribute_Manager<T>>(name_manager_map_[attribute]);
        if(p == nullptr) return false;
        p->SetNewDefaultValue(value);
        return true;
    }

    /**
     * @brief Gets a list of attribute names and their data types.
     * @return Vector of pair of strings - attribute name and attribute data type.
     */
    std::vector<std::pair<std::string, std::string>> GetAttributesList () {
        auto number_of_attributes = name_type_map_.size();
        std::vector<std::pair<std::string, std::string>> attribute_list;
        attribute_list.reserve(number_of_attributes);
        for(auto it = name_type_map_.begin(); it != name_type_map_.end(); ++it)
            attribute_list.emplace_back(it->first, it->second);
        return attribute_list;
    }

    /**
     * @brief Gets the data type of the attribute by the name attribute.
     * @param attribute Name of the attribute whose data type is being looked up.
     * @param getter Parameter passed-by-reference to store the data type of the attribute that is being looked up.
     * @return true, if manager for an attribute by the name attribute exists.
     * @return false, if manager for an attribute by the name attribute doesn't exist.
     */
    bool GetTypeForAttribute(std::string attribute, std::string& getter) {
        if(!HasAttribute(attribute)) return false;
        getter = name_type_map_[attribute];
        return true;
    }

    /**
     * @brief Checks if node with id node_id is recorded by the manager of the attribute by the name attribute.
     * @param attribute Name of the attribute whose manager is being checked if it holds the record of the node
     *        with id node_id.
     * @param node_id Id of the node which is being looked up into the records of the manager of the attribute
     *        by the name attribute.
     * @return true, if the record of the node with id node_id exists in the manager of the attribute by the name
     *         attribute.
     * @return false, if the record of the node with id node_id does not exist in the manager of the attribute by
     *         the name attribute, or if the attribute by the name attribute is not being managed.
     */
    bool AttributeHasNode(std::string attribute, io_file::Id node_id) {
        if(!HasAttribute(attribute)) return false;
        return name_manager_map_[attribute]->HasNode(node_id);
    }

    /**
     * @brief Creates or updates a record for a node with id node_id in the manager for the attribute
     *        by the name attribute
     * @param attribute Name of the attribute whose manager's record is being updated.
     * @param node_id Id of the node whose record is being added or updated.
     * @param value New value of the attribute corresponding to the node with id node_id.
     * @return true, if the data type of the attribute was correctly specified.
     * @return false, if the data type of the attribute was incorrectly specified.
     */
    template<class T>
    bool AddNodeToAttribute(std::string attribute, io_file::Id node_id, T value) {
        if(!HasAttribute(attribute)) AddAttribute<T>(attribute);
        auto p = std::dynamic_pointer_cast<Attribute_Manager<T>>(name_manager_map_[attribute]);
        if(p == nullptr) return false;
        p->AddNode(node_id, value);
        return true;
    }

    /**
     * @brief Gets the value of the attribute with name attribute corresponding to the node with id node_id from its
     *        manager and puts it into getter, the parameter passed-by-reference.
     * @param attribute Name of the attribute whose value corresponding to the node with id node_id is being accessed.
     * @param node_id Id of the node whose attribute value is being accessed.
     * @param getter Passed-by-reference parameter that would store the attribute value accessed.
     * @return true, if the attribute by the name attribute exists, if the data type of the attribute was correctly
     *         specified, and if the record of the node with id node_id exists in the attribute manager.
     * @return false, if the attribute of by the name attribute doesn't exist, if the data type is incorrectly specified
     *         for the attribute, or if the record of the node with id node_id doesn't exist in the attribute manager.
     */
    template<class T>
    bool GetAttributeForNode(std::string attribute, io_file::Id node_id, T& getter) {
        if(!HasAttribute(attribute)) return false;
        auto p = std::dynamic_pointer_cast<Attribute_Manager<T>>(name_manager_map_[attribute]);
        if(p == nullptr) return false;
        return p->GetValue(node_id, getter);
    }

    /**
     * @brief Deletes the record of the node with id node_id from the manager of the attribute with name attribute
     * @param attribute Name of the attribute from whose manager the record of the node is to be deleted.
     * @param node_id Id of the node whose record is being deleted from the attribute manager.
     * @return true, if the attribute by the name attribute exists, and the record of the node with id node_id exists
     *         in attribute manager.
     * @return false, if the attribute by the name attribute doesn't exist, or if the record of the node with id node_id
     *         doesn't exist in the attribute manager.
     */
    bool RemoveNodeFromAttribute(std::string attribute, io_file::Id node_id) {
        if(!HasAttribute(attribute)) return false;
        return name_manager_map_[attribute]->RemoveNode(node_id);
    }

    /**
     * @brief Deletes the record of the node with id node_id from all the attribute managers.
     * @param node_id Id of the node whose record is being deleted from all the attribute managers.
     */
    void RemoveNodeFromAllAttributes(io_file::Id node_id) {
        for(auto it = name_manager_map_.begin(); it != name_manager_map_.end(); ++it)
            it->second->RemoveNode(node_id);
    }

private:
    std::map<std::string, std::shared_ptr<Attribute_Manager_Interface>> name_manager_map_;
    std::map<std::string, std::string> name_type_map_;
};

#endif // ATTRIBUTES_MANAGER_H
