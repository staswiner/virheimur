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
	vector<vec3> Maths::Dijkstra(const map<vec3,map<vec3,int, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target)
	{
		map<vec3, map<vec3, int>> a;
#pragma region Initialization
		map<vec3, int, bool(*)(const vec3&,const vec3&)> minDistance(vec3Compare);
		map<vec3, vec3, bool(*)(const vec3&, const vec3&)> BackTracking(Stas::Maths::vec3Compare);

		vector<vec3> returnPath;
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
		activeVertices[source] = 0;
#pragma endregion Initialization
		while (!activeVertices.empty())
		{
			vec3 Where = activeVertices.begin()->first;
			if (Where == target)
			{
				vec3 backtrackingNode = target;
				while (backtrackingNode != source)
				{
					returnPath.push_back(backtrackingNode);
					backtrackingNode = BackTracking[backtrackingNode];
				}
				if (returnPath.size() > 1)
				{
					int i = 0;
				}
				returnPath.push_back(backtrackingNode);
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
					activeVertices[ed.first] = minDistance[ed.first];
					BackTracking[ed.first] = Where;
				}
			}
		}
		return vector<vec3>();

		//return INT_MAX;
	}
//	vector<vec3> Maths::DijkstraB(std::map<vec3, vector<vec3>, std::function<bool(const vec3& lhs, const vec3& rhs)>>
//		&graph, vec3 source, vec3 target)
//	{
//		map<vec3, map<vec3, int>> a;
//#pragma region Initialization
//		map<vec3, int, bool(*)(const vec3&, const vec3&)> minDistance(vec3Compare);
//		map<vec3, vec3, bool(*)(const vec3&, const vec3&)> BackTracking(Stas::Maths::vec3Compare);
//
//		vector<vec3> returnPath;
//		for (auto i : graph)
//		{
//			for each (auto j in i.second)
//			{
//				minDistance[j.first] = INT_MAX;
//			}
//			//for (auto &j : i)
//		}
//		minDistance[source] = 0;
//
//		map<vec3, int, bool(*)(const vec3&, const vec3&)> activeVertices(Stas::Maths::vec3Compare);
//		activeVertices[source] = 0;
//#pragma endregion Initialization
//		while (!activeVertices.empty())
//		{
//			vec3 Where = activeVertices.begin()->first;
//			if (Where == target)
//			{
//				vec3 backtrackingNode = target;
//				while (backtrackingNode != source)
//				{
//					returnPath.push_back(backtrackingNode);
//					backtrackingNode = BackTracking[backtrackingNode];
//				}
//				if (returnPath.size() > 1)
//				{
//					int i = 0;
//				}
//				returnPath.push_back(backtrackingNode);
//				return returnPath;
//				//return minDistance[where];
//			}
//			activeVertices.erase(activeVertices.begin());
//			for (auto ed : graph.at(Where))
//			{
//				if (minDistance[ed.first] > minDistance[Where] + ed.second)
//				{
//					activeVertices.erase(ed.first);
//					minDistance[ed.first] = minDistance[Where] + ed.second;
//					activeVertices[ed.first] = minDistance[ed.first];
//					BackTracking[ed.first] = Where;
//				}
//			}
//		}
//		return vector<vec3>();
//
//		//return INT_MAX;
//	}
	vector<vec3> Maths::Astar(const map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>,
		bool(*)(const vec3&, const vec3&)>& graph, vec3 source, vec3 target)
	{
		auto compare = [](const vec3& lhs, const vec3& rhs)->bool {
			if (lhs.x == rhs.x)
			{
				if (lhs.y == rhs.y)
					return lhs.z < rhs.z;
				return lhs.y < rhs.y;
			}
			return lhs.x < rhs.x;
		};
		auto functype = std::function<bool(const vec3&, const vec3&)>(compare);
		// used to store unique nodes to be references by in the graph
		map<vec3,node,decltype(functype)> Nodes(functype);
		std::map<vec3, pair<node*, vector<node*>>, decltype(functype)> Graph(functype);
		for (auto n : graph)
		{
			Nodes.insert(make_pair(n.first,node(n.first)));
		}
		for (auto n : graph)
		{
			vector<node*> vNeighbors;
			for (auto neighbor : n.second)
			{
				vNeighbors.push_back(&Nodes[neighbor.first]);
			}
			Graph[n.first] = make_pair(&Nodes[n.first],vNeighbors);
		}

		return Maths::AstarB(Graph,source,target);
		//return vector<vec3>();
	}
