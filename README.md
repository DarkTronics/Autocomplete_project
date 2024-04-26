# Cross-project-cs375
Cross project cs375 Xinwei, Andrew, Daniel

Priority logic:
- Each node stores its own key and the index of its highest-key ("favorite") child
- Insertion procedure, traversing letters in the input string:
    - If current node has no favorite (-1) or input key > current node's favorite's key (curr->children[curr->favorite]->key), current node's favorite is updated to the input string (the current character). This means that each non-leaf's key is equal to that of its highest-key descendant.
    - If input key > next node's, update next node's key. 

TODO: maybe a GUI or something