/*Tree Implementations:
o	Implement binary trees, binary search trees, and AVL trees.
o	Perform tree operations such as insertion, deletion, and balancing.
o	Implement tree traversal methods (in-order, pre-order, post-order).*/
class BinaryTree {
    static class Node {
        int value;
        Node left, right;

        Node(int value) {
            this.value = value;
            left = right = null;
        }
    }

    Node root;

    // In-order Traversal
    void inOrder(Node node) {
        if (node != null) {
            inOrder(node.left);
            System.out.print(node.value + " ");
            inOrder(node.right);
        }
    }

    // Pre-order Traversal
    void preOrder(Node node) {
        if (node != null) {
            System.out.print(node.value + " ");
            preOrder(node.left);
            preOrder(node.right);
        }
    }

    // Post-order Traversal
    void postOrder(Node node) {
        if (node != null) {
            postOrder(node.left);
            postOrder(node.right);
            System.out.print(node.value + " ");
        }
    }
}
// binary search trees
class BinarySearchTree extends BinaryTree {

    // Insert into BST
    Node insert(Node node, int value) {
        if (node == null) {
            return new Node(value);
        }

        if (value < node.value) {
            node.left = insert(node.left, value);
        } else if (value > node.value) {
            node.right = insert(node.right, value);
        }

        return node; // Return unchanged node
    }

    // Delete from BST
    Node delete(Node node, int value) {
        if (node == null) {
            return null;
        }

        if (value < node.value) {
            node.left = delete(node.left, value);
        } else if (value > node.value) {
            node.right = delete(node.right, value);
        } else {
            // Node with one or no child
            if (node.left == null)
                return node.right;
            else if (node.right == null)
                return node.left;

            // Node with two children: Get the inorder successor
            node.value = minValue(node.right);
            node.right = delete(node.right, node.value);
        }

        return node;
    }

    int minValue(Node node) {
        int min = node.value;
        while (node.left != null) {
            min = node.left.value;
            node = node.left;
        }
        return min;
    }
}
//  AVL trees
class AVLTree extends BinarySearchTree {

    // Get height of the tree
    int height(Node node) {
        if (node == null) return 0;
        return 1 + Math.max(height(node.left), height(node.right));
    }

    // Get balance factor
    int getBalance(Node node) {
        if (node == null) return 0;
        return height(node.left) - height(node.right);
    }

    // Right rotation
    Node rotateRight(Node y) {
        Node x = y.left;
        Node T2 = x.right;

        x.right = y;
        y.left = T2;

        return x;
    }

    // Left rotation
    Node rotateLeft(Node x) {
        Node y = x.right;
        Node T2 = y.left;

        y.left = x;
        x.right = T2;

        return y;
    }

    // Insert with balancing
    @Override
    Node insert(Node node, int value) {
        node = super.insert(node, value);

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && value < node.left.value)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && value > node.right.value)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && value > node.left.value) {
            node.left = rotateLeft(node.left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && value < node.right.value) {
            node.right = rotateRight(node.right);
            return rotateLeft(node);
        }

        return node; // Return unchanged node
    }
}

/*2.	Graph Implementations:
o	Represent graphs using adjacency lists and adjacency matrices.
o	Implement graph traversal algorithms (BFS, DFS).
o	Implement shortest path algorithms (Dijkstra’s, Bellman-Ford).
o	Implement spanning tree algorithms (Prim’s and Kruskal’s)*/
a. Adjacency List

import java.util.*;

class GraphAdjList {
    private final Map<Integer, List<Integer>> adjList = new HashMap<>();

    public void addEdge(int u, int v) {
        adjList.computeIfAbsent(u, k -> new ArrayList<>()).add(v);
        adjList.computeIfAbsent(v, k -> new ArrayList<>()).add(u); // For undirected graph
    }

    public void printGraph() {
        for (var entry : adjList.entrySet()) {
            System.out.println(entry.getKey() + " -> " + entry.getValue());
        }
    }
}
b. Adjacency Matrix

class GraphAdjMatrix {
    private final int[][] adjMatrix;
    private final int vertices;

    public GraphAdjMatrix(int vertices) {
        this.vertices = vertices;
        adjMatrix = new int[vertices][vertices];
    }

    public void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // For undirected graph
    }

    public void printGraph() {
        for (int[] row : adjMatrix) {
            System.out.println(Arrays.toString(row));
        }
    }
