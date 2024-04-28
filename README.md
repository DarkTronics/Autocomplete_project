# Cross-project-cs375
Cross project cs375 Xinwei, Andrew, Daniel

A basic implementation of auto-complete using a k-ary tree (Trie). 

Priority logic:
- Each node stores its own key and the index of its highest-key ("favorite") child
- Insertion procedure, traversing letters in the input string:
    - If current node has no favorite (-1) or input key > current node's favorite's key (curr->children[curr->favorite]->key), current node's favorite is updated to the input string (the current character). This means that each non-leaf's key is equal to that of its highest-key descendant.
    - If input key > next node's, update next node's key. 
    - Before moving to the next letter, increment the key. This way, the children have higher keys (which we can check for), preventing us from getting stuck at an irrelevant parent when searching for a suggestion.

TODO: 
- maybe find a better input list with less fake words
    - got mine from: https://martinweisser.org/corpora_site/word_lists.html
- implement top 10 or top 5 suggestions
- maybe a GUI or something
