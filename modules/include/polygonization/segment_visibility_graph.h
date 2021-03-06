#ifndef SEGMENT_VISIBILITY_GRAPH_H
#define SEGMENT_VISIBILITY_GRAPH_H

#include <boost/graph/astar_search.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <boost/graph/graphviz.hpp>
#include <sys/time.h>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <math.h>    // for sqrt

class Segment_Visibility_Graph
{
  public:
      
    class seg_vertex
    {
    public:
        int segment_index;
        int type;
        bool reflexive;
        double p_x;
        double p_y;
        seg_vertex(int i,int t) : segment_index(i), type(t) {};
        seg_vertex(int i,int t,double x, double y) 
            : segment_index(i), type(t), p_x(x), p_y(y) {reflexive = false;};
        seg_vertex() { reflexive = false;};
    };
    class seg_edge
    {
    public:
        int segment_index;
        int segment_index2;
        double distance;
        double p_x;
        double p_y;
        double edge_weight_t; 
        seg_edge(int i, int j, double d) : segment_index(i), segment_index2(j), distance(d) {};
        seg_edge(int i, int j, double d, double x, double y) 
            : segment_index(i), segment_index2(j), distance(d), p_x(x), p_y(y) {};
        seg_edge() {};
    };
    

    typedef double cost_t;
    typedef boost::adjacency_list
        <boost::listS, boost::vecS, boost::undirectedS, 
         seg_vertex, seg_edge 
        > mygraph_t;
    typedef boost::property_map
        <mygraph_t, double seg_edge::*>::type WeightMap;
    typedef mygraph_t::vertex_descriptor vertex;
    typedef mygraph_t::edge_descriptor edge_descriptor;
    typedef mygraph_t::vertex_iterator vertex_iterator;
    typedef std::pair<int, int> edge;

    std::list<vertex> 
    get_shortest_path(
        Segment_Visibility_Graph::vertex start, 
        Segment_Visibility_Graph::vertex end );
    
    Segment_Visibility_Graph( int n_v, int n_e, float* edge_weights, edge* edge_array );
    Segment_Visibility_Graph( );
    vertex add_vertex(seg_vertex vertex_info);
    edge_descriptor add_edge(vertex v1, vertex v2);
    void add_edge(vertex v1, vertex v2, double d);
    void add_edge(vertex v1, vertex v2, double x, double y, double d);
    
    
    

    struct location
    {
      float y, x; // lat, long
    };
    
    // euclidean distance heuristic
    class distance_heuristic : public boost::astar_heuristic<mygraph_t, double>
    {
    public:
      
      distance_heuristic(mygraph_t* g, mygraph_t::vertex_descriptor goal)
        : m_graph(g), m_goal(goal) {}
      double operator()(mygraph_t::vertex_descriptor u)
      {
        double dx = (*m_graph)[m_goal].p_x - (*m_graph)[u].p_x;
        double dy = (*m_graph)[m_goal].p_y - (*m_graph)[u].p_y;
        return ::sqrt(dx * dx + dy * dy);
      }
    private:
      mygraph_t* m_graph;
      mygraph_t::vertex_descriptor m_goal;
    };
    
    struct found_goal {}; // exception for termination
    
    // visitor that terminates when we find the goal
    template <class Vertex>
    class astar_goal_visitor : public boost::default_astar_visitor
    {
    public:
      astar_goal_visitor(Vertex goal) : m_goal(goal) {}
      template <class Graph>
      void examine_vertex(Vertex u, Graph& g) {
        if(u == m_goal)
          throw found_goal();
      }
    private:
      Vertex m_goal;
    };
    
    
public:
    mygraph_t* g;
    WeightMap weightmap;// = get(edge_weight, g);
    
};

#endif