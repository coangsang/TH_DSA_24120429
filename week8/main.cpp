#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

//1
vector<vector<int>> convertMatrixToList(const string& filename)
{
    ifstream fin(filename);
    int n;
    fin>>n;
    vector<vector<int>> mat(n,vector<int>(n));
    for (int i =0;i<n;i++)
    {
        for (int j =0;j<n;j++)
        {
            fin>>mat[i][j];
        }
    }
    fin.close();
    //Vector 2D list: n vector, mỗi vector là 1 vector có 1 phần tử
    //đều mang giá trị không;
    vector<vector<int>> ls(n,vector<int>(1,0));
    for (int i =0;i<n;i++)
    {
        for (int j =0;j<n;j++)
        {
            if (mat[i][j])
            {
                ls[i][0]++;
                ls[i].push_back(j);
            }
        }
    }
    ls.insert(ls.begin(),{n});
    return ls;
}
//2
vector<vector<int>> convertListToMatrix(const string& filename)
{
    ifstream fin(filename);
    int n;
    fin>>n;
    vector<vector<int>> mat(n, vector<int>(n,0));

    int quantity_vertices;
    int pos;
    for (int i =0;i<n;i++)
    {
        fin>>quantity_vertices;
        while (quantity_vertices--)
        {
            fin>>pos;
            mat[i][pos] = 1;
        }
    }
    fin.close();
    mat.insert(mat.begin(),{n});
    return mat;
}
//3
bool isDirected(const vector<vector<int>>& iadjMatrix)
{   
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.empty()) return true;
    if (adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }

    int num_vertex= adjMatrix.size();
    for (int i =0;i<num_vertex;i++)
        for (int j=i+1;j<num_vertex;j++)
            if (adjMatrix[i][j]!=adjMatrix[j][i])
                return true;
    return false;
}

int countVertices(const vector<vector<int>>& iadjMatrix)
{   vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }
    return adjMatrix.size();
}
int countEdges(const vector<vector<int>>& iadjMatrix)    
{
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }
    if (adjMatrix.empty()) return 0;
    int num_vertex = adjMatrix.size();
    int count = 0;
    if(!isDirected(adjMatrix))
    {
        for (int i =0;i<num_vertex;i++)
        {
            for (int j=i;j<num_vertex;j++)
            {
                if (adjMatrix[i][j])
                    count++;
            }
        }
        return count;
    }
    for (int i = 0; i < num_vertex; i++)
    {
        for (int j = 0; j < num_vertex; j++)
        {
            if (adjMatrix[i][j])
                count++;
        }
    }
    return count;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& iadjMatrix)
{
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }

    if (adjMatrix.empty()) return {};
    bool isIsolatedVertex=false;
    vector<int> result;
    int r = adjMatrix.size();
    int c = adjMatrix[0].size();
    for (int i =0;i<r;i++)
    {
        isIsolatedVertex = true;
        for (int j=0;j<c;j++)
            if (adjMatrix[i][j]||adjMatrix[j][i])
            {
                isIsolatedVertex = false;
                break;
            }

        if (isIsolatedVertex)
            result.push_back(i);
    }
    return result;
}

// Undirected Graph.
bool isCompleteGraph(const vector<vector<int>>& iadjMatrix)
{
    //Input không có trường hợp này
    //if (isDirected(adjMatrix)) return false;
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }

    int r = adjMatrix.size();
    int c = adjMatrix[0].size();
    for (int i =0;i<r;i++)
    {
        for (int j=i+1;j<c;j++)
        {
            if (!adjMatrix[i][j])
                return false;
        }
    }
    return true;
}
//kiểm tra xem có tồn tại vòng tự aka self-loop không 
bool isExistSelfLoop(const vector<vector<int>> &iadjMatrix)
{
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }

    for (int i = adjMatrix.size()-1;i>=0;i--)
    {
        if (adjMatrix[i][i])
            return true;
    }
    return false;
}

