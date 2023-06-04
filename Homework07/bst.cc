#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
// TODO: Implement this
   key = 0;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
}
// Constructor
Node::Node(int in) {
// TODO: Implement this
   key = in;
   parent = nullptr;
   left = nullptr;
   right = nullptr;
}
// Destructor
Node::~Node() {
// TODO: Implement this
   
}

// Add parent 
void Node::add_parent(Node* in) {
// TODO: Implement this
   this->parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
// TODO: Implement this
   this->left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
// TODO: Implement this
   this->right = in;
}

// Get key
int Node::get_key()
{
// TODO: Implement this
   return this->key;
}
// Get parent node
Node* Node::get_parent()
{
// TODO: Implement this
   return this->parent;
}
// Get left node
Node* Node::get_left()
{
// TODO: Implement this
   return this->left;
}
// Get right node
Node* Node::get_right()
{
// TODO: Implement this
   return this->right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
// TODO: Implement this
   if(in != nullptr){ //recursively call while not null
	   inorder_walk(in->get_left(), to);
	   in->print_info(to);
	   inorder_walk(in->get_right(), to);
   }
}
// Constructor
BST::BST()
{
// TODO: Implement this
   root = nullptr;
}
// Destructor
void destruct_inorder(Node* in)
{
    if(in == nullptr) {
        return;
    }
    destruct_inorder(in->get_left());
    destruct_inorder(in->get_right());
    delete in;
}
BST::~BST()
{
// TODO: Implement this
    destruct_inorder(root); //free the BST
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
// TODO: Implement this
    Node* current = this->root; //root node will be our start/current node
    Node* tmp = nullptr; //tmp node to hold current in the loop
    while(current != nullptr){
        tmp = current;
	if(in->get_key() < current->get_key()){ //check to see if we need to go to left subtree or right
            current = current->get_left();
	} else {
            current = current->get_right();
	}
    }
    in->add_parent(tmp); //add parent
    if(tmp == nullptr){
	    this->root = in; //update root value if tmp is null
    } else { //otherwise we check to see if the in->key is greater than tmp->key and add the node to the left or right
	    if(in->get_key() < tmp->get_key()){
		    tmp->add_left(in);
	    } else { 
		    tmp->add_right(in);
	    }
    }
}
       
// Delete a node to the subtree
void BST::delete_node(Node* out)
{
// TODO: Implement this
//
   // Create temporary nodes to handle reassignment
   Node* tmp1 = nullptr;
   Node* tmp2 = nullptr;
   // Check if the node to be deleted has one or no children
   if( out->get_left() == nullptr || out->get_right() == nullptr){
	   tmp1 = out;// If so, assign tmp1 to the node to be deleted
   } else {
	   tmp1 = this->get_succ(out);// Otherwise, find the successor of the node to be deleted and assign it to tmp1

   }
   if(tmp1->get_left() != nullptr){// Determine the child of tmp1 to be reassigned
	   tmp2 = tmp1->get_left();
   } else {
	   tmp2 = tmp1->get_right();
   }

   if(tmp2 != nullptr){// Reassign the child node's parent to tmp1 parent
	   tmp2->add_parent(tmp1->get_parent());
   }

   if(tmp1->get_parent() == nullptr){// Update the root if tmp1 was the root node
	   root = tmp2;
   } else if(tmp1 == tmp1->get_parent()->get_left()){// Otherwise, update the appropriate child pointer of tmp1 parent
	   tmp1->get_parent()->add_left(tmp2);
   } else {
	   tmp1->get_parent()->add_right(tmp2);
   }
   if(tmp1 != out){// If tmp1 is not the same as the node to be deleted (out)
	   tmp1->add_parent(out->get_parent());// Update tmp1 parent and reconnect it to the tree
	   if(tmp1->get_parent() == nullptr){
		   root = tmp1;
	   } else {
		   if(out == out->get_parent()->get_left()){
			   tmp1->get_parent()->add_left(tmp1);
		   } else {
			   tmp1->get_parent()->add_right(tmp1);
		   }
	   }
	   // Reassign left and right children of tmp1
	   tmp1->add_left(out->get_left());
	   tmp1->add_right(out->get_right());
	   if(tmp1->get_left() != nullptr){// Update parent pointers of tmp1 children
		   tmp1->get_left()->add_parent(tmp1);
	   } 
	   if(tmp1->get_right() != nullptr){
                   tmp1->get_right()->add_parent(tmp1);
           }
   }
   delete out; //delete the node for no mem leaks
}
// minimum key in the BST
Node* BST::tree_min()
{
// TODO: Implement this
    return get_min(root);
}
// maximum key in the BST
Node* BST::tree_max()
{
// TODO: Implement this
 return get_max(root); 
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
// TODO: Implement this
   Node* tmp = in;
   while(tmp->get_left() != nullptr){
	   tmp = tmp->get_left(); //get the left most node in the tree aka the smallest value
   }
   return tmp;
}

// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
// TODO: Implement this
   Node* tmp = in;
   while(tmp->get_right() != nullptr){
           tmp = tmp->get_right(); //get the right most node in the tree aka the max
   }
   return tmp;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
// TODO: Implement this
   Node* current = in;
   if(current == tree_max()){
	   return nullptr;
   }
   if(current->get_right() != nullptr){
	   return get_min(current->get_right());//get the minimum of the right which is the successor
   }
   Node* tmp = current->get_parent();
   while(tmp != nullptr && current == tmp->get_right()){
	   current = tmp;
	   tmp = tmp->get_parent();
   }
   return tmp;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
// TODO: Implement this
   Node* current = in;
   if(current == tree_min()){
	   return nullptr;
   }
   if(current->get_left() != nullptr){
	   return get_max(current->get_left()); //opposite of successor to get the predecessor
   }
   Node* tmp = current->get_parent();
   while(tmp != nullptr && current == tmp->get_left()){
	   current = tmp;
	   tmp = tmp->get_parent();
   }
   return tmp;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
// TODO: Implement this
   inorder_walk(root, to); //call inorder_walk
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
// TODO: Implement this
   Node* temp = root;
   while(temp != nullptr && search_key != temp->get_key()){//while not null or value other than key
	   if(search_key < temp->get_key()){ //if less than go left
		   temp = temp->get_left();
	   } else { //otherwise go right
		   temp = temp->get_right();
	   }
   }
   return temp;
}
// ---------------------------------------
