#ifndef PATTERN_RECOGNIZE_TREEMANAGER_H
#define PATTERN_RECOGNIZE_TREEMANAGER_H

#include "CriteriaNode.h"
#include <vector>
#include <map>

class TreeManager
{
public:
	explicit TreeManager(): currentId(0)
	{
		double temp_data[3] = {0,0,0};
		this->AddNode(temp_data);
	}

	const CriteriaNode& operator[](const int &i) const
		{return this->TreeVector[i];}
	CriteriaNode& operator[](const int &i)
		{return const_cast<CriteriaNode&>(static_cast<const TreeManager&>(*this)[i]);	}

	/**
	 * @name          TreeManager::AddNode(data [, parent])
	 * @desc          Adds node to the current tree
	 *
	 * @param data    Data of new node
	 * @param parent  Parent of current node
	 * @return        Id of node with such coordinates
	 */

	//Simple
	const uint16_t AddNode(double data[3])
	{
		for(int i = 0 ; i < TreeVector.size(); ++i)
			if(TreeVector[i].closeTo(data))
				return i;
		this->TreeVector.push_back(CriteriaNode::getByDimensions(data));
		TreeVector[TreeVector.size()-1].id = TreeVector.size()-1;
		return TreeVector.size()-1;
	}

	// This version of AddNode adds new Node after parent
	const uint16_t AddNode(double data[3], const u_int16_t parent) {
		uint16_t new_id = AddNode(data);
		TreeVector[parent].nextIds.push_back(new_id);
		return new_one;
	}

	/**
	 * @name          TreeManager::FindNodeAfterId
	 * @desc          Finds node with such data in children of object with id
	 *
	 * @param id      Id of parent object
	 * @param data    Data to be found
	 * @return        Id of such node
	 */
	const uint16_t FindNodeAfterId(const unsigned int id, double data[3])
	{
		for (int i = 0; i < TreeVector[id].nextIds.size(); ++i)
			if(TreeVector[TreeVector[id].childId(i)].closeTo(data))
				return TreeVector[id].childId(i);
		return 0;
	}

	uint16_t& getCurrentId()
		{return currentId;}
	CriteriaNode& getCurrent()
		{return TreeVector[currentId];};

private:
	std::vector<CriteriaNode> TreeVector;
	uint16_t currentId;
};


#endif //PATTERN_RECOGNIZE_TREEMANAGER_H
