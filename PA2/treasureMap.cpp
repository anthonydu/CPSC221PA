#include "treasureMap.h"

#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG& baseim, const PNG& mazeim,
                         pair<int, int> s) {
  /* YOUR CODE HERE */
  base = baseim;
  maze = mazeim;
  start = s;
}

void treasureMap::setGrey(PNG& im, pair<int, int> loc) {
  /* YOUR CODE HERE */
  RGBAPixel* pixel = im.getPixel(loc.first, loc.second);
  pixel->r = 2 * (pixel->r / 4);
  pixel->g = 2 * (pixel->g / 4);
  pixel->b = 2 * (pixel->b / 4);
}

void treasureMap::setLOB(PNG& im, pair<int, int> loc, int d) {
  /* YOUR CODE HERE */
  RGBAPixel* pixel = im.getPixel(loc.first, loc.second);
  pixel->r = pixel->r >> 2 << 2;
  pixel->g = pixel->g >> 2 << 2;
  pixel->b = pixel->b >> 2 << 2;
  pixel->r |= (d & 0b110000) >> 4;
  pixel->g |= (d & 0b001100) >> 2;
  pixel->b |= (d & 0b000011) >> 0;
  // cout << bitset<8>(d) << " " << bitset<8>(pixel->r) << " "
  //      << bitset<8>(pixel->g) << " " << bitset<8>(pixel->b) << " " << endl;
}

PNG treasureMap::renderMap() {
  /* YOUR CODE HERE */
  PNG img = base;
  vector<vector<bool>> visited;
  vector<vector<int>> distance;
  for (int i = 0; i < img.width(); i++) {
    visited.push_back(vector<bool>(img.height(), false));
    distance.push_back(vector<int>(img.height()));
  }
  Queue<pair<int, int>> q;
  visited[start.first][start.second] = true;
  distance[start.first][start.second] = 0;
  setLOB(img, start, 0);
  q.enqueue(start);
  pair<int, int> curr;
  while (!q.isEmpty()) {
    curr = q.peek();
    q.dequeue();
    for (auto p : neighbors(curr)) {
      if (good(visited, curr, p)) {
        visited[p.first][p.second] = true;
        distance[p.first][p.second] = distance[curr.first][curr.second] + 1;
        setLOB(img, p, distance[p.first][p.second]);
        q.enqueue(p);
      }
    }
  }
  return img;
}

PNG treasureMap::renderMaze() {
  /* YOUR CODE HERE */
  PNG img = base;
  vector<vector<bool>> visited;
  for (int i = 0; i < img.width(); i++) {
    visited.push_back(vector<bool>(img.height(), false));
  }
  Queue<pair<int, int>> q;
  visited[start.first][start.second] = true;
  setGrey(img, start);
  q.enqueue(start);
  pair<int, int> curr;
  while (!q.isEmpty()) {
    curr = q.peek();
    q.dequeue();
    for (auto p : neighbors(curr)) {
      if (good(visited, curr, p)) {
        visited[p.first][p.second] = true;
        setGrey(img, p);
        q.enqueue(p);
      }
    }
  }
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (start.first - 3 + i >= 0 && start.second - 3 + j >= 0) {
        img.getPixel(start.first - 3 + i, start.second - 3 + j)->r = 255;
        img.getPixel(start.first - 3 + i, start.second - 3 + j)->g = 0;
        img.getPixel(start.first - 3 + i, start.second - 3 + j)->b = 0;
      }
    }
  }
  return img;
}

bool treasureMap::good(vector<vector<bool>>& v, pair<int, int> curr,
                       pair<int, int> next) {
  /* YOUR CODE HERE */
  if (next.first < 0 || next.first >= base.width()) return false;
  if (next.second < 0 || next.second >= base.height()) return false;
  if (v[next.first][next.second]) return false;
  if ((*maze.getPixel(curr.first, curr.second) !=
       *maze.getPixel(next.first, next.second)))
    return false;
  return true;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr) {
  /* YOUR CODE HERE */
  vector<pair<int, int>> n;
  n.push_back(pair<int, int>(curr.first - 1, curr.second));
  n.push_back(pair<int, int>(curr.first, curr.second + 1));
  n.push_back(pair<int, int>(curr.first + 1, curr.second));
  n.push_back(pair<int, int>(curr.first, curr.second - 1));
  return n;
}