// Undirected Graph
bool isBipartite(const vector<vector<int>>& iadjMatrix)
{
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }

    if (isDirected(adjMatrix)) return false;
    if (adjMatrix.empty()) return true;
    if (isExistSelfLoop(adjMatrix)) return false;

    int num_vertex = adjMatrix.size();
    //Có 3 màu 1, -1, 0, với 0 là trắng
    vector<int> colour(num_vertex,0);
    for (int u = 0;u<num_vertex;u++)
    {
        queue<int> q;
        q.push(u);
        if (colour[u]==0)
            colour[u] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v = 0;v<num_vertex;v++)
            {
                if (adjMatrix[u][v])
                {
                    if (colour[v]==0)
                    {   
                        q.push(v);
                        colour[v] = -colour[u];
                    }
                    else if (colour[v]==colour[u])
                        return false;
                }
            }
        }
    }
    return true;
}


bool colouringNcheckBipartite(const vector<vector<int>> &adjMatrix,vector<int> &colour)
{


    if (isDirected(adjMatrix)) return false;
    if (adjMatrix.empty()) return true;
    if (isExistSelfLoop(adjMatrix)) return false;

    int num_vertex = adjMatrix.size();
    //Có 3 màu 1, -1, 0, với 0 là trắng
    for (int u = 0;u<num_vertex;u++)
    {
        queue<int> q;
        q.push(u);
        if (colour[u]==0)
            colour[u] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v = 0;v<num_vertex;v++)
            {
                if (adjMatrix[u][v])
                {
                    if (colour[v]==0)
                    {   
                        q.push(v);
                        colour[v] = -colour[u];
                    }
                    else if (colour[v]==colour[u])
                        return false;
                }
            }
        }
    }
    return true;
}
int getNumEdge( const vector<vector<int>> &adjMatrix, const vector<int> &listVertex)
{
    int num_vertex = adjMatrix.size();
    int num_edge = 0;
    for (const int& x:listVertex)
        for (int i =0;i<num_vertex;i++)
            if (adjMatrix[x][i])
                num_edge++;
    return num_edge;
}
bool isCompleteBipartite(const vector<vector<int>>& iadjMatrix)
{
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }


    int num_vertex = adjMatrix.size();
    vector<int> colour(num_vertex,0);
    if (!colouringNcheckBipartite(adjMatrix,colour))
        return false;
    vector<int> v1;
    vector<int> v2;
    for (int i =0;i<num_vertex;i++)
        if (colour[i]==1)
            v1.push_back(i);
        else
            v2.push_back(i);

    /*do đã đảm bảo đồ thị là bipartite vậy nên các đỉnh thuộc v1 là cô lập hoặc kề với 
        các đỉnh thuộc v2*/
    //Vì là đồ thị vô hướng nên số cạnh list đỉnh v1 = số cạnh list đỉnh v2
    return (v1.size()*v2.size()==getNumEdge(adjMatrix,v1));
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& iadjMatrix) 
{

    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }
    if (adjMatrix.empty()) return {};
    int num_vertex = adjMatrix.size();

    vector<vector<int>> result(num_vertex, vector<int>(num_vertex,0));
    for ( int i =0;i<num_vertex;i++)
    {
        result[i][i] = adjMatrix[i][i];
        for (int j = i+1;j<num_vertex;j++)
        {
            if (adjMatrix[i][j]||adjMatrix[j][i])
            {
                result[i][j]=1;
                result[j][i]=1;
            }
        }
    }
    return result;
}

/*5. Generate a complement graph from a given undirected graph and output its adjacency matrix (*undi-
rected graph).*/
//undirected graph
vector<vector<int>> getComplementGraph(const vector<vector<int>>& iadjMatrix)
{
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }

    int num_vertex = adjMatrix.size();
    vector<vector<int>> result(num_vertex, vector<int> (num_vertex,1));
    for (int i = 0;i<num_vertex;i++) 
    {
        for (int j = i;j<num_vertex;j++)
        {
            if (adjMatrix[i][j])
            {
                result[i][j] = result[j][i]=0;
            }
        }
    }
    return result;
}

