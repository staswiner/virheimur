#include "Maths.h"

namespace Stas
{
	Maths::Maths()
	{
	}


	Maths::~Maths()
	{
	}

	float Maths::barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos)
	{
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}
	float Maths::Mod(float a, float b)
	{
		float end = mod(a, b);
		if (end < 0.0f)
		{
			end += b;
		}
		return end;
	}
	//vector<vec3> Maths::Dijekstra(map<vec3, pair<vec3, float>> Nodes,vec3 Start, vec3 Destination)
	//{
	//	//vector<float> Distances;
	//	//// DHCP algorithm simulation
	//	//// Current implementation O(v²) = (v²+v)
	//	//list<vec3> Path;
	//	//// Initialize
	//	//for (auto it = Nodes.begin(); it != Nodes.end(); it++)
	//	//{
	//	//	it->second.second = 1000000; // milion;
	//	//								 //i->second.second=
	//	//}
	//	//for (int i = 0; i < Nodes.size(); i++)
	//	//{
	//	//	for (auto it = Nodes.begin(); it != Nodes.end(); it++)
	//	//	{
	//	//		// calculates current node from lastnode+distance
	//	//		if (float NewDistance = (Nodes[it->first].second + glm::distance(it->second.first, it->first)) < it->second.second)
	//	//		{
	//	//			it->second.second = NewDistance;
	//	//		}
	//	//	}
	//	//}
	//	//Nodes[Start].second = glm::distance(Start, Nodes[Start].first);
	//	return vector<vec3>();
	//}
	bool Maths::vec3Compare(const vec3& lhs, const vec3& rhs)
	{
		if (lhs.x == rhs.x)
		{
			if (lhs.y == rhs.y)
				return lhs.z < rhs.z;
			return lhs.y < rhs.y;
		}
		return lhs.x < rhs.x;
		// Distance factor
		/*return lhs.x*lhs.x+lhs.y*lhs.y +lhs.z*lhs.z < 
			rhs.x*rhs.x + rhs.y*rhs.y + rhs.z*rhs.z;*/
	}
	bool Maths::IsIn(vec2 TopLeft, vec2 BotRight, vec2 TestSample)
	{
		if (TopLeft.x > TestSample.x)
			return false;
		if (TopLeft.y > TestSample.y)
			return false;
		if (BotRight.x < TestSample.x)
			return false;
		if (BotRight.y < TestSample.y)
			return false;
		return true;
	}
	vector<vec3>* Maths::Dijkstra(const map<vec3,map<vec3,int, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target)
	{
#pragma region Initialization
		map<vec3, int, bool(*)(const vec3&,const vec3&)> minDistance(vec3Compare);
		map<vec3, vec3, bool(*)(const vec3&, const vec3&)> BackTracking(Stas::Maths::vec3Compare);

		vector<vec3>* returnPath = new vector<vec3>();
		for (auto i : graph)
		{
			for each (auto j in i.second)
			{
				minDistance[j.first] = INT_MAX;
			}
			//for (auto &j : i)
		}
		minDistance[source] = 0;

		map<vec3, int, bool(*)(const vec3&, const vec3&)> activeVertices(Stas::Maths::vec3Compare);
		activeVertices[ source ] = 0;
#pragma endregion Initialization
		while (!activeVertices.empty()) 
		{
			vec3 Where = activeVertices.begin()->first;
			if (Where == target)
			{
				vec3 backtrackingNode = target;
				while (backtrackingNode != source)
				{
					returnPath->push_back(backtrackingNode);
					backtrackingNode = BackTracking[backtrackingNode];
				}
				if (returnPath->size() > 1)
				{
					int i = 0;;
				}
				returnPath->push_back(backtrackingNode);
				return returnPath;
				//return minDistance[where];
			}
			activeVertices.erase(activeVertices.begin());
			for (auto ed : graph.at(Where))
			{
				if (minDistance[ed.first] > minDistance[Where] + ed.second) 
				{
					activeVertices.erase(ed.first);
					minDistance[ed.first] = minDistance[Where] + ed.second;
					activeVertices[ed.first]= minDistance[ed.first];
					BackTracking[ed.first]=Where;
				}
			}
		}
		return nullptr;

		//return INT_MAX;
	}
	vector<vec3>* Maths::Astar(const map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>,
		bool(*)(const vec3&, const vec3&)>& graph, vec3 source, vec3 target)
	{
		priority_queue<float> hi;
		float fx, gx, hx;
		vec3 CurrentNode = source;// = source;
		map<vec3, vec3, bool(*)(const vec3&, const vec3&)> BackTracking(Stas::Maths::vec3Compare);
		vector<vec3>* returnPath = new vector<vec3>();

		// Find Cheapest sibling
		map<vec3,int,bool(*)(const vec3&, const vec3&)> siblings = graph.at(source);
		map<float, vec3> ActiveNodes;
		while (CurrentNode != target)
		{

			vec3 MinSibling;
			float MinDistance = INT_MAX;

			for (auto sibling : siblings)
			{
				float /*fx*/ totaldistance = /*gx*/ (glm::distance(CurrentNode, sibling.first) +/*Current Node Total Distance*/0)
					+ /*hx*/ glm::distance(sibling.first, target);
				ActiveNodes[totaldistance] = sibling.first;
				if (MinDistance > sibling.second)
				{
					MinDistance = sibling.second;
					MinSibling = sibling.first;
				}
			}
			siblings.erase(CurrentNode);
			if (distance(BackTracking[ActiveNodes.begin()->second], CurrentNode) >
				distance(ActiveNodes.begin()->second, CurrentNode))
			{
				BackTracking[ActiveNodes.begin()->second] = CurrentNode;
			}
			if (CurrentNode == ActiveNodes.begin()->second)
			{
				ActiveNodes.erase(ActiveNodes.begin());
				CurrentNode = ActiveNodes.begin()->second;
			}
			CurrentNode = ActiveNodes.begin()->second;
		}

		vec3 backtrackingNode = target;
		while (backtrackingNode != source)
		{
			returnPath->push_back(backtrackingNode);
			backtrackingNode = BackTracking[backtrackingNode];
		}
		returnPath->push_back(backtrackingNode);
		return returnPath;
	}
}