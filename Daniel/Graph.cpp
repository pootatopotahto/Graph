#include "Graph.h"
#include <tuple>
#include <iomanip>
#include <algorithm>

std::istream& operator>>(std::istream &is, Graph &gp) {
    int v1, v2, weight;

    for (int i=0; i < gp.edge_count; ++i){
        if (!(is >> v1 >> v2 >> weight)) {
            if (!is.eof())
                throw std::runtime_error("operator>> - Error reading edge data");
            else  
                break;
        }
        gp.insertEdge(v1,v2, weight);       
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const Graph &gp) {
    os << "G= (" << gp.vert_count << ", " << gp.edge_count << ") "<< std::endl;
    for (int i=0; i < gp.vert_count; ++i){
        for(int j=0; j < gp.vert_count; ++j){
            if (gp.isEdge(i, j))
            os << i << " " << j << " "<< gp.getWeight(i,j) << std::endl;
        }
    }
    return os;
}

void Graph::printBFSTable(int source) {
    if (table.size() != 3)
        throw std::runtime_error("printBFSTable - Invalid Table");

    for (int i=0; i < vert_count; ++i) {
        std::cout << "[" << std::setw(3) << std::setfill(' ') << i << "]: " << "dist: " 
                  << std::setw(2) << std::setfill(' ') << table["dist"][i] << "   pred: " 
                  << std::setw(2) << std::setfill(' ') << table["pred"][i] << std::endl;
    }
}

void Graph::printBFSPath(int s, int d) {
    std::cout << this->size() << std::endl;
    if (table.size() != 3)
        throw std::runtime_error("printBFSPath - Invalid Table");
    if (table["dist"][d] == std::numeric_limits<int>::infinity()) {
        std::cout << "No such path" << std::endl;
        return;
    }
    std::vector<int> path;
    int curr = d;

    while (curr != s) {
        path.insert(path.begin(), curr);
        curr = table["pred"][curr];
    }
    path.insert(path.begin(), s);

    for (const auto& vert : path)
        std::cout << "v" << vert << " ";
    std::cout << std::endl;
}

void Graph::printMostDistant(int s) {
    if (s < 0 or s > vert_count - 1)
        throw std::invalid_argument("printMostDistant - Invalid Source");
    if (table.size() != 3)
        throw std::runtime_error("printMostDistant - Invalid Table");

    int max = -1;
    std::vector<int> indices;

    for (int i=0; i < vert_count; ++i) {
        if (table["dist"][i] > max) {
            max = table["dist"][i];
            indices.clear();
            indices.emplace_back(i);
        } 
        else if (table["dist"][i] == max)
            indices.emplace_back(i);
    }
    for (int index : indices) {
        std::cout << "v" << index << " ";
    }
    std::cout << "dist=" << max - s << std::endl;
}

bool Graph::isConnected(void) {
    if (table.size() != 3)
        throw std::runtime_error("isConnected - Invalid Table");

    if (vert_count == 0)
        return false;
    
    for (int i=0; i < vert_count; ++i) {
        if (table["color"][i] == 0)
            return false;
    }
    return true;
} 

void Graph::printDFSTable(void) {
    if (table.size() != 4)
        throw std::runtime_error("printDFSTable - Invalid Table");

    for (int i=0; i < vert_count; ++i) {
        std::cout << "[" << std::setw(3) << std::setfill(' ') << i << "]: "
                  << "dist: " << std::setw(2) << std::setfill(' ') << -1
                  << "   pred: " << std::setw(2) << std::setfill(' ') << table["pred"][i]
                  << "  (" << table["disc"][i] << "," << table["f"][i] << ")" << std::endl;
    }
}

void Graph::printTopologicalSort(void) {
    if (table.size() != 4)
        throw std::runtime_error("printTopologicalSort - Invalid Table");

    std::vector<std::pair<int, int>> topo_sort;

    for (int i=0; i < vert_count; ++i)
        topo_sort.emplace_back(std::make_pair(table["f"][i], i));

    std::sort(topo_sort.begin(), topo_sort.end(), std::greater<std::pair<int, int>>());

    for (int i=0; i < topo_sort.size(); ++i) {
        std::cout << "v" << topo_sort[i].second;

        if (i != topo_sort.size() - 1)
            std::cout << " > ";
    }
    std::cout << std::endl;
}

void Graph::printDFSParenthesization(void) {
    if (table.size() != 4)
        throw std::runtime_error("printDFSParenthesization - Invalid Table");

    std::vector<std::tuple<int, int, int>> paren;

    for (int i=0; i < vert_count; ++i) {
        paren.emplace_back(std::make_tuple(table["disc"][i], i, 0));
        paren.emplace_back(std::make_tuple(table["f"][i], i, 1));
    }
    std::sort(paren.begin(), paren.end());

    for (const auto& x : paren) {
        if (std::get<2>(x) == 0)
            std::cout << "(v" << std::get<1>(x) << " ";
        else
            std::cout << "v" << std::get<1>(x) << ") ";
    }
    std::cout << std::endl;
}

void Graph::classifyDFSEdges(void) {
    if (dfs_edges.size() == 0)
        throw std::runtime_error("classifyDFSEdges - No Edges");
    if (table.size() != 4)
        throw std::runtime_error("classifyDFSEdges - Invalid Table");

    for (const auto& edge : dfs_edges) {
        std::cout << "Edge (v" << edge.first << ",v" << edge.second << ") is a ";
        if (table["disc"][edge.second] > table["disc"][edge.first] and table["f"][edge.second] < table["f"][edge.first])
            std::cout << "tree/forward edge" << std::endl;
        if (table["disc"][edge.second] < table["disc"][edge.first] and table["f"][edge.second] > table["disc"][edge.first])
            std::cout << "back edge" << std::endl;
        if (table["f"][edge.second] < table["disc"][edge.first] or table["disc"][edge.second] > table["f"][edge.first])
            std::cout << "cross edge" << std::endl;
    }
}