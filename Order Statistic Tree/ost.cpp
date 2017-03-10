#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int ,null_type,less<int>,rb_tree_tag,
              tree_order_statistics_node_update>pbd_set;
/*This Function sorts the Data in increasing order and then Retrieves
  information by order on the n-th level from lowest to highest 
  every operation is fastest possible */              
  
int main(){
    pbd_set s;
    s.insert(4);s.insert(11);s.insert(12);s.insert(1);s.insert(7); //insert
    s.erase(4);                                                    //erase

    int n=4,ans;n--;
    if(s.order_of_key(n) != s.end()){                             //find
       ans = *s.order_of_key(n);printf("%d\n",ans);}
    else printf("invalid\n");

}
