#include "decoder.h"

#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG& tm, pair<int, int> s) : start(s), mapImg(tm) {
  /* YOUR CODE HERE */
  mapImg = tm;
  start = s;
  PNG img = tm;
  vector<vector<bool>> visited;
  vector<vector<int>> distance;
  vector<vector<vector<pair<int, int>>>> path;
  for (int i = 0; i < img.width(); i++) {
    visited.push_back(vector<bool>(img.height(), false));
    distance.push_back(vector<int>(img.height()));
    path.push_back(vector<vector<pair<int, int>>>(img.width()));
  }
  Queue<pair<int, int>> q;
  visited[start.first][start.second] = true;
  distance[start.first][start.second] = 0;
  path[start.first][start.second].push_back(start);
  q.enqueue(start);
  pair<int, int> curr;
  while (!q.isEmpty()) {
    curr = q.peek();
    q.dequeue();
    for (auto p : neighbors(curr)) {
      if (good(visited, distance, curr, p)) {
        visited[p.first][p.second] = true;
        distance[p.first][p.second] = distance[curr.first][curr.second] + 1;
        auto newPath = path[curr.first][curr.second];
        newPath.push_back(p);
        path[p.first][p.second] = newPath;
        q.enqueue(p);
      }
    }
  }
  pair<int, int> treasure;
  int maxDistance = 0;
  for (int y = 0; y < img.height(); y++) {
    for (int x = 0; x < img.width(); x++) {
      if (path[x][y].size() > maxDistance) {
        maxDistance = path[x][y].size();
        treasure = pair<int, int>(x, y);
      }
    }
  }
  pathPts = path[treasure.first][treasure.second];
}

PNG decoder::renderSolution() {
  /* YOUR CODE HERE */
  PNG img = mapImg;
  for (auto p : pathPts) {
    img.getPixel(p.first, p.second)->r = 255;
    img.getPixel(p.first, p.second)->g = 0;
    img.getPixel(p.first, p.second)->b = 0;
  }
  return img;
}

PNG decoder::renderMaze() {
  /* YOUR CODE HERE */
  PNG img = mapImg;
  vector<vector<bool>> visited;
  vector<vector<int>> distance;
  for (int i = 0; i < img.width(); i++) {
    visited.push_back(vector<bool>(img.height(), false));
    distance.push_back(vector<int>(img.height()));
  }
  Queue<pair<int, int>> q;
  visited[start.first][start.second] = true;
  distance[start.first][start.second] = 0;
  setGrey(img, start);
  q.enqueue(start);
  pair<int, int> curr;
  while (!q.isEmpty()) {
    curr = q.peek();
    q.dequeue();
    for (auto p : neighbors(curr)) {
      if (good(visited, distance, curr, p)) {
        visited[p.first][p.second] = true;
        distance[p.first][p.second] = distance[curr.first][curr.second] + 1;
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

void decoder::setGrey(PNG& im, pair<int, int> loc) {
  /* YOUR CODE HERE */
  RGBAPixel* pixel = im.getPixel(loc.first, loc.second);
  pixel->r = 2 * (pixel->r / 4);
  pixel->g = 2 * (pixel->g / 4);
  pixel->b = 2 * (pixel->b / 4);
}

pair<int, int> decoder::findSpot() {
  /* YOUR CODE HERE */
  return pathPts.back();
}

int decoder::pathLength() {
  /* YOUR CODE HERE */
  return pathPts.size();
}

bool decoder::good(vector<vector<bool>>& v, vector<vector<int>>& d,
                   pair<int, int> curr, pair<int, int> next) {
  /* YOUR CODE HERE */
  if (next.first < 0 || next.first >= mapImg.width()) return false;
  if (next.second < 0 || next.second >= mapImg.height()) return false;
  if (v[next.first][next.second]) return false;
  if (!compare(*(mapImg.getPixel(next.first, next.second)),
               d[curr.first][curr.second] + 1))
    return false;
  return true;
}

vector<pair<int, int>> decoder::neighbors(pair<int, int> curr) {
  /* YOUR CODE HERE */
  vector<pair<int, int>> n;
  n.push_back(pair<int, int>(curr.first - 1, curr.second));
  n.push_back(pair<int, int>(curr.first, curr.second + 1));
  n.push_back(pair<int, int>(curr.first + 1, curr.second));
  n.push_back(pair<int, int>(curr.first, curr.second - 1));
  return n;
}

bool decoder::compare(RGBAPixel p, int d) {
  /* YOUR CODE HERE */
  return ((((p.r & 0b11) << 4) | ((p.g & 0b11) << 2) | ((p.b & 0b11) << 0)) &
          0b111111) == (d & 0b111111);
}
