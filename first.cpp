class Node{
Node *links[26];
bool flag;
public:
Node(){
    flag=false;
    for(int i=0;i<26;i++){
        links[i]=NULL;
    }
}
bool notcontains(char ch){
    return (links[ch-'a']==NULL);
}
void put(char ch, Node *node){
    links[ch-'a']=node;
}
Node * get(char ch){
    return links[ch-'a'];
}
bool isend(){
    return flag;
}
void istrue(){
     flag=true;
}
};
class Trie {
    Node *root;
public:
    Trie() {
        root=new Node;
    }
    
    void insert(string word) {
        Node *node=root;
        for(int i=0;i<word.size();i++){
            if(node->notcontains(word[i])){
                node->put(word[i],new Node);
            }
            node=node->get(word[i]);
        }
        node->istrue();
    }
    
    bool search(string word) {
        Node *node=root;
        for(int i=0;i<word.size();i++){
             if(node->notcontains(word[i])){
                return false;
            }
            node=node->get(word[i]);
        }
        return node->isend();
    }
    
    bool startsWith(string prefix) {
        Node*node=root;
        for(int i=0;i<prefix.size();i++){
             if(node->notcontains(prefix[i])){
                return false;
            }
            node=node->get(prefix[i]);
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