2. Graph Traversal Algorithms
a. Breadth-First Search (BFS)

class BFS {
    public void bfsTraversal(GraphAdjList graph, int start) {
        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();

        queue.add(start);
        visited.add(start);

        while (!queue.isEmpty()) {
            int current = queue.poll();
            System.out.print(current + " ");

            for (int neighbor : graph.adjList.getOrDefault(current, new ArrayList<>())) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.add(neighbor);
                }
            }
        }
        System.out.println();
    }
}
b. Depth-First Search (DFS)

class DFS {
    public void dfsTraversal(GraphAdjList graph, int start) {
        Set<Integer> visited = new HashSet<>();
        dfsHelper(start, graph, visited);
        System.out.println();
    }

    private void dfsHelper(int node, GraphAdjList graph, Set<Integer> visited) {
        visited.add(node);
        System.out.print(node + " ");

        for (int neighbor : graph.adjList.getOrDefault(node, new ArrayList<>())) {
            if (!visited.contains(neighbor)) {
                dfsHelper(neighbor, graph, visited);
            }
        }
    }
}
class Dijkstra {
    public void dijkstra(int[][] graph, int start) {
        int vertices = graph.length;
        int[] dist = new int[vertices];
        boolean[] visited = new boolean[vertices];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[start] = 0;

        for (int i = 0; i < vertices - 1; i++) {
            int u = selectMinVertex(dist, visited);
            visited[u] = true;

            for (int v = 0; v < vertices; v++) {
                if (!visited[v] && graph[u][v] != 0 && dist[u] != Integer.MAX_VALUE &&
                    dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        System.out.println("Vertex\tDistance from Source");
        for (int i = 0; i < vertices; i++) {
            System.out.println(i + "\t\t" + dist[i]);
        }
    }

    private int selectMinVertex(int[] dist, boolean[] visited) {
        int min = Integer.MAX_VALUE, minIndex = -1;
        for (int i = 0; i < dist.length; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
}
4. Spanning Tree Algorithms
a. Prim’s Algorithm

class Prim {
    public void prim(int[][] graph) {
        int vertices = graph.length;
        boolean[] mstSet = new boolean[vertices];
        int[] key = new int[vertices];
        int[] parent = new int[vertices];
        Arrays.fill(key, Integer.MAX_VALUE);
        key[0] = 0;
        parent[0] = -1;

        for (int i = 0; i < vertices - 1; i++) {
            int u = selectMinKeyVertex(key, mstSet);
            mstSet[u] = true;

            for (int v = 0; v < vertices; v++) {
                if (graph[u][v] != 0 && !mstSet[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        System.out.println("Edge\tWeight");
        for (int i = 1; i < vertices; i++) {
            System.out.println(parent[i] + " - " + i + "\t" + graph[i][parent[i]]);
        }
    }

    private int selectMinKeyVertex(int[] key, boolean[] mstSet) {
        int min = Integer.MAX_VALUE, minIndex = -1;
        for (int i = 0; i < key.length; i++) {
            if (!mstSet[i] && key[i] < min) {
                min = key[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
}
b. Kruskal’s Algorithm

import java.util.*;

class Kruskal {
    static class Edge implements Comparable<Edge> {
        int src, dest, weight;

        public Edge(int src, int dest, int weight) {
            this.src = src;
            this.dest = dest;
            this.weight = weight;
        }

        @Override
        public int compareTo(Edge o) {
            return this.weight - o.weight;
        }
    }

    public void kruskal(int vertices, List<Edge> edges) {
        Collections.sort(edges);

        int[] parent = new int[vertices];
        for (int i = 0; i < vertices; i++) parent[i] = i;

        List<Edge> mst = new ArrayList<>();
        for (Edge edge : edges) {
            int root1 = find(parent, edge.src);
            int root2 = find(parent, edge.dest);

            if (root1 != root2) {
                mst.add(edge);
                union(parent, root1, root2);
            }
        }

        System.out.println("Edge\tWeight");
        for (Edge edge : mst) {
            System.out.println(edge.src + " - " + edge.dest + "\t" + edge.weight);
        }
    }

    private int find(int[] parent, int vertex) {
        if (parent[vertex] != vertex)
            parent[vertex] = find(parent, parent[vertex]);
        return parent[vertex];
    }

    private void union(int[] parent, int root1, int root2) {
        parent[root2] = root1;
    }
}
/*