vector<int> findEulerCycleUndirected(const vector<vector<int>> &adjMatrix) {
    
    int n = adjMatrix.size();
    vector<vector<int>> adjMatrix_cpy = adjMatrix;
    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            degree[i] += adjMatrix_cpy[i][j];
        if (degree[i] % 2 != 0)
            return {};
    }

    int start = -1;
    for (int i = 0; i < n; i++)
        if (degree[i] > 0) {
            start = i;
            break;
        }
    if (start == -1) return {};

    vector<int> cycle;
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top();
        bool hasEdge = false;
        for (int v = 0; v < n; v++) {
            if (adjMatrix_cpy[u][v] > 0) {
                adjMatrix_cpy[u][v]--;
                adjMatrix_cpy[v][u]--;
                st.push(v);
                hasEdge = true;
                break;
            }
        }
        if (!hasEdge) {
            cycle.push_back(u);
            st.pop();
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adjMatrix_cpy[i][j] > 0)
                return {};
    
    reverse(cycle.begin(), cycle.end());
    return cycle;
}

vector<int> findEulerCycleDirected(const vector<vector<int>> &adjMatrix) {

    int n = adjMatrix.size();
    vector<vector<int>> adjMatrix_cpy = adjMatrix;
    vector<int> inDeg(n, 0), outDeg(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) {
            outDeg[i] += adjMatrix_cpy[i][j];
            inDeg[j] += adjMatrix_cpy[i][j];
        }
        if (inDeg[i] != outDeg[i])
            return {};
    }
    

    int start = -1;
    for (int i = 0; i < n; i++)
        if (outDeg[i] > 0) {
            start = i;
            break;
        }
    if (start == -1) return {};

    vector<int> cycle;
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int u = st.top();
        bool hasEdge = false;
        for (int v = 0; v < n; v++) {
            if (adjMatrix_cpy[u][v] > 0) {
                adjMatrix_cpy[u][v]--;
                st.push(v);
                hasEdge = true;
                break;
            }
        }
        if (!hasEdge) {
            cycle.push_back(u);
            st.pop();
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adjMatrix_cpy[i][j] > 0)
                return {};
    
    reverse(cycle.begin(), cycle.end());
    return cycle;
}

/*6. Determine the Euler cycle from a given graph using Hierholzer’s Algorithm*/
vector<int> findEulerCycle(const vector<vector<int>>& iadjMatrix)
{
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }
    //nếu đồ thị rỗng
    if (adjMatrix.empty()) return {};
    //chia trường hợp 2 loại đồ thị
    if (isDirected(adjMatrix))
        return findEulerCycleDirected(adjMatrix);
    return findEulerCycleUndirected(adjMatrix);
}


void dfsSpanningTree_AUX(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& spanningTree) {
    visited[u] = true;
    int n = adjMatrix.size();
    for (int v = 0; v < n; ++v) {
        if (adjMatrix[u][v] && !visited[v]) {
            spanningTree[u].push_back(v);
            spanningTree[v].push_back(u); // Vì đồ thị vô hướng
            dfsSpanningTree_AUX(v, adjMatrix, visited, spanningTree);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& iadjMatrix, int start) {
    
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> spanningTree(n);

    dfsSpanningTree_AUX(start, adjMatrix, visited, spanningTree);

    return spanningTree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& iadjMatrix, int start) {
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }
    
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<vector<int>> spanningTree(n);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && !visited[v]) {
                visited[v] = true;
                spanningTree[u].push_back(v);
                spanningTree[v].push_back(u); // Đồ thị vô hướng
                q.push(v);
            }
        }
    }

    return spanningTree;
}

