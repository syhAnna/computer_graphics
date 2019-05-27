#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // consider algorithm from book: Fundamentals of Computer Graphics; p305
  // construct the bounding box
  int N = static_cast<int>(objects.size());
  int depth = this->depth;
  int AXIS = 3;

  // insert each object's box into the largest bounding box
  // first put each object's box into the largest box -> initialization
  for (const auto &object : objects) {
    insert_box_into_box(object->box, this->box);
  }

  if (N == 1) { // only one object
    this->left = objects[0];  // define to put it into left
    this->right = nullptr;

    // construct the box
    // the box size defined by the only object -> i.e.: with index 0
    this->box = BoundingBox(objects[0]->box.min_corner, objects[0]->box.max_corner);

    // (A, B) -> grow B by inserting A
    insert_box_into_box(this->left->box, this->box);
  } else if (N == 2) { // there are 2 objects
    this->left = objects[0];
    this->right = objects[1];

    // just insert, no need to construct, since have already constructed when only 1 object
    insert_box_into_box(this->left->box, this->box);
    insert_box_into_box(this->right->box, this->box);
  } else { // recursion
    std::vector<std::shared_ptr<Object> > left_partition;
    std::vector<std::shared_ptr<Object> > right_partition;
    double box_length;
    double midpoint = -std::numeric_limits<double>::infinity();
    double max_length = -std::numeric_limits<double>::infinity();
    int max_axis = -1;

    // find the midpoint m of the bounding box of A along AXIS (3)
    // and find the maximum midpoint

    for (int i = 0; i < AXIS; i++) {
      box_length = this->box.max_corner[i] - this->box.min_corner[i];
      if (box_length > max_length) {
        max_length = box_length;
        midpoint = (this->box.max_corner[i] + this->box.min_corner[i]) / 2;
        max_axis = i;
      }
    }

    // partition A into lists with lengths k and (N − k) surrounding m
    for (const auto &object : objects) {
      if (object->box.center()[max_axis] <= midpoint) { // left partition
        left_partition.push_back(object);
      } else { // right partition
        right_partition.push_back(object);
      }
    }

    // check the empty partition
    // if either one is empty get one item from the non-empty to empty
    if (left_partition.empty()) {
      left_partition.push_back(right_partition.back());
      right_partition.pop_back();
    }

    if (right_partition.empty()) {
      right_partition.push_back(left_partition.back());
      left_partition.pop_back();
    }

    this->left = std::make_shared<AABBTree>(left_partition, depth+1);
    this->right = std::make_shared<AABBTree>(right_partition, depth+1);
  }
  ////////////////////////////////////////////////////////////////////////////
}

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // consider algorithm from book: Fundamentals of Computer Graphics; p303
  std::shared_ptr<Object>  left;
  std::shared_ptr<Object>  right;

  if (ray_intersect_box(ray, this->box, min_t, max_t)) {
    bool left_hit, right_hit;
    double left_t, right_t;

    left_hit = (this->left) && this->left->ray_intersect(ray, min_t, max_t, left_t, left);
    right_hit = (this->right) && this->right->ray_intersect(ray, min_t, max_t, right_t, right);

    if(left_hit && (!left)){
      left = this->left;
    }
    if(right_hit && (!right)){
      right = this->right;
    }

    if (left_hit && right_hit) {
      if (left_t < right_t) { // find the closest
        t = left_t;
        descendant = left;
      } else {
        t = right_t;
        descendant = right;
      }
      return true;
    } else if (left_hit) {
      t = left_t;
      descendant = left;
      return true;
    } else if (right_hit) {
      t = right_t;
      descendant = right;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}
