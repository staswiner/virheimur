#include "Maths.h"


namespace Stas
{

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
	

	
	int ConvertToArray(int WorldWidth, int WorldHeight, int Width, int Height, int x, int z)
	{
		int newx = float(float(x + WorldWidth / 2) / float(WorldWidth)) * Width;
		int newz = float(float(z + WorldHeight / 2) / float(WorldHeight)) * Height;
		return (newx + Width*newz);
	}
	vec3 ConvertToWorldCoords(int WorldWidth, int WorldHeight, int Width, int Height, vec3 pos)
	{
		vec3 newpos = ((pos - vec3(Width / 2)) / float(Width)) * float(WorldWidth);
		return newpos;
	}
	vec3 ConvertToMapCoords(int WorldWidth, int WorldHeight, int Width, int Height, vec3 pos)
	{
		vec3 newpos = (pos + (vec3(WorldWidth) / 2.0f)) / float(WorldWidth) * (float)Width;
		return newpos;
	}
	
	unsigned long long Maths::llrand() {
		unsigned long long r = 0;

		for (int i = 0; i < 5; ++i) {
			r = (r << 15) | (rand() & 0x7FFF);
		}

		return r & 0xFFFFFFFFFFFFFFFFULL;
	}
	Maths::Vectors::Point Maths::Vectors::IntersectionTwoLines(Line line1, Line line2)
	{
		return Point();
	}
	Maths::Vectors::Point Maths::Vectors::IntersectionPlaneLine(Plane plane, Line line)
	{
		if (line.direction == vec3(0))
		{
			return Maths::Vectors::IntersectionPlanePoint(plane, Point(line.point, line.valid));
		}
		if (glm::dot(line.direction, plane.normal) == 0)
		{
			return Maths::Vectors::IntersectionPlanePoint(plane, Point(line.point, line.valid));
		}
		float D = (glm::dot(plane.point - line.point, plane.normal) / (glm::dot(line.direction, plane.normal)));
		if (D == NAN);
		vec3 Intersection = D*line.direction + line.point;
		Point ReturnPoint(Intersection, true);
		return ReturnPoint;
	}
	Maths::Vectors::Point Maths::Vectors::IntersectionPlanePoint(Plane plane, Point point)
	{
		if (plane.point == point.point)
		{
			point.valid = true;
			return point;
		}
		Line testLine(plane.point, point.point - plane.point);
		if (plane.normal.x * point.point.x +
			plane.normal.y * point.point.y +
			plane.normal.z * point.point.z ==
			plane.normal.x * plane.point.x +
			plane.normal.y * plane.point.y +
			plane.normal.z * plane.point.z)
		{
			point.valid = true;
			return point;
		}
		else
		{
			point.valid = false;
			return point;
		}
	}
	void Maths::Vectors::IntersectionTwoPlanes(Plane plane1, Plane plane2)
	{
	}
	void Maths::Vectors::IntersectionTwoBB(BoundryBox bb1, BoundryBox bb2)
	{
	}
	float Maths::Vectors::DistanceIntersectionTwoBB(BoundryBox bb1, BoundryBox bb2)
	{
		/*
		find nearest vertex to the nearest plane;
		calculate vertex from that plane distance in the direction of the velocity vector
		*/
		return 0.0f;
	}
	void Maths::Vectors::IntersectionSpherePlane(Sphere sphere1, Plane plane2)
	{
	}
	void Maths::Vectors::IntersectionSphereLine(Sphere sphere1, Line line2)
	{
	}
	Maths::Vectors::Circle Maths::Vectors::IntersectionTwoSpheres(Sphere sphere1, Sphere sphere2)
	{
		if (glm::distance(sphere1.Center, sphere2.Center) < sphere1.radius + sphere2.radius)
		{
			Circle circle;
			circle.valid = true;
			circle.Center = (sphere1.Center + sphere2.Center) / 2.0f;
			//circle.radius = ;
			return circle;
		}
		else
		{
			Circle circle;
			circle.valid = false;
			return circle;
		}
	}

