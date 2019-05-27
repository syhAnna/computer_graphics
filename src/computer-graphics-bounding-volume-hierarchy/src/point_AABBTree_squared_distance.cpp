#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

# define NODE std:: pair<double, std::shared_ptr<Object>>

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  auto priority = [](NODE left, NODE right) {
      // priority according to the distance
      return left.first > right.first;
  };

  // initialize the priority queue
  std::priority_queue<NODE, std::vector<NODE>, decltype(priority)> Queue(priority);

  // push the root to the priority queue
  double root_distance = point_box_squared_distance(query, root->box);
  Queue.push(std::make_pair(root_distance, root));

  double distance;
  sqrd = std::numeric_limits<double>::infinity();

  // loop over the priority queue
  while (!Queue.empty()) {
    NODE curr_node = Queue.top();
    std::shared_ptr<Object> subtree;
    distance = curr_node.first;
    subtree = curr_node.second;
    Queue.pop();

    if (distance < sqrd) {
      std::shared_ptr<Object> subtree_copy;
      subtree_copy = std::dynamic_pointer_cast<AABBTree> (subtree);

      if (subtree_copy == nullptr) { // leaf case
        double leaf_sqrd;
        std::shared_ptr<Object> leaf_descendant;

        if (subtree->point_squared_distance(query, min_sqrd, max_sqrd, leaf_sqrd,
                                            leaf_descendant)) {
          if (leaf_sqrd < sqrd) {
            sqrd = leaf_sqrd;
            descendant = subtree;
          }
        }
      } else { // do the recursion case, left and right part
        if (std::static_pointer_cast<AABBTree>(subtree_copy)->left != nullptr) {
          Queue.push(std::make_pair(point_box_squared_distance(query, (std::static_pointer_cast<AABBTree>)(subtree_copy)->left->box),
                                    (std::static_pointer_cast<AABBTree>)(subtree_copy)->left));
        }
        if (std::static_pointer_cast<AABBTree>(subtree_copy)->right != nullptr) {
          Queue.push(std::make_pair(point_box_squared_distance(query, (std::static_pointer_cast<AABBTree>)(subtree_copy)->right->box),
                                    (std::static_pointer_cast<AABBTree>)(subtree_copy)->right));
        }
      }
    }
  }

  return sqrd != std::numeric_limits<double>::infinity();
  ////////////////////////////////////////////////////////////////////////////
}
