#include "row.h"

namespace db{
    row::row(int n){
        r.resize(n);
    }

    int row::size(){
        return r.size();
    }

    rowtypes& row::operator[](int x){
        return r[x];
    }
}