	namespace Algorithms
	{
		namespace Approximate
		{
#pragma region PathFinding
#define OPENLIST 1
#define CLOSEDLIST 2
			vector<vec3> PathFinding::Dijkstra(const map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
				, bool(*)(const vec3&, const vec3&)> &graph, vec3 source, vec3 target)
			{
				map<vec3, map<vec3, int>> a;
				auto vec3Compare = [](const vec3& lhs, const vec3& rhs) -> bool {
					if (lhs.x == rhs.x)
					{
						if (lhs.y == rhs.y)
							return lhs.z < rhs.z;
						return lhs.y < rhs.y;
					}
					return lhs.x < rhs.x;
				};
#pragma region Initialization
				map<vec3, int, bool(*)(const vec3&, const vec3&)> minDistance(vec3Compare);
				map<vec3, vec3, bool(*)(const vec3&, const vec3&)> BackTracking(vec3Compare);

				vector<vec3> returnPath;
				for (auto i : graph)
				{
					for each (auto j in i.second)
					{
						minDistance[j.first] = INT_MAX;
					}
				}
				minDistance[source] = 0;

				map<vec3, int, bool(*)(const vec3&, const vec3&)> activeVertices(vec3Compare);
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
			vector<vec3> PathFinding::A_Star(const map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>,
				bool(*)(const vec3&, const vec3&)>& graph, vec3 source, vec3 target)
			{
				auto functype = std::function<bool(const vec3&, const vec3&)>(
					[](const vec3& lhs, const vec3& rhs)->bool {
					if (lhs.x == rhs.x)
					{
						if (lhs.y == rhs.y)
							return lhs.z < rhs.z;
						return lhs.y < rhs.y;
					}
					return lhs.x < rhs.x;
				});
				// used to store unique nodes to be references by in the graph
				map<vec3, node, decltype(functype)> Nodes(functype);
				std::map<vec3, pair<node*, vector<node*>>, decltype(functype)> Graph(functype);
				for (auto n : graph)
				{
					Nodes.insert(make_pair(n.first, node(n.first)));
				}
				for (auto n : graph)
				{
					vector<node*> vNeighbors;
					for (auto neighbor : n.second)
					{
						vNeighbors.push_back(&Nodes[neighbor.first]);
					}
					Graph[n.first] = make_pair(&Nodes[n.first], vNeighbors);
				}

				return PathFinding::A_Star_Algorithm(Graph, source, target);
			}
			vector<vec3> PathFinding::A_Star_Algorithm(std::map<vec3, pair<node*, vector<node*>>,
				std::function<bool(const vec3& lhs, const vec3& rhs)>>
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
			vector<vec3> PathFinding::A_Star_Grid(MinimapData& minimapData,
				vec3 source, vec3 target)
			{
				// Create grid graph
				vector<node> NewGraphNodes;
				int Height = minimapData.Height, Width = minimapData.Width;
				NewGraphNodes.resize(minimapData.Height*minimapData.Width);
				vector<vec3> Neighbors =
				{	vec3(1,0,0), vec3(-1,0,0),
					vec3(0,0,1), vec3(0,0,-1),
					vec3(1,0,1), vec3(-1,0,1),
					vec3(-1,0,1), vec3(-1,0,-1)
				};
				for (auto& n : Neighbors)
				{
					n *= 1;
				}
				vec3 Position = vec3(ConvertToArray(200, 200, 300, 300, source.x, source.z) % Width
					, 0, ConvertToArray(200, 200, 300, 300, source.x, source.z) / Width);
				vec3 targetPos = vec3(ConvertToArray(200, 200, 300, 300, target.x, target.z) % Width
					, 0, ConvertToArray(200, 200, 300, 300, target.x, target.z) / Width);
				// stuck in a fucking wall
				if (minimapData.Map[(int)targetPos.x + (int)targetPos.z * Width] == u8vec4(115, 77, 38, 255))
					return vector<vec3>();
				// algorithm
				//auto cmp = [](node* lhs, node* rhs)->bool { // O(nlog(n))
				//	return lhs->f > rhs->f; // reversed due to priority queue specification
				//};
				//priority_queue<node*,std::vector<node*>,decltype(cmp)> openList(cmp);
				//priority_queue<node*> openList;
				list<node*> openList;

				list<node*> closedList;

				node* StartNode = &NewGraphNodes[Position.x + Position.z * Width];
				(*StartNode).g = 0; // sets values for the starting node
				(*StartNode).h = glm::distance(Position, targetPos);
				(*StartNode).f = (*StartNode).g + (*StartNode).h;
				(*StartNode).pos = Position;
				openList.push_back(StartNode); // adds to the open list
				bool PathFound = false;
				while ((openList.size() > 0) && !PathFound)
				{
					///// sort the open list to find the smallest element
					///openList.sort([](const node* lhs, const node* rhs)->bool { // O(nlog(n)) * log n << n
					///	return lhs->f < rhs->f;
					///});
					auto min = openList.begin();
					for (auto it = openList.begin(); it != openList.end(); it++)
					{
						if ((*it)->f < (*min)->f)
						{
							min = it;
						}
					}
					///vec3 BestPosition = openList.front()->pos;
					vec3 BestPosition = (*min)->pos;
					//int Position = ConvertToArray(200, 200, 300, 300, BestNodePos.x, BestNodePos.z);
					node* BestNode = &NewGraphNodes[BestPosition.x + (int)BestPosition.z * minimapData.Width];
					if (BestPosition == targetPos)
					{
						break;
					}
					///openList.pop_front();
					openList.erase(min);

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

					for (auto offset : Neighbors)
					{
						//int Position = ConvertToArray(200, 200, 300, 300, BestNodePos.x + offset.x, BestNodePos.z + offset.z);
						vec3 OffsetPosition = BestPosition + offset;
						// obstacle
						if (minimapData.Map[(int)OffsetPosition.x + (int)(OffsetPosition.z) * Width] == u8vec4(115, 77, 38, 255))
						{
							continue;
						}
						node* n = &NewGraphNodes[OffsetPosition.x + (int)OffsetPosition.z * minimapData.Width];
						if (n->List == 0) // new node
							*n = node(OffsetPosition);
						if ((*n).List == CLOSEDLIST)
							continue;
						if ((*n).List != OPENLIST)
						{
							(*n).List = OPENLIST;
							openList.push_back(n);
						}
						else
						{
							int i = 0;
						}
						if (OffsetPosition == targetPos)
						{
							(*n).parent = BestNode;
							PathFound = true;
							break;
						}
						float g = (*BestNode).g + distance(BestPosition, OffsetPosition);
						float h = distance(targetPos, OffsetPosition);
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
				node currentNode = NewGraphNodes[ConvertToArray(200, 200, 300, 300, target.x, target.z)];
				// if no path found
				if (currentNode.parent == nullptr)
				{
					return returnPath;
				}
				// path found
				do {
					returnPath.push_back(ConvertToWorldCoords(200, 200, 300, 300, currentNode.pos));
					currentNode = *currentNode.parent;
				} while (currentNode.parent != nullptr);
				returnPath.push_back(ConvertToWorldCoords(200, 200, 300, 300, currentNode.pos));

				return returnPath;
			}
#undef OPENLIST 
#undef CLOSEDLIST 
#pragma endregion PathFinding
#pragma region TSP
			list<vec3> TSP::Greedy(vector<vec3> UnorderedList)
			{
				list<vec3> OrderedList;
				vec3 shortest = UnorderedList[0];
				UnorderedList.erase(UnorderedList.begin() + 0);
				OrderedList.push_back(shortest);
				while (true)
				{
					// end condition
					if (UnorderedList.size() == 0) break;
					//
					double minDistance = 1000000.0f;
					size_t bestIndex = 0;
					for (size_t i = 0; i < UnorderedList.size(); i++)
					{
						// check if best distance achieved
						int currentDistance;
						if ((currentDistance = glm::distance(
							shortest,
							UnorderedList[i])) < minDistance)
						{
							minDistance = currentDistance;
							bestIndex = i;
						}
					}
					shortest = UnorderedList[bestIndex];
					OrderedList.push_back(UnorderedList[bestIndex]);
					UnorderedList.erase(UnorderedList.begin() + bestIndex);
				}
				return OrderedList;
			}
			list<vec3> TSP::Christofides(vector<vec3> UnorderedList)
			{
				using node = pair<float, pair<vec3, vec3>>;
				vector<vector<pair<float, pair<vec3,vec3>>>> Connections;
				Connections.resize(UnorderedList.size());
				for (auto& col : Connections) {
					col.resize(UnorderedList.size(), 
					{
						make_pair(numeric_limits<float>::infinity(),
						make_pair(vec3(),vec3()))
					});
				}
				// O(n²)
				for (int i = 0; i < UnorderedList.size(); i++)
				{
					for (int j = i+1; j < UnorderedList.size(); j++)
					{
						Connections[i][j] = 
						{
							make_pair(glm::distance(UnorderedList[i], UnorderedList[j]),
							make_pair(UnorderedList[i], UnorderedList[j]))
						};
					}
					std::sort(Connections[i].begin(), Connections[i].end(), [](const node& n1, const node& n2) 
						-> bool
					{
						return n1.first < n2.first;
					});
				}
				using Comparator = std::function<bool(const vec3&, const vec3&)>;
				map<vec3, vec3, Comparator> SpanningTree([](const vec3& lhs,const vec3& rhs)->bool {
					if (lhs.x == rhs.x) {
						if (lhs.y == rhs.y) {
							return lhs.z < rhs.z;
						}
						return lhs.y < rhs.y;
					}
					return lhs.x < rhs.x;
				});
				for (auto i = Connections.begin(); i != Connections.end()-1; i++)
				{
					SpanningTree[(*i)[0].second.first] = (*i)[0].second.second;
				}

				// missing area
				/*
				
				*/

				list<vec3> OrderedList;
				OrderedList.push_back(SpanningTree.begin()->first);
				decltype(SpanningTree.begin()) next;
				while ((next = SpanningTree.find(OrderedList.back()))!=SpanningTree.end())
				{
					OrderedList.push_back(next->second);
				}
				return OrderedList;
			}
			list<vec3> TSP::DynamicProgramming(vector<vec3> UnorderedList)
			{
				vector<vector<float>> DPMatrix;
				DPMatrix.resize(UnorderedList.size());
				for (auto col : DPMatrix) {
					col.resize(UnorderedList.size(), numeric_limits<float>::infinity());
				}
				for (int i = 0; i < UnorderedList.size(); i++)
				{
					for (int j = 0; j < UnorderedList.size(); j++)
					{
						if ( i == j ) continue;
						float Distance;
						if ((Distance = glm::distance(UnorderedList[i],UnorderedList[j])) < DPMatrix[i][j])
						{
							DPMatrix[i][j] = Distance;
						}
					}
				}
				return list<vec3>();
			}
#pragma endregion TSP
		}
		
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
	map<vec3, vector<pair<vec3, float>>> graph; // each node has his siblings with the distance to them
	vector<vec3> backTrack; // sorted from End to Start
	map<float, vec3> ActiveNodes; // sorted by distance, all untouched nodes


}
