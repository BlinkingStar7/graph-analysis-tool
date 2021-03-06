#ifndef GRAPH_H
#define GRAPH_H

#include <list>
// TODO: Vector can be much more efficient type than list. Consider about it.
#include <vector>
#include <unordered_map>

namespace snu {

	class Graph; // graph having common aspects
	class DSGraph; //   directed simple graph
	class USGraph; // undirected simple graph
	//class DMGraph; //   directed multigraph, not implemented
	//class UMGraph; // undirected multigraph, not implemented

	class Graph {
	protected:
		typedef int Vid; // vertex id
		typedef int Eid; // edge   id
		typedef std::string Vlabel; // vertex label
		typedef std::string Elabel; // edge   label
		typedef int Weight; // integer type weight, other types of weight can be added

		class Vertex;
		class Edge;
		class Label_of_Vertices;
		class Label_of_Edges;

		class Vertex {
		public:
			Vid id;
			std::list <Label_of_Vertices *> labels;
			std::list <Edge *> edges;
			unsigned long long indegree;
		};

		class Edge {
		public:
			Eid id;
			std::list <Label_of_Edges *> labels;
			Vertex *from;
			Vertex *to;
			Weight wgt;
			// If graph is undirected, then there is no difference between from and to.
		};

		class Label_of_Vertices {
		public:
			Vlabel label;
			std::list <Vertex *> vertices;
		};

		class Label_of_Edges {
		public:
			Elabel label;
			std::list <Edge *> edges;
		};
	
		std::unordered_map <Vid, Vertex *> id_to_vertex;
		std::unordered_map <Eid, Edge *>   id_to_edge;

		std::unordered_map <Vlabel, Label_of_Vertices *> vlabel_to_class;
		std::unordered_map <Elabel, Label_of_Edges *>    elabel_to_class;

		unsigned long long negative_edge_num;

		//std::unordered_map <std::pair <VId, VId>, Edge *> id_pair_to_edge;

		Graph(); // prevent from creating Graph class and allow creating graph in subclass
		~Graph(); // destructor

		int add_vertex(Vid id, unsigned int num, Vlabel lbl[]); // add vertex, array version
		int add_vertex(Vid id, std::vector <Vlabel> *lbl); // vector version
		// if vertex is created normally, then return 0
		// if error occurs, then return 1

		// directed form of add_edge
		int add_edge(Eid id, unsigned int num, Elabel lbl[], Vid from, Vid to, Weight wgt); // array version
		// if edge is created normally, then return 0
		// if error occurs, then return 1
	};

	class DSGraph: public Graph { // directed simple graph
	public:
		int add_edge(Eid id, unsigned int num, Elabel lbl[], Vid from, Vid to, Weight wgt); // array version
		int add_edge(Eid id, std::vector <Elabel> *lbl, Vid from, Vid to, Weight wgt); // vector version

		// friend function
		friend void basic_stat(DSGraph *graph, struct DSResult *result);
		friend void count_stat(DSGraph *graph, struct DSResult *result);
		friend DSGraph *parse_snu_DSGraph(std::string file_path);
		friend DSGraph *parse_net_DSGraph(std::string file_path);
		friend DSGraph *parse_snap_DSGraph(std::string file_path);
		friend void make_plot(DSGraph *graph);
	};

	class USGraph: public Graph { // undirected simple graph
	public:
		int add_edge(Eid id, unsigned int num, Elabel lbl[], Vid from, Vid to, Weight wgt); // array version
		int add_edge(Eid id, std::vector <Elabel> *lbl, Vid from, Vid to, Weight wgt); // vector version

		// friend function
		friend void basic_stat(USGraph *graph, struct USResult *result);
		friend void count_stat(USGraph *graph, struct USResult *result);
		friend void make_plot(USGraph *graph);
	};


	// class DMGraph: public Graph {};
	// class UMGraph: public Graph {};
}

#endif // GRAPH_H