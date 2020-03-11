#ifndef IO_FILE_H
#define IO_FILE_H

#include <map>
#include <memory>
#include <vector>

#include "IO_Node.hpp"
#include "Attribute_Hierarchy_Manager.hpp"
#include "Attribute_Manager.hpp"
#include "Attributes_Manager.hpp"

/**
* @brief Class to store file information.
*        Information is stored as nodes.
*        - A node is one entity in the file.
*        - It has attributes attached to it.
*        - It can have as many attributes of as many types attached to it.
*        - One node can be set as a parent or a child to another nodes.
*         
*        For detailed information on how to use Attribute_Manager and Attributes_Manager,
*        please refer the respective header files.
*
* @author nsr
*/

class IO_File
{
public:
    IO_File()
        : next_node_id_(0) {}
    ~IO_File() = default;
    IO_File(const IO_File& lhs);                    /* Rule of 5 (C++) */
    IO_File(IO_File&& lhs);
    IO_File& operator = (const IO_File& lhs);
    IO_File &operator = (IO_File &&lhs);

    IO_Node CreateIONode();
    void DestroyIONode(const IO_Node& node);

    // Returns vector of nodes without parents.
    std::vector<IO_Node> GetTopLevelNodes();

    typedef std::map<io_file::Id, IO_Node>::iterator iterator;

    iterator begin() {
        return id_node_map_.begin();
    }

    iterator end() {
        return id_node_map_.end();
    }

    size_t size() {
        return id_node_map_.size();
    }

    static IO_Node GetIONode(iterator it) {
        return it->second;
    }

    // To check if the attribute exists in the IO_File
    // Returns true if it exists, else false.
    bool AttributeExists(const std::string& attribute) {
        return attributes_manager_.HasAttribute(attribute);
    }
    // To create a new attribute
    // Returns true if the attribute did not already exist, else false.
    // Please note the attribute is type sensitive. This datatype cannot be changed,
    // unless the attribute is destoyed and recreated.
    template <class T>
    bool CreateAttribute(const std::string& attribute, const T& default_value = T()) {
        return attributes_manager_.AddAttribute<T>(attribute, default_value);
    }
    // Removes the  attribute from the IO_File
    // Returns true if the  attribute previously existed, else false.
    bool DestroyAttribute(const std::string& attribute) {
        return attributes_manager_.RemoveAttribute(attribute);
    }
    // Updates the default value for a  attibute
    // Returns true if the attribute exists and the datatype is
    // specified correctly, else false.
    template <class T>
    bool SetDefaultValueForAttribute(const std::string& attribute, const T& default_value) {
        return attributes_manager_.SetDefaultValueForAttribute<T>(attribute, default_value);
    }
    // Returns a vector of pair of strings (attribute name, attribute type).
    std::vector<std::pair<std::string, std::string>> GetAttributesList() {
        return attributes_manager_.GetAttributesList();
    }
    // Returns the attribute type as a string.
    bool GetAttributeType(const std::string& attribute, std::string& getter) {
        return attributes_manager_.GetTypeForAttribute(attribute, getter);
    }
    // To check if a given node has the given  attribute.
    // Returns true if the attribute exists and the node has the attribute, else false.
    bool HasAttribute(const std::string& attribute, const IO_Node& node) {
        return attributes_manager_.AttributeHasNode(attribute, node.GetId());
    }
    // To add a  attribute to the given node.
    // Return true if successfully added.
    // Returns false if the attribute already existed but the datatype specified was incorrect.
    // If the attribute doesn't already exist, the attribute would be created. The datatype
    // then specified would be fixed for the attribute. It cannot be changed later.
    template <class T>
    bool AddAttribute(const std::string& attribute, const IO_Node& node, T value) {
        return attributes_manager_.AddNodeToAttribute(attribute, node.GetId(), value);
    }
    // Gets the value of the  attribute for a given node.
    // Returns true if the attribute exists and the node has the attribute and the datatype of the
    // attribute was correctly specified. Else false.
    template<class T>
    bool GetAttribute(const std::string& attribute, const IO_Node& node, T& getter) {
        return attributes_manager_.GetAttributeForNode(attribute, node.GetId(), getter);
    }
    // Removes the  attribute from the node.
    // Returns true if the attribute exists, else false.
    bool RemoveAttribute(const std::string& attribute, const IO_Node& node) {
        return attributes_manager_.RemoveNodeFromAttribute(attribute, node.GetId());
    }


private:
    io_file::Id next_node_id_;
    std::map<io_file::Id, IO_Node> id_node_map_;

    Attributes_Manager attributes_manager_;

    io_file::Id AssignId_();
    void RemoveIONodeFromHierarchy_(const IO_Node& node);
};

#endif // IO_FILE_H
