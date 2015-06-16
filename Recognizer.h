#ifndef PATTERN_RECOGNIZE_RECOGNIZER_H
#define PATTERN_RECOGNIZE_RECOGNIZER_H

#include <vector>
#include <stdexcept>
#include "TreeManager.h"

struct RecognitionResult {
	uint16_t id;
	float probability;
};

class Recognizer
{
public:
	explicit Recognizer()	{}

	/**
	 * @name        sRecognizer::analyzeData
	 * @desk        Analyze data inserted data
	 *
	 * @param data  Data to be analyzed
	 * @return      Index of recognized if reached end
	 *              Null, if did not
	 */
	const RecognitionResult analyzeData(double data[3])
	{
		RecognitionResult res = {0,0.0};
		uint16_t maxProbable = treeManager.getCurrentId();
		// Checking probability of current
		float maxSimilarity = treeManager.getCurrent().compareWith(data);
		// Choosing the most probable result
		for(int i = 0 ; i < treeManager.getCurrent().nextIds.size(); ++i) {
			uint16_t id = treeManager.getCurrent().childId(i);
			double similarity = treeManager[id].compareWith(data);
			if(maxSimilarity < similarity) {
				maxSimilarity = similarity;
				maxProbable = id;
			}
		}
		return {maxProbable,maxSimilarity};
	}
	const RecognitionResult analyzeData(std::vector<double [3]> data)
	{
		RecognitionResult res = {0,0.0};
		for(int i = 0 ; i < data.size(); ++i)
			res = analyzeData(data[i]);
		return res;
	};

	void addGesture(std::vector<double [3]> data) {
		uint16_t current_id = 0;
		for(unsigned int i = 0 ; i < data.size(); ++i) {
			uint16_t obj_id = treeManager.FindNodeAfterId(current_id,data[i]);
			if(obj_id>0) {
				//TODO: write handling of existance of current gesture
			} else {
				//TODO: write creation new node
				obj_id = treeManager.addNode(data[i]);
			}
		}
	}

protected:
	std::map<uint16_t, uint16_t> classMap;
	TreeManager treeManager;
};


#endif //PATTERN_RECOGNIZE_RECOGNIZER_H
