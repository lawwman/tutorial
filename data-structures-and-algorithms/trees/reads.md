# Complexity of Trees Vs other lists and arrays
- **Access/Search**: Array > Trees (with ordering like BST) > Linked List
  - Array is O(1) if index known
  - BST is O(h), h = height
  - Linked List, O(N) to slowly go through list
- **Insert/Delete**: Linked List > BST > Array
  - Linked List is O(1) if I have the reference already.
  - BST is O(h)
  - Array worst case is O(N) if I'm deleting the first position

Sources:
- https://en.wikipedia.org/wiki/Search_data_structure
- https://www.geeksforgeeks.org/complexity-different-operations-binary-tree-binary-search-tree-avl-tree/

# Properties
Assumptions:
- *Level of root: 0*
- *Height of root: 1*

Properties:
1. max number of nodes at lvl L = 2^L.
2. max number of nodes of height H = 2^H - 1
3. min height of N nodes = log2(N+1)

*Point 3 is derieved from point 2.*
- N = 2^H - 1 // point 2
- N + 1 = 2^H
- log2(N+1) = H

# Traversal

## Inorder (Left, Root, Right)
*In the case of binary search trees (BST), Inorder traversal gives nodes in non-decreasing order.*

**Algorithm Inorder(tree)**
   1. Traverse the left subtree, i.e., call Inorder(left-subtree)
   2. Visit the root.
   3. Traverse the right subtree, i.e., call Inorder(right-subtree)

> Visits nodes in order of increasing value. For a BST that contains [1, ..., 5], nodes visit in the order: 1, 2, 3, 4, 5.

## Preorder (Root, Left, Right)

**Algorithm Preorder(tree)**
   1. Visit the root.
   2. Traverse the left subtree, i.e., call Preorder(left-subtree)
   3. Traverse the right subtree, i.e., call Preorder(right-subtree)

## Postorder (Left, Right, Root)

**Algorithm Postorder(tree)**
   1. Traverse the left subtree, i.e., call Postorder(left-subtree)
   2. Traverse the right subtree, i.e., call Postorder(right-subtree)
   3. Visit the root.