void dfs_isConnected_AUX(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited) {
    visited[u]  = true;
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        if (adjMatrix[u][i] && !visited[i]) {
            dfs_isConnected_AUX(i, adjMatrix, visited);
        }
    }
}

// Kiểm tra có đường đi từ u đến và ngược lại
bool isConnected(int u, int v, const vector<vector<int>>& iadjMatrix) {
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }
    
    int n = adjMatrix.size();
    if (u < 0 || u >= n || v < 0 || v >= n) return false;

    vector<bool> visited(n, false);
    dfs_isConnected_AUX(u, adjMatrix, visited);

    if (visited[v]) return true;

    // Nếu là đồ thị có hướng và không có đường u->v, xét v->u
    if (isDirected(adjMatrix)) {
        //gán false cho mọi phần tử trong visited;;
        fill(visited.begin(), visited.end(), false);
        dfs_isConnected_AUX(v, adjMatrix, visited);
        return visited[u];
    }

    return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& iadjMatrix) {
    
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }

    int n = adjMatrix.size();
    vector<int> distance(n, INT_MAX); // Mảng khoảng cách
    vector<int> parent(n, -1); // Mảng lưu đỉnh cha
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
    //pq: khoảng cách, đỉnh

    // Khởi tạo khoảng cách từ đỉnh bắt đầu
    distance[start] = 0;
    pq.push({0, start});

    // Xử lý hàng đợi
    while (!pq.empty()) {
        int dist = pq.top().first; // khoảng cách hiện tại đến u
        int u = pq.top().second;   // ddỉnh hiện tại
        pq.pop();

        //đã đến đỉnh đích, dừng lại
        if (u == end) break;

        //khoảng cách không tối ưu, bỏ qua
        if (dist > distance[u]) continue;

        // Duyệt các đỉnh kề
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] && distance[u] + adjMatrix[u][v] < distance[v]) {
                distance[v] = distance[u] + adjMatrix[u][v]; //đường đi tốt hơn để đến v
                parent[v] = u; // Lưu đỉnh cha
                pq.push({distance[v], v});
            }
        }
    }

    // dựng đường đi
    vector<int> path;
    if (distance[end] != INT_MAX) {
        for (int at = end; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end()); //đảo ngược để có thứ tự start->end;
    }
    return path;
}


vector<int> bellmanFord(int start, int end, const vector<vector<int>>& iadjMatrix) {
    vector<vector<int>> adjMatrix = iadjMatrix;
    if (adjMatrix.size()>0 && adjMatrix.size()!=adjMatrix[0].size())
    {
        adjMatrix.erase(adjMatrix.begin());
    }
    
    int n = adjMatrix.size();
    vector<int> distance(n, INT_MAX);
    vector<int> parent(n, -1);
    
    //khởi tạo khoảng cách từ đỉnh bắt đầu
    distance[start] = 0;
    
    //relax tất cả các cạnh |V|-1 lần
    for (int i = 0; i< n-1; i++) {
        for (int u = 0;u< n; u++) {
            for (int v= 0;v<n; v++) {
                if (adjMatrix[u][v]!= 0&&distance[u]!= INT_MAX && 
                    distance[u]+ adjMatrix[u][v]< distance[v]) {
                    distance[v]= distance[u]+ adjMatrix[u][v];
                    parent[v]= u;
                }
            }
        }
    }
    
    //kiểm tra chu trình âm
    for (int u = 0; u< n; u++) {
        for (int v = 0; v< n; v++) {
            if (adjMatrix[u][v]!=0&&distance[u]!=INT_MAX && 
                distance[u]+adjMatrix[u][v]<distance[v]) {
                return vector<int>(); // Có chu trình âm
            }
        }
    }
    //dựng đường đi
    vector<int> path;
    if (distance[end]!=INT_MAX) {
        for (int at=end; at!= -1; at= parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(),path.end());
    }
    return path;
}