#define OPENLIST 1
#define CLOSEDLIST 2
	vector<vec3> Maths::AstarB(
		std::map<vec3, pair<node*, vector<node*>>, std::function<bool(const vec3& lhs, const vec3& rhs)>>
		& graph, vec3 source, vec3 target)
	{
		list<node*> openList;
		list<node*> closedList;
		node* StartNode = graph.at(source).first;
		(*StartNode).g = 0; // sets values for the starting node
		(*StartNode).h = glm::distance(source, target);
		(*StartNode).f = (*StartNode).g + (*StartNode).h;
		openList.push_back(StartNode); // adds to the open list
		while (openList.size() > 0)
		{
			// sort the open list to find the smallest element
			openList.sort([](const node* lhs, const node* rhs)->bool { // O(nlog(n))
				return lhs->f < rhs->f;
			});
			node* BestNode = graph.at((*openList.front()).pos).first;
			if ((*BestNode).pos == target)
			{
				break;
			}
			openList.pop_front();

			if ((*BestNode).parent)
			{
				closedList.push_back(BestNode);
				(*BestNode).List = CLOSEDLIST;
				(*BestNode).g = (*BestNode).parent->g + distance((*BestNode).parent->pos, (*BestNode).pos);
			}
			else
			{
				closedList.push_back(BestNode);
				(*BestNode).List = CLOSEDLIST;
			}

			for (auto v : graph.at((*BestNode).pos).second)
			{
				node* n = graph.at((*v).pos).first;
				if ((*n).List == CLOSEDLIST)
					continue;
				if ((*n).List != OPENLIST)
				{
					(*n).List = OPENLIST;
					openList.push_back(n);
				}
				if ((*v).pos == target)
				{
					(*v).parent = BestNode;
					break;
				}
				float g = (*BestNode).g + distance((*BestNode).pos, (*v).pos);
				float h = distance(target, (*v).pos);
				float f = g + h;
				if ((*n).f > f)
				{	
					(*n).parent = BestNode;
					(*n).f = f;
				}
				int i = 0;
			}
		}
		vector<vec3> returnPath;
		node currentNode = *graph.at(target).first;
		// if no path found
		if (currentNode.parent == nullptr)
		{
			return returnPath;
		}
		// path found
		do {
			returnPath.push_back(currentNode.pos);
			currentNode = *currentNode.parent;
		} while (currentNode.parent != nullptr);
		returnPath.push_back(currentNode.pos);

		return returnPath;
	}
	vector<vec3> Maths::AstarGrid(
		std::map<vec3, pair<node*, vector<node*>>, std::function<bool(const vec3& lhs, const vec3& rhs)>>
		& graph, vec3 source, vec3 target)
	{
		// Create grid graph
		MinimapData NewGraph;
		vector<node> NewGraphNodes;
		NewGraphNodes.resize(NewGraph.Height*NewGraph.Width);


		// algorithm
		list<node*> openList;
		list<node*> closedList;
		node* StartNode = graph.at(source).first;
		(*StartNode).g = 0; // sets values for the starting node
		(*StartNode).h = glm::distance(source, target);
		(*StartNode).f = (*StartNode).g + (*StartNode).h;
		openList.push_back(StartNode); // adds to the open list
		while (openList.size() > 0)
		{
			// sort the open list to find the smallest element
			openList.sort([](const node* lhs, const node* rhs)->bool { // O(nlog(n))
				return lhs->f < rhs->f;
			});
			node* BestNode = graph.at((*openList.front()).pos).first;
			if ((*BestNode).pos == target)
			{
				break;
			}
			openList.pop_front();

			if ((*BestNode).parent)
			{
				closedList.push_back(BestNode);
				(*BestNode).List = CLOSEDLIST;
				(*BestNode).g = (*BestNode).parent->g + distance((*BestNode).parent->pos, (*BestNode).pos);
			}
			else
			{
				closedList.push_back(BestNode);
				(*BestNode).List = CLOSEDLIST;
			}

			for (auto v : graph.at((*BestNode).pos).second)
			{
				node* n = graph.at((*v).pos).first;
				if ((*n).List == CLOSEDLIST)
					continue;
				if ((*n).List != OPENLIST)
				{
					(*n).List = OPENLIST;
					openList.push_back(n);
				}
				if ((*v).pos == target)
				{
					(*v).parent = BestNode;
					break;
				}
				float g = (*BestNode).g + distance((*BestNode).pos, (*v).pos);
				float h = distance(target, (*v).pos);
				float f = g + h;
				if ((*n).f > f)
				{
					(*n).parent = BestNode;
					(*n).f = f;
				}
				int i = 0;
			}
		}
		vector<vec3> returnPath;
		node currentNode = *graph.at(target).first;
		// if no path found
		if (currentNode.parent == nullptr)
		{
			return returnPath;
		}
		// path found
		do {
			returnPath.push_back(currentNode.pos);
			currentNode = *currentNode.parent;
		} while (currentNode.parent != nullptr);
		returnPath.push_back(currentNode.pos);

		return returnPath;
	}
#undef OPENLIST 
#undef CLOSEDLIST 
	unsigned long long Maths::llrand() {
		unsigned long long r = 0;

		for (int i = 0; i < 5; ++i) {
			r = (r << 15) | (rand() & 0x7FFF);
		}

		return r & 0xFFFFFFFFFFFFFFFFULL;
	}
}
struct Node
{
	vec3 Location;
	vec3 Parent;
	float fx; // estimate distance
	float gx; // true current distance
};
void function()
{
	priority_queue<float> hi;
	map<vec3, vector<pair<vec3,float>>> graph; // each node has his siblings with the distance to them
	vector<vec3> backTrack; // sorted from End to Start
	map<float, vec3> ActiveNodes; // sorted by distance, all untouched nodes


}
