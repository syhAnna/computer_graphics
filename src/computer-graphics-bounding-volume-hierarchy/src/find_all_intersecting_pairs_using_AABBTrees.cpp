#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // Consider the algorithm from the assignment handout
  std::list<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> >> Q;

  if (box_box_intersect(rootA->box, rootB->box)) {
    Q.push_back(std::make_pair(rootA, rootB));
  }

  while (!Q.empty()) {
    std::shared_ptr<Object> nodeA = Q.front().first;
    std::shared_ptr<Object> nodeB = Q.front().second;
    Q.pop_front();

    auto nodeA_ptr = std::dynamic_pointer_cast<AABBTree> (nodeA);
    auto nodeB_ptr = std::dynamic_pointer_cast<AABBTree> (nodeB);

    if (!nodeA_ptr && !nodeB_ptr) { // both nodeA and nodeB are leaves
      leaf_pairs.push_back(std::make_pair(nodeA, nodeB));
    } else if (!nodeA_ptr) { // nodeA is leaf
      if ((nodeB_ptr->left != nullptr) && (box_box_intersect(nodeA->box, nodeB_ptr->left->box))) {
        Q.push_back(std::make_pair(nodeA, nodeB_ptr->left));
      }
      if ((nodeB_ptr->right != nullptr) && (box_box_intersect(nodeA->box, nodeB_ptr->right->box))) {
        Q.push_back(std::make_pair(nodeA, nodeB_ptr->right));
      }
    } else if (!nodeB_ptr) { // nodeB is leaf
      if ((nodeA_ptr->left != nullptr) && (box_box_intersect(nodeA_ptr->left->box, nodeB->box))) {
        Q.push_back(std::make_pair(nodeA_ptr->left, nodeB));
      }
      if ((nodeA_ptr->right != nullptr) && (box_box_intersect(nodeA_ptr->right->box, nodeB->box))) {
        Q.push_back(std::make_pair(nodeA_ptr->right, nodeB));
      }
    } else { // both nodeA and nodeB are subtrees
      // remember to check none
      if ((nodeA_ptr->left != nullptr) && (nodeB_ptr->left != nullptr) &&
      (box_box_intersect(nodeA_ptr->left->box, nodeB_ptr->left->box))) {
        Q.push_back(std::make_pair(nodeA_ptr->left, nodeB_ptr->left));
      }
      if ((nodeA_ptr->left != nullptr) && (nodeB_ptr->right != nullptr) &&
      (box_box_intersect(nodeA_ptr->left->box, nodeB_ptr->right->box))) {
        Q.push_back(std::make_pair(nodeA_ptr->left, nodeB_ptr->right));
      }
      if ((nodeA_ptr->right != nullptr) && (nodeB_ptr->right != nullptr) &&
      (box_box_intersect(nodeA_ptr->right->box, nodeB_ptr->right->box))) {
        Q.push_back(std::make_pair(nodeA_ptr->right, nodeB_ptr->right));
      }
      if ((nodeA_ptr->right != nullptr) && (nodeB_ptr->left != nullptr) &&
      (box_box_intersect(nodeA_ptr->right->box, nodeB_ptr->left->box))) {
          Q.push_back(std::make_pair(nodeA_ptr->right, nodeB_ptr->left));
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
